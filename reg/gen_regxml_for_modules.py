#import cxxheaderparser as cxxhp
import re
import json

from cxxheaderparser.simple import parse_file, ParsedData
from cxxheaderparser.options import ParserOptions
from cxxheaderparser.preprocessor import make_gcc_preprocessor
from cxxheaderparser.types import Type, NameSpecifier, Array, Value, Pointer
import sys
import os
from regobjects import *
import xml.etree.ElementTree as ET


PROJECT_PATH = ".."
REGXML2_FILENAME = "reglist.regxml2"

ENCODING = 'utf-8'
EXCLUDE_DIRS = ["CANopenNode", "slcan", "tmp", "Debug", "Release", "MCU", "Desktop", "OD.h", "reg", "iqmath", "utils", "bits", "CMSIS_5", "mtb-xmclib-cat3"]

CPP_INCS = [PROJECT_PATH, os.path.join(PROJECT_PATH, "CANopenNode"),
            os.path.join(PROJECT_PATH, "CMSIS_5/CMSIS/Core/Include"),
            os.path.join(PROJECT_PATH, "mtb-xmclib-cat3/CMSIS/Infineon/COMPONENT_XMC4500/Include")]
CPP_DEFS = ["PORT_KIT_XMC45_RELAX_LITE_V1", "SYSLOG_GLOBAL"]

IGNORE_FIELDS_PREFIXES = ["m_"]
REMOVE_PREFIXES = ["p_", "r_"]
PARAM_PREFIX = "p_"

MAX_LINE_ARRAY_LEN = 64

BEGIN_INDEX = 0x2000
STEP_INDEX = 0x10



def makeParseOpts(incs: list[str] or None = None, defs: list[str] or None = None) -> ParserOptions:
    opts_incs = CPP_INCS.copy()
    opts_defs = CPP_DEFS.copy() + ['_Static_assert(...)=']
    if incs:
        for inc in incs:
            opts_incs.append(os.path.join(PROJECT_PATH, inc))
    if defs:
        opts_defs = opts_defs + defs
    opts = ParserOptions()
    opts.preprocessor = make_gcc_preprocessor(gcc_args=['gcc', '-std=c17'], include_paths=opts_incs, defines=opts_defs)
    opts.verbose = False
    opts.convert_void_to_zero_params = True
    return opts


class CType:

    _c_to_regdata_types = {
        'int': DataType.I32,
        'unsigned int': DataType.U32,
        'iql_t': DataType.I32,
        'control_t': DataType.U32,
        'status_t': DataType.U32,
        'warning_t': DataType.U32,
        'error_t': DataType.U32,
        'flag_t': DataType.U32,
        'strobe_t': DataType.U32,
        'state_t': DataType.U32,
        'int8_t': DataType.I8,
        'int16_t': DataType.I16,
        'int32_t': DataType.I32,
        'uint8_t': DataType.U8,
        'uint16_t': DataType.U16,
        'uint32_t': DataType.U32,
        'iq7_t': DataType.IQ7,
        'iq15_t': DataType.IQ15,
        'iq24_t': DataType.IQ24,
        'reg_i8_t': DataType.I8,
        'reg_i16_t': DataType.I16,
        'reg_i32_t': DataType.I32,
        'reg_u8_t': DataType.U8,
        'reg_u16_t': DataType.U16,
        'reg_u32_t': DataType.U32,
        'reg_iq7_t': DataType.IQ7,
        'reg_iq15_t': DataType.IQ15,
        'reg_iq24_t': DataType.IQ24,
    }

    @staticmethod
    def toRegDataType(cType: str) -> int:
        if cType in CType._c_to_regdata_types:
            return CType._c_to_regdata_types[cType]
        return DataType.I32


class Var:
    typename: str
    is_const: bool
    is_param: bool
    name: str
    count: int  # == 0 - var, > 0 - array.
    comment: str
    id: int or None
    rpdo: bool
    tpdo: bool
    base_name: str or None
    noconf: bool

    def __init__(self, vType: str, vName: str, vCount: int = 0):
        self.typename = vType
        self.is_const = False
        self.is_param = False
        self.name = vName
        self.count = vCount
        self.comment = ""
        self.id = None
        self.rpdo = False
        self.tpdo = False
        self.base_name = None
        self.noconf = False

    def __repr__(self):
        if self.count == 0:
            return self.typename + " " + self.name
        return self.typename + " " + self.name + "[" + str(self.count) + "]"


class Struct:
    typename: str
    fields: list[Var]

    def __init__(self, sType):
        self.typename = sType
        self.fields = []

    def addField(self, fVar: Var):
        self.fields.append(fVar)

    def __repr__(self):
        return self.typename + str(self.fields)


def getHeaders(path: str, excludes: list[str] = None) -> list[str]:
    headers: list[str] = []
    entries: list[str] = os.listdir(path)
    if excludes:
        for exclude in excludes:
            if exclude in entries:
                entries.remove(exclude)
    entries = [e for e in entries if not e.startswith('.')]
    for entry in entries:
        if os.path.isdir(os.path.join(path, entry)):
            entryHeaders: list[str] = getHeaders(os.path.join(path, entry), excludes)
            for e in entryHeaders:
                headers.append(os.path.join(entry, e))
        else:
            if entry.endswith(".h"):
                headers.append(entry)
    return headers


def getComment(comment: str) -> str:
    if not comment:
        return str()
    com = comment.replace("//!<", "")\
                 .replace("//!", "")\
                 .replace("//", "")\
                 .replace("/*", "")\
                 .replace("*/", "").strip()
    return com

def getJson(doxygen_comment: str) -> tuple[str or None, map or None]:
    json_data = None
    if doxygen_comment is not None:
        if not hasattr(getJson, "prog") or getJson.prog is None:
            getJson.prog = re.compile(r"@(\{.*\})")
        json_match = getJson.prog.search(doxygen_comment)
        if json_match is not None:
            # remove json from comment
            doxygen_comment = doxygen_comment[0:json_match.span()[0]] + doxygen_comment[json_match.span()[1]:]
            # parse json insertion
            json_group = json_match.group(1)
            try:
                json_data = json.loads(json_group)
            except json.JSONDecodeError as e:
                print("Error decode json ", json_group, ": ", e, sep='')
    return doxygen_comment, json_data


def getVars(parse_data: ParsedData) -> list[Var]:
    # regexp for json insertion
    # @{"param0": value0, "param1": value1}
    prog = re.compile(r"@(\{.*\})")
    variables: list[Var] = []
    for var in parse_data.namespace.variables:
        #print(var)
        var_id = None
        var_no_conf = False
        doxygen_comment, json_data = getJson(var.doxygen)
        #process json insertion
        if json_data is not None:
            var_id = json_data.get("id", None)
            var_no_conf = json_data.get("noconf", False)
        if isinstance(var.type, Type):  # or not isinstance(fld.type.typename.segments[0], NameSpecifier):
            var_name = var.name.segments[0].name
            var_type = var.type.typename.segments[0].name
            var_comment = getComment(doxygen_comment)
            v = Var(var_type, var_name)
            if var_name.startswith(PARAM_PREFIX):
                v.is_param = True
            v.is_const = var.type.const
            v.comment = var_comment
            v.id = var_id
            v.noconf = var_no_conf
            variables.append(v)
        elif isinstance(var.type, Array):
            #print(fld)
            arr_size = int(var.type.size.tokens[0].value)
            arr_type = var.type.array_of.typename.segments[0].name
            arr_name = var.name.segments[0].name
            arr_comment = getComment(doxygen_comment)
            #print(arr_name)
            v = Var(arr_type, arr_name, arr_size)
            if arr_name.startswith(PARAM_PREFIX):
                v.is_param = True
            v.comment = arr_comment
            v.id = var_id
            v.noconf = var_no_conf
            variables.append(v)

    return variables


def getArraySize(fldSize: Value) -> int:
    szStr = ""
    for tkn in fldSize.tokens:
        szStr = szStr + tkn.value
    szi = eval(szStr)
    return szi


def collectData(header: str) -> list[Struct]:
    structs: list[Struct] = []
    typedefs: dict = {}
    parse_data = parse_file(os.path.join(PROJECT_PATH, header),
                            encoding=ENCODING,
                            options=makeParseOpts(incs=[os.path.dirname(header)]))
    for td in parse_data.namespace.typedefs:
        #print(td, isinstance(td.type, Type))
        if not isinstance(td.type, Type) or not isinstance(td.type.typename.segments[0], NameSpecifier):
            continue
        td_type = td.type.typename.segments[0].name
        td_name = td.name
        if td.type.typename.classkey and td.type.typename.classkey == 'struct':
            typedefs[td_type] = td_name
        else:
            typedefs[td_name] = td_type
    #print(typedefs)
    for cs in parse_data.namespace.classes:
        #print(cs, isinstance(cs.class_decl.typename.segments[0], NameSpecifier))
        if not isinstance(cs.class_decl.typename.segments[0], NameSpecifier):
            continue
        struct_type = cs.class_decl.typename.segments[0].name
        if struct_type in typedefs:
            struct_type = typedefs[struct_type]
        structure = Struct(struct_type)
        for fld in cs.fields:
            #print(fld)
            if not fld.name:
                continue
            excludeByPrefix = False
            for prefix in IGNORE_FIELDS_PREFIXES:
                #print(prefix, fld)
                if fld.name and fld.name.startswith(prefix):
                    excludeByPrefix = True
                    break
            if excludeByPrefix:
                continue
            fld_id = None
            fld_rpdo = False
            fld_tpdo = False
            fld_base_name = None
            doxygen_comment, json_data = getJson(fld.doxygen)
            #process json insertion
            if json_data is not None:
                fld_id = json_data.get("id", None)
                fld_rpdo = json_data.get("rpdo", False)
                fld_tpdo = json_data.get("tpdo", False)
                fld_base_name = json_data.get("base", None)
            if isinstance(fld.type, Type): # or not isinstance(fld.type.typename.segments[0], NameSpecifier):
                field_name = fld.name
                field_type = fld.type.typename.segments[0].name
                if field_type in typedefs:
                    field_type = typedefs[field_type]
                field_comment = getComment(doxygen_comment)
                v = Var(field_type, field_name)
                if field_name.startswith(PARAM_PREFIX):
                    v.is_param = True
                v.is_const = fld.type.const
                v.comment = field_comment
                v.id = fld_id
                v.rpdo = fld_rpdo
                v.tpdo = fld_tpdo
                v.base_name = fld_base_name
                structure.addField(v)
            elif isinstance(fld.type, Array):
                #print(fld)
                arr_name = fld.name
                arr_size = getArraySize(fld.type.size) #int(fld.type.size.tokens[0].value)
                arr_type = fld.type.array_of.typename.segments[0].name
                if arr_type in typedefs:
                    arr_type = typedefs[arr_type]
                arr_comment = getComment(doxygen_comment)
                v = Var(arr_type, arr_name, arr_size)
                if arr_name.startswith(PARAM_PREFIX):
                    v.is_param = True
                v.is_const = fld.type.array_of.const
                v.comment = arr_comment
                v.id = fld_id
                v.rpdo = fld_rpdo
                v.tpdo = fld_tpdo
                v.base_name = fld_base_name
                structure.addField(v)
        structs.append(structure)
    return structs


def getVarStruct(varTypeName: str, structs: list[Struct]) -> Struct or None:
    for s in structs:
        if varTypeName == s.typename:
            return s
    return None


def getDefaultRegEntry(name: str, index: int) -> RegEntry:
    re = RegEntry()
    re.name = name
    re.objectType = ObjectType.REC
    re.index = index
    return re


def getDefaultRegVar(name: str, subIndex: int) -> RegVar:
    rv = RegVar()
    rv.name = name
    rv.subIndex = subIndex
    rv.flags = RegFlag.NONE
    rv.eflags = RegEFlag.CO_SDO_R
    rv.count = 1
    rv.dataType = DataType.I32
    return rv


def getRegFlagsEFlags(fieldVar: Var) -> tuple[int, int]:
    flags = 0
    eflags = RegEFlag.CO_SDO_R

    if fieldVar.is_param:
        flags = flags | RegFlag.CONF

    if fieldVar.is_const:
        flags = flags | RegFlag.READONLY
    else:
        eflags = eflags | RegEFlag.CO_SDO_W

    if fieldVar.rpdo:
        eflags = eflags | RegEFlag.CO_RPDO
    if fieldVar.tpdo:
        eflags = eflags | RegEFlag.CO_TPDO

    return flags, eflags


def getRegVar(memPath: str, subIndex: int, fieldVar: Var, name: str or None, structs: list[Struct]) -> list[RegVar] or None:
    #print(subIndex, fieldVar)
    regVars: list[RegVar] = []
    varName: str
    if name:
        varName = name
    else:
        varName = fieldVar.name
    for prefix in REMOVE_PREFIXES:
        if varName.startswith(prefix):
            varName = varName[len(prefix):]
    fieldStruct = getVarStruct(fieldVar.typename, structs)
    #print(fieldStruct)
    if not fieldStruct:
        if fieldVar.count == 0:
            rv = getDefaultRegVar(varName, subIndex)
            rv.dataType = CType.toRegDataType(fieldVar.typename)
            rv.memAddr = f"{memPath}.{fieldVar.name}" # &
            rv.flags, rv.eflags = getRegFlagsEFlags(fieldVar)
            rv.description = fieldVar.comment
            regVars.append(rv)
            #print(rv)
        else:
            if fieldVar.count <= MAX_LINE_ARRAY_LEN:
                for i in range(0, fieldVar.count):
                    rv = getDefaultRegVar(f"{varName}{i}", subIndex)
                    rv.dataType = CType.toRegDataType(fieldVar.typename)
                    rv.memAddr = f"{memPath}.{fieldVar.name}[{i}]" # &
                    rv.flags, rv.eflags = getRegFlagsEFlags(fieldVar)
                    rv.description = fieldVar.comment
                    regVars.append(rv)
                    subIndex = subIndex + 1
                    #print(rv)
            else: # DOMAIN
                rv = getDefaultRegVar(varName, subIndex)
                rv.dataType = DataType.MEM
                rv.memAddr = f"{memPath}.{fieldVar.name}" # &
                rv.count = DataType.getSize(CType.toRegDataType(fieldVar.typename)) * fieldVar.count
                rv.flags, rv.eflags = getRegFlagsEFlags(fieldVar)
                rv.description = fieldVar.comment
                regVars.append(rv)
                # print(rv)
    else:
        if fieldVar.count == 0:
            newMemPath = f"{memPath}.{fieldVar.name}"
            for field in fieldStruct.fields:
                rvs = getRegVar(newMemPath, subIndex, field, f"{varName}_{field.name}", structs)
                if rvs:
                    for rv in rvs:
                        regVars.append(rv)
                subIndex = subIndex + len(rvs)
        else:
            for i in range(0, fieldVar.count):
                for field in fieldStruct.fields:
                    newMemPath = f"{memPath}.{fieldVar.name}[{i}]"
                    rvs = getRegVar(newMemPath, subIndex, field, f"{varName}{i}_{field.name}", structs)
                    if rvs:
                        for rv in rvs:
                            regVars.append(rv)
                    subIndex = subIndex + len(rvs)
    #print(regVars)
    return regVars


def getRegEntry(index: int, entryVar: Var, entryType: Struct, structs: list[Struct]) -> RegEntry:
    re = getDefaultRegEntry(entryVar.name, index)
    re.description = entryVar.comment
    cntVar: RegVar = getDefaultRegVar("count", 0)
    cntVar.dataType = DataType.U8
    cntVar.flags = cntVar.flags | RegFlag.READONLY
    cntVar.eflags = cntVar.eflags | RegEFlag.CO_COUNT
    cntVar.description = "Number of sub entries count"
    re.addVar(cntVar)

    # reg vars dict
    regVars: dict[int, RegVar] = dict()

    # set of predefined ids
    predef_ids = set()
    predef_ids.add(cntVar.subIndex)
    # collect predefined ids
    for field in entryType.fields:
        if field.id is not None:
            # if the id already exists
            if field.id in predef_ids:
                print("Ignoring duplicate predefined id in subentry", field.name)
                # remove it
                field.id = None
            else:
                predef_ids.add(field.id)

    subIndex = 1
    for field in entryType.fields:
        # predefined ids
        id = field.id
        if id is None:
            while subIndex in predef_ids:
                subIndex = subIndex + 1
            id = subIndex
        else:
            if id in regVars:
                rv_collis: Var = regVars.get(id)
                print("subindex", id, "collision:", re.name, field.name, "with", None if not rv_collis else rv_collis.name)
                id = id + 1

        rvs = getRegVar(re.name, id, field, None, structs)
        if rvs:
            for rv in rvs:
                # process entryVar attributes
                if entryVar.noconf:
                    rv.flags = rv.flags & ~RegFlag.CONF
                    #print("NoConf", rv.flags, entryVar.name)
                #print(rv)
                # correct id if subindex exists
                id = rv.subIndex
                while id in regVars:
                    id = id + 1
                rv.subIndex = id
                regVars[rv.subIndex] = rv
            if field.id is None:
                subIndex = id + 1

    regVarsList = list(dict(sorted(regVars.items())).values())
    for rv in regVarsList:
        re.addVar(rv)

    #print(re.regVars)
    cntVar.defValue = str(len(regVarsList))
    return re


def exportRegEntries(fileName: str, regentries: list[RegEntry]):
    root = ET.Element('RegEntries')
    tree = ET.ElementTree(root)
    for re in regentries:
        entry_xml_attrs = {
            'index': str(re.index)
        }
        entry_elem = ET.SubElement(root, 'RegEntry', entry_xml_attrs)
        ET.SubElement(entry_elem, 'name').text = re.name
        ET.SubElement(entry_elem, 'type').text = str(re.objectType)
        ET.SubElement(entry_elem, 'description').text = re.description
        vars_elem = ET.SubElement(entry_elem, 'RegVars')
        for rv in re.regVars:
            var_xml_attrs = {
                'subindex': str(rv.subIndex)
            }
            var_elem = ET.SubElement(vars_elem, 'RegVar', var_xml_attrs)
            ET.SubElement(var_elem, 'name').text = rv.name
            ET.SubElement(var_elem, 'type').text = str(rv.dataType)
            ET.SubElement(var_elem, 'count').text = str(1 if rv.count == 0 else rv.count)
            ET.SubElement(var_elem, 'memory').text = rv.memAddr
            ET.SubElement(var_elem, 'minimum').text = rv.minValue
            ET.SubElement(var_elem, 'maximum').text = rv.maxValue
            ET.SubElement(var_elem, 'default').text = rv.defValue
            ET.SubElement(var_elem, 'flags').text = str(rv.flags)
            ET.SubElement(var_elem, 'eflags').text = str(rv.eflags)
            ET.SubElement(var_elem, 'base_index').text = str(rv.baseIndex)
            ET.SubElement(var_elem, 'base_subindex').text = str(rv.baseSubIndex)
            ET.SubElement(var_elem, 'description').text = rv.description

    try:
        with open(fileName, "wb") as f:
            tree.write(f, encoding='utf-8', xml_declaration=True, method="xml")
    except OSError:
        print("Error write regs file: %s" % fileName)
        return


def getBase(base_name: str) -> tuple[str, str] or None:
    dot_pos: int = base_name.find(".")
    if dot_pos < 0:
        return None

    mod_name = base_name[0:dot_pos]
    if not mod_name:
        return None

    field_name = base_name[dot_pos+1:].replace(".", "_")
    if not field_name:
        return None

    return mod_name, field_name



def parseModules():
    parse_data = parse_file(os.path.join(PROJECT_PATH, "modules", "modules.h"), encoding=ENCODING,
                            options=makeParseOpts())

    incs: list[str] = []
    mods: list[Var] = []
    structs: list = []
    regentries_by_id: dict[int, RegEntry] = {}
    regentries_by_name: dict[str, RegEntry] = {}

    incs = getHeaders(PROJECT_PATH, EXCLUDE_DIRS)
    mods = getVars(parse_data)
    max_count = None # -1
    for inc in incs:
        if max_count is not None and max_count >= 0:
            if max_count != 0:
                max_count = max_count - 1
            else:
                break
        structs = structs + collectData(inc)
    # for inc in ["data_log\\data_log.h", "sys_main\\sys_main.h", "fsm\\fsm.h"]: #
    #     structs = structs + collectData(inc)

    #print(structs)

    # set of predefined ids
    predef_ids = set()
    # collect predefined ids
    for m in mods:
        if m.id is not None:
            # if the id already exists
            if m.id in predef_ids:
                print("Ignoring duplicate predefined id in module", m.name)
                # remove it
                m.id = None
            else:
                predef_ids.add(m.id)

    # for m in mods:
    #     print(m.name, m.id)

    index = BEGIN_INDEX

    for m in mods:
        ms: Struct = getVarStruct(m.typename, structs)
        if not ms:
            continue
        # predefined ids
        id = m.id
        if id is None:
            while index in predef_ids:
                index = index + STEP_INDEX
            id = index
        re = getRegEntry(id, m, ms, structs)
        regentries_by_id[id] = re
        regentries_by_name[re.name] = re
        index = index + STEP_INDEX


    # find base id's
    for m in mods:
        ms: Struct = getVarStruct(m.typename, structs)
        if not ms:
            continue
        m_re = regentries_by_name.get(m.name, None)
        if not m_re:
            print("Can't find module reg entry:", m.name)
            continue
        for fld in ms.fields:
            if fld.base_name:
                base_mod, base_fld = getBase(fld.base_name)
                if not base_mod or not base_fld:
                    print("Error in base name", fld.base_name)
                    continue

                base_re: RegEntry = regentries_by_name.get(base_mod, None)
                if not base_re:
                    print("Can't find base reg entry:", base_mod)
                    continue

                if not base_re.regVars:
                    continue

                base_re_fld: RegVar = None
                for re_fld in base_re.regVars:
                    #print(re_fld)
                    if fld.base_name == re_fld.memAddr or base_fld == re_fld.name:
                        base_re_fld = re_fld
                        break

                if not base_re_fld:
                    print("Can't find base field", base_fld, "in reg entry", base_re.name)
                    continue

                #full_id = (base_re.index << 8) | (base_re_fld.subIndex & 0xff)

                m_re_fld = None
                m_fld_mem = '.'.join([m_re.name, fld.name])
                for rv in m_re.regVars:
                    if rv.memAddr == m_fld_mem:
                        m_re_fld = rv
                        break

                if not m_re_fld:
                    print("Can't find module field", m_fld_mem)
                    continue

                m_re_fld.baseIndex = base_re.index
                m_re_fld.baseSubIndex = base_re_fld.subIndex
                #print("Found base", fld.base_name, ":", base_re.name, base_re_fld.name, full_id)
                #print(fld.name, fld.base_name, base_mod, base_fld)

    regentries = list(dict(sorted(regentries_by_id.items())).values())
    regentries_by_id.clear()
    regentries_by_name.clear()

    #print(regentries)
    #return

    # for re in regentries:
    #     print(re)
    #     for rv in re.regVars:
    #         print(rv)

    exportRegEntries(REGXML2_FILENAME, regentries)


def main():
    parseModules()


if __name__ == '__main__':
    main()

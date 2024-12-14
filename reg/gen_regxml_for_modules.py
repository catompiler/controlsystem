#import cxxheaderparser as cxxhp
from cxxheaderparser.simple import parse_file, ParsedData
from cxxheaderparser.options import ParserOptions
from cxxheaderparser.preprocessor import make_gcc_preprocessor
from cxxheaderparser.types import Type, NameSpecifier, Array, Value
import sys
import os
from regobjects import *
import xml.etree.ElementTree as ET


PROJECT_PATH = ".."
REGXML2_FILENAME = "reglist.regxml2"

ENCODING = 'utf-8'
EXCLUDE_DIRS = ["CANopenNode", "slcan", "tmp", "Debug", "Release", "OD.h", "reg", "iqmath", "utils", "bits"]

CPP_INCS = [PROJECT_PATH, os.path.join(PROJECT_PATH, "CANopenNode")]
CPP_DEFS = []

IGNORE_FIELDS_PREFIXES = ["m_"]
REMOVE_PREFIXES = ["p_", "r_"]

MAX_LINE_ARRAY_LEN = 64

BEGIN_INDEX = 0x2000
STEP_INDEX = 0x10



def makeParseOpts(incs: list[str] or None = None, defs: list[str] or None = None) -> ParserOptions:
    opts_incs = CPP_INCS.copy()
    opts_defs = CPP_DEFS.copy()
    if incs:
        for inc in incs:
            opts_incs.append(os.path.join(PROJECT_PATH, inc))
    if defs:
        opts_defs = opts_defs + defs
    opts = ParserOptions()
    opts.preprocessor = make_gcc_preprocessor(gcc_args=['gcc'], include_paths=opts_incs, defines=opts_defs)
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
    name: str
    count: int  # == 0 - var, > 0 - array.
    comment: str

    def __init__(self, vType: str, vName: str, vCount: int = 0):
        self.typename = vType
        self.name = vName
        self.count = vCount
        self.comment = ""

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


def getVars(parse_data: ParsedData) -> list[Var]:
    variables: list[Var] = []
    for var in parse_data.namespace.variables:
        #print(var)
        if isinstance(var.type, Type):  # or not isinstance(fld.type.typename.segments[0], NameSpecifier):
            var_name = var.name.segments[0].name
            var_type = var.type.typename.segments[0].name
            var_comment = getComment(var.doxygen)
            v = Var(var_type, var_name)
            v.comment = var_comment
            variables.append(v)
        elif isinstance(var.type, Array):
            # print(fld)
            arr_size = int(var.type.size.tokens[0].value)
            arr_type = var.type.array_of.typename.segments[0].name
            arr_name = var.name.segments[0].name
            arr_comment = getComment(var.doxygen)
            #print(arr_name)
            a = Var(arr_type, arr_name, arr_size)
            a.comment = arr_comment
            variables.append(a)

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
            excludeByPrefix = False
            for prefix in IGNORE_FIELDS_PREFIXES:
                #print(prefix, fld.name.startswith(prefix))
                if fld.name.startswith(prefix):
                    excludeByPrefix = True
                    break
            if excludeByPrefix:
                continue
            name = fld.name
            if isinstance(fld.type, Type):  # or not isinstance(fld.type.typename.segments[0], NameSpecifier):
                field_name = name
                field_type = fld.type.typename.segments[0].name
                if field_type in typedefs:
                    field_type = typedefs[field_type]
                field_comment = getComment(fld.doxygen)
                v = Var(field_type, field_name)
                v.comment = field_comment
                structure.addField(v)
            elif isinstance(fld.type, Array):
                #print(fld)
                arr_name = name
                arr_size = getArraySize(fld.type.size) #int(fld.type.size.tokens[0].value)
                arr_type = fld.type.array_of.typename.segments[0].name
                if arr_type in typedefs:
                    arr_type = typedefs[arr_type]
                arr_comment = getComment(fld.doxygen)
                a = Var(arr_type, arr_name, arr_size)
                a.comment = arr_comment
                structure.addField(a)
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
    rv.eflags = RegEFlag.CO_SDO_R | RegEFlag.CO_SDO_W
    rv.count = 1
    rv.dataType = DataType.I32
    return rv


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
            rv.description = fieldVar.comment
            regVars.append(rv)
            #print(rv)
        else:
            if fieldVar.count <= MAX_LINE_ARRAY_LEN:
                for i in range(0, fieldVar.count):
                    rv = getDefaultRegVar(f"{varName}{i}", subIndex)
                    rv.dataType = CType.toRegDataType(fieldVar.typename)
                    rv.memAddr = f"{memPath}.{fieldVar.name}[{i}]" # &
                    rv.description = fieldVar.comment
                    regVars.append(rv)
                    subIndex = subIndex + 1
                    #print(rv)
            else: # DOMAIN
                rv = getDefaultRegVar(varName, subIndex)
                rv.dataType = DataType.MEM
                rv.memAddr = f"{memPath}.{fieldVar.name}" # &
                rv.count = DataType.getSize(CType.toRegDataType(fieldVar.typename)) * fieldVar.count
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
    cntVar = getDefaultRegVar("count", 0)
    cntVar.dataType = DataType.U8
    cntVar.description = "Number of sub entries count"
    re.addVar(cntVar)

    subIndex = 1
    for field in entryType.fields:
        rvs = getRegVar(re.name, subIndex, field, None, structs)
        if rvs:
            for rv in rvs:
                # print(rv)
                re.addVar(rv)
            subIndex = subIndex + len(rvs)

    cntVar.defValue = str(0 if subIndex == 0 else subIndex - 1)
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
        with open(REGXML2_FILENAME, "wb") as f:
            tree.write(f, encoding='utf-8', xml_declaration=True, method="xml")
    except OSError:
        print("Error write regs file: %s" % REGXML2_FILENAME)
        return


def parseModules():
    parse_data = parse_file(os.path.join(PROJECT_PATH, "modules", "modules.h"), encoding=ENCODING,
                            options=makeParseOpts())

    incs: list[str] = []
    mods: list[Var] = []
    structs: list = []
    regentries: list[RegEntry] = []

    incs = getHeaders(PROJECT_PATH, EXCLUDE_DIRS)
    mods = getVars(parse_data)
    for inc in incs:
        structs = structs + collectData(inc)
    # for inc in ["data_log\\data_log.h", "sys_main\\sys_main.h", "fsm\\fsm.h"]: #
    #     structs = structs + collectData(inc)

    #print(structs)

    index = BEGIN_INDEX

    for m in mods:
        ms: Struct = getVarStruct(m.typename, structs)
        if not ms:
            continue
        re = getRegEntry(index, m, ms, structs)
        regentries.append(re)
        index = index + STEP_INDEX

    #print(regentries)
    # for re in regentries:
    #     print(re)
    #     for rv in re.regVars:
    #         print(rv)

    exportRegEntries(REGXML2_FILENAME, regentries)


def main():
    parseModules()


if __name__ == '__main__':
    main()

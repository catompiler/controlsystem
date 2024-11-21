# -*- coding: utf-8 -*-
# coding: utf8

import sys
import os
import xml.etree.ElementTree as ET


class ObjectType:
    VAR = 0
    ARR = 1
    REC = 2


class DataType:
    I32 = 0
    I16 = 1
    I8 = 2
    U32 = 3
    U16 = 4
    U8 = 5
    IQ24 = 6
    IQ15 = 7
    IQ7 = 8

    _str_to_type = {
        'I32': I32,
        'I16': I16,
        'I8': I8,
        'U32': U32,
        'U16': U16,
        'U8': U8,
        'IQ24': IQ24,
        'IQ15': IQ15,
        'IQ7': IQ7
    }

    @staticmethod
    def fromStr(str_type) -> int:
        if str_type not in DataType._str_to_type:
            return 0
        return DataType._str_to_type[str_type]


class RegFlag:
    NONE = 0
    CONF = 1
    READONLY = 2

    _str_to_flag = {
        'NONE': NONE,
        'CONF': CONF,
        'READONLY': READONLY
    }

    @staticmethod
    def fromStr(str_flag):
        if str_flag not in RegFlag._str_to_flag:
            return 0
        return RegFlag._str_to_flag[str_flag]

    @staticmethod
    def fromList(flags) -> int:
        res_flags = 0
        for str_flag in flags:
            flag = RegFlag.fromStr(str_flag)
            res_flags = res_flags | flag
        return res_flags


class RegEFlag:
    NONE = 0x0
    RL_HIDE = 0x1
    CO_HIDE = 0x2
    CO_COUNT = 0x4
    RESERVED = 0x8
    CON_CNT_NMT = 0x10
    CON_CNT_EM = 0x20
    CON_CNT_SYNC = 0x40
    CON_CNT_SYNC_PROD = 0x80
    CON_CNT_STORAGE = 0x100
    CON_CNT_TIME = 0x200
    CON_CNT_EM_PROD = 0x400
    CON_CNT_HB_CONS = 0x800
    CON_CNT_HB_PROD = 0x1000
    CON_CNT_SDO_SRV = 0x2000
    CON_CNT_SDO_CLI = 0x4000
    CON_CNT_RPDO = 0x8000
    CON_CNT_TPDO = 0x10000
    CO_SDO_R = 0x20000
    CO_SDO_W = 0x40000
    CO_TPDO = 0x80000
    CO_RPDO = 0x100000
    CO_TSRDO = 0x200000
    CO_RSRDO = 0x400000


def entrylist_find_base(entrylist: list, base: str) -> list:
    if not base:
        return [0, 0]
    entry_item = base.split('.')
    if len(entry_item) != 2:
        return [0, 0]
    entry_name = entry_item[0]
    item_name = entry_item[1]

    for entry in entrylist:
        if entry['name'] == entry_name:
            for item in entry['items']:
                if item['name'] == item_name:
                    return [entry['id'], item['id']]
                    # return (entry['id'] << 8) | (item['id'] & 0xff)

    return [0, 0]


def entrylist_fix_bases(entrylist: list) -> None:
    for entry in entrylist:
        for item in entry['items']:
            item['base'] = entrylist_find_base(entrylist, item['base'])


def reglist_to_entrylist(reglist: list) -> list:
    entrylist = []

    for entry in reglist:
        items = entry['items']
        items_count = len(items)
        if items_count == 0:
            continue

        cur_id = 0

        new_entry = {}
        new_entry['id'] = entry['id']
        new_entry['name'] = entry['name']
        new_entry['type'] = ObjectType.VAR
        new_entry['items'] = []

        if items_count > 1:
            var = {}
            var['id'] = 0
            var['name'] = 'count'
            var['data'] = None
            var['type'] = DataType.U8
            var['min'] = 0
            var['max'] = items_count
            var['def'] = items_count
            var['flags'] = RegFlag.NONE
            var['eflags'] = RegEFlag.CO_COUNT | RegEFlag.CO_SDO_R
            var['base'] = None
            new_entry['type'] = ObjectType.REC
            new_entry['items'].append(var)
            cur_id = 1

        for reg in entry['items']:
            var = {}
            var['id'] = cur_id
            var['name'] = reg['name']
            var['data'] = reg['data']
            var['type'] = DataType.fromStr(reg['type'])
            var['min'] = 0
            var['max'] = 0
            var['def'] = 0
            var['flags'] = RegFlag.fromList(reg['flags'])
            var['eflags'] = RegEFlag.CO_SDO_R | RegEFlag.CO_SDO_W
            var['base'] = reg['base']
            new_entry['items'].append(var)
            cur_id = cur_id + 1

        entrylist.append(new_entry)

    entrylist_fix_bases(entrylist)

    # for entry in entrylist:
    #     for item in entry['items']:
    #         print(item)

    return entrylist


def gen_reglist(decls) -> list or dict:
    reglist = []
    cur_entry = None

    for decl in decls:
        t = decl['type']
        d = decl['data']

        if t == "group":
            if cur_entry:
                reglist.append(cur_entry)

            grp_name = d['name'].lower()
            grp_id = d['id']

            cur_entry = {}
            cur_entry['id'] = grp_id
            cur_entry['name'] = grp_name
            cur_entry['items'] = []

        elif t == "reg":
            if not cur_entry:
                return {'error': "reg defined without entry!"}

            reg_name = d['name'].lower()
            reg_data = d['data']
            reg_type = d['type']
            reg_flags_list = d['flags']
            reg_base = None
            if d['base'] != 'NONE':
                reg_base = d['base'].lower()
            reg = {}
            # reg['id'] = len(cur_entry['items'])
            reg['name'] = reg_name
            reg['data'] = reg_data
            reg['type'] = reg_type
            reg['flags'] = reg_flags_list
            reg['base'] = reg_base

            cur_entry['items'].append(reg)
        elif t == "begin":
            pass
        elif t == "end":
            pass
        elif t == "blank":
            pass
        elif t == "comment":
            pass
        elif t == "macro":
            pass
        elif t == "include":
            pass

    if cur_entry:
        reglist.append(cur_entry)

    return reglist


def makeReadableName(name: str) -> str:
    res_name = name.replace("_", " ").title()
    return res_name


def gen_regxml(entrylist, f):
    root = ET.Element('RegEntries')
    tree = ET.ElementTree(root)
    for entry in entrylist:
        entry_xml_attrs = {
            'index': str(entry['id']),
            'name': makeReadableName(entry['name']),
            'type': str(entry['type']),
            'description': ""
        }
        entry_elem = ET.SubElement(root, 'RegEntry', entry_xml_attrs)
        vars_elem = ET.SubElement(entry_elem, 'RegVars')
        for var in entry['items']:
            data = var['data']
            if not data:
                data = ""
            var_xml_attrs = {
                'subindex': str(var['id']),
                'name': makeReadableName(var['name']),
                'type': str(var['type']),
                'count': "1",
                'memory': data,
                'minimum': str(var['min']),
                'maximum': str(var['max']),
                'default': str(var['def']),
                'flags': str(var['flags']),
                'eflags': str(var['eflags']),
                'base_index': str(var['base'][0]),
                'base_subindex': str(var['base'][1]),
                'description': ""
            }
            var_elem = ET.SubElement(vars_elem, 'RegVar', var_xml_attrs)
    tree.write(f, encoding='utf-8', xml_declaration=True, method="xml")


def make_reg_id(suffix):
    return "REG_ID_%s" % suffix


def make_reg_id_name(group_name, reg_name):
    return make_reg_id("_".join([group_name, reg_name]))


def make_reg_id_value(group_id, reg_id):
    return (group_id << 8) | reg_id


def make_reg_type_name(reg_type):
    return "REG_TYPE_%s" % reg_type


def make_reg_data(reg_data, reg_type):
    if reg_type == 'STR':
        if len(reg_data) == 0 or reg_data[0] != '"' or reg_data[-1] != '"':
            return "\"%s\"" % reg_data
        return reg_data
    elif reg_type == 'MEM':
        if reg_data == "NULL":
            return reg_data
    return "&%s" % reg_data


def make_reg_flags_str(reg_flags_list):
    flags_strs = ["REG_FLAG_%s" % flag for flag in reg_flags_list]
    return " | ".join(flags_strs)


def make_reg_base_id(reg_base):
    return make_reg_id("_".join(reg_base.split(".")))


def gen_ids(decls, f=sys.stdout):
    f.write("#ifndef REG_IDS_H\n")
    f.write("#define REG_IDS_H\n\n")

    grp_name = ""
    grp_id = 0
    reg_id = 0

    for decl in decls:
        t = decl['type']
        d = decl['data']

        if t == "group":
            grp_name = d['name']
            grp_id = d['id']
            reg_id = 0

        elif t == "reg":
            reg_name = d['name']
            f.write("#define %s    0x%x\n" % (make_reg_id_name(grp_name, reg_name), make_reg_id_value(grp_id, reg_id)))
            reg_id = reg_id + 1

        elif t == "blank":
            f.write("\n")
        elif t == "comment":
            f.write("%s\n" % d)
        # elif(t == "macro"):
        #     f.write("%s\n" % (d));

    f.write("\n#endif /* REG_IDS_H */\n")


def gen_regs(decls, f=sys.stdout):
    f.write("#ifndef REG_LIST_DATA_H\n")
    f.write("#define REG_LIST_DATA_H\n\n")

    grp_name = ""
    # reg_name = ""
    # beg_name = ""

    # for decl in decls:
    #     t = decl['type'];
    #     d = decl['data'];
    #
    #     if(t == "include"):
    #         f.write("%s\n" % (d));
    #         decls.remove(decl);

    # f.write("\nREGS_BEGIN(REG_ARRAY_NAME)\n\n");

    for decl in decls:
        t = decl['type']
        d = decl['data']

        if t == "group":
            grp_name = d['name']

        elif t == "reg":
            reg_name = d['name']
            reg_data = d['data']
            reg_type = d['type']
            reg_flags_list = d['flags']
            reg_base = d['base']
            reg_data = make_reg_data(reg_data, reg_type)
            f.write("REG(%s, %s, %s, %s, %s)\n" % (
                make_reg_id_name(grp_name, reg_name),
                reg_data,
                make_reg_type_name(reg_type),
                make_reg_flags_str(reg_flags_list),
                make_reg_base_id(reg_base)
            ))
        elif t == "begin":
            beg_name = d['name']
            f.write("REGS_BEGIN(%s)\n" % beg_name)
        elif t == "end":
            # cnt_name = d['name']
            f.write("REGS_END()\n")
            # if(cnt_name):
            #     f.write("\n#define REGS_%s_COUNT REGS_COUNT_VALUE(%s)\n" % (cnt_name, beg_name));
            # else:
            #     f.write("\n#define REGS_COUNT REGS_COUNT_VALUE(%s)\n" % (beg_name));
        elif t == "blank":
            f.write("\n")
        elif t == "comment":
            f.write("%s\n" % d)
        elif t == "macro":
            f.write("%s\n" % d)
        elif t == "include":
            f.write("%s\n" % d)

    # f.write("\nREGS_END()\n");
    # f.write("\n#define REGS_COUNT REGS_COUNT_VALUE(REG_ARRAY_NAME)\n");
    f.write("\n#endif /* REG_LIST_DATA_H */\n")


def check_identifier(name: str) -> bool:
    return name.isidentifier()


def get_str_number_base(str_num: str) -> int:
    if str_num.startswith("0x"):
        return 16
    if str_num.startswith("0b"):
        return 2
    if str_num.startswith("0"):
        return 8
    return 10


def parse_begin(line, line_num):
    parts = line.partition(" ")

    beg_token = parts[0].strip()
    tokens = parts[2].split(' ')

    if beg_token != "BEGIN" or len(tokens) != 1:
        print("Bad BEGIN line (%d): expected \"BEGIN str_name\"" % line_num)
        return {}

    beg_name = tokens[0].strip()

    if not check_identifier(beg_name):
        print("Bad begin name: \"%s\" at line %d" % (beg_name, line_num))
        return {}

    return {'name': beg_name}


def parse_end(line, line_num):
    parts = line.partition(" ")

    end_token = parts[0].strip()
    tokens = parts[2].split(' ')

    if end_token != "END" or len(tokens) > 1:
        print("Bad END line (%d): expected \"END [str_count_name]\"" % line_num)
        return {}

    end_cnt_name = tokens[0].strip()

    if end_cnt_name and not check_identifier(end_cnt_name) and not end_cnt_name.isdigit():
        print("Bad end name: \"%s\" at line %d" % (end_cnt_name, line_num))
        return {}

    return {'name': end_cnt_name}


def parse_group(line, line_num):
    parts = line.partition(" ")

    grp_token = parts[0].strip()
    tokens = parts[2].split(',')

    if grp_token != "GROUP" or len(tokens) != 2:
        print("Bad GROUP line (%d): expected \"GROUP str_name, int_id\"" % line_num)
        return {}

    grp_name = tokens[0].strip()
    grp_id_str = tokens[1].strip()
    grp_id = 0

    if not check_identifier(grp_name):
        print("Bad group name: \"%s\" at line %d" % (grp_name, line_num))
        return {}

    grp_id_base = get_str_number_base(grp_id_str)

    try:
        grp_id = int(grp_id_str, grp_id_base)
    except ValueError or TypeError:
        print("Bad group id: \"%s\" at line %d" % (grp_id_str, line_num))
        return {}
    return {'name': grp_name, 'id': grp_id}


def parse_reg(line, line_num):
    reg_types = ["I32", "I16", "I8", "U32", "U16", "U8", "IQ24", "IQ15", "IQ7", "STR", "MEM"]

    parts = line.partition(" ")

    reg_token = parts[0].strip()
    tokens = parts[2].split(',')

    tokens_count = len(tokens)

    if reg_token != "REG" or tokens_count < 3:
        print("Bad REG line (%d): expected \"REG str_name, str_data, str_type [,str_flags [,str_base]]\"" % line_num)
        return {}

    reg_name = tokens[0].strip()
    reg_data = tokens[1].strip()
    reg_type = tokens[2].strip()
    reg_flags = ""
    reg_base = ""

    if tokens_count >= 4:
        reg_flags = tokens[3].strip()

    if tokens_count >= 5:
        reg_base = tokens[4].strip()

    if not check_identifier(reg_name):
        print("Bad register name: \"%s\" at line %d" % (reg_name, line_num))
        return {}

    if not reg_data:
        print("Bad register data: \"%s\" at line %d" % (reg_data, line_num))
        return {}

    if reg_type not in reg_types:
        print("Bad register type: \"%s\" at line %d" % (reg_type, line_num))
        return {}

    if not reg_flags:
        reg_flags = "NONE"

    if not reg_base:
        reg_base = "NONE"

    reg_flags_list = [i.strip() for i in reg_flags.split("|")]

    return {'name': reg_name, 'data': reg_data,
            'type': reg_type, 'flags': reg_flags_list, 'base': reg_base}


def read_decls(f):
    line_num = 0

    # cur_grp = {'name':"", 'id':0};
    # cur_reg = {'name':"", 'data':"", 'type':"", 'flags':[]};

    data = []
    # data_item = {'type':"none", 'data':{}};

    while True:
        line_num = line_num + 1

        line = f.readline()
        if not line:
            break

        line = line.strip()
        if not line:
            data.append({'type': 'blank', 'data': {}})
            continue

        if line.startswith("!"):
            continue

        if line.startswith("//"):
            data.append({'type': 'comment', 'data': line})
            continue

        if line.startswith("#include"):
            data.append({'type': 'include', 'data': line})
            continue

        if line.startswith("#"):
            data.append({'type': 'macro', 'data': line})
            continue

        keyword = line.partition(" ")[0]

        if keyword == "BEGIN":
            beg = parse_begin(line, line_num)
            if beg:
                data.append({'type': 'begin', 'data': beg})
        elif keyword == "END":
            end = parse_end(line, line_num)
            if end:
                data.append({'type': 'end', 'data': end})
        elif keyword == "GROUP":
            grp = parse_group(line, line_num)
            if grp:
                data.append({'type': 'group', 'data': grp})
        elif keyword == "REG":
            rg = parse_reg(line, line_num)
            if rg:
                data.append({'type': 'reg', 'data': rg})
        else:
            print("Unknown keyword: \"%s\" at line %d" % (keyword, line_num))

    return data


def print_usage():
    print("Usage: %s" % (
            os.path.basename(sys.argv[0])),
          "[--decl DECL_FILENAME]",
          "[--ids REG_IDS_FILENAME]",
          "[--list REG_LIST_DATA_FILENAME]",
          "[--xml REGXML_FILENAME]")


#
# input: dict {
#    'arg_key' -> [param_type, 'out_key']
# }
# output 0: dict {
#    'out_key' -> 'value'
# }
# output 1: dict {
#    index -> 'unknown argument of argument with error'
# }
#
# def parse_args(arg_keys: dict, defvals: dict, args: list = None) -> map or None:
def parse_args(params_keys: dict, args: list = None) -> tuple[dict, dict]:
    if not args:
        args = sys.argv
    args = args.copy()
    args.remove(sys.argv[0])

    errors = {}
    out = {}

    cur_key = None
    cur_index = 0

    for arg in args:
        if arg in params_keys:
            if cur_key:
                errors[cur_index - 1] = cur_key
            cur_key = None
            arg_params = params_keys[arg]
            if arg_params[0] == 0:
                out[arg_params[1]] = 1
            else:  # arg_params[1] >= 1:
                cur_key = arg
        else:
            if cur_key:
                arg_params = params_keys[cur_key]
                out[arg_params[1]] = arg
                cur_key = None
            else:
                errors[cur_index] = arg
        cur_index = cur_index + 1

    return out, errors


def main() -> None:

    if len(sys.argv) == 1:
        print_usage()
        return

    decl_specif = False
    decl_filename = "reg_list_decl.txt"
    ids_needed = False
    ids_filename = "reg_ids.txt"
    reg_list_needed = False
    reg_list_filename = "reg_list_data.txt"
    regxml_needed = False
    regxml_filename = "reg_list.regxml"
    help = 0
    moo = 0

    params_keys = {
        '--decl': [1, 'decl'],
        '--ids': [1, 'ids'],
        '--list': [1, 'list'],
        '--xml': [1, 'xml'],
        '--moo': [0, 'moo'],
        '--help': [0, 'help'],
        '-h': [0, 'help'],
        '-M': [0, 'moo']
    }

    params, errors = parse_args(params_keys)
    if len(errors) != 0:
        for key, val in errors.items():
            print("Invalid argument or value:", val)
            print_usage()
            return

    for param, value in params.items():
        if param == 'decl':
            value = value.strip()
            if len(value) == 0:
                print("Empty decl filename!")
                return
            decl_specif = True
            decl_filename = value
        elif param == 'ids':
            value = value.strip()
            if len(value) == 0:
                print("Empty ids filename!")
                return
            ids_needed = True
            ids_filename = value
        elif param == 'list':
            value = value.strip()
            if len(value) == 0:
                print("Empty reg list filename!")
                return
            reg_list_needed = True
            reg_list_filename = value
        elif param == 'xml':
            value = value.strip()
            if len(value) == 0:
                print("Empty xml filename!")
                return
            regxml_needed = True
            regxml_filename = value
        elif param == 'help':
            help = value
        elif param == 'moo':
            moo = value

    if help:
        print_usage()
        return

    if moo:
        print("Muuuuuu...")
        if len(sys.argv) == 2:
            return

    decls = []

    if decl_specif:
        try:
            with open(decl_filename, "r", encoding='utf-8', newline='\n') as f:
                decls = read_decls(f)
        except OSError:
            print("Error read decl file: %s" % decl_filename)
            return
    else:
        decls = read_decls(sys.stdin)

    if len(decls) == 0:
        print("Nothing to convert!")
        return

    if ids_needed:
        try:
            with open(ids_filename, "w", encoding='utf-8', newline='\n') as f:
                gen_ids(decls, f)
        except OSError:
            print("Error write ids file: %s" % ids_filename)
            return

    if reg_list_needed:
        try:
            with open(reg_list_filename, "w", encoding='utf-8', newline='\n') as f:
                gen_regs(decls, f)
        except OSError:
            print("Error write regs file: %s" % reg_list_filename)
            return

    if regxml_needed:
        reglist = gen_reglist(decls)
        if len(reglist) == 1 and 'error' in reglist:
            print(reglist['error'])
            return
        entrylist = reglist_to_entrylist(reglist)
        try:
            with open(regxml_filename, "wb") as f:
                gen_regxml(entrylist, f)
        except OSError:
            print("Error write regs file: %s" % reg_list_filename)
            return


if __name__ == '__main__':
    sys.stdout = open(1, 'w', encoding='utf-8', newline='\n', closefd=False)
    main()

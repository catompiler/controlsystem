# -*- coding: utf-8 -*-
# coding: utf8

import sys;


def make_reg_id_name(group_name, reg_name):
    return "REG_ID_%s_%s" % (group_name, reg_name);


def make_reg_type_name(reg_type):
    return "REG_TYPE_%s" % (reg_type);


def make_reg_flags_str(reg_flags_list):
    flags_strs = ["REG_FLAG_%s" % (flag) for flag in reg_flags_list];
    return " | ".join(flags_strs);


def gen_ids(decls):
    print("#ifndef REG_IDS_H");
    print("#define REG_IDS_H");
    print();

    #id_decl = {'name':"", id: 0};

    grp_name = "";
    grp_id = 0;

    reg_name = "";
    reg_id = 0;

    for decl in decls:
        t = decl['type'];
        d = decl['data'];

        if(t == "blank"):
            print();
        elif(t == "comment"):
            print(d);
        elif(t == "group"):
            grp_name = d['name'];
            grp_id = d['id'];
            reg_id = 0;

        elif(t == "reg"):
            reg_name = d['name'];
            print("#define %s    %d" % (make_reg_id_name(grp_name, reg_name), grp_id + reg_id));
            reg_id = reg_id + 1;

        #print(d);

    print("\n#endif /* REG_IDS_H */");


def gen_regs(decls):
    print("#ifndef REG_LIST_DATA_H");
    print("#define REG_LIST_DATA_H");
    print("\n\nREGS_BEGIN(REG_ARRAY_NAME)\n");

    #id_decl = {'name':"", id: 0};

    grp_name = "";

    reg_name = "";

    for decl in decls:
        t = decl['type'];
        d = decl['data'];

        if(t == "blank"):
            print();
        elif(t == "comment"):
            print(d);
        elif(t == "group"):
            grp_name = d['name'];

        elif(t == "reg"):
            reg_name = d['name'];
            reg_data = d['data'];
            reg_type = d['type'];
            reg_flags_list = d['flags'];
            print("REG(%s, %s, %s, %s)" % (\
                    make_reg_id_name(grp_name, reg_name),\
                    reg_data,\
                    make_reg_type_name(reg_type),\
                    make_reg_flags_str(reg_flags_list)\
                ));

        #print(d);

    print("\nREGS_END()");
    print("\n#define REGS_COUNT REGS_COUNT_VALUE(REG_ARRAY_NAME)");
    print("\n#endif /* REG_LIST_DATA_H */");


def check_identifier(name):
    return name.isidentifier();


def parse_group(line, line_num):

    parts = line.partition(" ");

    grp_token = parts[0].strip();
    tokens    = parts[2].split(',');

    if(grp_token != "GROUP" or len(tokens) != 2):
        print("Bad GROUP line (%d): expected \"GROUP str_name, int_id\"" % (line_num));
        return {};

    grp_name = tokens[0].strip();
    grp_id_str = tokens[1].strip();
    grp_id = 0;

    if(not check_identifier(grp_name)):
        print("Bad group name: \"%s\" at line %d" % (grp_name, line_num));
        return {};

    try:
        grp_id = int(grp_id_str);
    except:
        print("Bad group id: \"%s\" at line %d" % (grp_id_str, line_num));
        return {};
    return {'name':grp_name, 'id':grp_id};


def parse_reg(line, line_num):

    reg_types = ["I32", "U32", "IQ24", "IQ15"];

    parts = line.partition(" ");

    reg_token = parts[0].strip();
    tokens    = parts[2].split(',');

    if(reg_token != "REG" or len(tokens) != 4):
        print("Bad REG line (%d): expected \"REG str_name, str_data, str_type, str_flags\"" % (line_num));
        return {};

    reg_name  = tokens[0].strip();
    reg_data  = tokens[1].strip();
    reg_type  = tokens[2].strip();
    reg_flags = tokens[3].strip();

    if(not check_identifier(reg_name)):
        print("Bad register name: \"%s\" at line %d" % (reg_name, line_num));
        return {};

    if(not reg_data):
        print("Bad register data: \"%s\" at line %d" % (reg_data, line_num));
        return {};

    if(not reg_type in reg_types):
        print("Bad register type: \"%s\" at line %d" % (reg_type, line_num));
        return {};

    if(not reg_flags):
        reg_flags = "NONE";

    reg_flags_list = [i.strip() for i in reg_flags.split("|")];

    return {'name':reg_name, 'data':reg_data,\
            'type':reg_type, 'flags':reg_flags_list};


def read_decls(f):
    line_num = 0;

    #cur_grp = {'name':"", 'id':0};
    #cur_reg = {'name':"", 'data':"", 'type':"", 'flags':[]};

    data = [];
    #data_item = {'type':"none", 'data':{}};

    while True:
        line_num = line_num + 1;

        line = f.readline();
        if(not line):
            break;

        line = line.strip();
        if(not line):
            data.append({'type':'blank', 'data':{}});
            continue;

        if(line.startswith("//")):
            data.append({'type':'comment', 'data':line});
            continue;

        keyword = line.partition(" ")[0];

        if(keyword == "GROUP"):
            grp = parse_group(line, line_num);
            if(grp):
                data.append({'type':'group','data':grp});
        elif(keyword == "REG"):
            rg = parse_reg(line, line_num);
            if(rg):
                data.append({'type':'reg','data':rg});
        else:
            print("Unknown keyword: \"%s\" at line %d" % (keyword, line_num));

    #print(data);

    return data;


def main():

    #print(sys.argv);

    decls = [];

    try:
        with open("reg_list_decl.txt", "r", encoding='utf-8', newline = '\n') as f:
            decls = read_decls(f);
    except OSError:
        print("Error read decl file");
        return;

    gen_ids(decls);
    gen_regs(decls);

if(__name__ == '__main__'):
    sys.stdout = open(1, 'w', encoding='utf-8', newline = '\n', closefd=False)
    main();


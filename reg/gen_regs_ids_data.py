# -*- coding: utf-8 -*-
# coding: utf8

import sys;

def make_reg_id(suffix):
    return "REG_ID_%s" % (suffix);

def make_reg_id_name(group_name, reg_name):
    return make_reg_id("_".join([group_name, reg_name]));


def make_reg_type_name(reg_type):
    return "REG_TYPE_%s" % (reg_type);


def make_reg_flags_str(reg_flags_list):
    flags_strs = ["REG_FLAG_%s" % (flag) for flag in reg_flags_list];
    return " | ".join(flags_strs);

def make_reg_base_id(reg_base):
    return make_reg_id("_".join(reg_base.split(".")));


def gen_ids(decls, f=sys.stdout):
    f.write("#ifndef REG_IDS_H\n");
    f.write("#define REG_IDS_H\n\n");

    grp_name = "";
    grp_id = 0;

    reg_name = "";
    reg_id = 0;

    for decl in decls:
        t = decl['type'];
        d = decl['data'];

        if(t == "group"):
            grp_name = d['name'];
            grp_id = d['id'];
            reg_id = 0;

        elif(t == "reg"):
            reg_name = d['name'];
            f.write("#define %s    %d\n" % (make_reg_id_name(grp_name, reg_name), grp_id + reg_id));
            reg_id = reg_id + 1;

        elif(t == "blank"):
            f.write("\n");
        elif(t == "comment"):
            f.write("%s\n" % (d));
        #elif(t == "macro"):
        #    f.write("%s\n" % (d));

        #print(d);

    f.write("\n#endif /* REG_IDS_H */\n");


def gen_regs(decls, f=sys.stdout):
    f.write("#ifndef REG_LIST_DATA_H\n");
    f.write("#define REG_LIST_DATA_H\n\n");

    grp_name = "";
    reg_name = "";
    beg_name = "";

    # for decl in decls:
    #     t = decl['type'];
    #     d = decl['data'];
    #
    #     if(t == "include"):
    #         f.write("%s\n" % (d));
    #         decls.remove(decl);


    #f.write("\nREGS_BEGIN(REG_ARRAY_NAME)\n\n");

    for decl in decls:
        t = decl['type'];
        d = decl['data'];

        if(t == "group"):
            grp_name = d['name'];

        elif(t == "reg"):
            reg_name = d['name'];
            reg_data = d['data'];
            reg_type = d['type'];
            reg_flags_list = d['flags'];
            reg_base = d['base'];
            f.write("REG(%s, %s, %s, %s, %s)\n" % (\
                    make_reg_id_name(grp_name, reg_name),\
                    reg_data,\
                    make_reg_type_name(reg_type),\
                    make_reg_flags_str(reg_flags_list),\
                    make_reg_base_id(reg_base)\
                ));
        elif(t == "begin"):
            beg_name = d['name'];
            f.write("REGS_BEGIN(%s)\n" % (beg_name));
        elif(t == "end"):
            cnt_name = d['name'];
            f.write("REGS_END()\n");
            if(cnt_name):
                f.write("\n#define REGS_%s_COUNT REGS_COUNT_VALUE(%s)\n" % (cnt_name, beg_name));
            else:
                f.write("\n#define REGS_COUNT REGS_COUNT_VALUE(%s)\n" % (beg_name));
        elif(t == "blank"):
            f.write("\n");
        elif(t == "comment"):
            f.write("%s\n" % (d));
        elif(t == "macro"):
            f.write("%s\n" % (d));
        elif(t == "include"):
            f.write("%s\n" % (d));

        #print(d);

    #f.write("\nREGS_END()\n");
    #f.write("\n#define REGS_COUNT REGS_COUNT_VALUE(REG_ARRAY_NAME)\n");
    f.write("\n#endif /* REG_LIST_DATA_H */\n");


def check_identifier(name):
    return name.isidentifier();


def parse_begin(line, line_num):

    parts = line.partition(" ");

    beg_token = parts[0].strip();
    tokens    = parts[2].split(' ');

    if(beg_token != "BEGIN" or len(tokens) != 1):
        print("Bad BEGIN line (%d): expected \"BEGIN str_name\"" % (line_num));
        return {};

    beg_name = tokens[0].strip();

    if(not check_identifier(beg_name)):
        print("Bad begin name: \"%s\" at line %d" % (beg_name, line_num));
        return {};

    return {'name':beg_name};

def parse_end(line, line_num):

    parts = line.partition(" ");

    end_token = parts[0].strip();
    tokens    = parts[2].split(' ');

    if(end_token != "END" or len(tokens) > 1):
        print("Bad END line (%d): expected \"END [str_count_name]\"" % (line_num));
        return {};

    end_cnt_name = tokens[0].strip();

    if(end_cnt_name and not check_identifier(end_cnt_name) and not end_cnt_name.isdigit()):
        print("Bad end name: \"%s\" at line %d" % (end_cnt_name, line_num));
        return {};

    return {'name':end_cnt_name};


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

    reg_types = ["I32", "U32", "IQ24", "IQ15", "IQ7"];

    parts = line.partition(" ");

    reg_token = parts[0].strip();
    tokens    = parts[2].split(',');

    tokens_count = len(tokens);

    if(reg_token != "REG" or tokens_count < 3):
        print("Bad REG line (%d): expected \"REG str_name, str_data, str_type [,str_flags [,str_base]]\"" % (line_num));
        return {};

    reg_name  = tokens[0].strip();
    reg_data  = tokens[1].strip();
    reg_type  = tokens[2].strip();
    reg_flags = "";
    reg_base  = "";

    if(tokens_count >= 4):
        reg_flags = tokens[3].strip();

    if(tokens_count >= 5):
        reg_base  = tokens[4].strip();

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

    if(not reg_base):
        reg_base = "NONE";

    reg_flags_list = [i.strip() for i in reg_flags.split("|")];

    return {'name':reg_name, 'data':reg_data,\
            'type':reg_type, 'flags':reg_flags_list, 'base':reg_base};


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

        if(line.startswith("!")):
            continue;

        if(line.startswith("//")):
            data.append({'type':'comment', 'data':line});
            continue;

        if(line.startswith("#include")):
            data.append({'type':'include', 'data':line});
            continue;

        if(line.startswith("#")):
            data.append({'type':'macro', 'data':line});
            continue;

        keyword = line.partition(" ")[0];

        if(keyword == "BEGIN"):
            beg = parse_begin(line, line_num);
            if(beg):
                data.append({'type':'begin', 'data':beg});
        elif(keyword == "END"):
            end = parse_end(line, line_num);
            if(end):
                data.append({'type':'end', 'data':end});
        elif(keyword == "GROUP"):
            grp = parse_group(line, line_num);
            if(grp):
                data.append({'type':'group', 'data':grp});
        elif(keyword == "REG"):
            rg = parse_reg(line, line_num);
            if(rg):
                data.append({'type':'reg', 'data':rg});
        else:
            print("Unknown keyword: \"%s\" at line %d" % (keyword, line_num));

    #print(data);

    return data;


def print_usage():
    print("Usage: %s [DECL_FILENAME [REG_IDS_FILENAME REG_LIST_DATA_FILENAME]]" % (sys.argv[0]));

def main():

    decl_filename = "";#"reg_list_decl.txt";
    ids_filename = "";#"reg_ids.txt";
    regs_filename = "";#"regs_list_data.txt";

    if(len(sys.argv) > 4):
        print_usage();
        return;

    if(len(sys.argv) == 2):
        decl_filename = sys.argv[1];

    if(len(sys.argv) == 3):
        ids_filename = sys.argv[1];
        regs_filename = sys.argv[2];

    if(len(sys.argv) == 4):
        decl_filename = sys.argv[1];
        ids_filename = sys.argv[2];
        regs_filename = sys.argv[3];

    decls = [];

    if(decl_filename):
        try:
            with open(decl_filename, "r", encoding='utf-8', newline = '\n') as f:
                decls = read_decls(f);
        except OSError:
            print("Error read decl file: %s" % (decl_filename));
            return;
    else:
        decls = read_decls(sys.stdin);

    if(ids_filename):
        try:
            with open(ids_filename, "w", encoding='utf-8', newline = '\n') as f:
                gen_ids(decls, f);
        except OSError:
            print("Error write ids file: %s" % (ids_filename));
            return;
    else:
        gen_ids(decls, sys.stdout);

    if(regs_filename):
        try:
            with open(regs_filename, "w", encoding='utf-8', newline = '\n') as f:
                gen_regs(decls, f);
        except OSError:
            print("Error write regs file: %s" % (regs_filename));
            return;
    else:
        gen_regs(decls, sys.stdout);


if(__name__ == '__main__'):
    sys.stdout = open(1, 'w', encoding='utf-8', newline = '\n', closefd=False);
    main();


# -*- coding: utf-8 -*-
# coding: utf8

import sys;


def gen_module(fin, fout, tmplnames, modnames):
    #print(modnames);

    while True:
        line = fin.readline();
        if(not line):
            break;

        for key in tmplnames:
            #print(key);

            tmpl_str = tmplnames[key];
            mod_str = modnames[key];

            line = line.replace(tmpl_str, mod_str);

        fout.write(line);


def gen_mod_define(modname):
    return modname.upper();


def gen_mod_structname(modname):
    structname = "";

    upnext = 0;

    for i in range(0, len(modname)):
        c = modname[i];

        # Первый символ.
        if(i == 0):
            c = c.upper();

        # Символ после подчёркивания
        if(upnext == 1):
            c = c.upper();
            upnext = 0;

        # Установим флаг для следующего символа.
        if(c == '_'):
            upnext = 1;

        structname = structname + c;

    return structname;


def gen_modnames(modname, modthis):
    modnames = {};

    modnames['define'] = gen_mod_define(modname);
    modnames['struct'] = gen_mod_structname(modname);
    modnames['module'] = modname;
    modnames['this'] = modthis;

    return modnames;


def check_name(name):
    return name.isidentifier();


def print_usage():
    print("Usage: %s mod[_]name" % (sys.argv[0]));


def main():

    if(len(sys.argv) < 2 or len(sys.argv) > 3):
        print_usage();
        return;

    modname = sys.argv[1];
    modthis = modname;

    if(len(sys.argv) == 3):
        modthis = sys.argv[2];

    if(not check_name(modname)):
        print("Invalid module name: %s" % (modname));
        return;

    if(not check_name(modthis)):
        print("Invalid this name: %s" % (modthis));
        return;

    tmplnames = {'define':'MOD_TMPL', 'struct':'Mod_Tmpl',\
                 'module':'mod_tmpl', 'this':'tmpl'}
    modnames = gen_modnames(modname, modthis);

    ftmpl_h = 0;
    fmod_h = 0;
    ftmpl_c = 0;
    fmod_c = 0;

    try:
        ftmpl_h = open("mod_tmpl.h", "r", encoding='utf-8', newline = '\n');
        fmod_h = open("%s.h" % (modname), "w", encoding='utf-8', newline = '\n');
        #fmod_h = sys.stdout;
        gen_module(ftmpl_h, fmod_h, tmplnames, modnames);

        ftmpl_c = open("mod_tmpl.c", "r", encoding='utf-8', newline = '\n');
        fmod_c = open("%s.c" % (modname), "w", encoding='utf-8', newline = '\n');
        #fmod_c = sys.stdout;
        gen_module(ftmpl_c, fmod_c, tmplnames, modnames);
    except OSError:
        print("File IO error");
    finally:
        pass;
        ftmpl_h.close();
        fmod_h.close();
        ftmpl_c.close();
        fmod_c.close();



if(__name__ == '__main__'):
    sys.stdout = open(1, 'w', encoding='utf-8', newline = '\n', closefd=False)
    main();


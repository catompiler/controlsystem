function ltrim(s) { sub(/^[ \t\r\n]+/, "", s); return s }
function rtrim(s) { sub(/[ \t\r\n]+$/, "", s); return s }
function trim(s) { return rtrim(ltrim(s)); }

BEGIN{
#     count = 0
#     printf "%s\n", "uint32_t regs_data[];"
}
{
    if(NF){
        if(!($1~/^#include/) && !($1~/^\/\//)){
            for(i = 1; i <= NF; i ++){
                if(NR > 5 && i == 2){
                    #printf "&regs_data[%u]", count, #"NULL"
                    printf "%s", "NULL"
                }else{
                    printf "%s", trim($i)
                }
                if(i < NF){
                    printf "%s ", FS
                }else{
                    printf "%s", "\n"
                }
            }
#     count = count + 1
        }
    }else{
        print ""
    }
}
END{
#     printf "#ifdef DECL_REGS_DATA\n"
#     printf "#define DECL_REGS_DATA\n"
#     printf "uint32_t regs_data[%u] = {0};\n", count
#     printf "#endif // DECL_REGS_DATA\n"
}

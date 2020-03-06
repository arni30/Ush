#include <ush.h>

static void parse_pwd(char **args, int *flag) {
    int len = mx_count_arr_el(args);
    int stop = 0;

    for (int i = 1; i < len; i++) {
        if (mx_strcmp(args[i], "--") == 0)
            stop = 3;
        if (stop == 0 && args[i][0] == '-') { //errors -r
            for (int y =1; y < mx_strlen(args[i]); y++) {
                if (args[i][y] != 'L' && args[i][y] != 'P') {
                    fprintf(stderr, MX_PWD_ERR, args[i][y]);
                    *flag = 3;
                }
            }
            if (*flag == 3)
                break;
            if((*flag = mx_find_flag("LP", args[i])) > 0)
                continue;
        }
    }
}


void mx_pwd(char **args) {
    int flag = 0;
    char *position = mx_strdup(MX_PWD());
    int is_link = 0;

    parse_pwd(args, &flag);
    is_link = check_symlink(position, flag, 2);
    if (flag == 2 && is_link == 1 && flag!= 3)//redo
        printf("%s\n", position);
    else if (flag != 3)
        printf("%s\n", position);
    mx_strdel(&position);
}
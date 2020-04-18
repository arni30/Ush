#include <ush.h>

void lst_init(t_dbl_list* lst) {
    lst->first = lst->last = 0;
    lst->size = 0;
}

t_dbl_list* lst_create() {
    t_dbl_list *lst = (t_dbl_list*) malloc(sizeof (t_dbl_list));
    lst_init(lst);
    return lst;
}

//static int winsize(void) {
//    struct winsize wins;
//    int err = ioctl(0, TIOCGWINSZ, &wins);//заменить запрет функция
//
//    if (err == -1)
//        return 0;
//    return wins.ws_col;
//}

static int executing(char *ush_path, t_ush *ush) {
    int return_value = 0;
    t_queue **queue = NULL;
    if (ush->command != NULL) {
        queue = mx_parsing(ush->command);
        mx_push_execute_queue(queue, ush_path);
    }
    return return_value;
}

void sigint () {
    //signal(SIGINT, sigint);
    mx_printstr("\n");
}

static void set_shlvl(void) {
    char *shlvl = mx_itoa(mx_atoi(MX_SHLVL()) + 1);

    setenv("SHLVL", shlvl, 1);
    mx_strdel(&shlvl);
}

static char *find_ush_path(char **commands) {
    char *pwd = MX_PWD();
    char *ush_path = NULL;

    if (mx_strstr(commands[0], "./")){
        ush_path = mx_replace_substr(commands[0], ".", pwd);
    }
    else {
        ush_path = mx_strdup(commands[0]);
    }
    return ush_path;
}
int main(int argc, char **argv){
    //status 0 - normal; 1 - pipe; 2 - commsub; 3 - ^C break;
    t_ush *ush = mx_create_ush(argc, argv);
    int return_value = 0;
    char *ush_path = find_ush_path(argv);
    ush->history = lst_create();
    set_shlvl();
    while(1) {
        signal(SIGINT, sigint);
        mx_print_prompt(ush->emodji_num);
        ush->command = mx_process_input();
        //mx_parsing(ush->command);
        return_value = executing(ush_path, ush);
        mx_strdel(&ush->command);
        system("leaks -q ush");
    }
    mx_strdel(&ush_path);
    return return_value;
}

#include <ush.h>

static int mx_get_flag_index(const char *str, const char *sub) {
    int len_str = 0;
    int len_sub = 0;

    if (!str || !sub)
        return -2;

    len_str = mx_strlen(str);
    len_sub = mx_strlen(sub);

    for (int i = 0; i <= len_str - len_sub; i++)
        if (!mx_strncmp(&str[i], sub, len_sub))
            return i;

    return INT_MAX;
}

t_queue *mx_insort_t_queue(char *arr, t_queue **arr_queue) {
    int count = mx_count_queue_operation(arr);
    char **arr_str = NULL;
    char *temp = arr;
    int and = 0;
    int or = 0;

    for(int j = 0; j <= count; j++) {
            and = mx_get_flag_index(temp, "&&");
            or = mx_get_flag_index(temp, "||");
            if ((and >= 0) && (and < or)) {
                arr_str = mx_util_strsplit_one(temp, "&&");
                mx_push_back_queue(arr_queue, arr_str[0], '&');
                temp = arr_str[1];
                continue;
            } else if ((or >= 0) && (or < and )) {
                arr_str = mx_util_strsplit_one(temp, "||");
                mx_push_back_queue(arr_queue, arr_str[0], '|');
                temp = arr_str[1];
                continue;
            }  else if (and == INT_MAX && or == INT_MAX) {
                if (temp == NULL)
                    temp = arr;
                mx_push_back_queue(arr_queue, temp, '0');
            }
    }
    return *arr_queue;
}

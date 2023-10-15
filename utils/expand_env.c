#include "../includes/minishell.h"

// int remove_brackets(char **command, char bracket, int start, char **tmp)
// {
//     int len;
//     int i;

//     len = 0;
//     len = ft_strlen(command[0]);
//     i = 0;
//     if (bracket == '(')
//         bracket = ')';
//     else if (bracket == '{')
//         bracket = '}';
//     else
//         return (start);
//     while (command[0][start + i] != bracket && command[0][start + i] != '\0')
//         i++;
//     if (command[0][start + i] == '\0')
//         return (start + i);
//     tmp[0] = ft_substr(command[0], start + 2, i - 2);
//     return (start + i);
// }



// void expand_env(char **command, t_env *env_head)
// {
//     int i;
//     int j;
//     char *tmp;
//     char *before_env;
//     char *env_value;

//     i = 0;
//     j = 0;
//     if (command[0] == NULL)
//         return ;
//     // i = skip_space(command[0]);
//     command[0] = &command[0][i];
//     while (command[0][i] != '$' && command[0][i] != '\0')
//         i++;
//     if (command[0][i] == '$' && command[0][i] != '\0')
//     {
//         if (command[0][i + 1] == '?')
//             return ;
//         before_env = ft_substr(command[0], 0, i);
//         if (command[0][i + 1] == '(' || command[0][i + 1] == '{')
//         {
//             i = remove_brackets(&command[0], command[0][i + 1], i, &tmp);
//         }
//         else
//         {
//             while (command[0][i + j] != '\0' && command[0][i + j] != ' ' && command[0][i + j] != '\'' && command[0][i + j] != '\"')//条件見直し
//                 j++;
//             tmp = ft_substr(command[0], i + 1, j - 1);
//             i = i + j;
//         }
//         env_value = map_get(&env_head, tmp);
//         if (env_value != NULL)
//         {// freeeeeeeee
//             before_env = ft_strjoin(before_env, env_value);
//             if (command[0][i] != '\0')
//             {
//                 tmp = ft_substr(command[0], i, ft_strlen(command[0]));
//                 expand_env(&tmp, env_head);
//                 before_env = ft_strjoin(before_env, tmp);
//             }
//             // before_env = ft_strjoin(before_env, &command[0][i + 1]);
//         }
//         command[0] = ft_strdup(before_env);
//         free(tmp);
//     }
// }



char *deal_env(char *arg, int *i, t_env *env_head, int *increment)
{puts("-----deal_env-----");
    char *start;
    char *env_value;
    char *expanded;

    puts("[1]");
    (*i)++;
    start = &arg[*i];
    printf("start: [%s]\n", start);
    while (arg[*i] && ft_isalnum(arg[*i]))
        (*i)++;
    // printf("&arg[%d] - start: [%ld]\n", *i, &arg[*i] - start);
    env_value = ft_substr(start, 0, &arg[*i] - start);
    // (*i)++;
    start = &arg[*i];
    printf("start: [%s]\n", start);

    expanded = map_get(&env_head, env_value);
    // if (tmp)
    // {
    //     joined = ft_strjoin(tmp, expanded);
    //     // free(tmp);
    // }
    // else
    //     joined = ft_strdup(expanded);
    printf("env_value [%s]\n", env_value);
    // free(env_value);
    printf("expanded [%s]\n", expanded);
    *increment += ft_strlen(expanded);
    *increment -= (ft_strlen(env_value) + 1);
    puts("----------");
    return (expanded);
    // free(expanded);
}

char *deal_raw_env(char *arg, int *i, t_env *env_head)
{
    char *tmp;
    char *rest;
    int increment;
    char *joined;

    increment = 0;
    tmp = ft_substr(arg, 0, &arg[*i] - arg);
    // (*i)++;
    printf("tmp[%s]!!!!!!!!\n", tmp);
    rest = &arg[*i];
    rest++;
    while (*rest && ft_isalnum(*rest))
        rest++;
    if (*rest)
        rest = ft_strdup(rest);
    printf("rest:[%s]\n",rest);

    char *expanded = deal_env(arg, i, env_head, &increment);
    printf("expanded: [%s]\n", expanded);
    joined = ft_strjoin(tmp, expanded);
    // free(tmp);
    tmp = (ft_strjoin(joined, rest));
    printf("tmp: %s\n", tmp);

    *i += increment + 2;
    // free(arg);
    return (tmp);
}

char *expand_env(char *arg, int *i, t_env *env_head, int *increment)
{
    puts("------------expand_env--------------");
    char *start;
    char *env_value;
    char *expanded;
    int len;
    char *tmp;
    char *joined;

    len = 0;
    // printf("arg [%s]\n", &arg[*i]);
    // (*i)++;
    start = &arg[*i];
    printf("start: [%s]\n", start);


    tmp = NULL;
    joined = NULL;
    // for (int j = 0; j < 3; i++)
    while (arg[*i] != '\"' && arg[*i])
    {
        // while (arg[*i] && arg[*i] != '$')
        //     (*i)++;
        // len = &arg[*i] - start;
        // printf("len: [%d]\n", len);
        // if (len != 0)
        //     tmp = ft_substr(start, 0, len);
        // printf("tmp [%s]\n", tmp);
        if (arg[*i] == '$')
        {
                expanded = deal_env(arg, i, env_head, increment);
                start++;
                while(*start && ft_isalnum(*start))
                    start++;
                printf(":) start :%s\n", start);
                printf("joined [%s]\n", joined);
        }
        else
        {
            puts("[2]");
            while (arg[*i] && arg[*i] != '\"' && arg[*i] != '$')
                (*i)++;
            printf("&arg[%d] - start: [%ld]\n", *i, &arg[*i] - start);
            expanded = ft_substr(start, 0, &arg[*i] - start);
            printf("expanded [%s]\n", expanded);
        }
        if (!joined)
        {
            puts("[3]");
            tmp = ft_strdup(joined);
            // free(joined);
            joined = ft_strjoin(tmp, expanded);
        }
        else{
            puts("[4]");
            printf("joined [%s]\n", joined);
            tmp = ft_strdup(joined);
            // free(joined);
            joined = ft_strjoin(tmp,expanded);

        }
        printf("joined [%s]\n", joined);
        printf("start [%s]\n", start);
        printf("arg [%s]\n", &arg[*i]);
        // free(expanded);
    }
    (*i)++;
    printf("joined [%s]\n", joined);
    puts("-----------------------------");
    return (joined);


}



/* ------------------------------------------------------------------------ */

// void fatal_error(char *msg)
// {
//     ft_putstr_fd("minishell: ", STDERR_FILENO);
//     ft_putendl_fd(msg, STDERR_FILENO);
// 	exit(1);
// }

// int main() {
//     char *command = NULL; // テスト対象のコマンド文字列
//     int flag = 0; // シングルクォートフラグ（0: シングルクォート外、1: シングルクォート内）
//     t_env *env_head = NULL; // 環境変数リストの先頭アドレス
//     envmap_init(&env_head);
// 	// info.map_head = env;
//     printf("%s\n", map_get(&env_head, "HOME"));

//     // テストケース1: シングルクォート外の置換
//     command = strdup("$HOME \'$HOME\'");
//     expand_env(&command, env_head);
//     printf("テストケース1: %s\n", command);
//     free(command);
//     command = NULL;

//     return 0;
// }

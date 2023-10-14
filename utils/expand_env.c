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

char *expand_env(char *arg, int *i, t_env *env_head)
{
    char *start;
    char *env_value;
    char *expanded;
    bool inside_env;

    printf("arg [%s]\n", &arg[*i]);
    (*i)++;
    // return (NULL);
    start = &arg[*i];
    inside_env = false;


    while (arg[*i] != '\"')
    {
        while (arg[*i] && arg[*i] != '$')
            (*i)++;
        if (arg[*i] != '$')
        {
            (*i)++;
            inside_env != inside_env;
            while (arg[*i] && is_alnum(&arg[*i]))
                (*i)++;
            env_value = ft_substr(start, 0, &arg[*i] - start);
            expanded = map_get(&env_head, env_value);
            printf("env_value [%s]\n", env_value);
            free(env_value);
            printf("expanded [%s]\n", expanded);
            (*i)++;
        }
    }
    return (expanded);


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

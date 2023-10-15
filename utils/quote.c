#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

char *deal_env(char *arg, int *i, t_env *env_head);
char *deal_raw_env(char *arg, int *i, t_env *env_head);

int remove_quorts(char **command, char bracket, int start)
{
    int len;
    int i;
    char *tmp;

    len = 0;
    len = ft_strlen(command[0]);
    i = 0;
    while (command[0][i + 1] != bracket && command[0][i] != '\0')//ここなんで＋１？
        i++;
    if (command[0][i] == '\0')
        return (start + i + 1);
    tmp = ft_substr(command[0], 1, len - 2);
    ft_strlcpy(command[0], tmp, len - 1);
    free(tmp);
    return (start + i + 2);
}

// void expand_quote(char **command, t_env *env_head)
// {
//     int i;
//     int j;
//     char *tmp;
//     char *before_env;
//     char *env_value;
//     char quort;

//     i = 0;
//     j = 1;
//     tmp = NULL;
//     if (command[0] == NULL)
//         return ;
//     // i = skip_space(command[0]);
//     command[0] = &command[0][i];
//     // ' "を探す
//     while (command[0][i] != '\'' && command[0][i] != '\"' && command[0][i] != '\0')
//         i++;
//     if (command[0][i] == '\'')
//         quort = '\'';
//     else if (command[0][i] == '\"')
//         quort = '\"';
//     //後の' "を探す
//     while (command[0][i + j] != quort && command[0][i + j] != '\0')
//         j++;
//     // ' "があったら
//     if (command[0][i + 1] != '\0')
//     {
//         before_env = ft_substr(command[0], 0, i);
//         tmp = ft_substr(command[0], i, j + 1);
//         i = remove_quorts(&tmp, quort, i);
//         if (quort == '\"')
//         {
//             expand_env(&tmp, env_head);
//         }
//         before_env = ft_strjoin(before_env, tmp);
//         if (command[0][i] != '\0'){
//             tmp = ft_substr(command[0], i, ft_strlen(command[0]));
//             expand_quote(&tmp, env_head);
//             before_env = ft_strjoin(before_env, tmp);
//             // tmp = ft_strjoin(tmp, &command[0][i]);
//         }
//         // command[0] = ft_strdup(tmp);
//         command[0] = ft_strdup(before_env);
//         free(tmp);
//     }else{
//         expand_env(command, env_head);
//     }
// }

void deal_single_quote(char *arg, int *i)
{
    char *start;
    char *end;
    char *tmp;

    start = &arg[(*i)];
    end = &arg[(*i) + 1];
    ft_memmove(start, end, ft_strlen(end));
    tmp = arg;
    while (*tmp)
        tmp++;
    tmp--;
    *tmp = '\0';
    while (arg[(*i)] && arg[(*i)] != '\'')
        (*i)++;
    start = &arg[(*i)];
    end = &arg[(*i) + 1];
    ft_memmove(start, end, ft_strlen(end));
    tmp = arg;
    while (*tmp)
        tmp++;
    tmp--;
    *tmp = '\0';
}

char *deal_double_quote(char *arg, int *i, t_env *env_head)
{
    puts("--------------deal_double_quote---------------");
    char *rest;
    char *expanded;
    char *tmp;
    char *joined;
    int increment;

    tmp = NULL;
    rest = NULL;
    increment = 0;
    expanded = NULL;
    tmp = NULL;
    while (arg[(*i)] && arg[(*i)] != '\"')
        (*i)++;
    tmp = ft_substr(arg, 0, &arg[(*i)] - arg);
    printf("tmp [%s]\n", tmp);
    (*i)++;
    expanded = expand_env(arg, i, env_head, &increment);
    printf("i: %d\n", *i);
    // while (arg[(*i)] && arg[(*i)] != '\"')
    //     (*i)++;
    // (*i)++;
    // return (NULL);
    if (arg[(*i)] != '\0')
        rest = &arg[(*i)];
    printf("rest [%s]\n", rest);
    if (!expanded)
        joined = ft_strdup(tmp);
    else {
        joined = ft_strjoin(tmp, expanded);
        free(expanded);
    }

    printf("joined [%s]\n", joined);
    *i -= 2;
    *i += increment;
    // free(tmp);
    if (tmp)
        free(tmp);
    if (rest != NULL)
    {
        // tmp = ft_strdup(joined);
        printf("tmp [%s]\n", tmp); // => tmp [/Users/emukamada]
        printf("joined: [%s]\n", joined); // => joined: []
        tmp = ft_strjoin(joined, rest);
        printf("tmp: [%s]\n", tmp); // => (ft_strjoin) joined: [s]
    }
    else
    {
        tmp = ft_strdup(joined);
    }
    free(joined);
    printf("tmp: [%s]\n", tmp); // => joined: [s]
    free(arg);
    // arg = joined;

    return tmp;
}

char *expand_quote(char *arg, t_env *env_head)

{
    char    quote_char;
    char    *tmp;
    int increment;
    int i;

    tmp = arg;
    i = 0;
    increment = 0;
    while (arg[i])
    {
        while (arg[i] && arg[i] != '\'' && arg[i] != '\"' && arg[i] != '$')
                i++;
        if (arg[i] == '\'')
        {
            deal_single_quote(arg, &i);
            printf("result: [%s]\n", arg);
            printf("current i position: [%d]\n", i);
        }
        else if (arg[i] == '\"')
        {
            // return (arg);
            arg = deal_double_quote(arg, &i, env_head);
            printf("result: [%s]\n", arg);
            printf("current i position: [%d]\n", i);
        }
        else if (arg[i] == '$')
        {
            // expand_env(arg, &i, env_head, &increment);
            arg = deal_raw_env(arg, &i, env_head);
            printf("result: [%s]\n", arg);
            printf("current i position: [%d]\n", i);
        }
    }
    return (arg);
}



/* -------------------------------------------------------------------------- */

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
//     command = strdup("\"\'$HOME\'\"$HOME \"\'$HOME\'\"$HOME");
//     expand_quote(&command, env_head);
//     printf("テストケース1: %s\n", command);
//     free(command);
//     command = NULL;

//     return 0;
// }

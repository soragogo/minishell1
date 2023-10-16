#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

char *deal_env(char *arg, int *i, t_env *env_head);
char *deal_raw_env(char *arg, int *i, t_env *env_head);


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

char *deal_double_quote(char *arg, int *i, t_env *env_head, int *status)
{
    char *rest;
    char *expanded;
    char *tmp;
    char *joined;
    int increment;

    increment = 0;
    rest = NULL;
    expanded = NULL;
    tmp = NULL;
    joined = NULL;
    while (arg[(*i)] && arg[(*i)] != '\"')
        (*i)++;
    tmp = ft_substr(arg, 0, *i);
    (*i)++;
    expanded = expand_env(arg, i, env_head, &increment, status);
    if (arg[(*i)] != '\0')
        rest = &arg[(*i)];
    *i += increment - 2;
    joined = ft_strjoin(tmp, expanded);
    free(tmp);
    tmp = ft_strjoin(joined, rest);
    free(joined);
    free(expanded);
    free(arg);
    return tmp;
}

char *expand_quote(char *arg, t_env *env_head, int *status)

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
            deal_single_quote(arg, &i);
        else if (arg[i] == '\"')
            arg = deal_double_quote(arg, &i, env_head, status);
        if (ft_strncmp(&arg[i],"$?", 2) * ft_strncmp(&arg[i],"${?}", 4) == 0)
            arg = deal_status(arg, &i, *status, "arg");
        else if (arg[i] == '$')
            arg = deal_raw_env(arg, &i, env_head);
    }
    return (arg);
}




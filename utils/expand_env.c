#include "../includes/minishell.h"



char *deal_env(char *arg, int *i, t_env *env_head, int *increment)
{
    char *start;
    char *env_value;
    char *expanded;

    env_value = NULL;
    expanded = NULL;
    (*i)++;
    start = &arg[*i];
    if (ft_isdigit(arg[*i]))
    {
        while (ft_isdigit(arg[*i]))
            (*i)++;
    }
    else{
        while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
        (*i)++;
    }
    env_value = ft_substr(start, 0, &arg[*i] - start);
    start = &arg[*i];
    expanded = map_get(&env_head, env_value);
    *increment += ft_strlen(expanded);
    *increment -= (ft_strlen(env_value)+1);
    if (env_value)
    {
        free(env_value);
        env_value = NULL;
    }
    return (expanded);
}

char *deal_raw_env(char *arg, int *i, t_env *env_head)
{
    char *tmp;
    char *rest;
    int increment;
    char *joined;
    char *expanded;

    increment = 0;
    tmp = NULL;
    joined = NULL;
    rest = NULL;
    expanded = NULL;
    tmp = ft_substr(arg, 0, *i);
    rest = &arg[*i + 1];
    rest++;
    if (ft_isdigit(*rest))
    {
        while (ft_isdigit(*rest))
            rest++;
    }
    else
    {
        while (*rest && (ft_isalnum(*rest) || *rest == '_'))
        rest++;
    }
    rest = ft_strdup(rest);
    expanded = deal_env(arg, i, env_head, &increment);
    joined = ft_strjoin(tmp, expanded);
    free(tmp);
    tmp = NULL;
    tmp = ft_strjoin(joined, rest);
    free(rest);
    free(joined);
    free(expanded);
    (*i) += increment;
    free(arg);
    return (tmp);
}

char *expand_env(char *arg, int *i, t_env *env_head, int *increment)
{
    char *start;
    char *env_value;
    char *expanded;
    char *tmp;
    char *joined;

    start = &arg[*i];
    tmp = NULL;
    joined = NULL;
    expanded = NULL;
    while (arg[*i] != '\"' && arg[*i])
    {
        if (arg[*i] == '$')
        {
            expanded = deal_env(arg, i, env_head, increment);
            start++;
            if (ft_isdigit(*start))
            {
                while (ft_isdigit(*start))
                    start++;
            }
            else{
                while (*start && (ft_isalnum(*start) || *start == '_'))
                start++;
            }
        }
        else
        {
            while (arg[*i] && arg[*i] != '\"' && arg[*i] != '$')
                (*i)++;
            expanded = ft_substr(start, 0, &arg[*i] - start);
        }
        tmp = ft_strdup(joined);
        free(joined);
        joined = NULL;
        joined = ft_strjoin(tmp, expanded);
        free(tmp);
        tmp = NULL;
        free(expanded);
        expanded = NULL;
    }
    (*i)++;
    return (joined);
}

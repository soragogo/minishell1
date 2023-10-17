#include "../includes/minishell.h"

int caliculate_incriment(char *prev, char *new)
{
    int prev_len;
    int new_len;

    printf("prev: %s\n",prev);
    printf("new: %s\n",new);
    prev_len = ft_strlen(prev);
    new_len = ft_strlen(new);
    if (prev_len <= new_len)
        return (new_len - 1);
    else
        return (prev_len - new_len);
}

char *deal_status(char *arg, int *i, int status, char *ret)
{
    puts("------deal_status-----");
    char *a_st;
    char *tmp;
    char *joined;
    char *rest;

    a_st = ft_itoa(status);
    if (ft_strncmp(ret, "status", 6) == 0)
    {
        printf("arg[%d]: %s\n",*i, &arg[*i]);
        if (ft_strncmp(&arg[*i],"$?", 2) == 0)
            *i += caliculate_incriment("$?", a_st);
        else
            *i += caliculate_incriment("${?}", a_st);
        printf("arg[%d]: %s\n",*i, &arg[*i]);
        puts("-----");
        return (a_st);
    }
    joined = ft_substr(arg, 0, *i);
    tmp = ft_strjoin(joined, a_st);
    free(joined);
    if (ft_strncmp(&arg[*i],"$?", 2) == 0)
        rest = &arg[*i] + 2;
    else
        rest = &arg[*i] + 4;
    *i += ft_strlen(a_st);
    joined = ft_strjoin(tmp, rest);
    free(tmp);
    free(arg);
    free(a_st);
    puts("-----------");
    return (joined);
}

int return_end_of_env(char *end)
{
    int i;
    printf("end: %s\n", end);
    i = 0;
    if (ft_isdigit(end[i]))
    {
        while (ft_isdigit(end[i]))
            i++;
    }
    else if(end[i] == '{')
    {
        while (end[i] != '}' && end[i])
            i++;
        if (end[i] == '}')
            i++;
    }
    else if (end[i] == '?')
        i++;
    else
    {
        while (end[i] && (ft_isalnum(end[i]) || end[i] == '_'))
            i++;
    }
    return (i);
}

char *deal_env(char *arg, int *i, t_env *env_head, int *increment)
{
    char *start;
    char *env_value;
    char *expanded;

    env_value = NULL;
    expanded = NULL;
    (*i)++;
    start = &arg[*i];
    *i += return_end_of_env(&arg[*i]);
    if (*start == '{')
        env_value = ft_substr(start, 1, ft_strchr(start, '}') - start - 1);
    else
        env_value = ft_substr(start, 0, &arg[*i] - start);
    expanded = map_get(&env_head, env_value);
    *increment += ft_strlen(expanded) - (ft_strlen(env_value) + 1);
    free(env_value);
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
    rest += return_end_of_env(rest);
    rest = ft_strdup(rest);
    expanded = deal_env(arg, i, env_head, &increment);
    joined = ft_strjoin(tmp, expanded);
    free(tmp);
    tmp = ft_strjoin(joined, rest);
    free(rest);
    free(joined);
    free(expanded);
    (*i) += increment;
    free(arg);
    return (tmp);
}

char *expand_env(char *arg, int *i, t_env *env_head, int *increment, int *status)
{
    puts("-----expand_env----");
    char *start;
    char *env_value;
    char *expanded;
    char *tmp;
    char *joined;

    start = &arg[*i];
    tmp = NULL;
    joined = NULL;
    expanded = NULL;
    printf("arg[%d]: %s\n",*i, &arg[*i]);
    while (arg[*i] != '\"' && arg[*i])
    {
        if (arg[*i] == '$')
        {
            if (ft_strncmp(&arg[*i],"$?", 2) * ft_strncmp(&arg[*i],"${?}", 4) == 0)
                expanded = deal_status(arg, i, *status, "status");
            else
                expanded = deal_env(arg, i, env_head, increment);
            printf("start: %s\n", start);
            start += return_end_of_env(start + 1) + 1;
        }
        else
        {
            while (arg[*i] && arg[*i] != '\"' && arg[*i] != '$')
                (*i)++;
            expanded = ft_substr(start, 0, &arg[*i] - start);
            start += ft_strlen(expanded);
        }
        printf("expanded: %s\n", expanded);
        tmp = ft_strdup(joined);
        printf("tmp: %s\n", tmp);
        free(joined);
        joined = NULL;
        joined = ft_strjoin(tmp, expanded);
        printf("joined: %s\n", joined);
        free(tmp);
        tmp = NULL;
        free(expanded);
        expanded = NULL;
    }
    (*i)++;
    puts("----------------");
    return (joined);
}

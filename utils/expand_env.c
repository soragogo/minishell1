#include "../includes/minishell.h"

int caliculate_incriment(char *prev, char *new)
{
    int prev_len;
    int new_len;

    if (ft_strncmp(prev, "$?", 2) == 0)
        prev_len = ft_strlen("$?");
    else
        prev_len = ft_strlen("${?}");
    printf("prev: %s\n",prev);
    printf("new: %s\n",new);
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
        *i += caliculate_incriment(&arg[*i], a_st);
        printf("arg[%d]: %s\n",*i, &arg[*i]);
        puts("-----");
        return (a_st);
    }
    joined = ft_substr(arg, 0, *i);
    tmp = ft_strjoin(joined, a_st);
    free(joined);
    rest = &arg[*i] + 2;
    if (ft_strncmp(&arg[*i],"${?}", 2) == 0)
        rest += 2;
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
    printf("i: %d\n", i);
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
    joined = NULL;
    expanded = NULL;
    tmp = ft_substr(arg, 0, *i);
    rest = &arg[*i + 1] + return_end_of_env(&arg[*i + 1]);
    expanded = deal_env(arg, i, env_head, &increment);
    joined = ft_strjoin(tmp, expanded);
    free(tmp);
    tmp = ft_strjoin(joined, rest);
    free(joined);
    free(expanded);
    (*i) += increment;
    free(arg);
    return (tmp);
}

char *handle_dollar_expansion(char *arg, int *i, t_env *env_head, int *increment, int *status) {
    char *expanded;
    if (ft_strncmp(&arg[*i], "$?", 2) * ft_strncmp(&arg[*i], "${?}", 4) == 0) {
        expanded = deal_status(arg, i, *status, "status");
    } else {
        expanded = deal_env(arg, i, env_head, increment);
    }
    return expanded;
}

char *extract_until_special_char(char *arg, int *i) {
    char *start = &arg[*i];
    while (arg[*i] && arg[*i] != '\"' && arg[*i] != '$') {
        (*i)++;
    }
    return ft_substr(start, 0, &arg[*i] - start);
}

char *expand_env(char *arg, int *i, t_env *env_head, int *increment, int *status) {
    puts("-----expand_env----");
    char *expanded;
    char *tmp;
    char *joined;

    joined = NULL;
    printf("arg[%d]: %s\n", *i, &arg[*i]);
    while (arg[*i] != '\"' && arg[*i]) {
        if (arg[*i] == '$')
            expanded = handle_dollar_expansion(arg, i, env_head, increment, status);
        else
            expanded = extract_until_special_char(arg, i);
        tmp = ft_strdup(joined);
        free(joined);
        joined = ft_strjoin(tmp, expanded);
        free(tmp);
        free(expanded);
        expanded = NULL;
    }
    (*i)++;
    puts("----------------");
    return joined;
}

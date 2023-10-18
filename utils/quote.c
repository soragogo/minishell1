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
    while ((*tmp + 1))
        tmp++;
    *tmp = '\0';
    while (arg[(*i)] && arg[(*i)] != '\'')
        (*i)++;
    start = &arg[(*i)];
    end = &arg[(*i) + 1];
    ft_memmove(start, end, ft_strlen(end));
    tmp = arg;
    while ((*tmp + 1))
        tmp++;
    *tmp = '\0';
}

char *deal_double_quote(char *arg, int *i, t_env *env_head, int *status)
{
    puts("-----deal_double_quote----");
    char *rest;
    char *expanded;
    char *tmp;
    char *joined;
    int increment;

    increment = 0;
    rest = NULL;
    expanded = NULL;
    while (arg[(*i)] && arg[(*i)] != '\"')
        (*i)++;
    printf("*i: %d\n", *i);
    tmp = ft_substr(arg, 0, *i);
    printf("tmp: %s\n", tmp);
    (*i)++;
	rest = ft_strdup(ft_strchr(&arg[*i], '\"') + 1);
    printf("rest: %s\n", rest);
    expanded = expand_env(arg, *i, env_head, status);
    printf("expanded: %s\n", expanded);
    printf("&arg[%d]: %s\n", *i, &arg[*i]);
	printf("rest - tmp + 1 =%ld\n", ft_strchr(&arg[*i - 2], '\"') - &arg[*i - 2] - 2);
	if (*i > 1)
    	*i += ft_strlen(expanded) + ft_strchr(&arg[*i - 2], '\"') - &arg[*i - 2] - 2;
	printf("current *i: %d\n", *i);
    joined = ft_strjoin(tmp, expanded);
    free(tmp);
    tmp = ft_strjoin(joined, rest);
    free(joined);
    free(expanded);
    free(arg);
	free(rest);
    puts("-------------------------");
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
		printf("current i: %d\n", i);
		printf("arg[%d]: %s\n", i, arg);
	}
	return (arg);
}




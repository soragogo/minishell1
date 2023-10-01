#include "../includes/minishell.h"

char **join(char const *s1, char const *s2, char **environ)
{
	int		i;
	int		strslen;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	strslen = ft_strlen(s1) + ft_strlen(s2);
	environ = (char **)malloc(sizeof(char *) * 1);
	*environ = (char *)malloc(sizeof(char) * (strslen + 1));
	if (environ == NULL)
		return (NULL);
	while (*s1)
		environ[0][i++] = *s1++;
	while (*s2)
		environ[0][i++] = *s2++;
	environ[0][i] = 0;
	return (environ);
}

void env_join(char *name, char *value, char **environ)
{
	environ = join(name, "=", environ);
	environ = join(environ[0], value, environ);
}

//KEY=valueの形で環境変数を作成する関数
char **create_environ(t_env **env_head)
{
	t_env *tmp;
	char **environ;
    int i;

    i = 0;
	tmp = *env_head;
	while (tmp)
	{
		env_join(tmp->name, tmp->value, &environ[i]);
		i++;
		tmp = tmp->next;
	}
	environ = (char **)malloc(sizeof(char *) * 1);
	environ[i] = (char *)malloc(sizeof(char *) * 1);
    environ[i] = NULL;
	return (environ);
}
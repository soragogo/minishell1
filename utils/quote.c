#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

int remove_quorts(char **command, char bracket, int start, char **tmp)
{
    int len;
    int i;

    len = 0;
    len = ft_strlen(command[0]);
    i = 0;
    while (command[0][start + i] != bracket && command[0][start + i] != '\0')
        i++;
    if (command[0][start + i] == '\0')
        return (start + i);
    tmp[0] = ft_substr(command[0], start + 2, i - 2);
    return (start + i);
}

void expand_quote(char **command, t_env *env_head)
{
    int i;
    int j;
    char *tmp;
    int flag;
    char *before_env;
    char *env_value;

    i = 0;
    j = 0;
    flag = 0;
    if (command[0] == NULL)
        return ;
    i = skip_space(command[0]);
    command[0] = &command[0][i];
    while (command[0][i] != '$' && command[0][i] != '\0')
        i++;
    if (command[0][i] == '$' && command[0][i + 1] != '\0')
    {
        before_env = ft_substr(command[0], 0, i);
        if (command[0][i + 1] == '\'' || command[0][i + 1] == '\"')
        {
            if (command[0][i + 1] == '\'')
                flag = 1;
            i = remove_quorts(&command[0], command[0][i + 1], i, &tmp);
        }
        else
        {
            while (command[0][i + j] != '\0' && command[0][i + j] != ' ')
                j++;
            tmp = ft_substr(command[0], i + 1, i + j - 1);
            i = i + j;
        }
        if (flag == 0)
            env_value = map_get(&env_head, tmp);
        else
            env_value = tmp;
        if (env_value != NULL)
        {// freeeeeeeee
            before_env = ft_strjoin(before_env, env_value);
            if (command[0][i] != '\0')
                before_env = ft_strjoin(before_env, &command[0][i + 1]);
        }
        command[0] = ft_strdup(before_env);
        free(tmp);
    }
}


/* -------------------------------------------------------------------------- */

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

void fatal_error(char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

int main() {
    char *command = NULL; // テスト対象のコマンド文字列
    int flag = 0; // シングルクォートフラグ（0: シングルクォート外、1: シングルクォート内）

    // テストケース1: シングルクォート外の置換
    command = strdup("This is $HOME directory.");
    expand_quote(&command, &flag);
    printf("テストケース1: %s\n", command);
    free(command);
    command = NULL;

    // テストケース2: シングルクォート内の置換
    command = strdup("This is '$HOME' directory.");
    expand_quote(&command, &flag);
    printf("テストケース2: %s\n", command);
    free(command);
    command = NULL;

    // 他のテストケースを追加できます...

    return 0;
}

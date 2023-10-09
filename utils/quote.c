#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

// ' か　"見つける
// その後ろにある　'　か　"　を探す
// ' " を削除する
// "　なら　環境変数展開"

int remove_quorts(char **command, char bracket, int start)
{
    int len;
    int i;
    char *tmp;

    len = 0;
    len = ft_strlen(command[0]);
    i = 0;
    while (command[0][i + 1] != bracket && command[0][i] != '\0')
        i++;
    if (command[0][i] == '\0')
        return (start + i + 1);
    tmp = ft_substr(command[0], 1, len - 2);
    ft_strlcpy(command[0], tmp, len - 1);
    free(tmp);
    return (start + i + 2);
}

void expand_quote(char **command, t_env *env_head)
{
    int i;
    int j;
    char *tmp;
    char *before_env;
    char *env_value;
    char quort;

    i = 0;
    j = 1;
    tmp = NULL;
    if (command[0] == NULL)
        return ;
    // i = skip_space(command[0]);
    command[0] = &command[0][i];
    // ' "を探す
    while (command[0][i] != '\'' && command[0][i] != '\"' && command[0][i] != '\0')
        i++;
    if (command[0][i] == '\'')
        quort = '\'';
    else if (command[0][i] == '\"')
        quort = '\"';
    //後の' "を探す
    while (command[0][i + j] != quort && command[0][i + j] != '\0')
        j++;
    // ' "があったら
    if (command[0][i + 1] != '\0')
    {
        before_env = ft_substr(command[0], 0, i);
        tmp = ft_substr(command[0], i, j + 1);
        i = remove_quorts(&tmp, quort, i);
        if (quort == '\"')
        {
            expand_env(&tmp, env_head);
        }
        before_env = ft_strjoin(before_env, tmp);
        if (command[0][i] != '\0'){
            tmp = ft_substr(command[0], i, ft_strlen(command[0]));
            expand_quote(&tmp, env_head);
            before_env = ft_strjoin(before_env, tmp);
            // tmp = ft_strjoin(tmp, &command[0][i]);
        }
        // command[0] = ft_strdup(tmp);
        command[0] = ft_strdup(before_env);
        free(tmp);
    }
}


/* -------------------------------------------------------------------------- */

// int	skip_space(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
// 		i++;
// 	return (i);
// }

void fatal_error(char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

int main() {
    char *command = NULL; // テスト対象のコマンド文字列
    int flag = 0; // シングルクォートフラグ（0: シングルクォート外、1: シングルクォート内）
    t_env *env_head = NULL; // 環境変数リストの先頭アドレス
    envmap_init(&env_head);
	// info.map_head = env;
    printf("%s\n", map_get(&env_head, "HOME"));

    // テストケース1: シングルクォート外の置換
    command = strdup("\'asd$HOME\' \"$HOME\" ");
    expand_quote(&command, env_head);
    printf("テストケース1: %s\n", command);
    free(command);
    command = NULL;

    return 0;
}

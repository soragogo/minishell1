#include "../includes/minishell.h"

void remove_brackets(char **command, char bracket)
{
    int len;
    char *tmp;

    len = 0;
    len = ft_strlen(command[0]);
    if (bracket == '(')
        bracket = ')';
    else if (bracket == '{')
        bracket = '}';
    else
        return;
    if (command[0][len - 1] != bracket)
        return;
    tmp = ft_substr(command[0], 2, len - 3);
    command[0] = ft_strdup(tmp);
    free(tmp);
}

void expand_env(char **command, t_env *env_head)
{
    int i;
    int j;
    char *tmp;
    char *env_value;

    i = 0;
    j = 0;
    while (command[i] != NULL)
    {
        if (command[i][0] == '$')
        {
            j = 0;
            if (command[i][1] == '(' || command[i][1] == '{'){
                remove_brackets(&command[i], command[i][1]);
                tmp = command[i];
            }
            else{
                while (command[i][j] != '\0' && command[i][j] != ' ')
                    j++;
                tmp = ft_substr(command[i], 1, j - 1);
            }
            env_value = map_get(&env_head, tmp);
            if (env_value != NULL)
            { // freeeeeeeee
                command[i] = ft_strdup(env_value);
            }
            free(tmp);
        }
        i++;
    }
}

/* ------------------------------------------------------------------------ */

// int compare_arrays(char *arr1[], char *arr2[]);

// // expand_env 関数のテストケース
// void test_expand_env()
// {
//     // テスト用の環境変数を設定
//     t_env *env_head = NULL;
//     envmap_init(&env_head);
//     set_env(&env_head, "VAR1", "value1");
//     set_env(&env_head, "VAR2", "value2");

//     // テスト用のコマンド
//     char *command1[] = {"echo", "$(VAR1)", "${VAR2}", NULL};

//     // コマンドを展開
//     expand_env(command1, env_head);

//     // while (*command1 != NULL)
//     for (int i = 0; i < 3; i++)
//     {
//         printf("%s\n", command1[i]);
//         // command1++;
//     }

// }

// // 配列を比較するユーティリティ関数
// int compare_arrays(char *arr1[], char *arr2[])
// {
//     int i = 0;
//     while (arr1[i] != NULL && arr2[i] != NULL)
//     {
//         if (strcmp(arr1[i], arr2[i]) != 0)
//         {
//             return 0; // 配列が異なる要素を持っている場合は 0 を返す
//         }
//         i++;
//     }
//     return arr1[i] == NULL && arr2[i] == NULL; // 配列が同じであれば 1 を返す
// }

// int main()
// {
//     test_expand_env(); // expand_env 関数のテストを実行
//     return 0;
// }

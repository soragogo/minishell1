#include "../includes/minishell.h"

//$まで取っておく
//かっこがあったら
//$から先から変数名取り出す

int remove_brackets(char **command, char bracket, int start, char **tmp)
{
    int len;
    // char *tmp;
    int i;

    len = 0;
    len = ft_strlen(command[0]);
    i = 0;
    if (bracket == '(')
        bracket = ')';
    else if (bracket == '{')
        bracket = '}';
    else
        return (start);
    while (command[0][start + i] != bracket && command[0][start + i] != '\0')
        i++;
    if (command[0][start + i] == '\0')
        return (start + i);
    tmp[0] = ft_substr(command[0], start + 2, i - 2);
    // command[0] = ft_strdup(tmp[0]);
    // free(tmp);
    return (start + i);
}

void expand_env(char **command, t_env *env_head)
{
    int i;
    // int j;
    char *tmp;
    char *before_env;
    char *env_value;

    i = 0;
    // j = 0;
    // while (command[i] != NULL)
    // {
    if (command[0] == NULL)
        return;
    while (command[0][i] != '$' && command[0][i] != '\0')
        i++;
    if (command[0][i] == '$' && command[0][i + 1] != '\0')
    {
        before_env = ft_substr(command[0], 0, i);
        // j = 0;
        if (command[0][i + 1] == '(' || command[0][i + 1] == '{')
        {
            i = remove_brackets(&command[0], command[0][i + 1], i, &tmp);
            // tmp = command[0];
        }
        else
        {
            while (command[0][i] != '\0' && command[0][i] != ' ')
                i++;
            tmp = ft_substr(command[0], 1, i - 1);
        }
        env_value = map_get(&env_head, tmp);
        if (env_value != NULL)
        { // freeeeeeeee
            // ft_strjoin(command[0], before_env);
            before_env = ft_strjoin(before_env, env_value);
            if (command[0][i] != '\0')
                before_env = ft_strjoin(before_env, &command[0][i + 1]);
        }
        command[0] = ft_strdup(before_env);
        free(tmp);
    }
    // i++;
    // }
}

/* ------------------------------------------------------------------------ */

// // int compare_arrays(char *arr1[], char *arr2[]);

// // expand_env 関数のテストケース
// void test_expand_env()
// {
//     // テスト用の環境変数を設定
//     t_env *env_head = NULL;
//     envmap_init(&env_head);
//     set_env(&env_head, "VAR1", "value1");
//     set_env(&env_head, "VAR2", "value2");

//     // テスト用のコマンド
//     char *command1[] = {"$VAR1", "kjshda$(VAR1)lkjafs", "${VAR2}", NULL};

//     // コマンドを展開
//     int j = 0;
//     while (command1[j] != NULL)
//     {
//         expand_env(&command1[j], env_head);
//         j++;
//     }

//     // while (*command1 != NULL)
//     for (int i = 0; i < 3; i++)
//     {
//         printf("%s\n", command1[i]);
//         // command1++;
//     }
// }

// // // 配列を比較するユーティリティ関数
// // int compare_arrays(char *arr1[], char *arr2[])
// // {
// //     int i = 0;
// //     while (arr1[i] != NULL && arr2[i] != NULL)
// //     {
// //         if (strcmp(arr1[i], arr2[i]) != 0)
// //         {
// //             return 0; // 配列が異なる要素を持っている場合は 0 を返す
// //         }
// //         i++;
// //     }
// //     return arr1[i] == NULL && arr2[i] == NULL; // 配列が同じであれば 1 を返す
// // }

// int main()
// {
//     test_expand_env(); // expand_env 関数のテストを実行
//     return 0;
// }

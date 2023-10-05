#include "./../includes/minishell.h"

void ft_putstr(char *ch, int fd)
{
	if (!ch)
		return;
	write(fd, ch, strlen(ch));
}

int ft_echo(char **command, int status)
{
	int i;
	int n_option;

	i = 1;
	n_option = 0;
	if (command[i] && ft_strncmp(command[i], "-n", 3) == 0)// && strlen(command[i]) == 2)
	{
		n_option = 1;
		i++;
	}
	while (command[i])
	{
		if (command[i] && ft_strncmp(command[i], "$?", 2) == 0)
			ft_putnbr_fd(status, STDOUT_FILENO);
		else
			ft_putstr(command[i], STDOUT_FILENO);
		i++;
		if (command[i])
			write(1, " ", STDOUT_FILENO);
	}
	if (n_option == 0)
		write(1, "\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <string.h>

// // テスト用の関数
// void test_builtin_echo(char **argv) {
// 	setbuf(stdout, NULL);
//     printf("Input: ");
// 	fflush(stdout);
//     for (int i = 0; argv[i] != NULL; i++) {
//         printf("%s ", argv[i]);
// 		fflush(stdout);
//     }
//     printf("\nOutput: ");
// 	fflush(stdout);
//     ft_echo(argv, 1);
//     printf("\n\n");
// 	fflush(stdout);
// }

// int main() {
//     // テストケースを用意して実行
//     char *test1[] = {"echo", "Hello,", "world!", NULL};
//     test_builtin_echo(test1);

//     char *test2[] = {"echo", "-n", "No", "newline", "here.", NULL};
//     test_builtin_echo(test2);

//     char *test3[] = {"echo", NULL};
//     test_builtin_echo(test3);

// 	char *test4[] = {"echo", "$?", NULL};
// 	test_builtin_echo(test4);

//     return 0;
// }

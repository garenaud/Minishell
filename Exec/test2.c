/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:31:57 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/08 15:38:59 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 256 // longueur maximale d'une ligne de commande
#define MAX_ARGS 32 // nombre maximum d'arguments d'une commande

void run_command_line(char *command_line)
{
  // Déclaration des variables
  char *command, *arg, *saveptr, *token;
  int i, j, k, status, pipefd[2];
  pid_t pid;

  // Récupération de la première commande et de ses arguments
  command = strtok_r(command_line, "|", &saveptr);

  // Tant qu'il reste des commandes à exécuter...
  while (command != NULL) {
    // Récupération des arguments de la commande
    i = 0;
    while ((arg = strtok_r(NULL, " ", &saveptr)) != NULL && i < MAX_ARGS) {
      args[i] = arg;
      i++;
    }
    args[i] = NULL; // Indication de fin des arguments

    // Si c'est la première commande, on utilise STDIN comme entrée
    // Sinon, on utilise la sortie du tube comme entrée
    if (k == 0) {
      j = STDIN_FILENO;
    } else {
      j = pipefd[0];
    }

    // Si c'est la dernière commande, on utilise STDOUT comme sortie
    // Sinon, on crée un nouveau tube pour la sortie
    if (command = strtok_r(NULL, "|", &saveptr) == NULL) {
      k = STDOUT_FILENO;
    } else {
      if (pipe(pipefd) == -1) {
        fprintf(stderr, "Erreur lors de la création du tube : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      k = pipefd[1];
    }

    // Création d'un nouveau processus pour exécuter la commande
    pid = fork();

    if (pid == -1) {
      // Erreur lors de la création du processus
      fprintf(stderr, "Erreur lors de la création du processus : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // Processus fils

      // Redirection de l'entrée et de la sortie
      if (dup2(j, STDIN_FILEN

void    loop_pipe(char **path, char ***cmd, char *env) 
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0;
	int		nb_pipe = 1;
	int		i = 0;
	int		prev_pipe = STDIN_FILENO;
	char	*path1 = "/bin/ls";
	char	*arg1[] = {"ls", NULL}; // NULL = (char *)0

	while (i < nb_pipe)
    {
		printf(PURP"PID = %d \n"ENDC, pid);
		pipe(p);
		//int pid = fork();
		printf(RED"Fork[%i] = %d PID[%i] = %d\n"ENDC, i, fork(), i, pid);
/* 		if (pid == -1)
		{
			perror("Pipe failed");
		} */
		if (fork() == 0)
		{
			printf(PURP"Je suis dans l'enfant \n Path[%i] = %s PID = %d cmd[%i] = %s env = %s\n\n\n"ENDC, i, path1, pid, i, *arg1, env);
			printf(GREEN"PID = %d \n"ENDC, pid);
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			printf(GREEN"je vais passer le execve \n"ENDC);
			dup2(p[1], STDOUT_FILENO);
/* 			if (*(cmd + 1) != NULL)
				dup2(p[1], 1); */
			execve(path1, &arg1[i], &env);
			perror("execve failed");
			close(p[1]);
			exit(1);
        }
		close(prev_pipe);
		close(p[1]);
		prev_pipe = p[0];
		i++;
	}
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if(fork() > 0)
	{	
		wait(NULL);
		close(p[1]);
		fd_in = p[0];
		printf(GREEN"PID = %d je suis dans papa et maman\n"ENDC, pid);
	}
}


int main(int argc, char *argv[], char *env[])
{
  char *ls[] = {"ls", NULL};
  char *grep[] = {"test", NULL};
  char *wc[] = {"wc", NULL};
  char **cmd[] = {ls, grep, wc, NULL};
  char *path[] = {"/bin/ls", "/usr/bin/grep", "/usr/bin/wc", NULL};

  loop_pipe(path, cmd, *env);
  return (0);
}
/* void    loop_pipe(char **path, char ***cmd, char *env) 
{
  int   p[2];
  pid_t pid;
  int   fd_in = 0;
  int	nb_pipe = 1;
  int	i = 0;
  char	*path1 = "/bin/ls";
  char	*arg1[] = {"ls", (char *)0};

  while (i < nb_pipe)
    {
		printf(PURP"PID = %d \n"ENDC, pid);
		pipe(p);
		pid = fork();
		printf(RED"Fork[%i] = %d PID[%i] = %d\n"ENDC, i, fork(), i, pid);
		if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			printf(PURP"Je suis dans l'enfant \n Path[%i] = %s PID = %d cmd[%i] = %s env = %s\n\n\n"ENDC, i, path1, pid, i, *arg1, env);
			printf(GREEN"PID = %d \n"ENDC, pid);
			dup2(fd_in, 0); //change the input according to the old one 
			if (*(cmd + 1) != NULL)
				dup2(p[1], 1);
			close(p[0]);
			execve(path1, arg1, &env);
			perror("execve failed");
			exit(1);
        }
		else
		{
			wait(NULL);
			close(p[1]);
			fd_in = p[0]; //save the input for the next command
			cmd++;
		}
		i++;
		printf(GREEN"PID = %d \n"ENDC, pid);
	}
}

int main(int argc, char *argv[], char *env[])
{
  char *ls[] = {"ls", NULL};
  char *grep[] = {"test", NULL};
  char *wc[] = {"wc", NULL};
  char **cmd[] = {ls, grep, wc, NULL};
  char *path[] = {"/bin/ls", "/usr/bin/grep", "/usr/bin/wc", NULL};

  loop_pipe(path, cmd, *env);
  return (0);
}
 */
/* #define MAX_ARGC 4 // 3

int main(int argc, char *argv[], char *env[])
 {
    char *args[][4]= {{"/bin/ls","-allll", NULL},
    {"/usr/bin/grep", "mini", NULL},{"/usr/bin/wc", NULL} };

    size_t i, n;
    int prev_pipe, pfds[2];
    n = sizeof(args) / sizeof(*args);
    printf("n = %zu\n", n);
    prev_pipe = STDIN_FILENO;

    for (i = 0; i < n - 1; i++) {
        pipe(pfds);

        if (fork() == 0) {
            // Redirect previous pipe to stdin
            if (prev_pipe != STDIN_FILENO) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // Redirect stdout to current pipe
            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[1]);

            // Start command
            execve(args[i][0], args[i], env);

            perror("execve failed");
            exit(1);
        }

        // Close read end of previous pipe (not needed in the parent)
        close(prev_pipe);

        // Close write end of current pipe (not needed in the parent)
        close(pfds[1]);

        // Save read end of current pipe to use in next iteration
        prev_pipe = pfds[0];
    }

    // Get stdin from last pipe
    if (prev_pipe != STDIN_FILENO) {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }
    //execve(args1[0], args1, env);
    // Start last command
     execve(args[i][0], args[i], env);

    perror("execve failed");
    exit(1);
} */

/* ca marche mais qu'avec un pipe

int run_pipe(char *args[], char *env[])
 {
    int		i;
	int		n;
	int		prev_pipe;
	int		pfds[2];
	n = 1;
	prev_pipe = STDIN_FILENO;
	i = 0;
	while(i < n - 1)
	{
 		printf(RED"args[%i][0] = %s\n"ENDC, i, &args[i][0]);
		printf(PURP"args[%i] = %s\n"ENDC, i, args[i]);
 		printf(PURP"args[%i][0] = %s ; args[%i] = %s \n"ENDC, i, &args[i][0], i, args[i]);
		pipe(pfds);
		if (fork() == 0)
		{
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			dup2(pfds[1], STDOUT_FILENO);
			close(pfds[1]);
			execve(&args[i][0], &args[i], env);
			perror("execve failed");
			exit(1);
		}
		close(prev_pipe);
		close(pfds[1]);
		prev_pipe = pfds[0];
		i++;
	}
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	execve(&args[i][0], &args[i], env);
	perror("execve failed");
	printf(RED"success"ENDC);
	exit(1);
}

int	main(int argc, char *argv[], char *env[])
{
    (void) argc;
	(void) argv;
	char	*args[4][3] = 
		{{"/bin/ls","-allll", NULL},
    	{"/usr/bin/grep", "out", NULL},
		{"/usr/bin/wc", NULL} };
	//char	**argsimple[3][10] = {"/bin/ls", "-l", NULL};
	printf("args[0][0] = %s\n", args[0][0]);
	printf("args[1] = %s\n", *args[0]);
	run_pipe(*args, env);
	printf(PURP"fin du programme"ENDC);
} */
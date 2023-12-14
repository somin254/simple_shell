#ifndef CISFUN_SHELL_H
#define CISFUN_SHELL_H

#include <stdlib.h>

#define WRITE_BUF_SIZE 256
#define PROMPT "#cisfun$ "

/**
 * struct list_t - Definition of a linked list node
 * @str: String data
 * @next: Pointer to the next node
 */
typedef struct list_t
{
	char *str;               /* String data */
	struct list_t *next;     /* Pointer to the next node */
} list_t;

/**
 * struct info_t - Definition of information struct for the shell
 * @argv: Argument vector
 * @env: Environment variables
 * @argc: Argument count
 * @status: Status indicator
 * @err_num: Error number
 * @readfd: File descriptor for reading
 * @env_list: Linked list of environment variables
 * @prompt: Shell prompt
 */
typedef struct info_t
{
	char **argv;            /* Argument vector */
	char **env;             /* Environment variables */
	int argc;               /* Argument count */
	int status;             /* Status indicator */
	int err_num;            /* Error number */
	int readfd;             /* File descriptor for reading */
	list_t *env_list;       /* Linked list of environment variables */
	const char *prompt;     /* Shell prompt */
} info_t;

/* Prototypes */
int changeCurrentDirectory(info_t *infos);
int printCurrentEnvironment(info_t *infos);
int initializeOrModifyEnvVar(info_t *infos);
char *getEnvVarValue(info_t *infos, const char *name);
int populateEnvList(info_t *info);
int removeEnvVar(info_t *infos);
int showHelp(info_t *infos);
int exitShell(info_t *infos);

/* Errors */
void _eputs(char *str);
int _putfd(char ch, int fd);
int _putsfd(char *str, int fd);
int _eputchar(char ch);

/* _ATOI.C */
int interactive(info_t *infos);
int _isalpha(int ch);
int _atoi(char *str);
int is_delim(char ch, char *delim);

void _puts(const char *str);
char *_getenv(info_t *infos, const char *name);
int _strcmp(const char *s1, const char *s2);
void _putchar(char c);
void print_error(info_t *infos, const char *message);
void _setenv(info_t *infos, const char *name, const char *value);
int _erratoi(const char *str);

<<<<<<< HEAD

/**ENVIROMENT**/
void print_list_str(list_t *head);
int starts_with(const char *str, const char *prefix);
void add_node_end(list_t **head, const char *str, int len);
int _setenv(info_t *infos, const char *name, const char *value);
void _unsetenv(info_t *infos, const char *name);


/*--PROTOTYPES---*/

void _setenv(info_t *infos, const char *name, const char *value);
void _setenv_array(info_t *infos, const char *name, const char *value);
void _unsetenv_array(info_t *infos, const char *name);

#endif
=======
#endif /* CISFUN_SHELL_H */
>>>>>>> ed440e822346ed830b6ab580e383428e7f0ab375


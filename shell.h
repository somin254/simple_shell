#ifndef SHELL_H
#define SHELL_H

/*-----LIBRARIES---*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WRITE_BUF_SIZE 256
#define PROMPT "#cisfun$ "

typedef struct list_t {
    char *str;
    struct list_t *next;
} list_t;

typedef struct {
    char **argv;
    char **env;
    int argc;
    int status;
    int err_num;
    int readfd;
    list_t *env_list;
    const char *prompt;
} info_t;

/*--PROTOTYPES---*/

int changeCurrentDirectory(info_t *infos);
int printCurrentEnvironment(info_t *infos);
int initializeOrModifyEnvVar(info_t *infos);
char *getEnvVarValue(info_t *infos, const char *names);
int populateEnvList(info_t *info);
int removeEnvVar(info_t *infos);
int showHelp(info_t *infos);
int exitShell(info_t *infos);
/*errors.c*/
void _eputs(char *str);
int _putfd(char ch, int fd);
int _putsfd(char *str, int fd);
int _eputchar(char ch);
/*_ATOI.C*/
int interactive(info_t *infos);
int _isalpha(int ch);
int _atoi(char *str);
int is_delim(char ch, char *delime);


void _puts(const char *str);
char *_getenv(info_t *infos, const char *name);
int _strcmp(const char *s1, const char *s2);
void _putchar(char c);
void print_error(info_t *infos, const char *message);
void _setenv(info_t *infos, const char *name, const char *value);
int _erratoi(const char *str);


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


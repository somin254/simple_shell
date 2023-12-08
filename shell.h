#ifndef SHELL_H
#define SHELL_H

/*-----LIBRARIES---*/
#include <stdio.h>
#include <unistd.h>

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




#endif

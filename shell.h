#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/* To convert #s */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* for reading and writing buffs */
#define READ_BUF_SIZE 1024
#define FLUSH_BUFFER -1
#define WRITE_BUF_SIZE 1024

/* to chain cmd */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* one if using syt getline */
#define USE_STRTOK 0
#define USE_GETLINE 0

/*check history */
#define MAX_HISTORY     4096
#define HIST_FILE       ".simple_shell_history"


extern char **environ;

/**
  *struct builtin - check for builtin environ
  *@type: char checked
  *@func: function checked
  */
typedef struct builtin
{
        char *name;
        char *type;
        int (*func)(ino_t *);

} builtin_table;

struct builtin_table
{
        const char *name;
        int (*func)(ino_t *);
};

extern struct builtin_table builtintbl[];

/**
 * struct liststr - function to the singly linked list
 * @num: the # field
 * @stringValue: the string to check
 * @nextNode: pointer to the adjoining node
 */
typedef struct liststr
{
        int num;
        char *stringValue;
        char *string;
        struct liststr *nextNode;
}
list_t;



/**
 *struct passinfo - contains pseudo-args to pipe into a funct,
 *to allow similar prototype 4 funct pointer structure
 *@arg: a str produced from getline containing args
 *@argv: an array of strings produced from arguements
 *@path: a str path for the present cmd
 *@argc: args counter
 *@line_count: error counter
 *@alias: alias node
 *@env_changed: changed environ
 *@status: returned status of the final executed cmd
 *@cmd_buf: loc of pointer to command buffer, if linking
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: fd from which to read line input
 *@histcount: hist line # count
 *@err_num: the error code for exiter
 *@linecount_flag: count # of input
 *@fname: the pg fn
 *@env: copy of local environ in linked list
 *@environ: modified copy of customized environ from LL env
 *@history: the hist node
 *@argumentCount: argument counter
 *@argumentValues: argument values
 *@environmentList: environment list
 *@environmentVariables: environment variables
 */

typedef struct passinfo {
        char *arg;
        char *argument;
        char **argumentValues;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        char **environ;
        int env_changed;
        int status;
        list_t *env;
        list_t *environmentList;
        list_t *environmentVariables;
        list_t *history;
        list_t *alias;
        char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
        int cmd_buf_type; /* CMD_type ||, &&, ; */
        int readfd;
        int histcount;
} info_t;

#define INFO_INIT { \
        NULL,          /* arg */ \
        NULL,          /* argumentValues */ \
        NULL,          /* argv */ \
        NULL,          /* path */ \
        0,             /* argc */ \
        0,             /* line_count */ \
        0,             /* err_num */ \
        0,             /* linecount_flag */ \
        NULL,          /* fname */ \
        NULL,          /* environ */ \
        0,             /* env_changed */ \
        0,             /* status */ \
        NULL,          /* env */ \
        NULL,          /* environmentList */ \
        NULL,          /* environmentVariables */ \
        NULL,          /* history */ \
        NULL,          /* alias */ \
        NULL,          /* cmd_buf */ \
        0,             /* cmd_buf_type */ \
        0,             /* readfd */ \
        0              /* histcount */ \
}


/* Prototypes for Environ_m.c */
int _populateEnvironmentList(info_t *);
int _myunsetenv(info_t *);
int _mysetenv(info_t *);
char *_retrieveEnvironmentValue(info_t *, const char *);
int _printEnvironment(info_t *information);

/* Prototypes for Getenv_m.c */
int updateEnvVar(info_t *info, char *, char *);
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);

/* Prototypes for Getinfo_m.c*/
void free_info(info_t *, int);
void set_info(info_t *, char **);
void clear_info(info_t *info);

/* Prototypes for Getline_m.c */
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);
ssize_t read_buf(info_t *, char *, size_t *);

/* Prototypes for Lists1_m.c */
void set_info(info_t *, char **);
void clear_info(info_t *info);

/* Prototypes for Getline_m.c */
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);
ssize_t read_buf(info_t *, char *, size_t *);
ssize_t input_buf(info_t *, char **, size_t *);
ssize_t get_input(info_t *);

/* Prototypes for Lists1_m.c */
void set_info(info_t *, char **);
void clear_info(info_t *info);

/* Prototypes for Lists1_m.c */
size_t get_list_length(const list_t *);
char* convert_number(int, int, int);
size_t list_str(const list_t *);
ssize_t find_node_index(list_t *, list_t *);
list_t *find_node_with_prefix(list_t *, char *, char);
size_t print_linked_list(const list_t *);
char **convert_list_to_strings(list_t *);
size_t get_list_length(const list_t *);

/* Prototypes for Lists_m.c */
void freeList(list_t **);
int deleteNodeAtIndex(list_t **, unsigned int);
size_t printStringList(const list_t *);
list_t *addNodeAtEnd(list_t **, const char *, int);
list_t *addNode(list_t **, const char *, int);

/* Prototypes for Memory_m.c */
int safely_free_pointer(void **);

/* Prototypes for Reallocate_m.c */
void *customReallocate(void *, unsigned int, unsigned int);
void freeStringArray(char **);
char *my_memset(char *, char, unsigned int);

/* Prototypes for Strings_m.c */
char *concatenate_strings(char *, char *);
char *check_starts_with(const char *, const char *);
int compare_strings(char *, char *);
int get_string_length(char *str);
char *starts_with(const char *, const char *);
/* Prototypes for Tokenizer_m.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* Prototypes for Vars_m.c */
int replace_string(char **, char *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *information);

/* prototypes loop_am.c */
void fork_and_execute_command(info_t *);
void find_and_execute_command(info_t *);
int find_and_execute_builtin(info_t *);
int main_shell_loop(info_t *, char **);
void print_error_message(info_t *, const char *);
char *find_path(info_t *, const char *, const char *);
void print_prompt(const char *);
void fork_cmd(const char *);
void flush_buffer(void);
int is_cmd(info_t *info, const char *arg);
int read_user_input(const char *info);

/* prototypes to builtin_am.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *info);

/* prototypes to builtin1_am.c */
int _myalias(info_t *);
void print_alias_without_return(list_t *alias);
int set_alias(info_t *, char *);
int unset_alias(info_t *, char *);
int _myhistory(info_t *);
int deleteAliasByName(list_t **aliasList, const char *aliasName);
int findAliasIndex(list_t *aliasList, const char *aliasName);

list_t* findAliasStartingWith(list_t* alias, const char*, char);
int print_alias(list_t *alias);
void deleteAliasByIndex(list_t* aliasList, int);

void printList(list_t *list);
const char *startsWithAlias(list_t *aliasList, const char *, char);

/* prototype to delimiter_am.c */
int _atoi(char *);
int _isalpha(int);
int is_delim(char, char *);
int interactive(info_t *);

/* prototypes to error1_checker.c */
void remove_first_comment(char *);
char *convert_to_string(long int, int, int);
int print_decimal(int, int);
void print_error(info_t *, char *);
int strToIntWithErrHandling(char *);
int putchar_to_stdout(char);
void print_to_stdout(const char *);
void print_to_stdout_line_number(int);
void print_to_stderr(const char *);

/* prototypes to error_checker.c */
int _putsfd(char *, int);
int _putfd(char, int);
int _eputchar(char);
void _eputs(char *);

/* prototypes to exiter.c */
char *my_strchr(char *, char);
char *_strncat(char *dest, char *src, int x);
char *_strncpy(char *, char *, int);

/* prototypes to histo_am.c */
int addtoHistoryList(info_t *, char *, int);
int loadHistoryFromFile(info_t *);
int writeHistoryToFile(info_t *info);
char *fetchHistoryFilePath(info_t *);
int updateHistoryNumbers(info_t *);
void renumberHistory(info_t *info);
void writeStringToFile(const char *str, int fileDescriptor);
void flushBufferToFile(int action, int fileDescriptor);
char *getEnvironmentVariable(info_t *info, const char *varName);
void copyString(char *dest, const char *src);

/*prototypes to parser_am.c */
char *findCommandPath(info_t *info, char *, char *);
char *duplicateCharacters(char *, int, int);
int isExecutableCommand(info_t *, char *);

/* prototypes to shell_am.c */
int main(int, char **);

/* prototypes to string1_am.c*/
int _putchar(char);
void _puts(char *);
char *_strdup(const char *);
char *_strcpy(char *, char *);

#endif

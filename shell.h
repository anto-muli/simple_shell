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

/* To convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* for reading and writing buffs */
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
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
#define HIST_MAX     4096
#define HIST_FILE       ".simple_shell_history"


extern char **environ;


/**
 * struct liststr - function to the singly linked list
 * @num: the # field
 * @str: the string to check
 * @next: pointer to the adjoining node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
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
 */

typedef struct passinfo
{
	char *arg;
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
	list_t *history;
	list_t *alias;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mgt */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, 0, 0, NULL, NULL, NULL, NULL, \
	0, 0, 0}

/**
 *struct builtin - check for builtin environ
 *@type: char checked
 *@func: function checked
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



/* Prototypes for Environ_m.c */
char *_fetchenv(info_t *, const char *);
int _findenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int generate_env_list(info_t *);

/* Prototypes for Getenv_m.c */
char **fetch_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* Prototypes for Getinfo_m.c*/
void wipe_info(info_t *);
void place_info(info_t *, char **);
void release_info(info_t *, int);

/* Prototypes for Lists1_m.c */
void set_info(info_t *, char **);
void clear_info(info_t *info);

/* Prototypes for Getline_m.c */
ssize_t fetch_input(info_t *);
int _fetchline(info_t *, char **, size_t *);
void sigintOperator(int);

/* Prototypes for Lists1_m.c */
size_t list_length(const list_t *);
char **convert_list_to_strings(list_t *);
size_t display_list(const list_t *);
list_t *first_node(list_t *, char *, char);
ssize_t fetch_node_index(list_t *, list_t *);

/* Prototypes for Lists_m.c */
list_t *attach_node(list_t **, const char *, int);
list_t *attach_node_end(list_t **, const char *, int);
size_t display_list_str(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void release_list(list_t **);

/* Prototypes for Memory_m.c */
int bfree(void **);

/* Prototypes for Reallocate_m.c */
char *_memoryset(char *, char, unsigned int);
void free_string_array(char **);
void *_reallocate(void *, unsigned int, unsigned int);

/* Prototypes for Strings_m.c */
char *_strconcatenate(char *, char *);
char *str_starts_with(const char *, const char *);
int _strcompare(char *, char *);
int _strlength(char *str);

/* Prototypes for Tokenizer_m.c */
char **split_str(char *, char *);
char **split_str2(char *, char);

/* Prototypes for Vars_m.c */
int confirm_chain(info_t *, char *, size_t *);
void test_chain(info_t *, char *, size_t *, size_t, size_t);
int change_alias(info_t *);
int change_vars(info_t *);
int change_string(char **, char *);

/* prototypes loop_am.c */
int myhsh(info_t *, char **);
int detect_builtin(info_t *);
void detect_cmd(info_t *);
void split_cmd(info_t *);

/* loophsh.c */
int loophsh(char **);

/* prototypes to builtin_am.c */
int _ourexodus(info_t *);
int _ourcd(info_t *);
int _myaid(info_t *);

/* prototypes to builtin1_am.c */
int _ourhist(info_t *);
int _ouralias(info_t *);
int undo_alias(info_t *, char *);
int fix_alias(info_t *, char *);
int display_alias (list_t *);

/* prototype to delimiter_am.c */
int is_interactive(info_t *);
int check_delim(char, char *);
int _checkalpha(int);
int _atomizer(char *);

/* prototypes to error1_checker.c */
int _erratoi(char *);
void display_error(info_t *, char *);
int display_d(int, int);
char *change_number(long int, int, int);
void eliminate_comments(char *);

/* prototypes to error_checker.c */
void _displaystr(char *);
int _displaychar(char);
int _displayfd(char c, int fd);
int _displaysfd(char *str, int fd);

/* prototypes to exiter.c */
char *_strncopy(char *, char *, int);
char *_strnconcatenate(char *, char *, int);
char *_strchars(char *, char);

/* prototypes to histo_am.c */
char *fetch_histfile(info_t *info);
int record_hist(info_t *info);
int scan_hist(info_t *info);
int create_histlist(info_t *info, char *buf, int linecount);
int reorder_hist(info_t *info);

/*prototypes to parser_am.c */
int confirm_cmd(info_t *, char *);
char *clone_chars(char *, int, int);
char *detect_path(info_t *, char *, char *);

/* prototypes to Main.c */
int main(int, char **);

/* prototypes to string1_am.c*/
int _putchar(char);
void _puts(char *);
char *_strclone(const char *);
char *_strcopy(char *, char *);

#endif

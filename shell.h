#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for NumberToBaseString() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
* struct liststr - singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
* struct passinfo - contains pseudo-arguements to pass into a function,
* allowing uniform prototype for function pointer struct
* @arg: a string generated from getline containing arguements
* @argv:an array of strings generated from arg
* @path: a string path for the current command
* @argc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()s
* @linecount_flag: if on count this line of input
* @fname: the program filename
* @env: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @history: the history node
* @alias: the alias node
* @env_changed: on if environ was changed
* @status: the return status of the last exec'd command
* @cmd_buf: address of pointer to cmd_buf, on if chaining
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input
* @histcount: the history line number count
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
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
* struct builtin - contains a builtin string and related function
* @type: the shell_commands.command flag
* @func: the function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


/* shloop.c */
int hsh(info_t *, char **);
int BuiltinFinder(info_t *);
void SearchCommandExternal(info_t *);
void ExecuteCommand(info_t *);

/* verify_cmd_executable.c */
int IsExecutableFile(info_t *, char *);
char *CopyChars(char *, int, int);
char *LocateCMDInPath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* buffered_output.c */
void _DisplayStringError(char *);
int _DisplayCharError(char);
int _OutputCharToFileDescriptor(char c, int fd);
int _FileDescriptorStringOutput(char *str, int fd);

/* check_prefix.c */
int _GetLength(char *);
int _CompareStrings(char *, char *);
char *IsPrefixOf(const char *, const char *);
char *_StrMerge(char *, char *);

/* char_output.c */
char *_CopyCharArray(char *, char *);
char *_DuplicateToHeap(const char *);
void _PrintToStdOut(char *);
int _putchar(char);

/* exits.c */
char *_StringFill(char *, char *, int);
char *_TailoredStringAppend(char *, char *, int);
char *_CharLocation(char *, char);

/* str_to_word_array.c */
char **StrToWordArray(char *, char *);
char **SplitStringChar(char *, char);

/* DynamicMemory.c */
char *_ByteSet(char *, char, unsigned int);
void DeallocateStrings(char **);
void *_DynamicMemory(void *, unsigned int, unsigned int);

/* deallocate_ptr.c */
int FreeAndNull(void **);

/* ExtractIntFromString.c */
int CheckShell(info_t *);
int CheckCharSeparator(char, char *);
int _CheckAlphaLetter(int);
int _ExtractIntFromString(char *);

/* buffered_reporting.c */
int _StringToInt(char *);
void OutputErrorMessage(info_t *, char *);
int DecimalOutput(int, int);
char *NumberToBaseString(long int, int, int);
void StripFirstComment(char *);

/* shell_commands.c */
int _TerminateShell(info_t *);
int _ChangeDir(info_t *);
int _DisplayHelp(info_t *);

/* alias_history_utility.c */
int _ShowCommandHistory(info_t *);
int _myalias(info_t *);

/*toemLineParser.c */
ssize_t InputParser(info_t *);
int LineParser(info_t *, char **, size_t *);
void HandleSigint(int);

/* set_info_from_arguments.c */
void InitializeInfo(info_t *);
void ConfigureInfo(info_t *, char **);
void ReleaseInfo(info_t *, int);

/* environment_management.c */
char *_OutputEnvironmentVariables(info_t *, const char *);
int _PrepareEnvironmentList(info_t *);
int _ModifyEnvironmentVariable(info_t *);
int _EreaseEnvironmentValue(info_t *);
int DisplayEnvironmentList(info_t *);

/* OutputEnvironmentVariables.c */
char **EnvironmentParser(info_t *);
int _EnvironmentVariableEreaser(info_t *, char *);
int _SetEnvironmentVariable(info_t *, char *, char *);

/* file_operations.c */
char *OperationsFilePathParser(info_t *info);
int SaveOperations(info_t *info);
int LoadOperations(info_t *info);
int AddOperationsList(info_t *info, char *buf, int linecount);
int RenumberOperationsList(info_t *info);

/* update_node_at_index.c */
list_t *PrependNode(list_t **, const char *, int);
list_t *AppendNode(list_t **, const char *, int);
size_t OutputStringList(const list_t *);
int UnlinkNodeAtIndex(list_t **, unsigned int);
void ClearAllNodes(list_t **);

/* convert_list_to_strings.c */
size_t GetListLength(const list_t *);
char **ListToStrArray(list_t *);
size_t ListElementsOutput(const list_t *);
list_t *FindNodeWithPrefix(list_t *, char *, char);
ssize_t NodeIndexParser(list_t *, list_t *);

/* is_chain_delimeter.c */
int IdentifyChainDelimiter(info_t *, char *, size_t *);
void VerifyCommandLink(info_t *, char *, size_t *, size_t, size_t);
int AliasSubstitution(info_t *);
int ReplaceVariables(info_t *);
int UpdateStringValue(char **, char *);

#endif

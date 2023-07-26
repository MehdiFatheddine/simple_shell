#include "shell.h"
/**
* hsh - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
InitializeInfo(info);
if (CheckShell(info))
_PrintToStdOut("$ ");
_DisplayCharError(BUF_FLUSH);
r = InputParser(info);
if (r != -1)
{
ConfigureInfo(info, av);
builtin_ret = BuiltinFinder(info);
if (builtin_ret == -1)
SearchCommandExternal(info);
}
else if (CheckShell(info))
_putchar('\n');
ReleaseInfo(info, 0);
}
SaveOperations(info);
ReleaseInfo(info, 1);
if (!CheckShell(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}
/**
* BuiltinFinder - finds a shell_commands.command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int BuiltinFinder(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _TerminateShell},
{"env", _PrepareEnvironmentList},
{"help", _DisplayHelp},
{"history", _ShowCommandHistory},
{"setenv", _ModifyEnvironmentVariable},
{"unsetenv", _EreaseEnvironmentValue},
{"cd", _ChangeDir},
{"alias", _myalias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (_CompareStrings(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}
/**
* SearchCommandExternal - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void SearchCommandExternal(info_t *info)
{
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!CheckCharSeparator(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = LocateCMDInPath(info, _OutputEnvironmentVariables(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
ExecuteCommand(info);
}
else
{
if ((CheckShell(info) || _OutputEnvironmentVariables(info, "PATH=")
|| info->argv[0][0] == '/') && IsExecutableFile(info, info->argv[0]))
ExecuteCommand(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
OutputErrorMessage(info, "not found\n");
}
}
}
/**
* ExecuteCommand - forks a an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void ExecuteCommand(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, EnvironmentParser(info)) == -1)
{
ReleaseInfo(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
OutputErrorMessage(info, "Permission denied\n");
}
}
}

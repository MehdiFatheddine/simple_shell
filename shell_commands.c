#include "shell.h"
/**
* _TerminateShell - exits the shell
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: exits with a given exit status
* (0) if info.argv[0] != "exit"
*/
int _TerminateShell(info_t *info)
{
int exitcheck;
if (info->argv[1]) /* If there is an exit arguement */
{
exitcheck = _StringToInt(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
OutputErrorMessage(info, "Illegal number: ");
_DisplayStringError(info->argv[1]);
_DisplayCharError('\n');
return (1);
}
info->err_num = _StringToInt(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}
/**
* _ChangeDir - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _ChangeDir(info_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;
s = getcwd(buffer, 1024);
if (!s)
_PrintToStdOut("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = _OutputEnvironmentVariables(info, "HOME=");
if (!dir)
chdir_ret = /* TODO: what should this be? */
chdir((dir = _OutputEnvironmentVariables(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_CompareStrings(info->argv[1], "-") == 0)
{
if (!_OutputEnvironmentVariables(info, "OLDPWD="))
{
_PrintToStdOut(s);
_putchar('\n');
return (1);
}
_PrintToStdOut(_OutputEnvironmentVariables(info, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = _OutputEnvironmentVariables(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
OutputErrorMessage(info, "can't cd to ");
_DisplayStringError(info->argv[1]), _DisplayCharError('\n');
}
else
{
_SetEnvironmentVariable(info, "OLDPWD", _OutputEnvironmentVariables(info, "PWD="));
_SetEnvironmentVariable(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
* _DisplayHelp - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _DisplayHelp(info_t *info)
{
char **arg_array;
arg_array = info->argv;
_PrintToStdOut("help call works. Function not yet implemented \n");
if (0)
_PrintToStdOut(*arg_array); /* temp att_unused workaround */
return (0);
}

#include "shell.h"
/**
* IsExecutableFile - determines if a file is an executable command
* @info: the info struct
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int IsExecutableFile(info_t *info, char *path)
{
struct stat st;
(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
* CopyChars - duplicates characters
* @pathstr: the PATH string
* @start: starting index
* @stop: stopping index
*
* Return: pointer to new buffer
*/
char *CopyChars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}
/**
* LocateCMDInPath - finds this cmd in the PATH string
* @info: the info struct
* @pathstr: the PATH string
* @cmd: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *LocateCMDInPath(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pathstr)
return (NULL);
if ((_GetLength(cmd) > 2) && IsPrefixOf(cmd, "./"))
{
if (IsExecutableFile(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = CopyChars(pathstr, curr_pos, i);
if (!*path)
_StrMerge(path, cmd);
else
{
_StrMerge(path, "/");
_StrMerge(path, cmd);
}
if (IsExecutableFile(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
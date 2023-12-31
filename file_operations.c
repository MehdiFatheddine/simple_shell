#include "shell.h"
/**
* OperationsFilePathParser - gets the history file
* @info: parameter struct
*
* Return: allocated check_prefix.containg history file
*/
char *OperationsFilePathParser(info_t *info)
{
char *buf, *dir;
dir = _OutputEnvironmentVariables(info, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_GetLength(dir) + _GetLength(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_CopyCharArray(buf, dir);
_StrMerge(buf, "/");
_StrMerge(buf, HIST_FILE);
return (buf);
}
/**
* SaveOperations - creates a file, or appends to an existing file
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
int SaveOperations(info_t *info)
{
ssize_t fd;
char *filename = OperationsFilePathParser(info);
list_t *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
_FileDescriptorStringOutput(node->str, fd);
_OutputCharToFileDescriptor('\n', fd);
}
_OutputCharToFileDescriptor(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
* LoadOperations - reads history from file
* @info: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int LoadOperations(info_t *info)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = OperationsFilePathParser(info);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
AddOperationsList(info, buf + last, linecount++);
last = i + 1;
}
if (last != i)
AddOperationsList(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
UnlinkNodeAtIndex(&(info->history), 0);
RenumberOperationsList(info);
return (info->histcount);
}
/**
* AddOperationsList - adds entry to a history linked list
* @info: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @linecount: the history linecount, histcount
*
* Return: Always 0
*/
int AddOperationsList(info_t *info, char *buf, int linecount)
{
list_t *node = NULL;
if (info->history)
node = info->history;
AppendNode(&node, buf, linecount);
if (!info->history)
info->history = node;
return (0);
}
/**
* RenumberOperationsList - renumbers the history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
* Return: the new histcount
*/
int RenumberOperationsList(info_t *info)
{
list_t *node = info->history;
int i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}

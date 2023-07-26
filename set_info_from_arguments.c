#include "shell.h"
/**
* InitializeInfo - initializes info_t struct
* @info: struct address
*/
void InitializeInfo(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
* ConfigureInfo - initializes info_t struct
* @info: struct address
* @av: argument vector
*/
void ConfigureInfo(info_t *info, char **av)
{
int i = 0;
info->fname = av[0];
if (info->arg)
{
info->argv = StrToWordArray(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _DuplicateToHeap(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;
AliasSubstitution(info);
ReplaceVariables(info);
}
}
/**
* ReleaseInfo - frees info_t struct fields
* @info: struct address
* @all: true if freeing all fields
*/
void ReleaseInfo(info_t *info, int all)
{
DeallocateStrings(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
ClearAllNodes(&(info->env));
if (info->history)
ClearAllNodes(&(info->history));
if (info->alias)
ClearAllNodes(&(info->alias));
DeallocateStrings(info->environ);
info->environ = NULL;
FreeAndNull((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(BUF_FLUSH);
}
}

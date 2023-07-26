#include "shell.h"
/**
* _ShowCommandHistory - displays the history list, 1 command by line preceded
*              with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int _ShowCommandHistory(info_t *info)
{
ListElementsOutput(info->history);
return (0);
}
/**
* EreaseAlias - sets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int EreaseAlias(info_t *info, char *str)
{
char *p, c;
int ret;
p = _CharLocation(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = UnlinkNodeAtIndex(&(info->alias),
NodeIndexParser(info->alias, FindNodeWithPrefix(info->alias, str, -1)));
*p = c;
return (ret);
}
/**
* AddAlias - sets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int AddAlias(info_t *info, char *str)
{
char *p;
p = _CharLocation(str, '=');
if (!p)
return (1);
if (!*++p)
return (EreaseAlias(info, str));
EreaseAlias(info, str);
return (AppendNode(&(info->alias), str, 0) == NULL);
}
/**
* OutputAlias - prints an alias string
* @node: the alias node
*
* Return: Always 0 on success, 1 on error
*/
int OutputAlias(list_t *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = _CharLocation(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_PrintToStdOut(p + 1);
_PrintToStdOut("'\n");
return (0);
}
return (1);
}
/**
* _myalias - mimics the alias builtin (man alias)
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: Always 0
*/
int _myalias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
OutputAlias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = _CharLocation(info->argv[i], '=');
if (p)
AddAlias(info, info->argv[i]);
else
OutputAlias(FindNodeWithPrefix(info->alias, info->argv[i], '='));
}
return (0);
}

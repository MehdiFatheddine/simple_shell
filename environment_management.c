#include "shell.h"
/**
* _PrepareEnvironmentList - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int _PrepareEnvironmentList(info_t *info)
{
OutputStringList(info->env);
return (0);
}
/**
* _OutputEnvironmentVariables - gets the value of an environ variable
* @info: Structure containing potential arguments. Used to maintain
* @name: env var name
*
* Return: the value
*/
char *_OutputEnvironmentVariables(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;
while (node)
{
p = IsPrefixOf(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}
/**
* _ModifyEnvironmentVariable - Initialize a new environment variable,
*             or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int _ModifyEnvironmentVariable(info_t *info)
{
if (info->argc != 3)
{
_DisplayStringError("Incorrect number of arguements\n");
return (1);
}
if (_SetEnvironmentVariable(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}
/**
* _EreaseEnvironmentValue - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: Always 0
*/
int _EreaseEnvironmentValue(info_t *info)
{
int i;
if (info->argc == 1)
{
_DisplayStringError("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
_EnvironmentVariableEreaser(info, info->argv[i]);
return (0);
}
/**
* DisplayEnvironmentList - populates env linked list
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int DisplayEnvironmentList(info_t *info)
{
list_t *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
AppendNode(&node, environ[i], 0);
info->env = node;
return (0);
}

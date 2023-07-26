#include "shell.h"
/**
* GetListLength - determines length of linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t GetListLength(const list_t *h)
{
size_t i = 0;
while (h)
{
h = h->next;
i++;
}
return (i);
}
/**
* ListToStrArray - returns an array of strings of the list->str
* @head: pointer to first node
*
* Return: array of strings
*/
char **ListToStrArray(list_t *head)
{
list_t *node = head;
size_t i = GetListLength(head), j;
char **strs;
char *str;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_GetLength(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = _CopyCharArray(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}
/**
* ListElementsOutput - prints all elements of a list_t linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t ListElementsOutput(const list_t *h)
{
size_t i = 0;
while (h)
{
_PrintToStdOut(NumberToBaseString(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_PrintToStdOut(h->str ? h->str : "(nil)");
_PrintToStdOut("\n");
h = h->next;
i++;
}
return (i);
}
/**
* FindNodeWithPrefix - returns node whose string starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @c: the next character after prefix to match
*
* Return: match node or null
*/
list_t *FindNodeWithPrefix(list_t *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = IsPrefixOf(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}
/**
* NodeIndexParser - gets the index of a node
* @head: pointer to list head
* @node: pointer to the node
*
* Return: index of node or -1
*/
ssize_t NodeIndexParser(list_t *head, list_t *node)
{
size_t i = 0;
while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}

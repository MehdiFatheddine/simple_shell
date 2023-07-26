#include "shell.h"
/**
* _DisplayStringError - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void _DisplayStringError(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
_DisplayCharError(str[i]);
i++;
}
}
/**
* _DisplayCharError - writes the character c to stderr
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _DisplayCharError(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
/**
* _OutputCharToFileDescriptor - writes the character c to given fd
* @c: The character to print
* @fd: The filedescriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _OutputCharToFileDescriptor(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
/**
* _FileDescriptorStringOutput - prints an input string
* @str: the string to be printed
* @fd: the filedescriptor to write to
*
* Return: the number of chars put
*/
int _FileDescriptorStringOutput(char *str, int fd)
{
int i = 0;
if (!str)
return (0);
while (*str)
{
i += _OutputCharToFileDescriptor(*str++, fd);
}
return (i);
}

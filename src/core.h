#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static char *transform_text(const char *text, int (*convert)(int))
{
    char *result = malloc(strlen(text) + 1);
    for (int i = 0; text[i]; i++)
    {
        result[i] = convert(text[i]);
    }
    result[strlen(text)] = '\0';
    return result;
}
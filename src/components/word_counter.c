/**
 * File word counter components
 * Counts words, char, and lines in a file
 * Run the components: gcc word_counter.c -o wc
 * ./wc test.txt
 */

/**
 * printf()
 * fopen()
 * fgetc() reads one character at a time
 * fclose()
 * EOF - a constant that signals "end of file" reached return by fgetc() when nothing left to read
 * FILE - A type/struct that reprents an open file used to track file position, buffer etc
 */
#include <stdio.h>

/*
 * ctype.h is standard library that provides character classification and conversion functions

  Classification functions (return non-zero if true):
  - isalpha() - letter
  - isdigit() - digit
  - isalnum() - letter or digit
  - isspace() - whitespace
  - isupper() / islower() - case check
  - ispunct() - punctuation
  - isprint() - printable character

  Conversion functions:
  - toupper() - convert to uppercase
  - tolower() - convert to lowercase
 */
#include <ctype.h>

/**
 * argc (argument count) - number of command line argument passed to the program
 * argv (argument vector) - array of strings containing the actual arguements that has passed to the main
 */
int main(int argc, char *argv[])
{
    // read the first line of argc which is the file name
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Cannot count an empty file.\n");
        return 1;
    }

    int chars = 0, words = 0, lines = 0, inWord = 0;
    char ch;
    char lastChar = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        chars++;
        lastChar = ch;

        if (ch == '\n')
            lines++;

        if (isspace(ch))
        {
            inWord = 0;
        }
        else if (!inWord)
        {
            inWord = 1;
            words++;
        }
    }

    // Look for the last chanacter
    if (chars > 0 && lastChar != '\n')
        lines++;

    printf("Number of Lines: %d\n", lines);
    printf("Number of Words: %d\n", words);
    printf("Number of Characters: %d\n", chars);

    fclose(file);
    return 0;
}

#include <stdio.h>  // printf, fopen, fclose, fread, fprintf, fseek, ftell, rewind
#include <dlfcn.h>  // dlopen, dlsym, dlclose, dlerror (dynamic loading)
#include <stdlib.h> // malloc(), free()
#include <string.h> // strrchr - string reverse character reach (find the last character reached) //  snprintf

int main(int argc, char *argv[]) // argc = argument count, argv = argument values
{
    if (argc < 3) // need at least 3: program, plugin, file
    {
        printf("Usage: %s <upppercase.so|lowercase.so|reverse.so|trim.so|capitalise.so> <filename>\n",
               argv[0]);
        return 1; // exit with error code
    }

    // Load the plugin (.so file) into memory
    void *handle = dlopen(argv[1], RTLD_LAZY); // argv[1] = plugin path
    if (!handle)                               // NULL = failed to load
    {
        printf("Cannot load plugin: %s\n", dlerror()); // print error message
        return 1;
    }

    // Get pointer to transform() function from loaded plugin
    char* (*transform)(const char*) = dlsym(handle, "transform"); // dynamic library symbol 
    if (!transform) // NULL = function not found
    {
        printf("Cannot find transform function\n");
        return 1;
    }

    // Open input file
    FILE *file = fopen(argv[2], "r"); // argv[2] = filename, "r+" = read mode
    if (!file)                         // NULL = file not found
    {
        printf("Cannot open file\n");
        return 1;
    }

    // Get file size // Need to know file size to allocate exact memory
    fseek(file, 0, SEEK_END); // move cursor to end
    long size = ftell(file);  // get cursor position = file size
    rewind(file);             // move cursor back to start

    // Read entire file into memory
    char *text = malloc(size + 1); // allocate memory (+1 for \0)
    fread(text, 1, size, file);    // read 'size' bytes into 'text'
    text[size] = '\0';             // add null terminator
    fclose(file);                  // close input file

    // Create output filename (input.txt -> input_copy.txt)
    char outputName[256];              // buffer for new filename
    char *dot = strrchr(argv[2], '.'); // find last '.' in filename 
    if (dot)                           // has extension
    {
        int len = dot - argv[2]; // length before '.'
        snprintf(outputName, sizeof(outputName), "%.*s_copy%s", len, argv[2], dot); // string number print formatted - writes formatted text into a string buffer with size limit 
        // %.*s = print 'len' chars from argv[2], then "_copy", then extension
    }
    else // no extension
    {
        snprintf(outputName, sizeof(outputName), "%s_copy", argv[2]);
    }

    // Call the plugin's transform function
    char *result = transform(text); // text -> UPPERCASE (or whatever plugin does)

    // Write result to output file
    FILE *output = fopen(outputName, "w");  // "w" = write mode (creates file)
    fprintf(output, "%s", result);          // write transformed text
    fclose(output);                         // close output file
    printf("Written to: %s\n", outputName); // tell user where output is

    // Cleanup
    printf("%s\n", result); // print result to terminal
    free(text);             // free input buffer
    free(result);           // free output buffer (allocated in plugin)
    dlclose(handle);        // unload plugin
    return 0;               // success
}
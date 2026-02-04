# C Text File Formatter Plugin with Word, Line, Char Counter Component

A plugin-based text file transformation tool written in C. Uses dynamic library loading to apply different text transformations.

## Project Structure

```
├── doc/                    # Documentation
├── build/                  # Build output (generated)
├── test/
│   └── resource/           # Test input files
└── src/
    ├── main.c              # Main program - loads plugins and processes files
    ├── core.h              # Shared transformation utilities
    ├── plugin.h            # Plugin interface definition
    ├── plugins/            # Transformation plugins
    │   ├── uppercase.c     # Convert text to uppercase
    │   ├── lowercase.c     # Convert text to lowercase
    │   ├── reverse.c       # Reverse text
    │   ├── trim.c          # Trim whitespace
    │   └── capitalise.c    # Capitalize text
    └── components/
        └── word_counter.c  # Standalone word/line/char counter
```

## How to run the plugin
### Text file to all uppercase
```bash
gcc -shared -fPIC -Isrc src/plugins/uppercase.c -o build/uppercase.so
gcc src/main.c -o build/text-file-formatter -ldl
build/text-file-formatter build/uppercase.so test/resource/test.txt
```
- File for actual usecase: build/text-file-formatter build/upppercase.so <your_file_name_with_path>

### Txt file to all lowercase 
```bash
gcc -shared -fPIC -Isrc src/plugins/lowercase.c -o build/lowercase.so
gcc src/main.c -o build/text-file-formatter -ldl
build/text-file-formatter build/lowercase.so test/resource/test_copy.txt
```
- File for actual usecase: build/text-file-formatter build/upppercase.so <your_file_name_with_path>

## How to Run the Component: Word Counter
Standalone utility to count words, lines, and characters:
```bash
gcc src/components/word_counter.c -o build/wc
./build/wc test/resource/test.txt 
```
- File for actual usecase: ./build/wc <your_file_name_with_path>
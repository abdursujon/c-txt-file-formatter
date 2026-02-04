#include "core.h"

char* transform(const char *text){
    return transform_text(text, toupper);
}
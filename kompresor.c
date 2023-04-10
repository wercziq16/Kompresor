#include "kompresor.h"

#define INITIALS "WJDK"

void print_header(int compression_level, FILE * out) {
    fprintf(out, "%s", (char*)INITIALS);
    fprintf(out, "%d", compression_level);
}

void print_dict(){;}
#include "help.h"

char *help = "Pomoc programu kompresor/dekompresor\n"
             "Wywołanie:\n"
             "\t./huff [infile] [outfile] [flagi]\n"
             "\tMożliwe flagi:\n"
             "\t-0 brak kompresji\n"
             "\t-1 kompresja 8-bitowa\n"
             "\t-2 kompresja 12-bitowa\n"
             "\t-3 kompresja 16-bitowa\n"
             "\t-v statystyki kompresji\n"
             "\t-d uruchomienie dekompresji\n";

char * in_open = "Nie udalo sie otworzyc pliku wejsciowego.\n";
char * out_open = "Nie udalo sie otworzyc pliku wyjsciowego.\n";

void print_help() {
	fprintf(stderr, "%s\n", help);
}
void print_in_open() {
	fprintf(stderr, "%s\n", in_open);
}
void print_out_open() {
	fprintf(stderr, "%s\n", out_open);
}

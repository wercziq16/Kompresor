#include <stdio.h>
#include <stdlib.h>
// #include "prawdopodobienstwo.h"

int main(int argc, char** argv) {
  if (argc<2) {
    printf("Nie podano pliku wejsciowego. Podaj plik w formacie txt.");
  }
  FILE *in = fopen(argv[1], "r");
  wystapienia(in);

}

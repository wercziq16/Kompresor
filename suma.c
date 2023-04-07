#include "suma.h"

//sprawdzanie czy dziala
/*
int main(int argc, char **argv) {
    // Otwórz plik tekstowy
    FILE *plik = fopen(argv[1], "r");
    
    if (plik == NULL) {
        printf("Nie można otworzyć pliku.");
        return 1;
    }
    
    // Oblicz sumę kontrolną bitów w pliku
    unsigned long long suma_kontrolna = oblicz_sume_kontrolna(plik);
    
    // Wyświetl wynik
    printf("Suma kontrolna: %llu\n", suma_kontrolna);
    
    // Zamknij plik
    fclose(plik);
    
    return 0;
}
*/
unsigned long long oblicz_sume_kontrolna(FILE *plik) {
    unsigned long long suma = 0;
    int bit;
    
    // Odczytaj kolejne bity z pliku i wykonaj operację XOR na ich wartościach
    while ((bit = fgetc(plik)) != EOF) {
        suma ^= (unsigned char) bit;
    }
    
    // Zwróć obliczoną sumę kontrolną bitów pliku
    return suma;
}


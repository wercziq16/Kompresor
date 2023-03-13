#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
  if(argc<2){
    printf("Nie podano pliku wejsciowego. Podaj plik w formacie txt.");
  }
  FILE *in = fopen(argv[1], "r");
  int znaki[255]={0};
  if (in!=NULL){
    char znak;
    while((znak=fgetc(in))!=EOF){
      znaki[znak]++;
      } 
  }
  fclose(in);
//Sprawdzanie poprawnosci dzialania kodu
/*
  for(int i=0; i<255; i++){
    if(znaki[i]!=0){
      printf("%c %d\n", i, znaki[i]);
      }
  }
*/
}

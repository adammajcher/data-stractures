//SDIZO IS1 213B LAB06
//Adam Majcher
//ma39352@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//kompilacja zachodzi nastepujaco:
//gcc tablica_mieszajaca.c -lm
//potrzebne -lm - librery math, zeby dzialalo 'pow' - potegowanie

int SIZE = 997;

int oblicz_hash(int klucz){
  int potega = pow(2.0,klucz % 10);
  int wartosc = ((klucz % 1000) + potega + 1) % SIZE;
  return wartosc;
}

int oblicz_hash_prim(int klucz){
  int wartosc = (3 * klucz) % 19 + 1;
  return wartosc;
}

int dodaj_element_liniowo(int *tablica, int klucz){
  int H = oblicz_hash(klucz);
  int aktualny_H;
  for( int i=0; i<SIZE; i++){
    aktualny_H = (H + i) % SIZE;
    if( tablica[aktualny_H] == 0 ){
      tablica[aktualny_H] = klucz;
      return 1;
    }
  }
  //nie znalazłem miejsca wolnego w tablicy, więc niedodałem klucza
  return 0;
}

void usun_element_liniowo(int *tablica, int klucz){
  int H = oblicz_hash(klucz);
  int aktualny_H;
  for( int i=0; i<SIZE; i++){
    aktualny_H = (H + i) % SIZE;
    if( tablica[aktualny_H] == klucz ){
      tablica[aktualny_H] = -1;
      return;
    }
    if( tablica[aktualny_H] == 0 ){
      return;
    }
  }
}

void znajdz_element_liniowo(int *tablica, int klucz){
  int H = oblicz_hash(klucz);
  int aktualny_H;
  for( int i=0; i<SIZE; i++){
    aktualny_H = (H + i) % SIZE;
    if( tablica[aktualny_H] == klucz ){
      printf("%d: %d", tablica[aktualny_H], klucz);
      return;
    }
    if( tablica[aktualny_H] == 0 ){
      printf("Nie ma takiego klucza w tablicy mieszajacej.");
      return;
    }
  }
}

int dodaj_element_hashowanie_podwojne(int *tablica, int klucz){
  int H = oblicz_hash(klucz);
  int H_prim = oblicz_hash_prim(klucz);
  int aktualny_H;
  for( int i=0; i<SIZE; i++){
    aktualny_H = (H + i * H_prim) % SIZE;
    if( tablica[aktualny_H] == 0 ){
      tablica[aktualny_H] = klucz;
      return 1;
    }
  }
  //nie znalazłem miejsca wolnego w tablicy, więc niedodałem klucza
  return 0;
}

void usun_element_hashowanie_podwojne(int *tablica, int klucz){
  int H = oblicz_hash(klucz);
  int H_prim = oblicz_hash_prim(klucz);
  int aktualny_H;
  for( int i=0; i<SIZE; i++){
    aktualny_H = (H + i * H_prim) % SIZE;
    if( tablica[aktualny_H] == klucz ){
      tablica[aktualny_H] = -1;
      return;
    }
    if( tablica[aktualny_H] == 0 ){
      return;
    }
  }
}

void znajdz_element_hashowanie_podwojne(int *tablica, int klucz){
  int H = oblicz_hash(klucz);
  int H_prim = oblicz_hash_prim(klucz);
  int aktualny_H;
  for( int i=0; i<SIZE; i++){
    aktualny_H = (H + i * H_prim) % SIZE;
    if( tablica[aktualny_H] == klucz ){
      printf("%d: %d", tablica[aktualny_H], klucz);
      return;
    }
    if( tablica[aktualny_H] == 0 ){
      printf("Nie ma takiego klucza w tablicy mieszajacej.");
      return;
    }
  }
}

void wyswietl_od_do(int *tablica,int start, int koniec){
  for( int i=start; i<koniec; i++){
    printf("(%d: %d) ", i, tablica[i]);
  }
  printf("\n");
}

void dodaj_wiele_liniowo(int *tablica, int ilosc){
  int licznik = 0;
  while( licznik != ilosc ){
    int klucz = (rand() % (20001)) + 20000;
    licznik += dodaj_element_liniowo(tablica,klucz);
  }
}

void dodaj_wiele_hashowanie_podwojne(int *tablica, int ilosc){
  int licznik = 0;
  while( licznik != ilosc ){
    int klucz = (rand() % (20001)) + 20000;
    licznik += dodaj_element_hashowanie_podwojne(tablica,klucz);
  }
}

void wyczysc_tablica(int *tablica){
  for(int i=0; i<SIZE; i++){
    tablica[i] = 0;
  }
}

void odczytaj_plik(char* nazwa_pliku, int* ilosc_elementow, int *tab){
  FILE* otwieranie = fopen(nazwa_pliku, "r");
  if(otwieranie == NULL )
    printf("Nie mozna otworzyc pliku/jest pusty");
  else  {
    int i, pomocnicza;
    for(i=0;i<5;i++){
      fscanf(otwieranie, "%d", &pomocnicza);
      if(i==0)
        *ilosc_elementow = pomocnicza;
      else
        tab[i] = pomocnicza;
    }
  }
}

int main(int ilosc_argumentow, char** argumenty){
  srand(time(NULL));
  int X = 0;
  int tablica_k[4] = {0};
  if(ilosc_argumentow < 2)
      printf("Nie podano pliku do odczytu.\n");
  else
    odczytaj_plik(argumenty[1], &X, tablica_k);
  int tablica_mieszajaca[SIZE];
  //zegar-start
  clock_t start_liniowo, koniec_liniowo;
  double czas_liniowo;
  start_liniowo = clock();

  wyczysc_tablica(tablica_mieszajaca);
  usun_element_liniowo(tablica_mieszajaca,tablica_k[1]);
  dodaj_element_liniowo(tablica_mieszajaca,tablica_k[1]);
  wyswietl_od_do(tablica_mieszajaca,0,100);
  dodaj_wiele_liniowo(tablica_mieszajaca,X);
  dodaj_element_liniowo(tablica_mieszajaca,tablica_k[2]);
  dodaj_element_liniowo(tablica_mieszajaca,tablica_k[3]);
  dodaj_element_liniowo(tablica_mieszajaca,tablica_k[4]);
  wyswietl_od_do(tablica_mieszajaca,0,100);
  wyswietl_od_do(tablica_mieszajaca,500,600);
  usun_element_liniowo(tablica_mieszajaca,tablica_k[3]);
  usun_element_liniowo(tablica_mieszajaca,tablica_k[4]);
  wyswietl_od_do(tablica_mieszajaca,0,100);
  wyswietl_od_do(tablica_mieszajaca,500,600);

  //zegar-koniec
  koniec_liniowo = clock();
  czas_liniowo = (double)(koniec_liniowo - start_liniowo) / CLOCKS_PER_SEC;
  printf("Czas hashowania liniowego = %f\n", czas_liniowo);

  clock_t start_hashowanie_podwojne, koniec_hashowanie_podwojne;
  double czas_hashowanie_podwojne;
  start_hashowanie_podwojne = clock();

  wyczysc_tablica(tablica_mieszajaca);
  usun_element_hashowanie_podwojne(tablica_mieszajaca,tablica_k[1]);
  dodaj_element_hashowanie_podwojne(tablica_mieszajaca,tablica_k[1]);
  wyswietl_od_do(tablica_mieszajaca,0,100);
  dodaj_wiele_hashowanie_podwojne(tablica_mieszajaca,X);
  dodaj_element_hashowanie_podwojne(tablica_mieszajaca,tablica_k[2]);
  dodaj_element_hashowanie_podwojne(tablica_mieszajaca,tablica_k[3]);
  dodaj_element_hashowanie_podwojne(tablica_mieszajaca,tablica_k[4]);
  wyswietl_od_do(tablica_mieszajaca,0,100);
  wyswietl_od_do(tablica_mieszajaca,500,600);
  usun_element_hashowanie_podwojne(tablica_mieszajaca,tablica_k[3]);
  usun_element_hashowanie_podwojne(tablica_mieszajaca,tablica_k[4]);
  wyswietl_od_do(tablica_mieszajaca,0,100);
  wyswietl_od_do(tablica_mieszajaca,500,600);

  //zegar-koniec
  koniec_hashowanie_podwojne = clock();
  czas_hashowanie_podwojne = (double)(koniec_hashowanie_podwojne - start_hashowanie_podwojne) / CLOCKS_PER_SEC;
  printf("Czas hashowania liniowego = %f\n", czas_hashowanie_podwojne);

}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct struktura{
  int i;
  char c;
  float f;
};

void odczytaj_plik(char * nazwa_pliku, int* ilosc_struktur, char* litera_z_odczytu){
  int pomocnicza_liczba;
  char pomocniczy_char;
  FILE* otwieranie = fopen(nazwa_pliku, "r");
  if(otwieranie == NULL )
    printf("Nie mozna otworzyc pliku/jest pusty");
  else  {
    fscanf(otwieranie, "%d %c", &pomocnicza_liczba, &pomocniczy_char);
    *ilosc_struktur = pomocnicza_liczba;
    *litera_z_odczytu = pomocniczy_char;
    }
}

int losowa_liczba () {
  //wylosowanie liczby z przedzialu od -1000 do 9000
  int wylosowana_liczba =(rand() % (10000)) - 1000;
  return wylosowana_liczba;
}

char losowa_litera () {
  //wylosowanie litery z przedzialu od B do X
  int wylosowana_litera = (rand() % (89 - 66)) + 66;
  return wylosowana_litera;
}

struct struktura** tworzenie_dynamicznej_tablicy_struktur(int ilosc){
  //zalokowanie tablicy struktur
  struct struktura** tablica_struktur = malloc(ilosc*sizeof(struct struktura*));
  //uzupelnienie struktur
  int i, wylosowana_liczba;
  int tablica_pomocnicza_dla_losowych_intow[10001]={0}; //system 0/1; 0-nie wystapila, 1-wystapila

  for(i=0;i<ilosc;i++){
    //petla wytwarzajaca losowe, niepowtarzajace sie inty:
    do {
      wylosowana_liczba = losowa_liczba();
    } while(tablica_pomocnicza_dla_losowych_intow[wylosowana_liczba+1000] != 0);
    tablica_pomocnicza_dla_losowych_intow[wylosowana_liczba+1000] = 1;

    //wypelnianie struktury
    tablica_struktur[i] = malloc(sizeof(struct struktura));
    tablica_struktur[i]->i = wylosowana_liczba;
    tablica_struktur[i]->c = losowa_litera();
    tablica_struktur[i]->f = 1000+1+i;
  }
  return tablica_struktur; //zwraca wskaznik na tablice stuktur
}

void usuwanie_wszystkiego ( struct struktura** tablica_struktur, int ilosc){
  int i;
  for(i=1;i<ilosc-1;i++)
    free(tablica_struktur[i]);
  free(tablica_struktur);
}

void wyswietl_struktury ( struct struktura ** tablica_struktur, int ilosc){
  int i;
  // for(i=0;i<ilosc;i++) (DLA WSZYSTKICH)
  for(i=0;i<20;i++) //dla pierwszych 20
    printf("Z %d st, int: %d, char: %c, nr: %0.0f\n", i+1, tablica_struktur[i]->i, tablica_struktur[i]->c, tablica_struktur[i]->f);
}

void sortowanie_tablicy_struktur (struct struktura ** tablica_struktur, int ilosc){
  //sortowanie bąbelkowe, przestawianie wskaźników
  int i,j;
  int licznik_zmian=0;
  struct struktura *wskaznik_pomocniczy;
  for(i=0;i<ilosc;i++){
    for(j=0;j<ilosc-1-i;j++){
      if(tablica_struktur[j]->i > tablica_struktur[j+1]->i){
        wskaznik_pomocniczy = tablica_struktur[j];
        tablica_struktur[j] = tablica_struktur[j+1];
        tablica_struktur[j+1] = wskaznik_pomocniczy;
        licznik_zmian +=1;
      }
    }
    if ( licznik_zmian == 0){
      break;
      }
    licznik_zmian = 0;
  }
  
  printf("program posortowal tablice po %d iteracjach\n", i+1);
  //i zatrzyma sie w momencie breaka i pozostanie wartoscia rozna od 0
}

int zliczanie_wystepowania_podanej_litery(struct struktura ** tablica_struktur, int ilosc, char litera){
  int licznik = 0; //zwieksza sie za kazdym razem wystapienia szukanej litery
  int i;
  for(i=0;i<ilosc-1;i++){
    if(litera == tablica_struktur[i]->c)
      licznik +=1;
    }
  return licznik;
}

int main (int ilosc_argumentow, char** argumenty){

  int N; //ilosc struktur
  char litera; //litera do zliczenia

  //otwieranie i odczyt z pliku
  if(ilosc_argumentow < 2)
    printf("Nie podano pliku do odczytu");
  else
    odczytaj_plik(argumenty[1], &N, &litera);

  //za kazdym odpaleniem programu bedzie inny rand
  srand(time(NULL));

  //zegar-start
  clock_t begin, end;
  double time_spent;

  begin = clock();
  //tworzenie dynamicznej tablicy wskaznikow struktur
  struct struktura** tablica = tworzenie_dynamicznej_tablicy_struktur(N);

  //sortowanie
  sortowanie_tablicy_struktur(tablica,N);
  wyswietl_struktury(tablica,N); //ograniczone do 1. dwudziestu

  //zliczanie liter
  int licznik = zliczanie_wystepowania_podanej_litery(tablica,N, litera);
  printf("litera %c wystapila %d\n", litera ,licznik);

  //usuwanie
  usuwanie_wszystkiego(tablica,N);

  //zegar-koniec
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Czas trwania programu = %f\n", time_spent);

}

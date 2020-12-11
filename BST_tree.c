//SDIZO IS1 213B LAB03
//Adam Majcher
//ma39352@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct element{
  int klucz;
  char tablica_klucz[10];
  struct element* lewy;
  struct element* prawy;
};

int ile_jest_wezlow(struct element* element){
    if(element == NULL)
        return 0;
    else
        return (ile_jest_wezlow(element->prawy)+ile_jest_wezlow(element->lewy)+1);
}

void dodaj_element(struct element** wsk_root, int klucz){
  struct element* pierwszy_element = *wsk_root;

  //tworze strukturke
  struct element* nowy = (struct element*) malloc(sizeof(struct element));
  nowy->klucz = klucz;
  sprintf(nowy->tablica_klucz, "%d", klucz);
  nowy->lewy = NULL;
  nowy->prawy = NULL;

  //jezeli drzewo puste
  if(pierwszy_element == NULL)
    *wsk_root = nowy;

  //cos juz jest w drzewie
  else{
    struct element* aktualny = pierwszy_element;
    while(1){
      //podany klucz wystepuje - nic nie dodam
      if (klucz == aktualny->klucz){
        printf("Element o kluczu %d już istnieje w drzewie\n",klucz);
        free(nowy);
        break;
      }
      //szuka miejsca dla nowego klucza
      //wartosc nowego klucza mniejsza, lewy wolny
      else if(klucz < aktualny->klucz && aktualny->lewy == NULL){
        aktualny->lewy = nowy;
        break;
      }
      //wartosc nowego klucza mniejsza, lewy zajety
      else if (klucz < aktualny->klucz && aktualny->lewy != NULL){
        aktualny = aktualny->lewy;
        continue;
      }
      //wartosc nowego klucza wieksza, prawy wolny
      else if(klucz > aktualny->klucz && aktualny->prawy == NULL){
        aktualny->prawy = nowy;
        break;
      }
      //wartosc nowego klucza wieksza, prawy zajety
      else if(klucz > aktualny->klucz && aktualny->prawy != NULL){
        aktualny = aktualny->prawy;
        continue;
      }
    }
  }
}

int wyswietl_drzewo_inorder (struct element* element){
  if (element == NULL)
    return 0;
  else{
    int drzewo_lewe, drzewo_prawe;
    drzewo_lewe = wyswietl_drzewo_inorder(element->lewy);
    printf("Klucz: %d\n", element->klucz);
    drzewo_prawe = wyswietl_drzewo_inorder(element->prawy);
    return drzewo_lewe + drzewo_prawe + 1;
  }
}

void inorder (struct element* root){
  int licznik;
  licznik = wyswietl_drzewo_inorder(root);
  printf("Licznik po inorder: %d\n", licznik);
}

int wyswietl_drzewo_preorder (struct element* element){
  if (element == NULL)
    return 0;
  else{
    int drzewo_lewe, drzewo_prawe;
    printf("Klucz: %d\n", element->klucz);
    drzewo_lewe = wyswietl_drzewo_preorder(element->lewy);
    drzewo_prawe = wyswietl_drzewo_preorder(element->prawy);
    return drzewo_lewe + drzewo_prawe + 1;
  }
}

void preorder(struct element* root){
  int licznik;
  licznik = wyswietl_drzewo_preorder(root);
  printf("Licznik po preorder: %d\n", licznik);
}

int wyswietl_drzewo_postorder (struct element* element){
  if (element == NULL)
    return 0;
  else{
    int drzewo_lewe, drzewo_prawe;
    drzewo_lewe = wyswietl_drzewo_postorder(element->lewy);
    drzewo_prawe = wyswietl_drzewo_postorder(element->prawy);
    printf("Klucz: %d\n", element->klucz);
    return drzewo_lewe + drzewo_prawe + 1;
  }
}

void postorder(struct element* root){
  int licznik;
  licznik = wyswietl_drzewo_postorder(root);
  printf("Licznik po postorder: %d\n", licznik);
}

void dodaj_wiele_elementow(struct element** wsk_root, int ilosc){
  int ilosc_wezlow = 0;
  int tyle_bylo_wezlow = ile_jest_wezlow(*wsk_root);
  while(ilosc_wezlow != ilosc+tyle_bylo_wezlow){
    //randomowa liczba <-10000,10000>
    int klucz =(rand() % (20001)) - 10000;
    dodaj_element(wsk_root,klucz);
    ilosc_wezlow = ile_jest_wezlow(*wsk_root);
    }
}

struct element* znajdz_element(struct element* wsk_root, int klucz){
  struct element* aktualny = wsk_root;
  if (wsk_root == NULL)
    printf("Nie znajde takiego klucza, bo drzewo jest pusta\n");
  else{
    while(1){
      //znaleziono klucz
      if (klucz == aktualny->klucz ){
        return aktualny;
        break;
      }
      //szukany klucz mniejszy, drzewo jest rozrosniete w lewo
      else if (klucz < aktualny->klucz && aktualny->lewy != NULL ){
        aktualny = aktualny->lewy;
        continue;
      }
      //szukany klucz mniejszy, ale drzewo nie ma wiecej elementow w lewo
      else if (klucz < aktualny->klucz && aktualny->lewy == NULL){
        return NULL;
      }
      //szukany klucz wiekszy, drzewo jest rozrosniete w prawo
      else if (klucz > aktualny->klucz && aktualny->prawy != NULL ){
        aktualny = aktualny->prawy;
        continue;
      }
      //szukany klucz wiekszy, ale drzewo nie ma wiecej elementow w prawo
      else if (klucz > aktualny->klucz && aktualny->prawy == NULL ){
        return NULL;
      }
    }
  }
}

void szukaj_element(struct element *wsk_root, int klucz){
  if(wsk_root == NULL )
    printf("Nie znajde takiego elementu, bo drzewo jest puste");
  else{
    struct element* szukany = znajdz_element(wsk_root, klucz);
    if (szukany == NULL)
      printf("Nie znalazlem takiego klucza\n");
    else
      printf("Znalazlem szukany %d klucz!!\n", klucz);
  }
}

int ile_synow(struct element* aktualny){
  if(aktualny->lewy == NULL && aktualny->prawy == NULL)
    return 0;
  else if(aktualny->lewy != NULL && aktualny->prawy != NULL)
    return 2;
  else
    return 1;
}

void usun_element(struct element** wsk_root, int klucz_usuwany){
  struct element* poczatek = *wsk_root;

  //drzewo jest puste!!
  if (poczatek == NULL){
    printf("Nie mozna usunac elementu, bo drzewo jest puste");
    return;
  }

  struct element* rodzic = NULL;
  struct element* aktualny = poczatek;

  // szukanie elementu do usuniecia
  while(1){
    if(klucz_usuwany == aktualny->klucz){
      // znalazlem!!!!!!
      break;
    }
    //szukany klucz mniejszy, drzewo jest rozrosniete w lewo
    else if (klucz_usuwany < aktualny->klucz && aktualny->lewy != NULL ){
      rodzic = aktualny;
      aktualny = aktualny->lewy;
    }
    //szukany klucz mniejszy, ale drzewo nie ma wiecej elementow w lewo
    //nie znaleziono szukanego klucza
    else if (klucz_usuwany < aktualny->klucz && aktualny->lewy == NULL){
      printf("Nie ma takiego klucza do usuniecia w naszym drzewie\n");
      return;
    }
    //szukany klucz wiekszy, drzewo jest rozrosniete w prawo
    else if (klucz_usuwany > aktualny->klucz && aktualny->prawy != NULL ){
      rodzic = aktualny;
      aktualny = aktualny->prawy;
    }
    //szukany klucz wiekszy, ale drzewo nie ma wiecej elementow w prawo
    //nie znaleziono szukanego klucza
    else if (klucz_usuwany > aktualny->klucz && aktualny->prawy == NULL ){
      printf("Nie ma takiego klucza do usuniecia w naszym drzewie\n");
      return;
    }
  }

  // mam pare RODZIC + AKTUALNY(czyli element do usuniecia)

  //moj aktualny jest lisciem, nie ma synow
  if(ile_synow(aktualny) == 0){
    if(rodzic == NULL){
      //usuwam korzen; jest on jedynym elementem w drzewie
      free(aktualny);
      *wsk_root = NULL;
    }
    else {
      //aktualny jest lewym dzieckiem rodzica
      if(rodzic->lewy == aktualny)
        rodzic->lewy == NULL;
      //aktualny jest prawym dzieckiem rodzica
      else
        rodzic->prawy == NULL;
      free(aktualny);
    }
  }

  //moj aktualny(do usuniecia) ma 1. syna
  else if (ile_synow(aktualny) == 1){
    // przepisuje rodzica usuwanego elementu (!!) na jedynego syna usuwanego elementu
    struct element* jedyny_syn_usuwanego = NULL;
    if(aktualny->lewy == NULL)
      jedyny_syn_usuwanego = aktualny->prawy;
    else
      jedyny_syn_usuwanego = aktualny->lewy;

    if(rodzic == NULL)
      *wsk_root = jedyny_syn_usuwanego;
    else {
      if(rodzic->lewy == aktualny)
        rodzic->lewy = jedyny_syn_usuwanego;
      else
        rodzic->prawy = jedyny_syn_usuwanego;
    }
    free(aktualny);
  }

    else {
    // mam 2 synow
    //szukam wartosci najwiekszej(wraz z jego rodzicem) w lewym poddrzewie usuwanego do zastapienia go
    struct element* najwiekszy_w_lewym_poddrzewie_usuwanego = aktualny->lewy;
    struct element* rodzic_najwiekszego_w_lewym_poddrzewie = aktualny;
    while(najwiekszy_w_lewym_poddrzewie_usuwanego->prawy != NULL){
      rodzic_najwiekszego_w_lewym_poddrzewie = najwiekszy_w_lewym_poddrzewie_usuwanego;
      najwiekszy_w_lewym_poddrzewie_usuwanego = najwiekszy_w_lewym_poddrzewie_usuwanego->prawy;
    }

    if(rodzic_najwiekszego_w_lewym_poddrzewie == aktualny)
      najwiekszy_w_lewym_poddrzewie_usuwanego->lewy = najwiekszy_w_lewym_poddrzewie_usuwanego->lewy;
    else{
      rodzic_najwiekszego_w_lewym_poddrzewie->prawy = najwiekszy_w_lewym_poddrzewie_usuwanego->lewy;
      najwiekszy_w_lewym_poddrzewie_usuwanego->lewy = aktualny->lewy;
    }
    najwiekszy_w_lewym_poddrzewie_usuwanego->prawy = aktualny->prawy;

    if(rodzic == NULL)
      *wsk_root = najwiekszy_w_lewym_poddrzewie_usuwanego;
    else if(rodzic->lewy == aktualny)
      rodzic->lewy = najwiekszy_w_lewym_poddrzewie_usuwanego;
    else
      rodzic->prawy = najwiekszy_w_lewym_poddrzewie_usuwanego;
    free(aktualny);
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

//do MAIN -> int ilosc_argumentow, char** argumenty
int main (int ilosc_argumentow, char** argumenty){
  srand(time(NULL));
  int X = 0;
  int tablica_k[4] = {0};
  if(ilosc_argumentow < 2)
      printf("Nie podano pliku do odczytu");
  else
    odczytaj_plik(argumenty[1], &X, tablica_k);


  //zegar-start
  clock_t begin, end;
  double time_spent;
  begin = clock();

  struct element *root = NULL;

  usun_element(&root,tablica_k[1]);
  dodaj_element(&root,tablica_k[1]);
  dodaj_wiele_elementow(&root, X);
  inorder(root);
  preorder(root);
  dodaj_element(&root,tablica_k[2]);
  inorder(root);
  dodaj_element(&root,tablica_k[3]);
  dodaj_element(&root,tablica_k[4]);
  usun_element(&root,tablica_k[1]);
  preorder(root);
  szukaj_element(root,tablica_k[1]);
  usun_element(&root,tablica_k[2]);
  inorder(root);
  usun_element(&root,tablica_k[3]);
  usun_element(&root,tablica_k[4]);

  //zegar-koniec
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Czas trwania programu = %f\n", time_spent);
}

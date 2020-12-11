//SDIZO IS1 213B LAB04
//Adam Majcher
//ma39352@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct element{
  int klucz;
  int wysokosc;
  char tablica_klucz[10];
  struct element* lewy;
  struct element* prawy;
};

int maksimum(int liczba1, int liczba2){
  if( liczba1 > liczba2 )
    return liczba1;
  else
    return liczba2;
}

int wysokosc(struct element* element){
  if ( element == NULL )
    return 0;
  return element->wysokosc;
}

int pobierz_balans(struct element* element){
  if ( element == NULL )
    return 0;
  return wysokosc(element->lewy)-wysokosc(element->prawy);
}

struct element* prawa_rotacja(struct element* element){
  struct element* rodzic = element->lewy;
  struct element* prawe_dziecko = rodzic->prawy;

  rodzic->prawy = element;
  element->lewy = prawe_dziecko;

  element->wysokosc = maksimum(wysokosc(element->lewy), wysokosc(element->prawy))+1;
  rodzic->wysokosc = maksimum(wysokosc(rodzic->lewy), wysokosc(rodzic->prawy))+1;

  // printf("PRAWA rotacja, za %d wstawiam %d\n", element->klucz, rodzic->klucz);
  return rodzic;
}

struct element* lewa_rotacja(struct element* element){
  struct element* rodzic = element->prawy;
  struct element* lewe_dziecko = rodzic->lewy;

  rodzic->lewy = element;
  element->prawy = lewe_dziecko;

  element->wysokosc = maksimum(wysokosc(element->lewy), wysokosc(element->prawy))+1;
  rodzic->wysokosc = maksimum(wysokosc(rodzic->lewy), wysokosc(rodzic->prawy))+1;

  // printf("LEWA rotacja, za %d wstawiam %d\n", element->klucz, rodzic->klucz);
  return rodzic;
}

struct element* balansowanie_dodawanie(struct element* element, int klucz){

  if( element == NULL )
    return NULL;

  //schodze w prawo szukajac mojego elementu nowo
  if( klucz > element->klucz )
    element->prawy = balansowanie_dodawanie(element->prawy, klucz);
  //albo schodze w lewo
  else if ( klucz < element->klucz )
    element->lewy = balansowanie_dodawanie(element->lewy, klucz);
  else
    return element;

  //aktualizuj MAX wysokosc
  element->wysokosc = 1 + maksimum(wysokosc(element->lewy), wysokosc(element->prawy));


  //funkcja balansu
  int balans = pobierz_balans(element);

  //4 przypadki rotacji
  //lewa
  if ( balans > 1 && klucz < element->lewy->klucz ){
    return prawa_rotacja(element);
  }

  //prawa
  if( balans < -1 && klucz > element->prawy->klucz ){
    return lewa_rotacja(element);
  }

  //lewa-prawa
  if( balans > 1 && klucz > element->lewy->klucz ){
    element->lewy = lewa_rotacja(element->lewy);
    return prawa_rotacja(element);
  }

  //prawa-lewa
  if ( balans < -1 && klucz < element->prawy->klucz){
    element->prawy = prawa_rotacja(element->prawy);
    return lewa_rotacja(element);
  }

  return element;
}

struct element* balansowanie_usuwanie(struct element* element, int klucz){

  if( element == NULL )
    return NULL;

  //schodze w prawo szukajac mojego elementu nowo
  if( klucz > element->klucz )
    element->prawy = balansowanie_usuwanie(element->prawy, klucz);
  //albo schodze w lewo
  else if ( klucz < element->klucz )
    element->lewy = balansowanie_usuwanie(element->lewy, klucz);


  //aktualizuj MAX wysokosc
  element->wysokosc = 1 + maksimum(wysokosc(element->lewy), wysokosc(element->prawy));


  //funkcja balansu
  int balans = pobierz_balans(element);

  //4 przypadki rotacji
  //lewa
  int balans_lewy = pobierz_balans(element->lewy);
  int balans_prawy = pobierz_balans(element->prawy);
  if ( balans > 1 && balans_lewy >= 0 ){
    element = prawa_rotacja(element);
  }

  //prawa
  if( balans < -1 && balans_prawy <= 0 ){
    element = lewa_rotacja(element);
  }

  //lewa-prawa
  if( balans > 1 && balans_lewy < 0 ){
    element->lewy = lewa_rotacja(element->lewy);
    element = prawa_rotacja(element);

  }

  //prawa-lewa
  if ( balans < -1 && balans_prawy > 0){
    element->prawy = prawa_rotacja(element->prawy);
    element = lewa_rotacja(element);
  }

  return element;
}

void dodaj_element(struct element** wsk_root, int klucz){
  struct element* pierwszy_element = *wsk_root;

  struct element* nowy = (struct element*) malloc(sizeof(struct element));
  nowy->klucz = klucz;
  nowy->wysokosc = 1;
  sprintf(nowy->tablica_klucz, "%d", klucz);
  nowy->lewy = NULL;
  nowy->prawy = NULL;

  //jezeli drzewo puste
  if(pierwszy_element == NULL){
    *wsk_root = nowy;
    return;
  }
  //cos juz jest w drzewie
  else{
    struct element* aktualny = pierwszy_element;
    while(1){
      //podany klucz wystepuje - nic nie dodam
      if (klucz == aktualny->klucz){
        printf("Element o kluczu %d już istnieje w drzewie\n",klucz);
        free(nowy);
        return;
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
  struct element* nowy_root = balansowanie_dodawanie(pierwszy_element, klucz);
  *wsk_root = nowy_root;
  printf("DODALEM %d", nowy->klucz);
}

int ile_jest_wezlow(struct element* element){
    if(element == NULL)
        return 0;
    else
        return (ile_jest_wezlow(element->prawy)+ile_jest_wezlow(element->lewy)+1);
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

void znajdz_element(struct element* wsk_root, int klucz){
  if( wsk_root == NULL ){
    printf("Drzewo puste, szukany element w nim nie wystepuje");
    return;
  }
  struct element* aktualny = wsk_root;
  while(1){
    //znaleziono klucz
    if (klucz == aktualny->klucz ){
      printf("Znalazlem szukany %d klucz w drzewie", aktualny->klucz);
      break;
    }
    //szukany klucz mniejszy, drzewo jest rozrosniete w lewo
    else if (klucz < aktualny->klucz && aktualny->lewy != NULL ){
      aktualny = aktualny->lewy;
      continue;
    }
    //szukany klucz mniejszy, ale drzewo nie ma wiecej elementow w lewo
    else if (klucz < aktualny->klucz && aktualny->lewy == NULL){
      printf("Nie znalazlem szukanego klucza\n");
      break;
    }
    //szukany klucz wiekszy, drzewo jest rozrosniete w prawo
    else if (klucz > aktualny->klucz && aktualny->prawy != NULL ){
      aktualny = aktualny->prawy;
      continue;
    }
    //szukany klucz wiekszy, ale drzewo nie ma wiecej elementow w prawo
    else if (klucz > aktualny->klucz && aktualny->prawy == NULL ){
      printf("Nie znalazlem szukanego klucza\n");
      break;
    }
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
  if( poczatek == NULL ){
    printf("Drzewo puste, nie mozna usunac elementu");
    return;
  }

  struct element* aktualny = poczatek;
  struct element* rodzic = NULL;
  //szukam element do usuniecia(aktualny) oraz jego rodzica(by zmienic mu lewy/prawy)
  while(1){
    if( klucz_usuwany == aktualny->klucz ){
      // znalazlem!!!!!!
      break;
    }
    //szukany klucz mniejszy, drzewo jest rozrosniete w lewo
    else if ( klucz_usuwany < aktualny->klucz && aktualny->lewy != NULL ){
      rodzic = aktualny;
      aktualny = aktualny->lewy;
    }
    //szukany klucz mniejszy, ale drzewo nie ma wiecej elementow w lewo
    //nie znaleziono szukanego klucza
    else if ( klucz_usuwany < aktualny->klucz && aktualny->lewy == NULL ){
      printf("Nie ma takiego klucza do usuniecia w naszym drzewie\n");
      return;
    }
    //szukany klucz wiekszy, drzewo jest rozrosniete w prawo
    else if ( klucz_usuwany > aktualny->klucz && aktualny->prawy != NULL ){
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
  printf("Usunalem %d", aktualny->klucz);
  //do usuniecia jest lisciem
  if( ile_synow(aktualny) == 0 ){
    if( rodzic != NULL ){
      //aktualny jest lewym dzieckiem rodzica
      if( rodzic->lewy == aktualny )
        rodzic->lewy = NULL;
      //aktualny jest prawym dzieckiem rodzica
      else
        rodzic->prawy = NULL;
      free(aktualny);
      struct element* nowy_root = balansowanie_usuwanie(poczatek, rodzic->klucz);
      *wsk_root = nowy_root;
    }
    else{
      //usuwam korzen; jest on jedynym elementem w drzewie
      free(aktualny);
      *wsk_root = NULL;
    }

  }

  else if( ile_synow(aktualny) == 1 ){
    struct element* jedyny_syn_usuwanego = NULL;
    if(aktualny->lewy == NULL)
      jedyny_syn_usuwanego = aktualny->prawy;
    else
      jedyny_syn_usuwanego = aktualny->lewy;

    if( rodzic == NULL )
      *wsk_root = jedyny_syn_usuwanego;
    else {
      if( rodzic->lewy == aktualny )
        rodzic->lewy = jedyny_syn_usuwanego;
      else
        rodzic->prawy = jedyny_syn_usuwanego;
    }
    free(aktualny);
    struct element* nowy_root = balansowanie_usuwanie(poczatek, jedyny_syn_usuwanego->klucz);
    *wsk_root = nowy_root;
  }

  else if( ile_synow(aktualny) == 2 ){
    struct element* poprzednik = aktualny->lewy;
    struct element* rodzic_poprzednika = aktualny;
    while( poprzednik->prawy != NULL ){
      rodzic_poprzednika = poprzednik;
      poprzednik = poprzednik->prawy;
    }

    if( rodzic_poprzednika != aktualny ){
      rodzic_poprzednika->prawy = poprzednik->lewy;
      poprzednik->lewy = aktualny->lewy;
    }
    poprzednik->prawy = aktualny->prawy;

    if( rodzic == NULL )
      *wsk_root = poprzednik;
    else if( rodzic->lewy == aktualny )
      rodzic->lewy = poprzednik;
    else
      rodzic->prawy = poprzednik;

    int klucz_pomocniczy = rodzic_poprzednika->klucz;
    free(aktualny);
    poczatek = *wsk_root;
    struct element* nowy_root = balansowanie_usuwanie(poczatek, klucz_pomocniczy);
    *wsk_root = nowy_root;
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

  //zegar-start
  clock_t begin, end;
  double time_spent;
  begin = clock();

  //inizjalizacja pustego drzewa AVL
  struct element* root = NULL;
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
  znajdz_element(root,tablica_k[1]);
  usun_element(&root,tablica_k[2]);
  inorder(root);
  usun_element(&root,tablica_k[3]);
  usun_element(&root,tablica_k[4]);

  //zegar-koniec
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Czas trwania programu = %f\n", time_spent);
}

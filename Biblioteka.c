#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_IMIE 20 //Maksymalna dlugosc imienia
#define M_NAZWISKO 20 //Maksymalna dlugosc nazwiska

#define M_CZYTELNIKOW 5 //Maksymalna liczba czytelnikow w bazie danych
#define M_LICZBA_KSIAZEK 5 //Maksymalna liczba ksiazek wypozyczonych przez czytelnika

#define M_KSIAZEK 25

#define M_TYTUL 20
#define M_AUTOR 30

#define M_WYPOZYCZAJACYCH 5

#define M_NAZWA 25
#define M_KSIAZEK_KATALOG 10

#define M_KATALOGOW 25

typedef struct ksiazka
{
  char tytul[M_TYTUL];
  char autor[M_AUTOR];
  int rok; //1800<rw<2018
  int liczba_stron; //0<is<3000

  int id;

  int liczba_czytelnikow;
  int czytelnicy[M_WYPOZYCZAJACYCH];
} KSIAZKA;

typedef struct czytelnik
{
  char imie[M_IMIE];
  char nazwisko[M_NAZWISKO];

  int id;

  int liczba_ksiazek;
  int ksiazki[M_LICZBA_KSIAZEK];
} CZYTELNIK;

typedef struct katalog
{
    char nazwa[M_NAZWA];
    int id[M_KSIAZEK_KATALOG];
    int ilosc_id;
    int katalog_id;
} KATALOG;


//Funckje czytelnika:
int dodaj_czytelnika(CZYTELNIK czytelnicy[], int * liczba_czytelnikow, int * m_id);
int modyfikuj_czytelnika(CZYTELNIK czytelnicy[], int liczba_czytelnikow);
int usun_czytelnika(CZYTELNIK czytelnicy[], KSIAZKA ksiazki[], int * liczba_czytelnikow);

int znajdz_czytelnika_po_id(CZYTELNIK czytelnicy[], int liczba_czytelnikow, int id);

void wyswietl_ksiazki_czytelnika(CZYTELNIK czytelnicy[], KSIAZKA ksiazki[], int liczba_czytelnikow, int liczba_ksiazek);

//Funkcje ksiazek:
int dodaj_ksiazke(KSIAZKA ksiazki[], int * liczba_ksiazek, int * m_id);
int modyfikuj_ksiazke(KSIAZKA ksiazki[], int liczba_ksiazek);
int usun_ksiazke(KSIAZKA ksiazki[], CZYTELNIK czytelnicy[], KATALOG katalogi[], int * liczba_ksiazek, int liczba_katalogow, int liczba_czytelnikow);

int znajdz_ksiazke_po_id(KSIAZKA ksiazki[], int liczba_ksiazek, int id);

void usun_z_katalogow(KATALOG katalogi[], int liczba_katalogow, int id);

//Funkcje katalogow:
int dodaj_katalog(KATALOG katalogi[], int* liczba_katalogow, int* m_id);
int modyfikuj_katalog(KATALOG katalogi[], int katalogi_rozmiar);
void usun_katalog(KATALOG katalogi[], int * liczba_katalogow);

int znajdz_katalog_po_id(KATALOG katalogi[], int liczba_katalogow, int id);
void wyswietl_katalogi_skrot(KATALOG katalogi[], int liczba_katalogow);

int dodaj_do_katalogu(KATALOG katalogi[], KSIAZKA ksiazki[], int liczba_katalogow, int liczba_ksiazek);

//Sortowanie:
void sortuj_ksiazki(KSIAZKA books[], int liczba_ksiazek);
void sortuj_czytelnikow(CZYTELNIK czytelnicy[], int liczba_czytelnikow);

int wypozycz_ksiazke(CZYTELNIK czytelnicy[], KSIAZKA ksiazki[], int liczba_czytelnikow, int liczba_ksiazek); //Zwraca 0 jesli uzytkownik ma za duza liczbe wypozyczen, -1 jesli ksiazke wypozyczylo zbyt wiele uzytkownikow


//Funkcje pomocnicze:
int wczytaj(char slowo[], int maks_rozmiar);
void usun_z_tablicy(int tablica[], int* ilosc_elementow, int element);
int czy_jest_w(int tablica[], int rozmiar, int element);
void wczytaj_liczbe(int * id, int min, int max);

void wczytaj_ID_czytelnika (CZYTELNIK czytelnicy[], int * id, int liczba_czytelnikow);
void wczytaj_ID_ksiazki (KSIAZKA ksiazki[], int * id, int liczba_ksiazek);


void show_instruction();

//Wyswietlanie:
void wyswietl_czytelnicy(CZYTELNIK czytelnicy[], int liczba_czytelnikow);
void wyswietl_czytelnicy_skrot(CZYTELNIK czytelnicy[], int liczba_czytelnikow);
void wyswietl_ksiazki(KSIAZKA ksiazki[], CZYTELNIK czytelnicy[], int liczba_ksiazek);
void wyswietl_ksiazki_skrot(KSIAZKA ksiazki[], int liczba_ksiazek);
void wyswietl_katalogi(KATALOG katalogi[], int liczba_katalogow);

void wyswietl_ksiazki_w_katalogu(KATALOG katalogi[], KSIAZKA ksiazki[], int liczba_katalogow, int liczba_ksiazek);


//Funkcje porownujace:
int porownaj_tytuly (const void  *ksiazka1, const void  *ksiazka2);
int porownaj_lata (const void  *ksiazka1, const void  *ksiazka2);
int porownaj_strony (const void  *ksiazka1, const void  *ksiazka2);
int porownaj_autorow (const void  *ksiazka1, const void  *ksiazka2);

int porownaj_imiona (const void  *czytelnik1, const void  *czytelnik2);
int porownaj_nazwiska (const void  *czytelnik1, const void  *czytelnik2);


int main()
{
  int i;
  CZYTELNIK czytelnicy[M_CZYTELNIKOW];
  int liczba_czytelnikow = 0;
  int czytelnik_id = 0;

  KSIAZKA ksiazki[M_KSIAZEK];
  int liczba_ksiazek = 0;
  int ksiazka_id = 0;

  KATALOG katalogi[M_KATALOGOW];
  int liczba_katalogow = 0;
  int katalogi_id = 0;

  char akcja;

  show_instruction();

  do {
    if(akcja!='\n') printf("Podaj litere: ");
    akcja = getchar();
    switch(akcja)
    {
      case 'A':
      case 'a':
        if(dodaj_ksiazke(ksiazki, &liczba_ksiazek, &ksiazka_id))
          printf("Dodano ksiazke %s.\n", ksiazki[liczba_ksiazek-1].tytul);
        else
          printf("W bazie jest juz maksymalna liczba ksiazek.\n");
        break;

      case 'B':
      case 'b':
        if(dodaj_czytelnika(czytelnicy, &liczba_czytelnikow, &czytelnik_id))
            printf("Dodano czytelnika %s %s.\n", czytelnicy[liczba_czytelnikow-1].imie, czytelnicy[liczba_czytelnikow-1].nazwisko);
        else
          printf("W bazie jest juz maksymalna liczba czytelnikow.\n");
          break;

      case 'C':
      case 'c':
        if (modyfikuj_ksiazke(ksiazki, liczba_ksiazek))
          printf("Pomyslnie zmodyfikowano ksiazke. \n");
        else
          printf("Aby modyfikowac ksiazke w bazie musi znajdowac sie co najmniej jedna ksiazka!\n");
        break;

      case 'D':
      case 'd':
        if(modyfikuj_czytelnika(czytelnicy, liczba_czytelnikow))
          printf("Pomyslnie zmodyfikowano czytelnika.\n");
        else
          printf("Aby modyfikowac czytelnika w bazie musi znajdowac sie co najmniej jeden czytelnik!\n");
        break;

      case 'E':
      case 'e':
          usun_ksiazke(ksiazki, czytelnicy, katalogi, &liczba_ksiazek, liczba_katalogow, liczba_czytelnikow);
        break;

      case 'F':
      case 'f':
          usun_czytelnika(czytelnicy, ksiazki, &liczba_czytelnikow);
        break;

      case 'G':
      case 'g':
          wyswietl_ksiazki_czytelnika(czytelnicy, ksiazki, liczba_czytelnikow, liczba_ksiazek);
        break;

      case 'I':
      case 'i':
          sortuj_czytelnikow(czytelnicy, liczba_czytelnikow);
        break;

      case 'H':
      case 'h':
          sortuj_ksiazki(ksiazki, liczba_ksiazek);
        break;

      case 'j':
          i = wypozycz_ksiazke(czytelnicy, ksiazki, liczba_czytelnikow, liczba_ksiazek);
        if (i==1)
            fprintf(stderr, "Wypozyczono ksiazke!\n");
        else if (i==0)
            fprintf(stderr, "Czytelnik ma juz maksymalna liczbe wypozyczen\n");
        else if (i==-1)
            fprintf(stderr, "Ksiazke wypozyczylo juz zbyt wielu uzytkownikow.\n");
        else if (i==-2)
            fprintf(stderr, "W bazie musi byc co najmniej jeden czytelnik i jedna ksiazka!\n");
        break;

      case 'K':
      case 'k':
          wyswietl_ksiazki(ksiazki, czytelnicy, liczba_ksiazek);
        break;

      case 'L':
      case 'l':
          wyswietl_czytelnicy(czytelnicy, liczba_czytelnikow);
        break;

      case 'M':
      case 'm':
          if (dodaj_katalog(katalogi, &liczba_katalogow, &katalogi_id))
            printf("Dodano katalog %s!\n", katalogi[liczba_katalogow-1].nazwa);
          else
            fprintf(stderr, "W bazie jest juz maksymalna liczba katalogow!\n");
        break;

      case 'N':
      case 'n':
          if (modyfikuj_katalog(katalogi, liczba_katalogow))
            printf("Zmodyfikowano katalog!\n");
          else
            fprintf(stderr, "W bazie musi istniec co najmniej 1 katalog!\n");
        break;

      case 'O':
      case 'o':
          if (usun_katalog(katalogi, &liczba_katalogow))
            printf("Usunieto katalog!\n");
          else
            fprintf(stderr, "W bazie musi istniej co najmniej 1 katalog!\n");
        break;

      case 'P':
      case 'p':
          wyswietl_katalogi(katalogi, liczba_katalogow);
        break;

      case 'R':
      case 'r':
          wyswietl_ksiazki_w_katalogu(katalogi, ksiazki, liczba_katalogow, liczba_ksiazek);
        break;

      case 'S':
      case 's':
          i = dodaj_do_katalogu(katalogi, ksiazki, liczba_katalogow, liczba_ksiazek);
          if (i==1) printf("Dodano do katalogu!\n");
          else if (i==0) fprintf(stderr, "W bazie musi istniec co najmniej 1 ksiazka i 1 katalog!\n");
          else if (i==-1) fprintf(stderr, "W katalogu jest juz ta ksiazka!\n");
          else if (i==-2) fprintf(stderr, "W katalogu jest juz maksymalna liczba ksiazek!\n");
        break;

      case 'Z':
      case 'z':
        show_instruction();
        break;

      case '\n': //Po wczytaniu chara wczytany zostaje takze znak nowej linii
        break;

      case 'q':
        break;
      default:
        printf("Prosze podac litere z zakresu a-i lub q!\n");
    }

  } while(akcja!='q');

  return 0;
}

//Funkcje czytelnika:
int dodaj_czytelnika(CZYTELNIK czytelnicy[], int * liczba_czytelnikow, int * m_id)
{
  //Sprawdzamy, czy nie ma juz maksymalnej liczby czytelnikow.
  if(*liczba_czytelnikow < M_CZYTELNIKOW)
  {
    int temp;
    int dlugosc; // Dlugosc wczytanego slowa
    getchar(); // Pozbywamy sie nowej linii, ktora zostala w stdin po wprowadzeniu litery akcja

    //Wczytywanie imienia:
    do {
      printf("Podaj imie: ");
      dlugosc = wczytaj(czytelnicy[*liczba_czytelnikow].imie, M_IMIE);

      if (dlugosc==0) fprintf(stderr, "Pole imienia nie moze byc puste!\n");

    } while(dlugosc == 0);

    do {
      printf("Podaj nazwisko: ");
      dlugosc = wczytaj(czytelnicy[*liczba_czytelnikow].nazwisko, M_NAZWISKO);

      if (dlugosc==0) fprintf(stderr, "Pole nazwiska nie moze byc puste!\n");

    } while(dlugosc == 0);

    //Nadajemy rekordowi maksymalne id, aby zapewnic, ze nie bedzie dwoch czytelnikow o tym samym id
    czytelnicy[*liczba_czytelnikow].id = *m_id;
    (*m_id)++;

    //Czytelnik ma 0 wypozyczonych ksiazek
    czytelnicy[*liczba_czytelnikow].liczba_ksiazek = 0;

    //Zwiekszamy liczbe czytelnikow w bazie
    (*liczba_czytelnikow)++;

    return 1;
  }
  else
      return 0;
}

int modyfikuj_czytelnika(CZYTELNIK czytelnicy[], int liczba_czytelnikow)
{
  int id;
  int dlugosc;

  wyswietl_czytelnicy_skrot(czytelnicy, liczba_czytelnikow);

  //Sprawdzenie, czy jest przynajmniej jeden czytelnik w bazie.
  if(liczba_czytelnikow>=1)
  {
      getchar(); // Pozbywamy sie nowej linii, ktora zostala w stdin po wprowadzeniu litery akcja
      int id;

      printf("Podaj ID: ");

      wczytaj_ID_czytelnika(czytelnicy, &id, liczba_czytelnikow);
      getchar();

      do {
        printf("Podaj nowe imie: ");
        dlugosc = wczytaj(czytelnicy[id].imie, M_IMIE);
        if (dlugosc==0) fprintf(stderr, "Pole imienia nie moze byc puste!\n");
      } while(dlugosc == 0);

      do {
        printf("Podaj nowe nazwisko: ");
        dlugosc = wczytaj(czytelnicy[id].nazwisko, M_NAZWISKO);
        if (dlugosc==0) fprintf(stderr, "Pole nazwiska nie moze byc puste!\n");
      } while(dlugosc == 0);
      return 1;
  }
  return 0;
}

int usun_czytelnika(CZYTELNIK czytelnicy[], KSIAZKA ksiazki[], int * liczba_czytelnikow)
{
  //Musi byc co najmniej 1 czytelnik.
  if(*liczba_czytelnikow<1) return 0;
  else
  {
    int id;
    //int indeks;
    int jestOk;
    int i = 0; //Licznik petli.

    wyswietl_czytelnicy_skrot(czytelnicy, *liczba_czytelnikow);

    printf("Podaj id czytelnika do usuniecia.\n");

    wczytaj_ID_czytelnika(czytelnicy, &id, *liczba_czytelnikow);
    getchar();

    //Najpierw trzeba zmodyfikowac dane wypozyczajacych w rekordach ksiazek:
    //Usunac wypozyczenia:
    for(i=0; i<czytelnicy[id].liczba_ksiazek; i++)
    {
      int b_id;
      b_id = znajdz_ksiazke_po_id(ksiazki, M_KSIAZEK, czytelnicy[id].ksiazki[i]);
      usun_z_tablicy(ksiazki[b_id].czytelnicy, &ksiazki[b_id].liczba_czytelnikow, czytelnicy[id].id);
    }
    strcpy(czytelnicy[id].imie, czytelnicy[*liczba_czytelnikow-1].imie);
    strcpy(czytelnicy[id].nazwisko, czytelnicy[*liczba_czytelnikow-1].nazwisko);
    czytelnicy[id].id = czytelnicy[*liczba_czytelnikow-1].id;
    for (i=0; i < czytelnicy[*liczba_czytelnikow-1].liczba_ksiazek; i++) czytelnicy[id].ksiazki[i] = czytelnicy[*liczba_czytelnikow-1].ksiazki[i];
    czytelnicy[id].liczba_ksiazek = czytelnicy[*liczba_czytelnikow-1].liczba_ksiazek;

    czytelnicy[id].id = czytelnicy[*liczba_czytelnikow-1].id;

    (*liczba_czytelnikow)--;
    return 1;
  }

}

int znajdz_czytelnika_po_id(CZYTELNIK czytelnicy[], int liczba_czytelnikow, int id) //Id zostalo poprawnie znalezione, jesli funkcja zwroci i<liczba_czytelnikow.
{
  int i;

  for(i=0; i<liczba_czytelnikow; i++)
    if (czytelnicy[i].id == id) break;

  return i;
}

void wyswietl_ksiazki_czytelnika(CZYTELNIK czytelnicy[], KSIAZKA ksiazki[], int liczba_czytelnikow, int liczba_ksiazek)
{
  int r_id, b_id, i, jestOk;
  if (liczba_czytelnikow<=0) fprintf(stderr, "W bazie nie ma zadnych czytelnikow!\n");
  else
  {
    wyswietl_czytelnicy_skrot(czytelnicy, liczba_czytelnikow);
    printf("Podaj id czytelnika.");

    wczytaj_ID_czytelnika(czytelnicy, &r_id, liczba_czytelnikow);
    getchar();

    printf("Ksiazki %s %s:\n", czytelnicy[r_id].imie, czytelnicy[r_id].nazwisko);

    for (i=0; i<czytelnicy[r_id].liczba_ksiazek; i++)
    {
      b_id = znajdz_ksiazke_po_id(ksiazki, liczba_ksiazek, czytelnicy[r_id].ksiazki[i]);
      printf("\t%d. %s, '%s'\n", i+1, ksiazki[b_id].autor, ksiazki[b_id].tytul);
    }
  }
}

//Funckje ksiazek:
int dodaj_ksiazke(KSIAZKA ksiazki[], int * liczba_ksiazek, int * m_id)
{
  //Sprawdzamy, czy nie ma juz maksymalnej liczby ksiazek.
  if(*liczba_ksiazek < M_KSIAZEK)
  {
    int temp;
    int dlugosc; // Dlugosc wczytanego slowa
    getchar(); // Pozbywamy sie nowej linii, ktora zostala w stdin po wprowadzeniu litery akcja

    do {
      printf("Podaj tytul: ");
      dlugosc = wczytaj(ksiazki[*liczba_ksiazek].tytul, M_TYTUL);
      if (dlugosc==0) fprintf(stderr, "Tytul nie moze byc pusty!\n");
    } while(dlugosc == 0);

    do {
      printf("Podaj autora: ");
      dlugosc = wczytaj(ksiazki[*liczba_ksiazek].autor, M_AUTOR);
      if (dlugosc==0) fprintf(stderr, "Pole autora nie moze byc puste!\n");
    } while(dlugosc == 0);

    //Wczytywanie liczby stron.
      int liczba_stron;
      printf("Podaj liczbe stron: ");
      wczytaj_liczbe(&liczba_stron, 0, 3000);
      ksiazki[*liczba_ksiazek].liczba_stron = liczba_stron;

    //Wczytywanie roku wydania.
      int rok;

      printf("Podaj rok wydania: ");
      wczytaj_liczbe(&rok, 1500, 2018);
      ksiazki[*liczba_ksiazek].rok = rok;

    ksiazki[*liczba_ksiazek].id = *m_id;
    (*m_id)++;

    ksiazki[*liczba_ksiazek].liczba_czytelnikow = 0;
    (*liczba_ksiazek)++;
    return 1;
  }
  else
      return 0;
}

int modyfikuj_ksiazke(KSIAZKA ksiazki[], int liczba_ksiazek)
{
  int id;
  int dlugosc;
  int temp;

  wyswietl_ksiazki_skrot(ksiazki, liczba_ksiazek);

  if(liczba_ksiazek>=1)
  {
      getchar(); // Pozbywamy sie nowej linii, ktora zostala w stdin po wprowadzeniu litery akcja
          int jestOk;
          printf("Podaj ID modyfikowanej ksiazki.\n");
          wczytaj_ID_ksiazki(ksiazki, &id, liczba_ksiazek);
          getchar();

      do {
        printf("Podaj nowy tytul: ");
        dlugosc = wczytaj(ksiazki[id].tytul, M_TYTUL);
        if (dlugosc==0) fprintf(stderr, "Pole tytul nie moze byc puste!\n");
      } while(dlugosc == 0);

      do {
        printf("Podaj nowego autora: ");
        dlugosc = wczytaj(ksiazki[id].autor, M_AUTOR);
        if (dlugosc==0) fprintf(stderr, "Pole autor nie moze byc puste!\n");
      } while(dlugosc == 0);

      int liczba_stron;
      int czyOk;

      printf("Podaj nowa liczbe stron: ");

      wczytaj_liczbe(&liczba_stron, 0, 3000);

      ksiazki[id].liczba_stron = liczba_stron;

      int rok;

      printf("Podaj nowy rok wydania: ");

      wczytaj_liczbe(&rok, 1500, 2018);

      ksiazki[id].rok = rok;


      return 1;
  }
  return 0;
}

int usun_ksiazke(KSIAZKA ksiazki[], CZYTELNIK czytelnicy[], KATALOG katalogi[], int * liczba_ksiazek, int liczba_katalogow, int liczba_czytelnikow)
{
  int id;
  int i; //licznik petli
  int jestOk;

  wyswietl_ksiazki_skrot(ksiazki, *liczba_ksiazek);

  printf("Podaj id ksiazki do usuniecia.\n");

  wczytaj_ID_ksiazki(ksiazki, &id, *liczba_ksiazek);
  getchar();

  //Usunac ksiazki z rejestrow wypozyczen:
  for(i=0; i<ksiazki[id].liczba_czytelnikow; i++)
  {
    int r_id;
    r_id = znajdz_czytelnika_po_id(czytelnicy, liczba_czytelnikow, ksiazki[id].czytelnicy[i]);
    usun_z_tablicy(czytelnicy[r_id].ksiazki, &czytelnicy[r_id].liczba_ksiazek, ksiazki[id].id);
  }

  //Usunac ksiazki z katalogow:
  usun_z_katalogow(katalogi, liczba_katalogow, ksiazki[id].id);

  strcpy(ksiazki[id].tytul, ksiazki[*liczba_ksiazek-1].tytul);
  strcpy(ksiazki[id].autor, ksiazki[*liczba_ksiazek-1].autor);
  ksiazki[id].rok = ksiazki[*liczba_ksiazek-1].rok;
  ksiazki[id].liczba_stron = ksiazki[*liczba_ksiazek-1].liczba_stron;
  ksiazki[id].id = ksiazki[*liczba_ksiazek-1].id;
  for (i=0; i < ksiazki[*liczba_ksiazek-1].liczba_czytelnikow; i++) ksiazki[id].czytelnicy[i] = ksiazki[*liczba_ksiazek-1].czytelnicy[i];
  ksiazki[id].liczba_czytelnikow = ksiazki[*liczba_ksiazek-1].liczba_czytelnikow;

  (*liczba_ksiazek)--;
}

//Usuwa ksiazke z katalogow.
void usun_z_katalogow(KATALOG katalogi[], int liczba_katalogow, int id)
{
  int i;
  for(i=0; i<liczba_katalogow; i++)
  {
    if(czy_jest_w(katalogi[i].id, katalogi[i].ilosc_id, id))
    {
      usun_z_tablicy(katalogi[i].id, &katalogi[i].ilosc_id, id);
    }
  }
}

int znajdz_ksiazke_po_id(KSIAZKA ksiazki[], int liczba_ksiazek, int id) //Id zostalo poprawnie znalezione, jesli funkcja zwroci i<rozmiar.
{
  int i;
  for(i=0; i<liczba_ksiazek; i++)
  {
    if (ksiazki[i].id == id) break;
  }
  return i;
}

//Funkcje katalogow:
int dodaj_katalog(KATALOG katalogi[], int* liczba_katalogow, int* m_id)
{
    if (*liczba_katalogow < M_KATALOGOW)
    {
          int temp;
          int dlugosc; // Dlugosc wczytanego slowa
          getchar(); // Pozbywamy sie nowej linii, ktora zostala w stdin po wprowadzeniu litery akcja

          do {
            printf("Podaj nazwe: ");
            dlugosc = wczytaj(katalogi[*liczba_katalogow].nazwa, M_NAZWA);
            if (dlugosc==0) fprintf(stderr, "Nazwa nie moze byc pusta!\n");
          } while(dlugosc == 0);

          katalogi[*liczba_katalogow].katalog_id = *m_id;
          katalogi[*liczba_katalogow].ilosc_id = 0;

          (*liczba_katalogow)++;
          (*m_id)++;

          return 1;
    }
    else return 0;
}

int modyfikuj_katalog(KATALOG katalogi[], int liczba_katalogow)
{
  if (liczba_katalogow<=0) return 0;
  printf("Katalogi:\n");
  wyswietl_katalogi_skrot(katalogi, liczba_katalogow);
  else
  {
    int katalog_id;
    int dlugosc;
    printf("Podaj ID katalogu.\n");
    wczytaj_liczbe(&katalog_id, 0, liczba_katalogow);
    getchar();

    do {
      printf("Podaj nowa nazwe: ");
      dlugosc = wczytaj(katalogi[katalog_id].nazwa, M_NAZWA);
      if (dlugosc==0) fprintf(stderr, "Nazwa nie moze byc pusta!\n");
    } while(dlugosc == 0);

    return 1;
  }
}

int usun_katalog(KATALOG katalogi[], int * liczba_katalogow)
{
    int katalog_id, i;
    wyswietl_katalogi_skrot(katalogi, *liczba_katalogow);
    printf("Podaj ID katalogu do skasowania.\n");

    wczytaj_liczbe(&katalog_id, 0, *liczba_katalogow);
    getchar();

    if (*liczba_katalogow <= 0) return 0;
    else
    {
      katalog_id = znajdz_katalog_po_id(katalogi, *liczba_katalogow, katalog_id);
      strcpy(katalogi[katalog_id].nazwa, katalogi[*liczba_katalogow].nazwa);

      //kopiujemy id
      for(i=0; i<katalogi[*liczba_katalogow].ilosc_id; i++)
        katalogi[katalog_id].id[i] = katalogi[*liczba_katalogow].id[i];

      katalogi[katalog_id].ilosc_id = katalogi[*liczba_katalogow].ilosc_id;
      katalogi[katalog_id].katalog_id = katalogi[*liczba_katalogow].katalog_id;
      (*liczba_katalogow)--;

      return 1;
    }
}

void wyswietl_katalogi_skrot(KATALOG katalogi[], int liczba_katalogow)
{
    int i;
    printf("\tID\tNazwa\tIlosc ksiazek\n");
    for (i=0; i<liczba_katalogow; i++) printf("\t%d. %s, liczba ksiazek: %d\n", katalogi[i].katalog_id, katalogi[i].nazwa, katalogi[i].ilosc_id);
}

int znajdz_katalog_po_id(KATALOG katalogi[], int liczba_katalogow, int id) //Id zostalo poprawnie znalezione, jesli funkcja zwroci i<rozmiar.
{
  int i;
  for(i=0; i<liczba_katalogow; i++)
  {
    if (katalogi[i].katalog_id == id) break;
  }
  return i;
}

int dodaj_do_katalogu(KATALOG katalogi[], KSIAZKA ksiazki[], int liczba_katalogow, int liczba_ksiazek)
{
  if (liczba_katalogow<=0 || liczba_ksiazek <=0) return 0;
  int k_id, b_id;
  wyswietl_katalogi_skrot(katalogi, liczba_katalogow);
  printf("Podaj ID katalogu: ");

  wczytaj_liczbe(&k_id, 0, liczba_katalogow);
  getchar();

  k_id = znajdz_katalog_po_id(katalogi, liczba_katalogow, k_id);

  if (katalog[k_id].liczba_ksiazek == M_KSIAZEK_KATALOG) return -2;

  wyswietl_ksiazki_skrot(ksiazki, liczba_ksiazek);
  printf("Podaj ID ksiazki: ");

  wczytaj_ID_ksiazki(ksiazki, &b_id, liczba_ksiazek);

  if (czy_jest_w(katalogi[k_id].id, katalogi[k_id].ilosc_id, b_id)) return -1;

  katalogi[k_id].id[katalogi[k_id].ilosc_id] = b_id;
  katalogi[k_id].ilosc_id++;
  return 1;
}

int wypozycz_ksiazke(CZYTELNIK czytelnicy[], KSIAZKA ksiazki[], int liczba_czytelnikow, int liczba_ksiazek)
{
    if (liczba_czytelnikow<=0 || liczba_ksiazek <=0) return -2;
    int r_id, b_id, jestOk;
    wyswietl_czytelnicy_skrot(czytelnicy, liczba_czytelnikow);
    printf("Podaj id czytelnika\n");

    wczytaj_ID_czytelnika(czytelnicy, &r_id, liczba_czytelnikow);
    getchar();

    //Sprawdzamy, czy czytelnik moze jeszcze wypozyczyc ksiazki
    if (czytelnicy[r_id].liczba_ksiazek >= M_LICZBA_KSIAZEK) return 0;
    wyswietl_ksiazki_skrot(ksiazki, liczba_ksiazek);
    printf("Podaj id ksiazki\n");

    wczytaj_ID_ksiazki(ksiazki, &b_id, liczba_ksiazek);

    if (ksiazki[b_id].liczba_czytelnikow >= M_WYPOZYCZAJACYCH) return -1;

    //Sprawdzmy, czy czytelnik juz nie wypozyczyl tej ksiazki, oraz czy czytelnik nie ma maksymalnej ilosci ksiazek:
    if (!(czy_jest_w(czytelnicy[r_id].ksiazki, czytelnicy[r_id].liczba_ksiazek, b_id)) && czytelnicy[r_id].liczba_ksiazek< M_LICZBA_KSIAZEK)
    {
      czytelnicy[r_id].ksiazki[czytelnicy[r_id].liczba_ksiazek] = b_id;
      ksiazki[b_id].czytelnicy[ksiazki[b_id].liczba_czytelnikow] = r_id;
      (czytelnicy[r_id].liczba_ksiazek)++;
      (ksiazki[b_id].liczba_czytelnikow)++;
    }
    else
    {
      if (czytelnicy[r_id].liczba_ksiazek >= M_LICZBA_KSIAZEK) fprintf(stderr, "Blad! Czytelnik ma juz wypozyczona maksymalna liczbe ksiazek!\n");
      else fprintf(stderr, "Blad! Czytelnik juz wypozyczyl ta ksiazke!\n");
      return -3;
    }

    return 1;

}

//Sortowanie:
void sortuj_ksiazki(KSIAZKA ksiazki[], int liczba_ksiazek)
{
  char wybor;
  getchar();
  printf("Wybierz kryterium sortowania:");

  printf("\na)Po tytule\t\tb)Po autorze\nc)Po roku wydania\td)Po liczbie stron\n");

  scanf("%c", &wybor);
  //getchar(); //pozbywamy sie znaku nowej linii
  fprintf(stderr, "Wybrano %c\n", wybor);
    switch(wybor)
    {
      case 'A':
      case 'a':
        qsort(ksiazki, liczba_ksiazek, sizeof(KSIAZKA), porownaj_tytuly);
        printf("Posortowano po tytule\n");
      break;
      case 'B':
      case 'b':
        qsort(ksiazki, liczba_ksiazek, sizeof(KSIAZKA), porownaj_autorow);
        printf("Posortowano po autorze\n");
      break;
      case 'C':
      case 'c':
        qsort(ksiazki, liczba_ksiazek, sizeof(KSIAZKA), porownaj_lata);
        printf("Posortowano po roku wydania\n");
      break;
      case 'D':
      case 'd':
        qsort(ksiazki, liczba_ksiazek, sizeof(KSIAZKA), porownaj_strony);
        printf("Posortowano po ilosci stron\n");
      break;
      case '\n':
      break;
      default:
      printf("Prosze wybrac litere od a do d!\n");
    }

}

void sortuj_czytelnikow(CZYTELNIK czytelnicy[], int liczba_czytelnikow)
{
  char wybor;
  getchar();
  printf("Wybierz kryterium sortowania:");

  printf("\na)Po imieniu\tb)Po nazwisku\n");

  scanf("%c", &wybor);
  //getchar(); //pozbywamy sie znaku nowej linii
  fprintf(stderr, "Wybrano %c\n", wybor);
    switch(wybor)
    {
      case 'A':
      case 'a':
        qsort(czytelnicy, liczba_czytelnikow, sizeof(CZYTELNIK), porownaj_imiona);
        printf("Posortowano po imieniu\n");
      break;
      case 'B':
      case 'b':
        qsort(czytelnicy, liczba_czytelnikow, sizeof(CZYTELNIK), porownaj_nazwiska);
        printf("Posortowano po nazwisku\n");
      break;
      case '\n':
      break;
      default:
      printf("Prosze wybrac litere od a do d!\n");
    }

}

//Funkcje porownujace

int porownaj_tytuly (const void  *ksiazka1, const void  *ksiazka2)
{
    return strcmp(((KSIAZKA *)ksiazka1)->tytul, ((KSIAZKA *)ksiazka2)->tytul);
}

int porownaj_autorow (const void *ksiazka1, const void *ksiazka2)
{
   return strcmp(((KSIAZKA *)ksiazka1)->autor, ((KSIAZKA *)ksiazka2)->autor);
}

int porownaj_lata (const void *ksiazka1, const void *ksiazka2)
{
    return (((KSIAZKA *)ksiazka1)->rok > ((KSIAZKA *)ksiazka2)->rok - ((KSIAZKA *)ksiazka1)->rok < ((KSIAZKA *)ksiazka2)->rok);
}

int porownaj_strony (const void *ksiazka1, const void *ksiazka2)
{
    return (((KSIAZKA *)ksiazka1)->liczba_stron > ((KSIAZKA *)ksiazka2)->liczba_stron - ((KSIAZKA *)ksiazka1)->liczba_stron < ((KSIAZKA *)ksiazka2)->liczba_stron);
}

int porownaj_imiona (const void  *czytelnik1, const void  *czytelnik2)
{
    return strcmp(((CZYTELNIK *)czytelnik1)->imie, ((CZYTELNIK *)czytelnik2)->imie);
}

int porownaj_nazwiska (const void  *czytelnik1, const void  *czytelnik2)
{
    return strcmp(((CZYTELNIK *)czytelnik1)->nazwisko, ((CZYTELNIK *)czytelnik2)->nazwisko);
}

//Funkcje pomocnicze:

int wczytaj(char slowo[], int maks_rozmiar)
{
  char ch;
  int dlugosc = 0;

  //Wczytywanie znakow:
  while((ch=getchar())!='\n' && dlugosc < maks_rozmiar-1) // element o indeksie maks_rozmiar-1 jest zarezerwowany dla znaku '\0'
  {
    if (dlugosc==0) ch = toupper(ch);
    slowo[dlugosc] = ch;
    dlugosc++;
  }
  // Usuwanie zbednych danych po przekroczeniu maksymalnej dlugosci tytulu:
  if (dlugosc == maks_rozmiar-1 && ch != '\n')
    while ((ch=getchar())!='\n');

  slowo[dlugosc] = '\0';
  return dlugosc;
}

  //Funkcja pomocnicza usuwajaca elementy tablicy int. (uzyta do usuwania czytelnikow, ksiazek). Zamieniamy usuwany element z ostatnim i zmniejszamy ilosc elementow w tablicy
void usun_z_tablicy(int tablica[], int* ilosc_elementow, int element)
{
  int i = 0; //Indeks elementu
  while(i<*ilosc_elementow && tablica[i] != element) i++;
  tablica[i] = tablica[*ilosc_elementow-1];
  (*ilosc_elementow)--;
}
//Funkcja pomocnicza sprawdzajaca, czy jakis element jest w tablicy
int czy_jest_w(int tablica[], int rozmiar, int element)
{
  int i;
  for(i=0; i<rozmiar; i++)
  {
    if (tablica[i]==element) return 1;
  }
  return 0;
}

void wczytaj_liczbe(int * id, int min, int max)
{
  int jestOk;
  jestOk = scanf("%d", id);
  while(jestOk!=1 ||*id < min || *id > max-1)
  {
    char ch;
    fprintf(stderr, "Zla wartosc! Prosze podac liczbe miedzy %d a %d.\n", min, max-1);
    while((ch=getchar())!='\n');
    jestOk = scanf("%d", id);
  }
}

void wczytaj_ID_czytelnika (CZYTELNIK czytelnicy[], int * id, int liczba_czytelnikow)
{
  int jestOk;
  jestOk = scanf("%d", id);
  while(jestOk!=1)
  {
    char ch;
    fprintf(stderr, "Zla wartosc! Prosze podac jedna liczbe calkowita.\n");
    while((ch=getchar())!='\n');
    jestOk = scanf("%d", id);
  }

  *id = znajdz_czytelnika_po_id(czytelnicy, liczba_czytelnikow, *id);
  while (*id == liczba_czytelnikow)
  {
    fprintf(stderr, "Zle ID! Prosze podac wartosc z listy!\n");
    wczytaj_ID_czytelnika(czytelnicy, id, liczba_czytelnikow);
  }

}

void wczytaj_ID_ksiazki (KSIAZKA ksiazki[], int * id, int liczba_ksiazek)
{
  int jestOk;
  jestOk = scanf("%d", id);
  while(jestOk!=1)
  {
    char ch;
    fprintf(stderr, "Zla wartosc! Prosze podac jedna liczbe calkowita.\n");
    while((ch=getchar())!='\n');
    jestOk = scanf("%d", id);
  }

  *id = znajdz_ksiazke_po_id(ksiazki, liczba_ksiazek, *id);
  while (*id == liczba_ksiazek)
  {
    fprintf(stderr, "Zle ID! Prosze podac wartosc z listy!\n");
    wczytaj_ID_ksiazki(ksiazki, id, liczba_ksiazek);
  }

}

void show_instruction()
{
  printf("Biblioteka\n");
  printf("Aby zaczac, wpisz odpowiednia litere:\n");
  printf("\ta) Dodaj ksiazke\n");
  printf("\tb) Dodaj czytelnika\n");
  printf("\tc) Modyfikuj dane ksiazki\n");
  printf("\td) Modyfikuj dane czytelnika\n");
  printf("\te) Skasuj ksiazke\n");
  printf("\tf) Skasuj czytelnika\n");
  printf("\tg) Wyswietl ksiazki danego czytelnika\n");
  printf("\th) Posortuj katalog ksiazek wedlug kryteriow\n");
  printf("\ti) Posortuj katalog czytelnikow wedlug kryteriow\n");
  printf("\tj) Wypozycz ksiazke\n");
  printf("\tk) Wyswietl wszystkie ksiazki\n");
  printf("\tl) Wyswietl wszystkich czytelnikow\n");
  printf("\tm) Stworz katalog\n");
  printf("\tn) Zmien nazwe katalogu\n");
  printf("\to) Usun katalog\n");
  printf("\tp) Pokaz katalogi\n");
  printf("\tr) Pokaz ksiazki w danym katalogu\n");
  printf("\ts) Dodaj ksiazke do katalogu.\n");
  printf("\tz) Pokaz menu.\n");
  printf("\tq) Bywaj.\n");
}

//WYSWIETLANIE:
void wyswietl_ksiazki(KSIAZKA ksiazki[], CZYTELNIK czytelnicy[], int liczba_ksiazek)
{
  int i, j;
  printf("\tId\tAutor\tTytul\tLiczba stron\tRok wydania\n");
  for (i=0; i<liczba_ksiazek; i++)
  {
    printf("\t%d.\t%s\t%s\t%d\t%d\n", ksiazki[i].id, ksiazki[i].autor, ksiazki[i].tytul, ksiazki[i].liczba_stron, ksiazki[i].rok);
    for (j=0; j<ksiazki[i].liczba_czytelnikow; j++)
      {
        int id = znajdz_czytelnika_po_id(czytelnicy, M_CZYTELNIKOW, ksiazki[i].czytelnicy[j]);
        printf("\t\t%d.\t%s\t%s\n", czytelnicy[id].id, czytelnicy[id].imie, czytelnicy[id].nazwisko);
      }
  }
}

void wyswietl_ksiazki_skrot(KSIAZKA ksiazki[], int liczba_ksiazek)
{
  int i;
  printf("\tId\tAutor\tTytul\n");
  for (i=0; i<liczba_ksiazek; i++)
  {
    printf("\t%d.\t%s\t%s\n", ksiazki[i].id,  ksiazki[i].autor, ksiazki[i].tytul);
  }
}

void wyswietl_czytelnicy(CZYTELNIK czytelnicy[], int liczba_czytelnikow)
{
  int i;
  printf("\tId\tImie\tNazwisko\tLiczba wypozyczen\n");
  for (i=0; i<liczba_czytelnikow; i++)
  {
    printf("\t%d.\t%s\t%s\t%d\n", czytelnicy[i].id, czytelnicy[i].imie, czytelnicy[i].nazwisko, czytelnicy[i].liczba_ksiazek);
  }
}

void wyswietl_czytelnicy_skrot(CZYTELNIK czytelnicy[], int liczba_czytelnikow)
{
  int i;
  for (i=0; i<liczba_czytelnikow; i++)
    printf("\t%d. %s\t%s \n", czytelnicy[i].id, czytelnicy[i].imie, czytelnicy[i].nazwisko);
}

void wyswietl_katalogi(KATALOG katalogi[], int liczba_katalogow)
{
    int i;
    printf("\tId\tNazwa\tLiczba ksiazek\n");
    for (i=0; i<liczba_katalogow; i++) printf("\t%d.\t%s\t%d\n", katalogi[i].katalog_id, katalogi[i].nazwa, katalogi[i].ilosc_id);
}

void wyswietl_ksiazki_w_katalogu(KATALOG katalogi[], KSIAZKA ksiazki[], int liczba_katalogow, int liczba_ksiazek)
{
  int i, katalog_id, jestOk;
  wyswietl_katalogi(katalogi, liczba_katalogow);
  printf("Podaj id katalogu.\n");
  jestOk = scanf("%d", &katalog_id);
  while(jestOk != 1 || katalog_id<0 || katalog_id >= liczba_katalogow) //Sprawdzamy zakres id
  {
    char ch;
    printf("Prosze podac id miedzy 0 a %d!", liczba_katalogow-1);
    while ((ch=getchar())!='\n');
    scanf("%d", &katalog_id);
  }
  katalog_id = znajdz_katalog_po_id(katalogi, liczba_katalogow, katalog_id);

  for (i=0; i<katalogi[katalog_id].ilosc_id; i++)
  {
    int id = znajdz_ksiazke_po_id(ksiazki, liczba_ksiazek, katalogi[katalog_id].id[i]);
    printf("%d. %s, '%s'\n", ksiazki[id].id, ksiazki[id].autor, ksiazki[id].tytul);
  }
}

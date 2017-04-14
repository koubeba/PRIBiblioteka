#include <stdio.h>

#include "obsluga.h"
#include "czytelnik.h"

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

  if(rozmiar>=1)
  {
      getchar(); // Pozbywamy sie nowej linii, ktora zostala w stdin po wprowadzeniu litery akcja
      do {
          printf("Podaj ID modyfikowanego czytelnika.\n");
          scanf("%d", &id);
          id = znajdz_czytelnika_po_id(readers, rozmiar, id);
          if (id==rozmiar)
          {
            fprintf(stderr, "error\n");
            return -1;
          }
          getchar();
          if (id < 0 || id > rozmiar - 1) fprintf(stderr, "Zle ID! Prosze podac liczbe miedzy 0 a %d.\n", rozmiar-1);
      } while(id < 0 || id > rozmiar - 1);

      do {
        printf("Podaj nowe imie: ");
        dlugosc = wczytaj(readers[id].imie, MAKS_IMIE);
        if (dlugosc==0) fprintf(stderr, "Pole imienia nie moze byc puste!\n");
      } while(dlugosc == 0);

      do {
        printf("Podaj nowe nazwisko: ");
        dlugosc = wczytaj(readers[id].nazwisko, MAKS_NAZWISKO);
        if (dlugosc==0) fprintf(stderr, "Pole nazwiska nie moze byc puste!\n");
      } while(dlugosc == 0);
      return 1;
  }
  return 0;
}

int usun_czytelnika(CZYTELNIK czytelnicy[], int * liczba_czytelnikow)
{
  return 1;
}

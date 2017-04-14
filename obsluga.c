#include <stdio.h>
#include "obsluga.h"

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

int znajdz_czytelnika_po_id(CZYTELNIK czytelnicy[], int liczba_czytelnikow, int id) //Id zostalo poprawnie znalezione, jesli funkcja zwroci i<liczba_czytelnikow.
{
  int i;

  for(i=0; i<liczba_czytelnikow; i++)
    if (czytelnicy[i].id == id) break;

  return i;
}

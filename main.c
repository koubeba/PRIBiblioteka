#include <stdio.h>

#include "czytelnik.h"
#include "obsluga.h"

void show_instruction();

int main()
{

  CZYTELNIK czytelnicy[M_CZYTELNIKOW];
  int liczba_czytelnikow = 0;
  int czytelnik_id = 0;

  char akcja;

  do {
    //DEBUG!
    fprintf(stderr, "Liczba czytelnikow: %d\n", liczba_czytelnikow);
    akcja = getchar();
    switch(akcja)
    {
      case 'A':
      case 'a':
        break;
      case 'B':
      case 'b':
        if(dodaj_czytelnika(czytelnicy, &liczba_czytelnikow, &czytelnik_id))
            printf("Dodano czytelnika %s %s.\n", czytelnicy[liczba_czytelnikow-1].imie, czytelnicy[liczba_czytelnikow-1].nazwisko);
        else
          printf("W bazie jest juz maksymalna liczba czytelnikow.\n");
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
  printf("\tn) Dodaj ksiazki do katalogu\n");
  printf("\to) Usun katalog\n");
  printf("\tp) Pokaz katalogi\n");
  printf("\tr) Pokaz ksiazki w danym katalogu\n");
  printf("\tq) Bywaj.\n");
}

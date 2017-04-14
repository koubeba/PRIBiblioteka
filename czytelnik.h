#define M_IMIE 20 //Maksymalna dlugosc imienia
#define M_NAZWISKO 20 //Maksymalna dlugosc nazwiska

#define M_CZYTELNIKOW 5 //Maksymalna liczba czytelnikow w bazie danych
#define M_LICZBA_KSIAZEK 5 //Maksymalna liczba ksiazek wypozyczonych przez czytelnika

typedef struct czytelnik
{
  char imie[M_IMIE];
  char nazwisko[M_NAZWISKO];

  int id;

  int liczba_ksiazek;
  int ksiazki[M_LICZBA_KSIAZEK];
} CZYTELNIK;

int dodaj_czytelnika(CZYTELNIK czytelnicy[], int * liczba_czytelnikow, int * m_id);
int modyfikuj_czytelnika(CZYTELNIK czytelnicy[], int liczba_czytelnikow);
int usun_czytelnika(CZYTELNIK czytelnicy[], int * liczba_czytelnikow);

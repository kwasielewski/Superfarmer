#include <bits/stdc++.h>
#include <unistd.h> //do uzyskania ziarna na etapie testowym hosta
using namespace std;
//Program ten będzie kompilowany wraz z głównym programem zawierającym interfejs w GTK. Wszelkie funkcje hosta będą
//wywoływane przez główny program do obsługi przebiegu rozgrywki
extern long long krolikowy(const int Stado[5][7], int id);
extern long long randomizowany(const int Stado[5][7], int id);
extern long long usainbolt(const int Stado[5][7], int id);
extern long long swinski(const int Stado[5][7], int id);
extern void Koniec_Gry(int zwyciezca); //wywołanie komunikatu o zakończeniu gry w GTK
extern long long dokonajWymiany(const int Stado[5][7], int id); //wywołanie ludzkiego gracza do podjęcia deyzji o wymianie (początek cyklu)
extern void wymianaZatwierdzona(const int Stado[5][7]); //wyświetlenie informacji o zaakceptowaniu wymiany oraz aktualizacja planszy
extern void wymianaOdrzucona(); //wyświetlenie komunikatu o błędności żądania, freeze do czasu zamknięcia okienka
int (*bots[4])(const int[5][7], int); //wskaźniki na boty
int losuj() //funkcja do zastąpienia funkcją z modułu losującego - do testowania hosta
{
  srand(getpid() + time(NULL));
  return rand();
}
static bool czyKoniecGry(int Stado[5][7], int gracz)
{
  for(int j = 0; j <= 4; j++)
    if(Stado[gracz][j] == 0)
      return false;
  return true;
}
static int* usadzGraczy(bool CzyCzlowiekGra)
{
  int *Usadzenie = new int[4]; //tabela zawierająca kolejność rozgrywki poczynając od gracza pod indeksem 1
  //Gracze są oznaczani jako wartości: 1 - człowiek, 2 - bot królikowy, 3 - bot randomizowany, 4 - bot Usain Bolt, 5 - bot świński
  int wykluczony = 1; //id gracza który nie weźmie udziału w danej rozgrywce, defaultowo człowiek
  if(CzyCzlowiekGra)
    wykluczony = 2 + losuj()%4;
  int cnt = 0;
  for(int i = 1; i <= 5; i++)
    if(i != wykluczony)
      Usadzenie[cnt++] = i;
  random_shuffle(Usadzenie, Usadzenie + 4);
  for(int i = 0; i < 4; i++)
    switch (Usadzenie[i])
    {
      case 1: 
        bots[i] = dokonajWymiany;
        break;
      case 2: 
        bots[i] = krolikowy;
        break;
      case 3:
        bots[i] = randomizowany;
        break;
      case 4:
        bots[i] = usainbolt;
        break;
      case 5:
        bots[i] = swinski;
        break;
      default:
        break;
    }
  return Usadzenie;
}
static int** inicjujStada()
{
  int **Stado = new int*[5];
  for(int i = 0; i <= 4; i++)
    Stado[i] = new int[7];//0 - króliki, 1 - owce, 2 - świnie, 3 - krowy, 4 - konie, 5 - małe psy, 6 - duże psy
  Stado[0][0] = 60; Stado[0][1] = 24; Stado[0][2] = 20; Stado[0][3] = 12; Stado[0][4] = 6; Stado[0][5] = 4; Stado[0][6] = 2;
  for(int i = 1; i <= 3; i++)
    for(int j = 0; j <= 6; j++)
      Stado[i][j] = 0;
  return Stado;
}
void rozpocznijGre(bool czyCzlowiekGra)
{
  int *Usadzenie = usadzGraczy(czyCzlowiekGra);
  int **Stado = inicjujStada();
  int *Wymiana = new int[9];
  int zwyciezca = -1, kostka1, kostka2; //kostka1: 
  long long kodWymiany = 0;
  while(zwyciezca == -1){
    for(int i = 0; i < 4; i++){
      kodWymiany = bots[Usadzenie[i]](Stado[5][7], i + 1);
      if(kodWymiany & (1LL << 35)){ //gracz żąda wymiany
        konwersjaKoduWymiany(kodWymiany, Wymiana);
        if(!czyWymianaPoprawna(Stado[5][7], i + 1, Wymiana)){
          if(Usadzenie[i] != 1){
            zakonczGre(-1); //zakończenie rozgrywki z powodu błędu bota
            return;
          }
          else{ //wyświetlenie błędu żądania wymiany złożonej przez gracza i ponowienie możliwości wymiany
            i--;
            wymianaOdrzucona();
            continue;
          }
        }
        else //wymiana poprawna, dokonanie zmian w stadach
        {
          int kupno = (Wymiana[0] == 1)?1:-1;
          Stado[i][Wymiana[1]] += kupno;
          for(int j = 2; j <= 8; j++)
            Stado[i][j] -= kupno*Wymiana[j];
        }
      }
      //rzut kostką, zmiana w stadzie wynikająca z rzutu
      kostka1 = losuj();
      kostka2 = losuj();
      stadoPoRzucie(Stado[5][7], i + 1, kostka1, kostka2);
      //TUTAJ ZAPIS DO PLIKU
      if(czyKoniecGry(Stado[5][7], i + 1)){
        zwyciezca = i + 1;
        break;
      }
    }
  }
  for(int i = 0; i < 5; i++) //czyszczenie pamięci ze sterty
    delete[] Stado[i];
  delete[] Stado;
  delete[] Usadzenie;
  delete[] Wymiana;
  Koniec_Gry(zwyciezca);
}
int main() //w wersji release nie będzie tej funkcji - służy testowaniu hosta
{
  rozpocznijGre(true);
}
#include <bits/stdc++.h>
#include <unistd.h> //do uzyskania ziarna na etapie testowym hosta
using namespace std;
//Program ten będzie kompilowany wraz z głównym programem zawierającym interfejs w GTK. Wszelkie funkcje hosta będą
//wywoływane przez główny program do obsługi przebiegu rozgrywki
/* Biblioteki zewnętrzne do dołączenia w późniejszym etapie
#include "bot1.h"
#include "bot2.h"
#include "bot3.h"
#include "bot4.h"
#include "randomize.h"*/
//Boty z załączanych plików nagłówkowych
extern int krolikowy(const int tab[5][7], int id);
extern int randomizowany(const int tab[5][7], int id);
extern int usainbolt(const int tab[5][7], int id);
extern int swinski(const int tab[5][7], int id);
extern int dokonajWymiany(const int tab[5][7], int id);
typedef pair<int, int> PII;
int (*bots[4])(const int[5][7], int); //wskaźniki na boty
int losuj() //funkcja do zastąpienia funkcją z modułu losującego - do testowania hosta
{
  srand(getpid() + time(NULL));
  return rand();
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
bool rozpocznijGre(int Usadzenie[4], int Stado[5][7])
{
  //Construction site
}
int main() //w wersji release nie będzie tej funkcji - służy testowaniu hosta
{
  int *Usadzenie = usadzGraczy(true);
  int **Stado = inicjujStada();
}
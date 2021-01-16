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
typedef pair<int, int> PII;
int losuj() //funkcja do zastąpienia funkcją z modułu losującego - do testowania hosta
{
  srand(getpid() + time(NULL));
  return rand();
}
int* usadzGraczy(bool CzyCzlowiekGra)
{
  int *Usadzenie = new int[4]; //tabela zawierająca kolejność rozgrywki poczynając od gracza pod indeksem 1
  //Gracze są oznaczani jako wartości: 1 - człowiek, 2 - bot królikowy, 3 - bot randomizowany, 4 - bot zrównoważony, 5 - bot świński
  int wykluczony = 1; //id gracza który nie weźmie udziału w danej rozgrywce, defaultowo człowiek
  if(CzyCzlowiekGra)
    wykluczony = 2 + losuj()%4;
  int cnt = 0;
  for(int i = 1; i <= 5; i++)
    if(i != wykluczony)
      Usadzenie[cnt++] = i;
  random_shuffle(Usadzenie, Usadzenie + 4);
  return Usadzenie;
}
int main() //w wersji release nie będzie tej funkcji - służy testowaniu hosta
{

}
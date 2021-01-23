#include <bits/stdc++.h>
#include <unistd.h> //do uzyskania ziarna na etapie testowym hosta
using namespace std;
//Program ten będzie kompilowany wraz z głównym programem zawierającym interfejs w GTK. Wszelkie funkcje hosta będą
//wywoływane przez główny program do obsługi przebiegu rozgrywki
extern long long krolikowy(int *Stado[7], int id);
extern long long randomizowany(int *Stado[7], int id);
extern long long usainbolt(int *Stado[7], int id);
extern long long swinski(int *Stado[7], int id);
long long testowybot(int *Stado[7], int id)
{
  return 0LL;
}
extern void Koniec_Gry(int zwyciezca); //wywołanie komunikatu o zakończeniu gry w GTK
extern long long dokonajWymiany(int *Stado[7], int id); //wywołanie ludzkiego gracza do podjęcia deyzji o wymianie (początek cyklu)
extern void wymianaZatwierdzona(int *Stado[7]); //wyświetlenie informacji o zaakceptowaniu wymiany oraz aktualizacja planszy
extern void wymianaOdrzucona(); //wyświetlenie komunikatu o błędności żądania, freeze do czasu zamknięcia okienka
extern void wyswietlWynikRzutu(int *Stado[7], int id, int kostka1, int kostka2); //wyświetlenie komunikatu o wyniku rzutu i wynikających z niego zmianach w stadzie
long long (*bots[4])(int*[7], int); //wskaźniki na boty

int losuj() //funkcja do zastąpienia funkcją z modułu losującego - do testowania hosta
{
  srand(getpid() + time(NULL));
  return rand();
}

static void konwersjaKoduWymiany(int Wymiana[9], long long kodWymiany)
//funkcja zwraca liczbę zwierząt do wymiany bez oglądania się na możliwości stada
{
  Wymiana[8] = kodWymiany % (1LL << 2); //duży pies
  kodWymiany /= (1LL << 2);
  Wymiana[7] = kodWymiany % (1LL << 3); //mały pies
  kodWymiany /= (1LL << 3);
  Wymiana[6] = kodWymiany % (1LL << 3); //koń
  kodWymiany /= (1LL << 3);
  Wymiana[5] = kodWymiany % (1LL << 4); //krowa
  kodWymiany /= (1LL << 4);
  Wymiana[4] = kodWymiany % (1LL << 5); //świnia
  kodWymiany /= (1LL << 5);
  Wymiana[3] = kodWymiany % (1LL << 5); //owca
  kodWymiany /= (1LL << 5);
  Wymiana[2] = kodWymiany % (1LL << 6); //królik
  kodWymiany /= (1LL << 6);
  Wymiana[1] = kodWymiany % (1LL << 3); //id dużego zwierzęcia
  kodWymiany /= (1LL << 3);
  Wymiana[0] = kodWymiany & 1LL;
  return;
}

static bool czyWymianaPoprawna(int *Stado[7], int id, int Wymiana[9])
//funkcja sprawdza poprawność żądań z tabelą wymian i dostosowuje liczby do możliwości stada głównego 
//tj. może pogorszyć liczby z żądania gracza, lecz ten miał pełną informację na temat zasobności stada głównego żądając wymiany (wiedział ile może dostać)
{

}

static void stadoPoRzucie(int *Stado[7], int id, int kostka1, int kostka2)
{
  //kostka1: 1 - lis, 2/4/6/8/10/12 - królik, 3 - owca, 5 - świnia, 7 - koń, 9 - owca, 11 - świnia
  //kostka2: 1/3/5/7/9/11 - królik, 2 - krowa, 4 - owca, 6 - świnia, 8 - owca, 10 - wilk, 12 - owca
  int tab[5] = {0, 0, 0, 0, 0}; //kroliki, owce, swinie, krowy, konie (z kostek)
  if(kostka1 % 2 == 0)
    kostka1 = 2;
  if(kostka2 % 2 == 1)
    kostka2 = 1;
  switch (kostka1)
  {
    case 1:
      if(Stado[id][5] > 0){
        Stado[id][5]--;
        Stado[0][5]++;
      }
      else{
        Stado[0][0] += Stado[id][0];
        Stado[id][0] = 0;
      }
      break;
    case 2:
      tab[0]++;
      break;
    case 3:
      tab[1]++;
      break;
    case 5:
      tab[2]++;
      break;
    case 7:
      tab[4]++;
      break;
    case 9:
      tab[1]++;
      break;
    case 11:
      tab[2]++;
      break;
    default:
      break;
  }
  switch(kostka2)
  {
    case 1: 
      tab[0]++;
      break;
    case 2:
      tab[3]++;
      break;
    case 4:
      tab[1]++;
      break;
    case 6:
      tab[2]++;
      break;
    case 8:
      tab[1]++;
      break;
    case 10:
      if(Stado[id][6] > 0){
        Stado[id][6]--;
        Stado[0][6]++;
      }
      else
        for(int i = 1; i <= 3; i++){
          Stado[0][i] += Stado[id][i];
          Stado[id][i] = 0;
        }
      break;
    case 12:
      tab[1]++;
      break;
    default:
      break;
  }
  //transfer zwierząt z głównego stada w wyniku rozmnażania (z zachowaniem możliwości zasobnych głównego stada)
  for(int i = 0; i < 5; i++){
    int x = Stado[id][i], y = Stado[0][i];
    Stado[id][i] += min((x + tab[i])/2, y);
    Stado[0][i] -= min((x + tab[i])/2, y);
  }
  return;
}

static bool czyKoniecGry(int *Stado[7], int gracz)
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
        bots[i] = testowybot; //krolikowy;
        break;
      case 3:
        bots[i] = testowybot; //randomizowany;
        break;
      case 4:
        bots[i] = testowybot; //usainbolt;
        break;
      case 5:
        bots[i] = testowybot; //swinski;
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
  for(int i = 1; i <= 3; i++){
    Stado[i][0] = 1;
    for(int j = 1; j <= 6; j++)
      Stado[i][j] = 0;
  }
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
      kodWymiany = bots[Usadzenie[i]](Stado, i + 1);
      if(kodWymiany & (1LL << 33)){ //gracz żąda wymiany
        konwersjaKoduWymiany(Wymiana, kodWymiany);
        if(!czyWymianaPoprawna(Stado, i + 1, Wymiana)){
          if(Usadzenie[i] != 1){
            Koniec_Gry(-1); //zakończenie rozgrywki z powodu błędu bota
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
          Stado[0][Wymiana[1]] -= kupno;
          for(int j = 2; j <= 8; j++){
            Stado[i + 1][j] -= kupno*Wymiana[j];
            Stado[0][j] += kupno*Wymiana[j];
          }
        }
      }
      //rzut kostką, zmiana w stadzie wynikająca z rzutu
      kostka1 = 1 + losuj()%12;
      kostka2 = 1 + losuj()%12;
      stadoPoRzucie(Stado, i + 1, kostka1, kostka2);
      wyswietlWynikRzutu(Stado, i + 1, kostka1, kostka2);
      //TUTAJ ZAPIS DO PLIKU
      if(czyKoniecGry(Stado, i + 1)){
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
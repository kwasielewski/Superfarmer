//Mateusz Gieroba
#include <bits/stdc++.h>
//#include <unistd.h> //do uzyskania ziarna na etapie testowym hosta
using namespace std;
//Program ten będzie kompilowany wraz z głównym programem zawierającym interfejs w GTK. Wszelkie funkcje hosta będą
//wywoływane przez główny program do obsługi przebiegu rozgrywki

extern long long krolikowy(int *Stado[5], int id);
extern long long randomizowany(int *Stado[5], int id);
extern long long botQn(int *Stado[5], int id); //AKA usainbolt, highdollar
extern long long swinski(int *Stado[5], int id);
extern void slosuj();
extern int losowanko();
long long (*bots[4])(int*[5], int); //wskaźniki na boty

static void inicjujZapisDoPliku(ofstream &plik, int Usadzenie[4])
{
  plik << "LP,R1,S1,P1,C1,H1,d1,D1,R2,S2,P2,C2,H2,d2,D2,R3,S3,P3,C3,H3,d3,D3,R4,S4,P4,C4,H4,d4,D4,T1,T2,T3,T4\n0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,";
  for(int i = 0; i < 3; i++)
    plik << Usadzenie[i] << ',';
  plik << Usadzenie[3] << '\n';
}

static void zapiszRunde(ofstream &plik, int *Stado[5], int nrrundy)
{
  plik << nrrundy << ',';
  for(int i = 1; i < 5; i++)
    for(int j = 0; j < 7; j++)
      plik << Stado[i][j] << ',';
  plik << ",,,\n";
}

static void WypiszPlansze(int *Stado[5], int czlowiek)
{ //funkcja do testowania hosta
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 7; j++)
      cout << Stado[i][j] << ' ';
    if(i == czlowiek)
      cout << " <== TO TWOJE STADO";
    cout << '\n';
  }
}

long long dokonajWymiany(int *Stado[5], int id)
{//wywołanie ludzkiego gracza do podjęcia deyzji o wymianie (początek cyklu), funkcja do testowania hosta
  WypiszPlansze(Stado, id);
  long long output;
  reset:
  cout << "Czy chcesz podjąć wymianę 1-Tak/0-Nie\n";
  cin >>output;
  if(output==0){
  	return 0;
  }
  output = 1LL;
  int buy,  big,  rabbit,  sheep,  pig,  cow,  horse,  sDog, bDog;
  cout << "Podaj kod wymiany.\n";
  cout << "1-Kupno/0-Sprzedaż\n";
  output <<= 1LL;
  cin >> buy;
  cout << "Podaj numer zwierzęcia, którego dotyczy operacja\n0-Królik 1-Owca 2-Świnia 3-Krowa 4-Koń 5-Mały Pies 6-Duży Pies\n";
  
  cin >> big;
  if(big > 6 || big<0){
		cout << "Zły numer zwierzęcia\n";
		output = 1LL;
		goto reset;
		
	}
  cout << "Podaj 7 kolejnych liczb oznaczających liczbę zwierząt z każdego rodzaju na wymianę\n";
  cin >> rabbit >> sheep >> pig >> cow >> horse >> sDog >> bDog;
  //cout << "Czy chcesz dokonać "
	output += buy;
	
	output <<= 3LL;
	output += big;

	output <<= 6LL;
	output += rabbit;
	
	output <<= 5LL;
	output += sheep;

	output <<= 5LL;
	output += pig;

	output <<= 4LL;
	output += cow;

	output <<= 3LL;
	output += horse;

	output <<= 3LL;
	output += sDog;

	output <<= 2LL;
	output += bDog;
	if(rabbit > 60 || sheep > 24 || pig > 20 || cow > 12 || horse > 4 || sDog >4|| bDog>2){
		cout << "Liczba zwierząt przekroczyła liczbę żetonów w grze\n";
		output = 0;
		goto reset;
		
	}
  return output;
}

long long testowybot(int *Stado[5], int id)
{ //funkcja do testowania hosta
  return 0LL;
}
void Koniec_Gry(int zwyciezca, bool czyWygralCzlowiek){
  if(zwyciezca == -1)
    cout << "GRA ZAKOŃCZYŁA SIĘ W WYNIKU BŁĘDU!\n";
  if(zwyciezca == 0)
    cout << "DOSZŁO DO REMISU\n";
  if(czyWygralCzlowiek)
    cout << "WYGRAŁEŚ! GRATULACJE!\n";
  if(!czyWygralCzlowiek && zwyciezca > 0)
    cout << "PRZEGRAŁEŚ! WYGRAŁ GRACZ NUMER " << zwyciezca << '\n';
  return;
} //wywołanie komunikatu o zakończeniu gry w GTK, w obecnej postaci funkcja do testowania hosta
void wymianaZatwierdzona(int *Stado[5]) {return;} //wyświetlenie informacji o zaakceptowaniu wymiany oraz aktualizacja planszy
void wymianaOdrzucona(){
  cout << "Żądanie niepoprawne\n";
  return;} //wyświetlenie komunikatu o błędności żądania, freeze do czasu zamknięcia okienka
void wyswietlWynikRzutu(int *Stado[5], int id, int kostka1, int kostka2)
{ //funkcja w wersji do testowania hosta
  //kostka1: 1 - lis, 2/4/6/8/10/12 - królik, 3 - owca, 5 - świnia, 7 - koń, 9 - owca, 11 - świnia
  string jeden, dwa;
  if(kostka1 % 2 == 0)
    kostka1 = 2;
  if(kostka2 % 2 == 1)
    kostka2 = 1;  
  switch (kostka1)
  {
    case 1:
      jeden = "lisa";
      break;
    case 2:
      jeden = "królika";
      break;
    case 3:
      jeden = "owcę";
      break;
    case 5:
      jeden = "świnię";
      break;
    case 7:
      jeden = "konia";
      break;
    case 9:
      jeden = "owcę";
      break;
    case 11:
      jeden = "świnię";
      break;
    default:
      break;
  }
  //kostka2: 1/3/5/7/9/11 - królik, 2 - krowa, 4 - owca, 6 - świnia, 8 - owca, 10 - wilk, 12 - owca
  switch(kostka2)
  {
    case 1: 
      dwa = "królika";
      break;
    case 2:
      dwa = "krowę";
      break;
    case 4:
      dwa = "owcę";
      break;
    case 6:
      dwa = "świnię";
      break;
    case 8:
      dwa = "owcę";
      break;
    case 10:
      dwa = "wilka";
      break;
    case 12:
      dwa = "owcę";
      break;
    default:
      break;
  }
  cout << "Gracz numer " << id << " wyrzucił " << jeden << " i " << dwa << '\n';
  return;
} //wyświetlenie komunikatu o wyniku rzutu

// int losuj() //funkcja do zastąpienia funkcją z modułu losującego - do testowania hosta
// {
//   return rand();
// }

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
  cout << "WYMIANA: ";
  for(int i = 0; i <= 8; i++)
    cout << Wymiana[i] << ' ';
  cout << '\n';
  return;
}

static bool czyWymianaPoprawna(int *Stado[5], int id, int Wymiana[9])
//funkcja sprawdza poprawność żądań z tabelą wymian i dostosowuje liczby do możliwości stada głównego 
//tj. może pogorszyć liczby z żądania gracza, lecz ten miał pełną informację na temat zasobności stada głównego żądając wymiany (wiedział ile może dostać)
{
  int krolikojednostki[7] = {1, 6, 12, 36, 72, 6, 36}; //wartości zwierząt w przeliczeniu na króliki
  if(Wymiana[0] == 0)
  {
    if(Stado[id][Wymiana[1]] == 0)
      return false; //gracz nie posiada sprzedawanego zwierzęcia
    int otrzymywane = 0;
    for(int i = 2; i <= 8; i++)
      otrzymywane += Wymiana[i]*krolikojednostki[i - 2];
    if(otrzymywane > krolikojednostki[Wymiana[1]])
      return false; //zwierzęta żądane za sprzedawane są droższe niż sprzedawane (wg przeliczników)
    for(int i = 2; i <= 8; i++)
      Wymiana[i] = min(Wymiana[i], Stado[0][i - 2]); //zmiana żądania danego zwierzęcia jeżeli stado główne ma ich mniej niż żądanie (gracz wiedział w momencie decyzji ile jest ich w stadzie więc świadomie podjął te decyzje)
    return true;
  }
  else
  {
    if(Wymiana[1] == 0)
      return false; //duże zwierzę jest królikiem
    if(Stado[0][Wymiana[1]] == 0)
      return false; //stado główne nie posiada żądanego zwierzęcia
    for(int i = 2; i <= 8; i++)
      if(Wymiana[i] > Stado[id][i - 2])
        return false; //gracz nie posiada oferowanej liczby zwierząt
    int otrzymywane = 0;
    for(int i = 2; i <= 8; i++)
      otrzymywane += Wymiana[i]*krolikojednostki[i - 2];
    if(otrzymywane < krolikojednostki[Wymiana[1]])
      return false; //gracz żąda zwierzęcia oferując zwierzęta o zbyt małej wartości (względem królików wg tabeli przeliczników)
    return true;
  }
}

static bool stadoPoRzucie(int *Stado[5], int id, int kostka1, int kostka2)
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
  bool czy_zmiana = false; //czy następuje zmiana w stadzie
  //transfer zwierząt z głównego stada w wyniku rozmnażania (z zachowaniem możliwości zasobnych głównego stada)
  for(int i = 0; i < 5; i++){
    if(tab[i] > 0){
      int x = Stado[id][i], y = Stado[0][i];
      if(min((x + tab[i])/2, y) != 0)
        czy_zmiana = true;
      Stado[id][i] += min((x + tab[i])/2, y);
      Stado[0][i] -= min((x + tab[i])/2, y);
    }
  }
  return czy_zmiana;
}

static bool czyKoniecGry(int *Stado[5], int gracz)
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
    wykluczony = 2 + losowanko()%4;
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
        bots[i] = botQn;
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
  for(int i = 1; i <= 4; i++){
    Stado[i][0] = 1;
    for(int j = 1; j <= 6; j++)
      Stado[i][j] = 0;
  }
  return Stado;
}

void rozpocznijGre(bool czyCzlowiekGra, string nazwaPlikuDoZapisu)
{
  ofstream zapisDoPliku;
  zapisDoPliku.open(nazwaPlikuDoZapisu);
  slosuj();
  int *Usadzenie = usadzGraczy(czyCzlowiekGra);
  int **Stado = inicjujStada();
  int *Wymiana = new int[9];
  inicjujZapisDoPliku(zapisDoPliku, Usadzenie);
  int zwyciezca = -1, kostka1, kostka2, cnt = 0, nrrundy = 0, czlowiek = -1; 
  long long kodWymiany = 0;
  for(int i = 0; i < 4; i++)
    if(Usadzenie[i] == 1)
      czlowiek = i + 1;
  cout << "Jesteś graczem numer: " << czlowiek << '\n';
  while(zwyciezca == -1){
    bool czyzmiana = false;
    nrrundy++;
    for(int i = 0; i < 4; i++){
      kodWymiany = bots[i](Stado, i + 1);
      if(kodWymiany & (1LL << 32)){ //gracz żąda wymiany
        konwersjaKoduWymiany(Wymiana, kodWymiany);
        if(!czyWymianaPoprawna(Stado, i + 1, Wymiana)){
          if(Usadzenie[i] != 1){
            //Koniec_Gry(-1, false); //zakończenie rozgrywki z powodu błędu bota
            //return;
          }
          else{ //wyświetlenie błędu żądania wymiany złożonej przez gracza i ponowienie możliwości wymiany
            i--;
            wymianaOdrzucona();
            continue;
          }
        }
        else //wymiana poprawna, dokonanie zmian w stadach
        {
          czyzmiana = true;
          int kupno = (Wymiana[0] == 1)?1:-1;
          Stado[i + 1][Wymiana[1]] += kupno;
          Stado[0][Wymiana[1]] -= kupno;
          for(int j = 2; j <= 8; j++){
            Stado[i + 1][j - 2] -= kupno*Wymiana[j];
            Stado[0][j - 2] += kupno*Wymiana[j];
          }
          WypiszPlansze(Stado, czlowiek);
        }
      }
      //rzut kostką, zmiana w stadzie wynikająca z rzutu
      kostka1 = 1 + losowanko()%12;
      kostka2 = 1 + losowanko()%12;
      czyzmiana |= stadoPoRzucie(Stado, i + 1, kostka1, kostka2);
      wyswietlWynikRzutu(Stado, i + 1, kostka1, kostka2);
      if(czyKoniecGry(Stado, i + 1)){
        zwyciezca = i + 1;
        break;
      }
    }
    zapiszRunde(zapisDoPliku, Stado, nrrundy);
    if(!czyzmiana)
      cnt++;
    else
      cnt = 0;
    if(cnt > 6){ //liczba rund bez zmiany stanu --> remis
      zwyciezca = 0; //remis
      break;
    }
  }
  Koniec_Gry(zwyciezca, ((Usadzenie[zwyciezca - 1] == 1)?true:false));
  for(int i = 0; i < 5; i++) //czyszczenie pamięci ze sterty
    delete[] Stado[i];
  delete[] Stado;
  delete[] Usadzenie;
  delete[] Wymiana;
  zapisDoPliku.close();
}

int main(int argc, char *argv[]) //w wersji release nie będzie tej funkcji - służy testowaniu hosta
{
  //srand(getpid() + time(NULL));
  string s;
  if(argc < 2)
    s = "./Dane/dane1.csv";
  else{
    s = argv[1];  
    s ="./Dane/" + s +".csv";
  }
  rozpocznijGre(true, s);
}

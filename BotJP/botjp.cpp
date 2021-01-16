#include <iostream>
using namespace std;

long long int decisionMaker(int exchange, int buy, int big, int rabbit, int sheep, int pig, int cow, int horse, int sDog, int bDog, int s[5][7]);

long long int possible(long long int decision);


long long int botkrolik(int s[5][7], int id)
{
   long long int decision=0;
    const int bank=0;
    int state=0;
    int zapas=0;
    while((s[bank][0]+(zapas+1))*2<=s[id][0])  //sprawdzamy, ile królików możemy wydać na wymianę tak, by miec szanse potem odzyskać wszystkie króliki obecne w banku
        zapas++;






    for(int i=1;i<=4;i++)                //liczymy nadwyżkę zwierząt w "krolikojednostkach

    if(s[bank][0]*2>s[id][0])       //   skupiamy się na królikach
    {
        if(s[id][0]<=6)            // jeśli jesteśmy w początkowej fazie gry / stracilismy kroliki, chcemy je odzyskac sprzedajac inne zwierzeta
        {

        }

        else decisionMaker(0,0,0,0,0,0,0,0,0,0,s);    //zakończ turę i czekaj na rozmnozenie królików
    }
    else                     // jest wystarczająco dużo królików, staramy się zbudować kompletny zestaw zwierząt
    {

        ///   <<< sprawdzam czy mogę wygrać w jednym ruchu

        // nie mogę wygrać w jednym ruchu
        if(nadwyzka>=6)
        {
              if(s[id][2]==0 && zapas>=12)
              {
              // kup świnię
              decision=decisionMaker(1,1,2,12,0,0,0,0,0,0,s);
              }
              else {

               if(s[id][1]==0 && zapas>=6)
                {
                    //kup owcę
                    decision=decisionMaker(1,1,1,6,0,0,0,0,0,0,s);
                }

                else{

                    if(///mam dużo owiec i swin)
                    {
                    ///kup krowę
                    }
                    else {

                    ///dokup swinie i owce
                    }


                }


              }



        }
        else decision=decisionMaker=(0,0,0,0,0,0,0,0,0,0,s); //zakończ turę


        }

    return decision;
}



int main()
{
    int tab[5][7]= {{100, 100, 100, 100, 100, 100, 100}, {100, 100, 100, 100, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}};

    cout << bot(tab, 1);

    return 0;
}



long long int possible(long long int decision, int s[5][7])
{
    //jeśli pomijam to git

    int code[10];
    code[9]= decision%4;
    decision/=4;

    code[8]= decision%8;
    decision/=8;

    code[7]= decision%8;
    decision/=8;

    code[6]= decision%16;
    decision/=16;

    code[5]= decision%32;
    decision/=32;

    code[4]= decision%32;
    decision/=32;

    code[3]= decision%64;
    decision/=64;

    code[2]= decision%8;
    decision/=8;

    code[1]= decision%2;
    decision/=2;

    code[0]= decision;

    if(code[0] == 0)
    {
        return 0;
    }
    //jeśli się nie da kupić bo nie ma to wyzeruj
    if(code[1] == 1 && s[0][code[2]+1]==0)
    {
        return 0;
    }
    //jeśli się sprzedaje to wyzeruj
    if(code[1] == 0 )
    {
        for(int  i = 0; i < 7 ; i++)
        {
            if(code[3+i]>s[0][i])
            {
                return 0;
            }
        }
    }
    return decision;
}

long long int decisionMaker(int exchange, int buy, int big, int rabbit, int sheep, int pig, int cow, int horse, int sDog, int bDog, int s[5][7])
{
    long long int output = 0;

    output += exchange*2+buy;

    output *= 8;
    output = output+big;

    output *= 64;
    output += rabbit;

    output *= 32;
    output += sheep;

    output *= 32;
    output += pig;

    output *= 16;
    output += cow;

    output *= 8;
    output += horse;

    output *= 8;
    output += sDog;

    output *= 4;
    output += bDog;

    return possible(output,  s);
}

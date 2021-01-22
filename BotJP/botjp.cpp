#include <iostream>
using namespace std;

long long int decisionMaker(int exchange, int buy, int big, int rabbit, int sheep, int pig, int cow, int horse, int sDog, int bDog, int s[5][7]);

long long int possible(long long int decision);


long long int botkrolik(int s[5][7], int id)
{
    long long int decision=0;
    const int bank=0;
    int zapas=0;
    int portfel=0;
    bool closewin=1;
    while((s[bank][0]+(zapas+1))*2<=s[id][0])  //sprawdzamy, ile królików możemy wydać na wymianę tak, by miec szanse potem odzyskać wszystkie króliki obecne w banku
        zapas++;

    int mnożnik=1;
    for(int i=0; i<=3; i++) //liczymy nadwyżkę zwierząt w "krolikojednostkach"
    {
        if (s[id][i]==0)
        {
            closewin=0;
            break;
        }
        if(i==1)
            mnożnik=6;
        else if (i==2)
            mnoznik=12;
        else if (i==3)
            mnoznik=36;

        portfel+=(s[id][i]-1)*mnoznik;
    }



    if(s[bank][0]*2>s[id][0])       //   skupiamy się na królikach
    {
        if(s[id][0]<=6)            // jeśli jesteśmy w początkowej fazie gry / stracilismy kroliki, chcemy je odzyskac sprzedajac inne zwierzeta
        {
            // sprzedaj swinie
            if(s[id][2]>0)
                decision=decisionMaker(1,0,2,12,0,0,0,0,0,0,s);
            else if(s[id][1]>0)//sprzedaj owce
                decision=decisionMaker(1,0,1,12,0,0,0,0,0,0,s);
            else decision=decisionMaker(0,0,0,0,0,0,0,0,0,0,s);      //nic nie rób
        }

        else decision=decisionMaker(0,0,0,0,0,0,0,0,0,0,s);    //zakończ turę i czekaj na rozmnozenie królików
    }
    else                     // jest wystarczająco dużo królików, staramy się zbudować kompletny zestaw zwierząt
    {

        portfel+=s[id][5]*6+s[id][6]*36;
        if(closewin==1&&portfel>=72)    /////// moge wygrac w jednym ruchu czyli brakuje mi tylko konia
        {
            decision=decisionMaker(1,1,4,s[id][0]-1,s[id][1]-1,s[id][2]-1,s[id][3]-1,0,s[id][5],s[id][6],s);
        }

        // nie mogę wygrać w jednym ruchu
        else if(portfel>=6)
        {
            if(s[id][2]==0 && zapas>=12)
            {
                // kup świnię
                decision=decisionMaker(1,1,2,12,0,0,0,0,0,0,s);
            }
            else
            {

                if(s[id][1]==0 && zapas>=6)
                {
                    //kup owcę
                    decision=decisionMaker(1,1,1,6,0,0,0,0,0,0,s);
                }

                else
                {

                    if(s[id][1]==0||s[id][2]==0)
                        portfel=0;
                    else if(s[id][1]==1&&s[id][2]>1)
                        portfel=(s[id][2]-1)*2;
                    else if(s[id][1]>1&&s[id][2]==1)
                        portfel=s[id][1]-1
                                else portfel=(s[id][2]-1)*2+s[id][2]-1;



                    if(portfel>=6) //mam dużo owiec i swin (przeliczam na owce)
                    {
                          int swinia=0;
                          int owca=0;
                          while(s[id][2]>1&&(swinia+1)*2<=6)
                                świnia++;


                          if(świnia<3&&s[id][1]-1>=6-świnia*2)
                          while(świnia*2+owca<6)
                             owca++;

                          else
                          {
                          if(swinia<3)
                          świnia++;
                          while(świnia*2+owca<6)
                          owca++;
                          };


                          decisionMaker(1,1,3,0,owca,swinia,0,0,0,0,s);
                    }
                    else      //dokup swinie i owce
                    {



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
    /*cout << "Odzyskany kod ";
    for(int i = 0; i< 10; i ++){
    	cout << code[i] << " ";
    }
    cout << endl;*/
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
    cout << "Ex: " << exchange << " Buy: " << buy << " Big: " << big << " Num: " << rabbit << " " << sheep << " " << pig << " " << cow << " "  <<  horse << " " << sDog << " " << bDog <<endl;
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

    return possible(output,  s) ? output : 0;
}


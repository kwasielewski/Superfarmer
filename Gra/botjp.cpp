#include <iostream>
#include "functions.h"
using namespace std;




long long int krolikowy(int* s[5], int id)
{
    int swinia,owca;
    long long int decision=0;
    const int bank=0;
    int zapas=0;
    int portfel=0;
    bool closewin=1;
    while((s[bank][0]+(zapas+1))*2<=s[id][0])  //sprawdzamy, ile królików możemy wydać na wymianę tak, by miec szanse potem odzyskać wszystkie króliki obecne w banku
        zapas++;

    int mnoznik=1;
    for(int i=0; i<=3; i++) //liczymy nadwyżkę zwierząt w "krolikojednostkach"
    {
        if (s[id][i]==0)
        {
            closewin=0;
            break;
        }
        if(i==1)
            mnoznik=6;
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
                        portfel=s[id][1]-1;
                                else portfel=(s[id][2]-1)*2+s[id][2]-1;



                    if(portfel>=6) //mam dużo owiec i swin (przeliczam na owce)
                    {
                        swinia=0;
                        owca=0;
                        while(s[id][2]>1&&(swinia+1)*2<=6)
                            swinia++;


                        if(swinia<3&&s[id][1]-1>=6-swinia*2)
                            while(swinia*2+owca<6)
                                owca++;

                        else
                        {
                            if(swinia<3)
                                swinia++;
                            while(swinia*2+owca<6)
                                owca++;
                        }


                        decision=decisionMaker(1,1,3,0,owca,swinia,0,0,0,0,s);
                    }
                    else      //dokup swinie i owce
                    {
                        swinia=0;
                        owca=0;
                        if(s[id][2]==0)
                        {
                            if(zapas>=12)
                                decision=decisionMaker(1,1,2,12,0,0,0,0,0,0,s);
                            else if (zapas>=6&&s[id][1]==0)
                            decision=decisionMaker(1,1,1,12,0,0,0,0,0,0,s);
                            else decision=decisionMaker(0,0,0,0,0,0,0,0,0,0,s);
                        }
                        else if (s[id][1]==0)
                        {
                          if(zapas>=6)
                          decision=decisionMaker(1,1,1,6,0,0,0,0,0,0,s);
                          else decision=decisionMaker(0,0,0,0,0,0,0,0,0,0,s);

                        }
                        else{
                        if(zapas>=12) decision=decisionMaker(1,1,2,12,0,0,0,0,0,0,s);
                        else if(zapas>=6) decision=decisionMaker(1,1,1,6,0,0,0,0,0,0,s);
                        else decision=decisionMaker(0,0,0,0,0,0,0,0,0,0,s);

                        }



                    }

                }


            }



        }
        else decision=decisionMaker(0,0,0,0,0,0,0,0,0,0,s); //zakończ turę


    }

    return decision;
}



/*int main()
{
    int tab[5][7]= {{100, 100, 100, 100, 100, 100, 100}, {100, 100, 100, 100, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}};

    cout << krolikowy(tab, 1);

    return 0;
}*/





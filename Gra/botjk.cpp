#include <iostream>
#include "functions.h"
using namespace std;

//Autor:Jakub Kopystiański
//Bot Qń
// 0 - krol 1- owc 2-swin 3-cow 4-horse 5-sdog 6-bdog


/*
exchange 1 - wymieniam 0 -nie
buy 1 - male za duze 0 - na odwrot
*/

long long int botQn(int* s[5], int id)
{
    long long int decision=0;
    const int bank=0;
    if(s[id][4] > 1) decision = decisionMaker(1,0,4,6,3,1,1,0,0,0,s); // Mam 2 konie lub wiecej - wygrana!
    else if(s[id][3] > 1) decision = decisionMaker(1,1,4,0,0,0,2,0,0,0,s); // chce konia, mam 2 krowy
    else if(s[id][2] > 2 && s[id][3] == 1) decision = decisionMaker(1,1,4,0,0,3,1,0,0,0,s); // chce konia, mam 3 świnie i krowe
    else if(s[id][2] > 2) decision = decisionMaker(1,1,3,0,0,3,0,0,0,0,s); // mam 3 świnie chce krowe
    else if( (s[id][2] == 2 && s[id][1]>1) && s[id][3] == 1) decision = decisionMaker(1,1,4,0,2,2,1,0,0,0,s); // chce konia za 2 owce 2 świnie i krowe
    else if( (s[id][0] > 5 && s[id][1] >= 1) && (s[id][2] >= 2 && s[id][3] >= 1) ) decision = decisionMaker(1,1,4,6,1,2,1,0,0,0,s); // kon za 6 kro 1 owc 2 sw 1 kr
    else if(s[id][2]>=2 && s[id][1]>=2) decision = decisionMaker(1,1,3,0,2,2,0,0,0,0,s); //kr za 2 owc i 2 swinie
    else if(s[id][1]>=4 && s[id][2]>=1) decision = decisionMaker(1,1,3,0,4,1,0,0,0,0,s); // kr za 4 owc i 1 swinie
    else if(s[id][0]>5 && (s[id][1]>=1 && s[id][2] >= 2) ) decision = decisionMaker(1,1,3,6,1,2,0,0,0,0,s); //kr za 6k 1ow 2sw
    else if(s[id][0]>5 && (s[id][1]>=3 && s[id][2] >= 1) ) decision = decisionMaker(1,1,3,6,3,1,0,0,0,0,s); //kr za 6k 3ow 1sw
    else if(s[id][0]>11 && s[id][2] >= 2) decision = decisionMaker(1,1,3,12,0,2,0,0,0,0,s); // kr za 12 krol i 2 swinie
    else if(s[id][0]>17 && (s[id][1]>=1 && s[id][2] >= 1) ) decision = decisionMaker(1,1,3,18,1,1,0,0,0,0,s);//kr za 18 kl 1 owc i 1 swinie
    else if(s[id][1]>=2 ) decision = decisionMaker(1,1,2,0,2,0,0,0,0,0,s);
    else if(s[id][0]>5 && s[id][1]>=1 ) decision = decisionMaker(1,1,2,6,1,0,0,0,0,0,s);
    else if(s[id][0]>=12 ) decision = decisionMaker(1,1,2,12,0,0,0,0,0,0,s);
    else if(s[id][0]>=6 ) decision = decisionMaker(1,1,1,6,0,0,0,0,0,0,s);
    else if(s[id][1]>0)decision = decisionMaker(1,1,5,0,1,0,0,0,0,0,s);
    else if(s[id][3]>0)decision = decisionMaker(1,1,5,0,0,0,1,0,0,0,s);
    else if(s[id][2]>2)decision = decisionMaker(1,1,5,0,0,3,0,0,0,0,s);
    else decision = decisionMaker(0,0,0,0,0,0,0,0,0,0,s);
    return decision;
}



/*int main()
{
    int tab[5][7]= {{100, 100, 100, 100, 100, 100, 100}, {100, 100, 100, 100, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}};

    //cout << bot(tab, 1);

    return 0;
}*/




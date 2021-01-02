#include <iostream>
#include "conversion.h"
using namespace std;



int bot(int s[5][7], int id){
    int decision=0;
    int binDecision[21];
    int state = 0;
    bool presence[7];

    for(int i = 0; i < 7; i++){
        if(s[id][i]>0){
            presence[i] = 1;
        }else{
            presence[i] = 0;
        }
    }
    //określenie stadium gry early, mid, midlate, late



    //co robić w danym stadium
    if(state == 0){
        if(s[id][0]>6){
            decision = strToDec("11000000110000000000000");
        }
    }


    return decision;
}


int main(){
    int tab[5][7];
    bot(tab, 0);

    return 0;
}

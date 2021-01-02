#include <iostream>
#include "conversion.h"
using namespace std;



int bot(int s[5][7], int id){
    int decision=0;
    int binDecision[21];
    int state = -1;
    int presence = 0;
    for(int i = 4; i > -1; i--){
        presence *=2;
        if(s[id][i]>0){
            presence++;             // RSPCHdD
        }
    }
    //określenie stadium gry
    if(presence <2){
        state = 0;
    }


    //co robić w danym stadium
    if(state < -1){
        cout << "Nieokreślono stanu gry\n";
    }
    if(state == 0){
        if(s[id][0]>6){
            decision = strToDec("11000000110000000000000");
        }else{
            decision = 0;
        }
        return decision;
    }


    return decision;
}


int main(){
    int tab[5][7];
    bot(tab, 0);

    return 0;
}

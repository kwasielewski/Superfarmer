#include <iostream>
#include "conversion.h"
using namespace std;
int strToDec(string x){
    int y = 0;
    for(int i = 0;  i< x.size(); i++){
        y*=2;
        if(x[i]=='1'){
            y++;
        }
    }
    return y;

}


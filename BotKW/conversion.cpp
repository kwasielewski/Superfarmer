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
int decisionMaker(int exchange, int buy, int big, int rabbit, int sheep, int pig, int cow, int horse){
	int output = 0;
	
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
	
	return output;
}

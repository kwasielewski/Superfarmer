#include <iostream>
#include "conversion.h"
using namespace std;



int bot(int s[5][7], int id){
	int bankID = 0;
    int decision=0;
    int value[] ={1, 6, 12, 36, 72}; 
    //int binDecision[23];
    int state = -1;
    int presence = 0;
    int notPresent=0;
    int notPresentID= -1;
    for(int i = 4; i > -1; i--){
        presence *=2;
        if(s[id][i]>0){
        	presence++;             // RSPCHdD
        }else{
      		notPresent++;
      		notPresentID = i; 
        }
    }
    //określenie stadium gry
    
    /*
    0 - mam nie więcej niż króliki
    1 - mam owcę
    2 - mam świnię (ile?, mało/dokupić owcę/kupić psa/kupić/krowę)
    3 - mam krowę (czy mogę wygrać? czy mam poprzednie? czy mam króliki? czy chcę psa?)
    10 - da się wygrać w 1 ruchu
    */
    
    if(notPresent == 1){
    	int extra = 0;
    	for(int i = 0; i < 5; i ++){
    		extra = max(s[id][i]-1, 0)*value[i];
    	}
    	if(extra >= value[notPresentID]&& s[bankID][notPresentID]>0){
    		state = 10;
    	}
    
    }else if(presence&8==1){
    	state = 3;
    }else if(presence&4==1){
    	state = 2;
    }else if(presence&2 == 1){
    	state = 1;
    }else if(presence <2){
        state = 0;
    }
   
    


    //co robić w danym stadium
    if(state < -1){
        cout << "Nieokreślono stanu gry\n";
    }
    switch(state){
    	case 0:{
    		if(s[id][0]>6){
		    //decision = strToDec("11000000110000000000000");
		    decision = decisionMaker(1, 1, 0, 6, 0, 0, 0, 0);
		}else{
		    decision = 0;
		}
		break;
		}
	case 1:{
		
		if(s[bankID][0]< 20){
			if(s[id][1]>1){
				decision = decisionMaker(1, 1, 1, 0, 2, 0, 0, 0);
			}
		}else {
			if(s[id][0]>12){
				//kup świnię za króliki
				decision = decisionMaker(1, 1, 1, 12, 0, 0, 0, 0);
			}else if(s[id][0]>6 and s[id][1]> 1){
				decision  = decisionMaker(1, 1, 1, 6, 1, 0, 0, 0);
			}else if(s[id][1]>1){
				decision = decisionMaker(1, 1, 1, 0, 2, 0, 0, 0);
			}
		}
		break;
		}
	case 10:{
		int currentValue = 0;
		int buy[] = {0, 0 , 0, 0, 0};
		int x = notPresentID;
		while(x>-1 && currentValue < value[notPresent]){
			if(s[id][x]> 1){
				buy[x] = s[id][x]-1;
				currentValue += value[x];
			}else{
				x--;
			}
		}
		if(currentValue< value[notPresent]){
			for(int i = 0; i < 5; i++){
				buy[i] = 0;
			}
			buy[notPresentID] = 1;
		}else{
			decision = decisionMaker(1, 1, notPresentID-1,buy[0], buy[1], buy[2], buy[3], buy[4]);
			break;
		}
		x = notPresent ++;
		while(x < 5){
			if(s[id][x] > 1){
				decision = decisionMaker(1, 0, x, buy[0], buy[1], buy[2], buy[3], buy[4]);
			}
		}
		
		break;
		}
	case 2:{
		//mam świnię 
		
		//mało/dokupić owcę/kupić psa/kupić/krowę
		
		
		
	}
	default:{
		break;
    	}
    }
    	


    return decision;
}


int main(){
    int tab[5][7];
    bot(tab, 1);

    return 0;
}

#include <iostream>
using namespace std;

long long int decisionMaker(int exchange, int buy, int big, int rabbit, int sheep, int pig, int cow, int horse, int sDog, int bDog);

long long int possible(long long int decision);


long long int bot(int s[5][7], int id){
	int debug = 1;
	int bankID = 0;
    long long int decision=0;
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
    4 - mam braki w łańcuchu
    10 - da się wygrać w 1 ruchu
    */
    if(debug) cout << "Nie ma " << notPresent << " ID:" << notPresentID << endl;
    if(notPresent == 1){
    	int extra = 0;
    	for(int i = 0; i < 5; i ++){
    		extra += max(s[id][i]-1, 0)*value[i];
    	}
    	if(debug) cout << extra << endl;
    	if(extra >= value[notPresentID]&& s[bankID][notPresentID]>0){
    		state = 10;
    	}

    }else if(presence&8==8){

    	state = 3;
    }else if(presence&4==4){
    	state = 2;
    }else if(presence&2 == 2){
    	state = 1;
    }else if(presence <2){
        state = 0;
    }

    for(int i  = 1 ; i < 5;  i++){
        if(s[id][i-1]==0&&s[id][i]!=0){
            state = 4;
        }
    }


    if(debug) cout << (presence&8) << endl;
    if(debug) cout << (presence&4) << endl;
    if(debug) cout << (presence&2) << endl;


	if(debug)cout << presence << " " <<state <<"/";
    //co robić w danym stadium
    if(state < -1){
        cout << "Nieokreślono stanu gry\n";
    }
    switch(state){
        case 0:{
    		if(s[id][0]>6){
		    //decision = strToDec("11000000110000000000000");
		    decision = decisionMaker(1, 1, 0, 6, 0, 0, 0, 0, 0, 0);
		}else{
		    decision = 0;
		}
		break;
		}

        case 1:{

            if(s[bankID][0]< 20){
                if(s[id][1]>1){
                    decision = decisionMaker(1, 1, 1, 0, 2, 0, 0, 0, 0, 0);
                }
            }else {
                if(s[id][0]>12){
                    //kup świnię za króliki
                    decision = decisionMaker(1, 1, 1, 12, 0, 0, 0, 0, 0, 0);
                }else if(s[id][0]>6 and s[id][1]> 1){
                    decision  = decisionMaker(1, 1, 1, 6, 1, 0, 0, 0, 0, 0);
                }else if(s[id][1]>1){
                    decision = decisionMaker(1, 1, 1, 0, 2, 0, 0, 0, 0, 0);
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
                decision = decisionMaker(1, 1, notPresentID-1,buy[0], buy[1], buy[2], buy[3], buy[4], 0, 0);
                break;
            }
            x = notPresent ++;
            while(x < 5){
                if(s[id][x] > 1){
                    decision = decisionMaker(1, 0, x, buy[0], buy[1], buy[2], buy[3], buy[4], 0, 0);
                }
            }

            break;
            }

        case 2:{
            //mam świnię

            //mało/dokupić świnię/kupić psa/kupić/krowę

            //psa nie kupuję -przypadek pominięty

            //kupowanie krowy
            if((s[id][2]>1 && s[id][1] > 4)){
                decision = decisionMaker(1, 1, 3, 0, 4, 1, 0 ,0 ,0, 0);
            }else if(s[id][2] > 2 ){
                decision = decisionMaker(1, 1, 3 ,0 ,0, 3, 0, 0, 0, 0);
            }   else{
                //dokupienie świni
                if(s[id][0]>12){
                    //kup świnię za króliki
                    decision = decisionMaker(1, 1, 1, 12, 0, 0, 0, 0, 0, 0);
                }else if(s[id][0]>6 and s[id][1]> 1){
                    decision  = decisionMaker(1, 1, 1, 6, 1, 0, 0, 0, 0, 0);
                }else if(s[id][1]>1){
                    decision = decisionMaker(1, 1, 1, 0, 2, 0, 0, 0, 0, 0);
                }

            }

        }
        case 3: {
            //mam już krowę - zachowanie praktycznie takie jak w case 2
            if(s[id][0]>12){
                    //kup świnię za króliki
                    decision = decisionMaker(1, 1, 1, 12, 0, 0, 0, 0, 0, 0);
                }else if(s[id][0]>6 and s[id][1]> 1){
                    decision  = decisionMaker(1, 1, 1, 6, 1, 0, 0, 0, 0, 0);
                }else if(s[id][1]>1){
                    decision = decisionMaker(1, 1, 1, 0, 2, 0, 0, 0, 0, 0);
            }
        }
        case 4:{
            //być może uzupełnij niewygrywające braki
        }
        default:{
            break;
            }
        }



    return decision;
}



int main(){
    int tab[5][7]={{100, 100, 100, 100, 100, 100, 100}, {100, 100, 100, 100, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}};

    cout << bot(tab, 1);

    return 0;
}
long long int possible(long long int decision){
    return decision;
}

long long int decisionMaker(int exchange, int buy, int big, int rabbit, int sheep, int pig, int cow, int horse, int sDog, int bDog){
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

	output *= 3;
	output += sDog;

	output *= 2;
	output += bDog;

	return possible(output);
}

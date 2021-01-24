#include <iostream>
#include "functions.h"
using namespace std;




long long int swinski(int* s[5], int id){

	int debug = 0;
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

    }else if((presence&8)==8){
		//cout << "wynik " << (presence&8) << endl; 
    	state = 3;
    }else if((presence&4)==4){
    	state = 2;
    }else if((presence&2) == 2){
    	state = 1;
    }else {
        state = 0;
    }
	
    


    if(debug) cout << (presence&8) << endl;
    if(debug) cout << (presence&4) << endl;
    if(debug) cout << (presence&2) << endl;


	//cout << "Obecne "<<presence << " Stan " <<state <<"\n";
	//cout << "Stan " << state << endl;
    //co robić w danym stadium
    if(state < -1){
        cout << "Nieokreślono stanu gry\n";
    }
    
    switch(state){
        case 0:{
    		if(s[id][0]>6){
		    //decision = strToDec("11000000110000000000000");
		    //cout << "Powinienem tu być\n";
		    decision = decisionMaker(1, 1, 1, 6, 0, 0, 0, 0, 0, 0, s);
			}else{

				decision = 0;
			}
			break;
		}

        case 1:{

            if(s[bankID][0]< 20){
                if(s[id][1]>1){
                    decision = decisionMaker(1, 1, 2, 0, 2, 0, 0, 0, 0, 0,s);
                }
            }else {
                if(s[id][0]>12){
                    //kup świnię za króliki
                    decision = decisionMaker(1, 1, 2, 12, 0, 0, 0, 0, 0, 0, s);
                }else if(s[id][0]>6 and s[id][1]> 1){

                    decision  = decisionMaker(1, 1, 2, 6, 1, 0, 0, 0, 0, 0, s);
                }else if(s[id][1]>1){
                    decision = decisionMaker(1, 1, 2, 0, 2, 0, 0, 0, 0, 0, s);
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
                    currentValue += buy[x]*value[x];
                }
                    x--;
                
            }
          
            if(currentValue< value[notPresent]){
                for(int i = 0; i < 5; i++){
                    buy[i] = 0;
                }
                buy[notPresentID] = 1;
            }else{
                decision = decisionMaker(1, 1, notPresentID,buy[0], buy[1], buy[2], buy[3], buy[4], 0, 0 , s);
                break;
            }
            x = notPresent ++;
            while(x < 5){
                if(s[id][x] > 1){
                    decision = decisionMaker(1, 0, x+1, buy[0], buy[1], buy[2], buy[3], buy[4], 0, 0, s);
                	break;
                }else{
                	x++;
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
                decision = decisionMaker(1, 1, 3, 0, 4, 1, 0 ,0 ,0, 0, s);
            }else if(s[id][2] > 2 ){
                decision = decisionMaker(1, 1, 3 ,0 ,0, 3, 0, 0, 0, 0, s);
            }   else{
                //dokupienie świni
                if(s[id][0]>12){
                    //kup świnię za króliki
                    decision = decisionMaker(1, 1, 2, 12, 0, 0, 0, 0, 0, 0, s);
                }else if(s[id][0]>6 and s[id][1]> 1){
                    decision  = decisionMaker(1, 1, 2, 6, 1, 0, 0, 0, 0, 0, s);
                }else if(s[id][1]>1){
                    decision = decisionMaker(1, 1, 2, 0, 2, 0, 0, 0, 0, 0, s);
                }

            }

        }
        case 3: {
            //mam już krowę - zachowanie praktycznie takie jak w case 2
            if(s[id][0]>12){
                    //kup świnię za króliki
                    decision = decisionMaker(1, 1, 2, 12, 0, 0, 0, 0, 0, 0, s);
                }else if(s[id][0]>6 and s[id][1]> 1){
                    decision  = decisionMaker(1, 1,2, 6, 1, 0, 0, 0, 0, 0, s);
                }else if(s[id][1]>1){
                    decision = decisionMaker(1, 1, 2, 0, 2, 0, 0, 0, 0, 0, s);
            }
        }
        
        default:{
            break;
            }
        }



    return decision;
}



/*int main(){
    int **Stado = new int*[5];
  for(int i = 0; i <= 4; i++)
		Stado[i] = new int[7];//0 - króliki, 1 - owce, 2 - świnie, 3 - krowy, 4 - konie, 5 - małe psy, 6 - duże psy
	  Stado[0][0] = 60; Stado[0][1] = 24; Stado[0][2] = 20; Stado[0][3] = 12; Stado[0][4] = 6; Stado[0][5] = 4; Stado[0][6] = 2;
	  for(int i = 1; i <= 3; i++){
		Stado[i][0] = 7;
		for(int j = 1; j <= 6; j++)
		  Stado[i][j] = 0;
  }	
    int tab[5][7]={{100, 100, 100, 100, 100, 100, 100}, {1, 1, 1, 5, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}};

    cout <<"Jeden "<< bot(tab, 1) << endl;
	for(int i  = 0;  i <7; i++){
		tab[1][i] = 0;
	}
	tab[1][0]= 7;
	cout <<"Dwa " << bot(tab, 1)<<endl;
	tab[1][0] = 15;
	cout <<"Trzy "<< bot(tab,1) <<endl;
	
    
    cout << swinski(Stado, 1);
    return 0;
}*/









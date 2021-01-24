#include <iostream>
#include "functions.h"
using namespace std;


extern int losowanko();

long long int randomizowany(int* s[5], int id){
	
	int mozliwe[10];
	for(int  i = 0;  i <10; i++){
		mozliwe[i] = 0;
	}
	
	long long decision = 0;
	
	int pomin = 2;
	int kup = 0;
	int sprz = 0;
	int value[] ={1, 6, 12, 36, 72};
	int extra  = max(s[id][0]-1, 0) ;
	
	for(int  i = 0;  i <4;i++){
		if(value[i] <= extra){
   			mozliwe[i+2]=1;
   			kup++;
   		}
   		extra+=max(s[id][1+i]-1, 0);
	}
	for(int i = 0; i<4; i++){
		if(s[id][i+1]>1){
			sprz++;
			mozliwe[i+6]=1;
		}
	}
  
    int wynik = losowanko()%(pomin+kup+sprz);
    int poz = 0;
    while(wynik >0){
    	poz++;
    	poz=poz%(pomin+kup+sprz);
    	if(mozliwe[poz]!=0){
    		wynik--;
    		
    	}
    }
    //cout << poz;
    if(poz<2){
    	return 0;
    }else if(poz <6){
    	//kup 

    		int currentValue = 0;
            int buy[] = {0, 0 , 0, 0, 0};
            int x = poz-2;
			int IHave[5];
			for(int  i = 0;  i< 5; i++){
				IHave[i]=s[id][i];
			}
			while(x>-1&&currentValue < value[poz-1]){
				if(IHave[x]>1){
					currentValue+=value[x];
					buy[x]++;
					IHave[x]--;
				}else{
					x--;
				}
			}
            decision = decisionMaker(1, 1, poz-2, buy[0], buy[1], buy[2], buy[3], 0, 0, 0, s);
    }else{
    	//sprzedaj
    	int toSell[]= {0,0,0,0};
    	toSell[poz-6]=1;
    	decision = decisionMaker(1, 0, poz-6, 6*toSell[0],2*toSell[1],3*toSell[2],2*toSell[3] , 0, 0 ,0, s );
    }
    return decision;
}









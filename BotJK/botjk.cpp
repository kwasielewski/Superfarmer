#include <iostream>
using namespace std;

//Autor:Jakub Kopystiański
//Bot Qń
// 0 - krol 1- owc 2-swin 3-cow 4-horse 5-sdog 6-bdog

long long int decisionMaker(int exchange, int buy, int big, int rabbit, int sheep, int pig, int cow, int horse, int sDog, int bDog, int s[5][7]);
/*
exchange 1 - wymieniam 0 -nie
buy 1 - male za duze 0 - na odwrot
*/
long long int possible(long long int decision);
long long int botQn(int s[5][7], int id)
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



int main()
{
    int tab[5][7]= {{100, 100, 100, 100, 100, 100, 100}, {100, 100, 100, 100, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}};

    //cout << bot(tab, 1);

    return 0;
}


long long int possible(long long int decision, int s[5][7]){
    //jeśli pomijam to git

    int code[10];
    code[9]= decision%4;
    decision/=4;

    code[8]= decision%8;
    decision/=8;

    code[7]= decision%8;
    decision/=8;

    code[6]= decision%16;
    decision/=16;

    code[5]= decision%32;
    decision/=32;

    code[4]= decision%32;
    decision/=32;

    code[3]= decision%64;
    decision/=64;

    code[2]= decision%8;
    decision/=8;

    code[1]= decision%2;
    decision/=2;

    code[0]= decision;
    /*cout << "Odzyskany kod ";
	for(int i = 0; i< 10; i ++){
		cout << code[i] << " ";
	}
	cout << endl;*/
    if(code[0] == 0){
        return 0;
    }
    //jeśli się nie da kupić bo nie ma to wyzeruj
    if(code[1] == 1 && s[0][code[2]+1]==0){
        return 0;
    }
    //jeśli się sprzedaje to wyzeruj
    if(code[1] == 0 ){
        for(int  i = 0; i < 7 ;i++){
            if(code[3+i]>s[0][i]){
                return 0;
            }
        }
    }
    return decision;
}

long long int decisionMaker(int exchange, int buy, int big, int rabbit, int sheep, int pig, int cow, int horse, int sDog, int bDog, int s[5][7]){
	cout << "Ex: " << exchange << " Buy: " << buy << " Big: " << big << " Num: " << rabbit << " " << sheep << " " << pig << " " << cow << " "  <<  horse << " " << sDog << " " << bDog <<endl;
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

	output *= 8;
	output += sDog;

	output *= 4;
	output += bDog;

	return possible(output,  s) ? output : 0;
}

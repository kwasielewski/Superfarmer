import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import math

plotActive = False


def won(i):
    #R S P C H
    R = 'R' + str(i);
    S = 'S' + str(i);
    P = 'P' + str(i);
    C = 'C' + str(i);
    H = 'H' + str(i);
    if(df.iloc[-1][R]>=1 and df.iloc[-1][S]>=1 and df.iloc[-1][P]>=1 and df.iloc[-1][C]>=1 and df.iloc[-1][H]>=1):
        return True
    else:
        return False

def winnerGraph():
    if plotActive == False:
        return
    ax = plt.gca()
    df.plot(kind='line', x='LP', y=WR, color='orange', ax=ax)
    df.plot(kind='line', x='LP', y=WS, color='blue', ax=ax)
    df.plot(kind='line', x='LP', y=WP, color='pink', ax=ax)
    df.plot(kind='line', x='LP', y=WC, color='black', ax=ax)
    df.plot(kind='line', x='LP', y=WH, color='brown', ax=ax)

    plt.show()

def avrGraph():
    if plotActive==False:
        return
    for i in range(typesCount):
        ax = plt.gca()
        
        avrDF.plot(kind='line',  y=5*i+0, color='orange', ax=ax)
        avrDF.plot(kind='line',  y=5*i+1, color='blue', ax=ax)
        avrDF.plot(kind='line',  y=5*i+2, color='pink', ax=ax)
        avrDF.plot(kind='line',  y=5*i+3, color='black', ax=ax)
        avrDF.plot(kind='line',  y=5*i+4, color='brown', ax=ax)
        plt.show()

def avrWinGraph():
    if plotActive==False:
        return
    for i in range(typesCount):
        ax = plt.gca()
        
        avrWinDF.plot(kind='line',  y=5*i+0, color='orange', ax=ax)
        avrWinDF.plot(kind='line',  y=5*i+1, color='blue', ax=ax)
        avrWinDF.plot(kind='line',  y=5*i+2, color='pink', ax=ax)
        avrWinDF.plot(kind='line',  y=5*i+3, color='black', ax=ax)
        avrWinDF.plot(kind='line',  y=5*i+4, color='brown', ax=ax)
        plt.show()

def plotGameLength():
    #if plotActive==False:
    #    return
    plt.plot(gameLength)
    plt.ylabel('Liczba gier')
    plt.xlabel('Liczba tur')
    plt.show()
    


config = pd.read_csv(r'./config.csv')

typesCount = config.iloc[0]['Types']
numOfGames = config.iloc[0]['N']

maxLenOfGame = 0
minLenOfGame = math.inf
columnNames =np.array(['R','S','P','C', 'H'])

wins = np.zeros(typesCount)
avrTimeToWin = np.zeros(typesCount)

#print(config.iloc[0]['Types'])
#print(wins)

noWinner = 0


for n in range(numOfGames):
    #print(n)
    path = './Dane/dane'+str(n+1)+'.csv'
    df = pd.read_csv(path)
    #print(df)


    #print(df[-1:])

    #print(df.iloc[-1]['H1'])

    #wybór wygranego

    w_id = 0;
    maxLenOfGame = max(maxLenOfGame, df.iloc[-1]['LP'])
    minLenOfGame= min(minLenOfGame, df.iloc[-1]['LP'])
    for num in range(4):
        if won(num+1):
            w_id = num+1
            T  = 'T' + str(num+1)
            wins[int(df.iloc[0][T])]+=1
            avrTimeToWin[int(df.iloc[0][T])]+=df.iloc[-1]['LP']
            break

    if w_id == 0:
        noWinner += 1
        print("Rozgrywka bez zwycięzcy")

    winnerGraph()
    
print("Rozgrywek bez zwycięzcy łącznie: "noWinner)


for n in range(typesCount):
    if wins[n]==0:
        avrTimeToWin[n]=math.inf
    else:
        avrTimeToWin[n]=avrTimeToWin[n]/wins[n]

print("Max game lenght: ", maxLenOfGame)
print(wins)
print(avrTimeToWin)

avrDF = pd.DataFrame(0.0, index=range(int(minLenOfGame)), columns=range(5*typesCount))

for game in range(numOfGames):
    path = './Dane/dane'+str(game+1)+'.csv'
    df = pd.read_csv(path)
    for n in range(int(minLenOfGame)):#int(df.iloc[-1]['LP'])):
        #avrDF[0][n] = n+1
        for m in range(20):
            botType = 'T' + str(int(m/5)+1)
            op = columnNames[m%5]+ str(int(df.iloc[0][botType])+1)
            #print(df.iloc[n][op])
            avrDF[m][n]+=df.iloc[n][op]

for n in range(1, int(minLenOfGame)):
    for m in range(20):
        avrDF[m][n]=float(avrDF[m][n]/numOfGames)



#wypisanie średniego przebiegu rozgrywki

print(avrDF)
avrGraph()

avrWinDF = pd.DataFrame(0.0, index = range(int(minLenOfGame)), columns=range(5*typesCount))

for game in range(numOfGames):
    #print(n)
    path = './Dane/dane'+str(game+1)+'.csv'
    df = pd.read_csv(path)

    for num in range(4):
        if won(num+1):
            for n in range(int(minLenOfGame)):#int(df.iloc[-1]['LP'])):
                #avrDF[0][n] = n+1
                for m in range(20):
                    botType = 'T' + str(int(m/5)+1)
                    op = columnNames[m%5]+ str(int(df.iloc[0][botType])+1)
                    #print(df.iloc[n][op])
                    avrWinDF[m][n]+=df.iloc[n][op]
            break
        

for n in range(1, int(minLenOfGame)):
    for m in range(20):
        if(wins[int(m/5)]==0):
            avrWinDF[m][n]=0
        else:
            avrWinDF[m][n]=float(avrWinDF[m][n]/wins[int(m/5)])

print(avrWinDF)
avrWinGraph()

#maxGameLength

gameLength = np.zeros(int(maxLenOfGame)+1)
for game in range(numOfGames):
    path = './Dane/dane'+str(game+1)+'.csv'
    df = pd.read_csv(path)
    gameLength[int(df.iloc[-1]['LP'])] += 1

print(gameLength)
plotGameLength()
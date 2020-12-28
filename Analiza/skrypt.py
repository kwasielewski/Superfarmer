import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

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
    

config = pd.read_csv(r'./config.csv')

wins = np.zeros(config.iloc[0]['Types'])
#print(config.iloc[0]['Types'])
#print(wins)

for n in range(config.iloc[0]['N']):
    #print(n)
    path = './dane'+str(n+1)+'.csv'
    df = pd.read_csv(path)
    #print(df)


    #print(df[-1:])

    #print(df.iloc[-1]['H1'])

    #wybór wygranego

    w_id = 0;

    for num in range(4):
        if won(num+1):
            w_id = num+1
            T  = 'T' + str(num+1)
            wins[int(df.iloc[0][T])]+=1
            break

    if w_id == 0:
        print("Rozgrywka bez zwycięzcy")

    WR = 'R' + str(w_id);
    WS = 'S' + str(w_id);
    WP = 'P' + str(w_id);
    WC = 'C' + str(w_id);
    WH = 'H' + str(w_id);

    #print(df[WR])
    #print(n)
    winnerGraph()

print(wins)

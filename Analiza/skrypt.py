#import numpy as np
#import matplotlib as plt
import pandas as pd

def won(i):
    #R S P C H
    R = 'R' + str(i);
    S = 'S' + str(i);
    P = 'P' + str(i);
    C = 'C' + str(i);
    H = 'H' + str(i);
    if(df.iloc[-1][R]>=1 and df.iloc[-1][S]>=1and df.iloc[-1][P]>=1and df.iloc[-1][C]>=1and df.iloc[-1][H]>=1):
        return True
    else:
        return False


df = pd.read_csv(r'./dane.csv' )
print(df)


print(df[-1:])

print(df.iloc[-1]['H1'])

#wybór wygranego

w_id = 0;

for num in range(4):
    if won(num+1):
        w_id = num+1
        break

if w_id == 0:
    print("Rozgrywka bez zwycięzcy")




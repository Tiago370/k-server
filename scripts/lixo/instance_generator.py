from random import seed
import random
seed(1)
nNodes = 20
nServers = 2
def gerarMapa(nNodes):
    mapa = []
    for i in range(0, nNodes):
        mapa.append([])
        for j in range(0, nNodes):
            mapa[i].append(random.randint(1, 100))
    for i in range(0, nNodes):
        mapa[i][i] = 0

    for i in range(1, nNodes - 1):
        for j in range(i+1, nNodes):
            mapa[i][j] = mapa[j][i]
    return mapa
def printMapa(mapa):
    for i in range(0, len(mapa)):
        for j in range(0, len(mapa[i])):
            print(str(mapa[i][j]) + " ", end="")
        print()
printMapa(gerarMapa(nNodes))

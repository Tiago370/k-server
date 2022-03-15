import random
import matplotlib.pyplot as plt

"""
    n: é o número de nós
    a: é a procentagem de nós previlegiados
    b: é a procentagem de rquisições pertencentes aos nós previlegiados
    r: é o número de requisições
"""
def generateRequisitions(a, b, n, r):
    if a ==  100 and b == 100:
        requisitions = []
        for i in range(r):
            requisitions.append(random.randint(0, n - 1))
        return requisitions
    #obter o número de nós previlegiados
    nPrivileged = int((a/100) * n)
    #selecionar os nós previlegiados
    privilegedNodes = random.sample(range(0, n), nPrivileged)
    print("Nós previlegiados: ", privilegedNodes)
    #intervalo de roleta enviesada
    cotasTotal = n*10
    cotasPrivileged = int((cotasTotal*b/100)/nPrivileged)
    cotasNonPrivileged = int((cotasTotal*(100-b)/100)/(n-nPrivileged))
    cotas = []
    for i in range(nPrivileged):
        for j in range(0, cotasPrivileged):
            cotas.append(privilegedNodes[i])
    for i in range(0, n):
        if i not in privilegedNodes:
            for j in range(0, cotasNonPrivileged):
                cotas.append(i)
    
    #gerar as requisições
    requisitions = []
    for i in range(0, r):
        requisitions.append(random.choice(cotas))
    return requisitions
    


req = generateRequisitions(30, 50, 10, 1000)
#req = sorted(req)
plt.hist(req, 10, rwidth=0.9)
plt.show()
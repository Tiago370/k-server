import os
import random
import matplotlib.pyplot as plt

class Structurer:
    def __init__(self):
        self.meta_dados = {}
    def check(self):
        #verificar se a pasta dados existe
        if os.path.exists("dados"):
            pass
        else: # se não existir, criar a estrutura
            os.mkdir("dados")
            os.mkdir("dados/instancias")
            os.mkdir("dados/saida")

    def newBatch(self):
        nBatches = len(os.listdir("dados/instancias"))
        pathBatch = "dados/instancias/lote" + str(nBatches+1)
        os.mkdir(pathBatch)
        os.mkdir("dados/saida/lote" + str(nBatches + 1))

        arquivo = open(pathBatch + "/meta-dados.txt", "a")
        arquivo.write("nos = 10\n")
        arquivo.write("servidores = 2\n")
        arquivo.write("requisicoes = 100\n")
        arquivo.write("instancias = 3\n")
        arquivo.write("padrao_de_distribuicao = (100, 100)\n")
        arquivo.write("geracoes" + " = 10000\n")
        arquivo.write("individuos" + " = 100\n")
        arquivo.write("camadas_escondidas" + " = 2\n")
        arquivo.write("neuronios_escondidos" + " = 2\n")
        arquivo.write("geracoes_sem_melhora" + " = 200\n")
        arquivo.close()
        # Criar as pastas de treinamento e teste
        os.mkdir(pathBatch + "/req-trn")
        os.mkdir(pathBatch + "/req-tst")

    def generateMap(self, idLote):
        # Criar o arquivo mapa.txt
        pathBatch = "dados/instancias/lote" + str(idLote)
        arquivo = open(pathBatch + "/mapa.txt", "w")
        # Escrever o número de nós e servidores
        nNos = self.meta_dados["nos"]
        nServidores = self.meta_dados["servidores"]
        arquivo.write(str(nNos) + " " + str(nServidores) + "\n")
        nosIniciais = []
        # Escrever os nós iniciais
        for i in range(nServidores):
            r = random.randint(0, nNos - 1)
            while r not in nosIniciais:
                nosIniciais.append(r)
                r = random.randint(0, nNos - 1)
            arquivo.write(str(random.randint(0, nNos - 1)) + "\n")
        
        # Criar um array de pontos
        pontos = []
        for i in range(nNos):
            x = random.randint(0, 1000)
            y = random.randint(0, 1000)
            pontos.append((x, y))
        
        #Escrever a matriz de distâncias
        for i in range(nNos):
            for j in range(nNos):
                distancia = self.calculateDistance(pontos[i], pontos[j])
                arquivo.write(str(distancia) + " ")
            arquivo.write("\n")
        arquivo.close()

    def readMetaData(self, idLote):
        pathBatch = "dados/instancias/lote" + str(idLote)
        arquivo = open(pathBatch + "/meta-dados.txt", "r")
        dados = []
        
        for linha in arquivo:
            key, value = linha.split("=")
            #remover espaços em branco e o \n
            value = value.strip()
            value = value.replace("\n", "")
            key = key.strip()
            
            if key == "padrao_de_distribuicao":
                v = value.split(",")
                v[0] = v[0].strip()
                v[0] = v[0].replace("(", "")
                x = int(v[0])
                v[1] = v[1].strip()
                v[1] = v[1].replace(")", "")
                y = int(v[1])
                self.meta_dados[key] = (x, y)
            else:
                self.meta_dados[key] = int(value)
        arquivo.close()

    def calculateDistance(self, p1, p2):
        x1 = p1[0]
        y1 = p1[1]
        x2 = p2[0]
        y2 = p2[1]
        distancia = ((x1 - x2)**2 + (y1 - y2)**2)**(1/2)
        return distancia

    def generateInstances(self, idLote):
        nInstancias = self.meta_dados["instancias"]
        nRequisicoes = self.meta_dados["requisicoes"]
        nNos = self.meta_dados["nos"]
        padraoDeDistribuicao = self.meta_dados["padrao_de_distribuicao"]
        #gerar as requisições de treinamento
        for i in range(1, nInstancias + 1):
            pathBatch = "dados/instancias/lote" + str(idLote)
            arquivo = open(pathBatch + "/req-trn/req" + str(i) + ".txt", "w")
            arquivo.write(str(nRequisicoes) + "\n")
            requisicoes = self.generateRequisitions(padraoDeDistribuicao[0], padraoDeDistribuicao[1], nNos, nRequisicoes)
            for i in range(nRequisicoes):
                arquivo.write(str(requisicoes[i]) + "\n")
            arquivo.close()
        
        #gerar as requisições de teste
        for i in range(1, nInstancias + 1):
            pathBatch = "dados/instancias/lote" + str(idLote)
            arquivo = open(pathBatch + "/req-tst/req" + str(i) + ".txt", "w")
            arquivo.write(str(nRequisicoes) + "\n")
            requisicoes = self.generateRequisitions(padraoDeDistribuicao[0], padraoDeDistribuicao[1], nNos, nRequisicoes)
            for i in range(nRequisicoes):
                arquivo.write(str(requisicoes[i]) + "\n")
            arquivo.close()
    
    def train(self, idLote, toPrint):
        pathBatch = "dados/instancias/lote" + str(idLote)
        pathSaida = "dados/saida/lote" + str(idLote)
        # Obter os argumentos do meta-dados
        nGenerations = self.meta_dados["geracoes"]
        nIndividuals = self.meta_dados["individuos"]
        nHiddenLayers = self.meta_dados["camadas_escondidas"]
        nHiddenNeurons = self.meta_dados["neuronios_escondidos"]
        generationsWithoutImprovement = self.meta_dados["geracoes_sem_melhora"]
        loteId = idLote
        nInstances = self.meta_dados["instancias"]
        nServers = self.meta_dados["servidores"]
        
        # Executar o algoritmo de treinamento
        # ./build/k-server -training <nGenerations> <nIndividuals> <nHiddenLayers> <nHiddenNeurons> <generationsWithoutImprovement> <loteId> <nInstances>
        
        comando = "./build/k-server -training " + str(nGenerations) + " " + str(nIndividuals) + " " + str(nHiddenLayers) + " " + str(nHiddenNeurons) + " " + str(generationsWithoutImprovement) + " " + str(loteId) + " " + str(nInstances) + " " + str(nServers)
        if toPrint:
            print(comando)
        else:
            os.system(comando)

    def deleteBatch(self, idLote):
        # Deletar o batch dentro do diretório dados/instancias
        pathBatch = "dados/instancias/lote" + str(idLote)
        os.system("rm -rf " + pathBatch + "/")

        # Deletar o batch dentro do diretório dados/saida
        pathBatch = "dados/saida/lote" + str(idLote)
        os.system("rm -rf " + pathBatch + "/")

    def listBatches(self):
        # Obter o diretório de instâncias
        pathBatch = "dados/instancias"
        lista = os.listdir(pathBatch)
        lista.sort()
        print("Lista de lotes:")
        for i in range(len(lista)):
            print(str(i+1) + " - " + lista[i])

    def generateRequisitions(self, a, b, n, r):
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
    
    def runnet(self, idLote):        
        #./build/k-server -run dados/instancias/lote1/mapa.txt dados/instancias/lote1/req-tst/req1.txt dados/saida/lote1/rede-2x2.txt
        # Obter o caminho do mapa
        pathMap = "dados/instancias/lote" + str(idLote) + "/mapa.txt"
        # Obter o caminho das requisições de teste
        pathRequisitions = "dados/instancias/lote" + str(idLote) + "/req-tst"
        # Obter o caminho da rede
        pathNetwork = "dados/saida/lote" + str(idLote) + "/rede.txt"
        # Obter o número de instâncias
        nInstances = self.meta_dados["instancias"]
        # Obter o caminho do arquivo de resultados
        pathResults = "dados/saida/lote" + str(idLote) + "/resultados-rede.csv"
        # Apagar o conteúdo do arquivo de resultados
        os.system("rm " + pathResults)
        # Rodar todas as instâncias
        print("0i")
        for i in range(1, nInstances + 1):
            # Obter o caminho da requisição de teste
            pathRequisition = pathRequisitions + "/req" + str(i) + ".txt"
            # Rodar a rede
            comando = "./build/k-server -run " + pathMap + " " + pathRequisition + " " + pathNetwork + " " + idLote
            print(comando)
            os.system(comando)
    
    def runGreedy(self, idLote):
        #./build/k-server -greedy dados/instancias/lote1/mapa.txt dados/instancias/lote1/req-tst/req1.txt dados/saida/lote1/rede-2x2.txt 1
        # Obter o caminho do mapa
        pathMap = "dados/instancias/lote" + str(idLote) + "/mapa.txt"
        # Obter o caminho das requisições de teste
        pathRequisitions = "dados/instancias/lote" + str(idLote) + "/req-tst"
        # Rodar o algoritmo greedy para todas as requisições de teste
        for i in range(1, self.meta_dados["instancias"] + 1):
            # Obter o caminho da requisição de teste
            pathRequisition = pathRequisitions + "/req" + str(i) + ".txt"
            # Rodar o algoritmo greedy
            comando = "./build/k-server -greedy " + pathMap + " " + pathRequisition + " " + idLote
            print(comando)
            os.system(comando)
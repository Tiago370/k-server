import os
class Structurer:
    def __init__(self):
        pass

    def check(self):
        #verificar se a pasta dados existe
        if os.path.exists("dados"):
            pass
        else: # se não existir, criar a estrutura
            os.mkdir("dados")
            os.mkdir("dados/instancias")
            os.mkdir("dados/saida")
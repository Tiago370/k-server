#checar estrutura de pastas
import structurer
stt = structurer.Structurer()
stt.check()



"""
Estrutura da pasta dados:
    dados
        instancias
        saida

Estrutura de pastas das instâncias
    instancias
        lote1
            -meta-dados.txt
            - mapa.txt
            req-trn
                - req1.txt
                - req2.txt
                - req3.txt
            req-tst
                - req1.txt
                - req2.txt
                - req3.txt
        lote2
            -meta-dados.txt
            - mapa.txt
            - req-trn
                - req1.txt
                - req2.txt
                - req3.txt
            - req-tst
                - req1.txt
                - req2.txt
                - req3.txt
Estrutura do arquivo meta-dados.txt
    numero_de_nos = <int>
    numero_de_servidores = <int>
    numero_de_requisicoes = <int>
    numero_de_instancias = <int> # número de instancias de treino e de teste.
    padrao_de_distribuicao = (x, y) # O padrão (x, y) representa que y% das requisições são requisitadas por x% dos nós.

Estrutura da pasta de saída
    saida
        lote1
            - rede.txt
            - rst-trn.csv
            - rst-tst.csv
            - relatorio.txt
            sol-trn
                - sol1.txt
                - sol2.txt
                - sol3.txt
            sol-tst
                - sol1.txt
                - sol2.txt
                - sol3.txt
"""
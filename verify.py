from collections import defaultdict
grafo={}
def ler_grafo_arquivo(nome_arquivo):
    grafo = defaultdict(list)
    with open(nome_arquivo, 'r') as arquivo:
        for linha in arquivo:
            vertice1, vertice2 = linha.strip().split()
            grafo[vertice1].append(vertice2)
            grafo[vertice2].append(vertice1)
    return grafo

def busca_em_largura(grafo, vertice_inicial):
    visitados = set()
    fila = [vertice_inicial]

    while fila:
        vertice = fila.pop(0)
        if vertice not in visitados:
            visitados.add(vertice)
            fila.extend(grafo[vertice])

    return visitados

def eh_conexo(grafo):
    if not grafo:
        return False

    vertices = list(grafo.keys())
    visitados = busca_em_largura(grafo, vertices[0])

    return len(visitados) == len(vertices)

nome_arquivo = "grafo-matriz.txt"
grafo = ler_grafo_arquivo(nome_arquivo)
conexo = eh_conexo(grafo)

if conexo:
    print("O grafo é conexo.")
else:
    print("O grafo não é conexo.")
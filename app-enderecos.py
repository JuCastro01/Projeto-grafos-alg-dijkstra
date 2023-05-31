import googlemaps
from datetime import datetime
import itertools

lista_end = []
seletor = 0
matriz_dist_temp = []
inicial = 0
select_inicial = 0

def menu_inicial():
    seletor = input("\n \n Selecione a opção: \n \n a -> Adicionar endereços, lembrando que o primeiro sera o ponto de inicio \n b -> Calcular melhor rota \n ")
    if seletor == "a":
        add_end = input("Digite o endereço:")
        lista_end.append (add_end)
        print (lista_end)
        menu_inicial()

    if seletor == "a":
        api_dist()
    
def api_dist():

    for x,y in itertools.combinations(lista_end, 2):
        end_1 = x
        end_2 = y

        api_key = 'KEY'

        client = googlemaps.Client(api_key)

        origin = end_1
        destination = end_2

        now = datetime.now()

        directions_result = client.directions(origin, destination, mode="driving", departure_time=now)

        distance = directions_result[0]['legs'][0]['distance']['value']
        duration = directions_result[0]['legs'][0]['duration']['text']

        steps = directions_result[0]['legs'][0]['steps']

        print (f"A distancia entre {origin} e {destination} é {distance}")

        dist = (origin, destination, distance)
        
        matriz_dist_temp.append (dist)
    

        # Print the steps of the route
        # print("The steps for the route are:")
        # for step in steps:
        #     print (step['html_instructions'])

def get_google_maps_url(visited2):
    base_url = "https://www.google.com/maps/dir/"

    endq = '+'.join(map(str, visited2))

    google_maps_url = base_url + endq

    return google_maps_url

def main():
    menu_inicial()   
    print (matriz_dist_temp)
    lst= matriz_dist_temp

    result = {}
    for item in lst:
        src, dest, weight = item
        if src not in result:
            result[src] = {}
        if dest not in result:
            result[dest] = {}
        result[src][dest] = weight
        result[dest][src] = weight if dest in result[src] else 0
        
    for node in result:
        result[node] = {k: v for k, v in result[node].items() if v != 0}
    print (result)


    nodes = lista_end
    distances = result

    unvisited = {node: None for node in nodes} 
    visited = {}
    visited2 = []
    current = lista_end[0]
    currentDistance = 0
    unvisited[current] = currentDistance

    while True:
        for neighbour, distance in distances[current].items():
            if neighbour not in unvisited: continue
            newDistance = currentDistance + distance
            if unvisited[neighbour] is None or unvisited[neighbour] > newDistance:
                unvisited[neighbour] = newDistance
        visited[current] = currentDistance
        del unvisited[current]
        if not unvisited: break
        candidates = [node for node in unvisited.items() if node[1]]
        current, currentDistance = sorted(candidates, key = lambda x: x[1])[0]

    print(visited)

    for item in visited:
        visited2.append(item.replace(" ", "+"))
    print(visited2)

    maps_url = get_google_maps_url('/'.join(visited2))

    print("Google Maps URL:", maps_url)
    exit()


main()

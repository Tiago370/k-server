import math
def getDistanceFromLatLonInKm(lat1, lon1, lat2, lon2):
    R = 6371 #Radius of the earth in km
    dLat = math.radians(lat2-lat1) #deg2rad below
    dLon = math.radians(lon2-lon1) 
    a = math.sin(dLat/2) * math.sin(dLat/2) + math.cos(math.radians(lat1)) * math.cos(math.radians(lat2)) * math.sin(dLon/2) * math.sin(dLon/2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a)) 
    d = R * c #Distance in km
    return d;
def printMapa(mapa):
    for i in range(0, len(mapa)):
        for j in range(0, len(mapa[i])):
            print(str(mapa[i][j]) + " ", end="")
        print()
n = int(input())
coords = []
for i in range(0,18):
    linha = input()
    v = linha.split(',')
    lat = float(v[0])
    lng = float(v[1])
    coords.append((lat,lng))
#print(coords)
#print(getDistanceFromLatLonInKm(-22.4505429493694, -45.42110586834249, -22.44765639606411, -45.41952315958328))
distancias = []
for i in range(0, n):
    distancias.append([])
    for j in range(0, n):
        distancias[i].append(0)

for i in range(0, n):
    for j in range(0, n):
        distancias[i][j] = int(getDistanceFromLatLonInKm(coords[i][0], coords[i][1], coords[j][0], coords[j][1]) * 1000)

print(str(n) + " " + str(2))
printMapa(distancias)

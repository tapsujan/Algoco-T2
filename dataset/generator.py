import random

# Datasets A: strings de basalmente 10 caracteres
# Datasets B: strings de basalmente 100 caracteres
# Datasets C: strings de basalmente 1000 caracteres
# Datasets 0-10: strings balanceados (1:1), aleatorias
# Datasets 11-20: strings desbalanceados (1:2), aleatorias
# Datasets 21-30: strings muy desbalanceados (1:5), aleatorias
# Datasets 31-40: strings balanceados, 80% iguales
# Datasets 41-50: strings balanceados, 50% iguales

size = {"A":10, "B":100, "C":1000}
alphabet = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
aux = 1
chance = 0

#CODE - DATASET GENERATOR -

for k in size:
    for j in range(50):
        s1 = ""
        s2 = ""
        file = open("dataset{}{}.txt".format(k,j), "w")
        chance = 0
        if j <= 10:
            aux = 1
        elif j <= 20:
            aux = 2
        elif j <= 30:
            aux = 5
        elif j <= 40:
            aux = 1
            chance = 0.2
        else:
            aux = 1
            chance = 0.5
        for i in range(aux*size[k]):
            r = random.uniform(0,1)
            c = alphabet[random.randrange(len(alphabet)-1)]
            if i <= size[k]:
                s1 += c
            if(r > chance):
                c = alphabet[random.randrange(len(alphabet)-1)]
            s2 += c
        file.write("{}\n{}".format(s1,s2))
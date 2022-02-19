import random
nRequests = 1000000
aux = 0
print(nRequests)
for i in range(0, nRequests):
    number = random.randint(0, 17)
    while number == aux:
        number = random.randint(0, 17)
    aux = number
    print(number)
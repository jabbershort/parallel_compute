import random

def get_random(min,max):
    n = random.randrange(min,max)
    return n

def modmult(a,b,mod):
    return a*b % mod

def modpow(a,b,mod):
    return a**b % mod

def isPrime(n,num_tests=20):
    d = n-1
    s = 0

    while d%2 == 0:
        s += 1
        d /= 2
    
    for i  in range(num_tests):
        a = random.random() % (n-3) + 2
        x = modpow(a,d,n)

        for i in range(s):
            y = modmult(x,x,n)
            if (y == 1 and x != 1 and x != n-1):
                return False
            x = y
        if  x != 1:
            return False
    return True

if __name__ == "__main__":
    print(get_random(0,(2**64)-1))


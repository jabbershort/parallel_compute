import random
import time
from dataclasses import dataclass
# import pigpio

I2C_ADDRESS = 0x3a

@dataclass
class PrimeResult:
    time_taken: int
    prime: int
    board: str
    collected: bool

    def __str__(self):
        return f'Prime: {self.prime}, calculated in {self.time_taken}ms by {self.board}'

class PrimeGenerator:
    def __init__(self):
        self.result = PrimeResult(0,0,'Pi Zero 1.1',True)
        # self.pi = pigpio.pi()
        # e = self.pi.event_callback(pigpio.EVENT_BSC,self.i2c)

    # def i2c(self):


    def main_loop(self):
        while True:
            r, millis = generate_prime()
            self.result.collected = False
            self.result.prime = r
            self.result.time_taken = millis
            print(self.result)


    # def __del__(self):
    #     self.pi.bsc_i2c(0)
    #     self.pi.stop()

def get_random(min,max):
    n = random.randrange(min,max)
    return n

def miller_rabin(n, k):

    # Implementation uses the Miller-Rabin Primality Test
    # The optimal number of rounds for this test is 40
    # See http://stackoverflow.com/questions/6325576/how-many-iterations-of-rabin-miller-should-i-use-for-cryptographic-safe-primes
    # for justification

    # If number is even, it's a composite number

    if n == 2:
        return True

    if n % 2 == 0:
        return False

    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2
    for _ in range(k):
        a = random.randrange(2, n - 1)
        x = pow(a, s, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

def generate_prime():
    start = time.perf_counter()

    is_prime = False
    while not is_prime:
        r = get_random(0,(2**64)-1)
        is_prime = miller_rabin(r,20)
    end = time.perf_counter()
    millis = int((end-start)*1000)
    return r, millis


if __name__ == "__main__":
    gen = PrimeGenerator()
    gen.main_loop()
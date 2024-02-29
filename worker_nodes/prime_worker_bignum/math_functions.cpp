#include "math_functions.h"
#include <Arduino.h>
#include "BigNumber.h"

unsigned long long getRandom(unsigned long long const& min, unsigned long long const& max)
{
    return (((unsigned long long)(unsigned int)rand() << 32) + (unsigned long long)(unsigned int)rand()) % (max - min) + min;
}

BigNumber getRandom(int num_digits)
{
  char num[num_digits];
  for (int i = 0;i<num_digits;i++)
  {
    int c = (rand()%10);
    num[i] = '0'+c;
  }
  num[num_digits] = '\0';
  BigNumber bign (num);
  return bign;
}

long long modmult(long long a, long long b, long long mod) 
{  // Compute a*b % mod
    long long result = 0;
    while(b > 0) {
        if(b%2 == 1) {
            result = (result+a) % mod;
        }
        a = (a+a) % mod;
        b /= 2;
    }
    return result;
}

BigNumber modmult(BigNumber a, BigNumber b, BigNumber mod)
{ 
    BigNumber result = 0;
    while(b > 0) {
        if(b%BigNumber(2) == 1) {
            result = (result+a) % mod;
        }
        a = (a+a) % mod;
        b /= 2;
    }
    return result;
}

long long modpow(long long a, long long b, long long mod) 
{  // Compute a^b % mod
    long long result = 1;
    while(b > 0) {
        if(b%2 == 1) {
            result = modmult(result, a, mod);
        }
        a = modmult(a, a, mod);
        b /= 2;
    }
    return result;
}

BigNumber modpow(BigNumber a, BigNumber b, BigNumber mod)
{
    BigNumber result = 1;
    while(b > 0) {
        if(b%BigNumber(2) == 1) {
            result = modmult(result, a, mod);
        }
        a = modmult(a, a, mod);
        b /= 2;
    }
    return result;
}


// Miller–Rabin primality test
bool isPrime(long long n, int num_tests = 20) 
{  // Assumes n is an odd integer larger than 3
    long long d = n-1;
    long long s = 0;
    while(d%2 == 0) {
        s++;
        d /= 2;
    }
    
    for(int test = 0; test < num_tests; test++) {
        long long a = rand()%(n-3) + 2;  // Between 2 and v-2
        long long x = modpow(a, d, n);
        
        for(int i=0; i<s; i++) {
            long long y = modmult(x, x, n);
            if(y == 1 && x != 1 && x != n-1) {  // Nontrivial square root of 1 modulo n
                return false;  // (x+1)(x-1) divisible by n, meaning gcd(x+1, n) is a factor of n, negating primality
            }
            x = y;
        }
        if(x != 1) {
            return false;
        }
    }
    return true;  // Number is prime with likelihood of (1/4)^num_tests
}

bool isPrime(BigNumber n, int num_tests = 20) 
{  // Assumes n is an odd integer larger than 3
    BigNumber d = n-BigNumber(1);
    BigNumber s = 0;
    while(d%BigNumber(2) == 0) {
        s++;
        d /= 2;
    }
    
    for(int test = 0; test < num_tests; test++) {
        BigNumber a = rand()%(n-BigNumber(3)) + 2;  // Between 2 and v-2
        BigNumber x = modpow(a, d, n);
        
        for(int i=0; i<s; i++) {
            BigNumber y = modmult(x, x, n);
            if(y == 1 && x != 1 && x != n-BigNumber(1)) {  // Nontrivial square root of 1 modulo n
                return false;  // (x+1)(x-1) divisible by n, meaning gcd(x+1, n) is a factor of n, negating primality
            }
            x = y;
        }
        if(x != 1) {
            return false;
        }
    }
    return true;  // Number is prime with likelihood of (1/4)^num_tests
}

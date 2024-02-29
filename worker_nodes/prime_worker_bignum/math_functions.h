#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H
#include "BigNumber.h"

unsigned long long getRandom(unsigned long long const& min, unsigned long long const& max);
BigNumber getRandom(int num_digits);

long long modmult(long long a, long long b, long long mod);
BigNumber modmult(BigNumber a, BigNumber b, BigNumber mod);

long long modpow(long long a, long long b, long long mod);
BigNumber modpow(BigNumber a, BigNumber b, BigNumber mod);

bool isPrime(long long n, int num_tests);
bool isPrime(BigNumber n, int num_tests);
#endif
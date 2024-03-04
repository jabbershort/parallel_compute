#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <cstdint>

char * uintToStr(const uint64_t num, char *str );
unsigned long long getRandom(unsigned long long const& min, unsigned long long const& max);
long long modmult(long long a, long long b, long long mod);
long long modpow(long long a, long long b, long long mod);
bool isPrime(long long n, int num_tests);
#endif
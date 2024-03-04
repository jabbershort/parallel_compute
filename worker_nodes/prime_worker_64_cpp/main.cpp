#include <chrono>
#include <iostream>
#include "math_functions.h"

void generate_prime() {
  std::chrono::milliseconds start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  int k = 40;
  uint64_t r;
  bool pr = false;
  while (pr == false) {
    r = getRandom(0, UINT64_MAX);
    pr = isPrime(r, k);
  }
  std::chrono::milliseconds end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  std::cout << "Prime: " << r << std::endl ; 
  std::cout << "Calculated in " << (unsigned int)(end-start).count() << "ms" << std::endl;
}

int main(void){

    generate_prime();
}
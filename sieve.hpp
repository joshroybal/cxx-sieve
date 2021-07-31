#ifndef SIEVE_HPP
#define SIEVE_HPP

#include <vector>

void printArray(const bool*, int);
void printVector(const std::vector<int>&);

class sieveOfEratosthenes
{
   public:
      int countPrimes(int);
      int nthPrime(int);
      std::vector<int> simpleSieve(int);
      std::vector<int> segmentedSieve(int);
      std::vector<int> nPrimes(int);
   private:
      int count_primes_(int);
      int nth_prime_(int);
      std::vector<int> simple_sieve_(int);
      std::vector<int> segmented_sieve_(int);
      std::vector<int> n_primes_(int);
};

#endif

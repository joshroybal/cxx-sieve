#ifndef SIEVE_HPP
#define SIEVE_HPP

#include <vector>

void printArray(const bool*, unsigned);
void printVector(const std::vector<unsigned>&);

class sieveOfEratosthenes
{
   public:
      unsigned countPrimes(unsigned) const;
      unsigned nthPrime(unsigned) const;
      std::vector<unsigned> simpleSieve(unsigned) const;
      std::vector<unsigned> segmentedSieve(unsigned) const;
      std::vector<unsigned> nPrimes(unsigned) const;
      void gapTable() const;
   private:
      unsigned count_primes_(unsigned) const;
      unsigned nth_prime_(unsigned) const;
      std::vector<unsigned> simple_sieve_(unsigned) const;
      std::vector<unsigned> segmented_sieve_(unsigned) const;
      std::vector<unsigned> n_primes_(unsigned) const;
      void compute_segment_(const std::vector<unsigned>&, bool*, int, int, int) const;
      void gap_table_() const;
};

#endif

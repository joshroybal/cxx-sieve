#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "sieve.hpp"

static const unsigned LIMIT = 1000;

void printArray(const bool* arr, unsigned n)
{
    if (n > LIMIT) return;
    for (unsigned i = 0; i < n; i++)
        std::cout << ' ' << arr[i];
    std::cout << std::endl;
}

void printVector(const std::vector<unsigned>& v)
{
    if (v.size() > LIMIT) return;
    std::vector<unsigned>::const_iterator cit;
    for (cit = v.begin(); cit != v.end(); cit++) {
        std::cout << std::setw(12) << *cit;
        if ((cit - v.begin() + 1) % 6 == 0)
            std::cout << std::endl;
    }
    if (v.size() % 6 != 0)
        std::cout << std::endl;
}

// Class implementation of sieve of Eratosthenes

// public
unsigned sieveOfEratosthenes::nthPrime(unsigned n) const
{
    return nth_prime_(n);
}

unsigned sieveOfEratosthenes::countPrimes(unsigned n) const
{
    return count_primes_(n);
}

std::vector<unsigned> sieveOfEratosthenes::simpleSieve(unsigned n) const
{
    return simple_sieve_(n);
}

std::vector<unsigned> sieveOfEratosthenes::segmentedSieve(unsigned n) const
{
    return segmented_sieve_(n);
}

std::vector<unsigned> sieveOfEratosthenes::nPrimes(unsigned n) const
{
    return n_primes_(n);
}

void sieveOfEratosthenes::gapTable() const
{
    gap_table_();
}

// private
std::vector<unsigned> sieveOfEratosthenes::simple_sieve_(unsigned n) const
{
   if (n < 2) return std::vector<unsigned>();
   unsigned ssiz = n + 1;
   bool* sieve = new bool[ssiz];
   std::fill(sieve, sieve + 2, false);
   std::fill(sieve + 2, sieve + ssiz, true);
   std::vector<unsigned> prime;
   for (unsigned i = 2; i < sqrt(ssiz); i++)
      for (unsigned j = i * i; j < ssiz; j += i)
         sieve[j] = false;
   for (unsigned i = 2; i < ssiz; i++)
      if (sieve[i])
         prime.push_back(i);
   delete [] sieve;
   return prime;
}

std::vector<unsigned> sieveOfEratosthenes::segmented_sieve_(unsigned n) const
{
   if (n < 2) return std::vector<unsigned>();

   // compute base primes
   unsigned ssiz = floor(sqrt(n)) + 1;
   std::vector<unsigned> prime = simple_sieve_(ssiz);
   unsigned psiz = prime.size();

   // compute subsequent sieve segments of size ssiz
   bool* sieve = new bool[ssiz];
   for (unsigned lo = ssiz; lo <= n; lo += ssiz) {
      // compute next segment
      unsigned hi = (lo + ssiz <= n) ? lo + ssiz : n + 1;
      compute_segment_(prime, psiz, sieve, lo, hi);
      // append primes found in current segment
      for (unsigned j = lo; j < hi; j++)
         if (sieve[j-lo])
            prime.push_back(j);
   }
   delete [] sieve;
   return prime;
}

unsigned sieveOfEratosthenes::count_primes_(unsigned n) const
{
   if (n < 2) return 0;
   // compute and count base primes
   unsigned ssiz = sqrt(n) + 1;
   std::vector<unsigned> prime = simple_sieve_(ssiz);
   unsigned psiz = prime.size();
   unsigned count = psiz;

   // compute subsequent sieve segments and count primes found
   bool* sieve = new bool[ssiz];
   for (unsigned lo = ssiz; lo <= n; lo += ssiz) {
      // compute next segment
      unsigned hi = (lo+ssiz <= n) ? lo+ssiz : n + 1;
      compute_segment_(prime, psiz, sieve, lo, hi);
      // append primes found in current segment
      for (unsigned j = 0; j < hi-lo; j++)
         if (sieve[j])
            ++count;
   }
   delete [] sieve;
   return count;
}

std::vector<unsigned> sieveOfEratosthenes::n_primes_(unsigned n) const
{
   if (n < 1) return std::vector<unsigned>();

   unsigned ssiz;
   if (n >= 6)
      ssiz = floor(sqrt(n*log(n)+n*log(log(n))))+1;
   else
      ssiz = 12;

   // compute base primes
   std::vector<unsigned> prime = simple_sieve_(ssiz);
   unsigned psiz = prime.size();

   if (psiz >= n)
      return std::vector<unsigned>(prime.begin(), prime.begin() + n);
   const std::vector<unsigned> p(prime.begin(), prime.begin() + psiz);
   // compute subsequent sieve segments of size ssiz
   bool* sieve = new bool[ssiz];
   for (unsigned lo = ssiz; ; lo += ssiz) {
      // compute next segment
      compute_segment_(p, psiz, sieve, lo, lo+ssiz);
      // append primes found in current segment
      for (unsigned j = 0; j < ssiz; j++)
         if (sieve[j]) {
            prime.push_back(lo+j);
            if (prime.size() == n) {
               delete [] sieve;
               return prime;
            }
         }
   }
}

unsigned sieveOfEratosthenes::nth_prime_(unsigned n) const
{
   if (n < 1)
      return 0;

   unsigned ssiz;
   if (n >= 6)
      ssiz = floor(sqrt(n * log(n) + n* log(log(n)))) + 1;
   else
      ssiz = 12;

   // compute and count base prines
   std::vector<unsigned> prime = simple_sieve_(ssiz);
   unsigned psiz = prime.size();
   if (psiz >= n) return prime[n-1];
   unsigned count = psiz;

   // compute subsequent sieve segments of size ssiz
   bool* sieve = new bool[ssiz];
   for (unsigned lo = ssiz; ; lo += ssiz) {
      // compute next segment
      compute_segment_(prime, psiz, sieve, lo, lo+ssiz);
      // append primes found in current segment
      for (unsigned j = 0; j < ssiz; j++)
         if (sieve[j]) {
            ++count;
            if (count == n) {
                delete [] sieve;
                return lo+j;
            }
         }
   }
}

void sieveOfEratosthenes::compute_segment_(const std::vector<unsigned>& p,
    unsigned psiz, bool* s, unsigned lo, unsigned hi) const
{
  std::fill(s, s+(hi-lo), true);
  for (unsigned i = 0; i < psiz; i++) {
     // unsigned start = floor(lo/p[i])*p[i];
     unsigned start = lo-(lo%p[i]);
     if (start < lo)
        start += p[i];
     for (unsigned j = start; j < hi; j += p[i])
        s[j-lo] = false;
  }
}

void sieveOfEratosthenes::gap_table_() const
{
    const unsigned n = UINT_MAX;
    const unsigned m = sqrt(n) + 1;
    const std::vector<unsigned> prime(simple_sieve_(m));
    unsigned max_gap = 0;
    for (unsigned i = 1; i < prime.size(); i++) {
        unsigned gap = prime[i] - prime[i-1] - 1;
        if (gap > max_gap) {
            std::cout << prime[i-1] << '\t' << prime[i] << '\t' << gap << std::endl;
            max_gap = gap;
        }
    }
    unsigned p1 = prime[prime.size() - 1];
    unsigned p2 = 0;
    bool* sieve = new bool[m];
    for (unsigned i = m; i < n-m; i += m) {
        compute_segment_(prime, prime.size(), sieve, i, std::min(m+i, (n/m)*m));
        for (unsigned j = 0; j < m; j++) {
            if (sieve[j]) {
                p2 = i + j;
                unsigned gap = p2 - p1 - 1;
                if (gap > max_gap) {
                    std::cout << p1 << '\t' << p2 << '\t' << gap << std::endl;
                    max_gap = gap;
                }
                p1 = p2;
            }
        }
    }
    delete [] sieve;
}

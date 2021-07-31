#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "sieve.hpp"

static const int LIMIT = 1000;

void printArray(const bool* arr, int n)
{
    if (n > LIMIT) return;
    for (int i = 0; i < n; i++)
        std::cout << ' ' << arr[i];
    std::cout << std::endl;
}

void printVector(const std::vector<int>& v)
{
    if (v.size() > LIMIT) return;
    std::vector<int>::const_iterator cit;
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
int sieveOfEratosthenes::nthPrime(int n)
{
    return nth_prime_(n);
}

int sieveOfEratosthenes::countPrimes(int n)
{
    return count_primes_(n);
}

std::vector<int> sieveOfEratosthenes::simpleSieve(int n)
{
    return simple_sieve_(n);
}

std::vector<int> sieveOfEratosthenes::segmentedSieve(int n)
{
    return segmented_sieve_(n);
}

std::vector<int> sieveOfEratosthenes::nPrimes(int n)
{
    return n_primes_(n);
}

// private
std::vector<int> sieveOfEratosthenes::simple_sieve_(int n)
{
   if (n < 2) return std::vector<int>();
   int ssiz = n + 1;
   bool* sieve = new bool[ssiz];
   std::fill(sieve, sieve + 2, false);
   std::fill(sieve + 2, sieve + ssiz, true);
   std::vector<int> prime;
   for (int i = 2; i < sqrt(ssiz); i++)
      for (int j = i * i; j < ssiz; j += i)
         sieve[j] = false;
   for (int i = 2; i < ssiz; i++)
      if (sieve[i])
         prime.push_back(i);
   delete [] sieve;
   return prime;
}

std::vector<int> sieveOfEratosthenes::segmented_sieve_(int n)
{
   if (n < 2) return std::vector<int>();

   // compute base primes
   int ssiz = floor(sqrt(n)) + 1;
   std::vector<int> prime = simple_sieve_(ssiz);
   int psiz = prime.size();

   // compute subsequent sieve segments of size ssiz
   bool* sieve = new bool[ssiz];
   for (int i = ssiz; i <= n; i += ssiz) {
      // compute next segment
      std::fill(sieve, sieve + ssiz, true);
      for (int j = 0; j < psiz; j++) {
         int lo = floor(i / prime[j]) * prime[j];
         if (lo < i)
            lo += prime[j];
         int hi = (i + ssiz <= n) ? i + ssiz : n + 1;
         for (int k = lo; k < hi; k += prime[j])
            sieve[k - i] = false;
      }
      // append primes found in current segment
      int hi = (i + ssiz <= n) ? ssiz : n + 1 - i;
      for (int j = 0; j < hi; j++)
         if (sieve[j])
            prime.push_back(i + j);
   }
   delete [] sieve;
   return prime;
}

std::vector<int> sieveOfEratosthenes::n_primes_(int n)
{
   if (n < 1) return std::vector<int>();

   int ssiz;
   if (n >= 6)
      ssiz = floor(sqrt(n*log(n)+n*log(log(n))))+1;
   else
      ssiz = 12;

   // compute base primes
   std::vector<int> prime = simple_sieve_(ssiz);
   int psiz = prime.size();

   if (psiz >= n)
      return std::vector<int>(prime.begin(), prime.begin() + n);

   // compute subsequent sieve segments of size ssiz
   bool* sieve = new bool[ssiz];
   for (int i = ssiz; ; i += ssiz) {
      // compute next segment
      std::fill(sieve, sieve + ssiz, true);
      for (int j = 0; j < psiz; j++) {
         int lo = floor(i / prime[j]) * prime[j];
         if (lo < i)
            lo += prime[j];
         for (int k = lo; k < i + ssiz; k += prime[j])
            sieve[k - i] = false;
      }
      // append primes found in current segment
      for (int j = 0; j < ssiz; j++)
         if (sieve[j]) {
            prime.push_back(i + j);
            if (prime.size() == n) {
               delete [] sieve;
               return prime;
            }
         }
   }
}

int sieveOfEratosthenes::count_primes_(int n)
{
   if (n < 2) return 0;
   // compute and count base primes
   int ssiz = sqrt(n) + 1;
   std::vector<int> prime = simple_sieve_(ssiz);
   int psiz = prime.size();
   int count = psiz;

   // compute subsequent sieve segments and count primes found
   bool* sieve = new bool[ssiz];
   for (int i = ssiz; i <= n; i += ssiz) {
      // compute next segment
      std::fill(sieve, sieve + ssiz, true);
      for (int j = 0; j < psiz; j++) {
         int lo = floor(i / prime[j]) * prime[j];
         if (lo < i)
            lo += prime[j];
         int hi = (i + ssiz <= n) ? i + ssiz : n + 1;
         for (int k = lo; k < hi; k += prime[j])
            sieve[k - i] = false;
      }
      // append primes found in current segment
      int hi = (i + ssiz <= n) ? ssiz : n + 1 - i;
      for (int j = 0; j < hi; j++)
         if (sieve[j])
            ++count;
   }
   delete [] sieve;
   return count;
}

int sieveOfEratosthenes::nth_prime_(int n)
{
   if (n < 1)
      return -1;

   int ssiz;
   if (n >= 6)
      ssiz = floor(sqrt(n * log(n) + n* log(log(n)))) + 1;
   else
      ssiz = 12;

   // compute and count base prines
   std::vector<int> prime = simple_sieve_(ssiz);
   int psiz = prime.size();
   if (psiz >= n) return prime[n-1];
   int count = psiz;

   // compute subsequent sieve segments of size ssiz
   bool* sieve = new bool[ssiz];
   for (int i = ssiz; ; i += ssiz) {
      // compute next segment
      std::fill(sieve, sieve + ssiz, true);
      for (int j = 0; j < psiz; j++) {
         int lo = floor(i / prime[j]) * prime[j];
         if (lo < i)
            lo += prime[j];
         for (int k = lo; k < i + ssiz; k += prime[j])
            sieve[k - i] = false;
      }
      // append primes found in current segment
      for (int j = 0; j < ssiz; j++)
         if (sieve[j]) {
            ++count;
            if (count == n) {
               delete [] sieve;
               return i + j;
            }
         }
   }
}

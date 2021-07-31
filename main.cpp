#include <iostream>
#include <sstream>
#include "sieve.hpp"

int main(int argc, char *argv[])
{
   if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " n" << std::endl;
      return 1;
   }

   std::istringstream isstr(argv[1]);
   int n;
   isstr >> n;

   if (n < 1) {
      std::cerr << "n must be positive" << std::endl;
      return 1;
   }

   float t1, t2;
   std::vector<int> primes;
   sieveOfEratosthenes mySieve;

   std::cout << "simple sieve" << std::endl;
   t1 = clock();
   primes = mySieve.simpleSieve(n);
   t2 = clock();
   printVector(primes);
   std::cout << "elapsed time = " << (t2-t1)/CLOCKS_PER_SEC << " seconds\n";
   std::cout << std::endl;
    
   std::cout << "segmented sieve" << std::endl;
   t1 = clock();
   primes = mySieve.segmentedSieve(n);
   t2 = clock();
   printVector(primes);
   std::cout << "elapsed time = " << (t2-t1)/CLOCKS_PER_SEC << " seconds\n";
   std::cout << std::endl;

   std::cout << "prime counting function" << std::endl;
   t1 = clock();
   int count = mySieve.countPrimes(n);
   t2 = clock();
   std::cout << "pi(" << n << ") = " << count << std::endl;
   std::cout << "elapsed time = " << (t2-t1)/CLOCKS_PER_SEC << " seconds\n";
   std::cout << std::endl;

   std::cout << "first " << n << " prime nos." << std::endl;
   t1 = clock();
   primes = mySieve.nPrimes(n);
   t2 = clock();
   printVector(primes);
   std::cout << "elapsed time = " << (t2-t1)/CLOCKS_PER_SEC << " seconds\n";
   std::cout << std::endl;

   std::cout << "nth prime no." << std::endl;
   t1 = clock();
   int nth_prime = mySieve.nthPrime(n);
   t2 = clock();
   std::cout << "prime no. " << n << " = " << nth_prime << std::endl;
   std::cout << "elapsed time = " << (t2-t1)/CLOCKS_PER_SEC << " seconds\n";

   return 0;
}

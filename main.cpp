#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
using namespace std;


struct INumberGenerator
{
    virtual int next() = 0;
};


struct FibonacciNumberGenerator : public INumberGenerator
{
    int next() override
    {
        int n = b;
        int tmp = a;
        a = b;
        b = tmp + a;
        return n;
    }

private:
    int a{}, b{1};
};


struct PrimeNumberGenerator : public INumberGenerator
{
    int next() override
    {
        int prime = primes[primes.size() - 2];
        appendNextPrime();
        return prime;
    }

private:
    void appendNextPrime()
    {
        int v = primes.back() + 1;
        while(!isPrime(v))
        {
            v++;
        }
        primes.push_back(v);
    }

    bool isPrime(int n)
    {
        return std::none_of(std::begin(primes) + 1, std::end(primes), [n](auto p_value)
        {
            return (n % p_value) == 0;
        });
    }

    std::vector<int> primes = {1,2};
};


struct RandomNumberGenerator : public INumberGenerator
{
    int next() override
    {
        return 4;
    }
};


void printNumbers(INumberGenerator & numberGenerator, int numOfNumbers)
{
    for(int i = 0; i < numOfNumbers; ++i)
    {
        std::cout << numberGenerator.next() << std::endl;
    }
}


enum class GeneratorType
{
    RANDOM,
    FIBONACCI,
    PRIME
};


std::unique_ptr<INumberGenerator> createGenerator(GeneratorType type)
{
    switch(type)
    {
    case GeneratorType::RANDOM:
        return std::make_unique<RandomNumberGenerator>();
    case GeneratorType::FIBONACCI:
        return std::make_unique<FibonacciNumberGenerator>();
    case GeneratorType::PRIME:
        return std::make_unique<PrimeNumberGenerator>();
    default:
        throw std::logic_error("Invalid number generator type!");
    }
}

int sumGeneratedNumbers(std::unique_ptr<INumberGenerator> gen, int num)
{
    int acc = 0;
    for(int i = 0; i < num; ++i)
    {
        acc += gen->next();
    }
    return acc;
}


int sumNumbersFromGenerators(std::vector<GeneratorType> const& types, int num)
{
// TODO Write a loop that goes over a collection of GeneratorType values (types) and creates generator for given type, 
// then sums up all generated values for each type and returns the sum of sums.
// Use sumGeneratedNumbers to sum generate values for each generator.

    return std::accumulate(types.cbegin(), types.cend(), 0, [num](int a, const GeneratorType& genType){
        return a + sumGeneratedNumbers(createGenerator(genType), num);
    });
}

int main()
{
    auto gen = createGenerator(GeneratorType::RANDOM);

    auto generators = { GeneratorType::RANDOM, GeneratorType::FIBONACCI, GeneratorType::PRIME };

    std::cout << "Result: " << sumNumbersFromGenerators(generators, 10) << std::endl;

    return 0;
}


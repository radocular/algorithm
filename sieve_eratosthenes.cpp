#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <vector>

using namespace std;

template <class Container, class Number>
inline void sieve_eratosthenes(const Container& cache, const Number first,
    const Number last, function<void(decltype(first))> heureka) {
    static_assert(is_arithmetic<Number>::value and
        is_same<typename Container::value_type, Number>::value, "invalid");

    for (Number value = first; value <= last; value += 2) {
        for (Number prime: cache) {
            if (fmod(value, prime) == 0)
                break;

            if (prime == *(cache.end() - 1)) {
                heureka(value);
                break;
            }
        }
    }
}

template <class Number>
void find_primes(const Number bound) {
    static_assert(is_arithmetic<Number>::value, "invalid");

    vector<Number> cache { 3 };
    Number pivot = sqrt(bound);

    if (fmod(pivot, 2) != 1)
        ++pivot;

    if (bound >= 2)
        cout << 2 << " ";

    if (bound >= 3)
        cout << 3 << " ";

    sieve_eratosthenes(cache, Number(5), pivot,
        [&cache](const Number element) {
            cache.push_back(element);
            cout << element << " ";
        });

    sieve_eratosthenes(cache, Number(pivot + 2), bound,
        [](const Number element) {
            cout << element << " ";
        });

    cout << endl;
}

int main(const int argc, const char* argv[]) {
    uint64_t bound;

    if (argc != 2 or (stringstream(argv[1]) >> bound).fail())
        return EXIT_FAILURE;

    find_primes(bound);
    return EXIT_SUCCESS;
}

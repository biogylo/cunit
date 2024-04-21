#include <cunit.h>
#include <test_fizzbuzz.h>

int main() {
    SUITE(
        test_failing,
        test_fizzbuzz,
        test_failing,
        test_fizzbuzz,
        test_failing,
        test_fizzbuzz,
        test_failing,
        test_fizzbuzz
    );
}
# cunit

Simple C unit testing framework.

C kind of has a roll-your-own culture, and I wanted to create my own standard library to practice low level programming. For this though, I would need a resource for proving the correctness of my code. This is my first shot at creating a unit testing framework in C.

## Available assertions

Right now you have the following assertion macros, that you can use inside a test:
- `ASSERT(boolean_expression)`
    - If the boolean expression holds true, it will move on, otherwise fail the test, and print out useful information like filename, line number.
- `ASSERT_STREQ(string1,string2)`
    - Checks if two C strings are equals, and does the above

## Available fallible functions

Since segfaulting is possible if something fails, I am aiming at making fallible functions instead "ERROR" a test. We have.
- `TRY_CALLOC(n_elements, type_size)`
    - The same thing as `calloc`, however if it fails it will "ERROR" the surrounding test, and have reasonable behavior.

## How to make a test suite

Make a header file with your test defined the following way

`test_fizzbuzz.h`
```c
// test_fizzbuzz.h

#include <cunit.h>

TEST(
    name_of_the_test,
    /* Setup block      */,
    /* Test block       */,
    /* Teardown block   */
);

// A concrete example below
char * buffer;
TEST(
    fizz_buzz_example,
    /* Setup block      */
    buffer = (char *) TRY_CALLOC(32, sizeof(char));,
    /* Test block       */,
    fizzbuzz(buffer, 15)
    ASSERT_STREQ(buffer, "FizzBuzz");,
    /* Teardown block   */
    free(buffer);
);

```

I am still thinking of a good mechanism for running the tests, but for now, the main way, is to create a main file, include the header for the previously mentioned test, and, use the SUITE macro, while prepending `test_` to the test name

`main.c`
```c
//main.c
#include <test_fizzbuzz.h>

void main() {
    SUITE(
        test_name_of_the_test,
        test_fizz_buzz_example,
        test_failing_test
    )
}
```

## Output
The current output for the above example would be:

```
--- START TEST SUITE ---
[1] - name_of_the_test
                SUCCESS - in setup
                SUCCESS - in test
                SUCCESS - in teardown
[2] - fizz_buzz_example
                SUCCESS - in setup
                SUCCESS - in test
                SUCCESS - in teardown
[3] - failing_test
                SUCCESS - in setup
                FAILURE - in test
                SUCCESS - in teardown
Ran 3 tests!
3 PASSED, 0 FAILED, 0 ERRORED
--- PASSED TEST SUITE ---
```


## Possible future features
- Exit codes on bad/good test results
- Simple tests (no setup, teardown)
- Nicer terminal output
- Measuring test durations
- CLI arguments for deciding which tests to run
- Test reports
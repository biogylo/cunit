
#include "cunit.h"
#include <stdlib.h>
#include "fizzbuzz.h"
#include <string.h>
#include <stdio.h>

static c_str the_buffer;

TEST(fizzbuzz,
    // Setup
    the_buffer = (c_str) TRY_CALLOC(16, sizeof(char));,

    // Test
    fizzbuzz(the_buffer, 1);
    ASSERT_STREQ(the_buffer, "1");
    fizzbuzz(the_buffer, 2);
    ASSERT_STREQ(the_buffer, "2");
    fizzbuzz(the_buffer, 3);
    ASSERT_STREQ(the_buffer, "Fizz");
    fizzbuzz(the_buffer, 4);
    ASSERT_STREQ(the_buffer, "4");
    fizzbuzz(the_buffer, 5);
    ASSERT_STREQ(the_buffer, "Buzz");
    fizzbuzz(the_buffer, 15);
    ASSERT_STREQ(the_buffer, "FizzBuzz");
    fizzbuzz(the_buffer, 123456);
    ASSERT_STREQ(the_buffer, "Fizz");
    fizzbuzz(the_buffer, 4294967295);
    ASSERT_STREQ(the_buffer, "FizzBuzz");
    fizzbuzz(the_buffer, 4294967294);
    ASSERT_STREQ(the_buffer, "4294967294");
    fizzbuzz(the_buffer, 6);
    ASSERT_STREQ(the_buffer, "Fizz");,
    
    // Teardown
    free(the_buffer);
);
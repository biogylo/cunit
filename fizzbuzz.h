
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


/*
    Takes in a char buffer, and an integer. 
    
    Since we take in uint32 and the max number is 4294967295, 
    the buffer must be able to hold at least 11 characters.

    If the input is divisible by 3
        writes "Fizz" to the buffer
    If the input is divisible by 5
        writes "Buzz" to the buffer
    If the input is divisible by 15
        writes "FizzBuzz" to the buffer
    Otherwise it writes the number itself
*/
void fizzbuzz(char* buffer, uint32_t input) {
    if (input%15 == 0) {
        sprintf(buffer, "FizzBuzz");
    } else if (input %3 == 0) {
        sprintf(buffer, "Fizz");
    } else if (input %5 == 0) {
        sprintf(buffer, "Buzz");
    } else {
        sprintf(buffer,"%u", input);
    }
} 


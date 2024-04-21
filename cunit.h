#pragma once


#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

char static_buffer[1024];
typedef char* c_str;
const c_str ALLOC_ERROR = "Unable to allocate memory";

#define TRY_CALLOC(n_members, size) ({\
        void * the_pointer = calloc(n_members, size);\
        if (the_pointer == 0) {result_t result = {ERROR, ALLOC_ERROR};return result;};\
        the_pointer;})

#define ASSERT(boolean_expression) ({if (boolean_expression != true) { uint32_t line = __LINE__; \
        sprintf(static_buffer, "Assertion failed: (%s) in file %s:%d", #boolean_expression, __FILE__, line,); \
        result_t result = {FAILURE, static_buffer}; \
        return result;\
    }; })

#define ASSERT_STREQ(string1, string2) ({if (strcmp(string1,string2) != 0) { uint32_t line = __LINE__; \
        sprintf(static_buffer, "String assertion failed: (\"%s\" != \"%s\") in file %s:%d", \
                                                    string1, string2,       __FILE__, line); \
        result_t result = {FAILURE, static_buffer}; \
        return result;\
    };})


#define TEST(test_name, setup_block, test_block, teardown_block) \
    static result_t _setup() { \
        setup_block \
        result_t __final_result = {SUCCESS, NULL};\
        return __final_result;\
    }; \
    static result_t _test() { \
        test_block \
        result_t __final_result = {SUCCESS, NULL};\
        return __final_result;\
    }; \
    static result_t _teardown() { \
        teardown_block \
        result_t __final_result = {SUCCESS, NULL};\
        return __final_result;\
    }; \
    test_t test_ ## test_name = {\
        .name = # test_name, \
        .setup_fn = _setup, \
        .test_fn = _test, \
        .teardown_fn = _teardown}

typedef enum {
    SUCCESS = 0,
    FAILURE = 1,
    ERROR = 2,
} code_t;


typedef struct __result {
    code_t the_code;
    c_str explanation;
} result_t;

typedef struct __test {
    c_str       name;
    result_t    (*setup_fn)     ();
    result_t    (*test_fn)      ();
    result_t    (*teardown_fn)  ();
} test_t;

c_str code_to_str(code_t code);

test_t __noop_test = {"noop test noop test", NULL,NULL,NULL};
result_t __run(test_t test);
void __suite(test_t test, ...);


#define SUITE(...) __suite(__VA_ARGS__, __noop_test)
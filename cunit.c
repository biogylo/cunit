#include <cunit.h>

char static_buffer[1024];
const char* ALLOC_ERROR = "Unable to allocate memory";
test_t __noop_test = {"noop test noop test", NULL,NULL,NULL};

char* code_to_str(code_t code) {
    switch (code)
    {
    case SUCCESS:
        return "SUCCESS";
    case FAILURE:
        return "FAILURE";
    case ERROR:
        return "ERROR";
    }
}

result_t __run(test_t test){
    // First we need to run the setup
    if (test.setup_fn) {
        result_t setup_result = test.setup_fn();
        printf("\t\t%s - in setup", code_to_str(setup_result.the_code));

        if (setup_result.the_code != SUCCESS) {
            if (setup_result.explanation) {
                printf("\n\t\t    %s", setup_result.explanation);
            }
            printf("\n");
            return setup_result;
        }
        printf("\n");
    }

    result_t test_result = test.test_fn();
    printf("\t\t%s - in test", code_to_str(test_result.the_code));

    if (test_result.the_code != SUCCESS) {
        if (test_result.explanation) {
            printf("\n\t\t    %s", test_result.explanation);
        }
    }
    printf("\n");


    if (test.teardown_fn) {
        result_t teardown_result = test.teardown_fn();
        
        printf("\t\t%s - in teardown", code_to_str(teardown_result.the_code));

        if (teardown_result.the_code != SUCCESS) {
            if (teardown_result.explanation) {
                printf("\n\t\t    %s", teardown_result.explanation);
            }
        }
        printf("\n");
    }
    return test_result;
}


void __suite(...) {
    va_list tests;
    printf("--- START TEST SUITE ---\n");
    // While the noop test is not found
    uint32_t total = 0;
    uint32_t passed = 0;
    uint32_t failed = 0;
    uint32_t errored = 0;
    va_start(tests);

    while (true){
        test_t test = va_arg (tests, test_t);
        if (test.name == __noop_test.name) {
            break;
        }
        total++;
        printf("[%u] - %s\n",total, test.name);
        result_t result = __run(test);
        switch (result.the_code){
            case SUCCESS:passed++;break;
            case FAILURE:failed++;break;
            case ERROR:errored++;break;
        };
    };
    va_end(tests);
    printf("Ran %u tests!\n", total);
    printf("%u PASSED, %u FAILED, %u ERRORED\n", passed, failed, errored);
    if (failed == 0 && errored == 0) {
        printf("--- PASSED TEST SUITE ---\n");
    } else {
        printf("--- FAILED TEST SUITE ---\n");
    }
}


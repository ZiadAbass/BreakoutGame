#ifndef TESTS_H
#define TESTS_H

#include "Bar_Test.h"
#include "Ball_Test.h"


/**
 * @brief All the testing processes are run here
 *
 * @returns How many tests have failed
 */
int tests()
{
    // How many failed tests
    int failedTests = 0;

    ////////////////// BAR_TEST //////////////////////
    
    printf("Running the bar test \n");
    bool barTest = Bar_movement_test();

    // Did the test pass?
    if (barTest == true) {
        
        printf("Bar test Passed \n");
    }
    else {
        
        // Add one to the number of failed tests
        failedTests += 1;   
        printf("Bar test Failed \n");
    }
    
    
    
    ////////////////// BALL_TEST //////////////////////
    
    
    printf("Running the ball test \n");
    bool ballTest = Ball_movement_test();

    // Did the test pass?
    if (ballTest == true) {
        
        printf("Ball test Passed \n");
    }
    else {
        
        // Add one to the number of failed tests
        failedTests += 1;   
        printf("Ball test Failed \n");
    }
    
    
    /////////////////////////////////////////////////////

    // Overall result of the tests
    
    if (failedTests == 0)
    {
        printf("All tests passed \n");
    } else 
    {
        printf("%i tests failed \n",failedTests);
    }
    

    return failedTests;
}

#endif
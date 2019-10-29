#ifndef BAR_TEST_H
#define BAR_TEST_H


/**
* \brief Check that the bar moves correctly when the joystick does.
*
* \returns true if all the tests passed
*/


bool Bar_movement_test()
{

// Initialise the Bar. Init function already determines the start position to be (42,40) and the width to be 9
    Bar bar;
    bar.initBar(9,2,0.5);
    
// Apply the first user input & update position
    bar.refreshBarPosition(20, W);
    

// Read the bar's new position position
    Vector2D readPos = bar.current_position();
    printf("First Bar Position: %f, %f \n", readPos.x, readPos.y);
    
    
//SECOND DIRECTION////////


// Apply the second user input & update position
    bar.refreshBarPosition(50, E);
    
    
// Read the bar's new position position
    Vector2D readPos2 = bar.current_position();
    printf("Second Bar Position: %f, %f \n", readPos2.x, readPos2.y);
    
    
    

// Now check that both the positions are as expected
    bool success_flag = true;

// Fail the test if the first position is wrong
    if (readPos.x != 32 || readPos.y != 40) {
        success_flag = false;
    }

// Fail the test if the second position is wrong
    if (readPos2.x != 57 || readPos2.y != 40) {
        success_flag = false;
    }
    
    return success_flag;

}
#endif
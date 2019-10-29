#ifndef BALL_TEST_H
#define BALL_TEST_H


/**
* \brief Check that the ball moves correctly.
*
* \returns true if all the tests passed
*/


bool Ball_movement_test()
{

// Initialising ball, placing it at 42,40.
    Ball ball;
    ball.initBall(2,2);
    
// Place the ball at its starting position
    Vector2D starting_pos = {10,10};
    ball.set_position(starting_pos);
    
//Apply the velocity to the ball
    Vector2D applied_vel = {5,6};
    ball.set_velocity(applied_vel);
    ball.refreshBallPosition();

// Read the ball's new position position
    Vector2D new_pos = ball.current_position();
    printf("Final Ball Position: %f, %f \n", new_pos.x, new_pos.y);
    
    

// Now check that both the positions are as expected
    bool success_flag = true;

// Fail the test if the initial position is wrong
    if (starting_pos.x != 10 || starting_pos.y != 10) {
        success_flag = false;
    }

// Fail the test if the final position is wrong
    if (new_pos.x != 15 || new_pos.y != 16) {
        success_flag = false;
    }
    
    return success_flag;

}
#endif
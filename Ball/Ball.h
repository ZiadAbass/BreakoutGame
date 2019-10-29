#ifndef Ball_H
#define Ball_H

#include "N5110.h"
#include "Gamepad.h"
#include "mbed.h"
#include "Bar.h"


/** Ball Class
* @brief Displays the ball in its updated location and can obtain or set its position
* @author Ziad Abass
* @date April, 2018
*/
class Ball
{
    
public:
    
    /** Constructor */
    Ball();
    
    /** Destructor */
    ~Ball();
    
    /** Initialise ball parameters
    * @param Size of the ball (int)
    * @param Speed of the ball (int)
    */
    void initBall(int ball_size, int ball_speed);
    
    /** Display the ball on the LCD
    * @param N5110 object (lcd)
    */
    void drawBall(N5110 &lcd);
    
    /** Move the ball by updating its location
    */
    void refreshBallPosition();
    
    /** Set the ball's velocity
    * @param the new velocity of the ball (Vector2D)
    */
    void set_velocity(Vector2D vel);
    
    /** Set the ball's position
    * @param the new position of the ball (Vector2D)
    */
    void set_position(Vector2D pos);
    
    /** Obtain the ball's current velocity
    * @return the ball's velocity
    */
    Vector2D current_velocity();
    
    /** Obtain the ball's current position
    * @return the ball's position
    */
    Vector2D current_position();
    


private:
    
    int ballSize;
    int ballSpeed;
    int xpos;
    int ypos;

    Vector2D ballVelocity;
};

#endif

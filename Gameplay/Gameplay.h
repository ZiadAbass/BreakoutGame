#ifndef Gameplay_H
#define Gameplay_H

#include "N5110.h"
#include "Gamepad.h"
#include "mbed.h"

#include "Bar.h"
#include "Ball.h"
#include "Bricks.h"
#include "Score.h"
#include "PowerUps.h"


/** Gameplay Class
* @brief In charge of the running the game engine (ball & bar collisions and updating the display)
* @author Ziad Abass
* @date April, 2018
*/
class Gameplay
{
    
public:

    /** Constructor */
    Gameplay();
    
    /** Destructor */
    ~Gameplay();
    
    /** Call the initialisation of the bar, ball, bricks and the score.
    * @param Ball size (int)
    * @param Ball speed (int)
    * @param Bar width (int)
    * @param Bar height (int)
    * @param Bar speed (float)
    * @param X gap between bricks (int)
    * @param Y gap between bricks (int)
    * @param Bricks' width (int)
    * @param Bricks' height (int)
    * @param Number of columns (int)
    * @param Number of rows (int)
    * @param Number of lives (int)
    */
    void initGame(int ball_size, int ball_speed, int bar_width, int bar_height, float bar_speed, int gap_x, int gap_y,  int brick_width, int brick_height, int brick_columns, int brick_rows, int lives);
    
    /** Call the methods which update the locations of the ball, bar and bricks as long as there are lives remaining.
    * @param Gamepad object (gamepad)
    * @param N5110 object (lcd)
    */
    void refreshPositions(Gamepad &gamepad, N5110 &lcd);
    
    /** Draws the walls and call methods that display the items on the LCD
    * @param N5110 object (lcd)
    * @param Gamepad object (gamepad)
    */
    void drawItems(N5110 &lcd, Gamepad &gamepad);
        

private:

    // Rebound the ball off the walls
    void keepBallOnScreen(Gamepad &gamepad);
    
    // Rebound the ball off the bar
    void barBallCollision(Gamepad &gamepad);
    
    // Acknowledge that the ball hit one the bricks
    void ballBrickCollision(Gamepad &gamepad);
    
    // Check if the ball missed the bar and react if it did
    void ballMissedBar(Gamepad &gamepad);
    
    // Identifiy which brick was hit and hide it
    void hideStruckBrick(int xBallPosInt, int yBallPosInt, Vector2D ballPosFraction, Gamepad &gamepad);
    
    // Establish that the brick giving an extra life has been hit
    void specialLifeBrickStruck(N5110 &lcd);
    
    // Establish that the brick giving an extended bar has been hit
    void specialXTenderBrickStruck(N5110 &lcd);
    
    // Acknowledge wether the bar collected or missed the extra life powerUp
    void barCollectedXtraLife(Gamepad &gamepad);
    
    // Acknowledge wether the bar collected or missed the bar xTender powerUp
    void barCollectedWiderBar(Gamepad &gamepad);
    
    
    

    // Creating necessary objects:
    Bar bar;
    Ball ball;
    Bricks bricks;
    Score score;
    PowerUps pUps;
    
    
    int _bar_width;
    int _gap_x;
    int _gap_y;
    int _brick_width;
    int _brick_height;
    int _brick_columns;
    int _brick_rows;
    int _lives;
    
    // To obtain joystick direction and magnitude:
    Direction di;
    float ma;
    
    Vector2D ballPosition;
    Vector2D ballVelocity;
    Vector2D barPosition;
    
    int xBallPosInt;
    int yBallPosInt;
    Vector2D ballPosFraction;
    Vector2D scaledBallPos;
    
    Vector2D lifePos;
    Vector2D xTenderPos;
    int currentLoop;
    
    bool stopLookingForLife;
    bool stopLookingForXTender;
    
};

#endif

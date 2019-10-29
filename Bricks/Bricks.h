#ifndef Bricks_H
#define Bricks_H

#include "N5110.h"
#include "Gamepad.h"
#include "mbed.h"


/** Bricks Class
* @brief Sets the bricks' size and position and displays them on the LCD.
* @author Ziad Abass
* @date April, 2018
*/
class Bricks
{
    
public:

    /** Constructor */
    Bricks();
    
    /** Destructor */
    ~Bricks();
    
    /** Initialise the bricks' parameters and identify them all as not yet destroyed
    * @param Brick width (int)
    * @param Brick height (int)
    * @param Number of columns (int)
    * @param Number of rows (int)
    * @param X gap between bricks (int)
    * @param y gap between bricks (int)
    */
    void initBrick(int brick_width, int brick_height, int brick_columns, int brick_rows, int gap_x, int gap_y);
    
    /** Display the undestroyed bricks on the LCD
    * @param N5110 object (lcd)
    */
    void drawBrick(N5110 & lcd);
    
    /** Obtain the array showing which bricks are destroyed
    * @return the array representing the bricks' state
    */
    bool destroyed [9][5];
    

private:
    
    //X and Y gaps between bricks
    int gx;
    int gy;
    
    //Number of rows & columns
    int rows;
    int columns;
    
    //Dimensions of bricks
    int brickWidth;
    int brickHeight;
    
    //Bricks' positions
    int brickXpos;
    int brickYpos;


};

#endif
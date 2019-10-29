#include "Bricks.h"

Bricks::Bricks()
{

}

Bricks::~Bricks()
{

}


void Bricks::initBrick( int brick_width, int brick_height, int brick_columns, int brick_rows, int gap_x, int gap_y )
{
    brickWidth = brick_width;
    brickHeight = brick_height;

    gx = gap_x; //X gap between blocks
    gy = gap_y; //Y gap between blocks
    
    columns = brick_columns;
    rows = brick_rows;
    
    // 'destroyed' is an array representing each block's destruction state.
    // True = brick destroyed & vise versa
    for( int i = 0; i < columns; i++ ) 
    {
        for ( int j = 0; j < rows; j++ )
        {
            destroyed[i][j] = false;    // ie all bricks are not destroye
        }
    }
}


void Bricks::drawBrick(N5110 &lcd)
{

    for( int i = 0; i < columns; i++ ) 
    {
        for ( int j = 0; j < rows; j++ )
        {
            if (destroyed[i][j] == false)       //only draw the brick if it is not destroyed
            {
                //formula to place 40 equidistant bricks on the screen:
                lcd.drawRect((5+((brickWidth+gx)*i)), (5+((brickHeight+gy)*j)), brickWidth, brickHeight, FILL_BLACK);
            }
        }
    }
}

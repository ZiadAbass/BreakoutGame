#include "Bar.h"

Bar::Bar()
{

}

Bar::~Bar()
{

}

//initialising position, size, speed of bar:
void Bar::initBar(int bar_width, int bar_height, float bar_speed)
{
    ypos = 40;
    xpos = 42;
    barHeight = bar_height;
    barWidth = bar_width;
    speedMult = bar_speed; //speed multiplier
}
    
//drawing the bar on the LCD    
void Bar::drawBar(N5110 &lcd)
{
    lcd.drawRect(xpos, ypos, barWidth, barHeight, FILL_BLACK);
    
    //an int which increments with each game loop.
    //it is used to measure the time period through which the bar is extended if the xTender powerUp is taken
    incrNum++;
}


//Obtaining values from the joystick and positioning the bar accordingly
void Bar::refreshBarPosition(int speed, Direction dir)
{
    barSpeed = int(speed*speedMult);
    
    
    // Stop the bar leaving the screen
    if (xpos>73)
    {
        xpos = 73;
    }else if(xpos<3)
    {
        xpos = 3;
    }
    
    
    // Move the bar left & right
    if(dir == W)
    {
        xpos -= barSpeed;
        //printf("Bar moved Right, Speed = %i\n",barSpeed);
        
    }else if(dir == E)
    {
        xpos += barSpeed;
        //printf("Bar moved Left, Speed - %i\n",barSpeed);
    }
    
    
}


//obtain bar's current position:
Vector2D Bar::current_position()
{
    Vector2D currentP = {xpos,ypos};
    return currentP;
}


void Bar::setBarWidth(int width)
{
    barWidth = width;    
}




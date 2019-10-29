#ifndef Bar_H
#define Bar_H

#include "N5110.h"
#include "Gamepad.h"
#include "mbed.h"



/** Bar Class
* @brief Displays the bar in its updated location (depending on the joystick reading) and can obtain its current position.
* @author Ziad Abass
* @date April, 2018
*/
class Bar
{
    
public:

    /** Constructor */
    Bar();

    /** Destructor */
    ~Bar();
    
    /** Initialise bar parameters
    * @param Bar width (int)
    * @param Bar height (int)
    * @param Bar speed (float)
    */
    void initBar(int bar_width, int bar_height, float bar_speed);
    
    /** Display the bar on the LCD
    * @param N5110 object (lcd)
    */
    void drawBar(N5110 &lcd);
    
    /** Move the bar by updating its position according to the joystick movement
    * @param magnitude of the joystick's displacement (int)
    * @param the joystick's direction (Direction)
    */
    void refreshBarPosition(int speed, Direction dir);
    
    /** Obtain the bar's current position
    * @return the bar's position
    */
    Vector2D current_position();
    
    /** Method to change the bar's width
    * @param The bar's width (int)
    */
    void setBarWidth(int width);
    
    /** Obtain the loop number which increments with each game loop. This is used to time the barXtender powerUp
    * @return the loop number
    */
    int incrNum;


private:

    int xpos;
    int ypos;
    int pos;
    
    int barWidth;
    int barHeight;
    int barSpeed;
    float speedMult;

};

#endif
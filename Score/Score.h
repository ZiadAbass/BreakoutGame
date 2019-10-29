#ifndef Score_H
#define Score_H

#include "N5110.h"
#include "Gamepad.h"
#include "mbed.h"


/** Score Class
* @brief Adds up the score, keeps track of remaining lives and defines what's done after all lives are lost.
* @author Ziad Abass
* @date April, 2018
*/
class Score
{
    
public:

    /** Constructor */
    Score();
    
    /** Destructor */
    ~Score();
    
    /** Initialise the score by making it 0 and allowing 3 lives
    * @param Number of lives (int)
    */
    void init(int lives);
    
    /** Increase the score whenever a brick is hit
    * @param Gamepad object (gamepad)
    */
    void didHitBrick(Gamepad &gamepad);
    
    /** Reduce a life whenever the ball misses the bar
    * @param Gamepad object (gamepad)
    */
    void lostLife(Gamepad &gamepad);
    
    /** Display health icons representing remaining lives
    * @param N5110 object (lcd)
    * @param Gamepad object (gamepad)
    */
    void display(N5110 &lcd, Gamepad &gamepad);
    
    /** Display the final score after all lives are lost
    * @param N5110 object (lcd)
    * @param Gamepad object (gamepad)
    */
    void gameOver(N5110 &lcd, Gamepad &gamepad);
    
    /** Obtain the number of remaining lives
    * @return remaining lives
    */
    int livesRemaining;
    
    /** Obtain the score
    * @return currentScore
    */
    int currentScore;
    

private:

};

#endif
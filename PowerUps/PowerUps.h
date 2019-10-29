#ifndef PowerUps_H
#define PowerUps_H

#include "N5110.h"
#include "mbed.h"

#include "Bricks.h"

/** PowerUps Class
* @brief In charge of drawing and moving the 2 available power up icons
* @author Ziad Abass
* @date April, 2018
*/
class PowerUps
{
    
public:

    /** Constructor */
    PowerUps();
    
    /** Destructor */
    ~PowerUps();
    
    /** Call the initialisation of the powerUps.
    */
    void init();
    
    /** Draws the life powerUp icon
    * @param N5110 object (lcd)
    */
    void drawLife(N5110 &lcd);
    
    /** Update the position of the life icon.
    */
    void refreshLifePosition();
    
    /** Obtains and returns the current position of the extra life icon
    * @return the life icon's position
    */
    Vector2D currentLifePosition();
    
    
    /** Draws the xTender powerUp icon
    * @param N5110 object (lcd)
    */
    void drawXTender(N5110 &lcd);
    
    /** Update the position of the xTender icon.
    */
    void refreshXTenderPosition();
    
    /** Obtains and returns the current position of the extra life icon
    * @return the xTender's position
    */
    Vector2D currentXTenderPosition();
    
    
    int rowRand1;
    int colRand1;
    bool lifeReleased;
    int lifeX;
    int lifeY;
    
    int rowRand2;
    int colRand2;
    bool xTenderReleased;
    int xTenderX;
    int xTenderY;
    
    
    
private:

};

#endif

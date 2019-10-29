#include "PowerUps.h"

PowerUps::PowerUps()
{

}

PowerUps::~PowerUps()
{

}


// The sprite representing an extra life power
const int lifeIcon[4][7] =   {
    { 0,1,1,0,1,1,0 },
    { 0,1,1,1,1,1,0 },
    { 0,0,1,1,1,0,0 },
    { 0,0,0,1,0,0,0 },
    };
    
    
// The sprite representing a wider bar powerUp
const int xTenderIcon[5][7] =   {
    { 0,0,0,1,0,0,0 },
    { 0,0,1,1,1,0,0 },
    { 0,1,1,1,1,1,0 },
    { 1,1,1,1,1,1,1 },
    { 0,1,1,1,1,1,0 },
    };
    
    
    
void PowerUps::init()
{
    
    ///////////// initialising the extra life powerUp /////////////////
    
    //This will be the brick releasing the extra life power up
    rowRand1 = 2;
    colRand1 = 3;
    
    //Translating the (row,col) coordinates into the (x,y) starting pixel position of the heart sprite before it starts falling:
    
    // lifeX = 7 + (brickWidth + gapX)*(rowRand)
    lifeX = 7 + ( (7 + 2)*rowRand1 );
    
    // lifeY = 7 + (brickHeight + gapX)*(rowRand)
    lifeY = 7 + ( (2 + 2)*colRand1 );
    
    
    lifeReleased = false;
    
    
    ///////////// initialising the bar xTender powerUp /////////////////
    
    //This will be the brick releasing the extra life power up
    rowRand2 = 5;
    colRand2 = 3;
    
    // xTenderX = 7 + (brickWidth + gapX)*(rowRand2)
    xTenderX = 7 + ( (7 + 2)*rowRand2 );
    // xTenderY = 7 + (brickHeight + gapX)*(rowRand2)
    xTenderY = 7 + ( (2 + 2)*colRand2 );
    
    xTenderReleased = false;
    
}



///////////////////// EXTRA LIFE POWER UP /////////////////////

// extra life power up represented as a life icon
void PowerUps::drawLife(N5110 &lcd)
{
    lcd.drawSprite(lifeX,lifeY,4,7,(int *)lifeIcon);
}


//Move the powerUp downwards
void PowerUps::refreshLifePosition()
{
    //The life icon just moves downards
    lifeY += 1;
}



Vector2D PowerUps::currentLifePosition()
{
    Vector2D lifePos = {lifeX,lifeY};
    return lifePos;
}





///////////////////// WIDER BAR POWER UP /////////////////////

// wider bar power up represented as a star icon
void PowerUps::drawXTender(N5110 &lcd)
{
    lcd.drawSprite(xTenderX,xTenderY,5,7,(int *)xTenderIcon);
}


//Move the powerUp downwards
void PowerUps::refreshXTenderPosition()
{
    xTenderY += 1;
}


Vector2D PowerUps::currentXTenderPosition()
{
    Vector2D xTenderPos = {xTenderX,xTenderY};
    return xTenderPos;
}
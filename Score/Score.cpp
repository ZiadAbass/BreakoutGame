#include "Score.h"

Score::Score()
{

}

Score::~Score()
{

}

// The sprite representing a life
const int lifeIcon[4][7] =   {
    { 0,1,1,0,1,1,0 },
    { 0,1,1,1,1,1,0 },
    { 0,0,1,1,1,0,0 },
    { 1,1,0,1,0,1,1 },
    };


void Score::init(int lives)
{   
    //Game begins with 3 lives and a score of 0
    currentScore = 0;
    livesRemaining = lives;
}

//To earn points for hitting a brick
void Score::didHitBrick(Gamepad &gamepad)
{
    if (livesRemaining > 0)
    {
        currentScore += 10;
    }
    
    gamepad.tone(1100.0,0.1);
}


void Score::lostLife(Gamepad &gamepad)
{
    gamepad.tone(1000.0,0.23);
    livesRemaining -= 1;
    
    gamepad.leds_on();
    wait(0.1);
    gamepad.leds_off();
    wait(0.1);
    gamepad.leds_on();
    wait(0.1);
    gamepad.leds_off();
    
    printf("Life lost. Remaining: %i lives \n",livesRemaining);
    
}


void Score::display(N5110 &lcd, Gamepad &gamepad)
{   
    
    //Number of life sprites shown = Number of lives remaining
    for (int i = 84 - (9*livesRemaining); i < 76 ; i+=9)
    {
        lcd.drawSprite(i,43,4,7,(int *)lifeIcon);            
    }
    
    
    //Number of LEDs lit = Number of lives remaining
    for (int i = 7 - livesRemaining ; i < 7 ; i++)
    {
        gamepad.led(i, 1);      
    }
    
}


void Score::gameOver(N5110 &lcd, Gamepad &gamepad)
{
    
    while ( gamepad.check_event(Gamepad::Y_PRESSED) == false) 
    {
        lcd.clear();
        
        //Message shown depends on why the game ended
        if (currentScore == 400)
        {
            lcd.printString("GG!",34 ,1);
        } else {
            lcd.printString("Game Over!",13 ,1);
        }    
    
        //Display the score after game ends
        char buffer[8];         
        sprintf(buffer,"Score %li",currentScore);
        lcd.printString(buffer,15,2);
        
        lcd.printString("Press Y to",12 ,4);
        lcd.printString("restart",22 ,5);
        
        
        lcd.refresh();
    
        gamepad.led(4, 0);      //Switch off LEDs representing lives
        gamepad.led(5, 0);
        gamepad.led(6, 0);
    
        gamepad.leds_on();  //Flash leds until game restarts
        wait(0.1);
        gamepad.leds_off();
        wait(0.1);
    }
    
    
}

#include "Gameplay.h"

Gameplay::Gameplay()
{

}

Gameplay::~Gameplay()
{

}

void Gameplay::initGame(int ball_size, int ball_speed, int bar_width, int bar_height, float bar_speed, int gap_x, int gap_y,  int brick_width, int brick_height, int brick_columns, int brick_rows, int lives)
{
    //Saving the variables needed in this class to be used later
    _bar_width = bar_width;
    _gap_x = gap_x;
    _gap_y = gap_y;
    _brick_width = brick_width;
    _brick_height = brick_height;
    _brick_columns = brick_columns;
    _brick_rows = brick_rows;
    _lives = lives;
    
    //Initialising the game's classes with the relevent variables
    ball.initBall(ball_size, ball_speed);
    bar.initBar(_bar_width, bar_height, bar_speed);
    bricks.initBrick(_brick_width, _brick_height, _brick_columns, _brick_rows, _gap_x, _gap_y);
    score.init(_lives);
    
    pUps.init();
    stopLookingForLife = false;
    stopLookingForXTender = false;
    currentLoop = 0;
}


void Gameplay::refreshPositions(Gamepad &gamepad, N5110 &lcd)
{
    //Only update the gameplay if 1. There are lives remaining 
    //                        and 2. All the bricks have not yet been destryed
    if (score.livesRemaining > 0 && score.currentScore < 400 )
    {
        di = gamepad.get_direction();
        ma = gamepad.get_mag();  // in range 0.0 to 1.0
        
        //Update the ball and bar position
        ball.refreshBallPosition();
        bar.refreshBarPosition(int(10.0f*ma), di);
        keepBallOnScreen(gamepad);
        
        //Only move the extra life icon if its special brick is hit:
        if(pUps.lifeReleased == true)
        {
            pUps.refreshLifePosition();
            barCollectedXtraLife(gamepad);
        }
        
        //Only move the xTender icon if its special brick is hit:
        if(pUps.xTenderReleased == true)
        {
            pUps.refreshXTenderPosition();
            barCollectedWiderBar(gamepad);
        }
        
        //Acknowledge and react to collisions
        barBallCollision(gamepad);
        ballBrickCollision(gamepad);
    
        ballMissedBar(gamepad);
        
        //Only run methods of watching out for the powerUp-Bar collisions when the power ups are released:
        
        if(stopLookingForLife == false)
        {
            specialLifeBrickStruck(lcd);
        }
        
        if(stopLookingForXTender == false)
        {
            specialXTenderBrickStruck(lcd);
        }
    }
    
}


void Gameplay::drawItems(N5110 &lcd, Gamepad &gamepad)
{
    //Only update the screen if 1. There are lives remaining 
    //                  and 2. All the bricks have not yet been destryed
    if (score.livesRemaining > 0 && score.currentScore < 400 )
    {
        ball.drawBall(lcd);
        bricks.drawBrick(lcd);
        score.display(lcd, gamepad);
        
        //Counting the number of loops as a measure of time during which the bar is extended, then reduces the width back to 9
         if ( (currentLoop + 80) < bar.incrNum )
        {
            bar.setBarWidth(9);
        }
        bar.drawBar(lcd);
    
        lcd.drawLine(0,2,0,42,1);   //left wall
        lcd.drawLine(83,2,83,42,1); //right wall
        lcd.drawLine(2,0,81,0,1);   //top wall
        
        //Only draw the extra life icon if its special brick is hit:
        if(pUps.lifeReleased == true)
        {
            pUps.drawLife(lcd);
        }
        
        //Only draw the xTender icon if its special brick is hit:
        if(pUps.xTenderReleased == true)
        {
            pUps.drawXTender(lcd);
        }
        
    } else 
    {
     //Game Over method is called if all lives are lost or all bricks are destroyed. 
     score.gameOver(lcd, gamepad); // This method loops until 'Y' button is pressed
     
     //Now that button 'Y' is pressed, initialise the game to restart
     printf("Game Restarting \n");
     initGame(2,2,9,2,0.5,2,2,7,2,8,5,3);
    }
}


// To make the ball rebound off the 3 walls:
void Gameplay::keepBallOnScreen(Gamepad &gamepad)
{
    ballPosition = ball.current_position();
    ballVelocity = ball.current_velocity();
    
    if (ballPosition.x < 1)
    {
        ballPosition.x = 1;
        ballVelocity.x *= -1;    
    } else if (ballPosition.x > 81)
    {
        ballPosition.x = 81;
        ballVelocity.x *= -1;    
    } else if (ballPosition.y < 1)
    {
        ballPosition.y = 1;
        ballVelocity.y *= -1;    
    }
    
    //Update the ball's pos and vel
    ball.set_velocity(ballVelocity);
    ball.set_position(ballPosition);
    
}


// Making the ball rebound off the bar:
void Gameplay::barBallCollision(Gamepad &gamepad)
{
    barPosition = bar.current_position();
    
    if(ballPosition.x>=barPosition.x 
        && ballPosition.x<(barPosition.x+9)
        && ballPosition.y>(barPosition.y-2))
    {
        ballPosition.y = (barPosition.y-2);
        ballVelocity.y *= -1;
            
        gamepad.tone(1100.0,0.1);
  
    }
    
    ball.set_velocity(ballVelocity);
    ball.set_position(ballPosition);
}


void Gameplay::ballMissedBar(Gamepad &gamepad)
{
    barPosition = bar.current_position();
    
    if( ballPosition.y > (barPosition.y + 5)
        && ( ballPosition.x<barPosition.x || ballPosition.x>(barPosition.x+_bar_width) ) )
        {
            score.lostLife(gamepad);    //Calling a method to lose a life
            ballPosition.y = (barPosition.y-2);     //Restarting the ball's position
            ballPosition.x = (barPosition.x+4); 
        }
        
    ball.set_position(ballPosition);
}




// Acknowledging and reacting to a ball-brick collision:
void Gameplay::ballBrickCollision(Gamepad &gamepad)
{
    ballPosition = ball.current_position();
    ballVelocity = ball.current_velocity();
    
    //This is a mathematical method to know which brick has been hit by the ball:
    
    //Inverse of formula used to place bricks in Bricks.cpp:
    scaledBallPos.x = ((ballPosition.x - 5)/(_brick_width + _gap_x));
    scaledBallPos.y = ((ballPosition.y - 5)/(_brick_height + _gap_y));
    
    /*
    Splitting the x and y ball float positions into ints before the decimal point and floats after it.
    - The int before the decimal place give the row/column coordinate of the struck brick
    - The float after the decimal place can be used to know wether the ball hit a brick or a gap between the brick
        For X -> Brick collision if less than 0.7
        For Y -> Brick collision if less than 0.5
        ^ Both have to be satisfied for a collision to be ackknowledged.
    */
    
    //Obtaining the int before the decimal place
    xBallPosInt = (long)scaledBallPos.x;
    yBallPosInt = (long)scaledBallPos.y;
    
    //Obtaining the float after the decimal place
    ballPosFraction.x = scaledBallPos.x - xBallPosInt;
    ballPosFraction.y = scaledBallPos.y - yBallPosInt;
    
    //Call at the method which hides only the brick which is hit
    hideStruckBrick(xBallPosInt, yBallPosInt, ballPosFraction, gamepad);
         
}



void Gameplay::hideStruckBrick(int xBallPosInt, int yBallPosInt, Vector2D ballPosFraction, Gamepad &gamepad)
{
    // All the criteria necessary to acknowledge a collision:
    if ( bricks.destroyed[xBallPosInt][yBallPosInt] == false    //There is a collision only if the brick hasn't been already destroyed
        && ballPosFraction.x < 0.7f                             //As explained in the previous method
        && ballPosFraction.y < 0.5f
        && xBallPosInt <= _brick_columns - 1                   // -1 since they start at 0
        && yBallPosInt <= _brick_rows - 1
        && yBallPosInt >= 0 
        && xBallPosInt >= 0 )              
    {
        printf("Collision with block ( %i, %i )\n", xBallPosInt, yBallPosInt);
        bricks.destroyed[xBallPosInt][yBallPosInt] = true;   //turning the boolean 'destroyed' to 1 when collision with specific block happens
        ballVelocity.y *= -1;                                //Rebounds the ball off the bick
        score.didHitBrick(gamepad);                          //Calls method to earn points for hitting a brick
    }
    
    ball.set_velocity(ballVelocity);
}





void Gameplay::specialLifeBrickStruck(N5110 &lcd)
{
    //Aknowledge a collision with the special brick giving an extra life   
    if ( (bricks.destroyed[pUps.rowRand1][pUps.colRand1] == true) && (pUps.lifeReleased == false) )
    {
        printf("extra life special brick struck \n");
        pUps.lifeReleased = true;
        stopLookingForLife = true;     //to stop this method from running after the special extra life brick is struck
        
    }
}

void Gameplay::specialXTenderBrickStruck(N5110 &lcd)
{   
    //Aknowledge a collision with the special brick giving a wider bar
    if ( (bricks.destroyed[pUps.rowRand2][pUps.colRand2] == true) && (pUps.xTenderReleased == false) )
    {
        printf("bar xTender special brick struck \n");
        pUps.xTenderReleased = true;
        stopLookingForXTender = true;     //to stop this method from running after the special wider bar brick is struck
        
    }
}



void Gameplay::barCollectedXtraLife(Gamepad &gamepad)
{
    
    lifePos = pUps.currentLifePosition();
    
    //if the bar catches the powerUp
    if(lifePos.y>(barPosition.y-2))
    {
        if(lifePos.x >= (barPosition.x-3) 
        && lifePos.x<(barPosition.x+_bar_width) )
        {
            printf("Got the extra life!\n");
            pUps.lifeReleased = false;   //stop drawing and moving the life icon
            score.livesRemaining ++;    //give an extra life
            
            gamepad.tone(1300.0,0.1);
            
        } else {
            pUps.lifeReleased = false;  //hide the icon if it misses the bar
        }
  
    }
}


void Gameplay::barCollectedWiderBar(Gamepad &gamepad)
{
    
    xTenderPos = pUps.currentXTenderPosition();
    
    if(xTenderPos.y > (barPosition.y-2))
    {
        if(xTenderPos.x >= (barPosition.x-3) 
        && xTenderPos.x < (barPosition.x+_bar_width) )
        {
            //if the bar catches the powerUp:
            
            printf("Got the Wider Brick!\n");
            pUps.xTenderReleased = false;   //stop drawing and moving the xTender icon
            
            bar.setBarWidth(15);
            
            //Counting the number of loops as a measure of time during which the bar is extended:
            currentLoop = bar.incrNum;
            
            gamepad.tone(1300.0,0.1);
            
        } else {
            pUps.xTenderReleased = false;   //hide the icon if it misses the bar
        }
  
    }
}
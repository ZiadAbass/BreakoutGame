#include "Ball.h"

Ball::Ball()
{

}

Ball::~Ball()
{

}



void Ball::initBall(int ball_size, int ball_speed)
{
    //Ball starts close to where the bar starts
    xpos = 42;
    ypos = 40;
    
    //Initialising ball parameters
    ballSize = ball_size;
    ballSpeed = ball_speed;
    

    //Generating a random number (0 or 1)
    srand(time(NULL));
    int randNum = rand() % 2;
    
    // The ball will move randomly in either NE or NW direction, depending on the random number:
    if (randNum == 0) {
        ballVelocity.x = ballSpeed;
        ballVelocity.y = -ballSpeed;    //NE direction

    } else {
        ballVelocity.x = -ballSpeed;
        ballVelocity.y = -ballSpeed;    //NW direction
    }
}


void Ball::drawBall(N5110 &lcd)
{
    lcd.drawRect(xpos,ypos,ballSize,ballSize,FILL_BLACK);
}


void Ball::refreshBallPosition()
{
    ypos += ballVelocity.y;
    xpos += ballVelocity.x;
    
}


void Ball::set_position(Vector2D pos)
{
    xpos = pos.x;
    ypos = pos.y;
}

void Ball::set_velocity(Vector2D vel)
{
    ballVelocity.y = vel.y;
    ballVelocity.x = vel.x;
}


Vector2D Ball::current_position()
{
    Vector2D currentP = {xpos,ypos};
    return currentP;
}


Vector2D Ball::current_velocity()
{
    Vector2D vel = {ballVelocity.x,ballVelocity.y};
    return vel;
}



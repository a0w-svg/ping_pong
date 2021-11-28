#ifndef GAME_H
#define GAME_H
#include <GL/gl.h>
// globals variables
static int WindowX = 800, WindowY = 1200;
static int OrthoX = 600, OrthoY = 400;
// game variables
static char Score1[20] = {}, Score2[20] = {};
static GLint Player1Score = 0, Player2Score = 0;
static GLint Player1Life = 3, Player2Life = 3;
static GLint PaddleBoundary = 350, PaddleHeight = 400, PaddileVelocity = 15.0;
static GLint Player1PaddileY = 0, Player2PaddileY = 0, PaddleX = 595;
static GLfloat BallVelocityX = 0, BallVelocityY = 0, SpeedIncrement = 0.1;
static GLint BallPosX = 0, BallPosY = 0, BallRadius = 20;


#endif
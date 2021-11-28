#ifndef WINDOW_H
#define WINDOW_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
void CreateWindow();
void Display(void);
void Reshape(int W, int H);
    // Draw GameObjects
void DrawBall(int X, int Y);
void drawPaddle(int X, int Y);
void DrawCenterLines();
void DrawText(char* Text, int X, int Y, int Z);
    // Input
void MouseHandler(int Button, int State, int X, int Y);
void KeyboardHandler(unsigned char Key, int X, int Y);
void Init(void);

void StartGame();
#endif

#ifndef WINDOW_H
#define WINDOW_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
// constants
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

typedef struct
{
    char r;
    char g;
    char b;
}color_t;
void CreateWindow();
void Display(void);
void Reshape(int W, int H);
    // Draw GameObjects
void DrawBall(int X, int Y);
void drawPaddle(int X, int Y);
void DrawCenterLines();
void DrawText(char* Text, int X, int Y, int Z);
    // Input
void KeyboardHandler(unsigned char Key, int X, int Y);
void KeyboardHandlerUp(unsigned char Key, int X, int Y);
void SpecialKeyHandler(int key, int x, int y);
void SpecialKeyHandlerUp(int key, int x, int y);
// game logic
void Init(void);
void StartGame();

// menu 
void CreateMenu();
void ProcessMenuEvents(int option);
#endif

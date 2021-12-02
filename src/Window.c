#include "../include/Window.h"
#include <GL/freeglut.h>
#include <stdbool.h>
// globals variables
int WindowX = 800, WindowY = 1200;
int OrthoX = 600, OrthoY = 400;
// game variables
char Score1[20] = {}, Score2[20] = {};
GLint Player1Score = 0, Player2Score = 0;
GLint Player1Life = 3, Player2Life = 3;
GLint PaddleBoundary = 290, PaddleHeight = 100, PaddileVelocity = 8.0;
GLint Player1PaddileY = 0, Player2PaddileY = 0, PaddleX = 595;
GLfloat BallVelocityX = 0, BallVelocityY = 0, SpeedIncrement = 0.5;
GLint BallPosX = 0, BallPosY = 0, BallRadius = 20;
bool pressed_keys[5];

color_t ball_color = {.r = 255, .g = 0, .b = 0};
color_t paddle_color1 = {.r = 0, .g = 255, .b = 0};
color_t paddle_color2 = {.r = 0, .g = 255, .b = 150};
void Init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // initialize display with black colors
    glShadeModel(GL_FLAT);
    srand(time(NULL));
}

void StartGame()
{
    // move the ball
    BallPosX += BallVelocityX;
    BallPosY += BallVelocityY;
    //printf("%f:%f", BallPosX, BallPosY);
    // ball hits the top or bottom 
    if(BallPosY + BallRadius > OrthoY || BallPosY - BallRadius < -OrthoY)
    {
        BallVelocityY = -BallVelocityY;
    }
    // ball hits the left paddle
    if(BallPosX - BallRadius + 5 < -PaddleX && BallPosX - BallRadius < -PaddleX)
    {
        if(BallPosY < Player1PaddileY + PaddleHeight && BallPosY > Player1PaddileY - PaddleHeight)
        {
            BallVelocityX  = -BallVelocityX;
            if(BallVelocityX < 7.0 && BallVelocityY < 7.0)
            {
                BallVelocityX += SpeedIncrement;
                BallVelocityY += SpeedIncrement;
            }
            PaddileVelocity += SpeedIncrement;
        }
        else 
        {
            Player1Score++;
            BallVelocityX = -BallVelocityX;
        }
        ball_color.r = rand()%255;
        ball_color.g = rand()%255;
        ball_color.b = rand()%255;
    }

    // ball hits the right paddle
    if(BallPosX + BallRadius - 5 > PaddleX && BallPosX - BallRadius < PaddleX)
    {
        if(BallPosY < Player2PaddileY + PaddleHeight && BallPosY > Player2PaddileY - PaddleHeight)
            BallVelocityX = -BallVelocityX;
        else
        {
             Player2Score++;
             BallVelocityX = -BallVelocityX;
        }
        ball_color.r = rand()%255;
        ball_color.g = rand()%255;
        ball_color.b = rand()%255;
    }
    // move  the player1 paddle up
    if(Player1PaddileY < PaddleBoundary && pressed_keys[1] == true)
        Player1PaddileY += PaddileVelocity;
    // move the player1 paddle down
    if(Player1PaddileY > -PaddleBoundary && pressed_keys[2] == true)
        Player1PaddileY -= PaddileVelocity;
    // move  the player2 paddle up
    if(Player2PaddileY < PaddleBoundary && pressed_keys[3] == true)
        Player2PaddileY += PaddileVelocity;
    // move  the player2 paddle down
    if(Player2PaddileY > -PaddleBoundary && pressed_keys[4] == true)
        Player2PaddileY -= PaddileVelocity;

    glutPostRedisplay();
} 
void Display(void)
{
    //StartGame();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Draw Center lines
    DrawCenterLines();
    // draw left paddle
    drawPaddle(-PaddleX, Player1PaddileY);
    // draw right paddle 
    drawPaddle(PaddleX, Player2PaddileY);
    // draw the ball 
    DrawBall(BallPosX, BallPosY);
    // draw the score on the left for player one
    snprintf(Score2, sizeof(Score2), "%d", Player2Score);
    DrawText("Player 1:", -500, 280,0);
    DrawText(Score2, -150, 280, 0);
    // draw the score on the right for player 2
    snprintf(Score1, sizeof(Score1), "%d", Player1Score);
    DrawText("Player 2:", 100, 280,0);
    DrawText(Score1, 450, 280, 0);
    // swap the current frame with drawn frame
    glutSwapBuffers();
    glFlush();
}
void Reshape(int W, int H)
{
    glViewport(0, 0, (GLsizei)W, (GLsizei)H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-OrthoX, OrthoX, -OrthoY, OrthoY, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
    // Draw GameObjects
void DrawBall(int X, int Y)
{
    
    glPushMatrix();
    glTranslatef(X, Y, 0);
    glColor3ub(ball_color.r, ball_color.g, ball_color.b);
    glutSolidSphere(BallRadius, 20, 16);
    glPopMatrix();
}
void drawPaddle(int X, int Y)
{
    glPushMatrix();
    glTranslatef(X, Y, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    int height = PaddleHeight ;/// 2;
    glVertex2f(-5, height);
    glColor3f(1.0, 0.99, 1.0);
    glVertex2f(5, height);
    glColor3f(1.0, 0.99, 0.0);
    glVertex2f(5, -height);
    glColor3f(1.0, 1.1, 0.0);
    glVertex2f(-5, -height);
    glEnd();
    glPopMatrix();
}

// draw the center lines spaces 20 px apart and with a width of 4px
void DrawCenterLines()
{
    // center lines start;
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -410);
    glVertex2f(2, -410);
    glVertex2f(2, -390);
    glVertex2f(-2, -390);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -370);
    glVertex2f(2, -370);
    glVertex2f(2, -350);
    glVertex2f(-2, -350);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -330);
    glVertex2f(2, -330);
    glVertex2f(2, -310);
    glVertex2f(-2, -310);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -290);
    glVertex2f(2, -290);
    glVertex2f(2, -270);
    glVertex2f(-2, -270);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -250);
    glVertex2f(2, -250);
    glVertex2f(2, -230);
    glVertex2f(-2, -230);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -210);
    glVertex2f(2, -210);
    glVertex2f(2, -190);
    glVertex2f(-2, -190);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -170);
    glVertex2f(2, -170);
    glVertex2f(2, -150);
    glVertex2f(-2, -150);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -130);
    glVertex2f(2, -130);
    glVertex2f(2, -110);
    glVertex2f(-2, -110);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -90);
    glVertex2f(2, -90);
    glVertex2f(2, -70);
    glVertex2f(-2, -70);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -50);
    glVertex2f(2, -50);
    glVertex2f(2, -30);
    glVertex2f(-2, -30);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, -10);
    glVertex2d(2, -10);
    glVertex2d(2, 10);
    glVertex2d(-2, 10);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 30);
    glVertex2f(2, 30);
    glVertex2f(2, 50);
    glVertex2f(-2, 50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 70);
    glVertex2f(2, 70);
    glVertex2f(2, 90);
    glVertex2f(-2, 90);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 110);
    glVertex2f(2, 110);
    glVertex2f(2, 130);
    glVertex2f(-2, 130);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 150);
    glVertex2f(2, 150);
    glVertex2f(2, 170);
    glVertex2f(-2, 170);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 190);
    glVertex2f(2, 190);
    glVertex2f(2, 210);
    glVertex2f(-2, 210);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 230);
    glVertex2f(2, 230);
    glVertex2f(2, 250);
    glVertex2f(-2, 250);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 270);
    glVertex2f(2, 270);
    glVertex2f(2, 290);
    glVertex2f(-2, 290);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 310);
    glVertex2f(2, 310);
    glVertex2f(2, 330);
    glVertex2f(-2, 330);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 350);
    glVertex2f(2, 350);
    glVertex2f(2, 370);
    glVertex2f(-2, 370);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2, 390);
    glVertex2f(2, 390);
    glVertex2f(2, 410);
    glVertex2f(-2, 410);
    glEnd();
    // center lines end
}
void DrawText(char* Text, int X, int Y, int Z)
{
    glPushMatrix();
    glColor3f(0.6, 0.6, 1.0);
    glTranslatef(X, Y+8, Z);
    glScalef(0.5,0.5,1);
    glutStrokeString(GLUT_STROKE_ROMAN, Text);
    glPopMatrix();
}

void KeyboardHandler(unsigned char Key, int X, int Y)
{
    switch (Key)
    {
    // move player one paddile up    
    case 'w':
        pressed_keys[1] = true;
        break;
    // move player one paddile down
    case 's':
        pressed_keys[2] = true;
        break;
    case ' ':
        BallVelocityX = 4;
        BallVelocityY = 4;
        glutIdleFunc(StartGame);
        break;
    // exit on esc
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void KeyboardHandlerUp(unsigned char Key, int X, int Y)
{
    switch(Key)
    {
        // move player one paddile up    
        case 'w':
            pressed_keys[1] = false;
            break;
    // move player one paddile down
        case 's':
            pressed_keys[2] = false;
            break;
        default:
            break;
    }
}
void SpecialKeyHandler(int key, int x, int y)
{
    switch(key)
    {
        // set the  move the player 2 paddle up flag
        case GLUT_KEY_UP: 
            pressed_keys[3]  = true;
            break;
        //set the  move the player 2 paddle down flag
        case GLUT_KEY_DOWN:
            pressed_keys[4] = true;
            break;
        default:
            break;
    }

}
void SpecialKeyHandlerUp(int key, int x, int y)
{
    switch(key)
    {
        // release the  move the player 2 paddle up flag
        case GLUT_KEY_UP: 
            pressed_keys[3]  = false;
            break;
        // release the  move the player 2 paddle down flag
        case GLUT_KEY_DOWN:
            pressed_keys[4] = false;
            break;
        default:
            break;
    }

}

void CreateMenu()
{
    int menu;
    // create the menu and set the function to handle the events
    menu  = glutCreateMenu(ProcessMenuEvents); 
    // menu entries
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Green", GREEN);
    glutAddMenuEntry("Orange", ORANGE);
    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ProcessMenuEvents(int option)
{
   /* switch(option)
    {
        case RED:
            red = 1.0f;
    }
    */
}
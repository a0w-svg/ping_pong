#include "../include/Window.h"
#include "../include/Game.h"
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
        BallVelocityY = -BallVelocityY;
    // ball hits the left paddle
    if(BallPosX - BallRadius + 5 < -PaddleX && BallPosX - BallRadius < -PaddleX)
    {
        if(BallPosY < Player1PaddileY + PaddleHeight && BallPosY > Player1PaddileY - (PaddleHeight/2))
        {
            BallVelocityX  = -BallVelocityX;
            BallVelocityX += SpeedIncrement;
            BallVelocityY += SpeedIncrement;
            PaddileVelocity += SpeedIncrement;
        }
    }

    // ball hits the right paddle
    if(BallPosX + BallRadius - 5 > PaddleX && BallPosX - BallRadius < PaddleX)
    {
        if(BallPosY < Player2PaddileY + PaddleHeight && BallPosY > Player2PaddileY - (PaddleHeight/2))
            BallVelocityX = -BallVelocityX;
    }
    // player one scores
    if(BallPosX - BallRadius > OrthoX)
    {
        Player1Score++;
        //printf("Player 1 = %d\n", Player1Score);
        BallVelocityX = -BallVelocityX;
    }
    // player two scores
    if(BallPosX + BallRadius < -OrthoX)
    {
        Player2Score++;
        //printf("Player 2 = %d\n", Player2Score);
        BallVelocityX = -BallVelocityX;
    }
    glutPostRedisplay();
} 
void Display(void)
{
    StartGame();
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw Center lines
    DrawCenterLines();
    // draw left paddle
    drawPaddle(-PaddleX, Player1PaddileY);
    // draw right paddle 
    drawPaddle(PaddleX, Player2PaddileY);
    // draw the ball 
    DrawBall(BallPosX, BallPosY);
    // draw the score on the left for player one
    snprintf(Score1, sizeof(Score1), "%d", Player1Score);
    DrawText(Score1, -300, 200, 0);
    // draw the score on the right for player 2
    snprintf(Score2, sizeof(Score2), "%d", Player2Score);
    DrawText(Score2, 200, 200, 0);
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
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(BallRadius, 20, 16);
    glPopMatrix();
}
void drawPaddle(int X, int Y)
{
    glPushMatrix();
    glTranslatef(X, Y, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    int height = PaddleHeight /  2 ;/// 2;
    glVertex2f(-5, height);
    glVertex2f(5, height);
    glVertex2f(5, -height);
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
    glTranslatef(X, Y+8, Z);
    for(char* c = Text; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void KeyboardHandler(unsigned char Key, int X, int Y)
{
    switch (Key)
    {
    // move player one paddile up    
    case 'w':
        if(Player1PaddileY < PaddleBoundary)
            Player1PaddileY += PaddileVelocity;
        glutPostRedisplay();
        break;
    // move player one paddile down
    case 's':
        if(Player1PaddileY > -PaddleBoundary)
            Player1PaddileY -= PaddileVelocity;
        glutPostRedisplay();
        break;
    case ' ':
        BallVelocityX = 1.2;
        BallVelocityY = 1.2;
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

void SpecialKeyHandler(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            if(Player2PaddileY < PaddleBoundary)
                Player2PaddileY += PaddileVelocity;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if(Player2PaddileY > -PaddleBoundary)
                Player2PaddileY -= PaddileVelocity;
            glutPostRedisplay();
            break;
        default:
            break;
    }

}
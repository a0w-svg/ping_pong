#include "../include/Window.h"
int interval = 1000/60;
void update(int value)
{
    glutTimerFunc(interval, update, 0);
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("PingPong"); 
    Init();
    //Callback functions for rendering, reshape
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutTimerFunc(interval, update, 0);
    // Callback on mouse click and keyboard input
    glutKeyboardFunc(KeyboardHandler);
    glutKeyboardUpFunc(KeyboardHandlerUp);
    glutSpecialFunc(SpecialKeyHandler);
    glutSpecialUpFunc(SpecialKeyHandlerUp);
    glutMainLoop();
    return 0;
}
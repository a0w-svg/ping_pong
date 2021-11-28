#include "../include/Window.h"
#include "../include/Game.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("PingPong");
    Init();
    //Callback functions for rendering, reshape
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    // Callback on mouse click and keyboard input
    glutKeyboardFunc(KeyboardHandler);
    glutSpecialFunc(SpecialKeyHandler);
    glutMainLoop();
    return 0;
}
// custom headers
#include "shapes.h"

using namespace std;

// cloud global variables
float cloudOneY = OUTOFTHESCREEN;
float cloudTwoY = OUTOFTHESCREEN;
float cloudThreeY = OUTOFTHESCREEN;
float cloudFourY = OUTOFTHESCREEN;
float cloudFiveY = OUTOFTHESCREEN;

// game global variables
int GAME_STATE = 0; // 0 is homepage, 1 is gamepage
int SCORE = 0;

void showText(string text, float r, float g, float b, float x, float y, float z)
{
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void moveClouds()
{
    cloud(cloudOneY, 20, 0.8, 0.5);
    cloud(cloudTwoY, -50, 0.5, 0.7);
    cloud(cloudThreeY, -50, 0.9, 0.6);
    cloud(cloudFourY, 80, 0.6, 0.8);
    cloud(cloudFiveY, -100, 0.8, 0.9);
}

void specialKeyListener(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN: //down arrow key
        break;
    case GLUT_KEY_UP: // up arrow key
        break;

    case GLUT_KEY_RIGHT:
        break;
    case GLUT_KEY_LEFT:
        break;

    case GLUT_KEY_PAGE_UP:
        break;
    case GLUT_KEY_PAGE_DOWN:
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
}

void keyboardListener(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 's':
        GAME_STATE = 1;
        break;
    case 'q':
        GAME_STATE = 0;
        break;
    case 'S':
        GAME_STATE = 1;
        break;
    case 'Q':
        GAME_STATE = 0;
        break;
    default:
        break;
    }
}

void display()
{
    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0); //color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    // postion of camera,
    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);

    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);

    // object drawing functions

    if (GAME_STATE == 0)
    {
        showText("AIRPLANE RACING", 0, 0, 0, -22, 24, 1);
        showText("Press S to start the game.", 0, 0, 0, -25, 10, 1);
        rectangle(-35, 40, 0, 70, 40, 1, 1, 1);
        plane(-5, -20, 0, 0.5);
    }
    else
    {
        showText("PRESS Q TO QUIT", 1, 1, 1, -78, 72, 1);
        rectangle(-80, 80, 0, 45, 10, 0, 0.1, 0.1);

        showText("SCORE: ", 1, 1, 1, 51, 72, 1);
        rectangle(50, 80, 0, 30, 10, 0, 0.1, 0.1);
    }

    moveClouds();
    // drawAxes();
    // drawGrid();
    background();

    //ADD this line in the end if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate()
{
    //codes for any changes in Models, Camera
    glutPostRedisplay(); // marks the current window as needing to be redisplayed
}

void init()
{
    //clear the screen
    glClearColor(0, 0, 0, 0);

    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80, 1, 1, 5000);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB); //Depth, Double buffer, RGB color

    glutCreateWindow("Airplane Racing");

    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display); //display callback function
    glutIdleFunc(animate);    //what to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);

    glutMainLoop(); //The main loop of OpenGL

    return 0;
}
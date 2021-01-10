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
bool GAME_OVER = false;
int gameOverTimer = 0;

// plane position
float planeInitialPosX = -5;
float planePosX = planeInitialPosX;
float planeShooting = false;

// bullet postions
float bulletInitialPosX;
float bulletInitialPosY = -45;
bool getBulletInitial = false;

// enemy global variable
float enemyInitialPosY = 60;
float enemyTimer = 0;

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

void resetGame(string msg)
{
    enemyInitialPosY = 60;
    enemyTimer = 0;
    GAME_OVER = true;
    GAME_STATE = 0;
    planePosX = planeInitialPosX;
    cout << msg << endl;
}

void specialKeyListener(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (GAME_STATE == 1 && planePosX < OUTOFTHESCREEN)
        {
            planePosX += 4;
        }
        break;
    case GLUT_KEY_LEFT:
        if (GAME_STATE == 1 && planePosX > -OUTOFTHESCREEN)
        {
            planePosX -= 4;
        }
        break;
    case GLUT_KEY_UP:
        if (GAME_STATE == 1)
        {
            cout << "bullet" << endl;
            SCORE += 1;
            planeShooting = true;
        }
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
        resetGame("Game Over by Quitting!");
        break;
    case 'S':
        GAME_STATE = 1;
        break;
    case 'Q':
        resetGame("Game Over by Quitting!");
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

        plane(-5, -20, 0, 0.5, 0, 0, 0, 1, 1, 1);

        if (GAME_OVER == true)
        {
            if (gameOverTimer < 1500)
            {
                showText("GAME OVER!", 1, 0, 0, -15, -65, 1);
                showText("Your Score: ", 0, 0, 0, -14, -75, 1);
                showText(to_string(SCORE), 1, 1, 1, 12, -75, 1);
                gameOverTimer += 10;
            }
            else
            {
                GAME_OVER = false;
                gameOverTimer = 0;
                SCORE = 0;
            }
        }
    }
    else
    {
        showText("PRESS Q TO QUIT", 1, 1, 1, -78, 72, 1);
        rectangle(-80, 80, 0, 45, 10, 0, 0.1, 0.1);

        showText("SCORE: ", 1, 1, 1, 51, 72, 1);
        showText(to_string(SCORE), 1, 1, 1, 72, 72, 1);
        rectangle(50, 80, 0, 30, 10, 0, 0.1, 0.1);

        if (enemyTimer < 1500)
        {
            enemyHive(-60, enemyInitialPosY, 0);
            enemyTimer += 10;
        }
        else
        {
            enemyTimer = 0;
            enemyInitialPosY -= 10;

            if (enemyInitialPosY < -10)
            {
                resetGame("Game Over by Death!");
            }
        }
        if (planeShooting == true)
        {
            if (getBulletInitial == false)
            {
                bulletInitialPosX = ((planePosX + 5.0) * (3.0 / 10.0));
                getBulletInitial = true;
            }
            if (bulletInitialPosY >= enemyInitialPosY - 30)
            {
                planeShooting = false;
                getBulletInitial = false;
                bulletInitialPosY = -45;
                float bulletOutScreen = -300;
                bullet(bulletOutScreen, -300, 1);
            }
            else
            {
                bullet(bulletInitialPosY, bulletInitialPosX, 1);
            }
        }
        plane(planePosX, -180, 0, 0.3, 0, 0, 0, 1, 1, 1);
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
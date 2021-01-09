#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

// macros
#define PI (2 * acos(0.0))
#define OUTOFTHESCREEN 200

void circle(float radius_x, float radius_y)
{
    int i = 0;
    float angle = 0.0;

    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex3f(cos(angle) * radius_x, sin(angle) * radius_y, 0);
    }
    glEnd();
}

void rectangle(float x, float y, float z, float a, float b, float red, float green, float blue)
{
    glColor3f(red, green, blue);

    glBegin(GL_QUADS);
    {
        glVertex3f(x, y, z);
        glVertex3f(x + a, y, z);

        glVertex3f(x + a, y - b, z);
        glVertex3f(x, y - b, z);
    }
    glEnd();
}

void drawAxes()
{

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    {
        glVertex3f(1000, 0, 0);
        glVertex3f(-1000, 0, 0);

        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);

        glVertex3f(0, 0, 1000);
        glVertex3f(0, 0, -1000);
    }
    glEnd();
}

void drawGrid()
{
    int i;

    glColor3f(0.6, 0.6, 0.6); //grey
    glBegin(GL_LINES);
    {
        for (i = -8; i <= 8; i++)
        {

            if (i == 0)
                continue; //SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i * 10, -90, 0);
            glVertex3f(i * 10, 90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i * 10, 0);
            glVertex3f(90, i * 10, 0);
        }
    }
    glEnd();
}

void background()
{
    int a = 100;
    glBegin(GL_QUADS);
    {
        glColor3f(0.1, 0.2, 1);
        glVertex3f(a, a, 0);
        glColor3f(0.1, 0.2, 1);
        glVertex3f(a, -a, 0);

        glColor3f(0.2, 0.7, 0.7);
        glVertex3f(-a, -a, 0);
        glColor3f(0.2, 0.7, 0.7);
        glVertex3f(-a, a, 0);
    }
    glEnd();
}

void cloud(float &initialPosY, float initialPosX, float speed, float scale)
{
    initialPosY -= speed;
    if (initialPosY < -OUTOFTHESCREEN)
    {
        initialPosY = OUTOFTHESCREEN;
    }

    glPushMatrix();
    glScalef(scale, scale, 0);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(initialPosX, initialPosY, 0),
        circle(12, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(initialPosX + 20, initialPosY, 0),
        circle(15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(initialPosX + 40, initialPosY, 0),
        circle(12, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(initialPosX + 10, initialPosY - 10, 0),
        circle(15, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(initialPosX + 30, initialPosY - 10, 0),
        circle(15, 15);
    glPopMatrix();

    glPopMatrix();
}

void plane(float x, float y, float z, float scale)
{
    glPushMatrix();
    glScalef(scale, scale, 0);

    // top
    glColor3f(0, 0.1, 0.1);
    glBegin(GL_POLYGON);
    {
        glVertex3f(x, y, z);
        glVertex3f(x + 4, y + 8, z);
        glVertex3f(x + 6, y + 8, z);
        glVertex3f(x + 10, y, z);
    }
    glEnd();

    // body
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    {
        // glColor3f(1, 1, 1);
        glVertex3f(x, y, z);
        // glColor3f(0, 0.1, 0.1);
        glVertex3f(x + 10, y, z);
        // glColor3f(0, 0.1, 0.1);
        glVertex3f(x + 10, y - 50, z);
        // glColor3f(1, 1, 1);
        glVertex3f(x, y - 50, z);
    }
    glEnd();

    // right wing
    glColor3f(0, 0.1, 0.1);
    glBegin(GL_POLYGON);
    {
        glVertex3f(x + 10, y - 10, z);
        glVertex3f(x + 38, y - 10, z);
        glVertex3f(x + 38, y - 12, z);
        glVertex3f(x + 10, y - 30, z);
    }
    glEnd();

    // bottom wing
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    {
        glVertex3f(x + 5, y - 55, z);
        glVertex3f(x + 13, y - 63, z);
        glVertex3f(x + 13, y - 65, z);
        glVertex3f(x + 5, y - 63, z);
        glVertex3f(x - 3, y - 65, z);
        glVertex3f(x - 3, y - 63, z);
    }
    glEnd();

    // bottom
    glColor3f(0, 0.1, 0.1);
    glBegin(GL_POLYGON);
    {
        glVertex3f(x + 10, y - 50, z);
        glVertex3f(x + 5, y - 60, z);
        glVertex3f(x, y - 50, z);
    }
    glEnd();

    // left wing
    glColor3f(0, 0.1, 0.1);
    glBegin(GL_POLYGON);
    {
        glVertex3f(x, y - 10, z);
        glVertex3f(x - 28, y - 10, z);
        glVertex3f(x - 28, y - 12, z);
        glVertex3f(x, y - 30, z);
    }
    glEnd();
    glPopMatrix();
}
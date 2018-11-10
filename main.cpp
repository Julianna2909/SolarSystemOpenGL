#include <iostream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>

#include <GL/glut.h>

using namespace std;
float const PI = 3.14;

float sizes[8] = {0.05, 0.1, 0.1, 0.075, 0.5, 0.4, 0.2, 0.2};
float dist[8] = {1.5, 1.8, 2.1, 2.4, 3.3, 4.5, 5.2, 5.7};
float spin = 0.0;

void init (void)
{
float pos[4] = {0,0,1.5,0.7};
float color[4] = {1,1,1,1};
float sp[4] = {0.5,0.5,0.5,0.5};
float mat_specular[] = {1,1,1,1};
    glLightfv(GL_LIGHT0, GL_SPECULAR, sp);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
}

void resize(int w,int h)
{
if (h == 0) h = 1;
float ratio=w*1.0/h;
glViewport(0,0,w,h);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluPerspective(45.0, ratio, 0.1,20);
gluLookAt( 0,0, 13, 0,0,0, 0,1,0 );
//glulook
glMatrixMode( GL_MODELVIEW );
glutIdleFunc(NULL);
}

void moving(void)
{
spin+=0.9;
if(spin>=360) spin=0;
glutPostRedisplay();
}

int rx=0,ry=0,ox=1,oy=1,r1=0;

void mouse(int button,int state,int x,int y)
{
if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){glutIdleFunc(NULL);}
if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){glutIdleFunc(moving);}
}


void mouserot(int x,int y)
{
if(ox>(-1))
    {
    ry+=x-ox;
    rx+=y-oy;
    }
    ox=x;
    oy=y;
}

void display(void)
{
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glPushMatrix();
    glPushMatrix();
            glRotatef(rx,1,0,0);
            glRotatef(ry,0,1,0);
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        for (int j = 0; j < 8; j ++){
            glBegin(GL_LINE_LOOP);
                for(int i = 0; i <= 100; i++){
                float angle = (2 * PI * i / 100);
                float x = cos(angle);
                float y = sin(angle);
                glVertex3f(dist[j]*x,0,dist[j]*y);
                }
            glEnd();
            }
 glPopMatrix();

// spin1 = spin1;
// spin2 = spin1+spin2
// spin3 = spin2 + spin3
    for (int j = 7; j >= 0; j --){
    glRotatef(spin,0.0,1.0,0.0);
    glTranslatef(0.0, 0.0, dist[j]);

    if (j == 0 || j == 7) glColor3f(0,0,1);
    if (j == 1) glColor3f(0,1,0);
    if (j == 2) glColor3f(0,1,1);
    if (j == 3) glColor3f(1,1,0);
    if (j == 4) glColor3f(1,0,1);
    if (j == 5) glColor3f(1,0,0);
    if (j == 6) glColor3f(1,1,1);

    glutSolidSphere(sizes[j],10,10);
    glTranslatef(0.0, 0.0, -dist[j]);
    }

glPopMatrix();
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER,0.1);
glColor4f(1.0,1.0,0.0, 0.5);
glutSolidSphere(1,40,40);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
glutSwapBuffers();
}

void arrow_keys (int keys,int x,int y)
{
    switch(keys){
    case GLUT_KEY_UP: glutFullScreen(); break;
    case GLUT_KEY_DOWN :glutReshapeWindow(800,600); break;
    }
}

int main(int argc, char **argv) {
glutInit(&argc, argv);
glutInitWindowPosition(50, 50);
glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
glutCreateWindow("Solar system");
glutIdleFunc(display);
glutDisplayFunc(display);
init();
glutReshapeFunc(resize);
glutMotionFunc(mouserot);
glutMouseFunc(mouse);
glutSpecialFunc(arrow_keys);
glutIdleFunc(moving);
glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);

glutMainLoop();
}

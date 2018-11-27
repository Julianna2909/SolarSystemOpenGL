#include <iostream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include <GL/glut.h>

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilut.h>
#include <IL/ilu.h>
using namespace std;
float const PI = 3.14;

float sizes[8] = {0.05, 0.1, 0.1, 0.075, 0.5, 0.4, 0.2, 0.2};
float dist[8] = {1.5, 1.8, 2.1, 2.4, 3.3, 4.5, 5.2, 5.7};
float spin = 0.0;

GLuint PlatetTex [9];
GLuint SunTex;

const char pl0[] = "he.jpg";
const char pl1[] = "hotplanet.jpg";
const char pl2[] = "earth.jpg";
const char pl3[] = "frosenplanet.jpg";
const char pl4[] = "Jupiter.jpg";
const char pl5[] = "pink.jpg";
const char pl6[] = "moon.jpg";
const char pl7[] = "Ariel-0.jpg";

const char sun[] = "sun.jpg";

int DevILInit()
{
   if ( ilGetInteger ( IL_VERSION_NUM ) < IL_VERSION )
   {
       fprintf ( stderr, "Incorrect devil.dll version\n" );
       return 0;
   }
   if ( iluGetInteger ( ILU_VERSION_NUM ) < ILU_VERSION )
   {
       fprintf ( stderr, "Incorrect ilu.dll version\n" );
       return 0;
   }
   if ( ilutGetInteger ( ILUT_VERSION_NUM ) < ILUT_VERSION )
   {
       fprintf ( stderr, "Incorrect ilut.dll version\n" );
       return 0;
   }
   ilInit();
   iluInit();
   ilutInit();
}


void initTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	PlatetTex[0] = ilutGLLoadImage((char*)pl0);
    PlatetTex[1] = ilutGLLoadImage((char*)pl1);
    PlatetTex[2] = ilutGLLoadImage((char*)pl2);
    PlatetTex[3] = ilutGLLoadImage((char*)pl3);
    PlatetTex[4] = ilutGLLoadImage((char*)pl4);
    PlatetTex[5] = ilutGLLoadImage((char*)pl5);
    PlatetTex[6] = ilutGLLoadImage((char*)pl6);
    PlatetTex[7] = ilutGLLoadImage((char*)pl7);

    SunTex = ilutGLLoadImage((char*)sun);


	//moonTex = ilutGLLoadImage((char*)moon);
}

void initLight()
{
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[]={50.0};
	GLfloat light_position[]={1.0,1.0,1.0,0.0};
	GLfloat white_light[]={1.0,1.0,1.0,1.0};

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
	glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
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
	glEnable(GL_TEXTURE_2D);
glPushMatrix();
    glPushMatrix();
            glRotatef(rx,1,0,0);
            glRotatef(ry,0,0,1);
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

     //****TEXTURES ****///
     glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	float plane_s[] = {1.0,0.0,0.0,0.0};
	float plane_t[] = {0.0,1.0,0.0,0.0};
	glTexGenfv(GL_S, GL_OBJECT_PLANE, plane_s);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, plane_t);

        //****TEXTURES ****///

    glRotatef(spin,0.0,1.0,0.0);
    glTranslatef(0.0, 0.0, dist[j]);

  //  if (j == 0 || j == 7) glColor3f(0,0,1);
  //  if (j == 1) glColor3f(0,1,0);
  //  if (j == 2) glColor3f(0,1,1);
  //  if (j == 3) glColor3f(1,1,0);
   // if (j == 4) glColor3f(1,0,1);
   // if (j == 5) glColor3f(1,0,0);
   // if (j == 6) glColor3f(1,1,1);

    //****TEXTURES ****///

    glBindTexture(GL_TEXTURE_2D,PlatetTex[j]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    //****TEXTURES ****///

    glutSolidSphere(sizes[j],20,20);
    glTranslatef(0.0, 0.0, -dist[j]);

    glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

    }

glPopMatrix();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER,0.1);

    //****TEXTURES ****///
     glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	float plane_s[] = {1.0,0.0,0.0,0.0};
	float plane_t[] = {0.0,1.0,0.0,0.0};
	glTexGenfv(GL_S, GL_OBJECT_PLANE, plane_s);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, plane_t);
    glBindTexture(GL_TEXTURE_2D,SunTex);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

        //****TEXTURES ****///

glutSolidSphere(1,40,40);

    glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

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
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
glutCreateWindow("Solar system");
glutIdleFunc(display);
glutDisplayFunc(display);

	DevILInit();
	initTexture();
    initLight();

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

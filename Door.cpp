#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#include<string.h>
#define BLACK 1, 1, 1

float r=0;
float m=2;
void glPrintf(float r, float g, float b, float x, float y, float z, char* s)
{
    glColor3f(r,g,b);
    glRasterPos3f(x,y,z);
    int i, l = strlen(s);
    for(i=0;i<l;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);
    }
    //  GLUT_BITMAP_8_BY_13
    //GLUT_BITMAP_9_BY_15
    //GLUT_BITMAP_TIMES_ROMAN_10
    //GLUT_BITMAP_TIMES_ROMAN_24
    //GLUT_BITMAP_HELVETICA_10
    //GLUT_BITMAP_HELVETICA_12
    //GLUT_BITMAP_HELVETICA_18
}

void DrawBox(float height, float width, float depth, float x, float y, float z)
{

    float a[3]={0,width/2,-(depth/2)}; //low_back_right
    float b[3]={0,-width/2,-(depth/2)}; //low_back_left
    float c[3]={0,width/2,(depth/2)}; //low_front_right
    float d[3]={0,-width/2,(depth/2)}; //low_front_left

    float e[3]={height,width/2,-(depth/2)}; //top_back_right
    float f[3]={height,-width/2,-(depth/2)}; //top_back_left
    float g[3]={height,width/2,(depth/2)}; //top_front_right
    float h[3]={height,-width/2,(depth/2)}; //top_front_left
    glPushMatrix();
    {
        glTranslatef(x,y,z);
        glBegin(GL_QUADS);
        {


            glVertex3f(e[0],e[1],e[2]);
            glVertex3f(f[0],f[1],f[2]); // top
            glVertex3f(h[0],h[1],h[2]);
            glVertex3f(g[0],g[1],g[2]);

            glVertex3f(c[0],c[1],c[2]);
            glVertex3f(d[0],d[1],d[2]); // front
            glVertex3f(h[0],h[1],h[2]);
            glVertex3f(g[0],g[1],g[2]);



            glVertex3f(a[0],a[1],a[2]);
            glVertex3f(c[0],c[1],c[2]); // right
            glVertex3f(g[0],g[1],g[2]);
            glVertex3f(e[0],e[1],e[2]);

            glVertex3f(b[0],b[1],b[2]);
            glVertex3f(d[0],d[1],d[2]); // left
            glVertex3f(h[0],h[1],h[2]);
            glVertex3f(f[0],f[1],f[2]);
        }glEnd();

    }
}

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera is looking?
	//3. Which direction is the camera's UP direction?

	//instead of CONSTANT information, we will define a circular path.
//	gluLookAt(-30,-30,50,	0,0,0,	0,0,1);


	gluLookAt(.1, 0, 150,		0,0,0,		0,0,1);
	//NOTE: the camera still CONSTANTLY looks at the center
    glPrintf(1,0,0,-60,-60,0,"Example code for text display");
    glPrintf(0,.7,0,-50,-60,0,"Press 1 to open");
    glPrintf(.6,.1,.4,-40,-60,0,"Press 0 to close");


    glPushMatrix();
    {

        glRotatef(r,1,0,0);
        //glPushMatrix();
        //{

        //}glPopMatrix();

        glColor3f(1,.2,0);
        DrawBox(70,40,5,-25,-20,0); // Door
        glTranslatef(30,-15,3);
        glColor3f(.8,0,0); //handle
        glutSolidSphere(2.5,30,30);


    }glPopMatrix();

    glColor3f(.8,0,0);
    glPushMatrix();
    {
        DrawBox(5,42.5,5,-30,-20,0);

    }glPopMatrix();
    glPushMatrix();
    {
        DrawBox(5,42.5,5,45,-20,0);
    }glPopMatrix();
    glPushMatrix();
    {
        DrawBox(80,5,5,-30,-42.5,0);
    }glPopMatrix();
    glPushMatrix();
    {
        DrawBox(80,5,5,-30,2.5,0);
    }glPopMatrix();

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Camera

		// camera will rotate at 0.1 radians per frame.
		//r+=0.06;
		glutPostRedisplay();

	//codes for any changes in Models

	//MISSING SOMETHING?
}

void init(){

	//clear the screen
	glClearColor(BLACK, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70,	1,	0.1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':	//reverse the rotation of camera
			if(r>=-90)
            {
                r-=m;
                glutPostRedisplay();
            }
			break;

		case '0':	//increase rotation of camera by 10%
			if(r<=0)
            {
                r+=m;
                glutPostRedisplay();
            }
			break;
		default:
			break;
	}
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)


	glutKeyboardFunc(keyboardListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

//main.cpp
//Displaying main.cpp.


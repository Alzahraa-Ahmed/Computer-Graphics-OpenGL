#include <iostream>
#include <cmath>

#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>

#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


using namespace std;

//Called when a key is pressed

void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y)
{    //The current mouse coordinates

    switch (key) {

        case 27: //Escape key
            exit(0); //Exit the program

    }
}


//Initializes 3D rendering
void initRendering() {

    //Makes 3D drawing work when something is in front of something else

    glEnable(GL_DEPTH_TEST);
}


//Called when the window is resized
void handleResize(int w, int h) {

    //Tell OpenGL how to convert from coordinates to pixel values

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

//Set the camera perspective

    glLoadIdentity(); 		//Reset the camera

    gluPerspective(45.0,   	//The camera angle

                   (double)w / (double)h, //The width-to-height ratio

                   1.0,     //The near z clipping coordinate

                   200.0);     //The far z clipping coordinate
}



//Draws regular polygon given the radius of the touching excircle.
void regularPolygon(int noEdges, float radius, float orienationAngle){

    float angle = (2*3.14f)/noEdges;
    float x = 0.0f, y = radius;
    float lastX, lastY;

    glRotatef(orienationAngle, 0.0f,0.0f, 1.0f);

    glBegin(GL_POLYGON);

    while(noEdges--){
        glVertex3f(x, y, 0.0f);
        lastX= x; lastY = y;
        x = lastX*cos(angle)+ lastY*sin(angle);
        y = -1*lastX*sin(angle)+lastY*cos(angle);
    }

    glEnd();

}

//Draws the 3D scene
void drawScene() {
    //Clear information from last draw

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective

    glLoadIdentity(); //Reset the drawing perspective
    glPushMatrix();
    glTranslatef(-3.0f, 5.0f, -18.0f);
    regularPolygon(5, 1.5f, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, 5.0f, -18.0f);
    regularPolygon(6, 1.5f, 180/6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, -18.0f);
    regularPolygon(7, 1.5f, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, 0.0f, -18.0f);
    regularPolygon(8, 1.5f, 180/8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0f, -5.0f, -18.0f);
    regularPolygon(9, 1.5f, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, -5.0f, -18.0f);
    regularPolygon(10, 1.5f, 180/10);
    glPopMatrix();

    glutPostRedisplay();

    glutSwapBuffers();
    //Send the 3D scene to the screen

}


int main(int argc, char** argv) {

    //Initialize GLUT

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(500, 600); //Set the window size

    //Create the window
    glutCreateWindow("Regular polygons");

    initRendering(); //Initialize rendering

    //Set handler functions for drawing, keypresses, and window resizes
    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeypress);

    glutReshapeFunc(handleResize);


    glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.

    return 0; //This line is never reached
}

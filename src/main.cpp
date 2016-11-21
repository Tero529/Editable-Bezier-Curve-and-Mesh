/*! \file main.cpp
 * \brief Main Function for Curve and Surface Rendering
 *
 * Open a bank blakc screen which provides space for an editable bezier curve. 
 * Left click to add a point, press d to enter into dragging mode, right click to remove a control point.
 * upon clicking escape, drawing window is closed, surface of revolution of curve is obtained and saved as an OFF file.
 */

#include<GLUT/glut.h> // Support for OpenGL windowing and Callbacks
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"bezier.hpp"
#include "task2.hpp"
#include"task34.hpp"

//!Initialise Draw Settings
void Init();

//! Function to render objects to screen, main display function
void render(void);


/*! \brief Displays Control Point
*
*  Draws the control point to screen in a + fashion as a series of point
*  above and below the specified control point.
*/
 void drawPoint(std::pair<int,int> point);


//! Startpoint of Application
int main(int argc,char **argv){
    
    WIDTH=1280;
    HEIGHT=720;
    
    /*! Uses GLUT to initiliaze window with the created WIDTH
     *and HEIGHT and places window at top left of screen
     */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);//
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Bezier Curves"); //Window Title
    
    
    /*! Initialise Drawing settings wiith Init() */
    Init();
    
    glutDisplayFunc(render); // Registering function to display tree
    glutKeyboardFunc(keyFunctions);// Registering key callback function
    glutMouseFunc(mouseFunctions);//Register Mouse Function to register clicks
    glutMotionFunc(motionFunctions);//Register movement function to register dragging
    
    glutMainLoop(); //Main graphics loop which polls for events
    return 0;
}


void render(void){
    glClear(GL_COLOR_BUFFER_BIT);// Set Background
    
    
    //!Draws line along covex hull of curve using a stippled line drawing primitive and the points in the Point Vector
    glColor3f(1.0,0.0,0.0);// Set color of convex hull to Red
    glLineStipple(1, 0x00FF);//Draw a dotted line (
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    
    //Extract and draw points from the points vector
    for(std::pair<float,float> po :Points){
        glVertex2f(po.first,po.second);
    }
    
    glEnd();
    
    //! \n Then draws the curve in white using the De Castlejau recursive alogrithm
    glColor3f(1.0,1.0,1.0);//St color of curve to draw as White

    glBegin(GL_POINTS);

    // resolution of 10,000 points in the curve
    for(float t=1;t<10000.0f;t+=1.0f){
        
        std::pair<int,int> temp;
    
        temp=bezier(Points,(t/9999.0f));//Call the de castlejau algorithm in "bezier.hpp"
        
        glVertex2f(temp.first,temp.second);// Draw point gotten from the algorithm
        
        //Drawing the Control Point
        for(std::pair<int,int> point :Points){
            drawPoint(point);
        }
        
    }
    
    glEnd();
    glFlush();
    
}

void drawPoint(std::pair<int,int> point){
    
    for(int i=0;i<6;i++){
        glVertex2f(point.first,point.second-i);
        glVertex2f(point.first+i,point.second);
        glVertex2f(point.first-i,point.second);
        glVertex2f(point.first,point.second+i);
        
    }
}

void Init(){
    /*! Both Background and Drawing colour are set to Black
     *  The drawing mode is set to projection in orthographic mode
     *  with size equal to that of the window
     */
    glClearColor(0.0,0.0,0.0,0.0);//Black as Background Color
    glColor3f(0.0,0.0,0.0);//Black as draw color Color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH,0,HEIGHT);
}

/*! \file mainWS.c
 * \brief Main Driver for Wethrerell Shannon Drawing
 */

#include<GLUT/glut.h> // Support for OpenGL windowing and Callbacks
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"bezier.hpp"

//!Initialise Draw Settings
void Init();

//! Function to render objects to screen
void render(void);
void putPixel(float x, float y);
void drawPoint(std::pair<int,int> point);


//! Key Callback Functions
/*! Function sets a key callback for the escape key,
 *  so that the application quits whenever the user
 *  pressed the escape key
 */
/*! \param key The key pressed on the keyboard
 * \param x X-coordinate of mouse when key is pressed
 * \param y Y-coordinate of mouse when key is pressed
 */
void keyFunctions(unsigned char key,int x, int y);

void mouseFunctions(int button,int state,int x, int y);

void motionFunctions(int x,int y);
void passiveMotionFunctions(int x,int y);

int oldX,oldY;
int px,py;
bool valid=false;
bool first=true;
std::vector<std::pair<float, float> >::iterator save;


bool keys[1024];




std::vector<std::pair<float, float> > Points;



float WIDTH, //!< Window WIDTH,
HEIGHT; //!< Window HEIGHT


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
    
    
    /*! Then Initialise Drawing settings wiith Init() */
    Init();
    
    glutDisplayFunc(render); // Registering function to display tree
    glutKeyboardFunc(keyFunctions);// Registering key callback function
    glutMouseFunc(mouseFunctions);
    glutMotionFunc(motionFunctions);
    glutPassiveMotionFunc(passiveMotionFunctions);
    
    glutMainLoop(); //Main graphics loop which polls for events
    return 0;
}

void keyFunctions(unsigned char key,int x,int y){
    /*! polls for event when pressed key==27 */
    if(key==27)//27 corresponds to escape in ASCII
        exit(0); //Exit program is escape key is pressed
    keys[key] = !keys[key];
    std::cout<<key;
}

void mouseFunctions(int button,int state,int x,int y){
    
    oldX=x;
    oldY=y;
    valid= state==GLUT_DOWN;
    if(state==GLUT_UP)
        first=true;
    
    if(state==GLUT_DOWN && button == GLUT_LEFT_BUTTON && !keys['d']){

        Points.push_back(std::make_pair(x,HEIGHT-y));
        glutPostRedisplay();
    }
    
    if(state==GLUT_DOWN && button == GLUT_RIGHT_BUTTON){
        
        std::vector<std::pair<float, float> >::iterator it= Points.begin();
        
        for(;it!=Points.end();it++){
            if( (abs((int)(*it).first -x) <5 ) && (abs((int)(*it).second -(HEIGHT-y)) < 5)){
                Points.erase(it);
                glutPostRedisplay();
                break;
            }
        }
    }
}

void motionFunctions(int x,int y){
    px=x;
    py=y;
    if(first){
    if(valid && keys['d']){
        save=Points.begin();
        for(;save!=Points.end();save++){
            if( (abs((int)(*save).first -oldX) <3 ) && (abs((int)(*save).second -(HEIGHT-oldY)) < 3)){
                (*save).first=px;
                (*save).second=HEIGHT-py;
                glutPostRedisplay();
                first=false;
                break;
            }
        }
    }
    }
    else{
        (*save).first=px;
        (*save).second=HEIGHT-py;
        glutPostRedisplay();
    }
}

void passiveMotionFunctions(int x,int y){
        
}


void render(void){
    glClear(GL_COLOR_BUFFER_BIT);// Set Background
    
    
    glColor3f(1.0,1.0,1.0);//White
    glBegin(GL_POINTS);
    
    for(float t=1;t<10000.0f;t+=1.0f){
        std::pair<int,int> temp;
        temp=bezier(Points,(t/9999.0f));
        glVertex2f(temp.first,temp.second);
        
        for(std::pair<int,int> point :Points)
            drawPoint(point);
        
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

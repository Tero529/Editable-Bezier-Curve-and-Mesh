/*! \file
 * \brief Adding fucurve editabillity functionality using the mouse and keyboard
 *
 * Allows the user to interact with the bezier curve being drawn in one of three ways. \n
 * Add a control point by using left key
 * Delete a contorl point using a right click in a 5 pixel vicinity of the point
 * Enable dragging mode by clicking the d key and then dragging using a held down left click.
 */
#ifndef TASK2_HPP
#define TASK2_HPP
#include"task34.hpp"

//! Key Callback Functions
/*! Function sets a key callback for the escape key,
 *  so that the application quits whenever the user
 *  pressed the escape key after outputting surface of revolution of the curve to an OFF file.
 */
/*! \param key The key pressed on the keyboard
 * \param x X-coordinate of mouse when key is pressed
 * \param y Y-coordinate of mouse when key is pressed
 */
void keyFunctions(unsigned char key,int x, int y);

/*! \brief Registers Clicks and responds to them by adding/deleting/dragging control points
 */
void mouseFunctions(int button,int state,int x, int y);

/*! \brief Takes care of draggin functionality
 *
 *  First checks whether dragging has just begun or is in progres.
 *  If it in progress then updates the point specified by the save std::pair.
 * Otherise checks to see if the mouse is pressed, the dragging mode is enable( by the d key)
 * and cursor is in the 5 pixel vicinity of any point. Finds and saves this point in the point "pair"
 */
void motionFunctions(int x,int y);

int oldX, //!<Original x value of point being dragged
    oldY; //!<Original y value of point being dragged

int px,py;

bool valid=false;//!< Key which specified with a key eventis caused by is pressing(true) or releasing (false)
bool first=true;//!< Specified whether dragging has just begun (false is dragging is in progress


std::vector<std::pair<float, float> > Points;//!< Control Point List
std::vector<std::pair<float, float> >::iterator save;//!< To save the pointer to the point being currently dragged


bool keys[1024];//!< Keep track of currently toggled keys

float WIDTH, //!< Window WIDTH,
HEIGHT; //!< Window HEIGHT



void motionFunctions(int x,int y){
    px=x;
    py=y;
    
    //If draggins is in progress first=false
    if(first){
        //Check is mouse is pressed and dragging mode is toggled to on.
        if(valid && keys['d']){
            save=Points.begin();
            //Look for point being dragged in list of control points, save and update it.
            for(;save!=Points.end();save++){
                //5 Pixel Linear vicinity
                if( (abs((int)(*save).first -oldX) <5 ) && (abs((int)(*save).second -(HEIGHT-oldY)) < 5)){
                    (*save).first=px;
                    (*save).second=HEIGHT-py;
                    glutPostRedisplay();//Render with udpated control point
                    first=false;
                    break;
                }
            }
        }
    }
    else{ //If point is already being dragged, simply update
        (*save).first=px;
        (*save).second=HEIGHT-py;
        glutPostRedisplay(); //Render with updated control points.
    }
}


void keyFunctions(unsigned char key,int x,int y){
    /*! polls for event when pressed key==27 */
    if(key==27){//27 corresponds to escape in ASCII
        sample(Points);// Proceed to create surface of revolution and write to OFF file.

        exit(0); //Exit program is escape key is pressed
    }
    keys[key] = !keys[key];
    
    glutPostRedisplay();
}


void mouseFunctions(int button,int state,int x,int y){
    
    oldX=x;
    oldY=y;
    
    valid= state==GLUT_DOWN; //! Any operation is valid only is event is caused by a mouse press and not a mouse release
    
    if(state==GLUT_UP)//! A mouse release signifies that dragging operation has ended if in dragging mode
        first=true;
    
    if(state==GLUT_DOWN && button == GLUT_LEFT_BUTTON && !keys['d']){ //! Adds a new control point at the end of point list if the dragging mode is not enabled using the d key on a LEFT click.
        
        Points.push_back(std::make_pair(x,HEIGHT-y));
        glutPostRedisplay();
    }
    
    if(state==GLUT_DOWN && button == GLUT_RIGHT_BUTTON){ //! It looks for and removes a point in a 5 pixel vicinity on a right click on the canvas.
        
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

#endif


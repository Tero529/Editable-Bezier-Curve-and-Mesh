/*! \file
 * \brief Produces surface of revolution and OFF file of final curve
 *
 * Takes as input the control points of the final curve, as the user quits the editable application, 
 * uses them to create a surface of revolution for a curve sampled at t=0.1 and a 10 degree rotation sample
 * This surface is stored in a vertex-face mesh data structure and ouputted in an OFF format
 * The ouput should be redirected to desired file in the command prompt
 */
#ifndef TASK34_HPP
#define TASK34_HPP

#include<vector>
#include<utility>
#include<iostream>
#include<string.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define POINTS_PER_CURVE 10
#define DEGREES_PER_ROTATION 10

/*! \brief Mesh Data Structure
 */
struct TriangleMesh{
    std::vector<std::tuple<float,float,float> > vertexList; //List of Vertices in Polygon Mesh
    std::vector<std::tuple<int,int,int> > faceList; //!<List of triangular faces containining indices of vertices in counter clockwise order
}Surface;//!< Our Mesh Object;

/*! \brief Samples Control points ot create surface 
 *
 *  Control Points are sampled at a t values of 0.1 to create a curve
 *  The curve is rotated about the x acis a a sample degree value of 10 
 *  to create the surface of revolution
 */
void sample(std::vector<std::pair<float,float> > Points);

/*! \brief Uses sampled points and stores it as a Mesh Data Structure
 *
 *  Uses the vertices of the surface to generate faces as triangles, 
 *  with 20 faces between any two consecutive rotated curves
 */
void Store();

/*! \brief Uses mesh data structure to write in OFF format
 * 
 * Simply reads through the Surface structure and ouputs the list of vertices and their coorindates
 * Then outputs the traingular faces
 */
void Print();


void Store(){
    
    for(int i=0;i<396;i+=11){
        for(int j=i;(j-i)<POINTS_PER_CURVE;j++){
            //counter clockwise triangles amond 4 points of 2 adjacent curves , with 2 points on each curve
            Surface.faceList.push_back(std::make_tuple(j,j+1,(j+11)%Surface.vertexList.size()));
            Surface.faceList.push_back(std::make_tuple(j+1,(j+12)%Surface.vertexList.size(),(j+11)%Surface.vertexList.size()));
        }
    }
    Print();
}

void Print(){
    //Printf in OFF file format
    std::cout<<"OFF\n"<<Surface.vertexList.size()<<" "<<Surface.faceList.size()<<" "<<Surface.faceList.size() *3<<std::endl;
    
    for(std::tuple<float,float,float> point : Surface.vertexList){
        std::cout<<std::get<0>(point)<<" "<<std::get<1>(point)<<" "<<std::get<2>(point)<<std::endl;
    }
    for(std::tuple<int,int,int> face: Surface.faceList){
        std::cout<<3<<" "<<std::get<0>(face)<<" "<<std::get<1>(face)<<" "<<std::get<2>(face)<<std::endl;
    }
}




void sample(std::vector<std::pair<float,float> > Points ){
    
    glm::mat4 matrixR;
    //Sample curve at t=0.1
    for(float t=0.0f;t<1.1f;t+=.1f){
        
        std::pair<int,int> p;
        p=bezier(Points,t);
        Surface.vertexList.push_back(std::make_tuple(p.first,p.second,0.0f));
    }

    
    std::vector< std::tuple< float,float,float > > Copy = Surface.vertexList;

    //Use initial curve and sample at a rotation of 10 degrees
    for(float deg=DEGREES_PER_ROTATION;deg<360;deg+=DEGREES_PER_ROTATION){
        matrixR=glm::mat4();
        matrixR=glm::rotate(matrixR,glm::radians(deg),glm::vec3(1.0,0.0,0.0));
        
        for(std::tuple<float,float,float> p : Copy){

            glm::vec4 temp(std::get<0>(p),std::get<1>(p),std::get<2>(p),1.0f);
         //   std::cout<<"Before Rotation: "<<temp[0]<<" "<<temp[1]<<" "<<temp[2]<<" "<<temp[3]<<std::endl;

            temp=matrixR*temp;
       //     std::cout<<"After Rotation: "<<temp[0]<<" "<<temp[1]<<" "<<temp[2]<<" "<<temp[3]<<std::endl;
            Surface.vertexList.push_back(std::make_tuple(temp[0],temp[1],temp[2]));
        }
    }
    Store();
}





#endif
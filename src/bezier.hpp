/*! \file bezier.hpp
 * \brief Specifies De Castlejau's Bezier Drawing Algorthm
 */

#ifndef BEZIER_HPP
#define BEZIER_HPP

#include<iostream>
#include<vector> //For the vector STL container
#include<utility> //For the pair container


/*! \brief De Castlejau's Algorithm
 *
 * Taken an input as a list of control points and a "t" value
 * recursively generates a single ouput point on the bezier curve specified by the control points
 */
std::pair<float,float> bezier(std::vector<std::pair<float,float> > points,float t){
    
    
    //Extreme case if no control points entered
    if(points.size()==0)
        return std::make_pair(0,0);
    
    //Base case of Recursive algorithm
    if(points.size() == 1)
        return points.front();
    
    
    std::vector<std::pair<float, float> >::iterator it= points.begin();//Control Point Iterator
    std::vector<std::pair<float, float> > nextPoints;//The list to be passed on to deepre recursive level
    
    std::pair<float,float> temp; // Temporary placeholder for point before being pushed onto list.
    
    for(;(it+1)!=points.end() && (it)!=points.end();it+=1){
        
        temp.first = ((1-t)*(*it).first) + (t* (*(it+1)).first);//generate x value
        temp.second = ((1-t)*(*it).second) + (t* (*(it+1)).second); //generate y value

        nextPoints.push_back(temp);
    }
    
    return bezier(nextPoints,t);
}

#endif
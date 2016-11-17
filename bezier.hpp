#ifndef BEZIER_HPP
#define BEZIER_HPP

#include<iostream>
#include<vector> //For the vector STL container
#include<utility> //For the pair container


std::pair<float,float> bezier(std::vector<std::pair<float,float> > points,float t){
    
    if(points.size()==0)
        return std::make_pair(0,0);
    if(points.size() == 1)
        return points.front();
    
    std::vector<std::pair<float, float> >::iterator it= points.begin();
    std::vector<std::pair<float, float> > nextPoints;
    
    std::pair<float,float> temp;
    for(;(it+1)!=points.end() && (it)!=points.end();it+=1){
        temp.first = ((1-t)*(*it).first) + (t* (*(it+1)).first);
        temp.second = ((1-t)*(*it).second) + (t* (*(it+1)).second);

        nextPoints.push_back(temp);
    }
    
    return bezier(nextPoints,t);
}

#endif
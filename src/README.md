\mainpage Computer Graphics IS F311 Assignment 3
\section Contributors
 *  Varun Natu 2014A7PS841H
 *  Ayush Sharma 2014A7PS039H
 *  Akanksha Pandey 2014A7PS151H

\section Implementation
\subsection algo1 Editable Bezier Curve
A blank black canvas is created and displayed to the screen which is used to build bezier curves.
* Right clicking anywhere on the screen adds a control point and shows its effect on the bezier curve in real time.
* A left click in a 5 pixel vicinity of a control point leads to it's removal from the control point list, which is reflected in real time on the curve
* To be able to drag a point, the d key has to be pressed first to enable dragging mode after which any control point can be dragged while the right mouse key is pressed
* A convex hull of the control points is displayed as red dotted lines. 
The list of control points is converted to a bezier curve using the De Castlejau recursive algorithm
\see main.cpp bezier.hpp task2.hpp


\subsection algo2 Surface of Revolution and Mesh Generation
Once the user has finished editing his bezier curve on the given canvas, and clicks the escape key to exit the application, the curve is sampled at a t interval value of 0.1 and a surface of revolution is created by rotation about the x axis at a sampled angle of ten degrees. This surface of revolution is stored in a Triangular Vertex-Face mesh data structure and written to an ouput OFF file.
\see main.cpp task34.hpp

\subsection extra_algos Example Images
12 examples, 3 each for degrees 2,3,4,5 as a set of Curve,Mesh and OFF files can be found in the mentioned HTML page.


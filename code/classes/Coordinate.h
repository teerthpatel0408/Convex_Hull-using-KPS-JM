/**
 * @file Coordinate.h
 * @brief This file handles all basic functions for points and modification/creation of points.
 * @date 2024-04-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef COORDINATE_H
#define COORDINATE_H

#include<iostream>

using namespace std;

/**
 * @brief This class generates points on a 2D plot.
 * 
 */
class Coordinate{

  double x;
  double y;

  public:


    /**
     * @brief Constructor for class Coordinate, creates a new Coordinate object with both coordinates initialized to -1.
     * 
     */
    Coordinate(){

      this->x = -1;
      this->y = -1;
    }

    /**
     * @brief Constructor for class Coordinate, creates a new Coordinate object with coordinates set to those defined in the input.
     * 
     * @param x x coordinate for the new Coordinate object.
     * @param y y coordinate for the new Coordinate object.
     */
    Coordinate(double x,double y){

      this->x = x;
      this->y = y;
    }

    /**
     * @brief This function returns the x coordinate of the Coordinate object.
     * 
     * @return double return type.
     */
    double get_X(){

      return this->x;
    }

    /**
     * @brief This function returns the y coordinate of the Coordinate object.
     * 
     * @return double return type.
     */
    double get_Y(){

      return this->y;
    }

    /**
     * @brief Set the x and y coordinates of the Coordinate object to the values taken as input.
     * 
     * @param x Input x coordinate.
     * @param y Input y coordinate.
     */
    void set_point(double x,double y){

      this->x = x;
      this->y = y;
    }

    /**
     * @brief Set the x and y coordinates of the Coordinate object to be same as that of the input point.
     * 
     * @param pt Input point.
     */
    void set_point(Coordinate pt){

      this->x = pt.get_X();
      this->y = pt.get_Y();
    }

    /**
     * @brief Sets the x coordinate of the Coordinate object to the value taken as input.
     * 
     * @param x Input x coordinate value.
     */
    void set_X(double x){
      this->x = x;
    }

    /**
     * @brief Sets the y coordinate of the Coordinate object to the value taken as input.
     * 
     * @param y Input y coordinate value.
     */
    void set_Y(double y){

      this->y = y;
    }

    /**
     * @brief Gives us the orientation of the Coordinate object relative to the two input points. Returns 0 if the points are collinear,1 if they are in clockwise orientation and 2 if they are in anticlockwise orientation.
     * 
     * @param p1 First input point.
     * @param p2 Second input point.
     * @return int return type. 
     */
    int orientation(Coordinate p1,Coordinate p2)
    {
        int val = (p1.y - this->y)*(p2.x - p1.x) - (p1.x - this->x)*(p2.y-p1.y);
        if(val == 0) return  0;
        else if(val > 0) return 1;
        else return 2;
    }

    /**
     * @brief Gives us the suquare of the distance between our Coordinate object and the input Coordinate object.
     * 
     * @param p Input Coordinate object.
     * @return float return type.
     */
    float sq_dist(Coordinate p)
    {

      return (this->x - p.x)*(this->x - p.x) + (this->y - p.y)*(this->y - p.y);
    }

    /**
     * @brief This function returns true if our Coordinate object is equal to the input object, and returns false otherwise.
     * 
     * @param pt Input Coordinate object.
     * @return true 
     * @return false 
     */
    bool equals(Coordinate pt)
    {
      if(x == pt.x && y == pt.y)
        return true;
      else
        return false;
    }

    /**
     * @brief This function prints the coordinates of the Coordinate object.
     * 
     */
    void print()
    {
      cout<<"("<<x<<","<<y<<")";
    }
};

#endif

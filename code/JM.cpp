/**
 * @file main1.cpp
 * @author Teerth Patel
 * @author Vasu Bhadja
 * @author Manthan Patel
 * @author Darsh Nayak
 * @brief This code runs the Jarvis March Algorithm to create a convex hull.
 * @date 2024-04-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include<bits/stdc++.h>
#include <fstream>
#include<sstream>
#include<ctime>
#include "classes/List.h"
#include "classes/Coordinate.h"
#include "classes/Stack.h"
#include "classes/Pair.h"
#include "classes/utils.h"


using namespace std; 



/**
 * @brief The object of this class uses JarvisMarch algorithm to find the convex hull.
 * 
 */
class JarvisMarch
{
    List<Coordinate> points;
    int get_min_Y(List<Coordinate> points)
    {
      int i,curr_y,curr_x,index = 0;
      float min_y = points.get(0).get_Y();


      for (i=1;i<points.len();i++)
      {
        curr_y = points.get(i).get_Y();
        curr_x = points.get(i).get_X();
        if((curr_y < min_y) || (curr_y == min_y && curr_x < points.get(index).get_X())){

          min_y = curr_y;
          index = i;
        }
      }

      return index;
    }

  public:
    /**
     * @brief Constructor for the class JarvisMarch.It creates an empty list of type List<Coordinate>.
     * 
     */
    JarvisMarch(){
      points = List<Coordinate>();
    }

    /**
     * @brief accepts a list of points that make the dataset for finding the convex hull.
     * 
     * @param list It is a list of type List<Coordinate>.
     */
    void fit_set(List<Coordinate> list){
      points = list;
    }

    /**
     * @brief Takes a point and adds it to the dataset.
     * 
     * @param pt The point that is to be added to the dataset.
     */
    void add_point(Coordinate pt){
      points.insert(pt);
    }

    /**
     * @brief Computes the convex hull using Jarvis March Algo and returns a list of type List<Coordinate> containing the points of the convex hull.
     * 
     * @return List<Coordinate> The return type.
     */
    List<Coordinate> compute_hull()
    {
      if(points.len() < 3)
      {
        cout<<"Convex hull doesn't exist!!"<<endl;
        return 0;
      }

      int pt_index = get_min_Y(points);

      List<Coordinate> hull;
      int l = pt_index;
      int p = l,q;
      do{
          hull.insert(points.get(p));
          int n = points.len();
          q = (p+1)%n;
          int index = 0;
          while(index < n){
            if(points.get(p).orientation(points.get(index),points.get(q)) == 2)
              q = index;
              index = index + 1;
          }

           p = q;

      }while(p != l);

      make_result(hull,"results/results_1.csv");
      return hull;
    }
};

int main()
{
    JarvisMarch jm;
    List<Coordinate> points = make_list("points.csv");
    jm.fit_set(points);
    // int startTime = time(NULL);
    List<Coordinate> hull = jm.compute_hull();
    // int endTime = time(NULL);
    // cout << "TOTAL Execution Time : " << endTime - startTime << endl;
    hull.print();
    cout<<endl;
    cout<<endl;
}

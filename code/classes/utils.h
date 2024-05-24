/**
 * @file utils.h
 * @brief This file handles all csv file utility functions.
 * @date 2024-04-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include<bits/stdc++.h>
#include<climits>
#include<fstream>
#include<sstream>
#include "List.h"
#include "Coordinate.h"

using namespace std;

/**
 * @brief This function creates a csv file containing points as a list of Coordinates.
 * 
 * @param list List of points.
 * @param addr Address of the csv file.
 */
void make_result(List<Coordinate> list,string addr){

    fstream file;
    ostringstream str1;
    file.open(addr,ios::out);
    for(int i=0;i<list.len();i++){
      Coordinate p = list.get(i);
      file <<p.get_X()<<","<<p.get_Y()<<"\n";
    }
    file.close();
}

/**
 * @brief This function stores points in a list from a csv file and returns the list.
 * 
 * @param addr Address of the csv file.
 * @return List<Coordinate> return type.
 */
List<Coordinate> make_list(string addr){

    List<Coordinate> list;

    fstream file;
    file.open(addr);
    string line;
    while(getline(file,line,'\n')){
      istringstream templine(line);
      string data;
      int i=0;
      double a[2];
      while(getline(templine,data,',')){
          a[i] = stof(data);
          i++;
      }
      Coordinate p(a[0],a[1]);
      list.insert(p);

    }
    file.close();
    return list;
}

#endif

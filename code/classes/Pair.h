/**
 * @file Pair.h
 * @brief Pair datatype and its basic functions.
 * @date 2024-04-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PAIR_H
#define PAIR_H

#include<iostream>
using namespace std;

template<class S,class T>
/**
 * @brief Class for the Pair datatype. It contains two elements of different types.
 * 
 */
class Pair{
  public:
    S first;
    T second;

  public:
    /**
     * @brief Construct a new Pair< S, T> object.
     * 
     */
    Pair<S,T>(){
      this->first = S();
      this->second = T();
    }

    /**
     * @brief Construct a new Pair< S, T> object with initial values.
     * 
     * @param first First value.
     * @param second Second value.
     */
    Pair<S,T>(S first,T second){
      this->first = first;
      this->second = second;
    }

    /**
     * @brief Creates a pair
     * 
     * @param first First value.
     * @param second Second value.
     */
     void make_pair(S first,T second){
       this->first = first;
       this->second = second;
     }

     /**
      * @brief Print the Pair object.
      * 
      */
     void print(){

       cout<<"(";
       first.print();
       cout<<",";
       second.print();
       cout<<")";
     }

     /**
      * @brief Get the first object of the Pair object.
      * 
      * @return S return type.
      */
     S get_first(){
       return first;
     }

     /**
      * @brief Get the second object of the Pair object.
      * 
      * @return T return type.
      */
     T get_second()
     {
       return second;
     }
};
#endif

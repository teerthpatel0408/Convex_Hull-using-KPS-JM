/**
 * @file List.h
 * @brief This file handles all list operations.
 * @date 2024-04-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LIST_H
#define LIST_H

#include<iostream>
#include "Coordinate.h"
using namespace std;

template<class T>
/**
 * @brief 
 * 
 */
class List
{
  public:
    T *arr;
    int size;
    int max_size;

    public:

      /**
       * @brief Default Constructor of class list, creates a new List< T> object.
       * 
       */
      List<T>()
      {
        arr = new T[1000000];
        max_size = 1000000;
        size = 0;
      }

      /**
       * @brief Constructor of class list, creates a new list<T> object with the maximum size of list initialized to the input value.
       * 
       * @param max_size Input parameter for max_size.
       */
      List<T>(int max_size)
      {
        arr = new T[max_size];
        this->max_size = max_size;
        size = 0;
      }

      /**
       * @brief Adds the input object to the end of the list.
       * 
       * @param t Input object.
       */
      void insert(T t){
          arr[size] = t;
          size++;
      }

      /**
       * @brief Add the input list to the end of our list.
       * 
       * @param list Input list.
       */
      void append_list(List<T> list){
        for(int i=0;i<list.len();i++){
          T temp = list.get(i);
          insert(temp);
        }
      }

      /**
       * @brief This function returns the object present at a specified index in the list.
       * 
       * @param index Input for the index value.
       * @return T return type.
       */
      T get(int index){
          T t = arr[index];
          return t;
      }

      /**
       * @brief Changes the object present at the specified index in the list to the object taken as input.
       * 
       * @param index Input for the index value.
       * @param val Input object value.
       */
      void edit(int index,T val){
          arr[index] = val;
      }

      /**
       * @brief Returns the size of the list.
       * 
       * @return int return type.
       */
      int len()
      {
        return size;
      }

      /**
       * @brief Removes the last element from the list.
       * 
       */
      void remove()
      {
        size--;
      }

      /**
       * @brief Clears the list.
       * 
       */
      void clear()
      {
        size = 0;
      }

      /**
       * @brief Swaps the objects present at the two indices takes as input.
       * 
       * @param i1 First Index.
       * @param i2 Second Index.
       */
      void swap(int i1,int i2)
      {
        T temp;
        temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
      }

      /**
       * @brief Reverses the list.
       * 
       */
      void reverse()
      {
        for(int i=0;i<size/2;i++)
        {
          T temp;
          temp = arr[i];
          arr[i] = arr[size-i-1];
          arr[size-i-1] = temp;
        }
      }

      /**
       * @brief Returns a pointer to the first element of the list.
       * 
       * @return T* return type.
       */
      T* begin(){
        return &arr[0];
      }

      /**
       * @brief Returns a pointer to the index one greater than the last element in the list.
       * 
       * @return T* 
       */
      T* end(){
        return &arr[size];
      }

      /**
       * @brief Prints the elements of the list.
       * 
       */
      void print(){

        for(int i=0;i<size;i++)
        {
          arr[i].print();
          cout<<" ";
        }
      }

};

#endif

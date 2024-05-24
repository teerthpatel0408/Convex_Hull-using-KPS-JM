/**
 * @file Stack.h
 * @brief This file handles all stack related functionalities.
 * @date 2024-04-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef STACK_H
#define STACK_H

#include<iostream>
using namespace std;

template<class T>
/**
 * @brief Class for Stack, which is a data structure that allows insertion and removal of elements from one side only(in LIFO order).
 * 
 */
class Stack{
  public:
    T *arr;
    int max_size;
    int size;
    int top;

    public:

      /**
       * @brief Default constructor for class stack, creates a new Stack< T> object.
       * 
       */
      Stack<T>(){

        max_size = 1000000;
        arr = new T[max_size];
        top = -1;
        size = 0;
      }

      /**
       * @brief Constructor for class stack, creates a new Stack< T> object with the input value as the maximum size of the stack.
       * 
       * @param max_size Input for maximum size of stack.
       */
      Stack<T>(int max_size)
      {
        this->max_size = max_size;
        arr = new T[max_size];
        top = -1;
        size = 0;
      }

      /**
       * @brief This function pushes the object p onto the top of the stack.
       * 
       * @param p Input object.
       */
      void push(T p)
      {
          try
          {
            if(size == max_size){
              throw "Stack overflow exception";
            }
            top++;
            size++;
            arr[top] = p;
          }
          catch(const char *error)
          {
            cout<<error<<endl;
            exit(0);
          }

      }

      /**
       * @brief This function pops the top element of the stack.
       * 
       * @return T return type.
       */
      T pop(){

          try{
            if(size == 0){
              throw "Stack pop exception";
            }

            top--;
            size--;

            return arr[top+1];
          }
          catch(const char *error){

            cout<<error<<endl;
            exit(0);
          }
      }

      /**
       * @brief returns the element present at the top of the stack.
       * 
       * @return T return type.
       */
      T peek(){
        try{
          if(size == 0){
            throw "Stack peek exception";
          }

          return arr[top];
        }
        catch(const char *error){
          cout<<error<<endl;
          exit(0);
        }
      }

      /**
       * @brief Returns the size of the stack.
       * 
       * @return int return type.
       */
      int len()
      {
        return size;
      }

      /**
       * @brief Returns true if stack is empty, and false otherwise.
       * 
       * @return true 
       * @return false 
       */
      bool empty(){

        if(size == 0) return true;
        else return false;
      }

      /**
       * @brief Returns the element just below the top element of the stack, if such an element exists.
       * 
       * @return T return type.
       */
      T next_to_top(){
        try{
          if(size == 1){
            throw "Stack underflow exception";
          }

          return arr[top-1];
        }
        catch(const char *error){
          cout<<error<<endl;
          exit(0);
        }

      }

      /**
       * @brief Prints all elements present in the stack.
       * 
       */
      void print(){

        for(int i=0;i<size;i++){
          cout<<arr[i]<<" ";
        }
        cout<<endl;
      }
};

#endif

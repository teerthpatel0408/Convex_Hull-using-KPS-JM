/**
 * @file main2.cpp
 * @author Teerth Patel
 * @author Vasu Bhadja
 * @author Manthan Patel
 * @author Darsh Nayak
 * @brief This code runs the KirkPatrick Seidel Algorithm to create a convex hull.
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
 * @brief The object of this class uses Kirkpatrick Seidel algorithm to find the convex hull.
 * 
 */
class KPS
{
    List<Coordinate> points;

    /**
     * @brief This function swaps 2 points.
     * 
     * @param a Input point 1.
     * @param b Input point 2.
     */
    void swap(double *a, double *b){
    	double temp = *a;
    	*a = *b;
    	*b = temp;
    }

    /**
     * @brief This function returns the position at which partition takes place.
     * 
     * @param arr Input array of x coordinates.
     * @param l Left Index.
     * @param r Right Index.
     * @param x x coordinate for which we find the y coordinate.
     * @return int return type.
     */
    int partition(double arr[], int l, int r, double x)
    {
    	int i;
    	for (i=l; i<r; i++)
    		if (arr[i] == x)
    		break;
    	swap(&arr[i], &arr[r]);


    	i = l;
    	for (int j = l; j <= r - 1; j++)
    	{
    		if (arr[j] <= x)
    		{
    			swap(&arr[i], &arr[j]);
    			i++;
    		}
    	}
    	swap(&arr[i], &arr[r]);
    	return i;
    }

    /**
     * @brief This function returns the Median of all x coordinates in the input array.
     * 
     * @param arr Input array of x coordinates.
     * @param n Size of the array.
     * @return double rturn type.
     */
    double findMedian(double arr[], int n)
    {
    	sort(arr, arr+n);
    	return arr[n/2];
    }

    /**
     * @brief This function returns the absolute value of the given number.
     * 
     * @param a Input number.
     * @return double return type.
     */
    double abs_value(double a)
    {
      if(a < 0) 
        return 0-a;
      else 
        return a;
    }

    /**
     * @brief This function returns the kth smallest element in the input array.
     * 
     * @param arr Input array of x coordinates.
     * @param l Left Index.
     * @param r Right Index.
     * @param k Input index value.
     * @return double return type.
     */
    double kthSmallest(double arr[], int l, int r, int k){

    	if (k > 0 && k <= r - l + 1)
    	{
    		int n = r-l+1;

    		int i;
            double median[(n+4)/5];
    		for (i=0; i<n/5; i++)
    			median[i] = findMedian(arr+l+i*5, 5);
    		if (i*5 < n)
    		{
    			median[i] = findMedian(arr+l+i*5, n%5);
    			i++;
    		}

    		double medOfMed = (i == 1)? median[i-1]:kthSmallest(median, 0, i-1, i/2);

    		int pos = partition(arr, l, r, medOfMed);


    		if (pos-l == k-1)
    			return arr[pos];
    		if (pos-l > k-1)
    			return kthSmallest(arr, l, pos-1, k);


    		return kthSmallest(arr, pos+1, r, k-pos+l-1);
    	}
    	return INT_MAX;
    }

    /**
     * @brief This function returns a list of all points whose x coordinate is neither minimum nor maximum in the set, regardless of upper hull or lower hull.
     * 
     * @param p1 Point with the minimum x coordinate.
     * @param p2 Point with the maximum x coordinate.
     * @param points List of all the input points.
     * @param flag Control medium to see if we want to comput upper hull or lower hull. It is set to false for upper hull and true in case of lower hull.
     * @return List<Coordinate> return type.
     */
    List<Coordinate> get_T(Coordinate p1,Coordinate p2,List<Coordinate>* points,bool flag)
    {
      List<Coordinate> upper_T;
      double x1 = p1.get_X();
      double x2 = p2.get_X();
      double y1 = p1.get_Y();
      double y2 = p2.get_Y();

      double slope = (y1-y2)/(x1 - x2);

      int index = 0;
      int l = points->len();
      while(index < l)
      {
        Coordinate curr_point = points->get(index);

        if(curr_point.get_X() > x1 && curr_point.get_X() < x2 )
        {
          double curr_slope = (y1-curr_point.get_Y())/(x1 - curr_point.get_X());
          if(flag == false)
          {
             if(curr_slope > slope)
              upper_T.insert(curr_point);
          }
          else{
            if(curr_slope < slope){
              upper_T.insert(curr_point);
            }
          }
        }
        index++;
      }
      upper_T.insert(p1);
      upper_T.insert(p2);

      return upper_T;
    }

    /**
     * @brief This function returns the upper bridge(needed for upper hull).
     * 
     * @param points List of all input points.
     * @param median The median of x coordinates.
     * @return Pair<Coordinate,Coordinate> return type.
     */
    Pair<Coordinate,Coordinate> computeUpperBridge(List<Coordinate>* points,double median)
    {
          int index = 0;
          int l = points->len();
          sort(points->begin(),points->end(),[](Coordinate a,Coordinate b){ return a.get_X() < b.get_X();});
          List<Coordinate> candidates(l);
          List<Pair<Coordinate,Coordinate> > pairs(l/2 +1);
          
          if(l%2==0)
          {
            while(index < l){
              Coordinate first_coordinate = points->get(index);
              Coordinate second_coordinate = points->get(index+1);

              Pair<Coordinate,Coordinate> curr_pair(first_coordinate,second_coordinate);
              pairs.insert(curr_pair);
              index+=2;
            }
          }
          else
          {
            index=1;
            candidates.insert(points->get(0));
            while(index < l)
            {
              Coordinate first_coordinate = points->get(index);
              Coordinate second_coordinate = points->get(index+1);

              Pair<Coordinate,Coordinate> curr_pair(first_coordinate,second_coordinate);
              pairs.insert(curr_pair);
              index+=2;
            }
          }
          index = 0;
          int slopes_len = pairs.len();
          double slopes[slopes_len];
          while(index < slopes_len)
          {
            Coordinate c1= pairs.get(index).get_first();
            Coordinate c2 = pairs.get(index).get_second();
            double x1 = c1.get_X();
            double x2 = c2.get_X();
            double y1 = c1.get_Y();
            double y2 = c2.get_Y();

            if(x1 == x2)
            {
              if(y1 > y2)
              {
                candidates.insert(c1);
              }
              else{
                candidates.insert(c2);
              }
              slopes[index] = INT_MAX;
            }
            else{
                double slope = (y2-y1)/(double)(x2-x1);
                slopes[index] = slope;
            }
            index++;
          }
          index =0;
          double arr[slopes_len];
          int len = 0;
          while(index < slopes_len)
          {
            if(slopes[index] != INT_MAX)
            {
              arr[len++] = slopes[index];
            }
            index++;
          }
          double median_slope;
          if(len ==1)
            median_slope = arr[0];
          else
            median_slope = kthSmallest(arr,0,len-1,(len+1)/2);

          List<Pair<Coordinate,Coordinate> > SMALL(slopes_len);
          List<Pair<Coordinate,Coordinate> > EQUAL(slopes_len);
          List<Pair<Coordinate,Coordinate> > LARGE(slopes_len);
          index = 0;
          while(index < slopes_len)
          {
            Coordinate c1= pairs.get(index).get_first();
            Coordinate c2 = pairs.get(index).get_second();
            double x1 = c1.get_X();
            double x2 = c2.get_X();
            double y1 = c1.get_Y();
            double y2 = c2.get_Y();
            if(x1 != x2)
            {
              double slope = (y2-y1)/(x2-x1);
              if(abs_value(slope - median_slope) < 0.001)
              {
                Pair<Coordinate,Coordinate> curr_pair(c1,c2);
                EQUAL.insert(curr_pair);
              }
              else if(slope < median_slope)
              {
                Pair<Coordinate,Coordinate> curr_pair(c1,c2);
                SMALL.insert(curr_pair);
              }
              else if(slope > median_slope)
              {
                Pair<Coordinate,Coordinate> curr_pair(c1,c2);
                LARGE.insert(curr_pair);
              }
            }
            index++;
          }

          index = 0;
          l = points->len();
          double max_c = INT_MIN;
          while(index < l)
          {
            double x = points->get(index).get_X();
            double y = points->get(index).get_Y();
            double curr_c = (y - (double)median_slope*x);
            if(curr_c > max_c)
            {
              max_c = curr_c;
            }
            index++;
          }

          Coordinate pmin(INT_MAX,INT_MAX);
          Coordinate pmax(INT_MIN,INT_MIN);

          index = 0;
          l = points->len();
          while(index < l)
          {
            double x = points->get(index).get_X();
            double y = points->get(index).get_Y();

            double curr_c = y - (double)median_slope*x;

            if(abs_value((double)curr_c-max_c) < 0.001)
            {
              if(x < pmin.get_X()){
                pmin.set_point(x,y);
              }
              if(x > pmax.get_X()){
                pmax.set_point(x,y);
              }
            }
            index++;
          }

          if(pmin.get_X() <= median)
          {
            if(pmax.get_X() > median)
            {
                Pair<Coordinate,Coordinate> upper_bridge(pmin,pmax);
                return upper_bridge;
            }
            else
            {
                index = 0;
                l = EQUAL.len();
                while(index < l)
                {
                Coordinate pt = EQUAL.get(index).get_second();
                candidates.insert(pt);
                index++;
                }

                index = 0;
                l = LARGE.len();
                while(index < l)
                {
                Coordinate pt = LARGE.get(index).get_second();
                candidates.insert(pt);
                index++;
                }

                index = 0;
                l = SMALL.len();
                while(index < l)
                {
                Coordinate pt1 = SMALL.get(index).get_first();
                Coordinate pt2 = SMALL.get(index).get_second();
                candidates.insert(pt1);
                candidates.insert(pt2);
                index++;
                }
                return computeUpperBridge(&candidates,median);
                }
          }
          else 
          {
            index = 0;
            l = EQUAL.len();
            while(index < l)
            {
              Coordinate pt = EQUAL.get(index).get_first();
              candidates.insert(pt);
              index++;
            }

            index = 0;
            l = LARGE.len();
            while(index < l)
            {
              Coordinate pt1 = LARGE.get(index).get_first();
              Coordinate pt2 = LARGE.get(index).get_second();
              candidates.insert(pt1);
              candidates.insert(pt2);
              index++;
            }

            index = 0;
            l = SMALL.len();
            while(index < l)
            {
              Coordinate pt = SMALL.get(index).get_first();
              candidates.insert(pt);
              index++;
            }
            return computeUpperBridge(&candidates,median);
          }
          return {};
    }

    /**
     * @brief This function returns the list of points of the upper hull.
     * 
     * @param pmin Point with the minimum x coordinate.
     * @param pmax Point with the maximum x coordinate.
     * @param points List of all input points.
     * @return List<Coordinate> return type.
     */
    List<Coordinate> computeUpperHull(Coordinate pmin,Coordinate pmax,List<Coordinate>* points)
    {
        int index = 0;
        int l = points->len();
        List<Coordinate> upper_hull(l);
        
        double arr[l];
        while(index < l)
        {
          arr[index] = points->get(index).get_X();
          index++;
        }

        double median;
        if(l == 1)
          median = arr[0];
        else
          median = kthSmallest(arr,0,l-1,(l+1)/2);
        Pair<Coordinate,Coordinate> upper_bridge = computeUpperBridge(points,median);


        Coordinate cl = upper_bridge.get_first();
        Coordinate c2 = upper_bridge.get_second();

        if(cl.get_X() > c2.get_X())
        {
          Coordinate temp(cl);
          cl.set_point(c2);
          c2.set_point(temp);
        }

        upper_hull.insert(cl);
        upper_hull.insert(c2);



        if(pmin.equals(cl)==false)
        {
          List<Coordinate> upper_T_left = get_T(pmin,cl,points,false);
          List<Coordinate> left = computeUpperHull(pmin,cl,&upper_T_left);
          upper_hull.append_list(left);
        }

        if(pmax.equals(c2)==false)
        {
          List<Coordinate> upper_T_right = get_T(c2,pmax,points,false);
          List<Coordinate> right = computeUpperHull(c2,pmax,&upper_T_right);
          upper_hull.append_list(right);
        }

        return upper_hull;
    }

    /**
     * @brief This function returns the lower bridge(needed for lower hull).
     * 
     * @param points List of all input points.
     * @param median Median of x coordinates.
     * @return Pair<Coordinate,Coordinate> return type.
     */
    Pair<Coordinate,Coordinate> computeLowerBridge(List<Coordinate>* points,double median)
    {
          int index = 0;
          int l = points->len();
          sort(points->begin(),points->end(),[](Coordinate a,Coordinate b){ return a.get_X() < b.get_X();});

          List<Coordinate> candidates(l);
          List<Pair<Coordinate,Coordinate> > pairs(l/2 +1);
          if(l%2==0)
          {
            while(index < l)
            {
              Coordinate first_pt = points->get(index);
              Coordinate second_pt = points->get(index+1);
              Pair<Coordinate,Coordinate> curr_pair(first_pt,second_pt);
              pairs.insert(curr_pair);
              index+=2;
            }
          }
          else
          {
            index++;
            candidates.insert(points->get(0));
            while(index < l)
            {
              Coordinate first_pt = points->get(index);
              Coordinate second_pt = points->get(index+1);

              Pair<Coordinate,Coordinate> curr_pair(first_pt,second_pt);
              pairs.insert(curr_pair);
              index += 2;
            }
          }
          index = 0;
          int slopes_len = pairs.len();
          double slopes[slopes_len];
          while(index < slopes_len)
          {
            Coordinate p1= pairs.get(index).get_first();
            Coordinate p2 = pairs.get(index).get_second();
            double x1 = p1.get_X();
            double x2 = p2.get_X();
            double y1 = p1.get_Y();
            double y2 = p2.get_Y();
            if(x1 == x2)
            {
              if(y1 > y2)
              {
                candidates.insert(p2);
              }
              else{
                candidates.insert(p1);
              }
              slopes[index] = INT_MAX;
            }
            else
            {
                double slope = (y2-y1)/(x2-x1);
                slopes[index] = slope;
            }
            index++;
          }
          
          index = 0;
          double arr[slopes_len];
          int len = 0;
          while(index < slopes_len)
          {
            if(slopes[index] != INT_MAX){
              arr[len++] = slopes[index];
            }
            index++;
          }

          double median_slope;
          if(len ==1)
            median_slope = arr[0];
          else
            median_slope = kthSmallest(arr,0,len-1,(len+1)/2);


          List<Pair<Coordinate,Coordinate> > SMALL(slopes_len);
          List<Pair<Coordinate,Coordinate> > EQUAL(slopes_len);
          List<Pair<Coordinate,Coordinate> > LARGE(slopes_len);

          index = 0;
          while(index < slopes_len)
          {
            Coordinate p1= pairs.get(index).get_first();
            Coordinate p2 = pairs.get(index).get_second();
            double x1 = p1.get_X();
            double x2 = p2.get_X();
            double y1 = p1.get_Y();
            double y2 = p2.get_Y();

            if(x1 != x2)
            {
              double slope = (y2-y1)/(x2-x1);
              if(abs_value(slope - median_slope) < 0.001)
              {
                Pair<Coordinate,Coordinate> curr_pair(p1,p2);
                EQUAL.insert(curr_pair);
              }
              else if(slope < median_slope)
              {
                Pair<Coordinate,Coordinate> curr_pair(p1,p2);
                SMALL.insert(curr_pair);
              }
              else if(slope > median_slope)
              {
                Pair<Coordinate,Coordinate> curr_pair(p1,p2);
                LARGE.insert(curr_pair);
              }
            }
            index++;
          }

          double min_c = INT_MAX;
          index = 0;
          l = points->len();
          while(index < l)
          {
            double x = points->get(index).get_X();
            double y = points->get(index).get_Y();
            double curr_c = (y - median_slope*x);

            if(curr_c < min_c)
            {
              min_c = curr_c;
            }
            index++;
          }

          Coordinate pmin(INT_MAX,INT_MAX);
          Coordinate pmax(INT_MIN,INT_MIN);

          index = 0;
          while(index < l)
          {
            double x = points->get(index).get_X();
            double y = points->get(index).get_Y();
            double curr_c = (y - median_slope*x);

            if(abs_value(curr_c - min_c) < 0.001)
            {
              if(x < pmin.get_X())
              {
                pmin.set_point(x,y);
              }
              if(x > pmax.get_X())
              {
                pmax.set_point(x,y);
              }
            }
            index++;
          }

          if(pmin.get_X() <= median && pmax.get_X() > median)
          {
            Pair<Coordinate,Coordinate> lower_bridge(pmin,pmax);
            return lower_bridge;
          }
          else if(pmax.get_X() <= median)
          {
            index = 0;
            l = EQUAL.len();
            while(index < l)
            {
              Coordinate pt = EQUAL.get(index).get_second();
              candidates.insert(pt);
              index++;
            }

            index = 0;
            l = LARGE.len();
            while(index < l)
            {
              Coordinate pt1 = LARGE.get(index).get_first();
              Coordinate pt2 = LARGE.get(index).get_second();
              candidates.insert(pt1);
              candidates.insert(pt2);
              index++;
            }

            index = 0;
            l = SMALL.len();
            while(index < l)
            {
              Coordinate pt = SMALL.get(index).get_second();
              candidates.insert(pt);
              index++;
            }
            return computeLowerBridge(&candidates,median);
          }
          else if(pmin.get_X() > median)
          {
            index = 0;
            l = EQUAL.len();
            while(index < l)
            {
              Coordinate pt = EQUAL.get(index).get_first();
              candidates.insert(pt);
              index++;
            }

            index = 0;
            l = LARGE.len();
            while(index < l)
            {
              Coordinate pt = LARGE.get(index).get_first();
              candidates.insert(pt);
              index++;
            }
            
            index = 0;
            l = SMALL.len();
            while(index < l)
            {
              Coordinate pt1 = SMALL.get(index).get_first();
              Coordinate pt2 = SMALL.get(index).get_second();
              candidates.insert(pt1);
              candidates.insert(pt2);
              index++;
            }
            return computeLowerBridge(&candidates,median);
          }
        
        return {};
    }

    /**
     * @brief This function returns the list of points of the upper hull.
     * 
     * @param pmin Point with the minimum x coordinate.
     * @param pmax Point with the maximum x coordinate.
     * @param points List of all input points.
     * @return List<Coordinate> return type.
     */
    List<Coordinate> computeLowerHull(Coordinate pmin,Coordinate pmax,List<Coordinate>* points)
    {
        int index = 0;
        int l = points->len();
        List<Coordinate> lower_hull(l);

        double arr[l];
        while(index < l)
        {
          arr[index] = points->get(index).get_X();
          index++;
        }
        double median;
        if(l ==1)
          median = arr[0];
        else
          median = kthSmallest(arr,0,l-1,(l+1)/2);
        Pair<Coordinate,Coordinate> lower_bridge = computeLowerBridge(points,median);

        Coordinate cl = lower_bridge.get_first();
        Coordinate c2 = lower_bridge.get_second();

        if(cl.get_X() > c2.get_X())
        {
          Coordinate temp(cl);
          cl.set_point(c2);
          c2.set_point(temp);
        }

        lower_hull.insert(cl);
        lower_hull.insert(c2);

        if(pmin.equals(cl)==false)
        {
          List<Coordinate> lower_T_left = get_T(pmin,cl,points,true);
          List<Coordinate> left = computeLowerHull(pmin,cl,&lower_T_left);
          lower_hull.append_list(left);
        }
        if(pmax.equals(c2)==false)
        {
          List<Coordinate> lower_T_right = get_T(c2,pmax,points,true);
          List<Coordinate> right = computeLowerHull(c2,pmax,&lower_T_right);
          lower_hull.append_list(right);
        }

        return lower_hull;
    }

    public:

    /**
     * @brief Constructorfor class KPS, creates a new KPS object.
     * 
     */
    KPS(){
      points = List<Coordinate>();
    }

    /**
     * @brief accepts a list of points that make the dataset for finding the convex hull.
     * 
     * @param list List of input points.
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
     * @brief Computes the convex hull using KirkPatrick Seidel Algo and returns a list of type List<Coordinate> containing the points of the convex hull.
     * 
     * @return List<Coordinate> return type.
     */
    List<Coordinate> compute_hull(){

      if(points.len()<3){
        cout<<"Hull doesn't exist!!"<<endl;
        exit(0);
      }

      Coordinate pmin_u,pmin_l,pmax_u,pmax_l;

      pmin_l = pmin_u = pmax_u = pmax_l = points.get(0);
      int index = 1;
      int l = points.len();

      while(index < l)
      {
          Coordinate curr_point = points.get(index);
          if(curr_point.get_X() < pmin_l.get_X())
          {
            pmin_l = curr_point;
            pmin_u = curr_point;
          }
          else if(curr_point.get_X() > pmax_l.get_X()){
            pmax_l = curr_point;
            pmax_u = curr_point;
          }
          else if(curr_point.get_X() == pmin_l.get_X()){
            if(curr_point.get_Y() > pmin_u.get_Y()){
              pmin_u = curr_point;
            }
            else if(curr_point.get_Y() < pmin_l.get_Y()){
              pmin_l = curr_point;
            }
          }
          else if(curr_point.get_X() == pmax_l.get_X()){
            if(curr_point.get_Y() > pmax_u.get_Y()){
              pmax_u = curr_point;
            }
            else if(curr_point.get_Y() < pmax_l.get_Y()){
              pmax_l = curr_point;
            }
          }
          index++;
      }

      List<Coordinate> upper_T = get_T(pmin_u,pmax_u,&points,false);
      List<Coordinate> upper_hull = computeUpperHull(pmin_u,pmax_u,&upper_T);

      List<Coordinate> lower_T = get_T(pmin_l,pmax_l,&points,true);
      List<Coordinate> lower_hull = computeLowerHull(pmin_l,pmax_l,&lower_T);


      List<Coordinate> hull_edges;
      hull_edges.append_list(upper_hull);
      hull_edges.append_list(lower_hull);

      if(pmin_u.equals(pmin_l)==false)
      {
        hull_edges.insert(pmin_l);
        hull_edges.insert(pmin_u);
      }
      if(pmax_l.equals(pmax_u)==false)
      {
        hull_edges.insert(pmax_l);
        hull_edges.insert(pmax_u);
      }


       make_result(hull_edges,"results/results_1.csv");

      sort(hull_edges.begin(),hull_edges.end(),[](Coordinate a,Coordinate b){if(a.get_X() < b.get_X()) return true;else if(a.get_X() > b.get_X())
      return false;else return a.get_Y() < b.get_Y();});

      List<Coordinate> hull;
      hull.insert(hull_edges.get(0));
      int i=1;
      while(i<hull_edges.len()){
        while (i < hull_edges.len() && hull_edges.get(i).equals(hull_edges.get(i-1)))
          i++;

        if(i<hull_edges.len())
          hull.insert(hull_edges.get(i));

        i++;
      }

      return hull;
  }
};


int main()
{
    KPS kps;
    List<Coordinate> points = make_list("points.csv");
    kps.fit_set(points);
    // int startTime = time(NULL);
    List<Coordinate> hull = kps.compute_hull();
    // int endTime = time(NULL);
    // cout << "TOTAL Execution Time : " << endTime - startTime << endl;
    hull.print();
    cout<<endl;
    cout<<endl;
}

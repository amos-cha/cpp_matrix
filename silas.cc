#include "silas.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>    
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <ratio>
#include <thread>


using namespace std::chrono;
using namespace std; 


int seed = 0;



vector<double> backsolve (vector<vector<double>> a, 
                          vector<double> b,
                          vector <double> x) {
  double n = a.size();
  for (int i = n-1 ; i > 0 ; i--) {
    double sum = b[i];
    for (int j = i+1 ; j < n ; j++) {
      sum = sum - a[i][j]*x[j];
    }
    x[i] = sum/a[i][i];
  }
  return x;
}

vector<double> NaiveGaussKIJ (vector<vector<double>> a, 
                                       vector<double> b,
                                      vector <double> x) {
  double n = a.size();
  for (double k = 0 ; k < n-1 ; k++) {

    for (double i = k+1 ; i < n ; i++) {

      a[i][k] = (a[i][k])/(a[k][k]);
      for (double j = k+1 ; j < n ; j++) {

        a[i][j] = a[i][j] - a[i][k]*a[k][j];
      }
      b[i] = b[i] - a[i][k]*b[k];
    }
    x[n - 1] = (b[n - 1])/(a[n - 1][n - 1]);
  }
  return backsolve(a,b,x);
}

vector<double> randomRow (int n) {
  vector<double> row;
  for (int i = 0 ; i < n ; i++) {
    srand(seed);
    seed++;
    row.push_back(rand());
  }
  
  return row;
}

void print(vector<vector<double>> matrix, int n) {
  for (int i = 0 ; i < n ; i++){
    for (int j = 0 ; j < n ; j++) {
      cout<<matrix[i][j]<< " ";
    }
    cout<<endl;
  }
  cout<<"seed is : "<<seed<<endl;
}

void print(vector<double> arr, int n) {
  for (int j = 0 ; j < n ; j++) {
    cout<<arr[j]<< " ";
  }
  cout<<endl;
}


int main() {
  int n = 10;
  int rng = rand();
  vector<vector<double>> matrix;

  int size = 0;
  while (size<n) {
    matrix.push_back(randomRow(n));
    size++;
  }
  

  vector<double> x = randomRow(n);
  vector<double> b = randomRow(n);


  auto start = high_resolution_clock::now();
 // ================================================= 
  x = NaiveGaussKIJ(matrix,b,x);

 // =================================================
  auto stop = high_resolution_clock::now();
 // ================= P R I N T ===================== 

  cout<<"matrix : "<<endl;
  print(matrix,n);
  cout<<endl;

  cout<<"x :" <<endl;
  print(x,n);
  cout<<endl;

  cout<<"b : " <<endl;
  print(b,n);
  cout<<endl;

 // =================================================

  cout<<endl<<endl<<endl<<endl;
  auto duration = duration_cast<microseconds>(stop - start);
  cout<<"total time duration : "<<duration.count()<<" ms"<<endl;
  return 0;
}
/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(), put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

const double epsilon = 0.00001;

// Function declarations

void test_summarize();

void test_sum_empty();
void test_sum_small_data_set();

void test_count_empty();
void test_count_small_data_set();

void test_mean_empty();
void test_mean_small_data_set();

void test_median_empty();
void test_median_small_data_set();

void test_mode_empty();
void test_mode_tieless_data_set();
void test_mode_ties_data_set();

void test_min_empty();
void test_min_tieless_data_set();
void test_min_ties_data_set();

void test_max_empty();
void test_max_tieless_data_set();
void test_max_ties_data_set();

void test_stdev_empty();
void test_stdev_single();
void test_stdev_double();
void test_stdev();

void test_percentile_empty();
void test_percentile();


int main() {

  test_summarize();

  test_sum_empty();
  test_sum_small_data_set();

  test_count_empty();
  test_count_small_data_set();

  test_mean_empty();
  test_mean_small_data_set();

  test_median_empty();
  test_median_small_data_set();

  test_mode_empty();
  test_mode_tieless_data_set();
  test_mode_ties_data_set();

  test_min_empty();
  test_min_tieless_data_set();
  test_min_ties_data_set();

  test_max_empty();
  test_max_tieless_data_set();
  test_max_ties_data_set();

  test_stdev_empty();
  test_stdev_single();
  test_stdev_double();
  test_stdev();

  test_percentile_empty();
  test_percentile();


  return 0;
}


// Function definitions


// Testing summarize function
void test_summarize() {
  cout << "Testing summarize of dataset" << endl;

  vector<double> data;

  data.push_back(2);
  data.push_back(2);
  data.push_back(1);
  data.push_back(5);
  data.push_back(2);
  data.push_back(5);
  data.push_back(-10);
  data.push_back(1);

  vector<vector<double>> summary = {
    
    {-10, 1}, 
    {1, 2}, 
    {2, 3}, 
    {5, 2}
    
    };


  assert(summarize(data) == summary);

  cout << "Passed!" << endl;
}

// Testing sum function

void test_sum_empty() {
  cout << "Testing sum of empty vector" << endl;

  vector<double> data;

  assert(sum(data) == 0);

  cout << "Passed!" << endl;
}

void test_sum_small_data_set() {
  cout << "Testing sum of small dataset" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(-4);

  assert(sum(data) == 2);

  cout << "Passed!" << endl;
}

// Testing count function

void test_count_empty() {
  cout << "Testing count of empty dataset" << endl;

  vector<double> data;

  assert(count(data) == 0);

  cout << "Passed!" << endl;
}

void test_count_small_data_set() {

  cout << "Testing count for small dataset" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(count(data) == 3);

  cout << "Passed!" << endl;
}

// Testing mean function

void test_mean_empty() {
  cout << "Testing mean of empty dataset" << endl;

  vector<double> data;

  assert(mean(data) == 0);

  cout << "Passed!" << endl;
}

void test_mean_small_data_set() {
  cout << "Testing mean of small dataset" << endl;

  vector<double> data;

  data.push_back(1);
  data.push_back(2);
  data.push_back(-4);

  assert(abs(mean(data) - (-0.333333)) < epsilon);

  cout << "Passed!" << endl;

}

// Testing median function

void test_median_empty() {
  cout << "Testing median of empty dataset" << endl;

  vector<double> data;

  assert(median(data) == 0);

  cout << "Passed!" << endl;
}

void test_median_small_data_set(){
  cout << "Testing median of small dataset" << endl;

  vector<double> data;

  data.push_back(1);
  data.push_back(2);

  assert(abs(median(data) - (1.50000)) < epsilon);

  cout << "Passed!" << endl;

}

// Testing mode function

void test_mode_empty() {
  cout << "Testing mode of empty dataset" << endl;

  vector<double> data;

  assert(mode(data) == 0);

  cout << "Passed!" << endl;
}

void test_mode_tieless_data_set() {
  cout << "Testing mode of dataset without ties" << endl;

  // [1, 2, 2, 3, 3, 3]

  vector<double> data;

  data.push_back(1);
  data.push_back(2);
  data.push_back(2);
  data.push_back(3);
  data.push_back(3);
  data.push_back(3);
  
  assert(mode(data) == 3);

  cout << "Passed!" << endl;
}

void test_mode_ties_data_set() {
  cout << "Testing mode of dataset with ties" << endl;

  // [1, 1, 1, 2, 2, 2, 3, 3, 3]

  vector<double> data;

  data.push_back(1);
  data.push_back(2);
  data.push_back(1);
  data.push_back(2);
  data.push_back(2);
  data.push_back(3);
  data.push_back(1);
  data.push_back(3);
  data.push_back(3);
  
  assert(mode(data) == 1);

  cout << "Passed!" << endl;
}

// Testing min function

void test_min_empty() {
  cout << "Testing min of empty dataset" << endl;

  vector<double> data;

  assert(min(data) == 0);

  cout << "Passed!" << endl;
}

void test_min_tieless_data_set() {
  cout << "Testing min of dataset without ties" << endl;

  // [1, 2, 3, -4, 5]

  vector<double> data;

  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(-4);
  data.push_back(5);
  
  assert(min(data) == -4);

  cout << "Passed!" << endl;
}

void test_min_ties_data_set() {
  cout << "Testing min of dataset with ties" << endl;

  // [1, 2, 3, -4, -5, 6, -5]

  vector<double> data;

  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(-4);
  data.push_back(-5);
  data.push_back(6);
  data.push_back(-5);
  
  assert(min(data) == -5);

  cout << "Passed!" << endl;
}

// Testing max function

void test_max_empty() {
  cout << "Testing max of empty dataset" << endl;

  vector<double> data;

  assert(max(data) == 0);

  cout << "Passed!" << endl;
}

void test_max_tieless_data_set() {
  cout << "Testing max of dataset without ties" << endl;

  // [-1, -2, -3, -4, -5]

  vector<double> data;

  data.push_back(-1);
  data.push_back(-2);
  data.push_back(-3);
  data.push_back(-4);
  data.push_back(-5);
  
  assert(max(data) == -1);

  cout << "Passed!" << endl;
}

void test_max_ties_data_set() {
  cout << "Testing max of dataset with ties" << endl;

  // [1, 2, 3, -4, -5, 6, -5, 6]

  vector<double> data;

  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(-4);
  data.push_back(-5);
  data.push_back(6);
  data.push_back(-5);
  data.push_back(6);
  
  assert(max(data) == 6);

  cout << "Passed!" << endl;
}


// Testing stdev function

void test_stdev_empty() {
  cout << "Testing stdev of empty dataset" << endl;

  vector<double> data;

  assert(stdev(data) == 0);

  cout << "Passed!" << endl;
}

void test_stdev_single() {

  cout << "Testing stdev of dataset with single element" << endl;

  vector<double> data;

  data.push_back(3);

  assert(stdev(data) == 0);

  cout << "Passed!" << endl;
}

void test_stdev_double() {
  cout << "Testing stdev of dataset with two elements" << endl;

  vector<double> data;

  data.push_back(5);
  data.push_back(6);

  assert(abs(stdev(data) - (0.707106)) < epsilon);
  
  cout << "Passed!" << endl;
}

void test_stdev() {

  cout << "Testing stdev of dataset" << endl;

  vector<double> data;

  // [1, 2, 3, 4, 5]

  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);

  assert(abs(stdev(data) - (1.581138)) < epsilon);

  cout << "Passed!" << endl;

}


// Testing percentile function

void test_percentile_empty() {
  cout << "Testing percentile of empty dataset" << endl;

  vector<double> data;

  assert(percentile(data, 0.5) == 0);

  cout << "Passed!" << endl;
}

void test_percentile(){
  cout << "Testing percentile of dataset" << endl;

  vector<double> data;

  data.push_back(35);
  data.push_back(20);
  data.push_back(40);
  data.push_back(50);
  data.push_back(15);

  assert(abs(percentile(data, 0.4) - 29.000000) < epsilon);

  cout << "Passed!" << endl;
}
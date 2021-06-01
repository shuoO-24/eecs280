// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 5x3 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

// Fills a 3x5 matrix with a value
// and checks if Matrix_height and Matrix_width are
// set correctly

TEST(test_height_width) {

  Matrix* mat = new Matrix;
  
  const int height = 3;
  const int width = 5;

  Matrix_init(mat, width, height);
  
  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 3);

  delete mat;

}

// Fills a 5x3 Matrix with a value and fills
// the border with a different value
// Checks that Matrix_at returns the correct value for each element
TEST(test_fill_border) {

  Matrix* mat = new Matrix;

  const int width = 3;
  const int height = 5;
  const int value = 15;
  const int border_value = 20;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat, border_value);

  for(int r = 0; r < height; ++r) {
    for(int c = 0; c < width; ++c) {

      if(r == 0 || c == 0 || r == height - 1 || c == width - 1) {

        ASSERT_EQUAL(*Matrix_at(mat, r, c), 20);

      } else {

        ASSERT_EQUAL(*Matrix_at(mat, r, c), 15);

      }
    }
  }

  delete mat;

}


// Fills a 6x4 matrix with a value, checks if the Matrix_max
// returns the correct value. Then it changes one element
// to be greater than the rest, and checks
// if Matrix_max returns the correct value
TEST(test_max_element) {

  Matrix* mat = new Matrix;

  const int height = 6;
  const int width = 4;
  const int value = -15;
  const int new_value = 0;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_max(mat), value);

  *Matrix_at(mat, 5, 3) = new_value;
  *Matrix_at(mat, 2, 2) = new_value;

  ASSERT_EQUAL(Matrix_max(mat), new_value);

  delete mat;

}


// Fills a 3x5 matrix with a value, then fills the
// border with a different value, then changes two
// values and checks if Matrix_print outputs the
// correct matrix
TEST(test_print) {

  Matrix* mat = new Matrix;

  const int height = 3;
  const int width = 5;
  const int value = 2;
  const int border_value = 5;
  const int new_value = 3;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat, border_value);
  *Matrix_at(mat, 0, 0) = new_value;
  *Matrix_at(mat, 2, 4) = new_value;

  ostringstream expected;
  expected << "5 3\n"
           << "3 5 5 5 5 \n"
           << "5 2 2 2 5 \n"
           << "5 5 5 5 3 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;

}

// Fills a 3x5 matrix with a value
// and checks if Matrix_row and Matrix_column
// return the right values for a specific element

TEST(test_row_column) {

  Matrix* mat = new Matrix;

  const int height = 3;
  const int width = 5;
  const int value = 2;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  const int* ptr = Matrix_at(mat, 0, 3);

  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);

  delete mat;

}


// Fills a 3x5 matrix with a value
// changes some values and checks if
// Matrix_min_value_in_row returns the right value
// for each row

TEST(test_min_value_in_row) {

  Matrix* mat = new Matrix;

  const int height = 3;
  const int width = 5;
  const int value = 2;
  const int border_value = 3;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat, border_value);

  *Matrix_at(mat, 1, 2) = -2;
  *Matrix_at(mat, 2, 4) = 0;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 5), 3); // min value of entire 0th row
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 3, 5), 3);

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 5), -2); // min value of entire 1st row
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 2, 5), -2);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 3, 5), 2);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 2), 2);

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 5), 0); // min value of entire 2nd row
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 4), 3);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 4, 5), 0);

  delete mat;
  
}



// Fills a 3x5 matrix with a value
// changes some values and checks if
// Matrix_column_of_min_value_in_row returns the right value
// for each row

TEST(test_column_of_min_value_in_row) {

  Matrix* mat = new Matrix;

  const int height = 3;
  const int width = 5;
  const int value = 2;
  const int border_value = 3;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat, border_value);

  *Matrix_at(mat, 1, 2) = -2;
  *Matrix_at(mat, 2, 4) = 0;
  *Matrix_at(mat, 2, 1) = 0;

  // Matrix now looks like
  // 3 3 3 3 3
  // 3 2 -2 2 3
  // 3 0 3 3 0

  // Check column of min value in each row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 5), 0); // entire 0th row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 2, 5), 2); // partial 0th row

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 5), 2); // entire 1st row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 2), 1); // partial 1st row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 2); // partial 1st row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 2, 5), 2); // partial 1st row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 3, 5), 3); // partial 1st row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 4, 5), 4); // partial 1st row

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 5), 1); // entire 2nd row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 2), 1); // partial 2nd row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 1, 5), 1); // partial 2nd row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 2, 5), 4); // partial 2nd row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 2, 4), 2); // partial 2nd row

  delete mat;

}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
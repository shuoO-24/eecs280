// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.



// Creates a 4x5 (row x columns) Image and checks
// if image height and width are correct

TEST(test_height_width) {

  Image* img = new Image;

  Image_init(img, 5, 4);

  ASSERT_EQUAL(Image_height(img), 4);
  ASSERT_EQUAL(Image_width(img), 5);

  delete img;

}

// Reads image from PPM file and checks
// if dimensions are correct

TEST(test_height_width_ppm) {

  Image* img = new Image;

  string input_filename = "crabster_50x45.correct.ppm";

  std::ifstream fin(input_filename);

  Image_init(img, fin);

  ASSERT_EQUAL(Image_height(img), 45);
  ASSERT_EQUAL(Image_width(img), 50);

  delete img;

}

// Reads image from PPM file
// Checks if get_pixel works as intended

TEST(test_get_pixel) {

  Image* img = new Image;

  string input_filename = "crabster_50x45.correct.ppm";

  std::ifstream fin(input_filename);

  Image_init(img, fin);

  Pixel p1 = Image_get_pixel(img, 0, 0);
  Pixel p2 = Image_get_pixel(img, 15, 2);
  Pixel p3 = Image_get_pixel(img, 44, 49);

  ASSERT_TRUE(Pixel_equal(p1, {255, 255, 255}));
  ASSERT_TRUE(Pixel_equal(p2, {149, 45, 57}));
  ASSERT_TRUE(Pixel_equal(p3, {255, 255, 255}));
  
  delete img;

}

// Create a 4x3 image
// Check if Image_fill works correctly

TEST(test_fill) {

  Image* img = new Image;

  Image_init(img, 3, 4);
  Image_fill(img, {3, 4, 5});

  string output_correct = "P3\n3 4\n255\n3 4 5 3 4 5 3 4 5 \n3 4 5 3 4 5 3 4 5 \n3 4 5 3 4 5 3 4 5 \n3 4 5 3 4 5 3 4 5 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();

  ASSERT_EQUAL(actual, output_correct);

  delete img;
}

// Create two 4x3 images, initialize with ppm
// check if set_pixel works

TEST(test_set_pixel) {

  Image* img = new Image;
  Image* img2 = new Image;

  string input_filename = "crabster_50x45.correct.ppm";
  std::ifstream fin(input_filename);
  Image_init(img, fin);

  Image_init(img2, Image_width(img), Image_height(img));

  Image_fill(img2, {10, 2, 6});

  for (size_t r = 0; r < Image_height(img); ++r) {
    for(size_t c = 0; c < Image_width(img); ++c) {
      Image_set_pixel(img, r, c, {10, 2, 6});
    }
  }
  
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 1), {10, 2, 6}));
  ASSERT_TRUE(Image_equal(img, img2));

  delete img;
  delete img2;

}

// Create a 1x1 image and check
// if Image_print works

TEST(test_print) {

  Image* img = new Image;

  Image_init(img, 1, 1);
  Image_set_pixel(img, 0, 0, {3, 2, 6});

  string output_correct = "P3\n1 1\n255\n3 2 6 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();

  ASSERT_EQUAL(actual, output_correct);

  delete img;

}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
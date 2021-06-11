// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {

  /*

  1. Initalize the energy Matrix with the same size as the Image and fill it with zeros
  2. Compute the energy for each non-border pixel, using the formula.
  3. Find the maximum energy so far, and use it to fill in the border pixels.

  energy(X) = squared_difference(N, S) + squared_difference(W, E)

  */

  int width = Image_width(img);
  int height = Image_height(img);
  
  Matrix_init(energy, width, height);
  Matrix_fill(energy, 0);

  for(size_t r = 1; r < height - 1; ++r) {
    for(size_t c = 1; c < width - 1; ++c) {
      
      Pixel north = Image_get_pixel(img, r-1, c);
      Pixel south = Image_get_pixel(img, r+1, c);
      Pixel west = Image_get_pixel(img, r, c-1);
      Pixel east = Image_get_pixel(img, r, c+1);

      int pixel_energy = squared_difference(north, south) + squared_difference(west, east);
      *Matrix_at(energy, r, c) = pixel_energy;

    }
  }

  int max_energy = Matrix_max(energy);
  Matrix_fill_border(energy, max_energy);

}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {


  /*

  1. Initialize the cost Matrix with the same size as the energy Matrix.
  2. Fill in costs for the first row (index 0). The cost for these pixels is just the energy.
  3. Loop through the rest of the pixels in the Matrix, row by row, starting with the second row (index 1). 
  Use the recurrence formula to compute each cost.

  cost(row, col) = energy(row, col) + min(cost(row-1, col-1), cost(row-1, col), cost(row-1, col+1))

  */

  int width = Matrix_width(energy);
  int height = Matrix_height(energy);
  
  Matrix_init(cost, width, height);

  for (size_t c = 0; c < width; ++c) {
    
    *Matrix_at(cost, 0, c) = *Matrix_at(energy, 0, c);

  }

  for (size_t row = 1; row < height; ++row) {
    for(size_t col = 0; col < width; ++col) {

      int start_index;
      int end_index;

      if (col > 0) {

        // top left pixel is inbounds
        start_index = col - 1;

      } else {

        start_index = col;

      }

      if (col < width - 1) {

        // top right pixel in inbounds
        end_index = col + 2;

      } else {

        end_index = col + 1;

      }

      // Recurrence relation
      *Matrix_at(cost, row, col) = *Matrix_at(energy, row, col) + Matrix_min_value_in_row(cost, row - 1, start_index, end_index);

    }
  }
}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {

  int start_index;
  int end_index;

  int height = Matrix_height(cost);
  int width = Matrix_width(cost);

  // Minimum cost pixel in the bottom row
  int col = Matrix_column_of_min_value_in_row(cost, height - 1, 0, width);
  seam[height - 1] = col;

  for(int row = height - 2; row >= 0; --row) {

    if (col > 0) {

      // top left pixel is inbounds
      start_index = col - 1;

    } else {

      start_index = col;

    }

    if (col < width - 1) {

      // top right pixel in inbounds
      end_index = col + 2;

    } else {

      end_index = col + 1;

    }

    col = Matrix_column_of_min_value_in_row(cost, row, start_index, end_index);
    seam[row] = col;

  }
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {

  assert(Image_width(img) >= 2);

  int height = Image_height(img);
  int width = Image_width(img);
  Image* aux = new Image;
  Image_init(aux, width - 1, height); // new image has one fewer column

  
  for(size_t row = 0; row < height; ++row) {
    
    int col_to_remove = seam[row];
    assert(0 <= col_to_remove && col_to_remove < width);

    for (size_t col = 0; col < width; ++col) {

      // if not at column to remove, copy the pixel into correct position
      if (col != col_to_remove) {

        if (col > col_to_remove) {

          Image_set_pixel(aux, row, col - 1, Image_get_pixel(img, row, col));

        } else {
          
          Image_set_pixel(aux, row, col, Image_get_pixel(img, row, col));

        }
      }
    }
  }

  // copy back into original
  *img = *aux;
  delete aux;

}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image *img, int newWidth) {

  /*

  1. Compute the energy matrix
  2. Compute the cost matrix
  3. Find the minimal cost seam
  4. Remove the minimal cost seam

  Repeat above procedure repeatedly until required width is reached

  */

  int width = Image_width(img);
  int height = Image_height(img);
  int* seam = new int[height];

  assert(0 < newWidth && newWidth <= width);

  while(newWidth < width) {

    Matrix* energy = new Matrix;
    Matrix* cost = new Matrix;

    compute_energy_matrix(img, energy);
    compute_vertical_cost_matrix(energy, cost);
    find_minimal_vertical_seam(cost, seam);
    remove_vertical_seam(img, seam);

    width = Image_width(img);

    delete energy;
    delete cost;

  }

  delete[] seam;
  
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {

  int height = Image_height(img);

  assert(0 < newHeight && newHeight <= height);

  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);

}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {

  int width = Image_width(img);
  int height = Image_height(img);

  assert(0 < newWidth && newWidth <= width);
  assert(0 < newHeight && newHeight <= height);

  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);

}
// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {

  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  mat->width = width;
  mat->height = height;

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {

  int matrix_size = Matrix_height(mat) * Matrix_width(mat);

  const int* ptr = mat->data;

  os << Matrix_width(mat) << " " << Matrix_height(mat);

  // print rows

  for(size_t index=0; index < matrix_size; ++index) {

    if (index % Matrix_width(mat) == 0) {

      //new row

      os << "\n" << *ptr << " ";

    } else {

      os << *ptr << " ";

    }

    os << "\n";

    ++ptr;
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {

  return mat->width;

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {

  return mat->height;

}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {

  // number of values between ptr and mat->data = index of element pointed to by ptr
  // row = index / num_columns

  int index = ptr - mat->data;
  int row = index/Matrix_width(mat);

  return row;

}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {

  // number of values between ptr and mat->data = index of element pointed to by ptr
  // column = index % num_columns

  int index = ptr - mat->data;
  int column = index % Matrix_width(mat);

  return column;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {

  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  // index = (row * num_columns) + column
  int index = (row * Matrix_width(mat)) + column;

  int* ptr = mat->data;
  ptr += index;

  return ptr;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {

  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  //index = (row * num_columns) + column
  const int index = (row * Matrix_width(mat)) + column;
  const int* ptr = mat->data;

  ptr += index;

  return ptr;

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {

  int matrix_size = Matrix_height(mat) * Matrix_width(mat);
  
  int* ptr = mat->data;

  for (int i=0; i < matrix_size; ++i) {

    *ptr = value;
    ++ptr;

  }

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {

  int matrix_size = Matrix_height(mat) * Matrix_width(mat);
  int* ptr = mat->data;

  for(size_t i = 0; i < matrix_size; ++i) {

    int row = Matrix_row(mat, ptr);
    int column = Matrix_column(mat, ptr);

    if (row == 0 || column == 0 || row == (Matrix_height(mat) - 1) || column == (Matrix_width(mat) - 1)) {

      *ptr = value;

    }

    ++ptr;
  }
  
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {

  int matrix_size = Matrix_height(mat) * Matrix_width(mat);
  
  const int* ptr = mat->data;
  int max_element = *(mat->data);

  for(size_t i = 0; i < matrix_size; ++i) {

    int curr_element = *ptr;

    if (curr_element > max_element) {

      max_element = curr_element;

    }

    ++ptr;

  }

  return max_element;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  // index = (row * num_cols) + column
  int index_start = (row * Matrix_width(mat)) + column_start;
  int index_end = (row * Matrix_width(mat)) + column_end;
  int i = index_start;

  const int *ptr = mat->data;
  ptr += index_start;
  int min_element_in_row = *ptr;
  int column_of_min_element_in_row = column_start;

  while(i < index_end) {

    int curr_element = *ptr;

    if (curr_element < min_element_in_row) {
      
      min_element_in_row = curr_element;

      // column = index % num_cols
      column_of_min_element_in_row = i % Matrix_width(mat);

    }
    
    ++i;
    ++ptr;

  }

  return column_of_min_element_in_row;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  // index = (row * num_cols) + column
  int index_start = (row * Matrix_width(mat)) + column_start;
  int index_end = (row * Matrix_width(mat)) + column_end;
  int i = index_start;

  const int *ptr = mat->data;
  ptr += index_start;
  int min_element_in_row = *ptr;

  while(i < index_end) {

    int curr_element = *ptr;

    if (curr_element < min_element_in_row) {
      
      min_element_in_row = curr_element;

    }

    ++i;
    ++ptr;

  }

  return min_element_in_row;

}
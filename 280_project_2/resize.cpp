#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Image.h"
#include "processing.h"

int main(int argc, char const *argv[]) {

    if (argc != 4 && argc != 5) {
        std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
        << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;

        return -1;
    }

    int desired_width = -1;
    int desired_height = -1;
    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    std::ifstream fin(input_filename);

    if(!fin.is_open()) {

        std::cout << "Error opening file: " << input_filename << std::endl;
        return -1;

    }

    Image* img = new Image;
    Image_init(img, fin);
    int img_height = Image_height(img);
    int img_width = Image_width(img);
    
    if (argc == 4) {
        
        desired_width = atoi(argv[argc - 1]);

        if (desired_width < 0 || desired_width > img_width) {

            std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
            << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
            
            return -1;
        }

    } else {

        desired_height = atoi(argv[argc - 1]);
        desired_width = atoi(argv[argc - 2]);

        if (desired_width < 0 || desired_height < 0 || desired_width > img_width || desired_height > img_height) {
            
            std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
            << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
            
            return -1;

        }

    }

    seam_carve(img, desired_width, desired_height);

    std::ofstream fout(output_filename);
    
    if(!fout.is_open()) {

        std::cout << "Error opening file: " << input_filename << std::endl;
        return -1;

    } else {

        Image_print(img, fout);
        delete img;
        
        return 0;
    }
}
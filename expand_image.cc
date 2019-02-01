#include <cstdio>
#include "bitmap_image.hpp"
using namespace std;

// expand_image(bitmap_image, bitmap_image):
// recieves the old image and image diff as parameters to 
// construct the image of higher resolution.
void expand_image(bitmap_image oldImg, bitmap_image diff) {
    bitmap_image newImg(1280,720);
    int newH = 720, newW = 1280;
    if (true) {
        for (int y=0; y<newH; ++y) {
            if (y%2 == 0) {
                for (int x=0; x<newW; ++x) {
                    if (x%2 == 0) {
                        newImg.set_pixel(x,y,oldImg.get_pixel(x/2,y*2/3));
                    }
                    else {
                        newImg.set_pixel(x,y,diff.get_pixel(x,y));
                    }
                }
            } else {
                for (int x=0; x<newW; ++x) {
                    newImg.set_pixel(x,y,diff.get_pixel(x,y));
                }
            }
        }
    }
    else {
        throw std::logic_error("Not implemented for this res");
    }
    newImg.save_image("expanded.bmp");
}

int main(int argc, char *argv[]){
    bitmap_image diff(argv[1]);
    bitmap_image old(argv[2]);
    expand_image(old, diff);
}
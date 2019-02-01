#include <cstdio>
#include "bitmap_image.hpp"
using namespace std;

// generateDiff(string, string) 
// generates the diff, which is used by expand_image to expand the lower
// resolution image.
void generateDiff (string lowRes, string highRes){
   bitmap_image lowResImage(lowRes);
   bitmap_image highResImage(highRes);

 if (!highResImage){
      printf("Error - Failed to open file\n");
   }
   bitmap_image image(highResImage.width(),highResImage.height());

   const unsigned int height = image.height();
   const unsigned int width  = image.width();
   for (std::size_t y = 0; y < height; ++y){
      for (std::size_t x = 0; x < width; ++x){
         if (y % 2 == 1 || x % 2 == 1){
            rgb_t colour;
            highResImage.get_pixel(x, y, colour);
            image.set_pixel(x, y, colour);
         }
      }
   }
   image.save_image("diff-720.bmp");
}


int main(int argc, char *argv[]){
   generateDiff("480p.bmp", "720p.bmp");
}
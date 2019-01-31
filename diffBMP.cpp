#include <cstdio>
#include "bitmap_image.hpp"
using namespace std;

#import "bitmap_image.hpp"

bitmap_image expand_image(std::tuple<int, int> oldRes, std::tuple<int, int> newRes, bitmap_image oldImg, vector<vector<rgb_t>> diff) {
    int fact = std::get<0>(newRes) * std::get<1>(newRes) / std::get<0>(oldRes) * std::get<1>(oldRes);
    bitmap_image newImg(std::get<0>(newRes), std::get<0>(newRes));
    int newW = std::get<0>(newRes), newH = std::get<1>(newRes);
    if (fact == 4) {
        for (int i=0; i<newH; ++i) {
            if (i%2 == 0) {
                for (int j=0; j<newW; ++j) {
                    if (j%2 == 0) {
                        newImg.set_pixel(i,j,oldImg.get_pixel(i/2,j/2));
                    }
                    else {
                        newImg.set_pixel(i,j,diff.at(i).at((j-1)/2);
                    }
                }
            } else {
                for (int j=0; j<newW; ++j) {
                    newImg.set_pixel(i,j,diff.at(i).at(j));
                }
            }
        }
    }
    else {
        throw std::logic_error("Not implemented for this res")
    }
    newImg.save_image("expanded.bmp");
}

vector<vector<rgb_t> > getDiff (string input){
   vector<vector<rgb_t> > diff; 
   bitmap_image image(input);
   if (!image){
      printf("Error - Failed to open file\n");
      return diff;
   }


   const unsigned int height = image.height();
   const unsigned int width  = image.width();
   vector<rgb_t> row;
   for (std::size_t y = 0; y < height; ++y){
      for (std::size_t x = 0; x < width; ++x){
         if (y % 2 == 1 || x % 2 == 1){
            rgb_t colour;
            image.get_pixel(x, y, colour);
            row.push_back(colour);
         }
      }
      diff.push_back(row);
   }
   return diff;
}


// int main(int argc, char *argv[]){
//    vector<vector<rgb_t> > diff; 
//    diff = getDiff(argv[1]);
//    for (auto &row : diff ){
//       for (auto &col: row){
//          cout<<(int)col.blue;
//       }
//       cout<<endl;
//    }  
// }
#include <cstdio>
#include "bitmap_image.hpp"
using namespace std;

void expand_image(std::tuple<int, int> oldRes, std::tuple<int, int> newRes, bitmap_image oldImg, vector<vector<rgb_t>> diff) {
    int fact = std::get<0>(newRes) * std::get<1>(newRes) / std::get<0>(oldRes) * std::get<1>(oldRes);
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
                        newImg.set_pixel(x,y,diff.at(y).at((x-1)/2));
                    }
                }
            } else {
                for (int x=0; x<newW; ++x) {
                    newImg.set_pixel(x,y,diff.at(y).at(x));
                }
            }
        }
    }
    else {
        throw std::logic_error("Not implemented for this res");
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
   for (std::size_t y = 0; y < height; ++y){
         vector<rgb_t> row;
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


int main(int argc, char *argv[]){
   vector<vector<rgb_t> > diff; 
   diff = getDiff(argv[1]);
   // for (auto &it : diff){
   //    cout<<it.size()<<endl;
   // }
   // cout<<diff.size()<<endl;
   bitmap_image old("480p.bmp");
   expand_image(std::make_tuple<int, int>(480,640),std::make_tuple<int, int>(720, 1280), old, diff);
}
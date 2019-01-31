#include <cstdio>
#include "bitmap_image.hpp"
using namespace std;


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
#include <cstdio>
#include "bitmap_image.hpp"
using namespace std;

unsigned int gcd(unsigned int u, unsigned int v)
{
  int shift;

  /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
  if (u == 0) return v;
  if (v == 0) return u;
 
  /* Let shift := lg K, where K is the greatest power of 2
        dividing both u and v. */
  for (shift = 0; ((u | v) & 1) == 0; ++shift) {
         u >>= 1;
         v >>= 1;
  }
 
  while ((u & 1) == 0)
    u >>= 1;
 
  /* From here on, u is always odd. */
  do {
       /* remove all factors of 2 in v -- they are not common */
       /*   note: v is not zero, so while will terminate */
       while ((v & 1) == 0)  /* Loop X */
           v >>= 1;

       /* Now u and v are both odd. Swap if necessary so u <= v,
          then set v = v - u (which is even). For bignums, the
          swapping is just pointer movement, and the subtraction
          can be done in-place. */
       if (u > v) {
         unsigned int t = v; v = u; u = t; // Swap u and v.
       }
       
       v = v - u; // Here v >= u.
     } while (v != 0);

  /* restore common factors of 2 */
  return u << shift;
}

// generateDiff(string, string) 
// generates the diff, which is used by expand_image to expand the lower
// resolution image.
void generateDiff (string lowRes, string highRes){
   bitmap_image lowResImage(lowRes);
   bitmap_image highResImage(highRes);

   unsigned int denom = gcd(lowResImage.width(), highResImage.width());

   // finding numerator and denominator of ratio (lowFactor, highFactor respectively)
   int lowFactor = lowResImage.width() / denom;
   int highFactor = highResImage.width() / denom;

   // finding diffWidth from the difference between smaller vs newer chunk sizes
   int diffWidth = highFactor * highFactor - lowFactor * lowFactor;
   int highResArea = highResImage.width() * highResImage.height();

   // finding diffHeight from the number of chunks in a whole highRes image by finding the number of whole chunks (rounded up) for along the height and the width.
   int diffHeight = (highResImage.width() % highFactor == 0 ? highResImage.width() / highFactor : highResImage.width() / highFactor + 1 )
                  * (highResImage.height() % highFactor == 0 ? highResImage.height() / highFactor : highResImage.height() / highFactor + 1 );

   bitmap_image diff(diffWidth, diffHeight);

   if (!highResImage){
      printf("Error - Failed to open file\n");
   }

   const unsigned int height = highResImage.height();
   const unsigned int width  = highResImage.width();
   // iterating through blocks, x and y indicate the top left positions of each block.
   int diffX = 0;
   int diffY = 0;
   for (std::size_t y=0; y<height; y+= highFactor) {
      for (std::size_t x=0; x<width; x+= highFactor) {
         // iterating through inner block pixels, innerX and innerY indicate the current position of the block we are at.
         // increment diffY, reset diffX to 0 each time we go to a new block
         ++diffY;
         diffX = 0;
         for (int innerX = x; innerX < x+highFactor; ++innerX) {
            for (int innerY = y; innerY < y+highFactor; ++innerY) {
               // only get and set pixel if the block is not included in the old block (for now it is the top left smaller square with sides of length "lowFactor")
               if (!(innerX < x+lowFactor) && !(innerY < y+lowFactor)) {
                  // set pixel of the diff at diffX , diffY with the color at the highResImage at innerX , innerY
                  diff.set_pixel(diffX, diffY, highResImage.get_pixel(innerX, innerY));
                  // increment diffX every time we increment through the inner block.
                  ++diffX;
               }
            }
         }

      }
   }
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
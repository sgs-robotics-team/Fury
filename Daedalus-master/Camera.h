#include "bitmap_image.hpp"

class Camera
{
private:
  int fd;
 public:
  Camera();
  
  int init();	
  bitmap_image getFrame();
};

#include "Camera.h"

class Eyes{
 private:
  Camera c;
  int diff(int x, int y);
  double findCentroidsR(int row, bitmap_image line, const int lineColour[3], const int colourError, const int COLUMNS);
  double findCentroidsC(int column, bitmap_image line, const int lineColour[3], const int colourError, const int ROWS);
 public:
  Eyes();
  Eyes(Camera c);
  double getErrorLine(int r, int g, int b, int pres, int error);
  double* getErrorCenter(int r, int g, int b, int pres, int error);
};

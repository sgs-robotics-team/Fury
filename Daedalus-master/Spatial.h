#ifndef SPATIAL_H
#define SPATIAL_H

const int AXIS_X = 0; // left/right
const int AXIS_Y = 1; // forward/backward
const int AXIS_Z = 2; // up/down

class Spatial
{
public:
    Spatial();
    
    int spatialDataHandler(CPhidgetSpatial_SpatialEventDataHandle *data, int count);
    
    void printProperties(); //to be implemented later
    
    void zeroGyro();
    
    double getAcceleration(int axis) { return acceleration[axis]; }
    double getAngularRate(int axis) { return angularRate[axis]; }
    double getMagneticField(int axis) { return magneticField[axis]; }
    
    ~Spatial();
    
private:
    
    CPhidgetSpatialHandle spatial;
    
    double acceleration [3];
    double angularRate [3];
    double magneticField [3];
    
};

#endif // SPATIAL_H
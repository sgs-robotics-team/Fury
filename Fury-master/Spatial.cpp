#include <phidget21.h>
#include <iostream>

#include "Spatial.h"

namespace Handler
{
    int CCONV spatialDataHandler(CPhidgetSpatialHandle spatial, void *usrptr, CPhidgetSpatial_SpatialEventDataHandle *data, int count)
    {
        ((Spatial *) usrptr)->spatialDataHandler(data, count);
        
        return 0;
    }
}

Spatial::Spatial()
{
    CPhidgetSpatial_create(&spatial);
    CPhidget_open((CPhidgetHandle)spatial, -1);
    if(CPhidget_waitForAttachment((CPhidgetHandle)spatial, 1000)) {
        std::cout << "Error attaching Phidget Spatial." << std::endl;
    }
    
    CPhidgetSpatial_setDataRate(spatial, 10);
    
    CPhidgetSpatial_set_OnSpatialData_Handler(spatial, Handler::spatialDataHandler, this);
}

int Spatial::spatialDataHandler(CPhidgetSpatial_SpatialEventDataHandle *data, int count)
{
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            acceleration[j] = data[i]->acceleration[j];
            angularRate[j] = data[i]->angularRate[j];
            magneticField[j] = data[i]->magneticField[j];
        }
    }
    
	return 0;
}

void Spatial::printProperties()
{
    std::cout << "acc: " << acceleration[0] << " " << acceleration[1] << " " << acceleration[2] << std::endl;
    std::cout << "ang: " << angularRate[0] << " " << angularRate[1] << " " << angularRate[2] << std::endl;
    std::Cout << "mag: " << magneticField[0] << " " << magneticField[1] << " " << magneticField[2] << std::endl;
}

void Spatial::zeroGyro()
{
    CPhidgetSpatial_zeroGyro(spatial);
}

Spatial::~Spatial() {
    
    CPhidget_close((CPhidgetHandle)spatial);
    CPhidget_delete((CPhidgetHandle)spatial);
}
#include <ctime>
#include <sys/time.h>
#include <iostream>

#include "PID_Controller.h"

using namespace std;

PID_Controller::PID_Controller()
{
    P=1;
    I=0;
    D=0;
    t=getTime();
    e=0;
    e_last=0;
    e_total=0;
    // cout << "P:" << P << " I:" << I << " D:" << D << " Time:" << t << endl;
}

PID_Controller::PID_Controller(double p,double i,double d)
{
    P=p;
    I=i;
    D=d;
    t=getTime();
    e=0;
    e_last=0;
    e_total=0;
    // cout << "P:" << P << " I:" << I << " D:" << D << " Time:" << t << endl;
}

double PID_Controller::getCorrection(double error)
{
    t_last=t;
    t=getTime();
    e_last=e;
    e=error;
    e_total+=(e+e_last)*0.5*(t-t_last);
    //cout << "e:" << e << " e_last:" << e_last << " t:" << t << " t_last:" << t_last << " e_total:"<< e_total << " t_diff:"<< t-t_last<< endl;
    return P*e+I*e_total+D*((e-e_last)/(t-t_last));
}

double PID_Controller::getTime()
{
    struct timeval timeOfDay;
    gettimeofday(&timeOfDay, NULL);
    double utime;
    utime = timeOfDay.tv_usec/1000000.0;
    utime += timeOfDay.tv_sec;
    return utime;
}
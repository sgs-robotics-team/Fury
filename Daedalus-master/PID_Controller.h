#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PID_Controller{
    double P;
    double I;
    double D;
    double e_last;
    double e;
    double e_total;
    double t_last;
    double t;
public:
    PID_Controller();
    PID_Controller(double,double,double);
    double getCorrection(double);
    double getTime();
};

#endif // PID_CONTROLLER_H

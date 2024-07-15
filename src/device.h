#ifndef MAIN_H
#define MAIN_H

#include "MyTask.h"
#include <MPU6050.h>
#include <Wire.h>
#include <math.h>
#include "inter.h"

#define G 9.81
#define PI 3.14
#define NOT_ROTATE_TOLERANCE 1.0

class Device : public MyTask{
    public:
        Device();
        ~Device();
        const char* tag;
        int16_t stack_size;
        int8_t priority;
        void setup();
        void loop();
    private:
        uint16_t _task_id;
        void calibrate_mpu();
        bool calibrated = false;
        void locate_gravity_direction();
        int16_t Ax, Ay, Az, Wx, Wy, Wz;
        float ax, ay, az, wx, wy, wz;
        unsigned long time_out;
        // void _calculate_Xspeed_and_Xdistance();
        // float _ax, _vx=0.0, _xx=0.0;
        // float _dax, _ax0;
        // float _dt, _t, _t0;
        // bool time_initialized;
};

extern Device device;

#endif // MAIN_H
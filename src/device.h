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
#define ACC_RESOLUTION 16384.00 // for m/s^2
#define GYRO_RESOLUTION 131.00 // for degrees/second
#define B_RESOLUTION 4800.00 // for microTesla

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
        bool trust_data = false;
        void read_data();
        void calibrate_mpu_and_update_g_direction();
        bool stabilized = false;
        bool calibrated;
        void locate_gravity_direction();
        //@brief Time interval in milliseconds
        unsigned long t, t0;
        float dt;
        bool time_initialized = false;
        //@brief Accelerometer component in LSB
        int16_t Ax, Ay, Az;
        //@brief Gyroscope component in LSB
        int16_t Wx, Wy, Wz;
        //@brief Magnetic field component in LSB
        int16_t Bx, By, Bz;
        //@brief Acceleration component in m/s^2.
        float a, ax, ay, az, ax0, ay0, az0;
        //@brief Angular velocity component in deg/s.
        float w, wx, wy, wz, wx0, wy0, wz0;
        //@brief Magnetic field component in uTesla.
        float b, bx, by, bz, bx0, by0, bz0; 
        //@brief Circular position of X-axis in degrees
        float rollX;
        float roll_angle;
        //@brief Circular position of Y-axis in degrees
        float pitchY;
        float road_camber;
        //@brief Angle between gravity field and X-axis in radians
        float thetaX_gravity;
        //@brief Angle between gravity field and X-axis on YZ plane in radians
        float phiYZ_gravity;
        //@brief Angle between gravity field and Y-axis in radians
        float thetaY_gravity;
        //@brief Angle between gravity field and X-axis on XZ plance in radians
        float phiXZ_gravity;
        //@brief Gravity field component in m/sˆ2.
        float g, gx, gy, gz;
        unsigned long time_out;
        // void _calculate_Xspeed_and_Xdistance();
        // float _ax, _vx=0.0, _xx=0.0;
        // float _dax, _ax0;
        // float _dt, _t, _t0;
        // bool time_initialized;
        void calculate_speed_and_distance();
};

extern Device device;

#endif // MAIN_H
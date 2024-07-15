#include "device.h"

Device device;
MPU6050 mpu;

Device::Device() {
    _task_id = set_task_id();
    tag = ":DEVICE";
    stack_size = 32;
    priority = 4;
}

Device::~Device() {}

void Device::setup() {
    Wire.begin();
    mpu.initialize();
}

void Device::loop() {
    calibrate_mpu();
    // _calculate_Xspeed_and_Xdistance();
}

void Device::calibrate_mpu() {
    if (!calibrated) {
        // don't move the mpu when this function is called
        time_out = millis();
        for (int c = 0; c < 100;) {
            if (millis() - time_out > 500) {
                Serial.println("Calibrating MPU ...");
                mpu.CalibrateGyro();
                Serial.println("MPU Calibration Done.");
                time_out = millis();
            }
            mpu.getRotation(&Wx, &Wy, &Wz);
            wx = Wx/131.00;
            wy = Wy/131.00;
            wz = Wz/131.00;
            if (abs(wx) < NOT_ROTATE_TOLERANCE 
                and abs(wy) < NOT_ROTATE_TOLERANCE
                and abs(wz) < NOT_ROTATE_TOLERANCE) c++;
            else c = 0;
        }
        calibrated = true;

    }
    mpu.getAcceleration(&Ax, &Ay, &Az);
    ax = Ax/16384.1f;
    ay = Ay/16384.1f;
    az = Az/16384.1f;
    float a = 9.8*sqrt(ax*ax + ay*ay + az*az);
    Serial.printf("a (%.2f, %.2f, %.2f) = %.2f m/s^2\n", ax, ay, az, a);
}

// void Device::_calculate_Xspeed_and_Xdistance() {
//     if (!time_initialized) {    
//         _t0 = millis();
//         _ax0 = (mpu.getAccelerationX()/16384.00)*G;
//         time_initialized = true;
//     }
//     _t = millis();
//     _ax = (mpu.getAccelerationX()/16384.00)*G;
//     _dt = (_t - _t0)/1000.0; // in seconds
//     _dax = _ax - _ax0; // in m/s^2
//     // Serial.printf("Ax: %.2f m/s^2, dAcc: %.2f m/s^2, dT: %.2f\n", _ax, _dax, _dt);
//     _vx += _dax*_dt ;
//     // if (_vx < 0) _vx = -1*_vx;
//     _xx += _vx*_dt;

//     _t0 = _t;
//     _ax0 = _ax;

//     inter.speed = _vx;
//     inter.acc = _ax;
//     inter.distance = _xx;
//     // Serial.printf("Acc: %.2f m/s^2, dAcc: %.2f m/s^2 , Speed: %.2f m/s, Distance: %.2f m\n", _ax, _dax, _vx, _xx);
// }
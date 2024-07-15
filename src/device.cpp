#include "device.h"

Device device;
MPU6050 mpu;

Device::Device() {
    _task_id = set_task_id();
    tag = ":DEVICE";
    stack_size = 64;
    priority = 4;
}

Device::~Device() {}

void Device::setup() {
    Wire.begin();
    mpu.initialize();
}

void Device::loop() {
    read_data();
    calibrate_mpu_and_update_g_direction();
    // _calculate_Xspeed_and_Xdistance();
}

void Device::read_data() {
    t = micros();
    mpu.getMotion9(&Ax, &Ay, &Az, &Wx, &Wy, &Wz, &Bx, &By, &Bz);
    ax = Ax*G/ACC_RESOLUTION; // convert to m/s^2
    ay = Ay*G/ACC_RESOLUTION;
    az = Az*G/ACC_RESOLUTION;
    a = sqrt(ax*ax + ay*ay + az*az);
    wx = Wx/GYRO_RESOLUTION; // convert to deg/s
    wy = Wy/GYRO_RESOLUTION;
    wz = Wz/GYRO_RESOLUTION;
    w = sqrt(wx*wx + wy*wy + wz*wz);
    bx = Bx/B_RESOLUTION; // convert to uTesla
    by = By/B_RESOLUTION;
    bz = Bz/B_RESOLUTION;
    b = sqrt(bx*bx + by*by + bz*bz);
    if (!time_initialized) {
        t0 = t;
        wx0 = wx;
        wy0 = wy;
        wz0 = wz;
        time_initialized = true;
    }
    dt = (t - t0)/1000000.0;
}

void Device::calibrate_mpu_and_update_g_direction() {
    if (!stabilized) {
        // don't move the mpu when this function is called
        Serial.println("Stabilizing MPU...");
        for (int c = 0; c < 100;) {
            if (abs(wx) < NOT_ROTATE_TOLERANCE 
                and abs(wy) < NOT_ROTATE_TOLERANCE
                and abs(wz) < NOT_ROTATE_TOLERANCE) c++;
            else c = 0;
        }
        stabilized = true;
        gx = ax;
        gy = ay;
        gz = az;
        g = a;
        thetaX_gravity = acos(gx/g);
        phiYZ_gravity = acos(gy/g*sin(thetaX_gravity));
        rollX = phiYZ_gravity*180/PI;
        roll_angle = abs(rollX-90);
        thetaY_gravity = acos(gy/g);
        phiXZ_gravity = acos(gx/g*sin(thetaY_gravity));
        pitchY = phiXZ_gravity*180/PI;
        road_camber = abs(pitchY-90);
        Serial.println("MPU Stabilization Done.");
    } else {
        // update g direction
        roll_angle =(abs(wx) >=NOT_ROTATE_TOLERANCE)? roll_angle + wx*dt : roll_angle;
        road_camber = (abs(wy) >= NOT_ROTATE_TOLERANCE)? road_camber + wy*dt : road_camber;
        static unsigned long saved_time = millis();
        if (millis() - saved_time > 250) {
            Serial.printf("Inclinaison: %.2f, Pente: %.2f\n", roll_angle, road_camber);
            saved_time = millis();
        }

        t0 = t;
        wx0 = wx;
        wy0 = wy;
    }
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
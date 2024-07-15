#include "MyTaskRunner.h"
#include "device.h"

void setup() {
    Serial.begin(115200);
    TaskRunner.launch(&device, device.tag, device.stack_size, device.priority);
}

void loop() {
    // Serial.printf("Acc: %.2f Speed: %.1f m/s, distance: %.1f m\n", inter.acc, inter.speed, inter.distance);
    // Serial.printf("Inclinaison: %.2f, Pente: %.2f\n", inter.roll_angle, inter.road_camber);
    // delay(250);
}
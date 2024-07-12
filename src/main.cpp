#include "MyTaskRunner.h"
#include "device.h"

void setup() {
    Serial.begin(115200);
    TaskRunner.launch(&device, device.tag, device.stack_size, device.priority);
}

void loop() {
}
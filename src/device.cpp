#include "device.h"

Device device;

Device::Device() {
    _task_id = set_task_id();
    tag = ":DEVICE";
    stack_size = 16;
    priority = 1;
}

Device::~Device() {}

void Device::setup() {

}

void Device::loop() {

}
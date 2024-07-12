#ifndef MAIN_H
#define MAIN_H

#include "MyTask.h"

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
};

extern Device device;

#endif // MAIN_H
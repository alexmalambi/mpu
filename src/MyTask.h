/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyTask.h
 * Author: pascalkemajou
 *
 * Created on 18 novembre 2017, 19:36
 */

#ifndef MYTASK_H
#define MYTASK_H
//#include "MyTaskRunner.h"
#include <Arduino.h>

class MyTask {
public:

    virtual void setup() {};
    virtual void loop() {};
    //virtual String getTaskName(){}; 
    const uint16_t set_task_id();

protected:
private:
    static uint16_t task_number;
};

#endif /* MYTASK_H */


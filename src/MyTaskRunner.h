/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyTaskRunner.h
 * Author: pascalkemajou
 *
 * Created on 18 novembre 2017, 20:13
 */

#ifndef MYTASKRUNNER_H
#define MYTASKRUNNER_H

#define MYTASK_STACK_SIZE                             5126
// #define MYTASK_PRIO                                   0

#include "MyTask.h"

class MyTaskRunner {
public:
    void launch(MyTask *_task);
    /**
     * @brief low to high [0 ~ 4]
    */
    void launch(MyTask *_task, int task_priority);
    void launch(MyTask *_task, int task_priority, int stack_size);
    void launch(MyTask* _task, const char* task_name, int stack_size, int task_priority);

private:
    
    UBaseType_t _task_priority = 0;
protected:
    static void task_runner(void *_task);
};

extern MyTaskRunner TaskRunner;

#endif /* MYTASKRUNNER_H */


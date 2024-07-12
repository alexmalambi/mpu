/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MyTask.h"

uint16_t MyTask::task_number = 0;
//void MyTask::task_runner(void *_this) {
//
//    MyTask* dsl = (MyTask*) _this;
//    dsl->setup();
//
//    while (1) {
//        dsl->loop();
//    }
//}
//
//void MyTask::beginTask() {
//    xTaskCreate(task_runner, "client_task", MYTASK_STACK_SIZE, (void *) this, MYTASK_PRIO, NULL);
//}

const uint16_t MyTask::set_task_id()
{
  MyTask::task_number ++;
  return (const uint16_t)task_number;
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MyTaskRunner.h"

MyTaskRunner TaskRunner;

void MyTaskRunner::task_runner(void *_task) {

  MyTask* mytask = (MyTask*) _task;
  mytask->setup();
  //
  while (1) {
    mytask->loop();
    vTaskDelay(5/ portTICK_PERIOD_MS);
  }
}

void MyTaskRunner::launch(MyTask* _task) {
  xTaskCreate(task_runner, "client_task", MYTASK_STACK_SIZE, _task, this->_task_priority, NULL);
}

void MyTaskRunner::launch(MyTask* _task, int task_priority) {
  this->_task_priority = task_priority;
  xTaskCreate(task_runner, "client_task", MYTASK_STACK_SIZE, _task, this->_task_priority, NULL);
}

void MyTaskRunner::launch(MyTask* _task, const char* task_name, int stack_size, int task_priority)
{
  xTaskCreate(task_runner, task_name, MYTASK_STACK_SIZE, _task, task_priority, NULL);
}
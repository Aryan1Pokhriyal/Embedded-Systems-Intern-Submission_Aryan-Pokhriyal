# Problem Statement 1: RTOS Task and Queue Management

This project demonstrates the use of **FreeRTOS tasks**, **queues**, and **dynamic priority management** in an embedded system context using C.

## Code

- Two FreeRTOS tasks:
  - 'ExampleTask1': Periodically sends the data (every 500ms) to a queue.
  - 'ExampleTask2': Receives the data from the queue and:
    - Dynamically adjusts its own priority based on received values.
    - Deletes itself based on received values.

- Uses 'xQueueSend', 'xQueueReceive', 'vTaskPrioritySet', and 'vTaskDelete'.

- Queue size: 5 messages of a custom 'Data_t' struct.

#include <stdio.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Define the data structure
typedef struct {
    uint8_t dataID;
    int32_t dataValue;
} Data_t;

// Define the gloabal variables to get data from, the ID and it's value
uint8_t G_DataID = 1;
int32_t G_DataValue = 0;

// Define the task handles
TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

// Define the queue handles
QueueHandle_t Queue1;

// ExampleTask1 code
void ExampleTask1(void *pV) {
    
    // Define the data to be sent
    Data_t dataToSend;

    // Define the delay to be 500ms
    const TickType_t delay = pdMS_TO_TICKS(500);

    // Get the last waking time 
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (1) {
        // Put the global data values into the data to be sent
        dataToSend.dataID = G_DataID;
        dataToSend.dataValue = G_DataValue;

        // Send this data to the queue
        xQueueSend(Queue1, &dataToSend, portMAX_DELAY);
        printf("Data sent to queue: ID = %d, Value = %ld\n", dataToSend.dataID, dataToSend.dataValue);

        // Delay for 500ms
        vTaskDelayUntil(&lastWakeTime, delay);
    }
}

// Task2: Receives and processes data based on logic
void ExampleTask2(void *pV) {

    // Define the variable to recieve data
    Data_t receivedData;

    // Get the original priority of the task
    UBaseType_t originalPriority = uxTaskPriorityGet(NULL);

    // Flag variable to check if the priority has been increased
    BaseType_t priorityIncreased = pdFALSE;

    while (1) {

        // Condition for if the data has been recieved from the queue
        if (xQueueReceive(Queue1, &receivedData, portMAX_DELAY) == pdPASS) {

            // Print the received data
            printf("Data received: ID = %d, Value = %ld\n", 
                   receivedData.dataID, receivedData.dataValue);

            // Check the data ID
            if (receivedData.dataID == 0) {

                // If ID is 0, deletes the task
                printf("ID is 0, deleting task2\n");
                vTaskDelete(NULL);
            }

            if (receivedData.dataID == 1) {

                // Check for the data Value
                if (receivedData.dataValue == 0 && priorityIncreased == pdFALSE) {
                    // Increase the priority and update flag
                    vTaskPrioritySet(NULL, originalPriority + 2);
                    priorityIncreased = pdTRUE;
                    printf("Value = 0, priority increased by 2\n");
                } else if (receivedData.dataValue == 1 && priorityIncreased == pdTRUE) {
                    // Reset the priority and update the flag
                    vTaskPrioritySet(NULL, originalPriority);
                    priorityIncreased = pdFALSE;
                    printf("Value = 1, priority reset to original\n");
                } else if (receivedData.dataValue == 2) {
                    // Delete the Task2
                    printf("Value = 2, deleting task2\n");
                    vTaskDelete(NULL);
                }
            }
        }
    }
}

// Main function
int main(void) {
    // Creating the queue
    Queue1 = xQueueCreate(5, sizeof(Data_t));

    // If the queue is not created, display appropriate message
    if (Queue1 == NULL) {
        printf("Queue failed\n");
        while (1); // To stop the flow 
    }

    // Creating the tasks 
    xTaskCreate(ExampleTask1, "Task1", 1000, NULL, 2, &TaskHandle_1);  // Priority 2 (higher priority - to run every 500ms without fail)
    xTaskCreate(ExampleTask2, "Task2", 1000, NULL, 1, &TaskHandle_2);// Priorty 1

    //Initiate the scheduler
    vTaskStartScheduler();

    return 0;
}

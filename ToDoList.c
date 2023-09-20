#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK 100

// Structure to represent a task
struct Task {
    int id;
    char title[100];
    char desc[500];
    char status[30];
    int deadline;
};

int taskCount = 0;

// Function to add a new task
void addTask(struct Task tasks[], const char *title, const char *desc, const char *status, int deadline) {
    if (taskCount < MAX_TASK) {
        struct Task newTask;
        newTask.id = taskCount + 1; // Auto-incrementing ID
        strncpy(newTask.title, title, sizeof(newTask.title));
        strncpy(newTask.desc, desc, sizeof(newTask.desc));
        strncpy(newTask.status, status, sizeof(newTask.status));
        newTask.deadline = deadline;
        tasks[taskCount] = newTask;
        taskCount++;
        printf("Task added successfully!\n");
    } else {
        printf("The task list is full. Cannot add more tasks.\n");
    }
}

int main() {
    struct Task tasks[MAX_TASK];
    int choice, deadline;
    char title[100], desc[500], status[30];

   do {
        printf("==================================Welcome to the Task Management Application!==================================\n");
        printf("=      1. Add a new task                                                                                      =\n");
        printf("=      2. Add multiple tasks                                                                                  =\n");
        printf("=      3. Display the list of all tasks                                                                       =\n");
        printf("=      4. Modify a task                                                                                       =\n");
        printf("=      5. Delete a task                                                                                       =\n");
        printf("=      6. Search for a task by ID                                                                             =\n");
        printf("=      7. Search for a task by title                                                                          =\n");
        printf("=      8. Display statistics                                                                                  =\n");
        printf("=      9. Quit                                                                                                =\n");
        printf("==================================================Enter your choice:===========================================\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the title of the task: ");
                scanf("%99s", title);
                printf("Enter the description of the task: ");
                scanf("%499s", desc);
                printf("Enter the status of the task: ");
                scanf("%29s", status);
                printf("Enter the deadline: ");
                scanf("%d", &deadline);
                addTask(tasks, title, desc, status, deadline);
                break;
            case 2:
                // Add code to add multiple tasks here
                break;
            case 3:
                // Add code to display tasks here
                break;
            case 4:
                // Add code to modify a task here
                break;
            case 5:
                // Add code to delete a task here
                break;
            case 6:
                // Add code to search for a task by ID here
                break;
            case 7:
                // Add code to search for a task by title here
                break;
            case 8:
                // Add code to display statistics here
                break;
            case 9:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    
  } while (choice != 9);
    return 0;
}

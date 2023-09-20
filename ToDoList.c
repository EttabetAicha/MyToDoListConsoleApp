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
    int choice, deadline,rept;
    char title[100], desc[500], status[30];

   do {
         printf("==================================Bienvenue dans l'application de gestion de taches!==================================\n");
        printf("=      1. Ajouter une nouvelle tache                                                                                 =\n");
        printf("=      2. Ajouter plusieur tache                                                                                     =\n");
        printf("=      3. Afficher la liste de toutes les taches                                                                     =\n");
        printf("=      4. Modifier une tache                                                                                         =\n");
        printf("=      5. Supprimer une tache                                                                                        =\n");
        printf("=      6. Rechercher une tache par identifiant                                                                       =\n");
        printf("=      7. Rechercher une tache par titre                                                                             =\n");
        printf("=      8. Afficher les statiques                                                                                     =\n");
        printf("=      9. Quitter                                                                                                    =\n");
        printf("==================================================Entrez votre choix :================================================ \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter titre du tache: ");
                scanf("%99s", title);
                printf("Enter une description du tache : ");
                scanf("%499s", desc);
                printf("Enter une status pour la tache: ");
                scanf("%29s", status);
                printf("Enter  deadline du tache : ");
                scanf("%d", &deadline);
                addTask(tasks, title, desc, status, deadline);
                break;
            case 2:
               
                printf("Enter the number of tasks to add (1-5): ");
                scanf("%d", &rept);

                if (rept >= 1 && rept <= 5) {
                    for (int i = 0; i < rept; i++) {
                        printf("Enter the title of the task: ");
                        scanf("%99s", title);

                        printf("Enter the description of the task: ");
                        scanf("%499s", desc);

                        printf("Enter the status of the task: ");
                        scanf("%29s", status);

                        printf("Enter the deadline of the task: ");
                        scanf("%d", &deadline);

                        addTask(tasks, title, desc, status, deadline);
                    }
                } else {
                    printf("Invalid input. Please enter a number between 1 and 5.\n");
                }
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

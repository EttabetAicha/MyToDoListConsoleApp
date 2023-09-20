#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK 100

struct Task {
    int id;
    char title[100];
    char desc[500];
    char status[30];
    int deadline;
};

int taskCount = 0;

void addTask(struct Task tasks[], const char *title, const char *desc, const char *status, int deadline) {
    if (taskCount < MAX_TASK) {
        struct Task newTask;
        newTask.id = taskCount + 1; // Auto-incrementing ID
        strncpy(newTask.title, title, sizeof(newTask.title) - 1);
        newTask.title[sizeof(newTask.title) - 1] = '\0'; // Ensure null-terminated string
        strncpy(newTask.desc, desc, sizeof(newTask.desc) - 1);
        newTask.desc[sizeof(newTask.desc) - 1] = '\0'; // Ensure null-terminated string
        strncpy(newTask.status, status, sizeof(newTask.status) - 1);
        newTask.status[sizeof(newTask.status) - 1] = '\0'; // Ensure null-terminated string
        newTask.deadline = deadline;
        tasks[taskCount] = newTask;
        taskCount++;
        printf("Task added successfully!\n");
    } else {
        printf("The task list is full. Cannot add more tasks.\n");
    }
}

// Function to display the menu and get the user's choice
int getMenuChoice() {
    int choice;
    printf("\n==================================Bienvenue dans l'application de gestion de taches!==================================\n");
    printf("  =      1. Ajouter une nouvelle tache                                                                                   =\n");
    printf("  =      2. Ajouter plusieurs taches                                                                                     =\n");
    printf("  =      3. Afficher la liste de toutes les taches                                                                       =\n");
    printf("  =      4. Modifier une tache                                                                                           =\n");
    printf("  =      5. Supprimer une tache                                                                                          =\n");
    printf("  =      6. Rechercher une tache par identifiant                                                                         =\n");
    printf("  =      7. Rechercher une tache par titre                                                                               =\n");
    printf("  =      8. Afficher les statistiques                                                                                    =\n");
    printf("  =      9. Quitter                                                                                                      =\n");
    printf("  ================================================Entrez votre choix :==================================================== \n");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear input buffer
    return choice;
}

int main() {
    struct Task tasks[MAX_TASK];
    int choice, deadline, rept;
    char title[100], desc[500], status[30];

    do {
        choice = getMenuChoice();

        switch (choice) {
            case 1:
                printf("Enter titre du tache: ");
                fgets(title, sizeof(title), stdin);
                printf("Enter une description du tache : ");
                fgets(desc, sizeof(desc), stdin);
                printf("Enter une status pour la tache: ");
                fgets(status, sizeof(status), stdin);
                printf("Enter deadline du tache : ");
                scanf("%d", &deadline);
                while (getchar() != '\n'); // Clear input buffer
                addTask(tasks, title, desc, status, deadline);
                break;
            case 2:
                printf("Enter the number of tasks to add (1-5): ");
                scanf("%d", &rept);
                while (getchar() != '\n'); // Clear input buffer

                if (rept >= 1 && rept <= 5) {
                    for (int i = 0; i < rept; i++) {
                        printf("Enter the title of the task: ");
                        fgets(title, sizeof(title), stdin);
                        printf("Enter the description of the task: ");
                        fgets(desc, sizeof(desc), stdin);
                        printf("Enter the status of the task: ");
                        fgets(status, sizeof(status), stdin);
                        printf("Enter the deadline of the task: ");
                        scanf("%d", &deadline);
                        while (getchar() != '\n'); // Clear input buffer

                        addTask(tasks, title, desc, status, deadline);
                    }
                } else {
                    printf("Invalid input. Please enter a number between 1 and 5.\n");
                }
           case 3:
                  if (taskCount == 0) {
                    printf("Aucune tache à afficher.\n");
                } else {
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("| %-3s | %-30s | %-60s | %-20s | %-10s |\n", "ID", "Titre", "Description", "Statut", "Deadline");
                    printf("------------------------------------------------------------------------------------------------------------------------\n");

                    for (int i = 0; i < taskCount; i++) {
                        printf("| %-3d | %-30s | %-60s | %-20s | %-10d |\n",
                            tasks[i].id,
                            tasks[i].title,
                            tasks[i].desc,
                            tasks[i].status,
                            tasks[i].deadline);
                    }

                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                }

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_TASK 100
struct Task {
    int id;
    char title[100];
    char desc[200];
    time_t deadline;
    char status[30];
    time_t creationDate;
   
};
int parseDate(const char* dateStr, struct tm* result) {
    if (strlen(dateStr) != 10) {
        return 0;  // Invalid length
    }

    if (dateStr[4] != '-' || dateStr[7] != '-') {
        return 0;  // Invalid format
    }

    memset(result, 0, sizeof(struct tm));  // Initialize the result struct

    result->tm_year = atoi(dateStr) - 1900;  // Year since 1900
    result->tm_mon = atoi(dateStr + 5) - 1;  // Month (0-based)
    result->tm_mday = atoi(dateStr + 8);     // Day

    return 1;  // Parsing successful
}

int taskCount = 0;

void addTask(struct Task tasks[], int* numTasks) {
    // Check if the maximum number of tasks is reached
    if (*numTasks >= MAX_TASK) {
        printf("The maximum number of tasks has been reached.\n");
        return;
    }

    // Variables to store user input
    char dateStr[20];

    // Create a new task
    struct Task newTask;
    newTask.id = *numTasks + 1;

    printf("Enter the title of the task: ");
    scanf(" %[^\n]", newTask.title);

    printf("Enter the description of the task: ");
    scanf(" %[^\n]", newTask.desc);

    printf("Enter the deadline (in YYYY-MM-DD format): ");
    scanf("%19s", dateStr);

    struct tm deadline;  // Declare struct tm variable
    if (parseDate(dateStr, &deadline)) {
        // Convert the parsed time to a time_t value
        newTask.deadline = mktime(&deadline);
    } else {
        printf("Invalid date format. Please use YYYY-MM-DD.\n");
        return;
    }

    printf("Enter the status of the task: ");
    scanf(" %[^\n]", newTask.status);

    newTask.creationDate = time(NULL);

    // Add the new task to the array
    tasks[*numTasks] = newTask;
    (*numTasks)++;

    printf("\n\t \t \t \t \t *Task added successfully.*\n");
}
void addMultipleTasks(struct Task* tasks, int* numTasks) {
    int numNewTasks;
    printf("Combien de taches souhaitez-vous ajouter ? ");
    scanf("%d", &numNewTasks);

    for (int i = 0; i < numNewTasks; i++) {
        printf("Tache #%d :\n", i + 1);
        addTask(tasks, numTasks);
    }
}
int compareTasksByTitle(const void* a, const void* b) {
    const struct Task* taskA = (const struct Task*)a;
    const struct Task* taskB = (const struct Task*)b;
    return strcmp(taskA->title, taskB->title);
}

// Comparateur pour le tri par deadline
int compareTasksByDeadline(const void* a, const void* b) {
    const struct Task* taskA = (const struct Task*)a;
    const struct Task* taskB = (const struct Task*)b;
    return difftime(taskA->deadline, taskB->deadline);
}

void displayTasks(struct Task* tasks, int numTasks) {
       if (numTasks == 0) {
        printf("Aucune tache trouvae.\n");
        return;
    }

    int choice;
    printf("\n  ================================Menu d'affichage des taches :=============================================\n\n");
    printf("  *      \t \t  \t 1. Trier les taches par ordre alphabetique\n");
    printf("  *      \t \t  \t 2. Trier les taches par deadline \n");
    printf("  *      \t \t  \t 3. Afficher les taches dont le deadline est dans 3 jours ou moins\n");
    printf("  *      \t \t  \t 4. Afficher toutes les taches\n\n");
    printf("  ========================================Selectionnez une option============================================= \n");
    scanf("%d", &choice);

    switch (choice) {
            case 1:
                    // Triez les taches par ordre alphabétique du titre
                    qsort(tasks, numTasks, sizeof(struct Task), compareTasksByTitle);
                    // Header row
                    printf("_____________________________________________________________________________________________________________________________________\n");
                    printf("| %-14s | %-24s | %-39s | %-19s | %-39s \n", "Identifiant", "Titre", "Description", "Statut","Deadline" );
                    printf("_____________________________________________________________________________________________________________________________________\n");
                    // Data rows
                    for (int i = 0; i < numTasks; i++) {
                        printf("| %-14d | %-24s | %-39s | %-19s | %-39s \n", tasks[i].id, tasks[i].title, tasks[i].desc, tasks[i].status, ctime(&tasks[i].deadline));
                    }
                    printf("_____________________________________________________________________________________________________________________________________\n");
            break;

        case 2:
            // Triez les taches par deadline
            qsort(tasks, numTasks, sizeof(struct Task), compareTasksByDeadline);
            printf("_____________________________________________________________________________________________________________________________________\n");
            printf(" %-14s | %-24s | %-39s | %-19s | %-39s \n", "Identifiant", "Titre", "Description", "Statut","Deadline" );
            printf("_____________________________________________________________________________________________________________________________________\n");
            for (int i = 0; i < numTasks; i++) {
                printf("| %-14d | %-24s | %-39s | %-19s | %-39s \n", tasks[i].id, tasks[i].title, tasks[i].desc, tasks[i].status, ctime(&tasks[i].deadline));
            }
            printf("_____________________________________________________________________________________________________________________________________\n");
            break;
        case 3:
            {
                time_t currentTime = time(NULL);
                time_t threeDaysLater = currentTime + 3 * 24 * 3600; // 3 jours plus tard
                printf("Taches dont le deadline est dans 3 jours ou moins :\n");
                printf("_____________________________________________________________________________________________________________________________________\n");
                printf(" %-14s | %-24s | %-39s | %-19s | %-39s \n", "Identifiant", "Titre", "Description", "Statut","Deadline" );
                printf("_____________________________________________________________________________________________________________________________________\n");
                for (int i = 0; i < numTasks; i++) {
                    if (tasks[i].deadline <= threeDaysLater) {
                        printf("| %-14d | %-24s | %-39s | %-19s | %-39s \n", tasks[i].id, tasks[i].title, tasks[i].desc, tasks[i].status, ctime(&tasks[i].deadline));
                    }
                }
                printf("_____________________________________________________________________________________________________________________________________\n");

            }
            break;
        case 4:
            printf("Tout les tache :\n");
            printf("_____________________________________________________________________________________________________________________________________\n");
            printf(" %-14s | %-24s | %-39s | %-19s | %-39s \n", "Identifiant", "Titre", "Description", "Statut","Deadline" );
            printf("_____________________________________________________________________________________________________________________________________\n");
            for (int i = 0; i < numTasks; i++) {
                printf("| %-14d | %-24s | %-39s | %-19s | %-39s \n", tasks[i].id, tasks[i].title, tasks[i].desc, tasks[i].status, ctime(&tasks[i].deadline));
                printf("_____________________________________________________________________________________________________________________________________\n");

            }
            printf("_____________________________________________________________________________________________________________________________________\n");
            break;

        default:
            printf("Option invalide.\n");
            break;
    }
}


int main() {
    struct Task tasks[100]; // Tableau de taches (modifiable pour garer plus de taches)
    int numTasks = 0;
    while (1) {
    printf("\n  ================================Bienvenue dans l'application de gestion de taches!========\n\n");
    printf("  *      \t \t  \t 1. Ajouter une nouvelle tache                             *\n");
    printf("  *      \t \t  \t 2. Ajouter plusieurs taches                               *\n");
    printf("  *      \t \t  \t 3. Afficher la liste de toutes les taches                 *\n");
    printf("  *      \t \t  \t 4. Modifier une tache                                     *\n");
    printf("  *      \t \t  \t 5. Supprimer une tache                                    *\n");
    printf("  *      \t \t  \t 6. Rechercher une tache par identifiant                   *\n");
    printf("  *      \t \t  \t 7. Rechercher une tache par titre                         *\n");
    printf("  *      \t \t  \t 8. Afficher les statistiques                              *\n");
    printf("  *      \t \t  \t 9. Quitter                                                *\n\n");
    printf("  ========================================Entrez votre choix :============================== \n");
    int choice;
    scanf("%d", &choice);
        switch (choice) {
            case 1:
                addTask(tasks, &numTasks);
                break;
            case 2:
                addMultipleTasks(tasks, &numTasks);
                break;
            case 3:
                  displayTasks(tasks, numTasks);
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
    } ;

    return 0;
}

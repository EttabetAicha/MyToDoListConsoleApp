#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100

struct Task {
    int id;
    char title[100];
    char description[200];
    time_t deadline;
    char status[30];
    time_t creationDate;
};

// Function to parse a date string in the format "YYYY-MM-DD"
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
        printf("Aucune tâche trouvée.\n");
        return;
    }

    int choice;
    printf("Menu d'affichage des tâches :\n");
    printf("1. Trier les tâches par ordre alphabétique\n");
    printf("2. Trier les tâches par deadline\n");
    printf("3. Afficher les tâches dont le deadline est dans 3 jours ou moins\n");
    printf("4. Afficher toutes les tâches\n");
    printf("Sélectionnez une option : ");
    scanf("%d", &choice);

    switch (choice) {
            case 1:
            // Triez les tâches par ordre alphabétique du titre
            qsort(tasks, numTasks, sizeof(struct Task), compareTasksByTitle);
            printf("%-15s %-25s %-40s %-20s %-15s\n", "Identifiant", "Titre", "Description", "Deadline", "Statut");
            for (int i = 0; i < numTasks; i++) {
                printf("%-15d %-25s %-40s %-20s %-15s\n", tasks[i].id, tasks[i].title, tasks[i].description, ctime(&tasks[i].deadline), tasks[i].status);
            }
            break;
        case 2:
            // Triez les tâches par deadline
            qsort(tasks, numTasks, sizeof(struct Task), compareTasksByDeadline);
            printf("%-15s %-25s %-40s %-20s %-15s\n", "Identifiant", "Titre", "Description", "Deadline", "Statut");
            for (int i = 0; i < numTasks; i++) {
                printf("%-15d %-25s %-40s %-20s %-15s\n", tasks[i].id, tasks[i].title, tasks[i].description, ctime(&tasks[i].deadline), tasks[i].status);
            }
            break;
        case 3:
            {
                time_t currentTime = time(NULL);
                time_t threeDaysLater = currentTime + 3 * 24 * 3600; // 3 jours plus tard
                printf("Taches dont le deadline est dans 3 jours ou moins :\n");
                for (int i = 0; i < numTasks; i++) {
                    if (tasks[i].deadline <= threeDaysLater) {
                        // Affichez les détails de la tâche
                    }
                }
            }
            break;
        case 4:
            // Affichez toutes les tâches sans tri
            for (int i = 0; i < numTasks; i++) {
                // Affichez les détails de chaque tâche (identifiant, titre, description, deadline, statut, etc.)
            }
            break;
        default:
            printf("Option invalide.\n");
            break;
    }
}
// Function to add a new task
void addTask(struct Task tasks[], int* numTasks) {
    // Check if the maximum number of tasks is reached
    if (*numTasks >= MAX_TASKS) {
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
    scanf(" %[^\n]", newTask.description);

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

    printf("Task added successfully.\n");
}

// Function to modify a task
void modifyTask(struct Task* tasks, int numTasks) {
    // Demandez à l'utilisateur l'identifiant de la tache à modifier
    int taskId;
    printf("Enter the ID of the task to modify: ");
    scanf("%d", &taskId);

    // Recherchez la tache par son identifiant
    int taskIndex = -1;
    for (int i = 0; i < numTasks; i++) {
        if (tasks[i].id == taskId) {
            taskIndex = i;
            break;
        }
    }

    if (taskIndex == -1) {
        printf("Task not found.\n");
        return;
    }

    // Affichez les détails de la tâche actuelle
    printf("Current Task:\n");
    printf("ID: %d\n", tasks[taskIndex].id);
    printf("Title: %s\n", tasks[taskIndex].title);
    printf("Description: %s\n", tasks[taskIndex].description);
    printf("Deadline: %s", ctime(&tasks[taskIndex].deadline));
    printf("Status: %s\n", tasks[taskIndex].status);

    // Menu de modification
    printf("\nModification Menu:\n");
    printf("1. Modify description\n");
    printf("2. Modify status\n");
    printf("3. Modify deadline\n");
    printf("4. Cancel modification\n");
    printf("Select an option: ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the new description: ");
            scanf(" %[^\n]", tasks[taskIndex].description);
            break;
        case 2:
            printf("Enter the new status: ");
            scanf(" %[^\n]", tasks[taskIndex].status);
            break;
        case 3:
            printf("Enter the new deadline (in YYYY-MM-DD format): ");
            char dateStr[20];
            scanf("%19s", dateStr);
            struct tm newDeadline;

            // Clear the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            if (parseDate(dateStr, &newDeadline)) {
                tasks[taskIndex].deadline = mktime(&newDeadline);
                printf("Deadline modified successfully.\n");
            } else {
                printf("Invalid date format. Please use YYYY-MM-DD.\n");
            }
            break;
        case 4:
            printf("Modification canceled.\n");
            break;
        default:
            printf("Invalid option.\n");
            break;
    }
}

// Fonction pour supprimer une tache par identifiant
void deleteTask(struct Task* tasks, int* numTasks, int taskId) {
    // Recherchez la tache par son identifiant
    int taskIndex = -1;
    for (int i = 0; i < *numTasks; i++) {
        if (tasks[i].id == taskId) {
            taskIndex = i;
            break;
        }
    }

    if (taskIndex == -1) {
        printf("Tache non trouvée.\n");
        return;
    }

    // Supprimez la tache en déplaçant les éléments suivants vers le haut
    for (int i = taskIndex; i < *numTasks - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    (*numTasks)--;
    printf("Tache supprimée avec succès.\n");
}


// Fonction pour rechercher une tache par identifiant
void searchTaskById(struct Task* tasks, int numTasks, int taskId) {
    // Recherchez la tache par son identifiant
    int taskIndex = -1;
    for (int i = 0; i < numTasks; i++) {
        if (tasks[i].id == taskId) {
            taskIndex = i;
            break;
        }
    }

    if (taskIndex == -1) {
        printf("Tache non trouvée.\n");
        return;
    }

    // Affichez les détails de la tache trouvée
    printf("Tache trouvée :\n");
    printf("Identifiant : %d\n", tasks[taskIndex].id);
    printf("Titre : %s\n", tasks[taskIndex].title);
    printf("Description : %s\n", tasks[taskIndex].description);
    printf("Deadline : %s", ctime(&tasks[taskIndex].deadline));
    printf("Statut : %s\n", tasks[taskIndex].status);
    printf("Date de création : %s", ctime(&tasks[taskIndex].creationDate));

    // Vous pouvez également afficher la liste des collaborateurs ici si cette fonctionnalité est implémentée
}


// Fonction pour rechercher une tache par titre
void searchTaskByTitle(struct Task* tasks, int numTasks, const char* title) {
    // Parcourez toutes les taches pour trouver celles qui correspondent au titre
    int foundTasks = 0;

    for (int i = 0; i < numTasks; i++) {
        if (strcmp(tasks[i].title, title) == 0) {
            foundTasks++;
            printf("Tache trouvée :\n");
            printf("Identifiant : %d\n", tasks[i].id);
            printf("Titre : %s\n", tasks[i].title);
            printf("Description : %s\n", tasks[i].description);
            printf("Deadline : %s", ctime(&tasks[i].deadline));
            printf("Statut : %s\n", tasks[i].status);
            printf("Date de création : %s", ctime(&tasks[i].creationDate));
        }
    }

    if (foundTasks == 0) {
        printf("Aucune tache trouvée avec le titre \"%s\".\n", title);
    }
}
void addMultipleTasks(struct Task* tasks, int* numTasks) {
    int numNewTasks;
    printf("Combien de tâches souhaitez-vous ajouter ? ");
    scanf("%d", &numNewTasks);

    for (int i = 0; i < numNewTasks; i++) {
        printf("Tâche #%d :\n", i + 1);
        addTask(tasks, numTasks);
    }
}


void displayStatistics(struct Task* tasks, int numTasks) {
    int totalTasks = numTasks;
    int completedTasks = 0;
    int incompleteTasks = 0;

    time_t currentTime = time(NULL);

    for (int i = 0; i < numTasks; i++) {
        if (strcmp(tasks[i].status, "finalisée") == 0) {
            completedTasks++;
        } else {
            incompleteTasks++;
        }

        int daysRemaining = (int)difftime(tasks[i].deadline, currentTime) / (24 * 3600);
        printf("Tâche #%d - Deadline dans %d jours\n", tasks[i].id, daysRemaining);
    }

    printf("Nombre total de tâches : %d\n", totalTasks);
    printf("Tâches complétées : %d\n", completedTasks);
    printf("Tâches incomplètes : %d\n", incompleteTasks);
}


int main() {
    struct Task tasks[100]; // Tableau de taches (modifiable pour gérer plus de taches)
    int numTasks = 0;
    char searchTitle[100];
    int taskId;
    int searchId;

    while (1) {
        printf("\nMenu principal:\n");
        printf("1. Ajouter une nouvelle tache\n");
        printf("2. Ajouter plusieurs taches\n");
        printf("3. Afficher la liste de toutes les taches\n");
        printf("4. Modifier une tache\n");
        printf("5. Supprimer une tache par identifiant\n");
        printf("6. Rechercher une tache par titre\n");
        printf("7. Rechercher une tache par titre\n");
        printf("8. Afficher les statistiques \n");
        printf("9. Quitter \n");

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
                modifyTask(tasks, numTasks);
                break;
            case 5:
                // Demandez à l'utilisateur l'identifiant de la tache à supprimer
                printf("Entrez l'identifiant de la tache à supprimer: ");
                scanf("%d", &taskId);
                deleteTask(tasks, &numTasks, taskId);
                break;
            case 6:
                // Demandez à l'utilisateur l'identifiant de la tache à rechercher
                printf("Entrez l'identifiant de la tache à rechercher: ");
                scanf("%d", &searchId);
                searchTaskById(tasks, numTasks, searchId);
                break;
            case 7:
                // Demandez à l'utilisateur le titre de la tache à rechercher
                printf("Entrez le titre de la tache à rechercher: ");
                scanf("%s", searchTitle);
                searchTaskByTitle(tasks, numTasks, searchTitle);
                break;
            case 8:
                displayStatistics(tasks, numTasks);
                break;
            case 9:
                // Quitter l'application
                exit(0);
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}

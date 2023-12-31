#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_TASK 100
struct Task
{
    int id;
    char title[100];
    char desc[200];
    time_t deadline;
    char status[30];
    time_t creationDate;
};
int parseDate(const char *dateStr, struct tm *result)
{
    if (strlen(dateStr) != 10)
    {
        return 0; // Invalid length
    }

    if (dateStr[4] != '-' || dateStr[7] != '-')
    {
        return 0; // Invalid format
    }

    memset(result, 0, sizeof(struct tm)); // Initialize the result struct

    result->tm_year = atoi(dateStr) - 1900; // Year since 1900
    result->tm_mon = atoi(dateStr + 5) - 1; // Month (0-based)
    result->tm_mday = atoi(dateStr + 8);    // Day

    return 1; // Parsing successful
}
int taskCount = 0;
void addTask(struct Task tasks[], int *numTasks)
{
    // Check if the maximum number of tasks is reached
    if (*numTasks >= MAX_TASK)
    {
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

    struct tm deadline; // Declare struct tm variable
    if (parseDate(dateStr, &deadline))
    {
        // Convert the parsed time to a time_t value
        newTask.deadline = mktime(&deadline);
    }
    else
    {
        printf("Invalid date format. Please use YYYY-MM-DD.\n");
        return;
    }

    printf("Enter the status of the task: ");
    scanf(" %[^\n]", newTask.status);

    newTask.creationDate = time(NULL);

    // Add the new task to the array
    tasks[*numTasks] = newTask;
    (*numTasks)++;
    printf(" _________________________________\n");
    printf("|\t\t\t          |\n");
    printf("|\tTASK ADD SUCCESSFULLY     |\n");
    printf("|_________________________________|\n");
}
void addMultipleTasks(struct Task *tasks, int *numTasks)
{
    int numNewTasks;
    printf("Combien de taches souhaitez-vous ajouter ? ");
    scanf("%d", &numNewTasks);

    for (int i = 0; i < numNewTasks; i++)
    {   printf("____________________________");
        printf("\t \t Tache #%d :\n", i + 1);
        printf("____________________________");
        addTask(tasks, numTasks);
    }
}
int compareTasksByTitle(const void *a, const void *b)
{
    const struct Task *taskA = a;
    const struct Task *taskB = b;
    return strcmp(taskA->title, taskB->title);
}
int compareTasksByDeadline(const void *a, const void *b)
{
    const struct Task *taskA = a;
    const struct Task *taskB = b;

    if (taskA->deadline < taskB->deadline)
    {
        return -1;
    }
    else if (taskA->deadline > taskB->deadline)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void displayTasks(struct Task *tasks, int numTasks)
{
    if (numTasks == 0)
    {
        printf("\t\t\t _________________________________\n");
        printf("\t\t\t|\t\t\t          |\n");
        printf("\t\t\t|\tAucune tache trouver      |\n");
        printf("\t\t\t|_________________________________|\n");
        return;
    }

    int choice;
    printf("\n  ================================Menu d'affichage des taches :==================================\n\n");
    printf("  *      \t \t  \t 1. Trier les taches par ordre alphabetique\n");
    printf("  *      \t \t  \t 2. Trier les taches par deadline \n");
    printf("  *      \t \t  \t 3. Afficher les taches dont le deadline est dans 3 jours ou moins\n");
    printf("  *      \t \t  \t 4. Afficher toutes les taches\n\n");
    printf("  ========================================Selectionnez une option=================================== \n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        // Triez les taches par ordre alphabétique du titre
        qsort(tasks, numTasks, sizeof(struct Task), compareTasksByTitle);
        printf("_________________________________________________________________________________________________________________________________________________________________\n");
        printf("| %-10s | %-24s | %-60s | %-19s | %-39s\n", "Identifiant", "Titre", "Description", "Statut", "Deadline");
        printf("_________________________________________________________________________________________________________________________________________________________________\n");
        for (int i = 0; i < numTasks; i++)
        {
            printf("| %-10d | %-24s | %-60s | %-19s | %-39s \n", tasks[i].id, tasks[i].title, tasks[i].desc, tasks[i].status, ctime(&tasks[i].deadline));
        }
        printf("_________________________________________________________________________________________________________________________________________________________________\n\n");
        break;

    case 2:
        // Triez les taches par deadline
        qsort(tasks, numTasks, sizeof(struct Task), compareTasksByDeadline);
        printf("_____________________________________________________________________________________________________________________________________________________________________\n");
        printf(" %-10s | %-24s | %-66s | %-19s | %-39s\n", "Identifiant", "Titre", "Description", "Statut", "Deadline");
        printf("_____________________________________________________________________________________________________________________________________________________________________\n");
        for (int i = 0; i < numTasks; i++)
        {
            printf("| %-10d | %-24s | %-66s | %-19s | %-39s\n", tasks[i].id, tasks[i].title, tasks[i].desc, tasks[i].status, ctime(&tasks[i].deadline));
        }
        printf("_____________________________________________________________________________________________________________________________________________________________________\n\n");
        break;
    case 3:
    {
        time_t currentTime = time(NULL);
        time_t threeDaysLater = currentTime + 3 * 24 * 3600; // 3 jours plus tard
        printf("Taches dont le deadline est dans 3 jours ou moins :\n");
        printf("____________________________________________________________________________________________________________________________________________________________________\n");
        printf(" %-10s | %-24s | %-66s | %-19s | %-39s \n", "Identifiant", "Titre", "Description", "Statut", "Deadline");
        for (int i = 0; i < numTasks; i++)
        {
            if (tasks[i].deadline <= threeDaysLater)
            {
                printf("| %-10d | %-24s | %-66s | %-19s | %-39s \n", tasks[i].id, tasks[i].title, tasks[i].desc, tasks[i].status, ctime(&tasks[i].deadline));
            }
        }
        printf("___________________________________________________________________________________________________________________________________________________________________\n\n");
    }
    break;
    case 4:
        printf("Tout les tache :\n");
        printf("______________________________________________________________________________________________________________________________________________________________________\n");
        printf(" %-10s | %-24s | %-66s | %-19s | %-39s \n", "Identifiant", "Titre", "Description", "Statut", "Deadline");
        printf("_____________________________________________________________________________________________________________________________________________________________________\n");
        for (int i = 0; i < numTasks; i++)
        {
            printf("| %-10d | %-24s | %-66s | %-19s | %-39s \n", tasks[i].id, tasks[i].title, tasks[i].desc, tasks[i].status, ctime(&tasks[i].deadline));
            printf("__________________________________________________________________________________________________________________________________________________________________\n\n");
        }
        printf("_____________________________________________________________________________________________________________________________________________________________________\n\n");
        break;

    default:
        printf("Option invalide.\n");
        break;
    }
}
void modifyTask(struct Task *tasks, int numTasks)
{
    int taskId;
    printf("Enter the ID of the task to modify: ");
    scanf("%d", &taskId);

    // Recherchez la tache par son identifiant
    int taskIndex = -1;
    for (int i = 0; i < numTasks; i++)
    {
        if (tasks[i].id == taskId)
        {
            taskIndex = i;
            break;
        }
    }
    if (taskIndex == -1)
    {
    printf(" _________________________________\n");
    printf("|\t\t\t          |\n");
    printf("|\tTASK NOT FOUND           |\n");
    printf("|_________________________________|\n");
        return;
    }
    // Affichez les datails de la tache actuelle
    printf("Current Task:\n");
    printf("ID: %d\n", tasks[taskIndex].id);
    printf("Title: %s\n", tasks[taskIndex].title);
    printf("Description: %s\n", tasks[taskIndex].desc);
    printf("Deadline: %s", ctime(&tasks[taskIndex].deadline));
    printf("Status: %s\n", tasks[taskIndex].status);

    // Menu de modification
    printf("____________________________");
    printf("\nModification Menu:\n");
    printf("____________________________");
    printf("1. Modify description\n");
    printf("2. Modify status\n");
    printf("3. Modify deadline\n");
    printf("4. Cancel modification\n");
    printf("Select an option: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Enter the new description: ");
        scanf(" %[^\n]", tasks[taskIndex].desc);
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
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        if (parseDate(dateStr, &newDeadline))
        {
            tasks[taskIndex].deadline = mktime(&newDeadline);
            printf("Deadline modified successfully.\n");
        }
        else
        {
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
void deleteTask(struct Task *tasks, int *numTasks, int taskId)
{
    // Recherchez la tache par son identifiant
    int taskIndex = -1;
    for (int i = 0; i < *numTasks; i++)
    {
        if (tasks[i].id == taskId)
        {
            taskIndex = i;
            break;
        }
    }

    if (taskIndex == -1)
    {
    printf(" _________________________________\n");
    printf("|\t\t\t          |\n");
    printf("|\tTASK NOT FOUND           |\n");
    printf("|_________________________________|\n");
        return;
    }

    // Supprimez la tache en daplaçant les alaments suivants vers le haut
    for (int i = taskIndex; i < *numTasks - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }

    (*numTasks)--;
    printf("\t\t\tTache supprimae avec succes.\n");
}
void searchTaskById(struct Task *tasks, int numTasks, int taskId)
{
    // Recherchez la tache par son identifiant
    int taskIndex = -1;
    for (int i = 0; i < numTasks; i++)
    {
        if (tasks[i].id == taskId)
        {
            taskIndex = i;
            break;
        }
    }

    if (taskIndex == -1)
    {
        printf("Tache non trouve.\n");
        return;
    }

    // Affichez les datails de la tache trouvae
    printf("_________________________________________________________________________________\n");
    printf("\t\t\t\tTache trouvae :\n");
    printf("_________________________________________________________________________________\n");
    printf("\t\t\t\tIdentifiant : %d\n", tasks[taskIndex].id);
    printf("\t\t\t\tTitre : %s\n", tasks[taskIndex].title);
    printf("\t\t\t\tDescription : %s\n", tasks[taskIndex].desc);
    printf("\t\t\t\tDeadline : %s", ctime(&tasks[taskIndex].deadline));
    printf("\t\t\t\tStatut : %s\n", tasks[taskIndex].status);
    printf("\t\t\t\tDate de craation : %s", ctime(&tasks[taskIndex].creationDate));
    printf("_________________________________________________________________________________\n");

}
void searchTaskByTitle(struct Task *tasks, int numTasks, const char *title)
{
    // Parcourez toutes les taches pour trouver celles qui correspondent au titre
    int foundTasks = 0;

    for (int i = 0; i < numTasks; i++)
    {
        if (strcmp(tasks[i].title, title) == 0)
        {
            foundTasks++;
            printf("_________________________________________________________________________________\n");
            printf("\t\t\t\tTache trouvae :\n");
            printf("_________________________________________________________________________________\n");
            printf("\t\t\t\tIdentifiant : %d\n", tasks[i].id);
            printf("\t\t\t\tTitre : %s\n", tasks[i].title);
            printf("\t\t\t\tDescription : %s\n", tasks[i].desc);
            printf("\t\t\t\tDeadline : %s", ctime(&tasks[i].deadline));
            printf("\t\t\t\tStatut : %s\n", tasks[i].status);
            printf("\t\t\t\tDate de craation : %s", ctime(&tasks[i].creationDate));
            printf("_________________________________________________________________________________\n");

        }
    }

    if (foundTasks == 0)
    {
        printf("Aucune tache trouvae avec le titre \"%s\".\n", title);
    }
}
void displayStatistics(struct Task *tasks, int numTasks)
{
    int totalTasks = numTasks;
    int completedTasks = 0;
    int incompleteTasks = 0;

    time_t currentTime = time(NULL);

    for (int i = 0; i < numTasks; i++)
    {
        if (strcmp(tasks[i].status, "finalise") == 0)
        {
            completedTasks++;
        }
        else
        {
            incompleteTasks++;
        }

        int daysRemaining = (int)difftime(tasks[i].deadline, currentTime) / (24 * 3600);
        printf("Tache #%d - Deadline dans %d jours\n", tasks[i].id, daysRemaining);
    }
    printf("_________________________________________________________________________________\n");
    printf("\t\t\t\tstatistique\n");
    printf("_________________________________________________________________________________\n");
    printf("\t\t\t\tNombre total de taches : %d\n", totalTasks);
    printf("\t\t\t\tTaches complates : %d\n", completedTasks);
    printf("\t\t\t\tTaches incompletes : %d\n", incompleteTasks);
    printf("_________________________________________________________________________________\n");
}

int main()
{
    struct Task tasks[100]; // Tableau de taches (modifiable pour garer plus de taches)
    int numTasks = 0;
    char searchTitle[100];
    int taskId;
    int searchId;
    while (1)
    {
        printf("\t\t\t\t\t =================Bienvenue dans l'application de gestion de taches!=============\n\n");
        printf("\t\t\t\t\t*      \t \t  \t 1. Ajouter une nouvelle tache                            *\n");
        printf("\t\t\t\t\t*      \t \t  \t 2. Ajouter plusieurs taches                              *\n");
        printf("\t\t\t\t\t*      \t \t  \t 3. Afficher la liste de toutes les taches                *\n");
        printf("\t\t\t\t\t*      \t \t  \t 4. Modifier une tache                                    *\n");
        printf("\t\t\t\t\t*      \t \t  \t 5. Supprimer une tache                                   *\n");
        printf("\t\t\t\t\t*      \t \t  \t 6. Rechercher une tache par identifiant                  *\n");
        printf("\t\t\t\t\t*      \t \t  \t 7. Rechercher une tache par titre                        *\n");
        printf("\t\t\t\t\t*      \t \t  \t 8. Afficher les statistiques                             *\n");
        printf("\t\t\t\t\t*      \t \t  \t 9. Quitter                                               *\n\n");
        printf("\t\t\t\t        ================================Entrez votre choix :=============================== \n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
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
            printf("Entrez l'identifiant de la tache a supprimer: ");
            scanf("%d", &taskId);
            deleteTask(tasks, &numTasks, taskId);
            break;
        case 6:
            printf("Entrez l'identifiant de la tache a rechercher: ");
            scanf("%d", &searchId);
            searchTaskById(tasks, numTasks, searchId);
            break;
        case 7:
            printf("Entrez le titre de la tache a rechercher: ");
            scanf("%s", searchTitle);
            searchTaskByTitle(tasks, numTasks, searchTitle);
            break;
        case 8:
            displayStatistics(tasks, numTasks);
            break;
        case 9:
            printf("Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    };

    return 0;
}

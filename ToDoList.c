#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter une tache
struct Task {
    int id;
    char title[100];
    char description[500];
    char deadline[20];
    char status[30];
};


// Fonction pour ajouter une tache
void addTask(struct Task* tasks[], int* taskCount) {
  
}

// Fonction pour afficher la liste de toutes les taches
void displayTasks(struct Task* tasks[], int taskCount) {
}

// Fonction pour modifier une tache
void modifyTask(struct Task* tasks[], int taskCount) {
}

// Fonction pour supprimer une tache par identifiant
void deleteTask(struct Task* tasks[], int* taskCount) {
}

// Fonction pour rechercher une tache par identifiant
void searchTaskById(struct Task* tasks[], int taskCount) {
}

// Fonction pour rechercher une tache par titre
void searchTaskByTitle(struct Task* tasks[], int taskCount) {
}

int main() {
    struct Task tasks[100]; // Vous pouvez ajuster la taille du tableau en fonction de vos besoins
    int taskCount = 0;
    int choice;

    while (1) {
        printf("==================================Bienvenue dans l'application de gestion de taches!==================================\n");
        printf("=      1. Ajouter une nouvelle tache                                                                                 =\n");
        printf("=      2. Ajouter plusieur tache                                                                                     =\n");
        printf("=      2. Afficher la liste de toutes les taches                                                                     =\n");
        printf("=      3. Modifier une tache                                                                                         =\n");
        printf("=      4. Supprimer une tache                                                                                        =\n");
        printf("=      5. Rechercher une tache par identifiant                                                                       =\n");
        printf("=      6. Rechercher une tache par titre                                                                             =\n");
        printf("=      2. Afficher les statiques                                                                                     =\n");
        printf("=      7. Quitter                                                                                                    =\n");
        printf("==================================================Entrez votre choix :================================================ \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                displayTasks(tasks, taskCount);
                break;
            case 3:
                modifyTask(tasks, taskCount);
                break;
            case 4:
                deleteTask(tasks, &taskCount);
                break;
            case 5:
                searchTaskById(tasks, taskCount);
                break;
            case 6:
                searchTaskByTitle(tasks, taskCount);
                break;
            case 7:
                printf("Au revoir!\n");
                exit(0);
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }

    return 0;
}

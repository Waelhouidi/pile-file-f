#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef H_FILE
#define H_FILE

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
    Element *precedent;
};

typedef struct File File;
struct File
{
    Element *premier;
    Element *dernier;
};

File *init();
void enfiler(File *file, int nvNombre);
int defiler(File *file);
void afficherFile(File *file);
bool estDans(File *file, int nombre);
void inverse(File* file);
int positionDansFile(File *file, int valeur);
void supprimerValeur(File *file, int valeur);
int nombreOccurences(File *file, int valeur);

#endif

File *init() {
    File *file = malloc(sizeof(File));
    if (file != NULL) {
        file->premier = NULL;
        file->dernier = NULL;
    }
    return file;
}

void enfiler(File *file, int nvNombre) {
    Element *nouveau = malloc(sizeof(Element));
    if (nouveau != NULL) {
        nouveau->nombre = nvNombre;
        nouveau->suivant = NULL;
        nouveau->precedent = file->dernier;
        if (file->dernier != NULL) {
            file->dernier->suivant = nouveau;
        } else {
            file->premier = nouveau;
        }
        file->dernier = nouveau;
    } else {
        printf("Erreur d'allocation de mémoire.\n");
    }
}

int defiler(File *file) {
    if (file->premier != NULL) {
        Element *a_defiler = file->premier;
        int nombre = a_defiler->nombre;
        file->premier = a_defiler->suivant;
        if (file->premier != NULL) {
            file->premier->precedent = NULL;
        } else {
            file->dernier = NULL;
        }
        free(a_defiler);
        return nombre;
    } else {
        printf("La file est vide.\n");
        return -1;
    }
}

void afficherFile(File *file) {
    Element *actuel = file->premier;
    while (actuel != NULL) {
        printf("%d ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("\n");
}

bool estDans(File *file, int nombre) {
    Element *actuel = file->premier;
    while (actuel != NULL) {
        if (actuel->nombre == nombre) {
            return true;
        }
        actuel = actuel->suivant;
    }
    return false;
}

void inverse(File* file) {
    Element *actuel = file->premier;
    Element *temp = NULL;

    while (actuel != NULL) {
        temp = actuel->precedent;
        actuel->precedent = actuel->suivant;
        actuel->suivant = temp;
        actuel = actuel->precedent;
    }

    temp = file->premier;
    file->premier = file->dernier;
    file->dernier = temp;
}

int positionDansFile(File *file, int valeur) {
    int position = 0;
    Element *actuel = file->premier;
    while (actuel != NULL) {
        if (actuel->nombre == valeur) {
            return position;
        }
        actuel = actuel->suivant;
        position++;
    }
    return -1; // Not found
}

void supprimerValeur(File *file, int valeur) {
    int pos = positionDansFile(file, valeur);
    while (pos != -1) {
        Element *actuel = file->premier;
        for (int i = 0; i < pos; i++) {
            actuel = actuel->suivant;
        }
        if (actuel == file->premier) {
            defiler(file);
        } else {
            actuel->precedent->suivant = actuel->suivant;
            if (actuel->suivant != NULL) {
                actuel->suivant->precedent = actuel->precedent;
            } else {
                file->dernier = actuel->precedent;
            }
            free(actuel);
        }
        pos = positionDansFile(file, valeur);
    }
}

int nombreOccurences(File *file, int valeur) {
    int count = 0;
    Element *actuel = file->premier;
    while (actuel != NULL) {
        if (actuel->nombre == valeur) {
            count++;
        }
        actuel = actuel->suivant;
    }
    return count;
}

int main() {
    File *maFile = init();
    int choix, val;

    do {
        printf("\nMenu:\n");
        printf("1. Enfiler\n");
        printf("2. Defiler\n");
        printf("3. Afficher la file\n");
        printf("4. Inverser la file\n");
        printf("5. Position d'une valeur dans la file\n");
        printf("6. Supprimer toutes les occurrences d'une valeur\n");
        printf("7. Nombre d'occurrences d'une valeur\n");
        printf("8. Quitter\n");

        printf("Votre choix: ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("Valeur à enfiler: ");
                scanf("%d", &val);
                enfiler(maFile, val);
                break;
            case 2:
                printf("Défile %d\n", defiler(maFile));
                break;
            case 3:
                printf("\nÉtat de la file :\n");
                afficherFile(maFile);
                break;
            case 4:
                inverse(maFile);
                printf("La file après inversion :\n");
                afficherFile(maFile);
                break;
            case 5:
                printf("Valeur à chercher dans la file : ");
                scanf("%d", &val);
                printf("Position dans la file: %d\n", positionDansFile(maFile, val));
                break;
            case 6:
                printf("Valeur à supprimer de la file : ");
                scanf("%d", &val);
                supprimerValeur(maFile, val);
                break;
            case 7:
                printf("Valeur à compter dans la file : ");
                scanf("%d", &val);
                printf("Nombre d'occurrences: %d\n", nombreOccurences(maFile, val));
                break;
            case 8:
                printf("Au revoir !\n");
                break;
            default:
                printf("Saisir un choix valide.\n");
        }
    } while(choix != 8);

    Element *current = maFile->premier;
    Element *next;
    while (current != NULL) {
        next = current->suivant;
        free(current);
        current = next;
    }
    free(maFile);

    return 0;
}

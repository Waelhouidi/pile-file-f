#include<stdio.h>
#include<stdlib.h>

// Structure d'un noeud de la pile
struct Node {
    int data;
    struct Node* next;
};

// Fonction pour initialiser une pile vide
struct Node* init() {
    return NULL;
}

// Fonction pour empiler un élément sur la pile
struct Node* empiler(struct Node* top, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return top;
    }
    newNode->data = element;
    newNode->next = top;
    return newNode;
}

// Fonction pour dépiler un élément de la pile
struct Node* depiler(struct Node* top) {
    if (top == NULL) {
        printf("La pile est vide.\n");
        return NULL;
    }
    struct Node* temp = top->next;
    free(top);
    return temp;
}

// Fonction pour empiler un élément à une position donnée
struct Node* empilerPosition(struct Node* top, int element, int position) {
    if (position < 1) {
        printf("Invalid position.\n");
        return top;
    }
    if (position == 1) {
        return empiler(top, element);
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return top;
    }
    newNode->data = element;
    struct Node* temp = top;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position.\n");
        free(newNode);
        return top;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    return top;
}

// Fonction pour dépiler un élément à une position donnée
struct Node* depilerPosition(struct Node* top, int position) {
    if (top == NULL || position < 1) {
        printf("Invalid operation.\n");
        return top;
    }
    if (position == 1) {
        return depiler(top);
    }
    struct Node* temp = top;
    for (int i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position.\n");
        return top;
    }
    struct Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    free(nodeToDelete);
    return top;
}

// Fonction pour trier la liste (tri par sélection)
void trierListe(struct Node* top) {
    struct Node *i, *j;
    int temp;
    for (i = top; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// Fonction pour changer une valeur donnée à une position donnée
void changerValeur(struct Node* top, int position, int newVal) {
    struct Node* temp = top;
    for (int i = 1; i < position && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position.\n");
        return;
    }
    temp->data = newVal;
}

// Fonction pour afficher la pile
void afficherPile(struct Node* top) {
    printf("Pile: ");
    while (top != NULL) {
        printf("%d -> ", top->data);
        top = top->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* pile = init();
    int choix, element, position;

    do {
        printf("\nMenu:\n");
        printf("1. Empiler un element\n");
        printf("2. Depiler un element\n");
        printf("3. Empiler un element a une position donnee\n");
        printf("4. Depiler un element a une position donnee\n");
        printf("5. Trier la pile\n");
        printf("6. Changer une valeur a une position donnee\n");
        printf("7. Afficher la pile\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez l'element a empiler: ");
                scanf("%d", &element);
                pile = empiler(pile, element);
                break;
            case 2:
                pile = depiler(pile);
                break;
            case 3:
                printf("Entrez l'element a empiler: ");
                scanf("%d", &element);
                printf("Entrez la position: ");
                scanf("%d", &position);
                pile = empilerPosition(pile, element, position);
                break;
            case 4:
                printf("Entrez la position: ");
                scanf("%d", &position);
                pile = depilerPosition(pile, position);
                break;
            case 5:
                trierListe(pile);
                printf("Pile triee.\n");
                break;
            case 6:
                printf("Entrez la position: ");
                scanf("%d", &position);
                printf("Entrez la nouvelle valeur: ");
                scanf("%d", &element);
                changerValeur(pile, position, element);
                break;
            case 7:
                afficherPile(pile);
                break;
            case 0:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}


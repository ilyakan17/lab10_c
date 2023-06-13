#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

struct City {
    char name[100];
    int population;
    struct City* next;
};
struct City* hashTable[TABLE_SIZE];
// Функция для вычисления хэша для заданного имени города
unsigned int hashFunction(const char* name) {
    unsigned int hash = 0;
    for (int i = 0; i < strlen(name); i++) {
        hash = hash * 31 + name[i];
    }
    return hash % TABLE_SIZE;
}

void addCity(const char* name, long long population) {
    unsigned int index = hashFunction(name);
    struct City* newCity = (struct City*)malloc(sizeof(struct City));
    strncpy(newCity->name, name, sizeof(newCity->name));
    newCity->population = population;
    newCity->next = NULL;
    if (hashTable[index] == NULL) {
        hashTable[index] = newCity;
    } else {
        struct City* current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCity;
    }
}

void removeCity(const char* name) {
    unsigned int index = hashFunction(name);
    struct City* current = hashTable[index];
    struct City* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } 
            else {
                prev->next = current->next;
            }
            free(current);
            printf("City '%s' removed.\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("City '%s' not found.\n", name);
}

void listCities() {
    printf("Cities:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct City* current = hashTable[i];
        while (current != NULL) {
            printf("%s %d\n", current->name, current->population);
            current = current->next;
        }
    }
}

int main() {
    int choice;
    char name[100];
    int population;
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    do {
        printf("Menu:\n");
        printf("1 - add\n");
        printf("2 - remove\n");
        printf("3 - list\n");
        printf("0 - exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter city name: ");
                scanf("%s", name);
                printf("Enter population: ");
                scanf("%d", &population);
                addCity(name, population);
                break;
            case 2:
                printf("Enter city name: ");
                scanf("%s", name);
                removeCity(name);
                break;
            case 3:
                listCities();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
        printf("\n");
    } while (choice != 0);
    // Освобождаем память, занятую городами в хэш-таблице
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct City* current = hashTable[i];
        while (current != NULL) {
            struct City* temp = current;
            current = current->next;
            free(temp);
        }
    }
    return 0;
}


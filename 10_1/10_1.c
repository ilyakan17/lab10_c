#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* word;
    int frequency;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char* word) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->word = strdup(word);
    newNode->frequency = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, char* word) {
    // Если дерево пустое, создаем новый узел и делаем его корнем
    if (root == NULL) {
        return createNode(word);
    }
    // Если слово уже присутствует в дереве, увеличиваем его частоту
    if (strcmp(word, root->word) == 0) {
        root->frequency++;
    }
    // Если слово меньше текущего корня, рекурсивно вставляем его в левое поддерево
    else if (strcmp(word, root->word) < 0) {
        root->left = insert(root->left, word);
    }
    // Если слово больше текущего корня, рекурсивно вставляем его в правое поддерево
    else {
        root->right = insert(root->right, word);
    }
    return root;
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        // Рекурсивно освобождаем память левого поддерева
        freeTree(root->left);
        // Рекурсивно освобождаем память правого поддерева
        freeTree(root->right);
        // Освобождаем память текущего узла
        free(root->word);
        free(root);
    }
}

void printInOrderAsc(struct Node* root) {
    if (root != NULL) {
        // Рекурсивно выводим левое поддерево
        printInOrderAsc(root->left);
        // Выводим слово и его частоту
        printf("%s - %d\n", root->word, root->frequency);
        // Рекурсивно выводим правое поддерево
        printInOrderAsc(root->right);
    }
}

void printInOrderDesc(struct Node* root) {
    if (root != NULL) {
        printInOrderDesc(root->right);
        printf("%s - %d\n", root->word, root->frequency);
        printInOrderDesc(root->left);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./a.exe <filename> [-o ASC/DESC]\n");
        return 1;
    }
    char* filename = argv[1];
    char* sortOrder = "ASC";  // значение по умолчанию
    if (argc > 2) {
        if (strcmp(argv[2], "-o") == 0) {
            if (argc > 3) {
                sortOrder = argv[3];
            } 
            else {
                printf("Usage: ./a.exe <filename> [-o ASC/DESC]\n");
                return 1;
            }
        } 
        else {
            printf("Usage: ./a.exe <filename> [-o ASC/DESC]\n");
            return 1;
        }
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return 1;
    }
    char word[100];
    struct Node* root = NULL;
    // Считываем слова из файла и вставляем их в бинарное дерево
    while (fscanf(file, "%s", word) == 1) {
        root = insert(root, word);
    }
    fclose(file);
    if (strcmp(sortOrder, "ASC") == 0) {
        printInOrderAsc(root);
    } 
    else if (strcmp(sortOrder, "DESC") == 0) {
        printInOrderDesc(root);
    } 
    else {
        printf("Invalid sort order: %s\n", sortOrder);
    }
    freeTree(root);
    return 0;
}


// Includes 
#include <stdio.h>
#include <stdlib.h> // Required for atoi(), malloc(), free()
#include <string.h> // Required for strcmp()

// Struct Definition
typedef struct product product;

struct product {
    char* code;
    char* country;
    int price;
    product* next;
    product* prev;
};

// Function prototypes
product* constructList(int size, char**argv);
void updateProduct(product* listHead);
void outputList(product* listHead);
void freeList(product* listHead);

int main(int argc, char**argv) {
    // Initialize variables
    int size;
    product* head;

    // Get size and construct the linked list
    size = (argc - 1) / 3;
    head = constructList(size, argv);

    // Update the price of all irish products using updateProduct()
    updateProduct(head);

    // Output each linked list node (product) in a formatted manner
    outputList(head);

    // Free all the memory associated with the linked list;
    freeList(head);
    head = NULL;

    return 0; // End program
}

// Creates a linked list using the args from argv by dynamically allocating each struct and then linking
product* constructList(int size, char**argv) {
    product* head;
    product* curr;
    product* tmp;

    // Create head node
    head = (product*) malloc(sizeof(product));
    if (!head) {
        printf("Memory allocation failed.\n");
        exit -1;
    }

    head->code = argv[1];
    head->country = argv[2];
    head->price = atoi(argv[3]);
    head->next = NULL;
    head->prev = NULL;

    // Allocate, create, and link the rest of the list
    curr = head;
    for (int i = 1; i < size; i++) {
        tmp = (product*) malloc(sizeof(product));
        if (!tmp) {
            printf("Additional allocation failed.\n");
            free(head);
            head = NULL;
            exit -2;
        }

        tmp->code = argv[(i * 3) + 1];
        tmp->country = argv[(i * 3) + 2];
        tmp->price = atoi(argv[(i * 3) + 3]);
        tmp->next = NULL;
        tmp->prev = curr;

        curr->next = tmp;
        curr = tmp;
    }

    // Dicard unnecessary pointers
    curr = NULL;
    tmp = NULL;

    return head;
}

// Goes through the linked list and increase the price attribute by 20% if country == "Ireland"
void updateProduct(product* listHead) {
    while (listHead) {
        if (!(strcmp(listHead->country, "Ireland"))) {
            listHead->price += ((int) (listHead->price * 0.2));
        }

        listHead = listHead->next;
    }
}

// Outputs attributes from a product* linked list each on a new line
void outputList(product* listHead) {
    while (listHead) {
        printf("%s\n%s\n%d\n", listHead->code, listHead->country, listHead->price);

        listHead = listHead->next;
    }
}

// Using 2 pointers, free 1 node before moving onto the next until the end of the list is reached
void freeList(product* listHead) {
    product* tmp;

    while (listHead) {
        tmp = listHead;
        listHead = listHead->next;

        free(tmp);
    }

    tmp = NULL;
}
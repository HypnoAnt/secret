// Includes
#include <stdio.h>
#include <stdlib.h> // Required for atoi(), malloc(), free()

// Struct Definition
typedef struct num num;

struct num {
    int val;
    num* next;
    num* prev;
};

// Function Prototypes
num* constructList(int size, char**argv);
num* deleteEven(num* listHead, int size);
void printList(num* listHead);
int calculateSum(num* listHead);
void freeList(num* listHead);

int main(int argc, char**argv) {
    // Initialize Variables
    int size;
    int sum;
    num* head;

    // Get size and construct the linked list
    size = argc - 1;
    head = constructList(size, argv);

    // Remove all even nums from the linked list using deleteEven()
    head = deleteEven(head, size);
    
    // Output all nums from the new list and output the sum of elements
    printList(head);
    printf("%d\n", calculateSum(head));
    
    // Free all memory associated with the linked list using freeList()
    freeList(head);
    head = NULL;

    return 0; // End program
}

// Creates a linked list using the nums from argv by dynamically allocating each struct and then linking
num* constructList(int size, char**argv) {
    num* head;
    num* curr;
    num* tmp;

    // Create head node
    head = (num*) malloc(sizeof(num));
    if (!head) {
        printf("Memory allocation failed.");
        exit -1;
    }
    
    head->val = atoi(argv[1]);
    head->next = NULL;
    head->prev = NULL;

    // Allocate, create, and link the rest of the list
    curr = head;
    for (int i = 1; i < size; i++) {
        tmp = (num*) malloc(sizeof(num));
        if (!tmp) {
            printf("Additional allocation failed.\n");
            free(head);
            head = NULL;
            exit -2;
        }

        tmp->val = atoi(argv[i + 1]);
        tmp->next = NULL;
        tmp->prev = curr;

        curr->next = tmp;
        curr = tmp;
    }

    // Discard unneccessary pointers
    curr = NULL;
    tmp = NULL;

    return head;
}

// Go through the linked list and if an even is found, the adjacent nodes get their next and prev attributes changed
num* deleteEven(num* listHead, int size) {
    num* toDelete;
 
    // Check everything except list head and tail
    num* tmp = listHead;
    tmp = tmp->next; // Avoid list head

    for (; tmp->next; tmp = tmp->next) {
        if (!((tmp->val) % 2)) {
            toDelete = tmp;

            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            tmp = tmp->prev;

            free(toDelete);
            toDelete = NULL;
        }
    }

    // Check list head
    if (!((listHead->val) % 2)) {
        toDelete = listHead;
        listHead = listHead->next;

        free(toDelete);
        toDelete = NULL;
    }

    // Check list tail
    tmp = listHead;
    while (tmp->next) {
        tmp = tmp->next;
    }

    if (!((tmp->val) % 2)) {
        toDelete = tmp;
        tmp->prev->next = NULL;

        free(toDelete);
        toDelete = NULL;
    }
    
    // Discard unnecessary pointers
    tmp = NULL;

    return listHead;
}

// Prints val stored in each node untl end is reached
void printList(num* listHead) {
    while (listHead) {
        printf("%d\n", listHead->val);
        listHead = listHead->next;
    }
}

// Calculates total by adding a val from a node to the total then going to the next node
int calculateSum(num* listHead) {
    int total = 0;

    while (listHead) {
        total += listHead->val;
        listHead = listHead->next;
    }

    return total;
}

// Using 2 pointers, free 1 node before moving onto the next until the end of the list is reached
void freeList(num* listHead) {
    num* prev;

    while (listHead) {
        prev = listHead;
        listHead = listHead->next;

        free(prev);
    }

    prev = NULL;
}
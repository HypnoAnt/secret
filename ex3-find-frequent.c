// Includes 
#include <stdio.h>
#include <stdlib.h> // Required for atoi(), malloc(), realloc(), free()

// Function Prototypes
int* populateArray(int size, char**argv);
void selectionSort(int* array, int size);
int searchCount(int* array, int size, int n);
int* storeFrequent(int* array, int size);
void outputList(int* array, int size);

int main(int argc, char**argv) {
    // Initialize variables
    int size;
    int* list;
    int* frequentList;
    int frequentSize;

    // Get size, create the array and store all nums from argv
    size = argc - 1;
    list = populateArray(size, argv);

    // Sort array using selectionSort()
    selectionSort(list, size);

    // Returns only the frequent nums as a new array using storeFrequent()
    frequentList = storeFrequent(list, size);
    frequentSize = frequentList[0];

    // Output contents of frequentList()
    outputList(frequentList, frequentSize);

    // Free memory associated with the list
    free(list);
    free(frequentList);
    list = NULL;
    frequentList = NULL;

    return 0; // End program 
}

// Initially allocates 5 spaces to store nums from argv, if limit is exceeded realloc() is used to increase array size, return pointer to array after
int* populateArray(int size, char**argv) {
    int* list;
    int* tmpList = NULL;

    list = (int *) malloc(sizeof(int) * 5);
    if (!list) {
        printf("Initial memory allocation failed.\n");
        exit(-1);
    }

    // Populate array with nums from argv, if more than 5 numbers allocate more memory
    for (int i = 0; i < size; i++) {
        
        // Allocate more memory if necessary
        if (i >= 5) {
            tmpList = realloc(list, sizeof(int) * (i + 1));
            if (!tmpList) {
                printf("Reallocation failed.\n");
                free(list);
                list = NULL;
                exit(-2);
            }

            list = tmpList;
            tmpList = NULL;
        }

        list[i] = atoi(argv[i + 1]);
    }

    return list;
}

// Sort an array from smallest to largest using the selection sort algorithm
void selectionSort(int* array, int size) {
    for (int i = 0; i < size; i++) {
        int p = i;
        int q = i + 1;

        for (; q < size; q++) {
            if (array[q] < array[p]) {
                p = q;
            }
        }

        int tmp = array[i];
        array[i] = array[p];
        array[p] = tmp;
    }
}

// Goes through an array and counts the number of time n appears, if n > 3 return 1 else 0
int searchCount(int* array, int size, int n) {
    int count = 0;
    
    for(int i = 0; i < size; i++) {
        if (array[i] == n) {
            count++;

            if (count > 3) {
                return 1;
            }
        }
    }

    return 0;
}

// Stores a number from the array if it occurs 3 or more times using searchCount()
int* storeFrequent(int* array, int size) {
    int storeSize = 0;
    int* newList;
    int* tmp = NULL;

    // In order to store the array size we allocate 1 
    newList = (int*) malloc(sizeof(int));
    if (!newList) {
        printf("Frequent list allocation failed.\n");
        exit(-3);
    }

    // Now each time we come across a frequent num we realloc() and store into the array, note that we are starting from index 1
    // as index 0 will be used to return the array size
    for (int i = 0; i < size; i++) {
        if (searchCount(array, size, array[i])) {
            storeSize++;

            tmp = realloc(newList, sizeof(int) * (storeSize + 1));
            if(!tmp) {
                printf("Frequent list reallocation failed.\n");
                free(newList);
                newList = NULL;
                exit(-4);
            }
            newList = tmp;
            tmp = NULL;

            newList[storeSize] = array[i];
        }
    }
    
    // Assign index 0 to array size
    newList[0] = storeSize;

    return newList;
}

// Outputs the contents of an int* type array
void outputList(int* array, int size) {
    // +1 as first element is used to store array size
    for (int i = 1; i < (size + 1); i++) {
        printf("%d\n", array[i]);
    }
}
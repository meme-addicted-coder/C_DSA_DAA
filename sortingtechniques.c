#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateNumbers(int* arr, int n) {
    int i;
    srand(time(NULL)); // seed random number generator
    for (i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

// function to save array to text file
void save_to_file(int* arr, int n, char* filename) {
    int i;
    FILE* fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    for (i = 0; i < n; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);
}

void readNumbers(int* arr, int n, char* filename) {
    int i, num;
    FILE* fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d", &num);
        arr[i] = num;
    }
    fclose(fp);
}

void writeTimeComplexity(char *sortType, int n, double time) {
    FILE *fp = fopen("time_complexity.txt", "a");
    if (fp == NULL) {
        printf("Error: could not open file\n");
        return;
    }
    fprintf(fp, "%s Sort with %d numbers took %lf seconds\n", sortType, n, time);
    fclose(fp);
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
//merge sort
void mergeSort(int arr[], int l, int r) 
{
    if (l < r) 
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
//bubble sort
void bubbleSort(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
// selection sort algorithm
void selection_sort(int* arr, int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}
// quicksort algorithm
void quick_sort(int arr[], int left, int right) {
    int i = left;
    int j = right;
    int temp;
    int pivot = arr[(left + right) / 2];
    
    // Partition the array
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    
    // Recursively sort the sub-arrays
    if (left < j) {
        quick_sort(arr, left, j);
    }
    if (i < right) {
        quick_sort(arr, i, right);
    }
}

//insertion sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}




int main()
{
    int n = 150000;
    int arr[n];
    clock_t start_time;
    char filename[] = "numbers.txt";

    // generate random numbers and save to file
    generateNumbers(arr,n);
    save_to_file(arr, n, filename);
    // read numbers from file
    readNumbers(arr,n,filename);

    // sort using buble sort and write execution time to file
    start_time = clock();
    bubbleSort(arr,n);
    double  bubbleSort_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    writeTimeComplexity("Bubble",n,bubbleSort_time);

    // sort using merge sort and write execution time to file
    start_time = clock();
    mergeSort(arr,0,n);
    double mergeSort_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    writeTimeComplexity("Merge",n,mergeSort_time);

    // sort using selection sort and write execution time to file
    start_time = clock();
    selection_sort(arr,n);
    double selection_sort_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    writeTimeComplexity("Selection",n,selection_sort_time);

    // sort using insertion sort and write execution time to file
    start_time = clock();
    insertionSort(arr,n);
    double insertionSort_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    writeTimeComplexity("Insertion",n,insertionSort_time); 

    // sort using quick sort and write execution time to file
    start_time = clock();
    quick_sort(arr,0,n-1);
    double quick_sort_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    writeTimeComplexity("Quick",n,quick_sort_time); 
    return 0;
}

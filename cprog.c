extern int PRINT;
extern int DONE;

#define N 16
int arr[] = {0xF, 0xA, 0xB, 0xE,
             0x9, 0x1, 0x8, 0x4,
             0x6, 0x2, 0x5, 0x7,
             0x3, 0xC, 0x0, 0xD};

void printArray();
void quickSort(int low, int high);
void print(int n);

// Driver program to test above functions
int main() {
    printArray();
    print(0x66666666);
    quickSort(0, N - 1);
    printArray();
    DONE = 0;
}

void print(int n) {
    PRINT = n;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int low, int high) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void printArray() {
    for (int i = 0; i < N; i++) {
        print(arr[i]);
    }
}


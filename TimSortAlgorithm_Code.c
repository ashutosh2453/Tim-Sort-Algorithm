#include <stdio.h>

#define RUN 32

// Function to find minimum of two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Insertion Sort for small runs
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Merge function (like Merge Sort)
void merge(int arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;

    int left[len1], right[len2];

    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];

    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// TimSort function
void timSort(int arr[], int n) {

    // Sort small runs using insertion sort
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)));

    // Merge runs
    for (int size = RUN; size < n; size = 2 * size) {

        for (int left = 0; left < n; left += 2 * size) {

            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {

    int arr[] = {9, 3, 1, 5, 13, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array:\n");
    printArray(arr, n);

    timSort(arr, n);

    printf("Sorted Array:\n");
    printArray(arr, n);

    return 0;
}
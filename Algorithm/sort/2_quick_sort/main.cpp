/*
From
https://www.geeksforgeeks.org/cpp-program-for-quicksort/ 
*/

#include <bits/stdc++.h>
using namespace std;

/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (vector<int>& arr, int head, int tail) 
{ 
    int pivot = arr[tail];    // pivot 
    int i = (head - 1);  // Index of smaller element 
  
    for (int j = head; j <= tail- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(arr[i], arr[j]); 
        } 
    } 
    swap(arr[i + 1], arr[tail]); 
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort(vector<int>& arr, int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
  
/* Function to print an array */
void printArray(vector<int>& arr, int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  
// Driver program to test above functions 
int main() 
{ 
    vector<int> arr {89, 34, 23, 78, 67, 100, 66, 29, 79, 55, 78, 88, 23, 96, 96, 92}; 
    int n = arr.size(); 
    quickSort(arr, 0, n-1); 
    printf("Sorted array: \n"); 
    printArray(arr, n); 
    return 0; 
} 
#include <stdio.h>

void selectionSort(int arr[], size_t length);
void swap(int *a, int *b);

int main(){
    int arr[] = {10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
    int length = sizeof(arr) / sizeof(arr[0]);
    int start, end;


    return 0;
}

void selectionSort(int arr[], size_t length){
    int i, j, min_index, start, end;
    for(i = 0; i < length - 1; i++){
        min_index = i;
        for(j = 0 + 1; j < length; j++){
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
            swap(&arr[min_index], &arr[j]);
        }
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
}
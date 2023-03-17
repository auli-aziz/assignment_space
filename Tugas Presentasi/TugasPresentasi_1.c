#include <stdio.h>
#include <stdlib.h>
#define SIZE 1001

void swap(int *a, int *b);
int checkSorting(int arr[], int n);
void show(int arr[], size_t length);
void input(int arr[], size_t length);

int main(){
    int i, j, diff, length;
    int output = 1;
    int arr[SIZE];
    printf("Enter the length of your array: ");
    scanf("%d", &length);
    input(arr, length);
    show(arr, length);

    output = checkSorting(arr, length);

    printf("Output: ");
    (output == 1)? printf("yes \n"):printf("no \n");
    if(output == 1){
        printf("Your sorted array is \n");
        for(int i = 0; i < length; i++){
            printf("%d ", arr[i]);
        }
    }


    return 0;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int checkSorting(int arr[], int n){
    for (int i=0; i<n-1; i++)
    {
        if ((arr[i] - arr[i+1]) == 1){
            show(arr, n);
        }
        else{
            return 0;
        }
        if (arr[i] > arr[i+1]){
            swap(&arr[i], &arr[i+1]);
        }
    }
    return 1;
}

void show(int arr[], size_t length){
    printf("Your array is \n");
    for(int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }
    puts("");
}

void input(int arr[], size_t length){
    for(int i = 0; i < length; i++){
        printf("Enter index %d: ", i);
        scanf("%d", &arr[i]);
    }
}
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(){
    int i, j, diff;
    int output = 1;
    int arr[] = {1, 0, 3, 2};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Your array is \n");
    for(int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }
    puts("");

    for(i = 0; i < length - 1; i++){
        for(j = 0; j < length - i - 1; j++){
            if(arr[j+1] < arr[j]){
                diff = abs(arr[j+1] - arr[j]);
                if(diff != 1){
                    output = 0;
                }
                swap(&arr[j], &arr[j+1]);
            }
        }
    }

    printf("Output: ");
    (output == 1)? printf("yes"):printf("no");
    if(output == 1){
        puts("");
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
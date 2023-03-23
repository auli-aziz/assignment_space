#include <stdio.h>

int search(int arr[], int N, int x);
void swap(int *a, int *b);
void selectionSort(int arr[], size_t length);
void insertionSort(int arr[], size_t length);


int main(){
	int data,i;
	int array[10]={1,3,6,10,15,16,20,25,37,50};
	
	printf("Array: ");
	for(i=0;i<10;i++){
		printf("%d ",array[i]);
	}

    // printf("Array yang telah terurut menggunakan insertion sort: ");
    // printf("Array yang telah terurut menggunakan selection sort: ");
	
	printf("\nMasukkan data yang dicari:");
	scanf("%d",&data);
	
	int N = sizeof(array) / sizeof(array[0]);
 
    int result = search(array, N, data);
    (result == -1)
        ? printf("Elemen tidak terdapat dalam array")
        : printf("Elemen berada pada indeks ke-%d", result);
    return 0;
}

int search(int arr[], int N, int x){
    int i;
    for (i = 0; i < N; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], size_t length){
    int i, j, min_index;
    for(i = 0; i < length - 1; i++){
        min_index = i;
        for(j = 0; j < length; j++){
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        swap(&arr[min_index], &arr[j]);
    }
}

void insertionSort(int arr[], size_t length){
    int i, j, key;
    for(i = 1; i < length; i++){
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

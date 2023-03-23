#include <stdio.h>
#define SIZE 10

void swap(int *a, int *b);
void show(int arr[], int length);
int linearSearch(int arr[], int N, int x);
int binarySearch(int arr[], int l, int r, int target);
void selectionSort(int arr[], int length);
void insertionSort(int arr[], int length);


int main(){
	int data,i;
	int array[SIZE] = {0};
    int linearResult, binaryResult;

    puts("Masukkan 10 angka!");
    for(i = 0; i < SIZE; i++){
        printf("Index ke-%d: ", i+1);
        scanf("%d", &array[i]);
    }
	
	printf("\nArray: \n");
	show(array, SIZE);

    insertionSort(array, SIZE);
    printf("\nArray yang telah terurut menggunakan insertion sort:\n");
    show(array, SIZE);
    selectionSort(array, SIZE);
    printf("\nArray yang telah terurut menggunakan selection sort:\n");
    show(array, SIZE);
	
	printf("\nMasukkan data yang dicari: ");
	scanf("%d",&data);
 
    linearResult = linearSearch(array, 10, data);
    if(linearResult == -1) printf("Elemen tidak terdapat dalam array dengan linear search\n");
    else printf("Elemen berada pada indeks ke-%d dengan linear search\n", linearResult);
    binaryResult = binarySearch(array, 0, 10, data);
    if(binaryResult == -1) printf("Elemen tidak terdapat dalam array dengan binary search\n");
    else printf("Elemen berada pada indeks ke-%d dengan binary search\n", binaryResult);

    return 0;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void show(int arr[], int length){
    int i;
    for(i=0;i<length;i++){
		printf("%d, ",arr[i]);
	}
}

int linearSearch(int arr[], int N, int x){
    int i;
    for (i = 0; i < N; i++){
        if (arr[i] == x) return i;
    }
    return -1;
}

int binarySearch(int arr[], int l, int r, int target){
    int mid;

    while(r >= l){
        mid = l + (r - l) / 2;
        if(target == arr[mid]) return mid;
        else if (target < arr[mid]) r = mid-1;
        else l = mid+1;
    }
    return -1;
}

void selectionSort(int arr[], int length){
    int i, j, min_index;
    for(i = 0; i < length - 1; i++){
        min_index = i;
        for(j = i+1; j < length; j++){
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        swap(&arr[min_index], &arr[i]); 
    }
}

void insertionSort(int arr[], int length){
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

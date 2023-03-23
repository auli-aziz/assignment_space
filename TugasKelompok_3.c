#include <stdio.h>
#define SIZE 10

void swap(int *a, int *b);
void show(int arr[], int length);
int linearSearch(int arr[], int N, int x);
int binarySearch(int arr[], int l, int r, int target);
void selectionSort(int arr[], int length);
float find_mean(int arr[], int N);
float find_median(int arr[], int N);
int find_mode(int arr[], int N);



int main(){
	int data,i;    
    int array[10] = {1, 3, 6, 8, 6, 4, 3, 1, 3, 3};
    int linearResult, binaryResult;

    // puts("Masukkan 10 angka!");
    // for(i = 0; i < SIZE; i++){
    //     printf("Index ke-%d: ", i+1);
    //     scanf("%d", &array[i]);
    // }
	
	printf("\nArray: \n");
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

    float mean = find_mean(array, SIZE);
    printf("Mean: %.2f\n", mean);

    float median = find_median(array, SIZE);
    printf("Median: %.2f\n", median);

    int mode = find_mode(array, SIZE);
    printf("Modus: %d\n", mode);

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

float find_mean(int arr[], int N) {
    int i, sum = 0;
    for (i = 0; i < N; i++)
        sum += arr[i];
    return (float) sum / N;
}

float find_median(int arr[], int N) {
    if (N % 2 != 0)
        return (float) arr[N / 2];
    else
        return (float) (arr[(N - 1) / 2] + arr[N / 2]) / 2.0;
}

int find_mode(int arr[], int N) {
    int max_count = 0, mode = -1;
    int i, j, count;
    for (i = 0; i < N; i++) {
        count = 0;
        for (j = 0; j < N; j++) {
            if (arr[j] == arr[i])
                count++;
        }
        if (count > max_count) {
            max_count = count;
            mode = arr[i];
        }
    }
    return mode;
}

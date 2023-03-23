#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100    

typedef struct Student{
    char name[SIZE];
    int id;
    double gpa;
} Student;

void dataInput(Student data[], int n);
void dataOutput(Student data[], int n);
void swap(Student *a, Student *b);
// sorts alphabeticly
void selectionSort(Student data[], int n);
// sorts GPA
void bubbleSort(Student data[], int n);
// sorts student ID
void insertionSort(Student data[], int n);

int main(){
    Student data[SIZE];
    int n, menu;

    printf("Choose an sorting option:\n1. By alphabet\n2. By GPA\n3. By ID"
            "\ninput: ");
    scanf("%d", &menu);
    if(menu < 1 || menu > 3){
        printf("Invalid menu! \n");
        exit(1);
    }
    printf("Enter the amount of input data: ");
    scanf("%d", &n);
    printf("\nEnter %d student data: \n", n);
    dataInput(data, n);

    if(menu == 1){
        selectionSort(data, n);
        printf("\nSorted data: \n");
        dataOutput(data, n);
    } else if(menu == 2){
        bubbleSort(data, n);
        printf("\nSorted data: \n");
        dataOutput(data, n);
    } else{
        insertionSort(data, n);
        printf("\nSorted data: \n");
        dataOutput(data, n);
    }

    return 0;
}

void swap(Student *a, Student *b){
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void dataInput(Student data[], int n){
    for(int i = 0; i < n; i++){
        printf("%d-th data: \n", i+1);
        printf("Name: ");
        getchar();
        scanf("%[^\n]", data[i].name);
        printf("ID: ");
        scanf("%d", &data[i].id);
        printf("GPA: ");
        scanf("%lf", &data[i].gpa);
        if(i != n - 1) printf("===============\n");
    }
}

void dataOutput(Student data[], int n){
    for(int i = 0; i < n; i++){
        printf("%d-th data: \n", i+1);
        printf("Name: %s \n", data[i].name);
        printf("ID: %d \n", data[i].id);
        printf("GPA: %.1f \n", data[i].gpa);                    
        if(i != n - 1) printf("===============\n");
    }
}

// sorts alphabeticly
void selectionSort(Student data[], int n){
    int i, j, min_idx;
    for(i = 0; i < n - 1; i++){
        min_idx = i;
        for(j = i + 1; j < n; j++){
            if(strcmp(data[j].name, data[min_idx].name) < 0){
                min_idx = j;
            }
        }
        swap(&data[i], &data[min_idx]);
    }
}

// sorts GPA
void bubbleSort(Student data[], int n){
    int i , j;
    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - i - 1; j++){
            if(data[j+1].gpa > data[j].gpa){
                swap(&data[j], &data[j+1]);
            }
        }
    }
}

// sorts student ID
void insertionSort(Student data[], int n){
    int i, j, key1;
    char key2[SIZE];
    double key3;

    for(i = 1; i < n; i++){
        key1 = data[i].id;
        strcpy(key2, data[i].name);
        key3 = data[i].gpa;
        j = i - 1;

        while(j >= 0 && key1 < data[j].id){
            data[j+1] = data[j];
            j--;
        }

        data[j+1].id = key1;
        strcpy(data[j+1].name, key2);
        data[j+1].id = key1;
    }
}
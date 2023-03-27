#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

/*
1. input: jumlah mahsw, nama tiap mhsw ke dalam daftar_pembeli.txt CHECK
2. sort: memasukkan hasil ke dalam daftar_pembeli_sorted.txt 
3. search: minta input inisial dar daftar_pembeli_sorted.txt
            memberikan output nama
*/

typedef struct database{
	char name[100];
    char initial[50];
    char temp[100];
} Name;

void sortName(Name *Data, int count);
void input(Name Data[], int n, FILE *fptr);
void input_from_file(Name Data[], int n, FILE *fptr);
void sort(Name Data[], int n, int status, FILE *fptr); //status untuk membuat baris baru
int lineCount(FILE *fptr); //menghitung jml baris dalam file .txt
void search(Name Data[], int jumlahData);
void show(Name Data[], int jumlahData);

int main() {
    FILE *fptr;
    Name Data[100]; 
    int menu, count = 0;
    char chr;

    // Read input names from 
    fptr = fopen("daftar_pembeli.txt", "r");
    if(fptr == NULL){
        printf("File tidak ditemukan! \n");
        printf("PROGRAM MENCARI INISIAL \n\n");
        printf("Masukkan Jumlah Nama: ");
        scanf("%d", &count);
        input(Data, count, fptr);
        sortName(Data, count);
        sort(Data, count, 0, fptr);
    }else{
        printf("File tersedia! \n");
        count = lineCount(fptr);
        sortName(Data, count);
        sort(Data, count, 1, fptr);
        input_from_file(Data, count, fptr);
    }
    // Sort names and create initials
    printf("Sorting Selesai! \n");

    printf("\nMENU \n\n");
    printf("1. Input Data\n2. Cari Inisial\n3. Keluar\nInput: ");
    scanf("%d", &menu);



    // Print sorted names and searching result

    if(menu == 1){
        printf("Masukkan jumlah Nama: ");
        scanf("%d", &count);
        input(Data, count, fptr);
        sortName(Data, count);
        sort(Data, count, 0, fptr);
    }else if(menu == 2){
        printf("\nMENCARI INISIAL: \n");
        search(Data, count);
    } else{
        exit(0);
    }

    fclose(fptr);

    return 0;
}

void sortName(Name *Data, int count) {
    // Sort names in ascending order
    printf("Melakukan sorting... \n");
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(Data[i].name, Data[j].name) > 0) {
                // Swap names
                char temp[100];
                strcpy(temp, Data[i].name);
                strcpy(Data[i].name, Data[j].name);
                strcpy(Data[j].name, temp);
            }
        }
    }

    // Build a function/algorithm to create initials
    
}

void input(Name Data[], int n, FILE *fptr){
    int i, j, jumlah = 0;

    for(i = 0; i < n; i++){
        printf("Name-%d: ", i+1);
        getchar();
        scanf("%100[^\n]s", Data[i].name);
    }

    fptr = fopen("daftar_pembeli.txt", "w");
    
    for(j = 0; j < n; j++){
        fprintf(fptr, "%s \n", Data[j].name);
    }       
    fclose(fptr);
}

void sort(Name Data[], int n, int status, FILE *fptr){
    fptr = fopen("daftar_pembeli_sorted.txt", "w");
    for(int i = 0; i < n; i++){
        fprintf(fptr, "%s", Data[i].name);
        // if(status == 0) fprintf(fptr, "\n");
    }
    fclose(fptr);
}

int lineCount(FILE *fptr){
    char c;
    int count = 0; //inisialisasi terlebih dahulu
    fptr = fopen("daftar_pembeli.txt", "r");
    for (c = getc(fptr); c != EOF; c = getc(fptr)){
        if(c == '\n') count++;
    }
    fclose(fptr);
    printf("Terdapat %d baris dalam file \n", count+1);
    return count;
}

void input_from_file(Name Data[], int n, FILE *fptr){
    fptr = fopen("daftar_pembeli.txt", "r");
    for(int i = 0; i < n; i++){
        fgets(Data[i].name, 100, fptr);
    }
    fclose(fptr);
    show(Data, n);
}

void search(Name Data[], int jumlahData){
    printf("Inisial nama (kalung) yang ingin dicari: ");
    scanf("%s", Data[0].initial);
    int count[50] = {0}, init = 0, j = 0, line = 0, store = 0, kapital[50] = {0};
    
    for(line= 0; line < jumlahData; line++){
        count[line] = 0;
        init = 0;
        for(j = 0; j < strlen(Data[line].name); j++){
            if(Data[line].name[j] >= 65 && Data[line].name[j] <= 90){
                kapital[line]++; //menghitung jumlah huruf kapital total
            }
            if((Data[line].name[j] >= 65 && Data[line].name[j] <= 90) && (Data[line].name[j] == Data[0].initial[init])){
                count[line]++;  //menghitung jumlah huruf kapital yang sesuai
                init++;
            }
        }
    }
    
    printf("panjang inisial: %d\n", strlen(Data[0].initial));
    for(int i = 0; i < jumlahData; i++){
        // printf("Jumlah huruf besar yang sesuai pada baris ke-%d: %d\n", i+1, count[i]);
        // printf("Jumlah kapital pada baris ke-%d: %d\n", i+1, kapital[i]);
        if(strlen(Data[0].initial) == count[i] && count[i] == kapital[i]){
            strcpy(Data[store].temp, Data[i].name);
            store++;
        }
    }
    
    if(store > 0){
        for(int k = 0; k < store; k++){
            printf("Kalung %s adalah milik %s",Data[0].initial, Data[k].temp);
        }
    } else printf("Inisial tidak ditemukan \n");
}

void show(Name Data[], int jumlahData){
    printf("Data yang sudah terinput dari file ke dalam struct: ");
    for(int i = 0; i < jumlahData; i++){
        printf("Data ke-%d: %s ", i+1, Data[i].name);
    }
}
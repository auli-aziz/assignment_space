#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define LIMIT 50

/*
PEMROGRAMAN LANJUT 01
TUGAS PROYEK KELOMPOK TENGAH SEMESTER
JUDUL: SISTEM AKUN BANK
LINK VIDEO: https://youtu.be/X6YJ5lrSbCY
*********************************************
ANGGOTA: 
* Muhammad Abrisam Cahyo Juhartono || 2206026050
* Aulia Anugrah Aziz || 2206059364
* Naufal Rusyda Santosa || 2206813353
FITUR:
* Sistem bisa mengurutkan berdasarkan jumlah saldo, nama atau nomor rekening (ada pilihan admin dan nasabah di awal program) (S0RTING)
* Bisa menyimpan informasi Biodata pembuat rekening (termasuk password) dan melakukan pendaftaran rekening jika belum punya (STRUCT)
* Bisa cek informasi saldo rekening (FILE HANDLING)
* Bisa menghitung bunga tunggal jika sudah menjadi nasabah selama beberapa tahun (RECURSION)
PEMBAGIAN TUGAS:
* Ari: login, loginSukses
* Aziz: bikinAkun, admin, nasabah, debugging seluruh program
* Naufal: cek bunga, sortName, sortSaldo
*********************************************
TEKNIK KOMPUTER
UNIVERSITAS INDONESIA
*/

typedef struct Akun {
    char namaDepan[LIMIT];
    char namaBelakang[LIMIT];
    char username[LIMIT];
    char namaIbu[LIMIT];
    char alamat[SIZE];
    int tanggal, bulan, tahun;
    double saldo;
} Akun;

typedef struct Pin {
    char pinAdmin[SIZE];
    char pin[SIZE];
} Pin;

void admin();
void nasabah();
void bikinAkun();
void akunBerhasilDibuat();
void login();
void loginSukses(double saldo, char name[]);
void bungaBank(double saldo);
double menghitungBunga(double initial, double waktu, double bunga);
void sortName(int size, int jumlahNasabah);
void sortSaldo(int size, int jumlahNasabah);
int lineCount();
void swap(Akun *first, Akun *second);

int main(){
    int opsiUser;
    system("CLS");
    printf("SELAMAT DATANG DI BANK JAGO\n==================================\n");
    sleep(1);
    printf("MASUK SEBAGAI\n1. NASABAH\n2. ADMIN\n3. KELUAR\nPILIHAN: ");
    scanf("%d", &opsiUser);
    if(opsiUser == 1){
        nasabah();
    } else if(opsiUser == 2){
        admin();
    } else if(opsiUser == 3){
        sleep(1); printf("==================================\nTERIMA KASIH TELAH MENGGUNAKAN BANK JAGO"); sleep(3);
        exit(0);
    } else{
        printf("\nMENU TIDAK TERSEDIA \n"); sleep(5);
        main();
    }
}

void nasabah(){
    int menu;
    system("CLS");
    printf("ANDA MASUK SEBAGAI NASABAH\n==================================\n");
    printf("SILAKAN PILIH JENIS MENU YANG TERSEDIA\n");
    printf("1. MEMBUAT AKUN BARU\n2. SUDAH MEMPUNYAI AKUN\n3. KEMBALI KE MENU UTAMA\nPILIHAN: ");
    scanf("%d", &menu);
    switch(menu){
        case 1:
        sleep(1);
        bikinAkun();
        break;
        case 2:
        sleep(1);
        login();
        break;
        case 3:
        main();
        break;
        default:
        printf("PILIHAN TIDAK DITEMUKAN\n");
        sleep(1);
        nasabah();
    }
}

void admin(){
    FILE *fptr;
    Pin datum;
    int menu, convertPin, i = 0;
    int count = lineCount(), jumlahNasabah = count / 7;
    char ch;

    system("CLS");
    printf("ANDA MASUK SEBAGAI ADMIN\n==================================\n");
    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("\nJUMLAH TOTAL NASABAH: 0\n");
        sleep(5); main();
    } 
    fclose(fptr);

    printf("SILAKAN MASUKKAN PIN ADMIN: ");
    while (1) {
        ch = getch(); 
        if (ch == 13) { 
            break; 
        } else if (ch == 8) { 
            if (i > 0) {
                i--;
                datum.pinAdmin[i] = '\0'; 
                printf("\b \b"); 
            }
        } else {
            datum.pinAdmin[i++] = ch; 
            printf("*"); 
        }
    }
    datum.pinAdmin[i] = '\0'; 

    fptr = fopen("pin.txt", "w");
    fprintf(fptr, "%s", datum.pinAdmin);
    fclose(fptr);

    fptr = fopen("pin.txt", "r");
    fscanf(fptr, "%[^\n]%*c", datum.pinAdmin);
    fclose(fptr);

    convertPin = atoi(datum.pinAdmin);

    if(convertPin == 987654321){
        printf("\nJUMLAH TOTAL NASABAH: %d \n", jumlahNasabah);
        printf("1. SORT\n2. CLEAR DATABASE\n3. KEMBALI KE MENU UTAMA\nPILIHAN: ");
        scanf("%d", &menu);
        if(menu == 1){
            printf("\nURUT BERDASARKAN:\n1. NAMA\n2. SALDO (DARI YANG TERBESAR)\nPILIHAN: ");
            scanf("%d", &menu);
            if(menu == 1){
                sortName(count, jumlahNasabah);
            } else if(menu == 2){
                sortSaldo(count, jumlahNasabah);
            } else{
                printf("\nMENU TIDAK TERSEDIA");
                sleep(3); admin();
            }
        } else if(menu == 2){
            fptr = fopen("database.txt", "w");
            if(fptr == NULL){
                printf("GAGAL MEMBUKA FILE database.txt\n");
                return; 
            }
            fclose(fptr);
            printf("DATABASE BERHASIL DIHAPUS...\n");
            sleep(5); admin();
        } else if(menu == 3){
            main();
        }else{
            printf("MENU TIDAK TERSEDIA \n");
            sleep(5); admin();
        }
    } else{
        printf("\nPIN SALAH! \n");
    }
}

void bikinAkun(){
    FILE *fptr;
    Akun data;
    Pin datum;
    int i;
    char ch;

    system("CLS");
    printf("MENU PEMBUATAN AKUN BARU BANK JAGO\n==================================\n");
    sleep(1);
    printf("NAMA DEPAN: ");
    getchar();
    fgets(data.namaDepan, sizeof(data.namaDepan), stdin);
    data.namaDepan[strcspn(data.namaDepan, "\n")] = '\0'; //removes new line
    printf("NAMA BELAKANG: ");
    fgets(data.namaBelakang, sizeof(data.namaBelakang), stdin);
    printf("NAMA IBU KANDUNG: ");
    fgets(data.namaIbu, sizeof(data.namaIbu), stdin);
    printf("ALAMAT DOMISILI (MAX 100 KARAKTER): ");
    fgets(data.alamat, sizeof(data.alamat), stdin);
    printf("MASUKKAN TANGGAL LAHIR (HH/BB/TTTT): ");
    scanf("%d", &data.tanggal);
    getchar();
    scanf("%d", &data.bulan);
    getchar();
    scanf("%d", &data.tahun);
    printf("SALDO AWAL: Rp");
    scanf("%lf", &data.saldo);
    printf("USERNAME (DAPAT BERUPA HURUF SAJA): ");
    getchar();
    fgets(data.username, sizeof(data.username), stdin);
    
    printf("MASUKKAN PIN (HANYA DAPAT BERUPA ANGKA): ");
    while (1) {
        ch = getch(); // input karakter
        if (ch == 13) { // cek bila enter ditekan
            break; 
        } else if (ch == 8) { // cek bila Backspace ditekan
            if (i > 0) {
                i--;
                datum.pin[i] = '\0'; // remove karakter terakhir dari memori
                printf("\b \b"); // hapus karakter terakhir pada output
            }
        } else {
            datum.pin[i++] = ch; // simpan karakter pada struct
            printf("*"); // display '*' pada output
        }
    }
    

    datum.pin[i] = '\0';

    fptr = fopen("database.txt", "a");
    fprintf(fptr, "%s", data.username);
    fprintf(fptr, "%s \n", datum.pin);
    fprintf(fptr, "%s %s", data.namaDepan, data.namaBelakang);
    fprintf(fptr, "%s", data.namaIbu);
    fprintf(fptr, "%s", data.alamat);
    fprintf(fptr, "%d/%d/%d \n", data.tanggal, data.bulan, data.tahun);
    fprintf(fptr, "%.1f \n", data.saldo);
    fclose(fptr);

    akunBerhasilDibuat();
}

void akunBerhasilDibuat(){
    int i;
    char ch;
    system("CLS");
    printf(
        "HARAP TUNGGU....\n\nDATA SEDANG DIPROSES....\n\n");
    sleep(5);

    printf("AKUN BERHASIL DIBIKIN! \n");
    printf("TEKAN ENTER UNTUK LOGIN ");

    getch();
    login();
}

int lineCount(){
    FILE *fptr;
    char c;
    int count = 1; 

    fptr = fopen("database.txt", "r");
    for (c = getc(fptr); c != EOF; c = getc(fptr)){
        if(c == '\n') count++;
    }
    fclose(fptr);

    return count;
}

void login(){
    FILE *fptr;
    Akun data[SIZE];
    Pin datum[SIZE];
    int count = lineCount(), found = 0, foundIndex = 0, i, convertPin, tempPass;
    double saldo;
    char buffer[SIZE], tempUser[SIZE], tempName[SIZE], ch;

    system("CLS");
    printf("LAMAN LOGIN\n==================\n");

    fptr = fopen("database.txt", "r");

    if(fptr == NULL){
        printf("ERROR! DATABASE TIDAK TERSEDIA. HUBUNGI PETUGAS BANK\n");
        exit(0);
    }

    printf("MASUKKAN USERNAME: ");
    scanf("%s", tempUser);

    //search username (LINEAR SEARCH)
    for(i = 0; i < count; i += 7){
        fscanf(fptr, "%[^\n]%*c", data[i].username);
        if(strcmp(data[i].username, tempUser) == 0){
            found = 1;
            foundIndex = i;
        }
        for(int j = 0; j < 6; j++){
            fgets(buffer, SIZE, fptr); // skip baris
        }
    }
    fclose(fptr);

    // input saldo yang benar dari .txt
    fptr = fopen("database.txt", "r");
    for(i = 0; i < foundIndex + 6; i++){
        fgets(buffer, SIZE, fptr); // skip baris
    }
    fscanf(fptr, "%lf", &saldo);
    fclose(fptr);

    // input nama panjang yang benar dari .txt
    fptr = fopen("database.txt", "r");
    for(i = 0; i < foundIndex + 2; i++){
        fgets(buffer, SIZE, fptr); // skip baris
    }
    fscanf(fptr, "%[^\n]%*c", tempName);
    fclose(fptr);

    // input pin yang benar dari .txt
    fptr = fopen("database.txt", "r");
    for(i = 0; i < foundIndex + 1; i++){
        fgets(buffer, SIZE, fptr); // skip baris
    }
    fscanf(fptr, "%[^\n]%*c", datum[i].pin);
    fclose(fptr);
    convertPin = atoi(datum[i].pin);

    if(found == 0){
        printf("USERNAME TIDAK DITEMUKAN \n");
        exit(0);
    } else{
        printf("MASUKKAN PIN ANDA: ");
        i = 0; // reset i for inputting pin
        while (1) {
            ch = getch(); 
            if (ch == 13) { 
                break; 
            } else if (ch == 8) { 
                if (i > 0) {
                    i--;
                    datum[0].pinAdmin[i] = '\0'; 
                    printf("\b \b"); 
                }
            } else {
                datum[0].pinAdmin[i++] = ch; 
                printf("*"); 
            }
        }
        datum[0].pinAdmin[i] = '\0'; 

        fptr = fopen("pin.txt", "w");
        fprintf(fptr, "%s", datum[0].pinAdmin);
        fclose(fptr);

        fptr = fopen("pin.txt", "r");
        fscanf(fptr, "%[^\n]%*c", datum[0].pinAdmin);
        fclose(fptr);

        tempPass = atoi(datum[0].pinAdmin);
    }

    if(tempPass == convertPin){
        sleep(1);
        printf("\n\nLOGIN SUKSES!\n");
        sleep(2);
        loginSukses(saldo, tempName);
    } else{
        printf("\nPIN YANG ANDA MASUKKAN SALAH\n");
        exit(0);
    }
}

void loginSukses(double saldo, char name[]){
    Akun data;
    Pin datum;
    int opsiUser;

    system("CLS");
    sleep(1);
    printf("SELAMAT DATANG %s\n=========================\n", name);
    printf("PILIH MENU YANG TERSEDIA\n");
    printf("1. CEK SALDO\n2. CEK BUNGA\n3. KEMBALI KE MENU UTAMA\nPILIHAN: ");
    scanf("%d", &opsiUser);
    switch(opsiUser){
        case 1:
        printf("\nSaldo Anda: Rp%.2f \n", saldo);
        sleep(3);
        printf("TEKAN ENTER UNTUK KEMBALI KE MENU UTAMA ");

        getch();
        main();
        break;
        case 2:
        bungaBank(saldo);
        break;
        case 3:
        sleep(1); main();
        break;
        default:
        printf("PILIHAN TIDAK DITEMUKAN\n"); sleep(2);
        loginSukses(saldo, name);
    }
}

void bungaBank(double saldo){
	double durasi, temp, bunga = 0.0375;
    printf("\nBUNGA SIMPANAN BANK JAGO BERADA PADA LEVEL 3.75%% PER TAHUN \n");
	printf("BERAPA LAMA WAKTU ANDA MENABUNG (DALAM TAHUN)? ");
	scanf("%lf", &durasi);

    temp = menghitungBunga(saldo, durasi, bunga);
    printf("SALDO ANDA ADALAH Rp%.1f SETELAH MENABUNG SELAMA %.1f TAHUN", temp, durasi);

    sleep(3); printf("\n\nTEKAN ENTER UNTUK KEMBALI KE MENU UTAMA ");

    getch();
    main();
}

// fungsi rekursi
double menghitungBunga(double initial, double waktu, double bunga){
    if(waktu > 0){
        return menghitungBunga(initial, waktu - 1, bunga) + (bunga * initial);
    } else{
        return initial;
    }
}

// sort secara alfabet (BINARY SORTING)
void sortName(int size, int jumlahNasabah){
    FILE *fptr;
    int i, j, n;
    char buffer[SIZE];
    Akun data[SIZE];
    Akun temp;

    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("ERROR DATABASE TIDAK DITEMUKAN \n");
        exit(1);
    }
    //input nama dari .txt
    for(int j = 0; j < 2; j++){
        fgets(buffer, SIZE, fptr); // skip baris
    }
    for(i = 0; i < jumlahNasabah; i++){
        fscanf(fptr, "%[^\n]%*c", data[i].namaDepan);
        strtok(data[i].namaDepan, "\n");
        for(int j = 0; j < 6; j++){
            fgets(buffer, SIZE, fptr); // skip baris
        }
    }
    fclose(fptr);

    // swapping
    for (i = 0; i < jumlahNasabah - 1; i++) {
        for (j = 0; j < jumlahNasabah - i - 1; j++) {
            if (strcmp(data[j].namaDepan, data[j + 1].namaDepan) > 0) {
                swap(&data[j], &data[j + 1]);
            }
        }
    }
    
    printf("\nNAMA YANG SUDAH DIURUTKAN:\n");
    for(i = 0; i < jumlahNasabah; i++){
        printf("%s\n",data[i].namaDepan);
	}
	
	fptr = fopen("sorted_name.txt","w");
    if(fptr == NULL){
        printf("MEMBUAT FILE BARU...\n");
	}
	for(i = 0; i < jumlahNasabah; i++){
		fprintf(fptr,"%s\n",data[i].namaDepan);
	}
    fclose(fptr);

    sleep(3); printf("\nTEKAN ENTER UNTUK KEMBALI KE MENU UTAMA ");

    getch();
    main();
}

// sort berdasarkan saldo (SELECTION SORTING)
void sortSaldo(int size, int jumlahNasabah){
    FILE *fptr;
    char buffer[SIZE];
    int i, j, max_idx;
    Akun data[SIZE];
    Akun temp;

    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("ERROR DATABASE TIDAK DITEMUKAN \n");
        exit(1);
    }

    //input nama dari .txt
    for(int j = 0; j < 2; j++){
        fgets(buffer, SIZE, fptr); // skip baris
    }
    for(i = 0; i < jumlahNasabah; i++){
        fscanf(fptr, "%[^\n]%*c", data[i].namaDepan);
        strtok(data[i].namaDepan, "\n");
        for(int j = 0; j < 6; j++){
            fgets(buffer, SIZE, fptr); // skip baris
        }
    }
    fclose(fptr);
    //input saldo dari .txt
    fptr = fopen("database.txt", "r");
    for(int j = 0; j < 6; j++){
        fgets(buffer, SIZE, fptr); // skip baris
    }
    for(i = 0; i < jumlahNasabah; i++){
        fscanf(fptr, "%lf", &data[i].saldo);
        for(int j = 0; j < 7; j++){
            fgets(buffer, SIZE, fptr); // skip baris
        }
    }
    fclose(fptr);

    for (i = 0; i < jumlahNasabah - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < jumlahNasabah; j++) {
            if (data[j].saldo > data[max_idx].saldo) {
                max_idx = j;
            }
        }
        swap(&data[max_idx], &data[i]);
    }
    
    //display sorted saldo
    printf("\nSALDO YANG SUDAH DIURUTKAN:\n");
    for(i = 0; i < jumlahNasabah; i++){
        printf("%s: %.2f\n",data[i].namaDepan, data[i].saldo);
	}
	
	//make new file with sorted saldo
	fptr=fopen("sorted_saldo.txt","w");
    if(fptr == NULL){
        printf("MEMBUAT FILE BARU...\n");
	}
	for(i=0; i < jumlahNasabah; i++){
		fprintf(fptr,"%f\n",data[i].saldo);
	}
    fclose(fptr);

    sleep(3);
    printf("\n\nTEKAN ENTER UNTUK KEMBALI KE MENU UTAMA ");

    getch();
    main();
}

//swapping dengan call by reference
void swap(Akun *first, Akun *second){
    Akun temp = *first;
    *first = *second;
    *second = temp;
}
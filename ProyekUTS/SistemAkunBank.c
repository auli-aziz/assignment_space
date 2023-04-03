#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
PEMROGRAMAN LANJUT 01
TUGAS PROYEK KELOMPOK TENGAH SEMESTER
JUDUL: SISTEM AKUN BANK
LINK VIDEO: 
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
* Aziz: bikinAkun, admin, nasabah
* Naufal: cek bunga, sortName, sortSaldo
*********************************************
TEKNIK KOMPUTER
UNIVERSITAS INDONESIA
*/

typedef struct Akun {
    char namaDepan[25];
    char namaBelakang[25];
    char username[50];
    char namaIbu[50];
    char alamat[100];
    int tanggal, bulan, tahun;
    double saldo;
} Akun;

typedef struct Pin {
    int passAdmin;
    char password[100];
} Pin;

typedef struct Transfer {
    char tujuan[100];
    char asal[100];
    long int uang;
} Transfer;

void admin();
void nasabah();
void bikinAkun();
void akunBerhasilDibuat();
void login();
void loginSukses();
int lineCount();
void bungaBank();
double menghitungBunga(double initial, double waktu, double bunga);
void sortName(int size, int jumlahNasabah);
void sortSaldo(int size, int jumlahNasabah);

int main(){
    int opsiUser;
    system("CLS");
    printf("SELAMAT DATANG DI BANK JAGO\n");
    sleep(1);
    printf("MASUK SEBAGAI\n1. NASABAH\n2. ADMIN\nPILIHAN: ");
    scanf("%d", &opsiUser);
    if(opsiUser == 1){
        nasabah();
    } else if(opsiUser == 2){
        admin();
    } else{
        printf("MENU TIDAK TERSEDIA \n");
    }
        
    return 0;
}

void nasabah(){
    int menu;
    system("CLS");
    printf("ANDA MASUK SEBAGAI NASABAH\n==================================\n");
    printf("SILAKAN PILIH JENIS MENU YANG TERSEDIA\n");
    printf("1. MEMBUAT AKUN BARU\n2. SUDAH MEMPUNYAI AKUN\nPILIHAN: ");
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
        default:
        sleep(1);
        printf("PILIHAN TIDAK DITEMUKAN\n");
    }
}

void admin(){
    FILE *fptr;
    Pin datum;
    int menu;
    int count = lineCount();
    int jumlahNasabah = count / 7;
    
    system("CLS");
    printf("ANDA MASUK SEBAGAI ADMIN\n==================================\n");
    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("FILE DATABASE TIDAK DITEMUKAN\n");
    } 
    fclose(fptr);
    printf("SILAKAN MASUKKAN PIN ADMIN: ");
    scanf("%d", &datum.passAdmin);
    if(datum.passAdmin == 000){
        printf("JUMLAH TOTAL NASABAH: %d \n", jumlahNasabah);
        printf("1. SORT\n2. CLEAR DATABASE\nPILIHAN: ");
        scanf("%d", &menu);
        if(menu == 1){
            printf("\nURUT BERDASARKAN:\n1. NAMA\n2. SALDO (DARI YANG TERBESAR)\nPILIHAN: ");
            scanf("%d", &menu);
            if(menu == 1){
                sortName(count, jumlahNasabah);
            } else if(menu == 2){
                sortSaldo(count, jumlahNasabah);
            }
        } else if(menu == 2){
            fopen("database.txt", "w");
            fclose(fptr);
            printf("DATABASE BERHASIL DIHAPUS...\n");
            sleep(2);
        } else{
            printf("MENU TIDAK TERSEDIA \n");
        }
    } else{
        printf("PASSWORD SALAH! \n");
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
    printf("ALAMAT DOMISILI: ");
    fgets(data.alamat, sizeof(data.alamat), stdin);
    printf("MASUKKAN TANGGAL LAHIR (HH/MM/YYYY): ");
    scanf("%d", &data.tanggal);
    getchar();
    scanf("%d", &data.bulan);
    getchar();
    scanf("%d", &data.tahun);
    printf("SALDO AWAL: Rp");
    scanf("%lf", &data.saldo);
    printf("USERNAME (DAPAT BERUPA ANGKA DAN HURUF SAJA): ");
    getchar();
    fgets(data.username, sizeof(data.username), stdin);
    printf("MASUKKAN PASSWORD (DAPAT BERUPA ANGKA DAN HURUF SAJA): ");
    for (i = 0; i < 50; i++) {
        ch = getch();
        if (ch == 13) {
            break;
        } else if(ch != 8){
            datum.password[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
    }

    fptr = fopen("database.txt", "a");
    fprintf(fptr, "%s", data.username);
    fprintf(fptr, "%s \n", datum.password);
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
    Akun data[100];
    Pin datum[100];
    int count = lineCount(), found = 0, foundIndex = 0, i, convertPass, tempPass;
    double saldo;
    char buffer[100], tempUser[100];

    system("CLS");
    printf("LAMAN LOGIN\n==================\n\n");

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
            fgets(buffer, 100, fptr); // skip baris
        }
    }
    fclose(fptr);

    // input saldo yang benar dari .txt
    fptr = fopen("database.txt", "r");
    for(i = 0; i < foundIndex + 6; i++){
        fgets(buffer, 100, fptr); // skip baris
    }
    fscanf(fptr, "%lf", &saldo);
    fclose(fptr);

    // input password yang benar dari .txt
    fptr = fopen("database.txt", "r");
    for(i = 0; i < foundIndex + 1; i++){
        fgets(buffer, 100, fptr); // skip baris
    }
    fscanf(fptr, "%[^\n]%*c", datum[i].password);
    fclose(fptr);
    convertPass = atoi(datum[i].password);

    if(found == 0){
        printf("USERNAME TIDAK DITEMUKAN \n");
        exit(0);
    } else{
        printf("MASUKKAN PIN ANDA: ");
        scanf("%d", &tempPass);
    }

    if(tempPass == convertPass){
        loginSukses(saldo);
    } else{
        printf("PIN YANG ANDA MASUKKAN SALAH\n");
        exit(0);
    }
}

void loginSukses(double saldo){
    Akun data;
    Pin datum;
    int opsiUser;

    sleep(1);
    printf("\nLOGIN SUKSES!\n");
    sleep(2);
    system("CLS");
    sleep(1);
    printf("SELAMAT DATANG %s %s\n", data.namaDepan, data.namaBelakang); //perlu ada nama
    printf("PILIH MENU YANG TERSEDIA\n");
    printf("1. CEK SALDO\n2. CEK BUNGA\nPILIHAN: ");
    scanf("%d", &opsiUser);
    switch(opsiUser){
        case 1:
        printf("\nSaldo Anda: Rp%.2f \n", saldo);
        break;
        case 2:
        bungaBank(saldo);
        break;
        default:
        printf("PILIHAN TIDAK DITEMUKAN\n");
    }
}

void bungaBank(double saldo){
	double durasi, temp, bunga = 0.0375;
    printf("BUNGA SIMPANAN BANK JAGO BERADA PADA LEVEL 3.75%% PER TAHUN \n");
	printf("BERAPA LAMA WAKTU ANDA MENABUNG (DALAM TAHUN)? ");
	scanf("%lf", &durasi);

    temp = menghitungBunga(saldo, durasi, bunga);
    printf("SALDO ANDA ADALAH %.1f SETELAH MENABUNG SELAMA %.1f TAHUN", temp, durasi);
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
    char buffer[100];
    Akun data[100];
    Akun temp;

    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("ERROR DATABASE TIDAK DITEMUKAN \n");
        exit(1);
    }
    //input nama dari .txt
    for(int j = 0; j < 2; j++){
        fgets(buffer, 100, fptr); // skip baris
    }
    for(i = 0; i < jumlahNasabah; i++){
        fscanf(fptr, "%[^\n]%*c", data[i].namaDepan);
        strtok(data[i].namaDepan, "\n");
        for(int j = 0; j < 6; j++){
            fgets(buffer, 100, fptr); // skip baris
        }
    }
    fclose(fptr);

    // swapping
    for (i = 0; i < jumlahNasabah - 1; i++) {
        for (j = 0; j < jumlahNasabah - i - 1; j++) {
            if (strcmp(data[j].namaDepan, data[j + 1].namaDepan) > 0) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
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
}

// sort berdasarkan saldo (SELECTION SORTING)
void sortSaldo(int size, int jumlahNasabah){
    FILE *fptr;
    char buffer[100];
    int i, j, max_idx;
    Akun data[100];
    Akun temp;

    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("ERROR DATABASE TIDAK DITEMUKAN \n");
        exit(1);
    }

    //input nama dari .txt
    for(int j = 0; j < 2; j++){
        fgets(buffer, 100, fptr); // skip baris
    }
    for(i = 0; i < jumlahNasabah; i++){
        fscanf(fptr, "%[^\n]%*c", data[i].namaDepan);
        strtok(data[i].namaDepan, "\n");
        for(int j = 0; j < 6; j++){
            fgets(buffer, 100, fptr); // skip baris
        }
    }
    fclose(fptr);
    //input saldo dari .txt
    fptr = fopen("database.txt", "r");
    for(int j = 0; j < 6; j++){
        fgets(buffer, 100, fptr); // skip baris
    }
    for(i = 0; i < jumlahNasabah; i++){
        fscanf(fptr, "%lf", &data[i].saldo);
        for(int j = 0; j < 7; j++){
            fgets(buffer, 100, fptr); // skip baris
        }
    }
    fclose(fptr);

    //swapping
    for (i = 0; i < jumlahNasabah - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < jumlahNasabah; j++) {
            if (data[j].saldo > data[max_idx].saldo) {
                max_idx = j;
            }
        }
        temp = data[max_idx];
        data[max_idx] = data[i];
        data[i] = temp;
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
}
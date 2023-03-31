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
* Bisa transfer rekening ke tujuan (SEARCHING)
* Bisa cek bunga jika sudah menjadi nasabah selama beberapa lama (RECURSION)

PEMBAGIAN TUGAS:
* Ari: login
* Aziz: bikin akun, admin, nasabah
* Naufal: cek bunga, sorting
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
    int tanggal, bulan, tahun, saldo;
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
void login();
int lineCount();
void transfer();

int main(){
    int opsiUser;

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
    printf("SILAKAN PILIH JENIS MENU YANG TERSEDIA\n");
    printf("1. MEMBUAT AKUN BARU\n2. SUDAH MEMPUNYAI AKUN\nPILIHAN: ");
    scanf("%d", &menu);
    switch(menu){
        case 1:
        bikinAkun();
        break;
        case 2:

        break;
        default:
        printf("PILIHAN TIDAK DITEMUKAN\n");
    }
}

void admin(){
    FILE *fptr;
    Pin data;
    int menu;
    
    system("CLS");
    printf("ANDA MASUK SEBAGAI ADMIN\n");
    printf("==================================\n");
    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("FILE DATABASE TIDAK DITEMUKAN\n");
    } else{
        int count = lineCount();
    }
    printf("SILAKAN MASUKKAN PIN ADMIN: ");
    scanf("%d", &data.passAdmin);
    if(data.passAdmin == 000){
        printf("1. SORT\n2. SEARCH REKENING\nPILIHAN: ");
        scanf("%d", &menu);
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
    printf("MENU PEMBUATAN AKUN BARU BANK JAGO\n");
    printf("==================================\n");
    sleep(1);
    printf("NAMA DEPAN: ");
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
    fprintf(fptr, "%s %s", data.namaDepan, data.namaBelakang);
    fprintf(fptr, "%s", data.namaIbu);
    fprintf(fptr, "%s", data.alamat);
    fprintf(fptr, "%d/%d/%d \n", data.tanggal, data.bulan, data.tahun);
    fprintf(fptr, "%s", data.username);
    fprintf(fptr, "%s \n", datum.password);
    fprintf(fptr, "========================\n");
    fclose(fptr);
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
    printf("JUMLAH TOTAL NASABAH: %d \n", count / 7);
    return count;
}
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
    char password[100];
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

void bikinAkun();

int main(){
    int menu, opsiUser = 0;
    Pin data;

    printf("SELAMAT DATANG DI BANK JAGO\n");
    // sleep(1);
    printf("MASUK SEBAGAI\n1. NASABAH\n2. ADMIN\nPILIHAN: ");
    scanf("%d", &opsiUser);
    if(opsiUser == 1){
        system("CLS");
        printf("SILAKAN PILIH JENIS MENU YANG TERSEDIA\n");
        printf("1. MEMBUAT AKUN BARU\n2. SUDAH MEMPUNYAI AKUN\nPILIHAN: ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
            system("CLS");
            bikinAkun();
            break;
            case 2:
            break;
            default:
            printf("PILIHAN TIDAK DITEMUKAN\n");
        }
    } else if(opsiUser == 2){
        system("CLS");
        printf("ANDA MASUK SEBAGAI ADMIN\nSILAKAN MASUKKAN PIN ADMIN: ");
        scanf("%d", &data.passAdmin);
        if(data.passAdmin == 000){
            printf("1. SORT\n2. SEARCH REKENING\nPILIHAN: ");
            scanf("%d", &menu);
        } else{
            printf("PASSWORD SALAH! \n");
            exit(0);
        }
    } else{
        printf("MENU TIDAK TERSEDIA \n");
    }
        
    return 0;
}

void bikinAkun(){
    FILE *fptr;
    Akun data;
    printf("MENU PEMBUATAN AKUN BARU BANK JAGO\n");
    // sleep(1);
    printf("NAMA DEPAN: ");
    getchar();
    fgets(data.namaDepan, sizeof(data.namaDepan), stdin);
    data.namaDepan[strcspn(data.namaDepan, "\n")] = '\0'; //removes newline
    printf("NAMA BELAKANG: ");
    fgets(data.namaBelakang, sizeof(data.namaBelakang), stdin);
    printf("NAMA IBU KANDUNG: ");
    fgets(data.namaIbu, sizeof(data.namaIbu), stdin);
    printf("ALAMAT DOMISILI: ");
    fgets(data.alamat, sizeof(data.alamat), stdin);
    printf("USERNAME (DAPAT BERUPA ANGKA DAN HURUF SAJA): ");
    fgets(data.username, sizeof(data.username), stdin);


    fptr = fopen("database.txt", "a");
    fprintf(fptr, "==================== \n");
    fprintf(fptr, "NAMA LENGKAP: %s %s", data.namaDepan, data.namaBelakang);
    fprintf(fptr, "NAMA IBU KANDUNG: %s", data.namaIbu);
    fprintf(fptr, "ALAMAT: %s", data.alamat);
    fclose(fptr);
}
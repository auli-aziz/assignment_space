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
* Bisa menghitung bunga tunggal jika sudah menjadi nasabah selama beberapa tahun (RECURSION)

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
void login();
void loginSukses();
void lineCount();
void bungaBank();
double menghitungBunga(double initial, double waktu, double bunga);
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
    Pin datum;
    int menu;
    
    system("CLS");
    printf("ANDA MASUK SEBAGAI ADMIN\n");
    printf("==================================\n");
    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("FILE DATABASE TIDAK DITEMUKAN\n");
    } else{
        lineCount();
    }
    printf("SILAKAN MASUKKAN PIN ADMIN: ");
    scanf("%d", &datum.passAdmin);
    if(datum.passAdmin == 000){
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
    printf("MASUKKAN SALDO AWAL: ");
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
    fprintf(fptr, "%f", data.saldo);
    fprintf(fptr, "%s \n", datum.password);
    fprintf(fptr, "%s %s", data.namaDepan, data.namaBelakang);
    fprintf(fptr, "%s", data.namaIbu);
    fprintf(fptr, "%s", data.alamat);
    fprintf(fptr, "%d/%d/%d \n", data.tanggal, data.bulan, data.tahun);
    fprintf(fptr, "========================\n");
    fclose(fptr);
}

void lineCount(){
    FILE *fptr;
    char c;
    int count = 1; 

    fptr = fopen("database.txt", "r");
    for (c = getc(fptr); c != EOF; c = getc(fptr)){
        if(c == '\n') count++;
    }
    fclose(fptr);
    printf("JUMLAH TOTAL NASABAH: %d \n", count / 7);
}

void bungaBank(double saldo){
	double durasi, temp, bunga = 0.0375;
    printf("Bunga simpanan Bank Jago berada pada level 3.75%% per tahun \n");
	printf("Berapa lama waktu anda menabung (dalam tahun)? ");
	scanf("%lf", &durasi);

    temp = menghitungBunga(saldo, durasi, bunga);
    printf("Saldo anda adalah %.1f setelah menabung selama %.1f tahun", temp, durasi);
}

// fungsi rekursi
double menghitungBunga(double initial, double waktu, double bunga){
    if(waktu > 0){
        return menghitungBunga(initial, waktu - 1, bunga) + (bunga * initial);
    } else{
        return initial;
    }
}

void login(){
    FILE *fptr;
    Akun data;
    Pin datum;
    int isFound = 0;
    char temp[100];

    printf("MASUKKAN USERNAME: ");
    scanf("%s", &temp);
    fptr = fopen("database.txt", "r");
    while(fscanf(fptr, "%s %s %s %s %s %d/%d/%d %s %s", data.namaDepan, data.namaBelakang, data.namaIbu, data.alamat, data.username, &data.tanggal, &data.bulan, &data.tahun, datum.password, datum.passAdmin) != EOF){
        if(strcmp(data.username, temp) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound){
        char pass[100];
        int i = 0;
        printf("MASUKKAN PASSWORD: ");
        while(1) {
            char c = getch();
            if(c == '\r') {
                break;
            } else if(c == '\b') {
                if(i > 0) {
                    i--;
                    pass[i] = '\0';
                    printf("\b \b");
                }
            } else {
                pass[i++] = c;
                printf("*");
            }
        }
        if(strcmp(datum.password, pass) == 0){
            loginPage();
        } else{
            printf("\nPASSWORD SALAH!\n");
        }
    } else{
        printf("\nUSERNAME TIDAK DITEMUKAN!\n");
    }
    fclose(fptr);
}

void loginSukses(){
    printf("\nLOGIN SUKSES!\n");
            int opsiUser;
            sleep(1);
            printf("SELAMAT DATANG %s %s\n", data.namaDepan, data.namaBelakang);
            printf("PILIH MENU YANG TERSEDIA\n");
            printf("1. CEK SALDO\n2. TRANSFER\n3. CEK BUNGA\nPILIHAN: ");
            scanf("%d", &opsiUser);
            switch(opsiUser){
                case 1:
                cekSaldo(temp);
                break;
                case 2:
                transfer(temp);
                break;
                case 3:
                bungaBank();
                break;
                default:
                printf("PILIHAN TIDAK DITEMUKAN\n");
            }
}
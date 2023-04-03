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
* Ari: login, transfer
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
void akunBerhasilDibuat();
int lineCount();
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
        login();
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
    printf("ANDA MASUK SEBAGAI ADMIN\n==================================\n");
    fptr = fopen("database.txt", "r");
    if(fptr == NULL){
        printf("FILE DATABASE TIDAK DITEMUKAN\n");
    } else{
        int count = lineCount();
        printf("JUMLAH TOTAL NASABAH: %d \n", count / 7);
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
    Akun data[100];
    Pin datum[100];
    int count = lineCount(), found = 0, foundIndex = 0, i, convertPass, tempPass;
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
        loginSukses();
    } else{
        printf("PIN YANG ANDA MASUKKAN SALAH\n");
        exit(0);
    }
}

void loginSukses(){
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
    printf("1. CEK SALDO\n2. TRANSFER\n3. CEK BUNGA\nPILIHAN: ");
    scanf("%d", &opsiUser);
    switch(opsiUser){
        case 1:
        //printf("%d", data.saldo);
        break;
        case 2:
        //transfer();
        break;
        case 3:
        // bungaBank();
        break;
        default:
        printf("PILIHAN TIDAK DITEMUKAN\n");
    }
}
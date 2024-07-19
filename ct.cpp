#include <iostream> 
#include <conio.h> 
#include <cstdlib> 
using namespace std; 
struct data 
{ 
 int angka; 
 data *next; 
}*baru, *kepala=NULL, *ekor=NULL, *tampil, *hapus, *tambah, *a, 
*b; 
 
//fungsi untuk menginputkan data 
void gerbong() 
{ 
 int nilai; 
 cout<<"\nMasukkan nilai : "; 
 cin>>nilai; 
 baru = new data; 
 baru->angka = nilai; 
 baru->next = NULL; 
} 
/////////////////////////////////// 
 
//fungsi untuk menambah depan 
void tambah_depan() 
{ 
 gerbong(); 
 if(kepala==NULL) 
 { 
  kepala = baru; 
  ekor = baru; 
 } 
 else 
 { 
  baru->next = kepala; 
kepala = baru; 
} 
} 
///////////////////////////////// 
//fungsi untuk menambah belakang 
void tambah_belakang() 
{ 
gerbong(); 
if(kepala==NULL) 
{ 
kepala = baru; 
ekor = baru; 
} 
else 
{ 
ekor->next = baru; 
ekor = baru; 
} 
} 
///////////////////////////////// 
//fungsi untuk menampilkan data 
void muncul() 
{ 
if(kepala==NULL) 
{ 
cout<<"Data kosong"; 
} 
else 
{ 
tampil = kepala; 
while(tampil!=NULL) 
{ 
cout<<tampil->angka<<" "; 
tampil = tampil->next; 
} 
} 
} 
//////////////////////////////// 
//fungsi untuk menambah tengah 
void tambah_tengah() 
{ 
int masuk; 
gerbong(); 
cout<<"\nData yang ada : "; 
muncul();
cout<<"\n\ningin dimasukkan setelah data : "; 
cin>>masuk; 
if(kepala==NULL) 
{ 
kepala = baru; 
ekor = baru; 
} 
else 
{ 
tambah = kepala; 
while(tambah->angka!=masuk) 
{ 
tambah = tambah->next; 
} 
baru->next = tambah->next; 
tambah->next = baru; 
if(baru->next==NULL) 
{ 
ekor=baru; 
} 
} 
} 
/////////////////////////////////////////// 
//fungsi untuk menghapus depan 
void hapus_depan() 
{ 
hapus = kepala; 
if(kepala==NULL) 
{ 
cout<<"\nData kosong"; 
} 
else 
{ 
kepala = kepala->next; 
delete hapus; 
} 
} 
////////////////////////////////////// 
//fungsi untuk menghapus belakang 
void hapus_belakang() 
{ 
hapus = kepala; 
if(kepala==NULL) 
{ 
cout<<"\nData kosong"; 
}
else if (kepala==ekor) 
{ 
delete hapus; 
kepala = ekor = NULL; 
} 
else 
{ 
while(hapus->next!=ekor) 
{ 
hapus = hapus->next; 
} 
ekor = hapus; 
ekor->next = NULL; 
hapus = hapus->next; 
delete hapus; 
} 
} 
//////////////////////////////////////// 
//fungsi untuk menghapus tengah 
void hapus_tengah() 
{ 
int hps; 
cout<<"\nData yang ada : "; 
muncul(); 
cout<<"\ningin menghapus nilai berapa : "; 
cin>>hps; 
hapus = kepala; 
if(kepala==NULL) 
{ 
cout<<"\nData kosong"; 
} 
else if (hapus->angka==hps) 
{ 
hapus_depan(); 
} 
else 
{ 
while(hapus->angka!=hps) 
{ 
a = hapus; 
hapus = hapus->next; 
b = hapus->next; 
} 
a->next = b; 
delete hapus; 
} 
} 
///////////////////////////////////////// 
int main() 
{ 
int pilih; 
do 
{ 
cout<<"\n1. tambah depan"; 
cout<<"\n2. tambah belakang"; 
cout<<"\n3. tambah tengah"; 
cout<<"\n4. hapus depan"; 
cout<<"\n5. hapus belakang"; 
cout<<"\n6. hapus tengah"; 
cout<<"\n7. tampil"; 
cout<<"\n8. keluar..."; 
cout<<"\nMasukkan pilihan : "; 
cin>>pilih; 
if (pilih==1) 
{ 
tambah_depan(); 
} 
else if (pilih==2) 
{ 
tambah_belakang(); 
} 
else if (pilih==3) 
{ 
tambah_tengah(); 
getch(); 
} 
else if (pilih==4) 
{ 
hapus_depan(); 
} 
else if (pilih==5) 
{ 
hapus_belakang(); 
} 
else if (pilih==6) 
{ 
hapus_tengah(); 
} 
else if(pilih==7) 
{ 
muncul(); 
getch(); 
} 
else
{ 
exit(1); 
} 
system("cls"); 
} 
while(1); 
}
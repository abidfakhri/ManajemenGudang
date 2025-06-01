// @abidfakhri
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

struct DataBarang{
    string KodeBarang, NamaBarang;
    int stok = 0;
    double harga = 00.00;
};
struct Node{
    DataBarang barang;
    Node *next;
};

int NamaTerpanjang(Node *firstData){
    Node *temp = firstData;
    int size = temp->barang.NamaBarang.length();
    do{
        if(size < temp->next->barang.NamaBarang.length()){
            size = temp->next->barang.NamaBarang.length();
        }
        temp = temp->next;
    }while(temp->next != firstData);
    if (size < 4){
        return 5;
    }
    
    return size;
}

void cari(Node *firstData, DataBarang data){

    Node *temp = firstData;
    do{
        if(temp->barang.KodeBarang == data.KodeBarang){
            cout << "\nKode  : " << temp->barang.KodeBarang << endl;
            cout << "Nama  : " << temp->barang.NamaBarang << endl;
            cout << "Stok  : " << temp->barang.stok << endl;
            cout << "Harga : Rp" << temp->barang.harga << endl;
            return;
        }
        temp = temp->next;
    } while (temp->next != firstData);

    cout << "Barang tidak ditemukan..." << endl;
    
}

void tambahStok(Node *&firstData, DataBarang data){
    Node *temp = firstData;
    while(temp->barang.KodeBarang != data.KodeBarang && temp->next != firstData) temp = temp->next;
    if(temp->barang.KodeBarang == data.KodeBarang){
        char opsi; 
        do{
            cout << "Ingin menambah stok " << temp->barang.NamaBarang << "?[Y/n] : ";
            cin >> opsi; 
            if(toupper(opsi) == 'Y'){
                temp->barang.stok += data.stok;
                cout << "Stok " << temp->barang.NamaBarang << " ditambahkan..." << endl;
            }
        } while(toupper(opsi) != 'Y' && toupper(opsi) != 'N');
        return;
    }
    cout << "Kode barang tidak ditemukan..." << endl;
}

void updateHarga(Node *&firstData, DataBarang data){
    Node *temp = firstData;
    while(temp->barang.KodeBarang != data.KodeBarang && temp->next != firstData) temp = temp->next;
    if(temp->barang.KodeBarang == data.KodeBarang){
        char opsi; 
        do{
            cout << "Ingin update harga " << temp->barang.NamaBarang << "?[Y/n] : ";
            cin >> opsi; 
            if(toupper(opsi) == 'Y'){
                temp->barang.harga = data.harga;
                cout << "Harga " << temp->barang.NamaBarang << " diperbarui..." << endl;
            }
        } while(toupper(opsi) != 'Y' && toupper(opsi) != 'N');
        return;
    }
    cout << "Kode barang tidak ditemukan..." << endl;
}

void BarangMasuk(Node *&firstData, DataBarang data){

    Node *dataBaru = new Node;
    dataBaru->barang.KodeBarang = data.KodeBarang;
    dataBaru->barang.NamaBarang = data.NamaBarang;
    dataBaru->barang.stok = data.stok;
    dataBaru->barang.harga = data.harga;
    
    if (firstData == nullptr){
        firstData = dataBaru;
        dataBaru->next = firstData;
    }else{

        Node *temp = firstData;
        while(temp->barang.KodeBarang != data.KodeBarang && temp->next != firstData){
            temp = temp->next;
        }
        if (temp->barang.KodeBarang == data.KodeBarang){
            cout << "ID barang sudah ada di daftar..." << endl;
            return;
        }
        
        Node *tail = firstData;
        while (tail->next != firstData){
            tail = tail->next;
        }
        tail->next = dataBaru;
        dataBaru->next = firstData;
    }
}

void BarangKeluar(Node *&firstData, DataBarang data){
    
    Node *cari = firstData;
    while(cari->barang.KodeBarang != data.KodeBarang && cari->next != firstData){
        cari = cari->next;
    }

    if(cari->barang.KodeBarang == data.KodeBarang){
            if(cari->barang.stok > 0 && data.stok <= cari->barang.stok){
                cout << "Stok " << cari->barang.NamaBarang << " berkurang..." << endl;
                cari->barang.stok -= data.stok;
                return;
            }
            cout << "Stok tidak mencukupi..." << endl;
            return;
    }
    cout << "Kode barang tidak ditemukan..." << endl;
}

void display(Node *firstData){
    if(firstData == nullptr) {
        cout << "Daftar Barang Kosong..." << endl;
        return;
    }
    Node *temp = firstData;
    int panjang = NamaTerpanjang(firstData);

    cout << "\nDAFTAR BARANG\n";
    for (int i = 0; i < panjang+40; i++) cout << "=";
    cout << left << setw(11) << "\n|| Kode"
         << setw(panjang+3) << "| Nama" 
         << setw(10) << "| Stok" 
         << setw(15) << "| Harga " << "||" << endl;
    for (int i = 0; i < panjang+40; i++) cout << "=";
    cout << endl;
    cout << fixed << setprecision(2);
    do{
        cout << "|| " << left << setw(7) << temp->barang.KodeBarang 
        << "| " << setw(panjang+1) << temp->barang.NamaBarang 
        << "| " <<  setw(8) << temp->barang.stok
        << "| Rp" << setw(11) << temp->barang.harga << "||\n||";
        for (int i = 0; i < panjang+36; i++) cout << "-";
        cout << "||" << endl;
        temp = temp->next;
    }while(temp != firstData);
    for (int i = 0; i < panjang+40; i++) cout << "="; cout << endl;
}

void hapus(Node *&firstData, DataBarang data){

    Node *temp = firstData;
    Node *prev = nullptr;

    do{
        if(temp->barang.KodeBarang == data.KodeBarang){
            char opsi;
            do{
                cout << "Apakah anda ingin menghapus " << temp->barang.NamaBarang << " (" << temp->barang.KodeBarang << ") ? [Y/n] : "; cin >> opsi;
                if(toupper(opsi) != 'Y' && toupper(opsi) != 'N') cout << "Opsi tidak valid.." << endl;
            }while(toupper(opsi) != 'Y' && toupper(opsi) != 'N');

            if(toupper(opsi) == 'Y'){
                if (temp == firstData && temp->next == firstData){
                    delete firstData;
                    firstData = nullptr;
                } else if (temp == firstData){
                    Node *tail = firstData;
                    while (tail->next != firstData){
                        tail = tail->next;
                    }
                    firstData = firstData->next;
                    tail->next = firstData;
                    delete temp;
                }else{
                    prev->next = temp->next;
                    delete temp;
                }
                return;
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    } while (temp != firstData);
    cout << "Barang dengan kode " << data.KodeBarang << " tidak ditemukan..\n";
}

int main(){

    Node *firstData = nullptr;
    DataBarang barang;

    while (true){
        cout << "\n================================================\n";
        cout << "|          Program Manajemen Gudang            |\n";
        cout << "================================================" << endl;
        cout << "[1] Tampilkan Daftar Barang\t[5] Update Harga\n[2] Barang Masuk\t\t[6] Hapus Barang\n[3] Barang Keluar\t\t[7] Cari\n[4] Tambah Stok\t\t\t[0] Keluar\n>>> ";
        int opsi; cin >> opsi; cin.ignore();

        if (opsi >= 3 && opsi <= 7 && firstData == nullptr){
            cout << "Daftar Barang Kosong..." << endl;
            continue;
        }
        
        switch (opsi){
        case 0:
            cout << "Keluar program..." << endl;
            return 0;
        case 1:
            display(firstData);
            break;
        case 2:
            cout << "|============ Input Barang Masuk ==============|\n";
            cout << "Kode  : "; cin >> barang.KodeBarang; cin.ignore();
            cout << "Nama  : "; getline(cin, barang.NamaBarang);
            cout << "Stok  : "; cin >> barang.stok;
            cout << "Harga : Rp"; cin >> barang.harga;
            BarangMasuk(firstData, barang);
            break;
        case 3:
            cout << "|============ Input Barang Keluar =============|\n";
            cout << "Kode           : "; cin >> barang.KodeBarang;
            cout << "Jumlah Keluar  : "; cin >> barang.stok;
            BarangKeluar(firstData, barang);
            break;
        case 4:
            cout << "|================= Tambah Stok ================|\n";
            cout << "Kode : "; cin >> barang.KodeBarang;
            cout << "Stok : "; cin >> barang.stok;
            tambahStok(firstData, barang);
            break;
        case 5:
            cout << "|================ Update Harga ================|\n";
            cout << "Kode  : "; cin >> barang.KodeBarang;
            cout << "Harga : Rp"; cin >> barang.harga;
            updateHarga(firstData, barang);
            break;
        case 6:
            cout << "|=================== Hapus ====================|\n";
            cout << "Kode : "; cin >> barang.KodeBarang;
            hapus(firstData, barang);
            break;
        case 7:
            cout << "|==================== Cari ====================|\n";
            cout << "Kode : "; cin >> barang.KodeBarang;
            cari(firstData, barang);
            break;
        default:
            cout << "Opsi tidak ada di menu..." << endl;
            break;
        }
    }
    
    return 0;
}
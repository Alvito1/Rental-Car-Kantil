#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

class CarRental {
private:
    struct Car {
        int id;
        std::string nama;
        std::string plat;
        bool tersedia;
    };

    std::vector<Car> daftarMobil;
    std::string filename;

    void updateFile() {
        std::ofstream file(filename, std::ios::trunc);
        if (file.is_open()) {
            for (const auto &mobil : daftarMobil) {
                file << mobil.id << " " << mobil.nama << " " << mobil.plat << " " << mobil.tersedia << std::endl;
            }
            file.close();
            std::cout << "Data mobil telah diperbarui dalam file.\n";
        } else {
            std::cout << "Tidak bisa membuka file untuk memperbarui data.\n";
        }
    }

public:
    CarRental(const std::string& file = "mobil.txt") : filename(file) {
        muatDataDariFile();
    }

    void muatDataDariFile() {
        std::ifstream file(filename);
        if (!file.is_open())
            return;

        std::string line;
        daftarMobil.clear(); // Clear existing data before loading
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Car mobil;
            iss >> mobil.id >> mobil.nama >> mobil.plat >> mobil.tersedia;
            daftarMobil.push_back(mobil);
        }
        file.close();
    }

    void simpanDataKeFile() {
        std::ofstream file(filename);
        if (!file.is_open())
            return;

        for (const auto &mobil : daftarMobil) {
            file << mobil.id << " " << mobil.nama << " " << mobil.plat << " " << mobil.tersedia << "\n";
        }
        std::cout << "Data mobil telah diperbarui ke dalam file ketika keluar dari program.\n";
        file.close();
    }

    void tampilkanMobil() {
        std::cout << "\n====================\n";
        std::cout << "----Daftar Mobil----\n";
        std::cout << "====================\n\n";
        for (const auto &mobil : daftarMobil) {
            std::cout << "ID: " << mobil.id 
                      << ", Nama: " << mobil.nama 
                      << ", Plat: " << mobil.plat 
                      << ", Tersedia: " << (mobil.tersedia ? "Ya" : "Tidak") << "\n";
        }
    }

    void tambahMobil() {
        Car mobil;

        // Validate ID input
        std::cout << "Masukkan Id Mobil: ";
        while (!(std::cin >> mobil.id)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input tidak valid. Masukkan ID Mobil dalam bentuk angka: ";
        }

        // Check if ID already exists
        while (std::any_of(daftarMobil.begin(), daftarMobil.end(), 
               [&mobil](const Car& m) { return m.id == mobil.id; })) {
            std::cout << "\n\nID Mobil sudah ada. Masukkan ID Mobil yang berbeda: ";
            std::cin >> mobil.id;
        }

        std::cout << "Masukkan Nama Mobil: ";
        std::cin >> mobil.nama;
        std::cout << "Masukkan Plat Mobil: ";
        std::cin >> mobil.plat;
        mobil.tersedia = true;
        
        daftarMobil.push_back(mobil);
        updateFile();
    }

    void ubahMobil() {
        int id;
        std::cout << "Masukkan ID Mobil yang ingin diubah: ";
        std::cin >> id;
        
        auto it = std::find_if(daftarMobil.begin(), daftarMobil.end(), 
                                [id](const Car& mobil) { return mobil.id == id; });
        
        if (it != daftarMobil.end()) {
            std::cout << "Masukkan Nama Baru: ";
            std::cin >> it->nama;
            std::cout << "Masukkan Plat Baru: ";
            std::cin >> it->plat;
            updateFile();
        } else {
            std::cout << "Mobil tidak ditemukan.\n";
        }
    }

    void hapusMobil() {
        int id;
        std::cout << "Masukkan ID Mobil yang ingin dihapus: ";
        std::cin >> id;
        
        auto it = std::find_if(daftarMobil.begin(), daftarMobil.end(), 
                                [id](const Car& mobil) { return mobil.id == id; });
        
        if (it != daftarMobil.end()) {
            daftarMobil.erase(it);
            updateFile();
            std::cout << "Mobil dengan ID " << id << " berhasil dihapus.\n\n\n";
        } else {
            std::cout << "Mobil tidak ditemukan.\n";
        }
    }

    void sewaMobil() {
        int id;
        std::cout << "Masukkan ID Mobil yang ingin disewa: ";
        std::cin >> id;
        
        auto it = std::find_if(daftarMobil.begin(), daftarMobil.end(), 
                                [id](Car& mobil) { return mobil.id == id && mobil.tersedia; });
        
        if (it != daftarMobil.end()) {
            it->tersedia = false;
            std::cout << "\n Mobil " << id << " berhasil disewa.\n\n";
            updateFile();
        } else {
            std::cout << "Mobil tidak tersedia atau tidak ditemukan.\n";
        }
    }

    void kembalikanMobil() {
        int id;
        std::cout << "Masukkan ID Mobil yang ingin dikembalikan: ";
        std::cin >> id;
        
        auto it = std::find_if(daftarMobil.begin(), daftarMobil.end(), 
                                [id](Car& mobil) { return mobil.id == id && !mobil.tersedia; });
        
        if (it != daftarMobil.end()) {
            it->tersedia = true;
            std::cout << "Mobil berhasil dikembalikan.\n";
            updateFile();
        } else {
            std::cout << "Mobil tidak ditemukan atau sudah tersedia.\n";
        }
    }

    void jalankanMenu() {
        int pilihan;
        do {
            std::cout << "\n--- Aplikasi Rental Mobil KANTIL 💀 ---\n";
            std::cout << "        _______\n";
            std::cout << "       //  ||\\ \\\n";
            std::cout << " _____//___||_\\ \\___\n";
            std::cout << " )  _          _    \\\n";
            std::cout << " |_/ \\________/ \\___|\n";
            std::cout << "___\\_/________\\_/______\n";
            std::cout << "\n\n";
            std::cout << "1. Tampilkan Mobil\n";
            std::cout << "2. Tambah Mobil\n";
            std::cout << "3. Ubah Mobil\n";
            std::cout << "4. Hapus Mobil\n";
            std::cout << "5. Sewa Mobil\n";
            std::cout << "6. Kembalikan Mobil\n";
            std::cout << "0. Keluar\n";
            std::cout << "Pilih menu: ";

            // Validate input
            if (!(std::cin >> pilihan)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Input tidak valid. Masukkan angka.\n";
                continue;
            }

            switch (pilihan) {
                case 1: tampilkanMobil(); break;
                case 2: tambahMobil(); break;
                case 3: ubahMobil(); break;
                case 4: hapusMobil(); break;
                case 5: sewaMobil(); break;
                case 6: kembalikanMobil(); break;
                case 0: simpanDataKeFile(); break;
                default: std::cout << "Pilihan tidak valid.\n"; break;
            }
        } while (pilihan != 0);
    }
};

int main() {
    CarRental rental;
    rental.jalankanMenu();
    return 0;
}
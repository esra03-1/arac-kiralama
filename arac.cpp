#include <iostream>
#include<string.h>
#include<stdlib.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct Kisi
{
    char ad[20], soyad[20], tel[20], adres[20], id[20], parola[20], parolaTekrar[20];
};

struct Arac
{
    char marka[20], model[20], plaka[20];
    int yil;
    float gunlukUcret;
    bool kiralandi;
};

void yeniMusteriKayit()
{
    ofstream dosya("musteriBilgileri.dat", ios::binary | ios::app);

    if (!dosya.is_open())
    {
        cout << "Musteri bilgileri dosyasi acilamadi." << endl;
        return;
    }

    Kisi k1;
    cin.ignore();
    cout << "Yeni Musteri Kaydi\n";
    cout << "Ad: ";
    cin.getline(k1.ad, sizeof(k1.ad));
    cout << "Soyad: ";
    cin.getline(k1.soyad, sizeof(k1.soyad));
    cout << "Telefon: ";
    cin.getline(k1.tel, sizeof(k1.tel));
    cout << "Adres: ";
    cin.getline(k1.adres, sizeof(k1.adres));
    cout << "ID: ";
    cin.getline(k1.id, sizeof(k1.id));
    cout << "Parola (en az 8 karakter): ";
    char ch;
    int i = 0;
    ch = getch();
    while (ch != 13)
    {
        k1.parola[i] = ch;
        cout << "*";
        ch = getch();
        i++;
    }
    k1.parola[i] = '\0';

    cout << "\nParola Tekrar: ";
    i = 0;
    ch = getch();
    while (ch != 13)
    {
        k1.parolaTekrar[i] = ch;
        cout << "*";
        ch = getch();
        i++;
    }
    k1.parolaTekrar[i] = '\0';

    if (strcmp(k1.parola, k1.parolaTekrar) == 0 && strlen(k1.parola) >= 8)
    {
        dosya.write(reinterpret_cast<char *>(&k1), sizeof(Kisi));
        dosya.close();
        cout << "\nKayit basarili.\n";
    }
    else
    {
        cout << "\nParola kayit hatasi! Lutfen tekrar deneyin.\n";
    }
}

void aracEkle()
{    
    cin.ignore();
    ofstream dosya("aracBilgileri.dat", ios::binary | ios::app);

    if (!dosya.is_open())
    {
        cout << "Arac bilgileri dosyasi acilamadi." << endl;
        return;
    }

    Arac arac;


    cout << "Arac Ekle\n";
    cout << "Marka: ";
    cin.getline(arac.marka, sizeof(arac.marka));
    cout << "Model: ";
    cin.getline(arac.model, sizeof(arac.model));
    cout << "Plaka: ";
    cin.getline(arac.plaka, sizeof(arac.plaka));
    cout << "Yil: ";
    cin >> arac.yil;
    cout << "Gunluk Ucret: ";
    cin >> arac.gunlukUcret;

    arac.kiralandi = false;

    dosya.write(reinterpret_cast<char *>(&arac), sizeof(Arac));
    dosya.close();

    cout << "\nArac basariyla eklendi.\n";
}

void aracListele()
{
    ifstream dosya("aracBilgileri.dat", ios::binary);

    if (!dosya.is_open())
    {
        cout << "Arac bilgileri dosyasi acilamadi." << endl;
        return;
    }

    Arac arac;

    cout << "\n Kiralanabilir Arac Listesi:\n";

    while (dosya.read(reinterpret_cast<char *>(&arac), sizeof(Arac)))
    {
        cout << "Marka: " << arac.marka << "\tModel: " << arac.model << "\tPlaka: " << arac.plaka
             << "\tYil: " << arac.yil << "\tGunluk Ucret: " << arac.gunlukUcret;
        if (arac.kiralandi)
            cout << " (Kiralandi)";
        cout << endl;
    }

    dosya.close();
}




void kiralananAraclariListele()
{
    ifstream dosya("kiralamaBilgileri.dat", ios::binary);

    if (!dosya.is_open())
    {
        cout << "Kiralama bilgileri dosyasi acilamadi." << endl;
        return;
    }

    Kisi musteri;
    Arac arac;
    int kiraGunSayisi;
    float toplamKiraBedeli;

    cout << "\n Kiralanan Arac Listesi:\n";

    while (dosya.read(reinterpret_cast<char *>(&musteri), sizeof(Kisi)))
    {
        dosya.read(reinterpret_cast<char *>(&arac), sizeof(Arac));
        dosya.read(reinterpret_cast<char *>(&kiraGunSayisi), sizeof(int));
        dosya.read(reinterpret_cast<char *>(&toplamKiraBedeli), sizeof(float));

        cout << "Musteri ID: " << musteri.id << "\tMarka: " << arac.marka << "\tModel: " << arac.model
             << "\tPlaka: " << arac.plaka << "\tKira Gun Sayisi: " << kiraGunSayisi
             << "\tToplam Kira Bedeli: " << toplamKiraBedeli << " TL" << endl;
    }

    dosya.close();
}


void aracKiralama()
{
    ifstream aracDosya("aracBilgileri.dat", ios::binary | ios::in);
    ifstream musteriDosya("musteriBilgileri.dat", ios::binary | ios::in);

    if (!aracDosya.is_open() || !musteriDosya.is_open())
    {
        cout << "Dosyalar acilamadi." << endl;
        return;
    }

    Arac arac;
    Kisi musteri;

    cout << "Arac Kiralama\n";
    cout << "Musteri ID: ";
    char arananID[20];
    cin >> arananID;

    // Musteri bulma
    bool musteriVar = false;
    while (musteriDosya.read(reinterpret_cast<char *>(&musteri), sizeof(Kisi)))
    {
        if (strcmp(arananID, musteri.id) == 0)
        {
            musteriVar = true;
            break;
        }
    }

    if (!musteriVar)
    {
        cout << "Musteri bulunamadi.\n";
        aracDosya.close();
        musteriDosya.close();
        return;
    }

    // Arac listeleme
    aracListele();

    cout << "Plaka: ";
    char aracPlaka[20];
    cin >> aracPlaka;

    // Arac bulma
    bool aracVar = false;
    while (aracDosya.read(reinterpret_cast<char *>(&arac), sizeof(Arac)))
    {
        if (strcmp(aracPlaka, arac.plaka) == 0 && !arac.kiralandi)
        {
            aracVar = true;
            break;
        }
    }

    if (!aracVar)
    {
        cout << "Arac bulunamadi veya kiralanmis durumda.\n";
        aracDosya.close();
        musteriDosya.close();
        return;
    }

    // Kiralama iþlemi
    arac.kiralandi = true;


int kiraGunSayisi;
    cout << "Kac gun kiralamak istiyorsunuz: ";
    cin >> kiraGunSayisi;

    // Toplam kira bedelini hesapla
    float toplamKiraBedeli = kiraGunSayisi * arac.gunlukUcret;


    // Kiralama bilgilerini dosyaya yazma
    ofstream kiralamaDosya("kiralamaBilgileri.dat", ios::binary | ios::app);

    if (!kiralamaDosya.is_open())
    {
        cout << "Kiralama dosyasi acilamadi." << endl;
        aracDosya.close();
        musteriDosya.close();
        return;
    }

    // Kiralama bilgilerini yazma
    kiralamaDosya.write(reinterpret_cast<char *>(&musteri), sizeof(Kisi));
    kiralamaDosya.write(reinterpret_cast<char *>(&arac), sizeof(Arac));
    kiralamaDosya.write(reinterpret_cast<char *>(&kiraGunSayisi), sizeof(int));
    kiralamaDosya.write(reinterpret_cast<char *>(&toplamKiraBedeli), sizeof(float));

    kiralamaDosya.close();
    musteriDosya.close();
    
    // Gecici dosya oluþturma
    ofstream geciciDosya("geciciAracBilgileri.dat", ios::binary);


    if (!geciciDosya.is_open())
    {
        cout << "Gecici dosya acilamadi." << endl;
        aracDosya.close();
        musteriDosya.close();
        return;
    }

       // Arac bilgilerini gecici dosyaya yazma
    aracDosya.clear(); // Dosyanýn durumunu sýfýrla
    aracDosya.seekg(0, ios::beg);

    while (aracDosya.read(reinterpret_cast<char *>(&arac), sizeof(Arac)))
    {
        if (strcmp(aracPlaka, arac.plaka) != 0)
        {
            geciciDosya.write(reinterpret_cast<char *>(&arac), sizeof(Arac));
        }
    }
    
    
    // Dosyalarý kapatma ve silme iþlemleri
    geciciDosya.close();
    aracDosya.close();
    remove("aracBilgileri.dat");
    rename("geciciAracBilgileri.dat", "aracBilgileri.dat");
    
    cout << "\nKiralama islemi basariyla gerceklesti. Toplam Kira Bedeli: " << toplamKiraBedeli << " TL\n";
    
    
    // Listelenen kiralanan araçlarý göster
    kiralananAraclariListele();

    
    if (!kiralamaDosya.is_open())
    {
        cout << "Kiralama dosyasi acilamadi." << endl;
        musteriDosya.close();
        return;
    }

   // Kiralama bilgilerini yazma
    kiralamaDosya.write(reinterpret_cast<char *>(&musteri), sizeof(Kisi));
    kiralamaDosya.write(reinterpret_cast<char *>(&arac), sizeof(Arac));
    kiralamaDosya.write(reinterpret_cast<char *>(&kiraGunSayisi), sizeof(int));
    kiralamaDosya.write(reinterpret_cast<char *>(&toplamKiraBedeli), sizeof(float));

    kiralamaDosya.close();
    musteriDosya.close();

    cout << "\nKiralama islemi basariyla gerceklesti.\n";
}

int main()
{
    int secim;

    do
    {   
        
	    cout << "|------------Hosgeldiniz------------|" << endl ;
        cout << "|       ARAC KIRALAMA OTOMASYONU    |"<<endl;
	    cout << "|           Secim Yapiniz           |" << endl ;
        cout << "|       1- Yeni Musteri Kaydi       |"<<endl;
        cout << "|       2- Arac Ekle                |"<<endl;
        cout << "|       3- Arac Listele             |"<<endl;
        cout << "|       4- Arac Kiralama            |"<<endl;
        cout << "|       5- Cikis                    |"<<endl;
    	cout << "|-----------------------------------|" << endl ;
        
        cout << "   Seciminiz:";
        cin >> secim;

        switch (secim)
        {
        case 1:
            yeniMusteriKayit();
            break;
        case 2:
            aracEkle();
            break;
        case 3:
            aracListele();
            break;
        case 4:
            aracKiralama();
            break;
        case 5:
            cout << "Cikis yaptiniz.\n";
            break;
        default:
            cout << "Hatali Secim Yaptiniz.\n";
        }

    } while (secim != 5);

    return 0;
}



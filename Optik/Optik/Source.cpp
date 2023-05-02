#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <chrono>
#include <sstream>
#include <vector>
using namespace std;

class DosyaIslemleri {
public:
	void dosyaYazma(string dosyaIsmi, string dosyaYazilacakMetin);
	void dosyaOkuma(string dosyaIsmi);
};

void DosyaIslemleri::dosyaYazma(string dosyaIsmi, string dosyaYazilacakMetin) {

	// Dosya olusturma
	ofstream file(dosyaIsmi, ios::app);
	// Dosya acilirken bir hata olustuysa hata mesaji yazma ve dosyayi olusturma
	if (!file.is_open())
	{
		file.open(dosyaIsmi, ios::out);
	}
	// Dosyaya yazma
	file << dosyaYazilacakMetin << endl;
	// Dosyayı kapatma
	file.close();
}

void DosyaIslemleri::dosyaOkuma(string dosyaIsmi) {
	list<string> list;

	// Dosya olusturma
	ifstream file(dosyaIsmi);
	// Dosya acilirken bir hata olustuysa hata mesaji yazma ve dosyayi olusturma
	if (!file) {
		file.open(dosyaIsmi, ios::out);
	}

	// Dosyadaki satirlari okuma ve ekrana yazma
	string satir;
	int n = 1;
	while (getline(file, satir))
	{
		cout << n << ") " << satir << endl;
		n++;
	}
	// Dosyayı kapatma
	file.close();
}
vector<string> readLine(string filename, int lineNumber) {
	// Dosyayı açın
	ifstream file(filename);
	if (!file.is_open()) {
		// Dosya açılamadıysa hata verin ve boş bir dizi döndürün
		//cerr << "Dosya açılamadı!" << endl;
		return vector<string>();
	}

	// Dosyayı satır satır okuyun
	string line;
	int currentLine = 0;
	while (getline(file, line)) {
		// İstenilen satırı bulduysak, satırdaki elemanları ayırın ve döndürün
		if (currentLine == lineNumber) {
			vector<string> elements;
			stringstream ss(line);
			string element;
			while (getline(ss, element, ' ')) {
				elements.push_back(element);
			}
			return elements;
		}
		currentLine++;
	}

	// İstenilen satır bulunamadıysa hata verin ve boş bir dizi döndürün
	//cerr << "Belirtilen satır bulunamadı!" << endl;
	return vector<string>();
}


class UrunIslemleri : public DosyaIslemleri {
public:
	DosyaIslemleri dosya;

	string marka, model;
	int stok;
	double maliyet, fiyat;

	void ekle() {	//Urun ekleme bu fonksiyonda yapilir ve loga yazilir.
		cout << "-----Eklemek istediginiz urunun-----" << endl;
		cout << "Markasi : ";
		cin >> marka;
		cout << "Modeli: ";
		cin >> model;
		cout << "Stogu: ";
		cin >> stok;
		cout << "Maliyeti: ";
		cin >> maliyet;
		cout << "Fiyati: ";
		cin >> fiyat;
		dosyaYazma("Gozlukler.txt", "Marka: " + marka + " Model: " + model + " Stok: " + to_string(stok) + " Maliyet: " + to_string(maliyet) + " TL " + " Fiyat: " + to_string(fiyat) + " TL");
		dosyaYazma("log.txt", "Marka: " + marka + " Model: " + model + " Stok: " + to_string(stok) + " Maliyet: " + to_string(maliyet) + " TL " + " Fiyat: " + to_string(fiyat) + " TL urunu eklendi");
	}


	void sil(string dosyaIsmi) {	//Urun silme bu fonksiyonda yapilir ve loga yazilir.

		list < string >list;

		ifstream inputFile(dosyaIsmi);
		ofstream outputFile("tempp.txt");
		string line;
		ifstream file(dosyaIsmi);

		if (!file.is_open()) {
			file.open(dosyaIsmi, ios::out);
		}
		while (getline(file, line)) {
			list.push_back(line);
		}

		file.close();

		cout << "-----------------" << endl << " GOZLUKLER " << endl << "-----------------" << endl;
		int idd = 1;
		for (auto a : list) {
			cout << idd << ") " << a << endl;
			idd++;
		}

		int currentLine = 1;
		int silinecekSatir;

		cout << "silinecek urunun idsini girin: ";
		cin >> silinecekSatir;
		vector<string> dizi = readLine("Gozlukler.txt", silinecekSatir - 1);
		while (getline(inputFile, line))
		{
			if (currentLine != silinecekSatir)
				outputFile << line << endl;
			currentLine++;
		}


		inputFile.close();
		outputFile.close();

		remove(dosyaIsmi.c_str());
		rename("tempp.txt", dosyaIsmi.c_str());
		dosyaYazma("GozluklerLog.txt", dizi[0] + dizi[1] + " " + dizi[2] + dizi[3] + " " + dizi[9] + dizi[11] + " TL degerindeki urun silindi");
		dosyaYazma("log.txt", dizi[0] + dizi[1] + " " + dizi[2] + dizi[3] + " " + dizi[9] + dizi[11] + " TL degerindeki urun silindi");

	}






	void guncelle() {

		list < string >list;

		string dosya1;
		dosya1 = "Gozlukler.txt";


		// Dosyayi okuma modunda ac
		ifstream inputFile(dosya1);


		// Yedek dosya olusturma
		ofstream outputFile("temp.txt");


		// Dosya satir satir okunur ve yedek dosyaya yazilir
		int currentLine = 1;
		int guncellenecekSatir;

		string line;
		ifstream file(dosya1);
		if (!file.is_open()) {
			file.open(dosya1, ios::out);
		}
		while (getline(file, line)) {
			list.push_back(line);
		}

		file.close();

		dosyaOkuma("Gozlukler.txt");

		cout << "guncellenecek urunun idsini girin: ";
		cin >> guncellenecekSatir;
		vector<string> dizi = readLine("Gozlukler.txt", guncellenecekSatir - 1);

		while (getline(inputFile, line))
		{
			// Secilen satir silinir ve yazilmaz
			if (currentLine != guncellenecekSatir)
				outputFile << line << endl;
			else {

				string marka, model;
				int stok;
				double maliyet, fiyat;

				cout << "-----Guncellemek istediginiz urunun-----" << endl;
				cout << "Markasi : ";
				cin >> marka;
				cout << "Modeli: ";
				cin >> model;
				cout << "Stogu: ";
				cin >> stok;
				cout << "Maliyeti: ";
				cin >> maliyet;
				cout << "Fiyati: ";
				cin >> fiyat;


				string guncellenecek = "Marka: " + marka + " Model: " + model + " Stok: " + to_string(stok) + " Maliyet: " + to_string(maliyet) + " TL " + " Fiyat: " + to_string(fiyat) + " TL";
				outputFile << guncellenecek << endl;

			}

			currentLine++;
		}

		// Dosyalar kapatilir
		inputFile.close();
		outputFile.close();


		// ilk dosya silinir ve yedek dosya adiyla yeniden adlandirilir
		remove(dosya1.c_str());
		rename("temp.txt", dosya1.c_str());
		dosyaYazma("GozluklerLog.txt", dizi[0] + dizi[1] + " " + dizi[2] + dizi[3] + " " + dizi[9] + dizi[11] + " TL degerindeki urun guncellendi");
		dosyaYazma("log.txt", dizi[0] + dizi[1] + " " + dizi[2] + dizi[3] + " " + dizi[9] + dizi[11] + " TL degerindeki urun guncellendi");

	}
};

class MusteriIslemleri : public DosyaIslemleri {
private:

	void yeniMusteri()
	{
		string telNo, isim, soyIsim;

		cout << "Lutfen telefon numarinizi girin: ";
		cin >> telNo;
		cout << "Lutfen isminizi girin: ";
		cin >> isim;
		cout << "Lutfen soyisminizi girin: ";
		cin >> soyIsim;

		ofstream dosya;
		dosya.open(telNo + ".txt"); // telNo isminde bir txt dosyası oluşturulur
		dosya << "İsim: " << isim << endl;
		dosya << "Soyisim: " << soyIsim << endl;
		dosya.close();
	}


	void musteriGecmisi() {
		string telNo;
		cout << "Lutfen telefon numaranizi girin: ";
		cin >> telNo;
		string yazi = telNo + ".txt";
		dosyaOkuma(yazi);

	}

	friend class Menu;
};

class KasaIslemleri : DosyaIslemleri {

	double readAndSumValues(string dosyaAdi)
	{
		ifstream inputFile(dosyaAdi);
		string line;
		double value, sum = 0.0;
		while (getline(inputFile, line))
		{
			stringstream ss(line);
			while (ss >> value)
			{
				sum += value;
			}
		}

		inputFile.close();

		return sum;
	}
	void sil(string dosyaIsmi) {	//Urun silme bu fonksiyonda yapilir ve loga yazilir.

		list < string >list;

		ifstream inputFile(dosyaIsmi);
		ofstream outputFile("tempp.txt");
		string line;
		ifstream file(dosyaIsmi);
		if (!file.is_open()) {
			file.open(dosyaIsmi, ios::out);
		}
		while (getline(file, line)) {
			list.push_back(line);
		}

		file.close();

		cout << "-----------------" << endl << " GİDERLER " << endl << "-----------------" << endl;
		int idd = 1;
		for (auto a : list) {
			cout << idd - 1 << ") " << a << endl;
			idd++;
		}

		int currentLine = 1;
		int silinecekSatir;
		cout << "silinecek urunun idsini girin: ";
		cin >> silinecekSatir;
		while (getline(inputFile, line))
		{
			if (currentLine != silinecekSatir + 1)
				outputFile << line << endl;
			currentLine++;
		}

		inputFile.close();
		outputFile.close();

		remove(dosyaIsmi.c_str());
		rename("tempp.txt", dosyaIsmi.c_str());

	}
	vector<string> readLine(string filename, int lineNumber) {
		// Dosyayı açın
		ifstream file(filename);
		if (!file.is_open()) {
			// Dosya açılamadıysa hata verin ve boş bir dizi döndürün
			cerr << "Dosya açılamadı!" << endl;
			return vector<string>();
		}

		// Dosyayı satır satır okuyun
		string line;
		int currentLine = 0;
		while (getline(file, line)) {
			// İstenilen satırı bulduysak, satırdaki elemanları ayırın ve döndürün
			if (currentLine == lineNumber) {
				vector<string> elements;
				stringstream ss(line);
				string element;
				while (getline(ss, element, ' ')) {
					elements.push_back(element);
				}
				return elements;
			}
			currentLine++;
		}

		// İstenilen satır bulunamadıysa hata verin ve boş bir dizi döndürün
		cerr << "Belirtilen satir bulunamadı!" << endl;
		return vector<string>();
	}

	string detayliRapor(double gelir, double gider) {
		double oran;
		string text;
		double toplam = gelir + gider;
		double fark = gelir - gider;
		if (gelir > gider) {
			oran = 100.0 * fark / toplam;
			text = "+%" + to_string(oran);

		}
		else if (fark == 0) {
			oran = 0;
			text = "%" + to_string(oran);

		}
		else {
			fark = gider - gelir;
			oran = 100.0 * fark / toplam;
			text = "-%" + to_string(oran);
		}

		return text;
	}
	//// dosyadaki verilen satırı verilen string değer ile değiştirir
	//void dosya_satiri_degistir(const char* dosya_adi, int satir_numarasi, std::string yeni_deger) {
	//	// dosyayı açıyoruz
	//	FILE dosya;
	//	fopen(dosya_adi, "r+");

	//	// dosyanın verilen satırına gidiyoruz
	//	fseek(&dosya, 0, SEEK_SET);
	//	fseek(&dosya, (satir_numarasi - 1) * sizeof(char), SEEK_CUR);

	//	// verilen satırı okuyoruz
	//	char satir[100];
	//	fgets(satir, 100, &dosya);

	//	// dosyayı yeniden açarak verilen değeri yazıyoruz
	//	freopen(dosya_adi, "w", &dosya);
	//	fputs(yeni_deger.c_str(), &dosya);

	//	// dosyayı kapatıyoruz
	//	fclose(&dosya);
	//}

	void satisYap() {
		string musterid;

		cout << "Satis yapmak istediginiz musteri telefon numarasini giriniz: ";
		cin >> musterid;    //tel no alındı


		// Müşteri ID'si ile aynı isimde bir dosya var mı kontrol edin
		ifstream dosya(musterid + ".txt");
		if (!dosya.is_open()) {
			cout << "Müşteri kayıtlı değil" << endl;
			return;
		}
		dosya.close();

		dosyaOkuma("Gozlukler.txt");
		cout << "Urun seciniz: ";
		int satir;
		cin >> satir;
		vector<string> dizi = readLine("Gozlukler.txt", satir - 1);

		string yazi = dizi[0] + dizi[1] + " " + dizi[2] + dizi[3] + " " + dizi[9] + dizi[11] + " TL degerindeki urun satın alındı ";
		dosyaYazma(musterid + ".txt", yazi);
		dosyaYazma("gelirFiyat.txt", dizi[11]);
		dosyaYazma("giderFiyat.txt", dizi[7]);

		string yazi2 = dizi[0] + dizi[1] + " " + dizi[2] + dizi[3] + " " + dizi[9] + dizi[11] + " fiyatındaki ürün " + musterid + " tarafından satın alındı ";
		string yazi3 = dizi[0] + dizi[1] + " " + dizi[2] + dizi[3] + " " + dizi[6] + dizi[7] + " maliyetindeki ürün " + musterid + " tarafından satın alındı ";
		dosyaYazma("satisLog.txt", yazi2);
		dosyaYazma("giderLog.txt", yazi3);

		cout << "Satis yapildi" << endl;

		/*int sayi = stoi(dizi[5]) - 1;
		string yazi4 = "Marka: " + dizi[1] + " Model: " + dizi[3] + " Stok: " + to_string(sayi)+" Maliyet: " + dizi[7] + " TL " + " Fiyat: " + dizi[11] + " TL";
		dosya_satiri_degistir("Gozlukler.txt",satir,yazi4);*/
	}


	virtual void gelirler() { // virtual fonk kullanimi

		cout << "Toplam gelir: ";
		cout << readAndSumValues("gelirFiyat.txt");
		cout << "\nDetaylar [1] " << endl;
		cout << "Cikmak [0] " << endl;
		cout << "Seçiminiz:";


		int secim;
		cin >> secim;
		switch (secim) {
		case 1:
			dosyaOkuma("satisLog.txt");
			break;
		case 0:
			break;
		default:
			cout << "Hatali giris yaptiniz!";
			break;
		}
	}
	virtual void giderler() {

		cout << "Gider ekle [1]" << endl;
		cout << "Gider sil [2]" << endl;
		cout << "Mevcut giderler [3]" << endl;
		cout << "Cikis [0]" << endl;
		cout << "Seçiminiz:";

		int secim;
		cin >> secim;
		switch (secim) {
		case 1:
		{string isim;
		double fiyat;

		cout << "Gider ismi: ";
		cin >> isim;
		cout << "Gider fiyati: ";
		cin >> fiyat;

		dosyaYazma("giderFiyat.txt", to_string(fiyat));

		ofstream giderler("giderLog.txt", ios::app); // dosyayı append mode'unda açıyoruz, yani dosyanın sonuna yazıyoruz
		giderler << isim << " " << fiyat << " TL degerinde urun satin alindi" << endl;
		giderler.close();

		cout << "Gider eklendi." << endl;
		break;
		}case 2:
		{sil("giderLog.txt");

		break;
		}case 3:
		{dosyaOkuma("giderLog.txt");
		break;
		}case 0:
		{cout << "Cikis yapiliyor..." << endl;
		break;
		}default:
			cout << "Hatali giris yaptiniz!" << endl;
			break;
		}

	}
	void rapor() {
		double kâr = readAndSumValues("gelirFiyat.txt") - readAndSumValues("giderFiyat.txt");
		cout << "Toplam kariniz: " << kâr << endl;
		cout << detayliRapor(readAndSumValues("gelirFiyat.txt"), readAndSumValues("giderFiyat.txt")) << endl;

	}
	friend class Menu;
};


class Menu {
public:

	void navigasyon() {
		cout << "----------------------------------------------------\nSatis Asistanina Hos Geldin Patron \nBugun Sana Nasil Yardimci Olabilirim?\n----------------------------------------------------" << endl;
		cout << "Urun islemleri [1]" << endl;
		cout << "Musteri islemleri [2]" << endl;
		cout << "Kasa islemleri [3]" << endl;
		cout << "Islem yapmak istediginiz menu numarasini giriniz: ";
		int islem;
		UrunIslemleri urun;
		MusteriIslemleri musteri;
		KasaIslemleri kasa;
		cin >> islem;
		switch (islem) {
		case 1:
			cout << "Urun eklemek icin [1]" << endl;
			cout << "Urun silmek icin [2] " << endl;
			cout << "Urun guncellemek icin [3]" << endl;
			cout << "Geri gitmek icin [0]" << endl;
			cout << "Seciminiz: ";
			int secim;
			cin >> secim;
			switch (secim) {
			case 1:
				urun.ekle();

				navigasyon();
				break;
			case 2:
				urun.sil("Gozlukler.txt");
				navigasyon();
				break;
			case 3:
				urun.guncelle();
				navigasyon();
				break;
			case 0:
				navigasyon();
			default:
				cout << "Hatali giris yaptiniz!" << endl;
				break;
			}
			break;

		case 2:
			cout << "Yeni musteri icin [1]" << endl;
			cout << "Musteri gecmisini goruntulemek icin [2] " << endl;
			cout << "Geri gitmek icin [0]" << endl;
			cout << "Seciminiz: ";
			int secim2;
			cin >> secim2;
			switch (secim2) {
			case 1:
				musteri.yeniMusteri();
				navigasyon();
				break;
			case 2:
				musteri.musteriGecmisi();
				navigasyon();
				break;
			case 0:
				navigasyon();
				break;
			default:
				cout << "Hatali giris yaptiniz!" << endl;
				break;
			}
			break;

		case 3:
			cout << "Satis yapmak icin  [1]" << endl;
			cout << "Gelirleri goruntulemek icin [2] " << endl;
			cout << "Giderleri goruntulemek icin [3] " << endl;
			cout << "Rapor icin [4] " << endl;
			cout << "Geri gitmek icin [0]" << endl;
			cout << "Seciminiz: ";
			int secim3;
			cin >> secim3;
			switch (secim3) {
			case 1:
				kasa.satisYap();
				navigasyon();
				break;
			case 2:
				kasa.gelirler();
				navigasyon();
				break;
			case 3:
				kasa.giderler();
				navigasyon();
				break;
			case 4:
				kasa.rapor();
				navigasyon();
				break;
			case 0:
				navigasyon();
			default:
				cout << "Hatali giris yaptiniz!" << endl;
				break;
			}
			break;

			break;
		default:
			cout << "Hatali giris yaptiniz!" << endl;
			break;

		}

	}

};


int main() {

	Menu menu;
	menu.navigasyon();

	return 0;
}

// Proiect3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


									//GESTIUNEA UNUI MAGAZIN DE DECORATIUNI
#include <iostream>
#include<string>
#include<fstream>
#include<map>
#include<set>
#include<vector>
#include<list>
#pragma warning(disable:4996)
using namespace std;

//CLASE ABSTRACTE
class Fisier {
public:
	virtual void scriereInFisier(fstream& f) = 0;
	virtual void citireDinFisier(fstream& f) = 0;
};
class CAS{
public:
	virtual float calculCAS() = 0;
	virtual float calculCASS() = 0;
};

//CLASELE INITIALE
class Angajat :public Fisier
{
private:
	const int idAngajat;
	char* nume;
	string functie;
	float salariu;
	int vechime; // la acest magazin, exprimata in luni de zile;
	int oreLucrate[6]; //orele lucrate in ultimele 6 luni in cadrul magazinului;

public:

	void scriereInFisier(fstream& f)
	{
		f.write((char*)&this->idAngajat, sizeof(int));  //scrierea id-ului

		int lungime = strlen(this->nume) + 1;            //scrierea numelui
		f.write((char*)&lungime, sizeof(int));
		f.write(this->nume, lungime * sizeof(char));

		int lg = this->functie.length() + 1;             //scrierea functiei
		f.write((char*)&lg, sizeof(int));
		f.write(this->functie.data(), lg * sizeof(char));

		f.write((char*)&this->salariu, sizeof(float));   //scrierea salariului

		f.write((char*)&this->vechime, sizeof(int));     //scrierea vechimii

		for (int i = 0; i < 6; i++)                      //scrierea orelor lucrate
			f.write((char*)&this->oreLucrate[i], sizeof(int));
	}
	void citireDinFisier(fstream& f)
	{
		f.read((char*)&this->idAngajat, sizeof(int)); //citirea id-ului

		int lungime;                                  // citirea numelui
		f.read((char*)&lungime, sizeof(int));
		char* bufferNume = new char[lungime];
		f.read(bufferNume, lungime);
		delete[]this->nume;
		this->nume = new char[strlen(bufferNume) + 1];
		strcpy(this->nume, bufferNume);
		delete[] bufferNume;

		int lg;                                       //citirea functiei
		f.read((char*)&lg, sizeof(int));
		char* bufferFunctie = new char[lg];
		f.read(bufferFunctie, lg);
		this->functie = bufferFunctie;
		delete[]bufferFunctie;

		f.read((char*)&this->salariu, sizeof(float)); //citirea  salariului

		f.read((char*)&this->vechime, sizeof(int));   //citirea vechimii

		for (int i = 0; i < 6; i++)                   //citirea orelor lucrate
			f.read((char*)&this->oreLucrate[i], sizeof(int) * 6);
	}
	friend ofstream& operator<<(ofstream& f, Angajat a)
	{
		if (f.is_open())
		{
			f << a.idAngajat << endl;
			f << "" << a.nume << endl;
			f << "" << a.functie << endl;
			f << a.salariu << endl;
			f << a.vechime << endl;
			for (int i = 0; i < 6; i++)
				f << a.oreLucrate[i] << endl;
		}
		return f;
	}

	Angajat() :idAngajat(0)
	{
		nume = new char[strlen("Anonim") + 1];
		strcpy(nume, "Anonim");
		functie = "necunoscuta";
		salariu = 0;
		vechime = 0;
		for (int i = 0; i < 6; i++)
			oreLucrate[i] = 0;
	}
	Angajat(int idAngajat, const char* nume, string functie, float salariu, int vechime, int oreLucrate[]) :idAngajat(idAngajat)
	{
		if (nume != NULL)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		this->functie = functie;
		if (salariu > 0)
		{
			this->salariu = salariu;
		}
		if (vechime > 0)
			this->vechime = vechime;
		for (int i = 0; i < 6; i++)
			this->oreLucrate[i] = oreLucrate[i];
	}
	Angajat(int idAngajat, const char* nume, string functie, float salariu) :idAngajat(idAngajat)
	{
		if (nume != NULL)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		this->functie = functie;
		if (salariu > 0)
			this->salariu = salariu;
		vechime = 0;
		for (int i = 0; i < 6; i++)
			oreLucrate[i] = 0;
	}

	const int getidAngajat()
	{
		return this->idAngajat;
	}
	char* getnume()
	{
		return this->nume;
	}
	void setnume(const char* nume)
	{
		if (strlen(nume) > 3)
		{
			delete[] this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}
	string getfunctie()
	{
		return this->functie;
	}
	void setfunctie(string functie)
	{
		if (functie.size() > 5)
			this->functie = functie;
	}
	float getsalariu()
	{
		return this->salariu;
	}
	void setsalariu(float salariu)
	{
		if (salariu > 2550)  //salariul minim pe economie
			this->salariu = salariu;
	}
	int getvechime()
	{
		return this->vechime;
	}
	void setvechime(int vechime)
	{
		if (vechime > 0)
			this->vechime = vechime;
	}
	int* getoreLucrate()
	{
		return this->oreLucrate;
	}
	void setoreLucrate(const int ore[], int lungime)
	{
		if (lungime == 6)
			for (int i = 0; i < 6; i++)
			{
				if (ore[i] > 0)
					this->oreLucrate[i] = ore[i];
			}
	}

	Angajat(const Angajat& a) :idAngajat(a.idAngajat)
	{
		if (a.nume != NULL)
		{
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
		}
		this->functie = a.functie;
		if (a.salariu > 0)
			this->salariu = a.salariu;
		if (a.vechime > 0)
			this->vechime = a.vechime;
		for (int i = 0; i < 6; i++)
			this->oreLucrate[i] = a.oreLucrate[i];
	}
	Angajat& operator=(const Angajat& a)
	{
		if (this != &a)
		{
			delete[] this->nume;
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
			this->functie = a.functie;
			if (a.salariu > 0)
				this->salariu = a.salariu;
			if (this->vechime > 0)
				this->vechime = a.vechime;
			for (int i = 0; i < 6; i++)
				this->oreLucrate[i] = a.oreLucrate[i];
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Angajat& a)
	{
		out << "\n-----------------ANGAJAT-----------------" << endl;
		out << "Id angajat: " << a.idAngajat << endl;
		out << "Nume angajat: " << a.nume << endl;
		out << "Functie angajat: " << a.functie << endl;
		out << "Salariu angajat: " << a.salariu << " lei" << endl;
		out << "Vechime angajat: " << a.vechime << " luni" << endl;
		out << "Numar de ore lucrate in ultimele 6 luni:" << endl;
		for (int i = 0; i < 6; i++)
		{
			out << "Luna [" << i << "]= " << a.oreLucrate[i] << " ore" << endl;
		}
		out << "-----------------------------------------" << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Angajat& a)
	{
		delete[]a.nume;
		cout << "Introduceti numele angajatului: ";
		char aux[100];
		in >> aux;
		a.nume = new char[strlen(aux) + 1];
		strcpy(a.nume, aux);
		cout << "Introduceti functia angajatului: ";
		in >> a.functie;
		cout << "Introduceti valoarea salariului angajatului: ";
		in >> a.salariu;
		cout << "Introduceti vechimea angajatului: ";
		in >> a.vechime;
		cout << "Introduceti numarul de ore lucrate in fiecare luna: ";
		for (int i = 0; i < 6; i++)
		{
			cout << "Luna [" << i << "]= ";
			in >> a.oreLucrate[i];
		}
		return in;
	}
	~Angajat()
	{
		delete[] this->nume;
	}

	void cresteSalariu(float sumaDeAdaugat)
	{
		if (sumaDeAdaugat > 0)
			this->salariu += sumaDeAdaugat;
	}
	int medieOreLucrate()
	{
		int suma = 0;
		int medie = 0;
		for (int i = 0; i < 6; i++)
		{
			suma += this->oreLucrate[i];
		}
		medie = suma / 6;
		return medie;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < 6)
			return this->oreLucrate[index];
	}
	Angajat operator+(int nrOreSupl)
	{
		for (int i = 0; i < 6; i++)
		{
			this->oreLucrate[i] += nrOreSupl;
		}
		return *this;
	}

	Angajat& operator++()
	{
		this->vechime++;
		return *this;
	}
	Angajat operator++(int)
	{
		Angajat rez = *this;
		this->vechime++;
		return rez;
	}
	bool operator!()
	{
		if (this->vechime == 0)
			return true;
		else
			return false;
	}

	bool operator>=(const Angajat& a)
	{
		return this->salariu >= a.salariu;
	}
	explicit operator int()
	{
		int suma = 0;
		for (int i = 0; i < 6; i++)
		{
			suma += oreLucrate[i];
		}
		return suma;
	}
	bool operator==(const Angajat& a)
	{
		if (this->salariu != a.salariu)
			return false;
		return true;
	}
	virtual string incadrare()
	{
		string tip = "Angajat";
		return tip;
	}
	float calculCAS()
	{	
		return (25 * this->salariu/100);
	}
	float calculCASS()
	{
		return(10 * this->salariu / 100);
	}
};
class Client :public Fisier
{
private:
	const int id;
	char* numeC;
	char* nrTelefon;
	string adresa;
	int creditDisponibil;
	float valoriComenzi[3]; //valoarea ultimelor 3 comenzi


public:

	void scriereInFisier(fstream& f)
	{
		f.write((char*)&this->id, sizeof(int));

		int lg = strlen(this->numeC) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->numeC, lg * sizeof(char));

		int lg1 = strlen(this->nrTelefon) + 1;
		f.write((char*)&lg1, sizeof(int));
		f.write(this->nrTelefon, lg1 * sizeof(char));

		int lg2 = this->adresa.length() + 1;
		f.write((char*)&lg2, sizeof(int));
		f.write(this->adresa.data(), lg2 * sizeof(char));

		f.write((char*)&this->creditDisponibil, sizeof(int));

		for (int i = 0; i < 3; i++)
			f.write((char*)&this->valoriComenzi[i], sizeof(float));
	}
	void citireDinFisier(fstream& f)
	{
		f.read((char*)&this->id, sizeof(int));

		int lg;
		f.read((char*)&lg, sizeof(int));
		char* bufferNumeC = new char[lg];
		f.read(bufferNumeC, lg);
		delete[]this->numeC;
		this->numeC = new char[strlen(bufferNumeC) + 1];
		strcpy(this->numeC, bufferNumeC);
		delete[] bufferNumeC;

		int lg1;
		f.read((char*)&lg1, sizeof(int));
		char* bufferTelefon = new char[lg1];
		f.read(bufferTelefon, lg1);
		delete[]this->nrTelefon;
		this->nrTelefon = new char[strlen(bufferTelefon) + 1];
		strcpy(this->nrTelefon, bufferTelefon);
		delete[] bufferTelefon;

		int lg2;
		f.read((char*)&lg2, sizeof(int));
		char* bufferAdresa = new char[lg2];
		f.read(bufferAdresa, lg2);
		this->adresa = bufferAdresa;
		delete[]bufferAdresa;

		f.read((char*)&this->creditDisponibil, sizeof(int));

		for (int i = 0; i < 3; i++)
			f.read((char*)&this->valoriComenzi[i], sizeof(float));

	}
	Client() :id(0)
	{
		numeC = new char[strlen("Anonim") + 1];
		strcpy(numeC, "Anonim");
		nrTelefon = new char[strlen("N/A") + 1];
		strcpy(nrTelefon, "N/A");
		adresa = "Necunoscuta";
		creditDisponibil = 0;
		for (int i = 0; i < 3; i++)
			valoriComenzi[i] = 0;
	}
	Client(int id, const char* numeC, const char* nrTelefon, string adresa, int creditDisponibil, float valoriComenzi[]) :id(id)
	{
		this->numeC = new char[strlen(numeC) + 1];
		strcpy(this->numeC, numeC);
		this->nrTelefon = new char[strlen(nrTelefon) + 1];
		strcpy(this->nrTelefon, nrTelefon);
		this->adresa = adresa;
		if (creditDisponibil > 0)
			this->creditDisponibil = creditDisponibil;
		for (int i = 0; i < 3; i++)
			this->valoriComenzi[i] = valoriComenzi[i];
	}
	Client(int id, const char* numeC, const char* nrTelefon, string adresa) :id(id)
	{
		this->numeC = new char[strlen(numeC) + 1];
		strcpy(this->numeC, numeC);
		this->nrTelefon = new char[strlen(nrTelefon) + 1];
		strcpy(this->nrTelefon, nrTelefon);
		this->adresa = adresa;
		this->creditDisponibil = 0;
		for (int i = 0; i < 3; i++)
			valoriComenzi[i] = 0;
	}


	Client(const Client& c) :id(c.id)
	{
		this->numeC = new char[strlen(c.numeC) + 1];
		strcpy(this->numeC, c.numeC);
		this->nrTelefon = new char[strlen(c.nrTelefon) + 1];
		strcpy(this->nrTelefon, c.nrTelefon);
		this->adresa = c.adresa;
		if (c.creditDisponibil > 0)
			this->creditDisponibil = c.creditDisponibil;
		for (int i = 0; i < 3; i++)
			this->valoriComenzi[i] = c.valoriComenzi[i];
	}
	Client& operator=(const Client& c)
	{
		if (this != &c)
		{
			delete[] this->numeC;
			delete[] this->nrTelefon;

			this->numeC = new char[strlen(c.numeC) + 1];
			strcpy(this->numeC, c.numeC);
			this->nrTelefon = new char[strlen(c.nrTelefon) + 1];
			strcpy(this->nrTelefon, c.nrTelefon);
			this->adresa = c.adresa;
			if (c.creditDisponibil > 0)
				this->creditDisponibil = c.creditDisponibil;
			for (int i = 0; i < 3; i++)
				this->valoriComenzi[i] = c.valoriComenzi[i];
		}
		return *this;
	}
	~Client()
	{
		delete[] this->numeC;
		delete[] this->nrTelefon;
	}
	int getid()
	{
		return this->id;
	}
	char* getnumeC()
	{
		return this->numeC;
	}
	char* getnrTelefon()
	{
		return this->nrTelefon;
	}
	string getadresa()
	{
		return this->adresa;
	}
	int getcreditDisponibil()
	{
		return this->creditDisponibil;
	}
	float* getvaloriComenzi()
	{
		return this->valoriComenzi;
	}

	void setnumeC(const char* numeC)
	{
		if (strlen(numeC) > 3)
		{
			delete[]this->numeC;
			this->numeC = new char[strlen(numeC) + 1];
			strcpy(this->numeC, numeC);
		}
	}
	void setnrTelefon(const char* nrTelefon)
	{
		if (strlen(nrTelefon) >= 10 && strlen(nrTelefon) <= 14)  //numerele de telefon in Romania au 10 cifre, maxim 14 cifre daca se apeleaza cu prefix din afara
		{
			delete[]this->nrTelefon;
			this->nrTelefon = new char[strlen(nrTelefon) + 1];
			strcpy(this->nrTelefon, nrTelefon);
		}
	}
	void setadresa(string adresa)
	{
		if (adresa.size() > 10)
			this->adresa = adresa;
	}
	void setcreditDisponibil(int creditDisponibil)
	{
		if (creditDisponibil > 0)
			this->creditDisponibil = creditDisponibil;
	}
	void setvaloriComenzi(const float valoriComenzi[], int lungime)
	{
		if (lungime == 3)
			for (int i = 0; i < 3; i++)
			{
				if (valoriComenzi[i] > 0)
					this->valoriComenzi[i] = valoriComenzi[i];
			}
	}
	friend ostream& operator<<(ostream& out, const Client& c)
	{
		out << "--------------------CLIENT------------------------" << endl;
		out << "Id client: " << c.id << endl;
		out << "Nume client: " << c.numeC << endl;
		out << "Nr telefon: " << c.nrTelefon << endl;
		out << "Adresa clientului: " << c.adresa << endl;
		out << "Creditul disponibil: " << c.creditDisponibil << " lei" << endl;
		out << "Valori comenzi anterioare: " << endl;
		for (int i = 0; i < 3; i++)
		{
			out << "Valoarea comenzii [" << i << "]= " << c.valoriComenzi[i] << " lei" << endl;
		}
		out << "--------------------------------------------------" << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Client& c)
	{
		delete[] c.numeC;
		delete[] c.nrTelefon;
		cout << "Introduceti numele Clientului: ";
		char aux[100];
		in >> aux;
		c.numeC = new char[strlen(aux) + 1];
		strcpy(c.numeC, aux);
		cout << "Introduceti nr de telefon: ";
		char aux2[20];
		in >> aux2;
		c.nrTelefon = new char[strlen(aux2) + 1];
		strcpy(c.nrTelefon, aux2);
		cout << "Introduceti adresa: ";
		in >> c.adresa;
		cout << "Introduceti creditul disponibil: ";
		in >> c.creditDisponibil;
		for (int i = 0; i < 3; i++)
		{
			cout << "Introduceti valoarea comenzii [" << i << "]= ";
			in >> c.valoriComenzi[i];
		}
		return in;
	}
	void adaugacodPostal(string codPostal)
	{
		if (codPostal.size() == 6) //codurile postale sunt formate din 6 cifre
			this->adresa += " " + codPostal;
		else {
			throw new exception("Nu ati introdus un cod postal de dimensiune standard");
		}
	}
	void maresteCredit(int credit)
	{
		if (credit > 0)
			this->creditDisponibil += credit;
	}

	float operator[](int index)
	{
		if (index >= 0 && index < 3)
			return this->valoriComenzi[index];
	}
	Client operator-(int credit)
	{
		if (this->creditDisponibil - credit >= 0)
			this->creditDisponibil -= credit;
		return *this;
	}
	Client& operator--()
	{
		for (int i = 0; i < 3; i++)
			this->valoriComenzi[i]--;
		return *this;
	}
	Client operator--(int)
	{
		Client rez = *this;
		this->creditDisponibil--;
		return rez;
	}
	bool operator< (const Client& c)
	{
		float suma = 0;
		float sumac = 0;
		for (int i = 0; i < 3; i++)
		{
			suma += this->valoriComenzi[i];
		}
		for (int i = 0; i < 3; i++)
		{
			sumac += c.valoriComenzi[i];
		}

		return suma < sumac;
	}
	bool operator!()
	{
		if (this->creditDisponibil == 0)
			return true;
		else
			return false;
	}
	bool operator==(const Client& c)
	{
		if (this->numeC != c.numeC)
			return false;
		return true;
	}
	explicit operator string()
	{
		return this->adresa;
	}
	virtual float reducereAplicata()
	{
		return (5 * this->creditDisponibil)/100;
	}
};
class Produs :public Fisier
{
private:
	const int cod_inregistrare;
	string denumire;
	char* descriere;
	float pret;
	int stoc;
	int bucatiVandute[4]; //nr de bucati vandute in cele 4 trimestre ale anului

public:
	void scriereInFisier(fstream& f)
	{
		f.write((char*)&this->cod_inregistrare, sizeof(int));

		int lg = this->denumire.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->denumire.data(), lg * sizeof(char));

		int lg2 = strlen(this->descriere) + 1;
		f.write((char*)&lg2, sizeof(int));
		f.write(this->descriere, lg2 * sizeof(char));

		f.write((char*)&this->pret, sizeof(float));

		f.write((char*)&this->stoc, sizeof(int));

		for (int i = 0; i < 4; i++)
			f.write((char*)&this->bucatiVandute[i], sizeof(int));
	}
	void citireDinFisier(fstream& f)
	{
		f.read((char*)&this->cod_inregistrare, sizeof(int));

		int lg;
		f.read((char*)&lg, sizeof(int));
		char* bufferDenumire = new char[lg];
		f.read(bufferDenumire, lg);
		this->denumire = bufferDenumire;
		delete[]bufferDenumire;

		int lg2;
		f.read((char*)&lg2, sizeof(int));
		char* bufferDescriere = new char[lg2];
		f.read(bufferDescriere, lg2);
		delete[]this->descriere;
		this->descriere = new char[strlen(bufferDescriere) + 1];
		strcpy(this->descriere, bufferDescriere);
		delete[] bufferDescriere;

		f.read((char*)&this->pret, sizeof(float));

		f.read((char*)&this->stoc, sizeof(int));

		for (int i = 0; i < 4; i++)
			f.read((char*)&this->bucatiVandute[i], sizeof(int));
	}
	Produs() :cod_inregistrare(0)
	{
		denumire = "anonim";
		descriere = new char[strlen("Necunoscuta") + 1];
		strcpy(descriere, "Necunoscuta");
		pret = 0;
		stoc = 0;
		for (int i = 0; i < 4; i++)
			bucatiVandute[i] = 0;
	}
	Produs(int cod_inregistrare, string denumire, const char* descriere, float pret, int stoc, int bucatiVandute[4]) :cod_inregistrare(cod_inregistrare)
	{
		this->denumire = denumire;
		this->descriere = new char[strlen(descriere) + 1];
		strcpy(this->descriere, descriere);
		if (pret > 0)
			this->pret = pret;
		if (stoc >= 0)
			this->stoc = stoc;
		for (int i = 0; i < 4; i++)
			this->bucatiVandute[i] = bucatiVandute[i];
	}
	Produs(int cod_inregistrare, string denumire, const char* descriere, float pret) :cod_inregistrare(cod_inregistrare)
	{
		this->denumire = denumire;
		this->descriere = new char[strlen(descriere) + 1];
		strcpy(this->descriere, descriere);
		if (pret > 0)
			this->pret = pret;
		for (int i = 0; i < 4; i++)
			this->bucatiVandute[i] = 0;
		this->stoc = 0;
	}
	Produs(const Produs& p) :cod_inregistrare(p.cod_inregistrare)
	{
		this->denumire = p.denumire;
		this->descriere = new char[strlen(p.descriere) + 1];
		strcpy(this->descriere, p.descriere);
		if (p.pret > 0)
			this->pret = p.pret;
		if (p.stoc >= 0)
			this->stoc = p.stoc;
		for (int i = 0; i < 4; i++)
			this->bucatiVandute[i] = p.bucatiVandute[i];
	}
	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			delete[]this->descriere;
			this->denumire = p.denumire;
			this->descriere = new char[strlen(p.descriere) + 1];
			strcpy(this->descriere, p.descriere);
			if (p.pret > 0)
				this->pret = p.pret;
			if (p.stoc > 0)
				this->stoc = p.stoc;
			for (int i = 0; i < 4; i++)
				this->bucatiVandute[i] = p.bucatiVandute[i];
		}
		return *this;
	}

	const int getcod_inregistrare()
	{
		return this->cod_inregistrare;
	}
	string getdenumire()
	{
		return this->denumire;
	}
	void setdenumire(string denumire)
	{
		if (denumire.size() > 3)
			this->denumire = denumire;
	}
	char* getdescriere()
	{
		return this->descriere;
	}
	void setdescriere(const char* descriere)
	{
		if (strlen(descriere) > 6)
		{
			delete[] this->descriere;
			this->descriere = new char[strlen(descriere) + 1];
			strcpy(this->descriere, descriere);
		}
	}
	float getpret()
	{
		return this->pret;
	}
	void setpret(float pret)
	{
		if (pret > 0)
			this->pret = pret;
	}
	int getstoc()
	{
		return this->stoc;
	}
	void setstoc(int stoc)
	{
		if (stoc >= 0)
			this->stoc = stoc;
	}
	int* getbucatiVandute()
	{
		return this->bucatiVandute;
	}
	void setbucatiVandute(int* bucati, int lungime)
	{
		if (lungime == 4)
			for (int i = 0; i < 4; i++)
				if (bucati[i] >= 0)
					this->bucatiVandute[i] = bucati[i];
	}


	friend ostream& operator<<(ostream& out, const Produs& p)
	{
		out << "-----------------PRODUS---------------";
		out << "\nCod inregistrare: " << p.cod_inregistrare << endl;
		out << "Denumire: " << p.denumire << endl;
		out << "Descriere: " << p.descriere << endl;
		out << "Pret: " << p.pret << " lei" << endl;
		out << "Stoc: " << p.stoc << endl;
		for (int i = 0; i < 4; i++)
			if (p.bucatiVandute[i] > 0)
				out << "Trimestrul[" << i << "]= " << p.bucatiVandute[i] << " bucati vandute" << endl;
		out << "--------------------------------------";
		return out;
	}
	friend istream& operator>>(istream& in, Produs& p)
	{
		cout << "Introduceti denumirea produsului: ";
		in >> p.denumire;
		cout << "Introduceti descrierea produsului: ";
		char aux[35];
		in >> aux;
		p.descriere = new char[strlen(aux) + 1];
		strcpy(p.descriere, aux);
		cout << "Introduceti pretul produsului: ";
		in >> p.pret;
		cout << "Introduceti stocul disponibil al produsului: ";
		in >> p.stoc;
		for (int i = 0; i < 4; i++)
		{
			cout << "Introduceti numarul de bucati vandute in trimestrul[" << i << "]= ";
			in >> p.bucatiVandute[i];
		}
		return in;
	}
	~Produs()
	{
		delete[] this->descriere;
	}
	float calculTotal()
	{
		int nr = 0;
		for (int i = 0; i < 4; i++)
		{
			nr += this->bucatiVandute[i];
		}
		float total = 0;
		total = nr * this->pret;
		return total;
	}
	int unitatiVandute()  //totalul pe a doua jumatate a anului, adica ultimele 2 trimestre
	{
		int total = 0;
		for (int i = 2; i < 4; i++)
		{
			total += this->bucatiVandute[i];
		}
		return total;
	}
	int operator[](int index)
	{
		for (int i = 0; i < 4; i++)
			if (index == bucatiVandute[i])
				return i;
	}
	Produs operator+(int adaos)
	{
		Produs rez = *this;
		rez.pret += adaos;
		return rez;
	}
	Produs& operator++()
	{
		this->stoc++;
		return *this;
	}
	Produs operator++(int)
	{
		Produs rez = *this;
		this->stoc++;
		return rez;
	}
	bool operator!()
	{
		if (this->stoc == 0)
			return true;
		else
			return false;
	}
	bool operator>(const Produs& p) {
		return this->pret > p.pret;
	}
	bool operator==(const Produs& p)
	{
		if (this->denumire != p.denumire)
			return false;
		return true;
	}
	operator float()
	{
		return this->pret;
	}
	virtual float recalcularePret()
	{
		if (this->stoc < 10)
			return (this->pret-(this->pret*10/100));
	}

};
class Comanda:public Fisier
{
private:
	static int taxalivrare;
	char* awb = NULL;
	Client client;
	int valoare = 0;
	int durataPregatire = 0; //durata de pregatire a comenzii exprimata in zile


public:
	void scriereInFisier(fstream& f)
	{
		int lg2 = strlen(this->awb) + 1;
		f.write((char*)&lg2, sizeof(int));
		f.write(this->awb, lg2 * sizeof(char));
		f.write((char*)& this->client, sizeof(Client));
		f.write((char*)&this->valoare, sizeof(int));
		f.write((char*)&this->durataPregatire, sizeof(int));
	}
	void citireDinFisier(fstream& f)
	{
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* bufferAwb = new char[lg];
		f.read(bufferAwb, lg);
		delete[]this->awb;
		this->awb = new char[strlen(bufferAwb) + 1];
		strcpy(this->awb, bufferAwb);
		delete[] bufferAwb;

		f.read((char*)&this->client, sizeof(Client));

		f.read((char*)&this->valoare, sizeof(int));

		f.read((char*)&this->durataPregatire, sizeof(int));

	}
	Comanda()
	{

	}
	Comanda(const char* awb, Client client, int valoare, int durataPregatire)
	{
		if (awb != NULL)
		{
			this->awb = new char[strlen(awb) + 1];
			strcpy(this->awb, awb);
		}
		this->client = client;
		if (valoare > 0)
			this->valoare = valoare;
		if (durataPregatire >= 0)
			this->durataPregatire = durataPregatire;
	}
	Comanda(const char* awb, int valoare)
	{
		if (awb != NULL)
		{
			this->awb = new char[strlen(awb) + 1];
			strcpy(this->awb, awb);
		}
		if (valoare > 0)
			this->valoare = valoare;
	}
	Comanda(const Comanda& co)
	{
		if (co.awb != NULL)
		{
			this->awb = new char[strlen(co.awb) + 1];
			strcpy(this->awb, co.awb);
		}
		this->client = co.client;
		if (co.valoare > 0)
			this->valoare = co.valoare;
		if (co.durataPregatire >= 0)
			this->durataPregatire = co.durataPregatire;
	}
	Comanda& operator=(const Comanda& co)
	{
		if (this != &co)
		{
			delete[]this->awb;
			if (co.awb != NULL)
			{
				this->awb = new char[strlen(co.awb) + 1];
				strcpy(this->awb, co.awb);
			}
			this->client = co.client;
			if (co.valoare > 0)
				this->valoare = co.valoare;
			if (co.durataPregatire >= 0)
				this->durataPregatire = co.durataPregatire;
		}
		return *this;
	}
	~Comanda()
	{
		delete[] this->awb;
	}
	friend ostream& operator<<(ostream& out, const Comanda& co)
	{
		out << "\n-------------------COMANDA--------------";
		out << "\nAwb: " << co.awb << endl;
		out << "Client: \n" << co.client;
		out << "Valoare: " << co.valoare << " lei" << endl;
		out << "Durata pregatire: " << co.durataPregatire << " zile" << endl;
		out << "-------------------------------------------";
		return out;
	}
	friend istream& operator>>(istream& in, Comanda& co)
	{
		delete[]co.awb;
		cout << "Introduceti awb-ul: ";
		char aux[15];
		in >> aux;
		co.awb = new char[strlen(aux) + 1];
		strcpy(co.awb, aux);
		cout << "Introduceti clientul: ";
		in >> co.client;
		cout << "Introduceti valoarea comenzii: ";
		in >> co.valoare;
		cout << "Introduceti durata de pregatire: ";
		in >> co.durataPregatire;
		return in;
	}
	char* getawb()
	{
		return this->awb;
	}
	void setawb(const char* awb)
	{
		if (strlen(awb) == 8)
		{
			delete[] this->awb;
			this->awb = new char[strlen(awb) + 1];
			strcpy(this->awb, awb);
		}
	}
	Client getclient()
	{
		return this->client;
	}
	void setclient(Client c)
	{
		this->client = c;
	}
	int getvaloare()
	{
		return this->valoare;
	}
	void setvaloare(int valoare)
	{
		if (valoare > 0)
			this->valoare = valoare;
	}
	int getdurataPregatire()
	{
		return this->durataPregatire;
	}
	void setdurata(int durata)
	{
		if (durata >= 0)
			this->durataPregatire = durata;
	}
	static int gettaxaLivrare()
	{
		return Comanda::taxalivrare;
	}
	static void settaxaLivrare(int taxalivrare)
	{
		if (taxalivrare > 0)
		{
			Comanda::taxalivrare = taxalivrare;
		}
		else {
			throw new exception("Valoarea introdusa nu este pozitiva");
		}
	}
	int operator[](int index)
	{

	}
	Comanda operator+(int val)
	{
		this->valoare += val;
		return *this;
	}
	Comanda& operator++()
	{
		this->durataPregatire++;
		return *this;
	}
	Comanda operator++(int)
	{
		Comanda rez = *this;
		this->durataPregatire++;
		return rez;
	}
	explicit operator int()
	{
		return this->valoare;
	}
	bool operator!()
	{
		if (this->durataPregatire == 0)
			return true;
		return false;
	}
	bool operator<(const Comanda& co)
	{
		return this->durataPregatire < co.durataPregatire;
	}
	int total()
	{
		int t = 0;
		t = this->valoare + Comanda::taxalivrare;
		return t;
	}
	bool operator==(const Comanda& co)
	{
		if (this->valoare != co.valoare)
			return false;
		return true;
	}
	void scaderedurata(int s)
	{
		if (this->durataPregatire - s > 0)
			this->durataPregatire = this->durataPregatire - s;
	}

};
int Comanda::taxalivrare = 15;
class Furnizor :public Fisier
{
private:
	char* nume = NULL;
	string adresa = "N/A";
	int perioadaContract = 0; //perioada de timp exprimata in luni de zile 
	float valoriTransport[3]; // valoarea ultimelor 3 transporturi


public:
	void scriereInFisier(fstream& f)
	{
		int lg = strlen(this->nume) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->nume, lg * sizeof(char));

		int lg2 = this->adresa.length() + 1;
		f.write((char*)&lg2, sizeof(int));
		f.write(this->adresa.data(), lg2 * sizeof(char));

		f.write((char*)&this->perioadaContract, sizeof(int));
		for (int i = 0; i < 3; i++)
			f.write((char*)&this->valoriTransport[i], sizeof(float));
	}
	void citireDinFisier(fstream& f)
	{
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* bufferNume = new char[lg];
		f.read(bufferNume, lg);
		delete[]this->nume;
		this->nume = new char[strlen(bufferNume) + 1];
		strcpy(this->nume, bufferNume);
		delete[] bufferNume;

		int lg1;
		f.read((char*)&lg1, sizeof(int));
		char* bufferAdresa = new char[lg1];
		f.read(bufferAdresa, lg1);
		this->adresa = bufferAdresa;
		delete[]bufferAdresa;

		f.read((char*)&this->perioadaContract, sizeof(int));

		for (int i = 0; i < 3; i++)
			f.read((char*)&this->valoriTransport[i], sizeof(float));
	}
	Furnizor()
	{
		for (int i = 0; i < 3; i++)
			valoriTransport[i] = 0;
	}
	Furnizor(const char* nume, string adresa, int perioadaContract, float valoriTransport[3])
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->adresa = adresa;
		if (perioadaContract >= 0)
			this->perioadaContract = perioadaContract;
		for (int i = 0; i < 3; i++)
			this->valoriTransport[i] = valoriTransport[i];

	}
	Furnizor(const char* nume, int perioadaContract)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		if (perioadaContract >= 0)
			this->perioadaContract = perioadaContract;
	}
	Furnizor(const Furnizor& f)
	{
		this->nume = new char[strlen(f.nume) + 1];
		strcpy(this->nume, f.nume);
		this->adresa = f.adresa;
		if (f.perioadaContract >= 0)
			this->perioadaContract = f.perioadaContract;
		for (int i = 0; i < 3; i++)
			this->valoriTransport[i] = f.valoriTransport[i];

	}
	~Furnizor()
	{
		delete[]this->nume;
	}
	Furnizor& operator=(const Furnizor& f)
	{
		if (this != &f)
		{
			delete[]this->nume;

			this->nume = new char[strlen(f.nume) + 1];
			strcpy(this->nume, f.nume);
			this->adresa = f.adresa;
			if (f.perioadaContract >= 0)
				this->perioadaContract = f.perioadaContract;
			for (int i = 0; i < 3; i++)
				this->valoriTransport[i] = f.valoriTransport[i];
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Furnizor& f)
	{
		out << "-------------------FURNIZOR------------------" << endl;
		out << "Nume: " << f.nume << endl;
		out << "Adresa: " << f.adresa << endl;
		out << "Perioada contract: " << f.perioadaContract << " luni" << endl;
		for (int i = 0; i < 3; i++)
		{
			out << "Valoarea transportului [" << i << "] = " << f.valoriTransport[i] << endl;
		}
		out << "\n---------------------------------------------";

		return out;
	}
	friend istream& operator>>(istream& in, Furnizor& fu)
	{
		delete[] fu.nume;

		cout << "Introduceti numele furnizorului: ";
		char aux[20];
		in >> aux;
		fu.nume = new char[strlen(aux) + 1];
		strcpy(fu.nume, aux);
		cout << "Introduceti adresa furnizorului: ";
		in >> fu.adresa;
		cout << "Introduceti perioada contractuala: ";
		in >> fu.perioadaContract;
		for (int i = 0; i < 3; i++)
		{
			cout << "Introduceti valoarea transportului [" << i << "] =";
			in >> fu.valoriTransport[i];
		}

		return in;

	}

	char* getnume()
	{
		return this->nume;
	}
	void setnume(const char* nume)
	{
		if (strlen(nume) > 3)
		{
			delete[]this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}
	string getadresa()
	{
		return this->adresa;
	}
	void setadresa(string adresa)
	{
		if (adresa.length() > 10)
			this->adresa = adresa;
	}
	int getperioadaContract()
	{
		return this->perioadaContract;
	}
	void setperioadaContract(int perioadaContract)
	{
		if (perioadaContract >= 0)
		{
			this->perioadaContract = perioadaContract;
		}
	}
	float* getvaloriTransport()
	{
		return this->valoriTransport;
	}
	void setvaloriTransport(const float valoriT[], int lungime)
	{
		if (lungime == 3)
			for (int i = 0; i < 3; i++)
				if (valoriT[i] > 0)
					this->valoriTransport[i] = valoriT[i];

	}

	float medie()
	{
		float suma = 0;
		float medie = 0;
		int contor = 0;
		for (int i = 0; i < 3; i++)
		{
			if (this->valoriTransport[i] > 0)
			{
				suma += valoriTransport[i];
				contor++;
			}
		}
		medie = suma / contor;
		return medie;
	}
	void crestePerioada(int d)
	{
		this->perioadaContract = this->perioadaContract + d;
	}
	Furnizor operator+(int taxaLivrareRapida)
	{
		for (int i = 0; i < 3; i++)
			this->valoriTransport[i] += taxaLivrareRapida;
		return *this;
	}

	float operator[](int index)
	{
		if (index > 0 && index < 3)
			return this->valoriTransport[index];
	}

	Furnizor& operator++()
	{
		this->perioadaContract++;
		return *this;
	}
	Furnizor operator++(int)
	{
		Furnizor rez = *this;
		this->perioadaContract++;
		return rez;
	}

	explicit operator int()
	{
		return this->perioadaContract;
	}
	bool operator!()
	{
		if (this->perioadaContract == 0) {
			return true;
		}
		return false;
	}
	bool operator>=(const Furnizor& f)
	{
		float total = 0;
		float total1 = 0;
		for (int i = 0; i < 3; i++)
		{
			total = total + this->valoriTransport[i];
		}
		for (int i = 0; i < 3; i++)
		{
			total1 = total + f.valoriTransport[i];
		}
		return total >= total1;
	}
	bool operator==(const Furnizor& f)
	{
		if (this->adresa != f.adresa)
			return false;
		return true;
	}

};

//CLASELE DERIVATE 
class ClientFidel :public Client
{
private:
	int reducere = 0;  //valoarea este exprimata in procente

public:
	ClientFidel()
	{

	}
	ClientFidel(int id, const char* numeC, const char* nrTelefon, string adresa, int creditDisponibil, float valoriComenzi[], int reducere) :Client(id, numeC, nrTelefon, adresa, creditDisponibil, valoriComenzi)
	{
		if (reducere > 0)
			this->reducere = reducere;
	}
	ClientFidel(const ClientFidel& cf) :Client(cf)
	{
		this->reducere = cf.reducere;
	}
	ClientFidel& operator=(const ClientFidel& cf)
	{
		Client::operator=(cf);
		this->reducere = cf.reducere;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const ClientFidel& cf)
	{
		out << (Client)cf;
		out << "\nReducerea este: " << cf.reducere << endl;
		return out;
	}
	float reducereAplicata()
	{
		return (5* Client::getcreditDisponibil())/100 + this->reducere;
	}
};
class LichidareStoc :public Produs
{
private:
	int perioada = 0;// exprimata in zile
public:
	LichidareStoc()
	{

	}
	LichidareStoc(int cod_inregistrare, string denumire, const char* descriere, float pret, int stoc, int bucatiVandute[4], int perioada) :Produs(cod_inregistrare, denumire, descriere, pret, stoc, bucatiVandute)
	{
		if (perioada > 0)
			this->perioada = perioada;
	}
	LichidareStoc(const LichidareStoc& l):Produs(l)
	{
		this->perioada = l.perioada;
	}
	LichidareStoc& operator=(const LichidareStoc& l)
	{
		Produs::operator=(l);
		this->perioada = l.perioada;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const LichidareStoc& l)
	{
		out << (Produs)l;
		out << "\nPerioada este: " << l.perioada<<endl;
		return out;
	}
	float recalcularePret()
	{
		if (this->perioada < 2)
			return (Produs::recalcularePret()-Produs::recalcularePret() * 50/100);
		else
			return (Produs::recalcularePret()-Produs::recalcularePret() * 30/100);
	}
};
class AngajatPartTime :public Angajat
{
private:
	int plataOra = 0;
public:
	AngajatPartTime()
	{

	}
	AngajatPartTime(int idAngajat, const char* nume, string functie, float salariu, int vechime, int oreLucrate[], int plataOra) :Angajat(idAngajat, nume, functie, salariu, vechime, oreLucrate)
	{
		this->plataOra = plataOra;
	}
	AngajatPartTime(const AngajatPartTime& ap):Angajat(ap)
	{
		this->plataOra = ap.plataOra;
	}
	AngajatPartTime& operator=(const AngajatPartTime& ap)
	{
		this->Angajat::operator=(ap);
		this->plataOra = ap.plataOra;
		return*this;
	}
	friend ostream& operator<<(ostream& out, const AngajatPartTime& ap)
	{
		out << (Angajat)ap;
		out << "\nPlata pe ora este de: " << ap.plataOra << " lei"<<endl;
		return out;
	}
	string incadrare()
	{
		string tip = "Part-time";
		return tip;
	}

};
class AngajatFullTime :public Angajat
{
private:
	int oreSupl = 0;
public:
	AngajatFullTime()
	{
		
	}
	AngajatFullTime(int idAngajat, const char* nume, string functie, float salariu, int vechime, int oreLucrate[],int oreSupl) :Angajat(idAngajat, nume, functie, salariu, vechime, oreLucrate)
	{
		this->oreSupl = oreSupl;
	}
	AngajatFullTime(const AngajatFullTime& af) :Angajat(af)
	{
		this->oreSupl = af.oreSupl;
	}
	AngajatFullTime& operator=(const AngajatFullTime& af)
	{
		this->Angajat::operator=(af);
		this->oreSupl = af.oreSupl;
		return*this;
	}
	friend ostream& operator<<(ostream& out, const AngajatFullTime& af)
	{
		out << (Angajat)af;
		out << "\nNumarul de ore suplimentare al angajatului este: " << af.oreSupl << endl;
		return out;
	}
	string incadrare()
	{
		string tip = "Full-time";
		return tip;
	}
	
};

//CLASA DE TIP COLECTIE
class ColectivAngajati
{
private:
	int nr_Angajati=0;
	Angajat** angajati=NULL;
public:
	ColectivAngajati()
	{

	}
	ColectivAngajati(int nr_Angajati, Angajat** angajati)
	{
		this->nr_Angajati = nr_Angajati;
		this->angajati = new Angajat*[this->nr_Angajati];
		for (int i = 0; i < this->nr_Angajati; i++)
			this->angajati[i] = angajati[i];
	}
	void tipincadrare()
	{
		for (int i = 0; i < this->nr_Angajati; i++)
			cout << "Angajatul "<<angajati[i]->getnume() <<" lucreaza " << angajati[i]->incadrare() << endl;
	}
};


int main(int argc, char* argv[])
{
	//TESTARE PENTRU CLASA ANGAJAT
	/*int oreLucrate[6] = {120,120,135,130,125,145};
	Angajat a1(1, "Andrei", "Casier", 2600, 12, oreLucrate); // constructor cu toti parametrii
	//testare operator <<"
	//cout << a1;
	cout << "\n\n";
	//constr copiere
	Angajat a2(a1);
	cout << a2;
	cout << "\n\n";
	// testare operator egal
	int oreLucrate2[6] = { 123,120,124,126,130,116 };
	Angajat a3(3, "Razvan", "Operator marfa", 2750, 18, oreLucrate2);
	a2 = a3;
	cout << a2;
	cout << "\n\n";
	//testare operator>>
	Angajat a;
	//  cin >> a;
	// cout << a;

	 //get si set
	cout << "Id: " << a1.getidAngajat() << endl;
	cout << "Nume: " << a1.getnume() << endl;
	cout << "Functie: " << a1.getfunctie() << endl;
	cout << "Salariu: " << a1.getsalariu() << endl;
	cout << "Vechime: " << a1.getvechime() << endl;
	cout << "Repartitia orelor lucrate pe luni este:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << "Luna[" << i << "]=" << a1.getoreLucrate()[i] << " ";
	}
	cout << "\n";

	a1.setnume("Marius");
	a1.setfunctie("Lucrator comercial");
	a1.setsalariu(2900);
	a1.setvechime(14);
	int ore[] = { 142,135,137,150,134,139 };
	a1.setoreLucrate(ore, 6);
	cout << a1;
	//testare metoda prelucrare salariu
	a3.cresteSalariu(350);
	cout << "\n";
	cout << a3;
	// testare metoda medieOreLucrate
	cout << "\nMedia nr de ore lucrate este de: " << a3.medieOreLucrate() << " ore";

	// testare operator []
	int orelucrate = a1[2];
	cout << "\n\nNr ore lucrate in respectiva luna: " << orelucrate << endl;

	//testare operator +
	int oreLucrate4[6] = { 130,128,125,125,127,135 };
	Angajat a4(4, "Mihai", "Manipulator marfa", 3000, 15, oreLucrate4);
	a4 + 6; // creste nr de ore lucrate din fiecare luna cu inca 6 ce au fost suplimentare
	cout << a4 << "\n";

	//testare postincrementare
	a3 = a1++;
	cout << a3;
	cout << "\n";
	cout << a1;
	cout << "\n";
	// testare preincrementare
	a3 = ++a1;
	cout << a3;
	cout << "\n";
	cout << a1;

	// testare operator !
	cout << "\n";
	Angajat a7(7, "Eusebiu", "Descarcare marfa", 3430);
	if (!a7)
		cout << "Salariatul este angajat de mai putin de o luna";

	// testare operator >=
	cout << "\n\n";
	Angajat a5(5, "Alin", "Lucrator comercial", 3600);
	Angajat a6(6, "Andrei", "Lucrator comercial", 3200);
	if (a6 >= a5)
		cout << "Andrei are salariul mai mare decat Alin";
	else cout << "Alin are salariul mai mare decat Andrei";

	// testare operator cast explicit
	cout << "\n";
	int total = int(a3);
	cout << "\nAngajatul are un total de: " << total << " ore lucrate" << endl;
	// testare operator ==
	Angajat a8(8, "Laurentiu", "Manipulator marfa", 3000);
	cout << "\n";
	if (a8 == a4)
		cout << " Laurentiu si Mihai au acelasi salariu";
	cout << "\n";*/
	//TESTARE PENTRU CLASA CLIENT
	/*float valoriComenzi[3] = {120,240,100};
	Client c1(100, "Stefan", "0752420635", "Bd.Iuliu Maniu, nr.5", 550, valoriComenzi);
	Client c4(104, "Marius", "0783487354", "Soseaua Iancului nr 12");
	// testare operator <<
	cout << c1;
	cout << "\n";
	//testare constructor de copiere
	Client c2(c1);
	cout << c2;
	cout << "\n";
	//testare operator =
	float valoriComenzi2[3] = { 250,220,330 };
	Client c3(101, "Claudiu", "0732345890", "Str.Baicului nr.1, Sc.B, Ap.12", 300, valoriComenzi2);
	Client c;
	c = c3;
	cout << c;
	cout << "\n";

	// testare get si set
	cout << "Id: " << c1.getid() << endl;
	cout << "Nume: " << c1.getnumeC() << endl;
	cout << "Nr telefon " << c1.getnrTelefon() << endl;
	cout << "Adresa: " << c1.getadresa() << endl;
	cout << "Credit: " << c1.getcreditDisponibil() << endl;
	cout << "Valori comenzi: " << endl;
	for (int i = 0; i < 3; i++)
		cout << "Comanda [" << i << "]= " << c1.getvaloriComenzi()[i] << "lei" << " ";
	cout << "\n";

	c1.setnumeC("Adrian");
	c1.setnrTelefon("0783234323");
	c1.setadresa("Bd.Camil Ressu nr.120");
	c1.setcreditDisponibil(600);
	float valori[3] = { 270,350,400 };
	c1.setvaloriComenzi(valori, 3);
	cout << c1;

	//testare >> si afisarea clientului introdus de la tastatura
	//cin >> c;
	//cout << c;

	//testare operator []
	cout << "Valoarea ultimei comenzi este de: " << c1[2] << " lei" << endl;
	//testare operator -
	c1 - 200;
	cout << c1;
	cout << "\n";
	//testare operator -- pre
	c3 = --c2;
	cout << c3;
	cout << "\n";
	cout << c2;
	cout << "\n\n";
	//testare operator -- post
	c3 = c2--;

	cout << c3;
	cout << "\n";
	cout << c2;
	cout << "\n";

	//testare operator <
	if (c1 < c3)
		cout << c1.getnumeC() << " are suma comenzilor anterioare mai mica decat " << c3.getnumeC();
	else
		cout << c3.getnumeC() << " are suma comenzilor anterioare  mai mica decat " << c1.getnumeC();
	//testare operator !
	cout << "\n";
	if (!c1)
		cout << "Clientul nu are credit disponibil pt achizitii" << endl;
	//testare operator cast
	string adr = (string)c1;
	cout << "Adresa este: " << string(c1) << endl;
	// testare operator ==
	cout << "\n";
	if (c1 == c3)
		cout << "Cei 2 clienti au acelasi nume";
	else
		cout << "Cei 2 clienti au nume diferite";
	//testare metoda adaugacodPostal
	cout << "\n";
	try {
		c1.adaugacodPostal("60036"); // va adauga la finalul adresei clientului
		cout << c1;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	cout << "\n";
	//testare metoda maresteCredit
	cout << c3.getcreditDisponibil() << " lei" << endl;
	c3.maresteCredit(336);
	cout << c3.getcreditDisponibil() << " lei" << endl;
	cout << "\n\n";*/	
	//TESTARE PENTRU CLASA PRODUS
	/*int bucatiVandute[4] = {73,102,85,64};
	Produs p1(8821, "Vaza metalica", "Alb, 35x17x17cm", 179, 40, bucatiVandute);
	cout << p1;
	//cin >> p1;
	//cout << p1;

	// testare get si set
	cout << "\n";
	cout << "Cod: " << p1.getcod_inregistrare() << " ";
	cout << "Denumire: " << p1.getdenumire() << " ";
	cout << "Descriere: " << p1.getdescriere() << " ";
	cout << "Pret: " << p1.getpret() << " ";
	cout << "Stoc: " << p1.getstoc() << endl;
	cout << "Valori vanzari pe trimestre: ";
	for (int i = 0; i < 4; i++)
		cout << p1.getbucatiVandute()[i] << " ";

	p1.setdenumire("Vaza de sticla");
	p1.setdescriere("Negru, 35x17x17cm");
	p1.setpret(199);
	p1.setstoc(45);
	int bucati[4] = { 70,100,75,60 };
	p1.setbucatiVandute(bucati, 4);
	cout << "\n" << p1;

	//testare constr de copiere
	cout << "\n";
	Produs p(p1);
	cout << p << "\n";

	// testare operator egal
	int bucati2[4] = { 113,124,86,97 };
	Produs p2(5643, "Suport lumanare", "Sticla, 9x8cm", 39, 60, bucati2);
	p = p2;
	cout << p;
	// testare metoda calcul total
	cout << "\n";
	cout << "S-a inregistrat un venit total de: " << p2.calculTotal() << " lei de pe urma vanzarii produsului" << endl;
	// testare metoda unitatiVandute
	cout << "Numarul total de bucati vandute in a doua jumatate a anului este: " << p2.unitatiVandute() << endl;
	//testare operator index
	cout << "S-a inregistrat o vanzare de 86 unitati in trimestrul " << p2[86] << endl;
	// testare operator+
	p = p1 + 25;
	cout << p1;
	cout << "\n";
	cout << p;
	cout << "\n";
	// testare ++ pre
	Produs p3;
	p3 = ++p1;
	cout << p3;
	cout << "\n";
	cout << p1;
	cout << "\n";
	//testare ++ post
	p3 = p1++;
	cout << p3;
	cout << "\n";
	cout << p1;
	// testare operator !
	if (!p1)
		cout << "\nStocul disponibil este 0";
	else cout << "\nExista cel putin un produs pe stoc";
	//testare operator >
	cout << "\n";
	if (p1 > p2)
		cout << "P1 este mai scump decat p2";
	else cout << "p2 este mai scump decat p1";
	// testare operator ==
	int bucati3[] = { 54,43,60,37 };
	Produs p4(8830, "Vaza de sticla", "Rosu,30x10x12cm", 330, 34, bucati3);
	if (p1 == p4)
		cout << "\nProdusele au aceeasi denumire";
	// testare operator cast
	cout << "\nPretul produsului este: " << (float)p4;*/	
	//TESTARE PENTRU CLASA COMANDA
	/*Comanda co1("BC100230", c2, 155, 2);
	Comanda co3("SJ435632", 350);
	//cin >> co1;
	cout << co1;
	cout << "\n\n";

	//testare get si set
	cout << "\n";
	cout << "Awb: " << co1.getawb() << endl;
	cout << co1.getclient();
	cout << "Valoare: " << co1.getvaloare() << " lei" << endl;
	cout << "Durata:" << co1.getdurataPregatire() << " zile" << endl;
	cout << "Taxa livrare: " << co1.gettaxaLivrare() << " lei" << endl;

	co1.setawb("CJ783124");
	co1.setclient(c3);
	co1.setvaloare(225);
	co1.setdurata(1);
	cout << co1;
	try {
		co1.settaxaLivrare(25);
		cout << "\nNoua taxa de livrare este de " << co1.gettaxaLivrare() << " lei" << endl;
	}
	catch (exception* ex)
	{
		cout << endl << ex->what();
		delete ex;
	}
	//TESTARE CONSTR DE COPIERE";
	Comanda co(co1);
	cout << co << "\n\n";
	// TESTARE OPERATOR="
	Comanda co2;
	co2 = co1;
	cout << co2 << "\n";
	//testare operator+
	cout << co2.getvaloare() << " lei" << endl;
	co2 + 150;
	cout << co2.getvaloare() << " lei" << endl;
	//testare operator cast
	cout << "Valoarea comenzii este: " << (int)co1 << " lei" << endl;
	//testare operator!
	if (!co1)
		cout << "Comanda nu necesita timp pentru pregatire" << endl;
	else
		cout << "Comanda necesita " << co1.getdurataPregatire() << " Zile" << endl;
	//testare operator <
	float valoriComenzi15[3] = { 356,420,299 };
	Client c15(15, "Andreea", "0755909003", "Str.Venus nr.14 sc.b, ap.1", 785, valoriComenzi15);
	Comanda co4("TM456789", c15, 400, 3);
	if (co1 < co4)
		cout << "Comanda co1 are durata de pregatire mai mica decat comanda co4" << endl;
	else cout << "Comanda co4 are durata de pregatire mai mica decat comanda co1" << endl;
	//testare operator==
	if (co1 == co4)
		cout << "Co1 si co4 au aceeasi valoare a comenzii" << endl;
	else
		cout << "Co1 si co4 au comenzi de valori diferite" << endl;
	//testare operator ++ pre
	co4 = ++co1;
	cout << co4;
	cout << "\n";
	cout << co1;
	//testare operator++ post
	co4 = co1++;
	cout << co4;
	cout << "\n";
	cout << co1;
	//testare metoda total
	cout << "\nTotalul comenzii co4 este de: " << co4.total() << " lei" << endl;
	// testare metoda
	co4.scaderedurata(1);
	cout << co4.getdurataPregatire();*/	
	//TESTARE PENTRU CLASA FURNIZOR
	/*float valoriTransport[3] = {1300,1500,1320};;
	Furnizor f1("Impex SRL", "Bd.Chisinau nr.13", 10, valoriTransport);
	float valoriTransport3[3] = { 1250,1700,1816 };
	Furnizor f3("Lems SRL", "Str.Dobrogei nr.324", 17, valoriTransport3);

	//cin >> f1;
	cout << f1 << endl;

	//testare constr de copiere
	Furnizor f(f1);
	cout << f << endl;
	//testare operator egal
	Furnizor f2;
	f2 = f;
	cout << f2 << endl;
	//testare get si set
	cout << f1.getnume() << " /" << f1.getadresa() << " /" << f1.getperioadaContract() << " luni" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << f1.getvaloriTransport()[i] << " ";
	}
	float valorimodif[3] = { 3200,1750,2500 };
	f1.setnume("Subif SRL");
	f1.setadresa("Bd.Iuliu Maniu nr.35B");
	f1.setperioadaContract(23);
	f1.setvaloriTransport(valorimodif, 3);
	cout << "\n";
	cout << f1;

	// testare metode
	cout << "\n";
	cout << "Valoarea medie a transporturilor realizate de furnizor este: " << f1.medie() << " lei" << endl;
	f1.crestePerioada(6);
	cout << f1.getperioadaContract() << " luni" << endl;
	// testare operator []
	cout << "\n";
	cout << "Ultimul transport al furnizorului a avut valoarea de : " << f1[2] << " lei" << endl;
	cout << "\n";

	//testare operator+
	cout << f1;
	f1 + 35;
	cout << "\n";
	cout << f1;
	// testare operator ++ preincrementare
	cout << "\n";
	f1 = ++f3;
	cout << f1.getperioadaContract() << endl;
	cout << f3.getperioadaContract() << endl;
	//testare operator ++ postincrementare
	cout << "\n";
	f1 = f3++;
	cout << f1.getperioadaContract() << endl;
	cout << f3.getperioadaContract() << endl;
	// testare operator cast
	int perioada = (int)f1;
	cout << "Perioada contractuala este de: " << (int)f1 << " luni" << endl;
	//testare operator !
	Furnizor f4("Depot Brico", 0);
	if (!f4)
		cout << "Inca nu exista un contract de asociere cu firma Depot Brico" << endl;;
	// testare operator >
	float valoriTransport5[3] = { 1300,1650,1900 };
	Furnizor f5("Vasion", "Strada Nicolae Balcescu nr 14", 15, valoriTransport5);
	if (f1 >= f5)
		cout << "f1 are totalul celor 3 transporturi mai mare sau egal decat totalul lui f5" << endl;
	else
		cout << "f5 are totalul celor 3 transporturi mai mare sau egal decat totalul lui f1" << endl;
	// testare operator ==
	if (f1 == f5)
		cout << "Furnizorii f1 si f5 au aceeasi adresa" << endl;
	else cout << "Furnizorii f1 si f5 nu au aceeasi adresa" << endl;*/
     //CREARE FISIERE BINARE
	/*fstream fout1("angajat.dat", ios::out | ios::binary);
	int oreLucratef[6] = { 120,128,135,130,122,140 };
	Angajat f(1, "Dragos", "Casier", 2400, 8, oreLucratef);
	f.scriereInFisier(fout1);
	fout1.close();

	fstream fout2("client.dat", ios::out | ios::binary);
	float valoriComenzif[3] = { 250,228,370 };
	Client cf(500, "Marius", "0735643224", "Str.Mihai Viteazu nr.14 sc.D, ap.23", 340, valoriComenzif);
	cf.scriereInFisier(fout2);
	fout2.close();

	fstream fout3("produs.dat", ios::out | ios::binary);
	int bucatiVandutef[4] = { 65,103,89,63 };
	Produs pf(8829, "Ornament floral", "Alb, 35x17x17cm", 199, 43, bucatiVandutef);
	pf.scriereInFisier(fout3);
	fout3.close();

	float valoriTransportf[3] = { 1300,1900,2400 };
	Furnizor ff("Confert SRL", "Bd.Chisinau nr.98, intrarea A", 13, valoriTransportf);
	fstream fout("Furnizor.dat", ios::out | ios::binary);
	ff.scriereInFisier(fout);
	fout.close();*/	
	//CREARE FISIERE TXT
	/*ofstream g("Angajat.txt");
	int oreLucrateTxt[6] = { 120,120,135,120,133,145 };
	Angajat atxt(85, "Dumitru", "Agent Vanzari", 3600, 7, oreLucrateTxt);
	g << atxt;
	g.close();

	ofstream h("Client.txt");
	float valoriComenziTxt[3] = { 250,433,378 };
	Client ctxt(535, "Radu", "07356324224", "Str.Ion Ghica nr.13 sc.A, ap.87", 300, valoriComenziTxt);
	h << ctxt;
	h.close();

	ofstream i("Produs.txt");
	int bucatiVanduteTxt[4] = { 65,123,75,63 };
	Produs ptxt(8829, "Ornament Pisica", "Negru, 35x12x17cm", 145, 32, bucatiVanduteTxt);
	i << ptxt;
	i.close();
	
	ofstream l("Comanda.txt");
	Comanda cotxt("IS43231", ctxt, 452, 3);
	l << cotxt;
	l.close();

	ofstream j("Furnizor.txt");
	float valoriTransportTXT[] = {2200,2500,1750};
	Furnizor ftxt("Adeplast SRL", "Str.Vadul Bistritei nr.141", 35, valoriTransportTXT);
	j << ftxt;
	j.close();*/

	// nu s-a introdus niciun fisier txt ca input, atunci se vizualizeaza datele din fisierele salvate la locatiile cunoscute de programator
	if (argc < 2)     // nu s-a introdus niciun fisier txt ca input, atunci se vizualizeaza fisiere salvate la locatiile cunoscute de programator
	{
		fstream fin1("angajat.dat", ios::in | ios::binary);
		Angajat anou;
		anou.citireDinFisier(fin1);
		cout << anou;

		fstream fin2("client.dat", ios::in | ios::binary);
		Client cnou;
		cnou.citireDinFisier(fin2);
		cout << cnou;
		cout << "\n";

		fstream fin3("produs.dat", ios::in | ios::binary);
		Produs pnou;
		pnou.citireDinFisier(fin3);
		cout << pnou;
		cout << "\n";

		fstream fin("Furnizor.dat", ios::in | ios::binary);
		Furnizor fnou;
		fnou.citireDinFisier(fin);
		cout << fnou;
		cout << "\n";

	}
	
	//citire date din fisier txt introdus prin argumentele functiei main
	for (int i = 0; i < argc; i++)
	{
		string numefisier = argv[i];
		cout << numefisier;
		fstream f(numefisier);
		string line = "";
		while (getline(f, line))
		{
			cout << line << '\n';
		}
		cout << "\n";
	}

	//TESTARE METODA VIRTUALA DIN CLASA DERIVATA ClientFidel
	/*cout << "\n";
	float valoriV[3] = { 260,300,500 };
	Client v(567, "Marinescu Andrei", "0723564432", "Str.Oltetului nr.30", 420, valoriV);
	ClientFidel cf1(568, "Damian Iulian", "0744564730", "Str.Garii nr.87", 400, valoriV, 15);
	cout <<"\nTestare metoda virtuala reducereAplicata"<<endl;
	cout <<"Reducerea standard va fi de "<< v.reducereAplicata()<<" lei" << endl;
	cout << "Reducerea pt client fidel va fi de " << cf1.reducereAplicata() << " lei" << endl;
	*/
	//TESTARE METODA VIRTUALA DIN CLASA DERIVATA LichidareStoc
	/*cout << "\n";
	int bucatiVanduteV[] = { 60,24,123,88 };
	Produs pv(452, "Lampa", "Albastru cu bec led", 100, 5, bucatiVanduteV);
	LichidareStoc lv(452, "Lampa", "Albastru cu bec led", 100, 5, bucatiVanduteV, 3);
	cout << "\nTestare metoda virtuala RecalcularePret"<<endl;
	cout <<"Dupa o reducere initiala de 10%, pretul produsului va fi de " <<pv.recalcularePret() <<" lei" << endl;
	cout <<"Pretul final al produsului in perioada de lichiditate va fi de: "<<lv.recalcularePret()<<" lei" << endl;
	*/
	//VECTOR DE POINTERI
	/*Angajat** vector = new Angajat * [2];
	int oreAPT[] = { 80,100,76,75,80,82 };
	vector[0] = new AngajatPartTime(1000, "Remus", "Casier", 1600, 7, oreAPT, 20);
	int oreAFT[] = { 150,145,150,134,138,143 };
	vector[1] = new AngajatFullTime(1001, "Adrian", "Sef magazin", 4300, 6, oreAFT, 14);
	ColectivAngajati ca(2, vector);
	ca.tipincadrare();
	*/
	//TESTARE METODE PURE DIN CLASA ABSTRACTA CAS
	/*Angajat cas (831, "Dejan", "Reprezentant media", 4500);
	cout << "Suma platita de angajator pentru asigurarile sociale este de: " << cas.calculCAS() << " lei"<<endl;
	cout << "Suma platita de angajator pentru asigurarile sociale de sanatate este de: " << cas.calculCASS() << " lei"<<endl;*/

	//TESTARE STL
	int oreL[] = { 127,130,127,145,150,138 };
	Angajat s1(503, "Matei", "Casier", 3200, 11, oreL);
	Angajat s2(504, "Ionut", "Casier", 3300, 8, oreL);
	Angajat s3(505, "Narcis", "Manipulator marfa", 2850, 12, oreL);
	//MAP
	/*cout << "\n------STL MAP--------\n";
	map<int, Angajat> mapAn;
	mapAn[0] = s1;
	mapAn[6] = s2;
	mapAn[3] = s3;
	map<int, Angajat>::iterator itMap;
	for (itMap = mapAn.begin(); itMap != mapAn.end(); itMap++)
	{
		cout << endl << itMap->first << " " << itMap->second;
	}*/
	//SET
	/*cout << "\n------STL SET--------\n";
	set<string> setString;
	setString.insert(s1.getnume());
	setString.insert(s2.getnume());
	setString.insert(s3.getnume());
	set<string>::iterator itSet;
	for (itSet = setString.begin(); itSet != setString.end(); itSet++)
	{
		cout << *itSet << " ";
	}*/
	//LIST
	/*cout << "\n------STL LIST--------\n";
	list<int> lint;
	lint.push_back(s1.getoreLucrate()[0]);
	lint.push_back(s1.getoreLucrate()[1]);
	lint.push_back(s1.getoreLucrate()[2]);
	lint.push_front(s1.getoreLucrate()[3]);
	lint.push_front(s1.getoreLucrate()[4]);
	lint.push_front(s1.getoreLucrate()[5]);
	list<int >::iterator itList;
	for (itList = lint.begin(); itList != lint.end(); itList++)
		cout << *itList << " ";*/
	//VECTOR
	/*cout << "\n------STL VECTOR--------\n";
	vector<float> vS;
	vS.push_back(s1.getsalariu());
	vS.push_back(s2.getsalariu());
	vS.push_back(s3.getsalariu());
	vector<float>::iterator it;
	cout << endl;
	for (it = vS.begin(); it != vS.end(); it++)
		cout << *it << " ";*/
	
	return 0;
}




#include <iostream>
#include "asema.h"
#include "nappula.h"
#include "ruutu.h"
#include <algorithm>
using namespace std;

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_lauta[i][j] = NULL;
	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	_lauta[5][0] = vl;
	_lauta[6][0] = vr;
	_lauta[7][0] = vt;

	_lauta[0][1] = vs;
	_lauta[1][1] = vs;
	_lauta[2][1] = vs;
	_lauta[3][1] = vs;
	_lauta[4][1] = vs;
	_lauta[5][1] = vs;
	_lauta[6][1] = vs;
	_lauta[7][1] = vs;

	_lauta[0][7] = mt;
	_lauta[1][7] = mr;
	_lauta[2][7] = ml;
	_lauta[3][7] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;

	_lauta[0][6] = ms;
	_lauta[1][6] = ms;
	_lauta[2][6] = ms;
	_lauta[3][6] = ms;
	_lauta[4][6] = ms;
	_lauta[5][6] = ms;
	_lauta[6][6] = ms;
	_lauta[7][6] = ms;
	// Kunkun testausta varten
	/*_lauta[7][5] = vk; 
	_lauta[5][5] = mt;
	_lauta[4][3] = ml;
	_lauta[3][3] = vs;*/

	//_lauta[4][4] = vr;

	_siirtovuoro = 0;
	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;

}


void Asema::paivitaAsema(Siirto *siirto)
{

	// Kaksoisaskel-lippu on oletusarvoisesti pois p‰‰lt‰.
	// Asetetaan myˆhemmin, jos tarvii.
	this->kaksoisaskelSarakkeella = -1;

	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna()) {
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[6][0] = vk; // kuningas uudelle paikalle
			_lauta[7][0] = NULL; // tornin paikalle tyhj‰
			_lauta[5][0] = vt; // torni uudella paikalle
		}
		if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[6][7] = mk; // kuningas uudelle paikalle
			_lauta[7][7] = NULL; // tornin paikalle tyhj‰
			_lauta[5][7] = mt; // torni uudella paikalle
		}
	}

	// onko pitk‰ linna
	else if (siirto->onkoPitk‰linna()) {
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[2][0] = vk; // kuningas uudelle paikalle
			_lauta[0][0] = NULL; // tornin paikalle tyhj‰
			_lauta[3][0] = vt; // torni uudella paikalle
		}
		if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[2][7] = mk; // kuningas uudelle paikalle
			_lauta[0][7] = NULL; // tornin paikalle tyhj‰
			_lauta[3][7] = mt; // torni uudella paikalle
		}

	}
	else {// Kaikki muut siirrot

		int alkuRiviInt;
		int alkuSarakeInt;
		int loppuRiviInt;
		int loppuSarakeInt;

		//Ottaa siirron alkuruudussa olleen nappulan talteen 
		alkuRiviInt = siirto->getAlkuruutu().getRivi();
		alkuSarakeInt = siirto->getAlkuruutu().getSarake();
		Nappula* nappula = _lauta[alkuSarakeInt][alkuRiviInt];

		//Laittaa talteen otetun nappulan uuteen ruutuun
		loppuRiviInt = siirto->getLoppuruutu().getRivi();
		loppuSarakeInt = siirto->getLoppuruutu().getSarake();

		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)
		if
		(
			(_lauta[alkuSarakeInt][alkuRiviInt]->getKoodi() == VS || _lauta[alkuSarakeInt][alkuRiviInt]->getKoodi() == MS) &&
			(alkuRiviInt - loppuRiviInt == 2 || alkuRiviInt - loppuRiviInt == -2)
		)
			kaksoisaskelSarakkeella = alkuSarakeInt;

		// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		if
		(
			(_lauta[alkuSarakeInt][alkuRiviInt]->getKoodi() == VS || _lauta[alkuSarakeInt][alkuRiviInt]->getKoodi() == MS) &&
			(alkuSarakeInt != loppuSarakeInt) &&
			(_lauta[loppuSarakeInt][loppuRiviInt] == NULL)
		)
			_lauta[loppuSarakeInt][alkuRiviInt] = NULL;

		//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		//if ((nappula->getKoodi() == VS || nappula->getKoodi() == MS) && (loppuRiviInt == 0 || loppuRiviInt == 7)) {
		//	_lauta[alkuSarakeInt][alkuRiviInt] = NULL;
		//}
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
		//else {
		_lauta[alkuSarakeInt][alkuRiviInt] = NULL;
		_lauta[loppuSarakeInt][loppuRiviInt] = nappula;
		if (siirto->_miksikorotetaan != NULL)
			_lauta[loppuSarakeInt][loppuRiviInt] = siirto->_miksikorotetaan;
//		}
		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		if (nappula->getKoodi() == VK) {
			_onkoValkeaKuningasLiikkunut = true;
		}
		if (nappula->getKoodi() == MK) {
			_onkoMustaKuningasLiikkunut = true;
		}
		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
		if (nappula->getKoodi() == VT && alkuSarakeInt == 7 && alkuRiviInt == 0) {
			_onkoValkeaKTliikkunut = true;
		}
		if (nappula->getKoodi() == VT && alkuSarakeInt == 0 && alkuRiviInt == 0) {
			_onkoValkeaDTliikkunut = true;
		}
		if (nappula->getKoodi() == MT && alkuSarakeInt == 7 && alkuRiviInt == 7) {
			_onkoMustaKTliikkunut = true;
		}
		if (nappula->getKoodi() == VT && alkuSarakeInt == 0 && alkuRiviInt == 7) {
			_onkoMustaDTliikkunut = true;
		}
	}
	//p‰ivitet‰‰n _siirtovuoro
	if (_siirtovuoro == 0)
		_siirtovuoro = 1;
	else
		_siirtovuoro = 0;
}
/*Nappula Asema::annaNappulaRuudusta(Ruutu *ruutu){
	int sarake = ruutu->getSarake();
	int rivi = ruutu->getRivi();
	return *_lauta[rivi][sarake];
}*/


int Asema::getSiirtovuoro() 
{
	return this->_siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	this->_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return this->_onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return this->_onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return this->_onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return this->_onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return this->_onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return this->_onkoMustaKTliikkunut;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	std::list<Siirto> vastustajaSiirrotLista;
	//V‰reitt‰in k‰yd‰‰n l‰pi kaikki ruudut ja niiss‰ olevan nappulan siirrot ker‰t‰‰n vastustajan siirtolistaan
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			if (this->_lauta[i][j]->getVari() == vastustajanVari)
				this->_lauta[i][j]->annaSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), this, vastustajanVari); // myˆh.sidonta
		}
	}
	// K‰yd‰‰n vastustajaSiirtoLista l‰pi ja jos sielt‰ lˆytyy tarkasteltava ruutu niin tiedet‰‰n sen olevan uhattu
	bool ruutuOk = true;
	for (auto s : vastustajaSiirrotLista)
	{
		if (ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi()) {
			ruutuOk = false;
			break;
		}
	}
	return ruutuOk;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	// poistaa listasta siirrot jotka viev‰t oman kuninkaan shakkiin
	// k‰yd‰‰n saatua siirtolistaa l‰pi ja jos siell‰ oleva siirto asettaa kuninkaan shakkiin, 
	// niin siirto poistetaan listasta
	int kuninkaanX;
	int kuninkaanY;
	if (vari == 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] == NULL)
					continue;
				if (this->_lauta[i][j]->getKoodi() == VK) {
					kuninkaanX = i;
					kuninkaanY = j;
					break;
				}
			}
		}
	}
	if (vari == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] == NULL)
					continue;
				if (this->_lauta[i][j]->getKoodi() == MK) {
					kuninkaanX = i;
					kuninkaanY = j;
					break;
				}
			}
		}
	}
	// Jotta ei jouduta perumaan oikeaan asemaan tehty‰ siirtoa
	Asema testiAsema;
	std::list<Siirto> siivottuSiirrotLista;
	for (auto s : lista) {
		testiAsema = *this;
		testiAsema.paivitaAsema(&s);
		int x, y;

		// Kuninkaan siirto?
		if (s.onkoLyhytLinna())
		{
			x = 6;
			if (this->getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else if (s.onkoPitk‰linna())
		{
			x = 2;
			if (this->getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else
		{
			Nappula* siirtyva = this->_lauta[s.getAlkuruutu().getSarake()][s.getAlkuruutu().getRivi()];
			if (siirtyva->getKoodi() == VK || siirtyva->getKoodi() == MK)
			{
				x = s.getLoppuruutu().getSarake();
				y = s.getLoppuruutu().getRivi();
			}
			else
			{
				// Ei ole, kuninkaan sijainti sama kuin ennen siirron s kokeilua
				x = kuninkaanX;
				y = kuninkaanY;
			}
		}

		// huom !vari
		if (testiAsema.onkoRuutuUhattu(&Ruutu(x, y), !vari) == true) {
			siivottuSiirrotLista.push_back(s);
		}
	}
	lista = siivottuSiirrotLista;
}


void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari)
{
	//// Linnoituksien huomioiminen
	//// 1. Kuningas ei saa olla liikkunut
	//// 2. Torni ei saa olla liikkunut
	//// 3. Kuningas ei saa olla shakattuna
	//// 4. Ruutujen pit‰‰ olla tyhj‰t
	//// 5. Ruudut eiv‰t saa olla uhattuja
	if (vari == 0) {
		//valkean lyhyt linna
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 0), !vari)
			&& this->onkoRuutuUhattu(&Ruutu(5, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(6, 0), !vari)
			&& this->_lauta[5][0] == NULL && this->_lauta[6][0] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(true, false)); // lis‰t‰‰n listaan lyhyt linna
		}
		//valkean pitk‰ linna
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 0), !vari)
			&& this->onkoRuutuUhattu(&Ruutu(3, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(3, 0), !vari)
			&& this->_lauta[3][0] == NULL && this->_lauta[2][0] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(false, true)); // lis‰t‰‰n listaan lyhyt linna
		}
	}
	if (vari == 1) {
		//mustan lyhyt linna
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 7), !vari)
			&& this->onkoRuutuUhattu(&Ruutu(5, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(6, 7), !vari)
			&& this->_lauta[5][7] == NULL && this->_lauta[6][7] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(true, false)); // lis‰t‰‰n listaan lyhyt linna
		}
		//mustan pitk‰ linna
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 7), !vari)
			&& this->onkoRuutuUhattu(&Ruutu(3, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(3, 7), !vari)
			&& this->_lauta[3][7] == NULL && this->_lauta[2][7] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(false, true)); // lis‰t‰‰n listaan lyhyt linna
		}
	}
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	int vari = this->getSiirtovuoro();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//Ei kysele tyhjilt‰ ruuduilta nappulan nime‰
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			if (this->_lauta[i][j]->getVari() != vari) {
				continue;
			}
			this->_lauta[i][j]->annaSiirrot(lista, &Ruutu(i, j), this, vari); // myˆh‰inen sidonta!
		}
	}
	this->annaLinnoitusSiirrot(lista, vari);
	this->huolehdiKuninkaanShakeista(lista, vari);
}


MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);

	// Rekursion kantatapaus 1: peli on loppu koska laillisia siirtoja ei ole.
	if (siirrot.size() == 0)
	{
		paluuarvo._evaluointiArvo = lopputulos();
		return paluuarvo;
	}

	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	if (syvyys == 0)
	{
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	paluuarvo._evaluointiArvo = (_siirtovuoro == 0 ? -1000000 : 1000000);
	for (auto s : siirrot)
	{
		// Seuraaja-asema (tehd‰‰n nykyisess‰ asemassa siirto s).
		Asema uusi_asema = *this;
		uusi_asema.paivitaAsema(&s);

		// Rekursiivinen kutsu.
		MinMaxPaluu arvo = uusi_asema.minimax(syvyys - 1);

		// Tutkitaan ollaan lˆydetty uusi paras siirto.
		if
		(
			(_siirtovuoro == 0 && arvo._evaluointiArvo > paluuarvo._evaluointiArvo) ||
			(_siirtovuoro == 1 && arvo._evaluointiArvo < paluuarvo._evaluointiArvo)
		)
		{
			// Lˆydettiin uusi paras siirto.
			paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
			paluuarvo._parasSiirto = s;
		}
	}
	return paluuarvo;
}


double Asema::lopputulos()
{
	// Asemassa ei ole en‰‰ laillisia siirtoja. Etsit‰‰n siirtovuoroisen pelaajan
	// kuningas; jos kuningas on uhattu, on pelaaja h‰vinnyt (muuten tasapeli, "patti").

	// Kuninkaan sijainti (x,y).
	Nappula* kunkku = _siirtovuoro == 0 ? vk : mk;
	int kx, ky;
	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			if (_lauta[x][y] == kunkku)
			{
				kx = x;
				ky = y;
			}
		}
	}

	if (onkoRuutuUhattu(&Ruutu(kx, ky), _siirtovuoro == 0 ? 1 : 0))
		return 0; // tasapeli (patti)
	else
		return _siirtovuoro == 0 ? -1000000 : 1000000;	// matti
}


/* 
	Aseman numeerinen arviointi eri tekijˆiden perusteella, esim.

	1. Nappuloiden arvo ("materiaali")
		Daami = 9
		Torni = 5
		L‰hetti = 3,25
		Ratsu = 3
		Sotilas = 1

	2. Kuninkaan turvallisuus/hyvyys
		Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
		Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
		vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa.

	3. Sentralisaatio (keskustan hallinta)
		Nappulat ovat yleens‰ paremmin laudan keskell‰ kuin laidoilla.

	4. Linjojen hallinta
		Tornit sijaitsevat hyvin avoimilla linjoilla (= linja jolla ei ole yht‰‰n omaa sotilasta).

	jne. jne.
*/
double Asema::evaluoi()
{
	// Vakiokertoimet kuvaavat eri tekijˆiden t‰rkeytt‰ suhteessa toisiinsa.
	// Kertoimien asettaminen edellytt‰‰ testaamista ja sovellusalueen (shakki)
	// osaamista. T‰ss‰ materiaalin t‰rkeydeksi on asetettu 1. Muiden tekijˆiden
	// kertoimet ovat yleens‰ t‰t‰ pienempi‰, koska materiaali on kaikkein
	// t‰rkein yksitt‰inen tekij‰.
	int siirtoVuoroKerroin = 1;


	if (getSiirtovuoro() == 1)
	{
		siirtoVuoroKerroin = -1;
	}

	std::list<Siirto> sList;
	annaLaillisetSiirrot(sList);

	const double materiaaliKerroin = 1.0;
	const double nappulaSijaintiKerroin = 0.1;
	const double laillisetSiirrotKerroin = 0.2*siirtoVuoroKerroin;
	const double parasPosKerroin = 0.01;
	const double linnotusPKerroin = 0.5*siirtoVuoroKerroin;
	const double kunkunlahiKerroin = 1;

	// Materiaali
	double valkoisenM = laskeNappuloidenArvo(0);
	double mustanM = laskeNappuloidenArvo(1);
	
	double materiaali = valkoisenM - mustanM;

	double paikka = laskeNappuloidenSijainti(0) - laskeNappuloidenSijainti(1);
	double parhaatNappulaPos;
	double linnotusP = linnotusPorkkana(getSiirtovuoro());
	//double kunkunLahi = katsoKunkkuLaheisyys(getSiirtovuoro());
	
	if (valkoisenM <= 15 || mustanM <= 15) 
	{
		
		parhaatNappulaPos=laskeParhaatNappulaPositiot(getSiirtovuoro(), false);

	}
	else
	{
		parhaatNappulaPos= laskeParhaatNappulaPositiot(getSiirtovuoro(), true);
	}

	
	double siirrot = sList.size();

	// Palautetaan eri tekijˆiden painotettu summa.
	return materiaaliKerroin * materiaali + nappulaSijaintiKerroin * paikka + laillisetSiirrotKerroin * siirrot+parhaatNappulaPos*parasPosKerroin+linnotusP*linnotusPKerroin; // + linjaKerroin * linjat + ... jne
}
double Asema::laskeNappuloidenSijainti(int vari)
{
	double valkeaArvo = 0;
	double mustaArvo = 0;

	double kerroin = 1;
	//valkoinen
	if (this->_lauta[3][3] != NULL && (this->_lauta[3][3]->getKoodi() == VS || this->_lauta[3][3]->getKoodi() == VR)) {
		valkeaArvo += kerroin;
	}
	if (this->_lauta[4][3] != NULL && (this->_lauta[4][3]->getKoodi() == VS || this->_lauta[4][3]->getKoodi() == VR)) {
		valkeaArvo += kerroin;
	}
	if (this->_lauta[3][4] != NULL && (this->_lauta[3][4]->getKoodi() == VS || this->_lauta[3][4]->getKoodi() == VR)) {
		valkeaArvo += kerroin;
	}
	if (this->_lauta[4][4] != NULL && (this->_lauta[4][4]->getKoodi() == VS || this->_lauta[4][4]->getKoodi() == VR)) {
		valkeaArvo += kerroin;
	}
	//musta
	if (this->_lauta[3][3] != NULL && (this->_lauta[3][3]->getKoodi() == MS || this->_lauta[3][3]->getKoodi() == MR)) {
		mustaArvo += kerroin;
	}
	if (this->_lauta[4][3] != NULL && (this->_lauta[4][3]->getKoodi() == MS || this->_lauta[4][3]->getKoodi() == MR)) {
		mustaArvo += kerroin;
	}
	if (this->_lauta[3][4] != NULL && (this->_lauta[3][4]->getKoodi() == MS || this->_lauta[3][4]->getKoodi() == MR)) {
		mustaArvo += kerroin;
	}
	if (this->_lauta[4][4] != NULL && (this->_lauta[4][4]->getKoodi() == MS || this->_lauta[4][4]->getKoodi() == MR)) {
		mustaArvo += kerroin;
	}

	if (vari == 0)
		return valkeaArvo;
	else
		return mustaArvo;
}


//double Asema::katsoKunkkuLaheisyys(int vari) 
//{
//	int kuninkaanX;
//	int kuninkaanY;
//	if (vari == 0) {
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				if (this->_lauta[i][j] == NULL)
//					continue;
//				if (this->_lauta[i][j]->getKoodi() == VK) {
//					kuninkaanX = i;
//					kuninkaanY = j;
//					break;
//				}
//			}
//		}
//	}
//	if (vari == 1) {
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				if (this->_lauta[i][j] == NULL)
//					continue;
//				if (this->_lauta[i][j]->getKoodi() == MK) {
//					kuninkaanX = i;
//					kuninkaanY = j;
//					break;
//				}
//			}
//		}
//	}
//
//	int cx = kuninkaanX - 1;
//	int default_x = cx;
//	int cy = kuninkaanY - 1;
//	int default_y = cy;
//
//	double pisteet = 0;
//	double soltunPisteet = 0.1;
//
//	for (int y = 0; y < 3; y++)
//	{
//		for (int x = 0; x < 3; x++)
//		{
//			if (cx >= 0 || cy >= 0 || cx < 7 || cy < 7) {
//				
//				if (this->_lauta[cx][cy] != NULL)
//				{
//					try {
//						int name = this->_lauta[cx][cy]->getKoodi();
//
//						if (name == VS && vari == 0)
//						{
//							pisteet += soltunPisteet;
//						}
//						if (name == MS && vari == 1)
//						{
//							pisteet += soltunPisteet;
//						}
//
//						throw 1;
//					}
//					catch (...) 
//					{
//
//					}
//					
//
//				}
//			}
//			
//
//			
//			cx++;
//
//		}
//		
//		cx = default_x;
//		cy++;
//	}
//
//	return pisteet;
//
//
//}
double Asema::linnotusPorkkana(int vari)
{	
	std::list<Siirto> siirrot;
	annaLinnoitusSiirrot(siirrot,vari);

	if (siirrot.empty())
		return 0;

	return 1;


}
double Asema::laskeParhaatNappulaPositiot(int vari, bool isMiddleGame)
{
	double vp = 0;
	double mp = 0;

	double vpe = 0;
	double mpe = 0;
	int index = 0;
	
	int arvoM = 0;
	int m_arvoM = 0;
	int arvoE = 0;
	int m_arvoE = 0;

	int sotilasM[] = { 0, 0, 0, 0, 0, 0, 0, 0,
		-21, -16, -6, -1, -1, -6, -16, -21,
		-21, -16, -6, 4, 4, -6, -16, -21,
		-21, -16, -1, 9, 9, -1, -16, -21,
		-14, -8, 6, 17, 17, 6, -8, -14,
		-5, 1, 14, 29, 29, 14, 1, -5,
		7, 11, 23, 39, 39, 23, 11, 7,
		0, 0, 0, 0, 0, 0, 0, 0 };
	int m_sotilasM[64];
	reverse_copy(begin(sotilasM), end(sotilasM), begin(m_sotilasM));
	
	int sotilasE[] = { 0, 0, 0, 0, 0, 0, 0, 0,
		5, -10, -20, -25, -25, -20, -10, 5,
		5, -10, -20, -25, -25, -20, -10, 5,
		10, -5, -15, -20, -20, -15, -5, 10,
		18, 2, -8, -15, -15, -8, 2, 18,
		30, 14, 1, -10, -10, 1, 14, 30,
		45, 30, 16, 5, 5, 16, 30, 45,
		0, 0, 0, 0, 0, 0, 0, 0 };
	int m_sotilasE[64];
	reverse_copy(begin(sotilasE), end(sotilasE), begin(m_sotilasE));

	int ratsuM[] = { -69, -19, -24, -14, -14, -24, -19, -69,
		-54, -39, -9, 11, 11, -9, -39, -54,
		-39, 1, 31, 21, 21, 31, 1, -39,
		-39, 11, 41, 36, 36, 41, 11, -39,
		-39, 41, 51, 51, 51, 51, 41, -39,
		-39, 46, 61, 71, 71, 61, 46, -39,
		-39, 21, 41, 41, 41, 41, 21, -39,
		-59, -39, -29, -29, -29, -29, -39, -59 };
	int m_ratsuM[64];
	reverse_copy(begin(ratsuM), end(ratsuM), begin(m_ratsuM));

	int ratsuE[] = { -63, -53, -43, -43, -43, -43, -53, -63,
		-53, -43, 18, 28, 28, 18, -43, -53,
		-43, 18, 48, 38, 38, 48, 18, -43,
		-43, 38, 58, 68, 68, 58, 38, -43,
		-43, 38, 73, 78, 78, 73, 38, -43,
		-43, 28, 78, 73, 73, 78, 28, -43,
		-53, -43, 38, 48, 48, 38, -43, -53,
		-63, -53, -43, -43, -43, -43, -53, -63 };
	int m_ratsuE[64];
	reverse_copy(begin(ratsuE), end(ratsuE), begin(m_ratsuE));

	int lahettiM[] = { -30, -25, -20, -20, -20, -20, -25, -30,
		-28, 11, 6, 1, 1, 6, 11, -28,
		-25, 6, 16, 11, 11, 16, 6, -25,
		1, 1, 16, 21, 21, 16, 1, 1,
		1, 21, 21, 26, 26, 21, 21, 1,
		1, 11, 21, 26, 26, 21, 11, 1,
		-10, 11, 1, 1, 1, 1, 11, -10,
		-20, -18, -16, -14, -14, -16, -18, -20 };
	int m_lahettiM[64];
	reverse_copy(begin(lahettiM), end(lahettiM), begin(m_lahettiM));
	
	int lahettiE[] = { -38, -18, -8, 2, 2, -8, -18, -38,
		-18, -8, 2, 7, 7, 2, -8, -18,
		-8, 2, 10, 12, 12, 10, 2, -8,
		2, 12, 16, 20, 20, 16, 12, 2,
		2, 12, 17, 22, 22, 17, 12, 2,
		-8, 2, 20, 22, 22, 20, 2, -8,
		-18, -8, 0, 12, 12, 0, -8, -18,
		-38, -18, -8, 2, 2, -8, -18, -38 };
	int m_lahettiE[64];
	reverse_copy(begin(lahettiE), end(lahettiE), begin(m_lahettiE));

	int torniM[] = { -8, -6, 2, 7, 7, 2, -6, -8,
		-8, -6, 2, 7, 7, 2, -6, -8,
		-8, -6, 6, 7, 7, 6, -6, -8,
		-8, -6, 6, 7, 7, 6, -6, -8,
		-8, -6, 6, 8, 8, 6, -6, -8,
		-8, -6, 6, 10, 10, 6, -6, -8,
		2, 2, 7, 12, 12, 7, 2, 2,
		-8, -6, 2, 7, 7, 2, -6, -8 };
	int m_torniM[64];
	reverse_copy(begin(torniM), end(torniM), begin(m_torniM));

	int torniE[] = { 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0 };
	int m_torniE[] = { 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0 };

	int daamiM[] = { -26, -16, -6, 4, 4, -6, -16, -26,
		-16, -11, -1, 4, 4, -1, -11, -16,
		-6, -6, -1, 4, 4, -1, -6, -6,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4 };
	int m_daamiM[64];
	reverse_copy(begin(daamiM), end(daamiM), begin(m_daamiM));

	int daamiE[] = { -46, -41, -31, -26, -26, -31, -41, -46,
		-31, -26, -16, -6, -6, -16, -26, -31,
		-16, -1, 14, 24, 24, 14, -1, -16,
		-6, 9, 24, 34, 34, 24, 9, -6,
		-6, 9, 24, 34, 34, 24, 9, -6,
		-6, 9, 24, 34, 34, 24, 9, -6,
		-16, 4, 19, 29, 29, 19, 4, -16,
		-26, -6, -1, 4, 4, -1, -6, -26 };
	int m_daamiE[64];
	reverse_copy(begin(daamiE), end(daamiE), begin(m_daamiE));

	int kunkkuM[] = { -20, 0, 0, -10, -10, 0, 0, -20,
		-30, -30, -30, -35, -35, -30, -30, -30,
		-40, -40, -45, -50, -50, -45, -40, -40,
		-50, -50, -55, -60, -60, -55, -50, -50,
		-55, -55, -60, -70, -70, -60, -55, -55,
		-55, -55, -60, -70, -70, -60, -55, -55,
		-55, -55, -60, -70, -70, -60, -55, -55,
		-55, -55, -60, -70, -70, -60, -55, -55 };
	int m_kunkkuM[64];
	reverse_copy(begin(kunkkuM), end(kunkkuM), begin(m_kunkkuM));

	int kunkkuE[] = { -30, -25, -15, -10, -10, -15, -25, -30,
		-15, -10, 0, 10, 10, 0, -10, -15,
		0, 15, 30, 40, 40, 30, 15, 0,
		10, 25, 40, 50, 50, 40, 25, 10,
		10, 25, 40, 50, 50, 40, 25, 10,
		10, 25, 40, 50, 50, 40, 25, 10,
		0, 20, 35, 45, 45, 35, 20, 0,
		-10, 10, 15, 20, 20, 15, 10, -10 };
	int m_kunkkuE[64];
	reverse_copy(begin(kunkkuE), end(kunkkuE), begin(m_kunkkuE));


	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (this->_lauta[x][y] != NULL)
			{
				int name = this->_lauta[x][y]->getKoodi();
				
				if (name == VS || name == MS)
				{
					arvoM = sotilasM[index];
					arvoE = sotilasE[index];

					m_arvoM = m_sotilasM[index];
					m_arvoE = m_sotilasE[index];

					vp += arvoM;
					mp += m_arvoM * -1;

					vpe += arvoE;
					mpe += m_arvoE *-1;
				}

				if (name == VR || name == MR)
				{
					arvoM = ratsuM[index];
					arvoE = ratsuE[index];

					m_arvoM = m_ratsuM[index];
					m_arvoE = m_ratsuE[index];

					vp += arvoM;
					mp += m_arvoM * -1;

					vpe += arvoE;
					mpe += m_arvoE * -1;
				}

				if (name == VL || name == ML)
				{
					arvoM = lahettiM[index];
					arvoE = lahettiE[index];

					m_arvoM = m_lahettiM[index];
					m_arvoE = m_lahettiE[index];

					vp += arvoM;
					mp += m_arvoM * -1;

					vpe += arvoE;
					mpe += m_arvoE * -1;
				}

				if (name == VT || name == MT)
				{
					arvoM = torniM[index];
					arvoE = torniE[index];

					m_arvoM = m_torniM[index];
					m_arvoE = m_torniE[index];

					vp += arvoM;
					mp += m_arvoM * -1;

					vpe += arvoE;
					mpe += m_arvoE * -1;
				}

				if (name == VD || name == MD)
				{
					arvoM = daamiM[index];
					arvoE = daamiE[index];

					m_arvoM = m_daamiM[index];
					m_arvoE = m_daamiE[index];

					vp += arvoM;
					mp += m_arvoM * -1;

					vpe += arvoE;
					mpe += m_arvoE * -1;
				}

				if (name == VK || name == MK)
				{
					arvoM = kunkkuM[index];
					arvoE = kunkkuE[index];

					m_arvoM = m_kunkkuM[index];
					m_arvoE = m_kunkkuE[index];

					vp += arvoM;
					mp += m_arvoM * -1;

					vpe += arvoE;
					mpe += m_arvoE * -1;
				}


			}
			index++;
		}
	}

	
	if (vari == 0)
		if (isMiddleGame)
		{
			return vp;
		}
		else {
			return vpe;
		}
		
	else
		if (isMiddleGame) 
		{
			return mp;
		}
		else
		{
			return mpe;
		}
		




}

double Asema::laskeNappuloidenArvo(int vari)
{
	double valkeaArvo = 0;
	double mustaArvo = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (this->_lauta[x][y] != NULL) {
				int nappulanNimi = this->_lauta[x][y]->getKoodi();
				//Valkoiset
				if (nappulanNimi == VD)
					valkeaArvo += 9;
				if (nappulanNimi == VT)
					valkeaArvo += 5;
				if (nappulanNimi == VL)
					valkeaArvo += 3.25;
				if (nappulanNimi == VR)
					valkeaArvo += 3;
				if (nappulanNimi == VS)
					valkeaArvo += 1;
				//Mustat
				if (nappulanNimi == MD)
					mustaArvo += 9;
				if (nappulanNimi == MT)
					mustaArvo += 5;
				if (nappulanNimi == ML)
					mustaArvo += 3.25;
				if (nappulanNimi == MR)
					mustaArvo += 3;
				if (nappulanNimi == MS)
					mustaArvo += 1;
			}
		}
	}
	if (vari == 0)
		return valkeaArvo;
	else
		return mustaArvo;
}



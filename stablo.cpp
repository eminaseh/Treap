#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"
#include <utility>

template <typename Tip>
Stablo<Tip>::Stablo(){
    korijen = nullptr;
    broj_elemenata = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Ako je element koji korisnik trazi jednak trenutnom elementu, funkcija vraca true, ako je manji od njega onda se pretraga nastavlja u
 lijevom podstablu a ako je veci onda se pretraga nastavlja u desnom podstablu.
 Ako funkcija ne pronadje element vraca false.*/

template <typename Tip>
bool Stablo<Tip>::FindRek(Tip element, Cvor *cvor){
    if(cvor == nullptr)
        return false;
    if(element == cvor->element)
        return true;
    if(element < cvor->element)
        return FindRek(element,cvor->ld);
    else return FindRek(element,cvor->dd);
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Krece od korijena i ide lijevo ukoliko je element kojeg trazi manji od trenutnog elementa. U suprotnom ide desno.
 Ako funkcija pronadje element vraca pokazivac na taj cvor, a ako ga nema u stablu vraca nullptr.*/

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::FindCvor(Tip element){
    Cvor *trenutni = korijen;
    while(trenutni != nullptr){
        if(element == trenutni->element)
            return trenutni;
        if(element < trenutni->element)
            trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
    }
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Elementi se ispisuju u redoslijedu od najmanjeg do najveceg. Obilazi se prvo lijevo podstablo, zatim korijen pa onda desno podstablo.
  Ispisuje se svaki elemenet, prioritet elementa i djeca elementa ukoliko ih ima.*/

template <typename Tip>
void Stablo<Tip>::InOrderRek(Cvor* cvor) {
  if(cvor==nullptr)
    return;
  InOrderRek(cvor->ld);
  cout<<"Element : "<<cvor->element<<" - Prioritet("<<cvor->prioritet<<")";
  if(cvor->ld != nullptr)
    cout<<" - Lijevo dijete: "<<cvor->ld->element;
  if(cvor->dd != nullptr)
    cout<<" - Desno dijete: "<<cvor->dd->element;
  cout<<endl;
  InOrderRek(cvor->dd);
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Vrsi desnu rotaciju kada lijevo dijete ima veci prioritet od roditelja.*/

template <typename Tip>
void Stablo<Tip>::RotirajDesno(Cvor* &cvor){
    Cvor *x = cvor->ld;
    Cvor *S2 = x->dd;
    x->dd = cvor;
    cvor->ld = S2;
    cvor = x;
}
///////////////////////////////////////////////////////////////////////////////////////////////
/*Vrsi lijevu rotaciju kada desno dijete ima veci prioritet od roditelja.*/

template <typename Tip>
void Stablo<Tip>::RotirajLijevo(Cvor* &cvor){
    Cvor *y = cvor->dd;
    Cvor *S2 = y->ld;
    y->ld = cvor;
    cvor->dd = S2;
    cvor = y;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Bazni slucaj: ako je cvor nullptr, cvor sa unesenom vrijednoscu se umece u stablo.
  Ako je element vec u stablu ne radi nista.
  Ako je element manji(veci) od trenutnog elementa poziva se funkcija rekurzivno za lijevo (desno) podstablo i ako nije zadovoljena osobina max-heapa
  za prioritete vrsi rotacije. Rotacije se vrse pozivanjem funkcija RotirajDesno i RotirajLijevo.
  Prilikom ubcaivanja elementa, elementu ce se dodijeliti slucajni prioritet. Korisnik ne moze unositi prioritet pozivanjem javne funkcije
  Insert(Tip element), ali privatna funkcija InsertRek omogucava izbor specificnog prioriteta elementa sto je potrebno za implementaciju drugih funkcija.
*/

template <typename Tip>
void Stablo<Tip>::InsertRek(Tip element, Cvor* &cvor, int prioritet){

    if(cvor == nullptr){
       if(prioritet == 0)
            prioritet = rand() % 100;
       cvor = new Cvor(element,prioritet);
       broj_elemenata++;
       return;
    }

    if(element == cvor->element)
        return;

    if(element < cvor->element){
        InsertRek(element,cvor->ld,prioritet);
        if(cvor->ld != nullptr && cvor->ld->prioritet > cvor->prioritet)
            RotirajDesno(cvor);
    }
    else{
        InsertRek(element,cvor->dd,prioritet);
        if(cvor->dd != nullptr && cvor->dd->prioritet > cvor->prioritet)
            RotirajLijevo(cvor);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Ako je cvor list samo ga obrise. Ako ima jedno dijete onda na njegovo mjesto postavi to dijete a njega obrise
  a ako ima dvoje djece gleda koje dijete ima manji prioritet. Ako lijevo dijete ima manji prioritet od desnog, vrsi lijevu rotaciju
  i poziva funkciju rekurzivno na lijevo dijete. U suprotnom vrsi desnu rotaciju i poziva rekurzivnu funkciju na desno dijete.*/

template <typename Tip>
void Stablo<Tip>::DeleteRek(Tip element, Cvor* &cvor){
    if(cvor == nullptr)
        return;

    if(element < cvor->element)
        DeleteRek(element,cvor->ld);

    else if(element > cvor->element)
        DeleteRek(element,cvor->dd);

    else {
        if(cvor->ld == nullptr && cvor->dd == nullptr){
        delete cvor;
        broj_elemenata--;
        cvor = nullptr;
        }
        else if(cvor->ld == nullptr){
            Cvor *pomocni = cvor->dd;
            Cvor *trenutni = cvor;
            cvor = pomocni;
            delete trenutni;
            broj_elemenata--;

        }
        else if(cvor->dd == nullptr){
            Cvor *pomocni = cvor->ld;
            Cvor *trenutni = cvor;
            cvor = pomocni;
            delete trenutni;
            broj_elemenata--;
        }
        else if(cvor->ld != nullptr && cvor->dd != nullptr){
                if(cvor->ld->prioritet < cvor->dd->prioritet){
                    RotirajLijevo(cvor);
                    DeleteRek(element,cvor->ld);
                }
                else{
                    RotirajDesno(cvor);
                    DeleteRek(element,cvor->dd);
                }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija koja prima stablo s i neku vrijednost kljuca k (za koji se moze pretpostaviti da ne postoji u stablu), te vraca par stabala,
  jedno stablo gdje su svi elementi manji od k, te drugo stablo gdje su svi elementi veci od k. U stablo umece element koji ima vrijednost k
  i dodjeljuje mu prioritet veci od prioriteta svih elemenata u stablu (tj. od prioriteta korijena).
  Dodjeljuje mu prioritet korijena + 1 pa on prilikom umetanja postaje korijen. Njegovo lijevo i desno podstablo su stabla koja funkcija vraca.*/

template <typename Tip>
pair<Stablo<Tip>,Stablo<Tip>> Stablo<Tip>::RazdvojiStablo(Stablo<Tip> s, int k){
    s.InsertRek(k,s.korijen,s.korijen->prioritet+1);
    Stablo<Tip> s1;
    Stablo<Tip> s2;
    s1.korijen = s.korijen->ld;
    s2.korijen = s.korijen->dd;

    return {s1,s2};
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Vraca maksimum u stablu*/
template <typename Tip>
Tip Stablo<Tip>::Maksimum(){
    if(korijen == nullptr) throw "Stablo je prazno";
    Cvor *trenutni = korijen;
    while(trenutni->dd != nullptr){
        trenutni = trenutni->dd;
    }
    return trenutni->element;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija prima dva stabla S1 i S2 koja su prethodno nastala razdvajanjem tako da su svi elementi u S1 manji od svih elemenata u S2.
  Ukoliko je S1 prazno stablo vraca S2. Ako je S2 prazno stablo vracamo S1. Pravi cvor cija je vrijednost veca od svih elemenata u S1
  a manja od svih elemenata u S2. Koristi funkciju Tip Maksimum() koja vraca najvecu vrijednost u stablu. Vrijednost novog cvora je najveca vrijednost
  iz S1 + 1. Ta vrijednost ce biti manja od svih vrijednosti iz S2 jer su stabla S1 i S2 nastala razdvajanjem stabla a stablo razdvaja na manje i vece
  elemente u odnosu na neku vrijednost k. Izmedju najvece vrijednosti iz S1 i najmanje vrijednosti iz S2 ima barem jedan broj.
  Novom elementu dodjeljuje prioritet manji od svih prioriteta iz S1 i S2 INT_MIN. Nakon toga pravi novo stablo ciji je korijen novokreirani cvor,
  lijevo podstablo mu je S1, desno podstablo mu je S2. Na kraju brise taj element koristeci funkciju Delete. Funkcija vraca kreirano stablo.*/

template <typename Tip>
Stablo<Tip> Stablo<Tip>::SpojiStabla(Stablo<Tip> s1, Stablo<Tip> s2){
    if(s1.korijen == nullptr)
        return s2;
    else if(s2.korijen == nullptr)
        return s1;
    Tip najveca_vr_u_s1 = s1.Maksimum();
    Tip vr_novog_cvora = najveca_vr_u_s1 + 1;
    Cvor* novi_cvor = new Cvor(najveca_vr_u_s1 + 1,INT_MIN);
    Stablo<Tip> s;
    s.korijen = novi_cvor;
    s.korijen->ld = s1.korijen;
    s.korijen->dd = s2.korijen;
    s.Delete(vr_novog_cvora);
    return s;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija prima dva stabla pri cemu se pretpostavlja da stabla nemaju zajednickih elemenata. Ukoliko je stablo S1 prazno funkcija vraca stablo S2.
  Ukoliko je stablo S2 prazno funkcija vraca stablo S1. Funkcija provjerava koji od korijena ova dva stabla ima veci prioritet.
  Ako korijen drugog stabla ima veci prioritet pozivam fukciju swap(S1,S2). Ako korijen prvog stabla ima veci prioritet onda se funkcija (unija)
  rekurzivno poziva najprije za lijevo podstablo prvog stabla i lijevo stablo koje nastane razdvajanjem drugog stabla na vrijednosti manje i vece
  od vrijednosti korijena prvog stabla, a zatim na desno podstablo prvog stabla i desno stablo drugog stabla koje nastane razdvajanjem drugog stabla
  na vrijednosti manje i vece od vrijednosti korijena prvog stabla. Nakon toga se spajaju dvije novodobijene unije pomocu funkcije SpojiStabla i
  umece korijen iz S1. Funkcija vraca uniju stabala S1 i S2.*/

template <typename Tip>
Stablo<Tip> Stablo<Tip>::UnijaStabala(Stablo<Tip> s1, Stablo<Tip> s2){
    if(s1.korijen == nullptr)
        return s2;
    if(s2.korijen == nullptr)
        return s1;
    if(s1.korijen->prioritet < s2.korijen->prioritet)
        swap(s1,s2);

    Stablo<Tip> lijevo_podstablo;
    lijevo_podstablo.korijen = s1.korijen->ld;
    Stablo<Tip> desno_podstablo;
    desno_podstablo.korijen = s1.korijen->dd;

    pair<Stablo<Tip>,Stablo<Tip>> s_nastalo_razd_s2 = RazdvojiStablo(s2,s1.korijen->element);
    Stablo<Tip> l_unija = UnijaStabala(lijevo_podstablo,s_nastalo_razd_s2.first);
    Stablo<Tip> d_unija = UnijaStabala(desno_podstablo,s_nastalo_razd_s2.second);
    Stablo<Tip> s_unija = SpojiStabla(l_unija,d_unija);
    s_unija.Insert(s1.korijen->element);


    return s_unija;

}
///////////////////////////////////////////////////////////////////////////////////////////////


#endif // STABLO_CPP

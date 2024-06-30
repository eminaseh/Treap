#ifndef STABLO_H
#define STABLO_H
#include <iostream>
#include <utility>

using namespace std;
/*Postoje mnoge metode koje sluze za odrzavanje balansiranosti binarnog stable pretrage (kao sto su AVL stabla ili crveno-crna stabla).
 Jedan od nacina je da se simulira slucajni redoslijed umetanja u stablo, odakle onda na osnovu teorije vjerovatnoce slijedi da ce stablo biti
 balansirano sa velikom vjerovatnocom (tj. visina stabla ce biti O(logn)).
 Ideja je da elementi stabla pored vrijednosti (koja ce u ovom slucaju biti i kljuc za pretragu), sadrze i prioritete, koji se slucajno generisu
 pri umetanju elemenata u stablo. Svaka dva cvora treba da zadovoljavaju osobinu heapa za prioritete, tj. svaki cvor ima veci prioritet od svog djeteta,
 a manji od svog roditelja.
 Za odrzavanje osobine MaxHeap-a prilikom umetanja i brisanja iz stabla koriste se rotacije.
 Neka su T1,T2 i T3 podstabla stabla sa korijenom u Y(na lijevoj strani) i X na desnoj strani.
 Kljucevi u oba stabla prate redoslijed Kljucevi(T1) < kljuc(X) < kljucevi(T2) < kljuc(Y) < kljuc(T3).

                Y                               X
               / \     Desna rotacija          /  \
              X   T3   – – – – – – – >        T1   Y
             / \       < - - - - - - -            / \
            T1  T2     Lijeva rotacija           T2  T3


*/
template <typename Tip>
class Stablo{

    struct Cvor{
        Tip element;
        int prioritet;
        Cvor *ld, *dd;//Pokazivaci na lijevo i desno dijete cvora.
        Cvor(Tip element, int prioritet = 0, Cvor *ld = nullptr, Cvor *dd = nullptr):
            element(element), prioritet(prioritet), ld(ld), dd(dd) {}
    };

    Cvor *korijen;
    int broj_elemenata;
    bool FindRek(Tip element, Cvor *cvor);
    Cvor* FindCvor(Tip element);
    void InOrderRek(Cvor *cvor);
    void RotirajDesno(Cvor* &cvor);
    void RotirajLijevo(Cvor* &cvor);
    void InsertRek(Tip element, Cvor* &cvor, int prioritet = 0);
    void DeleteRek(Tip element, Cvor* &cvor);


    public:
    Stablo();
    bool Find(Tip element){ return FindRek(element,korijen); }
    void InOrder() { InOrderRek(korijen); }
    void Insert(Tip element){ InsertRek(element,korijen); }
    int VratiBrojElemenata(){ return broj_elemenata; }
    void Delete(Tip element) { DeleteRek(element,korijen); }
    pair<Stablo<Tip>,Stablo<Tip>> RazdvojiStablo(Stablo<Tip> s,int k);
    Tip Maksimum();
    Stablo<Tip> SpojiStabla(Stablo<Tip> s1, Stablo<Tip> s2);
    Stablo<Tip> UnijaStabala(Stablo<Tip> s1, Stablo<Tip> s2);

};

#include "stablo.cpp"
#endif // STABLO_H

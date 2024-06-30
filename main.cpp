#include<iostream>
#include "stablo.h"

using namespace std;

int main(){
    Stablo<int> s;

    s.Insert(50);
    s.Insert(30);
    s.Insert(10);
    s.Insert(40);
    s.Insert(7);
    s.Insert(60);
    s.Insert(25);
    s.Insert(5);
    s.Insert(15);

/*
    s.Insert(45);
    s.Insert(23);
    s.Insert(35);
    s.Insert(4);
    s.Insert(7);
    s.Insert(52);
    s.Insert(33);
    s.Insert(62);
    s.Insert(48);
*/

    cout<<"ISPIS STABLA OD NAJMANJEG DO NAJVECEG:"<<endl;
    s.InOrder();
    cout<<endl<<"Broj elemenata u stablu je: "<<s.VratiBrojElemenata()<<endl;

/*
    cout<<endl<<"BRISANJE: "<<endl;
    cout<<"Brisem 40: "<<endl;
    s.Delete(40);
    s.InOrder();
    cout<<endl<<"Broj elemenata u stablu je: "<<s.VratiBrojElemenata()<<endl;

    cout<<endl<<"Brisem 50: "<<endl;
    s.Delete(50);
    s.InOrder();
    cout<<endl<<"Broj elemenata u stablu je: "<<s.VratiBrojElemenata()<<endl;
*/

    cout<<endl<<"PRETRAGA: "<<endl;
    cout<<"Da li se u stablu nalazi 52: "<<s.Find(52)<<endl;
    cout<<"Da li se u stablu nalazi 99: "<<s.Find(99)<<endl;
    cout<<"Da li se u stablu nalazi 30: "<<s.Find(30)<<endl;
    cout<<"Da li se u stablu nalazi 5: "<<s.Find(5)<<endl;

    cout<<endl<<"RAZDVAJANJE STABLA: "<<endl;
    int k = 16;
    pair<Stablo<int>,Stablo<int>> par = s.RazdvojiStablo(s,k);
    Stablo<int> s_manji = par.first;
    Stablo<int> s_veci = par.second;
    cout<<"Stablo u kojem su svi manji od : "<<k<<endl;
    s_manji.InOrder();
    cout<<"Stablo u kojem su svi veci od : "<<k<<endl;
    s_veci.InOrder();

    cout<<endl<<"STABLO NASTALO SPAJANJEM STABALA"<<endl;
    Stablo<int> stablo_nastalo_spajanjem;
    stablo_nastalo_spajanjem = stablo_nastalo_spajanjem.SpojiStabla(s_manji,s_veci);
    stablo_nastalo_spajanjem.InOrder();

    cout<<endl<<"UNIJA STABALA"<<endl;
    Stablo<int> stablo1;
    stablo1.Insert(30);
    stablo1.Insert(60);
    stablo1.Insert(90);
    stablo1.Insert(20);
    stablo1.Insert(110);
    stablo1.Insert(80);
    cout<<"Stablo 1"<<endl;
    stablo1.InOrder();

    Stablo<int> stablo2;
    stablo2.Insert(40);
    stablo2.Insert(70);
    stablo2.Insert(100);
    stablo2.Insert(50);
    cout<<"Stablo 2"<<endl;
    stablo2.InOrder();

    Stablo<int> stablo_unija;
    stablo_unija = stablo_unija.UnijaStabala(stablo1,stablo2);
    cout<<"UNIJA stabla 1 i stabla2"<<endl;
    stablo_unija.InOrder();
}

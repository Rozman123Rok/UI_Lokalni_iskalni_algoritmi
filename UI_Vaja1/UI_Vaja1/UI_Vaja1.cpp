/**
    TO DO:
        Sahovnica more bit velikosti med 4 in 12, toliko je tudi kraljic, vsaka v svojem stolpcu
        Ustvarit array ki bo imel koordinate kraljic (index je stolpec, vrednost vrstice)
        hill climbing (nvm se kateri je pravi)
        local beam search
        simulated annealing
        genetic algorithm
        
        POGLEJ DODATNE PARAMETRE!
        ! NE POZABI ZBRISAT HILL CLIMB !
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <algorithm> 

struct sahovnica_LBS /// struktura za Local beam
{
    std::vector<int> kraljice;
    int hevristika;
};

int izbira_algoritma();
void rand_stanje(std::vector<int>& kraljice, int velikost);
void izris_sahovnice(std::vector<int> k);
int izracun_hevristike_HILLC(std::vector<int>k, int velikost);
void my_HillClimb(std::vector<int>& kraljice, int velikost, int st_interakcij);
void my_Simulated_Annealing(std::vector<int>& kraljice, int velikost, int st_interakcij);
void my_Local_Beam_Search(std::vector<int>& kraljice, int velikost, int k, int st_interakcij);
bool za_sort(sahovnica_LBS i, sahovnica_LBS j);
void my_Genetic_Algorithm(std::vector<int>& kraljice, int velikost, int k, int st_generacij);

int main()
{
    srand(time(0));
    int izbira;
    ///Lahko bi se dodal da je 0
    //do
    //{
    izbira = izbira_algoritma();
    //std::cout << "Izbira algoritma: " << izbira << "\n";
    int velikost_matrike;
    std::vector<int> kraljice;
    std::cout << "Vpisi velikost matrike: ";
    std::cin >> velikost_matrike;
    //std::cout << "Velikost matrike: " << velikost_matrike << "\n";
    
    for (int i = 0; i < velikost_matrike; i++)
    {
        kraljice.push_back(0); /// nastavimo vse kraljice na 0
    }
    
    rand_stanje(kraljice, velikost_matrike);

    switch (izbira)
    {
    case 1:
        std::cout << "Hill Climbing\n";
        int st_interakcij;
        std::cout << "Stevilo interakcij: ";
        std::cin >> st_interakcij;
        izris_sahovnice(kraljice);
        std::cout << "Hevristika: " << izracun_hevristike_HILLC(kraljice, velikost_matrike) << "\n";
        my_HillClimb(kraljice, velikost_matrike, st_interakcij);
        izris_sahovnice(kraljice);
        std::cout << "Hevristika: " << izracun_hevristike_HILLC(kraljice, velikost_matrike) << "\n";
        break;
    case 2:
        int T; /// temperatura
        std::cout << "Simulated Annealing\n";
        std::cout << "Temperatura: ";
        std::cin >> T;
        izris_sahovnice(kraljice);
        std::cout << "Hevristika: " << izracun_hevristike_HILLC(kraljice, velikost_matrike) << "\n";
        my_Simulated_Annealing(kraljice, velikost_matrike, T);
        izris_sahovnice(kraljice);
        std::cout << "Hevristika: " << izracun_hevristike_HILLC(kraljice, velikost_matrike) << "\n";
        break;
    case 3:
        int k; 
        std::cout << "Local Beam Search \n";
        std::cout << "K: ";
        std::cin >> k;
        izris_sahovnice(kraljice);
        std::cout << "Hevristika: " << izracun_hevristike_HILLC(kraljice, velikost_matrike) << "\n";
        my_Local_Beam_Search(kraljice, velikost_matrike, k, 10);
        izris_sahovnice(kraljice);
        std::cout << "Hevristika: " << izracun_hevristike_HILLC(kraljice, velikost_matrike) << "\n";
        break;
    case 4:
        int k_g, st_gen;
        std::cout << "Genetic Algorithm \n";
        std::cout << "Stevilo generacij: ";
        std::cin >> st_gen;
        std::cout << "Stevilo k v vsaki generaciji: ";
        std::cin >> k_g;
        if (k_g < 5) { k_g = 5; } /// nemore bit manj kot 5
        izris_sahovnice(kraljice);
        std::cout << "Hevristika: " << izracun_hevristike_HILLC(kraljice, velikost_matrike) << "\n";
        my_Genetic_Algorithm(kraljice,velikost_matrike,k_g,st_gen);
        izris_sahovnice(kraljice);
        std::cout << "Hevristika: " << izracun_hevristike_HILLC(kraljice, velikost_matrike) << "\n";
        break;
    default:
        break;
    }

    //} while (izbira!=0);
    //int h = izracun_hevristike_HILLC(kraljice, velikost_matrike);
    //std::cout << "Hevristika: " << h << "\n";
}

int izbira_algoritma() {
    int izbira;
    do
    {
    std::cout << "IZBERI KATERI ALGORITEM ZELIS UPORABITI: \n";
    std::cout << "1) Hill climbing \n";
    std::cout << "2) Simulated annealing \n";
    std::cout << "3) Local beam search \n";
    std::cout << "4) Genetic algorithm \n";
    //std::cout << "0) Koncaj \n";
    std::cout << "\n";
    std::cout << "Izbira: ";
    std::cin >> izbira;
    } while (izbira > 4 && izbira < 1);
    system("cls");
    return izbira;
}

void rand_stanje(std::vector<int>& kraljice, int velikost) {
    
    for (int i = 0; i < velikost; i++)
    {
        kraljice[i] = rand() % velikost;
        //std::cout << "Koordinate: x: " << i << " y: " << kraljice[i] << "\n";
    }
}

void izris_sahovnice(std::vector<int> k) {
    int velikost = k.size();
    std::cout << "---------------------------------\n";
    std::cout << "SAHOVNICA\n";
    for (int i = 0; i < velikost; i++)
    {
        for (int j = 0; j < velikost; j++)
        {
            if (k[j] == i) {
                std::cout << "1 ";
            }
            else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "---------------------------------\n";
}

int izracun_hevristike_HILLC(std::vector<int>k, int velikost) {
    int hevristika = 0;
    int hev_Dia = 0;
    // V istih vrsticah
    for (int i = 0; i < velikost; i++)
    {
        for (int j = i + 1; j < velikost; j++) {
            if (k[i] == k[j]) {
                hevristika++;
            }
        }

    }
    //std::cout << "Hevristika po vrsticah: " << hevristika << "\n";
    
    // po diagonali
    for (int i = 0; i < velikost; i++)
    {
        for (int j = 0; j < velikost; j++) {
            if (i != j) {
                if (abs(k[i] - k[j]) - abs(i - j) == 0) {
                    hev_Dia++;
                }
            }
        }
    }
    //std::cout << "Hevristika po dia: " << hev_Dia << "\n";
    /*if (hevristika + hev_Dia / 2 == 0) {
        izris_sahovnice(k);
    }*/
    return hevristika + hev_Dia / 2;

}

void my_HillClimb(std::vector<int>& kraljice, int velikost, int st_interakcij) {

    int trenutna_h = izracun_hevristike_HILLC(kraljice, velikost);
    //std::cout << "Trenutna: " << trenutna_h << "\n";
    std::vector<int> temp = kraljice;

    int index;
    int v = 0;
    do
    {
        int hev_pred = izracun_hevristike_HILLC(kraljice, velikost);
        for (int j = 0; j < st_interakcij; j++)
        {
            /// v tej izracunamo doloceno stevilo potez
            index = rand() % velikost; // izbremo rand stolpec
            v = rand() % velikost; // rand vrednost, ki jo nato nastavimo v stolpec
            if (temp[index] != v) {temp[index] = v;} // si shranimo to vrednost
            else if (temp[index] == v) { temp[index]++; } /// ce je ista vrednost pristejemo ena da jo spremenimo
            if (temp[index] >= velikost) { temp[index] = 0; } /// ce gremo prenizko skocimo nazaj na vrh
            trenutna_h = izracun_hevristike_HILLC(kraljice, velikost);
            int nova_h = izracun_hevristike_HILLC(temp, velikost); /// izracunamo novo hevristiko
            if (nova_h < trenutna_h) {
                /// si shranimo prvega najboljsega
                kraljice = temp; /// si shranimo najboljsega
                ///std::cout << "Nova: " << nova_h << "\n";
            }
        }
        if (izracun_hevristike_HILLC(kraljice, velikost) >= hev_pred) {
            break;
        }

        //std::cout << "I: " << i << "\n";
        //std::cout << "Hevristika: " << trenutna_h << "\n";
        //std::cout << "Nova sahovnica: \n";
        //izris_sahovnice(kraljice);

    } while (true);
    
}

void my_Simulated_Annealing(std::vector<int>& kraljice, int velikost, int st_interakcij) {
    /// dobimo sahovnico, ki ima neko hevristiko ki jo izracunam
    
    std::vector<int> temp = kraljice;
    int temperatura = st_interakcij; /// temperatura
    int delta_T = 1; /// sprememba temp

    int index;
    int v;
    int delta_h;
    do {
        // mislim da tu tudi izberes rand stolpec in isto kot pri hill climb
        if (temperatura == 0) {
            break;
        }

        index = rand() % velikost; // izbremo rand stolpec
        v = rand() % velikost; // rand vrednost, ki jo nato nastavimo v stolpec
        //temp[index] += v; // pristejemo to vrednost k vrednosti, ki je ze v stolpcu (torej premaknemo kraljico dol)
        //if (temp[index] >= velikost) { temp[index] = 0; } /// ce gremo y sahovnice gremo nazaj na vrh
        if (temp[index] != v) { temp[index] = v; } // si shranimo to vrednost
        else if (temp[index] == v) { temp[index]++; } /// ce je ista vrednost pristejemo ena da jo spremenimo
        if (temp[index] >= velikost) { temp[index] = 0; } /// ce gremo prenizko skocimo nazaj na vrh
        int trenutna_h = izracun_hevristike_HILLC(kraljice, velikost); /// hevristika
        int nova_h = izracun_hevristike_HILLC(temp, velikost); /// izracunamo novo hevristiko

        delta_h = nova_h - trenutna_h; //// izracunamo deltaT

        if (delta_h < 0) {
            kraljice = temp; /// pomeni da je nova hev < prejsne
        }
        else {
            float r = (float)delta_h / (float)temperatura;
            float nekaj = 1/exp(r);
            //std::cout << "Nekaj: " << nekaj << "\n";
            if (nekaj < 1) {
                /// tisti pogoj z vrjetnostjo zamenjave
                kraljice = temp;
            }
        }

        temperatura = temperatura - delta_T;
    } while (true);

    //izris_sahovnice(kraljice);
    //std::cout << "Hev: " << izracun_hevristike_HILLC(kraljice, velikost) << "\n";
}

void my_Local_Beam_Search(std::vector<int>& kraljice, int velikost, int k, int st_interakcij) {
    /// mnozica k zakljucenih stanj
    std::vector<sahovnica_LBS> najboljsih_k; /// shranjenih k sahovnic
    std::vector<sahovnica_LBS> sahovnica; /// tu bojo shranjene vse sahovnice (k*k)
    
    /// rabim rand k sahovnic
    for (int i = 0; i < k; i++) {
        sahovnica_LBS temp; /// temp struktura da jo push v vektor
        rand_stanje(kraljice, velikost); /// izracunamo rand postavitev sahovnice
        temp.kraljice = kraljice; /// si shranimo v temp
        temp.hevristika = izracun_hevristike_HILLC(kraljice, velikost);
        sahovnica.push_back(temp); /// push temp v vektor
    }
    
    /**
    /// izpis
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < velikost; j++)
        {
            std::cout << sahovnica[i].kraljice[j] << " ";
        }
        std::cout << " h: " << sahovnica[i].hevristika << "\n";
        std::cout << "-----------------------------\n";
    }
    */
    
    int index; /// keri stolpec
    int v; /// vrednost
    bool flag = false; /// flag za break
    int index_hev_nic; /// da si zaponim kje je bila hevristika 0
    do
    {

    for (int i = 0; i < k; i++) {
        /// da grem cez vseh k v vektorju
        for (int j = 0; j < k; j++) {
            /// da za vsakega iz vektorja razvijem k novih stanj
            index = rand() % velikost; // izbremo rand stolpec
            v = rand() % velikost; // rand vrednost, ki jo nato nastavimo v stolpec
            sahovnica_LBS temp;
            temp = sahovnica[i]; /// kopiram vrednosti ki jih bom spreminjal potem 
            if (sahovnica[i].kraljice[index] != v) { temp.kraljice[index] = v; } // si shranimo to vrednost
            else if (sahovnica[i].kraljice[index] == v) { temp.kraljice[index]++; } /// ce je ista vrednost pristejemo ena da jo spremenimo
            if (sahovnica[i].kraljice[index] >= velikost) { temp.kraljice[index] = 0; } /// ce gremo prenizko skocimo nazaj na vrh
            temp.hevristika = izracun_hevristike_HILLC(temp.kraljice, velikost); // shranim hevristiko
            sahovnica.push_back(temp); /// dodam kjer imam shranjene vse
        }
    }

    /*
    std::cout << "------PONOVEN IZPIS----------\n";
    /// ponovno izris sahovnice
    for (int i = 0; i < sahovnica.size(); i++) {
        for (int j = 0; j < velikost; j++) {
            std::cout << sahovnica[i].kraljice[j] << " ";
        }
        std::cout << " h: " << sahovnica[i].hevristika << "\n";
        std::cout << "-----------------------------\n";
    }
    **/


    /// jih zgeneriramo dovolj
    /// zaj jih moremo razvrstit
    //// sortiramo

    std::sort(sahovnica.begin(), sahovnica.end(), za_sort); /// sort s svojo funkcijo

    /**
    std::cout << "------PONOVEN IZPIS PO SORT----------\n";
    /// ponovno izris sahovnice
    for (int i = 0; i < sahovnica.size(); i++) {
        for (int j = 0; j < velikost; j++) {
            std::cout << sahovnica[i].kraljice[j] << " ";
        }
        std::cout << " h: " << sahovnica[i].hevristika << "\n";
        std::cout << "-----------------------------\n";
    }
    */

    /// Zaj pa pogledamo ce je keri hev = 0
    if (najboljsih_k.size() > 0) {
        /// ce ze imam shranjeno kaj v najboljsih_k
        najboljsih_k.clear(); /// jih spraznemo
    }
    for (int i = 0; i < sahovnica.size(); i++)
    {
        if (sahovnica[i].hevristika == 0) { 
            // ce imamo kdaj hevristiko 0
            flag = true; 
            index_hev_nic = i; /// shranimo na katerem indeksu je bila
            break; 
        }

        if (i < k) {
            /// ker so ze urejene lahko gremo kr po vrsti
            //// si shranimo k najboljsih
            sahovnica_LBS temp; /// kamor si jih shranim zacasno
            temp.kraljice = sahovnica[i].kraljice;
            temp.hevristika = sahovnica[i].hevristika;
            najboljsih_k.push_back(temp); /// push v top k
        }
    }

    /// si spraznemo se sahovnico polje
    if (flag) {
        kraljice = sahovnica[index_hev_nic].kraljice; /// shranimo sahovnico z hev 0 v kraljice (osnovna sahovnica)
        break; 
    }
    
    sahovnica.clear(); /// sahovnico spraznem da lahko dodam potem novih k ki sem jih izbral

    /**
    std::cout << "------IZPIS TOP K----------\n";
    /// ponovno izris sahovnice
    for (int i = 0; i < najboljsih_k.size(); i++) {
        for (int j = 0; j < velikost; j++) {
            std::cout << najboljsih_k[i].kraljice[j] << " ";
        }
        std::cout << " h: " << najboljsih_k[i].hevristika << "\n";
        std::cout << "-----------------------------\n";
    }

    std::cout << "Velikost sahovnica: " << sahovnica.size() << " velikost topk: " << najboljsih_k.size() << "\n";
    */

    /// si  damo nazaj v sahovnico top k
    sahovnica = najboljsih_k;

    } while (true);

}

bool za_sort(sahovnica_LBS i, sahovnica_LBS j) { return (i.hevristika < j.hevristika); }

void my_Genetic_Algorithm(std::vector<int>& kraljice, int velikost, int k, int st_generacij) {
    /// funkcija za genetski algoritem
    /// krizanje zamenjamo stolpca
    /// mutacija zamenjamo dve celici
    /// st_generacij 1000
    /// krizanje 35%, mutacija 5%, elitizem 20% (20% top avtomatsko v novo generacijo)

    std::vector<sahovnica_LBS> elita; /// shranjena elita
    std::vector<sahovnica_LBS> starsi; /// starsi katere krizamo, elita se ne kriza
    std::vector<sahovnica_LBS> sahovnica; /// tu bojo shranjene vse sahovnice (k*k)
    
    const int krizanje_vr = 35;
    const int mutacija_vr = 5;

    for (int i = 0; i < k; i++) {
        sahovnica_LBS temp; /// temp struktura da jo push v vektor
        rand_stanje(kraljice, velikost); /// izracunamo rand postavitev sahovnice
        temp.kraljice = kraljice; /// si shranimo v temp
        temp.hevristika = izracun_hevristike_HILLC(kraljice, velikost); /// izracunamo hevristiko
        sahovnica.push_back(temp); /// push temp v vektor
    }

    //std::cout << "SAHOVNICA SIZE " << sahovnica.size() << "\n";

    int stevec_generacij = 0; /// koliko generacij smo naredili
    bool hev_nic = false; /// ce je hev enaka 0
    int poz_hev_nic; /// si shranimo polozaj ki je hev 0
    do
    {
        for (int i = 0; i < k; i++)
        {
            sahovnica[i].hevristika = izracun_hevristike_HILLC(sahovnica[i].kraljice, velikost); /// izracunamo hevristike
        }

        std::sort(sahovnica.begin(), sahovnica.end(), za_sort); /// sort s svojo funkcijo
        //std::cout << "SAHOVNICA SIZE " << sahovnica.size() << "\n";
        
        /// izpis
        /*
        std::cout << "Prva v loop: \n";
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < velikost; j++)
            {
                std::cout << sahovnica[i].kraljice[j] << " ";
            }
            std::cout << " h: " << sahovnica[i].hevristika << "\n";
            std::cout << "-----------------------------\n";
        }
        */
        
        int s_elit = k * 0.2; /// vzamemo 20% k elementov
        int preostali_delez = k - s_elit; /// ostali elementi ki niso v eliti

        //std::cout << "Elit ele: " << s_elit << "\n";
        //std::cout << "SAHOVNICA SIZE " << sahovnica.size() << "\n";
        
        for (int i = 0; i < s_elit; i++)
        {
            elita.push_back(sahovnica[i]); /// si shranimo element sahovnice v elito
            sahovnica.erase(sahovnica.begin()); /// ga odstranimo ko smo ga uporabli
            if (elita[i].hevristika == 0)
            {
                poz_hev_nic = i; /// si shranimo polozaj elite kjer je hev 0
                hev_nic = true; /// si oznacimo flag
            }
        }

        if (hev_nic)
        {
            kraljice = elita[poz_hev_nic].kraljice; /// si shranimo elito in koncamo
            break; /// smo koncali
        }
        
        /**
        // izpis
        for (int i = 0; i < elita.size(); i++)
        {
            for (int j = 0; j < velikost; j++)
            {    
            std::cout << elita[i].kraljice[j] << " ";
            }
            std::cout << " Hev: " << elita[i].hevristika << "\n";
        }
        */


        //std::cout << "SAHOVNICA SIZE " << sahovnica.size() << "\n";
        for (int i = 0; i < preostali_delez; i++)
        {
            int index = rand() % sahovnica.size(); /// izberemo rand el ki ga damo v starse
            //std::cout << "Index: " << index << " s_elit: " << s_elit << "\n";
            //elita.push_back(sahovnica[i]);
            starsi.push_back(sahovnica[index]); /// te bomo krizali
            sahovnica.erase(sahovnica.begin() + index); /// ga odstranimo ko smo ga uporabli
        }

        //std::cout << "Velikost sahovnica (more bit 0): " << sahovnica.size() << "\n";

        for (int i = 0; i < s_elit; i++)
        {
            sahovnica.push_back(elita[i]); /// si shranimo elito za naslednjo generacijo
        }

        /**
        std::cout << "--------- IZPIS ELITE/ NOVA GEN -------\n";
        for (int i = 0; i < elita.size(); i++)
        {
            for (int j = 0; j < velikost; j++)
            {
                std::cout << elita[i].kraljice[j] << " ";
            }
            std::cout << " Hev: " << elita[i].hevristika << "\n";
        }
        */

        bool samo_en = false;
        for (int i = 0; i < preostali_delez; i+=2)
        {

            int stars1, stars2; /// dva stars ki jih bomo izbrali
            if (starsi.size() == 1) {
                /// ce nam ostane se samo en element
                //std::cout << "Se samo en element\n";
                sahovnica.push_back(starsi[0]); /// imamo samo en element in gre direkt v novo generacijo
                samo_en = true;
            }
            else {
                /// izberemo rand starsa za zamenjavo
                stars1 = rand() % starsi.size(); /// rand starsa 1 izberemo
                
                /*
                for (int i = 0; i < velikost; i++)
                {
                    std::cout << starsi[stars1].kraljice[i] << " ";
                }
                std::cout << "Stars1: " << starsi[stars1].hevristika << "\n";
                */


                stars2 = rand() % starsi.size(); /// izberemo rand drugega starsa
                if (stars2 == stars1)
                {
                    stars2++; /// da nista enake velikosti
                }
                if (stars2 >= starsi.size()) {
                    stars2 = 0; /// ce bi sel preko
                }

                /**
                for (int i = 0; i < velikost; i++)
                {
                    std::cout << starsi[stars2].kraljice[i] << " ";
                }
                std::cout << "Stars2: " << starsi[stars2].hevristika << "\n";
                */

                int lala = rand() % 100; /// pogledamo ce bomo krizali

                if (lala <= krizanje_vr) {
                    /// naredimo krizanje
                    int stolpec = rand() % velikost; /// si izberemo stolpec ki ga bomo zamenjali
                    int temp_v = starsi[stars1].kraljice[stolpec]; /// si shranimo vrednost kjer je kralica
                    starsi[stars1].kraljice[stolpec] = starsi[stars2].kraljice[stolpec]; /// prekopiramo
                    starsi[stars2].kraljice[stolpec] = temp_v; /// prekopiramo

                    /*
                    std::cout << "Izpis po krizanju!\n";
                    for (int i = 0; i < velikost; i++)
                    {
                        std::cout << starsi[stars1].kraljice[i] << " ";
                    
                    }
                    
                    std::cout << "Stars1 nova h: " << izracun_hevristike_HILLC(starsi[stars1].kraljice,velikost)<< "\n";
                    */
                    
                    starsi[stars1].hevristika = izracun_hevristike_HILLC(starsi[stars1].kraljice, velikost); /// izracunamo novo hevristiko
                    
                    /**
                    for (int i = 0; i < velikost; i++)
                    {
                        std::cout << starsi[stars2].kraljice[i] << " ";
                    
                    }
                    std::cout << "Stars2 nova h: " << izracun_hevristike_HILLC(starsi[stars2].kraljice, velikost) << "\n";
                    */

                    starsi[stars2].hevristika = izracun_hevristike_HILLC(starsi[stars2].kraljice, velikost); /// izracunamo novo hevristiko
                    

                }

                //sahovnica.push_back(starsi[stars1]); /// si shranimo za naslednjo generacijo
                //sahovnica.push_back(starsi[stars2]); /// si shranimo za naslednjo generacijo

                ///prvo morem zbrisat vecjega
                
                /*
                if (stars1 < stars2) {
                    starsi.erase(starsi.begin() + stars2);
                    starsi.erase(starsi.begin() + stars1);
                }
                else
                {
                    starsi.erase(starsi.begin() + stars1); /// ga odstranimo ko smo ga uporabli
                    starsi.erase(starsi.begin() + stars2);
                }
                */
            }

            //std::cout << "Stars1: " << stars1 << " stars2: " << stars2 << "\n";
            /// MUTACIJA
            int mutacija = rand() % 100;
            if (mutacija <= mutacija_vr) {
                ///delamo mutacijo
                int rand_stolpec = rand() % velikost; /// mamo matriko velikost x velikost
                int rand_vrstica = rand() % velikost; ///izbiramo 
                
                //std::cout << "Rand stolpec: " << rand_stolpec << " rand_vrstica: " << rand_vrstica << "\n";
                
                if (!(sahovnica[stars1].kraljice[rand_vrstica] == rand_stolpec && sahovnica[stars2].kraljice[rand_vrstica] == rand_stolpec ||
                    sahovnica[stars1].kraljice[rand_vrstica] != rand_stolpec && sahovnica[stars2].kraljice[rand_vrstica] != rand_stolpec))
                {
                    /// prvi pogoj: imata obe kraljico na tem mestu ne rabimo spreminjat
                    /// drugi pogoj: ali pa je doben nima in prav tako ne rabimo spreminjati 
                    /// ampak smo negirali tako da morem spremenit
                    /**
                    std::cout << "Izpis sahovnice mutacijo!\n";
                    for (int i = 0; i < sahovnica.size(); i++)
                    {
                        for (int j = 0; j < velikost; j++) {
                            std::cout << sahovnica[i].kraljice[j] << " ";
                        }
                        std::cout << "Hev: " << sahovnica[i].hevristika << "\n";
                    }
                    */
                    int temp = sahovnica[stars1].kraljice[rand_vrstica]; /// si shranimo vrednost
                    sahovnica[stars1].kraljice[rand_vrstica] = sahovnica[stars2].kraljice[rand_vrstica]; /// prekopiramo
                    sahovnica[stars2].kraljice[rand_vrstica] = temp; /// prekopiramo

                    /**
                    std::cout << "Ponoven izpis sahovnice po mutaciji!\n";
                    for (int i = 0; i < sahovnica.size(); i++)
                    {
                        for (int j = 0; j < velikost; j++) {
                            std::cout << sahovnica[i].kraljice[j] << " ";
                        }
                        std::cout << "Hev: " << sahovnica[i].hevristika << "\n";
                    }
                    */
                }
                ///
                
            }
            if (!samo_en) {
                sahovnica.push_back(starsi[stars1]); /// si shranimo za naslednjo generacijo
                sahovnica.push_back(starsi[stars2]); /// si shranimo za naslednjo generacijo

                if (stars1 < stars2) {
                    starsi.erase(starsi.begin() + stars2); // brisemo iz starsi da ga nebomo vec uporabljali
                    starsi.erase(starsi.begin() + stars1);
                }
                else
                {
                    starsi.erase(starsi.begin() + stars1); /// ga odstranimo ko smo ga uporabli
                    starsi.erase(starsi.begin() + stars2);
                }
            }
            /// izpis sahovnice
            /**
            std::cout << "Ponoven izpis sahovnice zadnja v loop!\n";
            for (int i = 0; i < sahovnica.size(); i++)
            {
                for (int j = 0; j < velikost; j++) {
                    std::cout << sahovnica[i].kraljice[j] << " ";
                }
                std::cout << "Hev: " << sahovnica[i].hevristika << "\n";
            }
            */
        }


        std::sort(sahovnica.begin(), sahovnica.end(), za_sort); /// sort s svojo funkcijo
        
        
        int polozaj_nic; /// kjer je hev 0
        //std::cout << "Ponoven izpis sahovnice zadnja v loop!\n";
        for (int i = 0; i < sahovnica.size(); i++)
        {
            /**
            for (int j = 0; j < velikost; j++) {
                std::cout << sahovnica[i].kraljice[j] << " ";
            }
            */
            //std::cout << "Hev: " << sahovnica[i].hevristika << "\n";
            if (sahovnica[i].hevristika == 0) {
                /// testiramo ce je hev 0 da smo koncali
                polozaj_nic = i;
                hev_nic = true;
            }
        }

        //std::cout << "###############################################\n###############################################\n";

        stevec_generacij++; /// povecamo stevilo gen
        if (hev_nic)
        {
            kraljice = sahovnica[polozaj_nic].kraljice; /// ce je nic smo koncali
            break;
        }
        else {
            kraljice = sahovnica[0].kraljice; /// shranimo si prvega, ker ima najboljso hev
        }
    } while (stevec_generacij<st_generacij);


}


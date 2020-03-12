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
        std::cout << "Gene \n";
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



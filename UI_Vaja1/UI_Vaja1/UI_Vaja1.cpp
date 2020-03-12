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

struct sahovnica_LBS
{
    std::vector<int> kraljice;
    int hevristika;
};

int izbira_algoritma();
void rand_stanje(std::vector<int>& kraljice, int velikost);
void izris_sahovnice(std::vector<int> k);
int izracun_hevristike_HILLC(std::vector<int>k, int velikost);
void HillClimbing(std::vector<int>& kraljice, int velikost, int st_interakcij);
void my_HillClimb(std::vector<int>& kraljice, int velikost, int st_interakcij);
void my_Simulated_Annealing(std::vector<int>& kraljice, int velikost, int st_interakcij);
void my_Local_Beam_Search(std::vector<int>& kraljice, int velikost, int k, int st_interakcij);
//void rand_stanje_LBS(std::vector<int>& kraljice, int velikost);
bool za_sort(sahovnica_LBS i, sahovnica_LBS j);



int main()
{
    srand(time(0));
    int izbira = izbira_algoritma();
    std::cout << "Izbira algoritma: " << izbira << "\n";
    int velikost_matrike;
    std::vector<int> kraljice;
    std::cout << "Vpisi velikost matrike:";
    std::cin >> velikost_matrike;
    std::cout << "Velikost matrike: " << velikost_matrike << "\n";
    for (int i = 0; i < velikost_matrike; i++)
    {
        kraljice.push_back(0);
    }
    
    rand_stanje(kraljice, velikost_matrike);

    switch (izbira)
    {
    case 1:
        std::cout << "HILL C \n";
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
        std::cout << "simulated annealing\n";
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
        std::cout << "local beam search \n";
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

void HillClimbing(std::vector<int>& kraljice, int velikost, int st_interakcij) {
    // izracunamo trenutno hevristiko
    int min_hev;
    int trenutna_h = izracun_hevristike_HILLC(kraljice, velikost);
    std::cout << "Trenutna: " << trenutna_h << "\n";
    std::vector<int> temp;
    for (int i = 0; i < st_interakcij && trenutna_h > 0; i++)
    {
        bool flag = true;
        
        int temp_h = trenutna_h;

        for (int col = 0; col < velikost && flag; col++) {

            for (int row = 0; row < velikost; row++) {
                // we do not need to evaluate because we already know current cost by costToBeat.
                if (row == kraljice[col])
                    continue;

                // init new copy
                std::vector<int>rc = kraljice;
                rc[col] = row;
                int cena = izracun_hevristike_HILLC(kraljice, velikost);
                if (trenutna_h > cena) {
                    temp = kraljice;
                    kraljice[col] = row;
                    trenutna_h = cena;
                    flag = false;
                    min_hev = cena;
                    break;
                }
                
            }
        }
        // if it gets stuck at local maxima
        if (temp_h == trenutna_h)
            rand_stanje(kraljice, velikost);
            //r = SolverUtils.generateRandomState(n);

    }
    //std::cout << "TEMP   \n"<<min_hev<<"\n";
    izris_sahovnice(temp);
    kraljice = temp;
    //kraljice = rc
    //return trenutna_h == 0 ? kraljice : NULL; // return solution if solved

}

void my_HillClimb(std::vector<int>& kraljice, int velikost, int st_interakcij) {
    // tota bi naj sla dokler se hevristika ne poveca al neke takega 
    //int min_hev; /// min hevristika
    int trenutna_h = izracun_hevristike_HILLC(kraljice, velikost);
    //min_hev = trenutna_h; /// prva hev je tudi min
    //std::cout << "Trenutna: " << trenutna_h << "\n";
    std::vector<int> temp = kraljice;
    //std::vector<int> top = kraljice;
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
                std::cout << "Nova: " << nova_h << "\n";
            }
        }
        if (izracun_hevristike_HILLC(kraljice, velikost) >= hev_pred) {
            break;
        }

        //std::cout << "I: " << i << "\n";
        std::cout << "Hevristika: " << trenutna_h << "\n";
        //std::cout << "Nova sahovnica: \n";
        //izris_sahovnice(kraljice);

    } while (true);
    
    
    /**
    int min_hev;
    int trenutna_h = izracun_hevristike_HILLC(kraljice, velikost);
    std::cout << "Trenutna: " << trenutna_h << "\n";
    std::vector<int> temp = kraljice;
    int i = 0;
    int index;
    int v = 0;
    int stevec = 0;
    do {
        index = rand() % velikost; // izbremo rand stolpec
        v = rand() % velikost; // rand vrednost, ki jo nato nastavimo v stolpec
        temp[index]+=v; // pristejemo to vrednost k vrednosti, ki je ze v stolpcu (torej premaknemo kraljico dol)
        if (temp[index] >= velikost) { temp[index] = 0; } /// ce gremo y sahovnice gremo nazaj na vrh
        int nova_h = izracun_hevristike_HILLC(temp, velikost); /// izracunamo novo hevristiko
        if (nova_h < trenutna_h || nova_h == 0) {
            /// se mnda ni pravi pogoj
            /// ce se izbolsa hev
            kraljice = temp; // si shranimo polozaj kraljic
            trenutna_h = nova_h; /// zamenjamo hev, ki jo moramo premagati
            //stevec = 0; /// stevec damo na nic ker ni bila ista vrednost hev
        }
        //stevec++; // povecamo hev
        //if (stevec > 15) {
            // ce ze 15 ponovitev racunamo isto hevristiko
          //  rand_stanje(temp, velikost); // dobimo novo rand stanje na sahovnici
        //}
        i++; /// povecamo stevilo ponovitev
        //if (trenutna_h == 0) {
            //std::cout << "HEVRISTIKA JE NIC! KRALJICE: \n";
            //izris_sahovnice(kraljice);
            //izris_sahovnice(temp);
        //}
    } while (i<st_interakcij && trenutna_h != 0); // dokler hevristika ni 0 in nismo presegli stevilo interakcij

    std::cout << "I: " << i << "\n";
    std::cout << "Hevristika: " << trenutna_h << "\n";
    //std::cout << "Nova sahovnica: \n";
    //izris_sahovnice(kraljice);
    */
}

void my_Simulated_Annealing(std::vector<int>& kraljice, int velikost, int st_interakcij) {
    /// dobimo sahovnico, ki ima neko hevristiko ki jo izracunam
    
    std::vector<int> temp = kraljice;
    int temperatura = st_interakcij; /// temperatura
    int delta_T = 1; /// sprememba temp
    // postopek ki se mi manka
    /***
        RABIM ONO ENACBO 
        VSAKIC KO GREM SKOZI LOOP ZMANSAM T-delta_T
        PO TISTI ENACBI SPREMINJAM POLOZAJE
        POGLEJ V UCB
    */
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

        delta_h = nova_h - trenutna_h;

        if (delta_h < 0) {
            kraljice = temp;
        }
        else {
            float r = (float)delta_h / (float)temperatura;
            float nekaj = 1/exp(r);
            std::cout << "Nekaj: " << nekaj << "\n";
            if (nekaj < 1) {
                /// tisti pogoj z vrjetnostjo zamenjave
                kraljice = temp;
            }
        }

        temperatura = temperatura - delta_T;
    } while (true);

    izris_sahovnice(kraljice);
    std::cout << "Hev: " << izracun_hevristike_HILLC(kraljice, velikost) << "\n";
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
    
    //prve_k = sahovnica;

    int index; /// keri stolpec
    int v; /// vrednost
    bool flag = false;
    int index_hev_nic;
    do
    {

    


    for (int i = 0; i < k; i++) {
        /// da grem cez vseh k v vektorju
        for (int j = 0; j < k; j++) {
            /// da za vsakega iz vektorja razvijem k novih stanj
            index = rand() % velikost; // izbremo rand stolpec
            v = rand() % velikost; // rand vrednost, ki jo nato nastavimo v stolpec
            sahovnica_LBS temp;
            temp = sahovnica[i];
            if (sahovnica[i].kraljice[index] != v) { temp.kraljice[index] = v; } // si shranimo to vrednost
            else if (sahovnica[i].kraljice[index] == v) { temp.kraljice[index]++; } /// ce je ista vrednost pristejemo ena da jo spremenimo
            if (sahovnica[i].kraljice[index] >= velikost) { temp.kraljice[index] = 0; } /// ce gremo prenizko skocimo nazaj na vrh
            temp.hevristika = izracun_hevristike_HILLC(temp.kraljice, velikost);
            sahovnica.push_back(temp);
        }
    }

    std::cout << "------PONOVEN IZPIS----------\n";
    /// ponovno izris sahovnice
    for (int i = 0; i < sahovnica.size(); i++) {
        for (int j = 0; j < velikost; j++) {
            std::cout << sahovnica[i].kraljice[j] << " ";
        }
        std::cout << " h: " << sahovnica[i].hevristika << "\n";
        std::cout << "-----------------------------\n";
    }



    /// jih zgeneriramo dovolj
    /// zaj jih moremo razvrstit
    //// sortiramo
    std::sort(sahovnica.begin(), sahovnica.end(), za_sort);


    std::cout << "------PONOVEN IZPIS PO SORT----------\n";
    /// ponovno izris sahovnice
    for (int i = 0; i < sahovnica.size(); i++) {
        for (int j = 0; j < velikost; j++) {
            std::cout << sahovnica[i].kraljice[j] << " ";
        }
        std::cout << " h: " << sahovnica[i].hevristika << "\n";
        std::cout << "-----------------------------\n";
    }

    /// Zaj pa pogledamo ce je keri hev = 0
    if (najboljsih_k.size() > 0) {
        najboljsih_k.clear(); /// jih spraznemo
    }
    for (int i = 0; i < sahovnica.size(); i++)
    {
        if (sahovnica[i].hevristika == 0) { 
            flag = true; 
            index_hev_nic = i; 
            break; 
        }

        if (i < k) {
            //// si shranimo k najboljsih
            sahovnica_LBS temp;
            temp.kraljice = sahovnica[i].kraljice;
            temp.hevristika = sahovnica[i].hevristika;
            najboljsih_k.push_back(temp);
        }
    }
    /// si spraznemo se sahovnico polje
    if (flag) {
        kraljice = sahovnica[index_hev_nic].kraljice;
        break; }
    sahovnica.clear();

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

    /// si  damo nazaj v sahovnico top k
    sahovnica = najboljsih_k;

    } while (true);

    /*sahovnica_LBS sahovnica;
    for (int i = 0; i < velikost; i++)
    {
        sahovnica.kraljice.push_back(rand() % velikost);
        std::cout << sahovnica.kraljice[i] << " ";
    }
    std::cout << "\n";*/
    /**
    std::vector<sahovnica_LBS> sahovnica;
    for (int i = 0; i < k; i++)
    {
        /// si shranimo k stevilo zacetnega stanja
        sahovnica_LBS temp;
        temp.kraljice = kraljice;
        temp.hevristika = izracun_hevristike_HILLC(kraljice, velikost);
        sahovnica.push_back(temp);
    }
    */
    /**
    std::vector<sahovnica_LBS> sahovnica;
    std::vector<sahovnica_LBS> dodatna;
    for (int i = 0; i < k; i++)
    {
        /// si shranimo k stevilo zacetnega stanja
        sahovnica_LBS temp;
        temp.kraljice = kraljice;
        temp.hevristika = izracun_hevristike_HILLC(kraljice, velikost);
        sahovnica.push_back(temp);
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < velikost; j++)
        {
            std::cout << sahovnica[i].kraljice[j] << " ";
        }
        std::cout << " h: " << sahovnica[i].hevristika << "\n";
        std::cout << "-----------------------------\n";
    }

    ///  sedaj imamo mnozico k zacetnih stanj
    /// spreminjamo vsako stanje posebaj
    /// ko jih uredimo mamo neki sahovnica_lBS temp ... lahko kr bubble sort ... lahko kr sproti
    /// pogledam ce je hev =0 .... sem konec
    /// q najboljsih si direkt dam v novo mnozico

    /// gremo skozi vsako stanje st_interakcij krat

    dodatna = sahovnica;

    int index;
    int v;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < st_interakcij; j++) {
            index = rand() % velikost; // izbremo rand stolpec
            v = rand() % velikost; // rand vrednost, ki jo nato nastavimo v stolpec
            if (dodatna[i].kraljice[index] != v) { dodatna[i].kraljice[index] = v; } // si shranimo to vrednost
            else if (dodatna[i].kraljice[index] == v) { dodatna[i].kraljice[index]++; } /// ce je ista vrednost pristejemo ena da jo spremenimo
            if (dodatna[i].kraljice[index] >= velikost) { dodatna[i].kraljice[index] = 0; } /// ce gremo prenizko skocimo nazaj na vrh
            dodatna[i].hevristika = izracun_hevristike_HILLC(dodatna[i].kraljice, velikost);
            //temp[index] += v; // pristejemo to vrednost k vrednosti, ki je ze v stolpcu (torej premaknemo kraljico dol)
            ///if (temp[index] >= velikost) { temp[index] = 0; } /// ce gremo y sahovnice gremo nazaj na vrh
        }
    }


    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < velikost; j++)
        {
            std::cout << dodatna[i].kraljice[j] << " ";
        }
        std::cout << " h: " << dodatna[i].hevristika << "\n";
        std::cout << "-----------------------------\n";
    }
    */

}


bool za_sort(sahovnica_LBS i, sahovnica_LBS j) { return (i.hevristika < j.hevristika); }



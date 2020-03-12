/**
    TO DO:
        Sahovnica more bit velikosti med 4 in 12, toliko je tudi kraljic, vsaka v svojem stolpcu
        Ustvarit array ki bo imel koordinate kraljic (index je stolpec, vrednost vrstice)
        hill climbing (nvm se kateri je pravi)
        local beam search
        simulated annealing
        genetic algorithm
        
        POGLEJ DODATNE PARAMETRE!
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

int izbira_algoritma();
void rand_stanje(std::vector<int>& kraljice, int velikost);
void izris_sahovnice(std::vector<int> k);
int izracun_hevristike_HILLC(std::vector<int>k, int velikost);
void HillClimbing(std::vector<int>& kraljice, int velikost, int st_interakcij);
void my_HillClimb(std::vector<int>& kraljice, int velikost, int st_interakcij);
void my_Simulated_Annealing(std::vector<int>& kraljice, int velikost, int st_interakcij);


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

    //izris_sahovnice(kraljice);
    switch (izbira)
    {
    case 1:
        std::cout << "HILL C \n";
        int st_interakcij;
        //HillClimbing(kraljice, velikost_matrike, 100);
        std::cout << "Stevilo interakcij: ";
        std::cin >> st_interakcij;
        izris_sahovnice(kraljice);
        my_HillClimb(kraljice, velikost_matrike, st_interakcij);
        izris_sahovnice(kraljice);
        break;
    case 2:
        std::cout << "Local beam \n";
        break;
    case 3:
        std::cout << "Sim a \n";
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
    std::cout << "2) Local beam search \n";
    std::cout << "3) Simulated annealing \n";
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
        //kraljice.push_back(rand() % velikost);
        kraljice[i] = rand() % velikost;
        std::cout << "Koordinate: x: " << i << " y: " << kraljice[i] << "\n";
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
    if (hevristika + hev_Dia / 2 == 0) {
        izris_sahovnice(k);
    }
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
    std::cout << "TEMP   \n"<<min_hev<<"\n";
    izris_sahovnice(temp);
    kraljice = temp;
    //kraljice = rc
    //return trenutna_h == 0 ? kraljice : NULL; // return solution if solved

}

void my_HillClimb(std::vector<int>& kraljice, int velikost, int st_interakcij) {
    // tota bi naj sla dokler se hevristika ne poveca al neke takega 
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

    //std::cout << "I: " << i << "\n";
    std::cout << "Hevristika: " << trenutna_h << "\n";
    //std::cout << "Nova sahovnica: \n";
    //izris_sahovnice(kraljice);
}

void my_Simulated_Annealing(std::vector<int>& kraljice, int velikost, int st_interakcij) {
    /// dobimo sahovnico, ki ima neko hevristiko ki jo izracunam
    int trenutna_h = izracun_hevristike_HILLC(kraljice, velikost);
    // morem si dolocit neko temp in delta temp
    int temperatura = 1000; /// temperatura
    int delta_T = 1; /// sprememba temp
    // postopek ki se mi manka
    /***
        RABIM ONO ENACBO 
        VSAKIC KO GREM SKOZI LOOP ZMANSAM T-delta_T
        PO TISTI ENACBI SPREMINJAM POLOZAJE
        POGLEJ V UCB
    */
    do {
        // mislim da tu tudi izberes rand stolpec in isto kot pri hill climb

        temperatura = temperatura - delta_T;
    } while (temperatura !=0);
}









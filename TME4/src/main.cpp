#include "Banque.h"  // Assurez-vous d'inclure le fichier d'en-tête Banque.h
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

using namespace std;

const int NB_THREADS = 5;  // Remplacez le nombre de threads selon vos besoins
const int NB_TRANSACTIONS = 1000;

int main() {
    // Création d'une instance de la classe Banque avec 10 comptes initialisés à 500 chacun
    pr::Banque banque(10, 500);

    // Vecteur pour stocker les threads de transaction
    vector<thread> threads;

    for (int i = 0; i < NB_THREADS; ++i) {
        threads.push_back(thread([&banque]() {
            // Générateur aléatoire
            random_device rd;
            mt19937 generator(rd());

            for (int n = 0; n < NB_TRANSACTIONS; ++n) {
                // Choix aléatoire de deux indices de comptes (i et j)
                uniform_int_distribution<size_t> dist(0, banque.size() - 1);
                size_t i = dist(generator);
                size_t j = dist(generator);

                // Montant aléatoire entre 1 et 100
                uniform_int_distribution<int> mDist(1, 100);
                int m = mDist(generator);

                // Tentative de transfert de i vers j
                banque.transfert(i, j, m);

                // Dormir une durée aléatoire entre 0 et 20 ms
                uniform_int_distribution<int> delayDist(0, 20);
                this_thread::sleep_for(chrono::milliseconds(delayDist(generator)));
            }
        }));
    }

    if (banque.comptabiliser(500 * 10)) {
        cout << "success" << endl;
        }

    // Attente que tous les threads se terminent
    for (auto &t : threads) {
        t.join();
    }

    if (banque.comptabiliser(500 * 10)) {
        cout << "success" << endl;
        }

    return 0;
}


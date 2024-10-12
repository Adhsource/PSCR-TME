#include "Banque.h"
#include <iostream>

using namespace std;

using namespace pr;

const int NB_THREAD = 100;

void banqueThreads(Banque & b){
	size_t max=b.size(); 
	for (int a=0; a<1000; ++a){
	int i = rand()%(max) + 0;
	int j = rand()%(max) + 0;
	int m= rand()%(100)+1; 
	b.transfert(i,j,m); 
	cout << "Transfert effectués de " << i << " vers " << j << " de " << m << "$" << endl;
	/*b.comptabiliser(100); 
	cout << "le solde est de " << b.getCompte(i).getSolde() << "à la " << a << " itération" << endl;
	*/
	bool comptabilisationOK = b.comptabiliser(10 * b.size());
        if (!comptabilisationOK) {
            cout << "Erreur de comptabilité à l'itération " << a << endl;
        }

	//this_thread::sleep_for(chrono::milliseconds(10));
	}

}

int main () {
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	Banque b(10,10); 

	for(int i=0; i<NB_THREAD; i++){
		threads.emplace_back(& banqueThreads, ref(b)); 	
	}

	for (auto & t : threads) {
		t.join();
	}
	for(int i=0; i<b.size(); ++i){
		cout<< "le compte numéro " << i << " qui a comme solde " << b.getCompte(i).getSolde() << endl; 

	}


	// TODO : tester solde = NB_THREAD * JP

	return 0;
}

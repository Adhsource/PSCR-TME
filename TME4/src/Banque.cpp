#include "Banque.h"
#include <mutex>
#include <iostream>

using namespace std;


namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	unique_lock<recursive_mutex> lock1(debiteur.getMutex(), defer_lock);
	unique_lock<recursive_mutex> lock2(crediteur.getMutex(), defer_lock);
	lock(lock1, lock2); 
	/* grace à lock et defer_lock, on peut retarder le verrouillage des deux entités mais aussi les verrouiller
	même temps par la suite*/
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}

}

 Compte& Banque::getCompte(size_t index) { 
    return comptes[index]; 
}

size_t Banque::size() const {
	return comptes.size();
}


bool Banque::comptabiliser (int attendu) const {
	unique_lock<mutex> lock(m); 
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu){
		cout << "Bilan co mptable faux : attendu " << attendu << " obtenu : " << bilan << endl;

	}
	
	return bilan == attendu;
}

}


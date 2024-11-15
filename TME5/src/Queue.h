#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <cstdlib>
#include <mutex>
using namespace std; 

namespace pr {

// MT safe version of the Queue, non blocking.
template <typename T>
class Queue {
	T ** tab;
	const size_t allocsize;
	size_t begin;
	size_t sz;
	mutable std::mutex m;
	condition_variable condFull; 
	condition_variable condEmpty;
	bool isBlockant=true; 

	// fonctions private, sans protection mutex
	bool empty() const {
		return sz == 0;
	}
	bool full() const {
		return sz == allocsize;
	}
public:
	Queue(size_t size) :allocsize(size), begin(0), sz(0) {
		tab = new T*[size];
		memset(tab, 0, size * sizeof(T*));
	}
	size_t size() const {
		std::unique_lock<std::mutex> lg(m);
		return sz;
	}
	T* pop() {
		std::unique_lock<std::mutex> lg(m);
		while(empty() && isBlockant){
			condEmpty.wait(lg); 
		}
		if (empty()) {
			return nullptr;
		}
		auto ret = tab[begin];
		tab[begin] = nullptr;
		sz--;
		begin = (begin + 1) % allocsize;
		condFull.notify_one(); 
		return ret;
	}
	bool push(T* elt) {
		std::unique_lock<std::mutex> lg(m);
		while( full() && isBlockant){
			condFull.wait(lg); 
		}
		if (full()) {
			return false;
		}
		tab[(begin + sz) % allocsize] = elt;
		sz++;
		condEmpty.notify_one(); 
		return true;
	}
	void setBlocking(bool Bloquant){
		this->isBlockant=Bloquant; 
		condEmpty.notify_all();
		condFull.notify_all();  
	}
	~Queue() {
		// ?? lock a priori inutile, ne pas detruire si on travaille encore avec
		for (size_t i = 0; i < sz; i++) {
			auto ind = (begin + i) % allocsize;
			delete tab[ind];
		}
		delete[] tab;
	}
};

}

#endif /* SRC_QUEUE_H_ */

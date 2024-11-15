#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;
int pv=3;

void handlerAttack(int n){
	if(n==0){
		exit(NULL); 
	}
	n--; 
	cout<< "nombre de pv restant "<< n<<endl; 
	 
}

void attaque(pid_t adversaire){
	 struct sigaction act; 
	 act.sa_handler=&handlerAttack; 
	 sigset_t setneg; 
	 sigfillset(&setneg); 
	 sigdelset(&setneg,SIGINT); 
	 kill(adversaire, SIGINT);

}

void defense(){

}

void combat(pid_t adversaire){

}

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int ppid=getpid(); 
	int nb_children=0; 
	for (int i=1, j=N; i<=N && j==N ; i++ ) {
		if(fork()==0){
			nb_children=0;
		}
		else{
			nb_children++;
			break;
		}
		std::cout << " i:j " << i << ":" << j << std::endl;
		nb_children++;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
				nb_children=0; 
			}else{
			nb_children++;
		}
		}
	}
	//cout<<"fin du programme" <<endl; 
	for(int i=0; i<nb_children; ++i){
		wait(NULL); 
		
	}
	
	if(ppid==getpid()){
		cout<<"fin du programme" <<endl;
	}
	return 0;
}

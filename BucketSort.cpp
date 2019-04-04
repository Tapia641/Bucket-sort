/*LIBRERIAS OBSOLETAS DE C*/
#include <pthread.h>//Para el manejo de hilos

/*LIBRERIAS DE CPP*/
#include <iostream>
#include <string>
#include <vector> //La estructura ideal ;)
#include <algorithm> //Para ocupar sort con complejidad de O(nlogn)
#include <cstdlib> //rand
#include <ctime> //sacar verdaderos aleatorios

using namespace std;
#define MAX 3500
#define IP A
#define PORT q12

struct DATA
{
	string ip;
	int port;
	vector<int> v;
	void push(int n){
		v.push_back(n);
	}
};


//0-RangoMax
void DivideCubetas(vector< vector<int> > &TotalCubetas, int &N){

	//Variable local
	vector<int> v;
	int NumeroAleatorio, M = 0;

	//Generamos los 3500 numeros en 0-999
	for (int i = 0; i < MAX; ++i)
	{
		NumeroAleatorio = (rand()%999)+1;
		//M = max(M,NumeroAleatorio);
		cout<<NumeroAleatorio<<endl;
		v.push_back(NumeroAleatorio);
	}

	cout<<M<<endl;

}


int main(int argc, char const *argv[])
{
	int CUBETAS;
	if (argc > 1)
	{
		//Ingresamos el numero de cubetas por la linea de comandos
		CUBETAS = atoi(argv[1]);

		//Vector que lleva las cubetas
		vector< vector<int> > TotalCubetas;
		DivideCubetas(TotalCubetas, CUBETAS);

		//Creamos un arreglo de hilos con tamanio de las cubetas
		pthread_t *TotalHilos = (pthread_t *)malloc(CUBETAS *sizeof(pthread_t));

		//Creamos los hilos
		for (int i = 0; i < CUBETAS; ++i)
		{
			//A cada hilo le mandamos cada una de las cubetas
			//pthread_create(&TotalHilos[i], NULL, Ordena(DivideCubetas[i]), NULL);
		}

		//Esperamos a los hilos culminen
		for (int i = 0; i < CUBETAS; ++i)
		{
			pthread_join(TotalHilos[i], NULL);
		}
	}else{
		cout<<"USO:\n"<<"./programa N\n";
	}

}

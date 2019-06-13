/* AUTOR: HERNANDEZ TAPIA LUIS ENRIQUE */

/*LIBRERIAS OBSOLETAS DE C*/
#include <pthread.h>//Para el manejo de hilos

/*LIBRERIAS DE CPP*/
#include <iostream>
#include <string>
#include <vector> //La estructura ideal ;)
#include <algorithm> //Para ocupar sort con complejidad de O(nlogn)
#include <cstdlib> //rand()
#include <ctime> //sacar verdaderos aleatorios
#include <cmath> //Para ceil

using namespace std;
#define MAX 3500

//Creamos una estructura para poder enviarla por el thread :D
struct DATA
{
	vector<int> v;

	void setVector(vector<int> p){
		v = p;
	}

	vector<int> getVector(){
		return v;
	}

	void Imprime(){
		for (int i = 0; i < v.size(); ++i)
		{
			cout<<v[i]<<endl;
		}
	}

	int getTam(){
		return v.size();
	}
	
};

//0-RangoMax
void DivideCubetas(vector<vector<int> > &TotalCubetas, int &N){

	//Variable local
	vector<int> v;
	int NumeroAleatorio, M = 0, Division = 0;

	//Generamos los 3500 numeros en 0-999
	srand(time(NULL));

	for (int i = 0; i < MAX; ++i)
	{
		NumeroAleatorio = (rand()%999)+1;
		M = max(M, NumeroAleatorio);
		v.push_back(NumeroAleatorio);
	}

	//Establecemos los rangos de para cada cubeta
	Division = floor(M/N);
	vector<int> Rango;

	//Establecemos el limite de cada rango
	for (int i = 0; i < N; ++i)
	{
		Rango.push_back(Division*i);
	}

	//Segmentamos cada numero en cada cubeta
	vector<int> CubetaSimple;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			//Considerar el i+1 cuando llegue a i == N overflow
			if (i == N-1)
			{
				if (v[j] >= Rango[i])
				{
					CubetaSimple.push_back(v[j]);
				}
			}else if(v[j] > Rango[i] && v[j] < Rango[i+1])
			{
				//cout<<v[j]<<endl;
				CubetaSimple.push_back(v[j]);
			}
		}
		TotalCubetas.push_back(CubetaSimple);
		CubetaSimple.clear();
	}
}

void *OrdenaCubeta(void *p){
	struct DATA *aux = (struct DATA *) p;
	vector<int> v = aux->getVector();
	sort(v.begin(), v.end()); //O(nlogn)
	aux->setVector(v);
	p = aux;
}


int main(int argc, char const *argv[])
{
	int CUBETAS;
	if (argc > 1)
	{
		//Ingresamos el numero de cubetas por la linea de comandos
		CUBETAS = atoi(argv[1]);

		//Vector que lleva las cubetas
		vector<vector<int> > TotalCubetas;
		DivideCubetas(TotalCubetas, CUBETAS);

		//Creamos un arreglo de hilos con tamanio de las cubetas
		pthread_t *TotalHilos = (pthread_t *)malloc(CUBETAS *sizeof(pthread_t));

		//Creamos un arreglo de informacion del tamanio de las cubetas
		struct DATA prueba[CUBETAS];

		//Creamos los hilos
		for (int i = 0; i < CUBETAS; ++i)
		{
			//A cada hilo le mandamos cada una de las cubetas
			prueba[i].setVector(TotalCubetas[i]);
			pthread_create(&TotalHilos[i], NULL, OrdenaCubeta, &prueba[i]);
		}

		//Esperamos a que los hilos culminen
		for (int i = 0; i < CUBETAS; ++i)
		{
			pthread_join(TotalHilos[i], NULL);
		}

		//Imprimimos resultado
		for (int i = 0; i < CUBETAS; ++i)
		{
			cout<<"Cubeta ["<<i+1<<"]: "<<endl;
			prueba[i].Imprime();
		}

	}else{
		cout<<"USO:\n"<<"./programa N\n";
	}

}

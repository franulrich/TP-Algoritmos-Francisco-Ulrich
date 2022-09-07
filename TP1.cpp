#include <iostream>
#include <fstream>

using namespace std;

void saber_ultimo(int dim_productos, int& ultimo, int& dif_ultimo, int i, float pesos[][5]){ //Función para saber qué productos son los dos últimos a mostrar, con el fin de poner punto, coma o "y"
    for(int j = 0 ; j < dim_productos ; j++){
            dif_ultimo++;
            if(pesos[i][j] > 13000){
                    ultimo = j;
                 if(j != dim_productos - 1)
                    dif_ultimo = 0; //No puedo hacer que para bat y zortzi funcione el "y".
                }
          }
}
void total_entregas(int entregas[][5], int entregasxproducto[5], int dim_productos, int dim_nombres){
    for(int i = 0 ; i < dim_nombres ; i++){
        for(int j = 0 ; j < dim_productos ; j++){
            entregasxproducto[j] += entregas[i][j];
        }
    }
}
void bubble_sort(float v[], int dim) //Algoritmo de ordenamiento de burbuja
{
	int i, j;
    float temp;
	bool desordenado {true};

	for (i = 1; i < dim && desordenado ; i++) {
		desordenado = false;
		for (j = 0 ; j < dim - i ; j++) {
			if (v[j] > v[j+1]) {
				temp = v[j+1];
				v[j+1] = v[j];
				v[j] = temp;
				desordenado = true;
			}
		}
	}
}


int main(){

    const int dim_nombres {8};
    string nombres[dim_nombres];
    const int dim_productos {5};
    string productos[dim_productos];
    
    ifstream archilec;
    archilec.open("Nombres.txt");
    if(!archilec){
        cout << "Error de lectura." << endl;
    }
    //Carga de datos
    for(int i = 0 ; i < dim_nombres && archilec >> nombres[i] ; i++);
    for(int i = 0 ; i < dim_productos && archilec >> productos[i] ; i++);
    archilec.close();

    cout << "Punto 1: " << endl;
    archilec.open("Datos.txt");
    if(!archilec){
        cout << "Error de lectura." << endl;
    }

    float pesos[dim_nombres][dim_productos] {0};
    float distancias[dim_nombres][dim_productos] {0};
    int entregas[dim_nombres][dim_productos] {0};
    int lista[dim_nombres][dim_productos] {0};
    int entregasxproducto[dim_productos] {0};
    int cliente, producto, ultimo;
    float peso, km;
    int dif_ultimo {0};
    int prodxcliente[dim_nombres] {0};
    while(archilec >> cliente >> producto >> peso >> km){
        pesos[cliente][producto] += peso;
        entregas[cliente][producto]++;
        distancias[cliente][producto] += km;
    }
    for(int i = 0 ; i < dim_nombres ; i ++){
        for(int j = 0 ; j < dim_productos ; j++){
            if(pesos[i][j] > 13000)
                lista[i][j] = j;
        }
    }
    for(int i = 0 ; i < dim_nombres ; i++){ 
        ultimo = 0;
        cout << nombres[i] << ": ";
        saber_ultimo(dim_productos, ultimo, dif_ultimo, i, pesos);
        for(int j = 0 ; j < dim_productos ; j++){
            if(pesos[i][j] > 13000){
                cout << productos[lista[i][j]];
                prodxcliente[i]++;
                if(j == ultimo)
                    cout << ".";
                else if(j == (ultimo - dif_ultimo))
                    cout << " y ";
                else
                cout << ", ";
            }
        }
        cout << endl;
    }
    cout << endl;

    cout << "Punto 2: " << endl;
    int clientemax {0};
    for(int i = 0 ; i < dim_nombres ; i++){
        if(prodxcliente[i] > prodxcliente[clientemax])
            clientemax = i;
    }
    cout << "El cliente con más productos que superan los 13000kg es " << nombres[clientemax] << ", entonces:" << endl << endl;

    float ordenkm[dim_productos];
    for(int i = 0 ; i < dim_productos ; i++){
        ordenkm[i] = distancias[clientemax][i];
    }
    bubble_sort(ordenkm, dim_productos);

    int ultimoj;
    for(int i = 0 ; i < dim_productos ; i++){
        for(int j = 0 ; j < dim_productos ; j++){
            if(ordenkm[i] == distancias[clientemax][j]){
                cout << productos[j] << ": " << ordenkm[i] << endl;
                ultimoj = j;
            }
        }
    }

    cout << endl << "Punto 3:" << endl;
    total_entregas(entregas, entregasxproducto, dim_productos, dim_nombres);
    cout << "Cantidad de entregas de \"" << productos[ultimoj] << "\": " << entregasxproducto[ultimoj];
}
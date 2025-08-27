#include <bits/stdc++.h>
using namespace std;

/*
  Función para mostrar el contenido de un arreglo de enteros
*/
void show_array(int* A, int n){
    //Se abre un bracket para el arreglo
    cout << "[ ";
    //Se recorre el arreglo
    for(int i = 0; i < n; i++)
        //Se imprime la posición actual seguida de un espacio
        cout << A[i] << " ";
    //Se cierra el bracket del arreglo
    cout << "]\n";
}

/*
  Funciones para ordenar un arreglo de enteros utilizando el
  Quicksort
*/
//Función que calcula el punto de partición en el arreglo
int partition(int* A, int p, int r){
    int temp; //Variable auxiliar
    //Se toma como pivote el primer dato
    int pivot = A[p];
    //Se toma como primera posición de referencia una después
    //del primer dato
    int i = p+1;

    /* Recorrido de los datos */
    //Desde la derecha del pivote y hasta la última posición
    for(int j = p+1; j <= r; ++j)
        //Si el dato actual es más pequeño que el pivote,
        //se intercambia con el dato que está en la
        //posición de referencia
        if(A[j] <= pivot){
            swap(A[i], A[j]);
            ++i; //Se desplaza la posición de referencia hacia la derecha
        }
    
    //Se mueve el pivote a su nueva posición (a la izquierda
    //de la última posición de referencia)
    swap(A[p], A[i-1]);

    //Se retorna la nueva posición del pivote
    //como el punto de corte
    return i-1;
}

//Función principal del método
void quicksort(int* A, int p, int r){
    //Se verifica que el arreglo tenga al menos
    //2 datos para poder proceder.
    //Si p == r, solo hay un dato.
    //Si p > r, es un arreglo no válido.
    if(p < r){
        //Se calcula el punto de corte
        int q = partition(A, p, r);

        //Se ordena la mitad izquierda
        quicksort(A, p, q-1);
        //Se ordena la mitad derecha
        quicksort(A, q+1, r);
    }
}

int main(void){
    //Arreglo de prueba
    int size = 8, A[size] = {5,2,4,6,1,3,9,7};

    cout << "Arreglo antes de ordenar: ";
    show_array(A,size);

    //Se ejecuta el ordenamiento
    quicksort(A,0,size-1);
    
    cout << "Arreglo después de ordenar: ";
    show_array(A,size);

    return 0;
}

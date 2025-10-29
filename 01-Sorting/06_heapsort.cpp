#include <bits/stdc++.h>
using namespace std;

void show_array(int A[], int n){
    cout << "[ ";
    for(int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << "]\n";
}

/******** Funciones de Heaps (Max-Heap específicamente) ********/

int parent(int i){
    return (i-1)/2;
}

int left(int i){
    return 2*i + 1;
}

int right(int i){
    return 2*i + 2;
}

void max_heapify(int A[], int i, int heap_size){
    int largest;

    int l = left(i);
    int r = right(i);

    if( l < heap_size && A[l] > A[i] )
        largest = l;
    else
        largest = i;

    if( r < heap_size && A[r] > A[largest] )
        largest = r;

    if( largest != i ){
        swap(A[i], A[largest]);
        max_heapify(A, largest, heap_size);
    }
}

void build_max_heap(int A[], int heap_size){
    for(int i = heap_size/2-1; i >= 0; i--)
        max_heapify(A, i, heap_size);
}

/******* Algoritmo que realiza el proceso de ordenamiento *******/

void heapsort(int A[], int n){
    //Tamaño inicial del montículo es la longitud del arreglo
    int heap_size = n;

    //Se transforma el arreglo en un montículo de máximos
    build_max_heap(A, heap_size);

    //Se hace un recorrido en reversa, para ir colocando los datos más grande hacia el final
    for(int i = n-1; i > 0; i--){
        //El dato en la raíz del montículo es el más grande de todos, por lo que se manda al final
        swap(A[0], A[i]);

        //Se reduce el tamaño del montículo en 1, ya que el dato del final actual ya está ordenado
        heap_size--;

        //Se corrige el montículo antes de proceder
        max_heapify(A, 0, heap_size);
    }
}

/*  Main  */
int main(void){
    //Arreglo de prueba
    int n = 10, A[n] = {77,79,34,32,80,22,45,1,13,21};

    cout << "Arreglo A antes de ordenar: ";
    show_array(A, n);
    //Se ordena el arreglo
    heapsort(A, n);
    cout << "Arreglo ordenado: ";
    show_array(A, n);

    return 0;
}



#include <bits/stdc++.h>
using namespace std;

/*
  Función para mostrar el contenido de un arreglo de enteros
*/
void show_array(int A[], int n){
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
  Funciones auxiliares para los heaps
*/
//Función para obtener, dado el índice de un nodo, el índice de su padre
int parent(int i){
    return (i-1)/2; //El floor se ejecuta automáticamente por devolverse como int
}

//Función para obtener, dado el índice de un nodo, el índice de su hijo izquierdo
int left(int i){
    return 2*i + 1;
}

//Función para obtener, dado el índice de un nodo, el índice de su hijo derecho
int right(int i){
    return 2*i + 2;
}

/*
  Funciones para MAX_HEAP
*/
//Función que, si la relación entre un nodo y sus hijos no cumple las especificaciones
//de un montículo de máximos, corrige la situación poniendo como padre al dato más
//grande de los tres
void max_heapify(int A[], int i, int heap_size){
    //Se preparan variables auxiliares
    int largest;

    //Se obtienen los índices de los hijos en el arreglo
    int l = left(i);
    int r = right(i);

    //Si el hijo izquierdo existe, se determina quién es más grande entre él y el padre
    if( l < heap_size && A[l] > A[i] )
        largest = l;
    else
        largest = i;

    //Si el hijo derecho existe, se determina quién es más grande entre él y el ganador anterior
    if( r < heap_size && A[r] > A[largest] )
        largest = r;

    //Si el padre no quedó como el más grande, se intercambia con el más grande de sus hijos
    if( largest != i ){
        swap(A[i], A[largest]);
        //En la nueva posición del padre puede haberse roto también la propiedad de montículo,
        //por lo que se envía a recursión para corregirlo
        max_heapify(A, largest, heap_size);
    }
}

//Función que transforma el contenido de un arreglo en un montículo
//En este caso se trabaja con un montículo de máximos
void build_max_heap(int A[], int heap_size){
    //Se corrige el contenido del arreglo para que cumpla las propiedades de un montículo de máximos
    //Se trabaja desde la mitad del arreglo en reversa, ya que la segunda mitad son las hojas del montículo
    //(lo anterior es una propiedad demostrable, si el lector está interesado puede consultarlo con el docente)
    for(int i = heap_size/2-1; i >= 0; i--) //El floor se ejecuta automáticamente por almacenarse en un int
        max_heapify(A, i, heap_size);
}

//Función para extraer la raíz de un MAX_HEAP
int pop_max(int A[], int* heap_size){
    //Se recoloca la raíz en la última posición
    swap(A[0], A[*heap_size - 1]);
    //Se extrae la última posición (la raíz)
    int answer = A[*heap_size - 1];

    //Se reduce el heap size
    (*heap_size)--;
    //Se corrije el heap desde la raíz y hacia abajo
    max_heapify(A, 0, *heap_size);

    //Se retorna la raíz
    return answer;
}

//Función para corregir un MAX_HEAP al insertar un nuevo dato
void patch_max_heap(int A[], int index){
    //Si se ha llegado a la raíz, ya no hay nada que hacer
    if(index == 0) return;

    //Se obtiene el padre del dato
    int p = parent(index);
    //Se verifica si el dato es más grande que su padre
    if(A[index] > A[p]){
        //Se hace el intercambio
        swap(A[index], A[p]);
        //Se sigue corrigiendo hacia arriba
        patch_max_heap(A, p);
    }
}

//Función para añadir un dato a un MAX_HEAP
void push_max(int A[], int* heap_size, int value){
    //Se añade el nuevo dato al final del heap actual
    A[*heap_size] = value;
    //Se actualiza el heap size
    (*heap_size)++;

    //Se corrige el heap desde el nuevo dato y hacia arriba
    patch_max_heap(A, *heap_size - 1);
}

/*
  Funciones para MIN_HEAP
*/
//Función que, si la relación entre un nodo y sus hijos no cumple las especificaciones
//de un montículo de mínimos, corrige la situación poniendo como padre al dato más
//pequeño de los tres
void min_heapify(int A[], int i, int heap_size){
    //Se preparan variables auxiliares
    int smallest;

    //Se obtienen los índices de los hijos en el arreglo
    int l = left(i);
    int r = right(i);

    //Si el hijo izquierdo existe, se determina quién es más pequeño entre él y el padre
    if( l < heap_size && A[l] < A[i] )
        smallest = l;
    else
        smallest = i;

    //Si el hijo derecho existe, se determina quién es más pequeño entre él y el ganador anterior
    if( r < heap_size && A[r] < A[smallest] )
        smallest = r;

    //Si el padre no quedó como el más pequeño, se intercambia con el más pequeño de sus hijos
    if( smallest != i ){
        swap(A[i], A[smallest]);
        //En la nueva posición del padre puede haberse roto también la propiedad de montículo,
        //por lo que se envía a recursión para corregirlo
        min_heapify(A, smallest, heap_size);
    }
}

//Función que transforma el contenido de un arreglo en un montículo
//En este caso se trabaja con un montículo de mínimos
void build_min_heap(int A[], int heap_size){
    //Se corrige el contenido del arreglo para que cumpla las propiedades de un montículo de mínimos
    //Se trabaja desde la mitad del arreglo en reversa, ya que la segunda mitad son las hojas del montículo
    //(lo anterior es una propiedad demostrable, si el lector está interesado puede consultarlo con el docente)
    for(int i = heap_size/2-1; i >= 0; i--) //El floor se ejecuta automáticamente por almacenarse en un int
        min_heapify(A, i, heap_size);
}

//Función para extraer la raíz de un MIN_HEAP
int pop_min(int A[], int* heap_size){
    //Se recoloca la raíz en la última posición
    swap(A[0], A[*heap_size - 1]);
    //Se extrae la última posición (la raíz)
    int answer = A[*heap_size - 1];
    
    //Se reduce el heap size
    (*heap_size)--;
    //Se corrije el heap desde la raíz y hacia abajo
    min_heapify(A, 0, *heap_size);

    //Se retorna la raíz
    return answer;
}

//Función para corregir un MIN_HEAP al insertar un nuevo dato
void patch_min_heap(int A[], int index){
    //Si se ha llegado a la raíz, ya no hay nada que hacer
    if(index == 0) return;

    //Se obtiene el padre del dato
    int p = parent(index);
    //Se verifica si el dato es más pequeño que su padre
    if(A[index] < A[p]){
        //Se hace el intercambio
        swap(A[index], A[p]);
        //Se sigue corrigiendo hacia arriba
        patch_min_heap(A, p);
    }
}

//Función para añadir un dato a un MAX_HEAP
void push_min(int A[], int* heap_size, int value){
    //Se añade el nuevo dato al final del heap actual
    A[*heap_size] = value;
    //Se actualiza el heap size
    (*heap_size)++;

    //Se corrige el heap desde el nuevo dato y hacia arriba
    patch_min_heap(A, *heap_size - 1);
}

/*
  Main
*/
int main(void){
    //Arreglo de prueba
    int sizeA = 10, sizeB = 10,
        A[50] = {77,79,34,32,80,22,45,1,13,21}, 
        B[50] = {23,68,45,75,44,87,100,60,43,24};

    cout << "Arreglo A antes de max_heapify: ";
    show_array(A, sizeA);
    //Se transforma el arreglo A en un MAX_HEAP
    build_max_heap(A, sizeA);
    cout << "Arreglo A después de max_heapify: ";
    show_array(A, sizeA);

    cout << "Arreglo B antes de min_heapify: ";
    show_array(B, sizeB);
    //Se transforma el arreglo B a un MIN_HEAP
    build_min_heap(B, sizeB);
    cout << "Arreglo B después de min_heapify: ";
    show_array(B, sizeB);

    cout << "Se extra la raíz de cada heap y se muestran:\n";
    cout << "Max: " << pop_max(A, &sizeA) << "\n";
    show_array(A, sizeA);
    cout << "Min: " << pop_min(B, &sizeB) << "\n";
    show_array(B, sizeB);

    cout << "Se añade un nuevo dato a cada heap y se muestran:\n";
    push_max(A, &sizeA, 59);
    show_array(A, sizeA);
    push_min(B, &sizeB, 15);
    show_array(B, sizeB);

    return 0;
}

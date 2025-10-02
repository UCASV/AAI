#include "test_array.hpp"

/* Funciones para ordenamiento */
int partition(int A[], int p, int r){
    int x = A[r];
    int i = p - 1;
    for(int j = p; j < r; j++)
        if( A[j] <= x){
            i++;
            swap(A[i], A[j]);
        }
    i++;
    swap(A[i], A[r]);
    return i;
}
void quicksort(int A[], int p, int r){
    if( p < r ){
        int q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}

/*
    Función que implementa el algoritmo de
    Búsqueda Binaria
    (Versión Iterativa)
*/
bool binary_search(int A[], int n, int v){
    //Se prepara una variable bandera, por defecto "abajo"
    bool ans = false;
    //Se preparan las variables del algoritmo:
    //  - Posición inicial
    //  - Posición final
    //  - Posición de la celda al medio
    int p = 0;
    int r = n - 1;
    int q;

    //Si el arreglo no está ordenado, debe ordenarse primero
    quicksort(A, 0, n-1); //Esta línea no es parte del algoritmo

    //Mientras quede al menos un dato a evaluar, se continúa el proceso
    while(p <= r){
        //Se calcula la celda al medio
        q = (p + r) / 2; //El floor se ejecuta automáticamente

        //Se compara el dato al medio con el buscado
        if(v == A[q]){
            //Si se ha encontrado el dato, se "levanta" la bandera
            ans = true;
            //Ya no es necesario seguir buscando
            break;
        }else
            //Si el dato es menor que el del medio, se continúa buscando
            //a su izquierda
            if(v < A[q]) r = q - 1; //Se ajusta la posición final
            //Si el dato es mayor que el del medio, se continúa buscando
            //a su derecha
            else p = q + 1; //Se ajusta la posición inicial
    }

    //Se retorna el resultado del proceso
    return ans;
}

/*
    Función que implementa el algoritmo de
    Búsqueda Binaria
    (Versión Recursiva)
*/
bool binary_search_recursive_aux(int A[], int p, int r, int v){
    //Mientras quede al menos un dato a evaluar, se ejecuta el proceso
    if(p <= r) {
        //Se calcula la celda al medio
        int q = (p + r) / 2; //El floor se ejecuta automáticamente

        //Se compara el dato al medio con el buscado
        if(v == A[q])
            //Se ha encontrado el dato
            return true;
        else
            //Si el dato es menor que el del medio, se continúa buscando
            //a su izquierda
            if(v < A[q])
                return binary_search_recursive_aux(A, p, q - 1, v); //Se ajusta la posición final
            //Si el dato es mayor que el del medio, se continúa buscando
            //a su derecha
            else
                return binary_search_recursive_aux(A, q + 1, r, v); //Se ajusta la posición inicial
    }

    //Si la condición del if falla, es que los valores p y r son inválidos,
    //y por ende, el dato buscado no se encuentra en el arreglo
    return false;
}
bool binary_search_recursive(int A[], int n, int v) {
    //Si el arreglo no está ordenado, debe ordenarse primero
    quicksort(A, 0, n-1); //Esta línea no es parte del algoritmo

    //Se busca el dato con el proceso recursivo.
    //Se especifican los valores iniciales para p y r
    return binary_search_recursive_aux(A, 0, n - 1, v);
}

/* Main */
int main(int argc, char** argv){
    //Se verifica que se haya invocado el programa proporcionando el dato a buscar
    if( argc != 2 ){
        cout << "El programa debe ejecutarse colocando el dato a buscar. >:|\n";
        exit(EXIT_FAILURE);
    }

    //Se extrae el dato a buscar del segundo argumento
    int v = atoi(argv[1]);
    
    //Se busca el dato utilizando búsqueda binaria (versión iterativa)
    if(binary_search(A, n, v)) cout << "El dato fue encontrado! :)\n";
    else cout << "El dato NO fue encontrado! :(\n";

    //Se busca el dato utilizando búsqueda binaria (versión recursiva)
    if(binary_search_recursive(A, n, v)) cout << "El dato fue encontrado! :)\n";
    else cout << "El dato NO fue encontrado! :(\n";

    return 0;
}
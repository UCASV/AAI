#include <bits/stdc++.h>
using namespace std;

/* Función utilitaria para mostrar estéticamente un arreglo */
void show_array(int A[], int n) {
    cout << "[ ";
    for(int i = 1; i < n; ++i)
        cout << A[i] << " ";
    cout << "]\n\n";
}

/* Funciones para el Fenwick Tree */

/*
    Función para acumular un dato X en un Fenwick Tree
    a partir de la posición i.
*/
void acum_fenwick(int F[], int n, int X, int i) {
    //Se continúa mientras no nos hayamos salido del arreglo
    while(i < n) {
        //Se acumula X en el índice actual
        F[i] += X;

        //Se calcula el paso
        int delta_i = i & (-i);

        //Se actualiza i
        i += delta_i;
    }
}

/*
    Función para construir un Fenwick Tree a partir de una
    base de datos unidimensional.
*/
void build_fenwick(int A[], int n, int F[]) {
    //Se recorre la base de datos.
    //No se utiliza la posición 0.
    for(int i = 1; i < n; ++i)
        //El valor actual en la base de datos es X.
        //Se acumula X en el Fenwick Tree a partir de la
        //posición actual en el recorrido.
        acum_fenwick(F, n, A[i], i);
}

/*
    Función para obtener el Range Sum Query (RSQ) de una
    colección de datos, desde la primera posición hasta una
    posición i, utilizando un Fenwick Tree.
*/
int RSQ_basic(int F[], int n, int i) {
    //Se inicializa el acumulador que contendrá la respuesta
    int res = 0;

    //El proceso continúa mientras no hayamos llegado a 0
    while(i > 0) {
        //Se acumula la posición actual en el Fenwick Tree
        res += F[i];

        //Se calcula el paso
        int delta_i = i & (-i);

        //Se actualiza i
        i -= delta_i;
    }

    //Se retorna el resultado
    return res;
}

/*
    Función para obtener el Range Sum Query (RSQ) de una
    colección de datos, desde una posición a hasta una
    posición b, utilizando un Fenwick Tree.
*/
int RSQ(int F[], int n, int a, int b) {
    // RSQ(a,b) = RSQ(1,b) - RSQ(1,a-1)
    return RSQ_basic(F, n, b) - RSQ_basic(F, n, a - 1);
}

/*********** Main ***********/

int main() {
    //Base de datos ilustrativa
    int n = 10;
    int A[n] = {-99, 7, 10, 11, 2, 10, 7, 20, 30, 5};

    //Se inicializa el Fenwick Tree para la base de datos
    int F[n] = {-99, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    //Mostramos la base de datos
    show_array(A, n);

    //Se construye el Fenwick Tree y se muestra
    build_fenwick(A, n, F);
    show_array(F, n);

    //Se ilustran varias RSQs
    cout << "RSQ(1, 8): " << RSQ_basic(F, n, 8) << "\n";
    cout << "RSQ(1, 4): " << RSQ_basic(F, n, 4) << "\n";
    cout << "RSQ(1, 9): " << RSQ_basic(F, n, 9) << "\n";
    cout << "RSQ(1, 7): " << RSQ_basic(F, n, 7) << "\n";
    cout << "RSQ(5, 9): " << RSQ(F, n, 5, 9) << "\n";
    cout << "RSQ(3, 5): " << RSQ(F, n, 3, 5) << "\n\n";

    //La base de datos sufre una modificación
    A[2] = 5; //Se modela como que se acumuló en esta posición un valor de -5

    //Se actualiza el Fenwick Tree acumulando -5 desde la posicion modificada
    acum_fenwick(F, n, -5, 2);
    //Se muestra el Fenwick Tree modificado
    show_array(F, n);

    //Calculamos nuevamente las RSQs que se ven afectadas por la moficiación,
    //para verificar que siguen funcionando.
    cout << "RSQ(1, 8): " << RSQ_basic(F, n, 8) << "\n";
    cout << "RSQ(1, 4): " << RSQ_basic(F, n, 4) << "\n";
    cout << "RSQ(1, 9): " << RSQ_basic(F, n, 9) << "\n";
    cout << "RSQ(1, 7): " << RSQ_basic(F, n, 7) << "\n";

    return 0;
}
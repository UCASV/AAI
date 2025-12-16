#include <bits/stdc++.h>
using namespace std;

// Estructura de un nodo de un Segment Tree
typedef struct Node {
    struct Node* parent;    // Puntero al padre
    string label;           // Label del intervalo al que corresponde el nodo
    int data;               // Dato del nodo
    struct Node* left;      // Puntero al hijo izquierdo
    struct Node* right;     // Puntero al hijo derecho
} Tree;

/* 
    Función para mostrar el contenido de un Segment Tree de forma jerárquica,
    es decir, dejando explícito cuáles son los hijos de cada nodo y a que nivel
    del árbol se encuentran.
    Esta función hace el recorrido estrictamente en PRE-ORDER.
*/
void show_with_levels(Tree* T, int level) {
    /*
        La siguiente línea coloca el contenido del nodo actual de la siguiente manera:
        - Coloca primero una cantidad de espacio equivalente al nivel actual de
          profundidad en el árbol (indicado por el parámetro level).
        - Coloca después el label del nodo actual seguido del dato del nodo actual.
        - Si el nodo actual es un nodo nulo, coloca entonces un '-' para indicarlo.
    */
    cout << [level](){ string r = ""; for(int i = 0; i < level; ++i) r+="   "; return r; }() 
         << ((T == NULL)?"-":T->label+": "+to_string(T->data)) << "\n";
    
    //Si el árbol está vacío, ya se indicó en la línea anterior, no hay nada más que hacer
    if( T == NULL ) return;
    //Se muestra el subárbol izquierdo
    show_with_levels(T->left, level + 1);
    //Se muestra el subárbol derecho
    show_with_levels(T->right, level + 1);
}

/* Función para crear un nuevo nodo con un valor y un label indicados */
Tree* create_node(int n, int p, int r) {
    //Se crea espacio en memoria para el nuevo nodo
    Tree* nodo = new Tree();

    //Se establece el dato del nodo como el parámetro n
    nodo->data = n;
    //Se construye el label del nodo a partir de los parámetros p y r
    nodo->label = to_string(p)+"-"+to_string(r);
    //Se inicializan los tres punteros del nodo
    nodo->parent = nodo->left = nodo->right = nullptr;
    
    //Se retorna el nuevo nodo
    return nodo;
}

/*
    Función para construir un Segment Tree a partir de un arreglo de enteros.
    Se asume que la operación de interés es la suma.
*/
Tree* build_segment(int A[], int p, int r) {
    //Si hay al menos dos datos, se continúa el proceso de Divide & Conquer
    if(p < r) {
        //Se calcula el punto medio
        int q = (p+r) / 2;

        //Se envía a recursión la mitad izquierda [p, q]
        Tree* L = build_segment(A, p, q);
        //Se envía a recursión la mitad izquierda [q+1, r]
        Tree* R = build_segment(A, q+1, r);

        //Se crea un nuevo nodo que contenga la suma de las raíces
        //de los árboles obtenidos desde la izquierda y la derecha
        Tree* N = create_node(L->data + R->data, p, r);

        //Se establece que L y R son los hijos de N
        //y que N es el padre de los árboles L y R
        N->left = L;
        N->right = R;
        L->parent = R->parent = N;

        //Se retorna N como el árbol resultante
        return N;
    }

    //Si hay un solo dato, es un caso trivial
    //Se crea un nuevo nodo con el dato
    else 
        return create_node(A[p], p, r); //Se podía utilizar tanto A[p] como A[r]
}

/*
    Función para obtener el Range Sum Query (RSQ) de una
    colección de datos, desde una posición p hasta una
    posición r, utilizando un Segment Tree.
*/
int RSQ(Tree* T, int p, int r) {
    //Se extraen el p y r del nodo a partir de su label
    int pl = stoi((T->label).substr(0,1));
    int rl = stoi((T->label).substr(2,3));

    //Si el intervalo solicitado esta completamente a la izquierda,
    //o completamente a la derecha, del intervalo del nodo, entonces
    //no se toma en cuenta y se retorna el elemento neutro de la operación.
    //(En este caso un 0 por tratarse de la suma)
    if (r < pl || rl < p) return 0;

    //Si el intervalo del nodo está total o parcialmente en el intervalo
    //solicitado, entonces se retorna su dato
    if (p <= pl && rl <= r) return T->data;

    //En cualquier otro caso, la respuesta será la agregación de la
    //respuesta del subárbol izquierdo con la del subárbol derecho
    return RSQ(T->left, p, r) + RSQ(T->right, p, r);
}

/* main */
int main(void) {
    //Arreglo de prueba
    int A[10] = { 21, 23, 61, 46, 97, 26, 48, 77, 71, 84 };
    
    //Se construye el Segment Tree
    Tree* S = build_segment(A, 0, 9);

    //Se muestra el Segment Tree construido
    show_with_levels(S, 0);

    //Consultas de prueba:
    cout << "RSQ(0,9): " << RSQ(S, 0, 9) << "\n";
    cout << "RSQ(5,9): " << RSQ(S, 5, 9) << "\n";
    cout << "RSQ(2,4): " << RSQ(S, 2, 4) << "\n";
    
    return 0;
}

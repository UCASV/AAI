#include <bits/stdc++.h>
using namespace std;

// Enumeración utilizada para la posición de un nodo con respecto a su padre
enum side {NONE, LEFT, RIGHT};
// Enumeración utilizada para los distintos tipos de recorridos de un árbol binario
enum mode {PRE, IN, POST};

// Estructura de un nodo de un BST
typedef struct Node {
    int data;               // Dato del nodo
    struct Node* left;      // Puntero al hijo izquierdo
    struct Node* right;     // Puntero al hijo derecho
    struct Node* parent;    // Puntero al padre
} TreeNode;

/* Función para mostrar un árbol binario en modo PRE-ORDER */
void BST_show_pre_order(TreeNode* T) {
    //Si el árbol está vacío, no hay nada que mostrar
    if( T == NULL ) return;
    cout << T->data << " ";         // 1o: Se muestra el nodo actual
    BST_show_pre_order(T->left);    // 2o: Se muestra el subárbol izquierdo
    BST_show_pre_order(T->right);   // 3o: Se muestra el subárbol derecho
}

/* Función para mostrar un árbol binario en modo POST-ORDER */
void BST_show_post_order(TreeNode* T) {
    //Si el árbol está vacío, no hay nada que mostrar
    if( T == NULL ) return;
    BST_show_post_order(T->left);   // 1o: Se muestra el subárbol izquierdo
    BST_show_post_order(T->right);  // 2o: Se muestra el subárbol derecho
    cout << T->data << " ";         // 3o: Se muestra el nodo actual
}

/* Función para mostrar un árbol binario en modo IN-ORDER */
void BST_show_in_order(TreeNode* T) {
    //Si el árbol está vacío, no hay nada que mostrar
    if( T == NULL ) return;
    BST_show_in_order(T->left);     // 1o: Se muestra el subárbol izquierdo
    cout << T->data << " ";         // 2o: Se muestra el nodo actual
    BST_show_in_order(T->right);    // 3o: Se muestra el subárbol derecho
}

/* Función para mostral un árbol indicando el modo deseado (PRE, IN, POST) */
void BST_show(TreeNode* T, enum mode modo) {
    //Se mostrará el contenido del árbol encerrado en corchetes
    cout << "[ ";
    //Se verifica cuál modo fue el solicitado
    //y se invoca a la función de recorrido correspondiente
    switch (modo) {
        case PRE:
            BST_show_pre_order(T);
            break;
        case IN:
            BST_show_in_order(T);
            break;
        case POST:
            BST_show_post_order(T);
            break;
    }
    //Se cierra el corchete
    cout << "]\n";
}

/* 
    Función para mostrar el contenido de un árbol binario de forma jerárquica,
    es decir, dejando explícito cuáles son los hijos de cada nodo y a que nivel
    del árbol se encuentran.
    Esta función hace el recorrido estrictamente en PRE-ORDER.
*/
void BST_show_with_levels(TreeNode* T, int level) {
    /*
        La siguiente línea coloca el contenido del nodo actual de la siguiente manera:
        - Coloca primero una cantidad de espacio equivalente al nivel actual de
          profundidad en el árbol (indicado por el parámetro level).
        - Coloca después el dato del nodo actual. Si el nodo actual es un nodo nulo,
          coloca entonces un '-' para indicarlo.
    */
    cout << [level](){ string r = ""; for(int i = 0; i < level; ++i) r+="   "; return r; }() << ((T == NULL)?"-":to_string(T->data)) << "\n";
    //Si el árbol está vacío, ya se indicó en la línea anterior, no hay nada más que hacer
    if( T == NULL ) return;
    //Se muestra el subárbol izquierdo
    BST_show_with_levels(T->left, level + 1);
    //Se muestra el subárbol derecho
    BST_show_with_levels(T->right, level + 1);
}

/* Función para crear un nuevo nodo con un valor indicado */
TreeNode* create_node(int n) {
    //Se crea espacio en memoria para el nuevo nodo
    TreeNode* node = new TreeNode();
    //Se establece el dato del nodo como el parámetro n
    node->data = n;
    //Se inicializan los tres punteros del nodo a NULL
    node->left = node->right = node->parent = NULL;
    
    //Se retorna el nuevo nodo
    return node;
}

/* Función para insertar un nuevo nodo en un BST */
TreeNode* BST_insert(TreeNode* T, int value) {
    //Cuando el nodo actual está vacío, es acá donde
    //se inserta el nuevo nodo.
    if( T == NULL ) T = create_node(value); //Se crea el nuevo nodo
    else
        //Si el nodo actual no está vacío, se verifica si debe
        //insertarse en el subárbol izquierdo o el derecho
        if( value <= T->data ) {
            //Se envía el subárbol izquierdo para su modificación,
            //y el árbol resultante sobreescribe el subárbol izquierdo
            //actual
            T->left = BST_insert(T->left, value);
            //Se establece el nodo actual como el padre del nuevo
            //subárbol izquierdo
            T->left->parent = T;
        } else {
            //Se envía el subárbol derecho para su modificación,
            //y el árbol resultante sobreescribe el subárbol derecho
            //actual
            T->right = BST_insert(T->right, value);
            //Se establece el nodo actual como el padre del nuevo
            //subárbol derecho
            T->right->parent = T;
        }

    //Se retorna el árbol actual con las modificaciones incorporadas
    return T;
}

/* Función para verificar si un dato se encuentra almacenado en un BST */
bool BST_search(TreeNode* T, int value) {
    //Si el árbol está vacío, entonces el dato no se encuentra en el BST
    if( T == NULL ) return false;
    else
        //Se verifica si el nodo actual contiene el dato buscado
        if( value == T->data ) return true;
        else
            //Se compara el dato buscado con el del nodo actual para
            //saber en cuál subárbol continuar la búsqueda
            if( value < T->data )
                //Se continúa buscando en el subárbol izquierdo, el
                //resultado dependerá de este proceso
                return BST_search(T->left, value);
            else
                //Se continúa buscando en el subárbol derecho, el
                //resultado dependerá de este proceso
                return BST_search(T->right, value);
}

/* Función para obtener la dirección del nodo que contenga un dato indicado en un BST */
TreeNode* BST_get(TreeNode* T, int value) {
    //Si el árbol está vacío, entonces el dato no se encuentra en el BST
    if( T == NULL ) return NULL;
    else
        //Se verifica si el nodo actual contiene el dato buscado. Si es así,
        //se retorna la dirección del nodo actual
        if( value == T->data ) return T;
        else
            //Se compara el dato buscado con el del nodo actual para
            //saber en cuál subárbol continuar la búsqueda
            if( value < T->data )
                //Se continúa buscando en el subárbol izquierdo, el
                //resultado dependerá de este proceso
                return BST_get(T->left, value);
            else
                //Se continúa buscando en el subárbol derecho, el
                //resultado dependerá de este proceso
                return BST_get(T->right, value);
}

/* Función para determinar de qué lado de su padre se encuentra un nodo */
enum side check_child_side(TreeNode* T) {
    //Si el nodo no tiene padre, entonces el concepto no aplica
    if( T->parent == NULL ) return NONE;
    //Se determina si el nodo es igual al hijo izquierdo de su padre
    if( T->parent->left == T ) return LEFT;
    //o si es igual al hijo derecho de su padre
    else return RIGHT;
}

/* 
    Función para extraer la dirección del IN-ORDER Sucessor (IOS) de un nodo
    - "El más pequeño de los datos más grandes que él en el BST"
    - "El nodo más a la izquierda de su subárbol derecho"

    Se asume que la función recibe la raíz del subárbol derecho del nodo
    en análisis.
*/
TreeNode* BST_extractIOS(TreeNode* T) {
    //Si ya no es posible avanzar hacia la izquierda, el nodo actual es el IOS
    if( T->left == NULL ) return T;
    //De lo contrario, se avanza hacia la izquierda
    return BST_extractIOS(T->left);
}

/* Función para borrar un nodo dentro de un BST que contenga el dato indicado */
void BST_delete(TreeNode* T, int value) {
    //Se verifica primero si el dato efectivamente se encuentra en el BST
    if( BST_search(T,value) ) {
        //Se extrae el nodo a eliminar
        TreeNode* dead = BST_get(T, value);

        //Se procede a evaluar cuál caso de borrado corresponde.
        //Se encierra el bloque en un DO-WHILE ya que es posible que
        //el proceso reinicie (aunque se sabe que si ocurre, solo
        //ocurriría una vez)
        do{
            //Caso 1: Los dos hijos del nodo a borrar son nulos
            if( dead->left == NULL && dead->right == NULL ) {
                //Se verifica si el nodo a eliminar es el hijo izquierdo de su padre
                if( check_child_side(dead) == LEFT )
                    dead->parent->left = NULL;  //Se registra la eliminación en el padre
                //o si es el hijo derecho de su padre
                else dead->parent->right = NULL;  //Se registra la eliminación en el padre

                //Se elimina el nodo
                delete dead;
                //Se termina el proceso
                return;
            }

            //Caso 2.1: Solo el hijo izquierdo del nodo a borrar no es nulo
            if( dead->left != NULL && dead->right == NULL ) {
                //Se verifica si el nodo a eliminar es el hijo izquierdo de su padre
                if( check_child_side(dead) == LEFT ) {
                    //El nuevo hijo izquierdo del padre, es el hijo izquierdo del nodo a borrar
                    dead->parent->left = dead->left;
                    //El nuevo padre del hijo izquierdo del nodo a borrar, es el padre de éste
                    dead->left->parent = dead->parent;
                //o si es el hijo derecho de su padre
                } else {
                    //El nuevo hijo derecho del padre, es el hijo izquierdo del nodo a borrar
                    dead->parent->right = dead->left;
                    //El nuevo padre del hijo izquierdo del nodo a borrar, es el padre de éste
                    dead->left->parent = dead->parent;
                }

                //Se elimina el nodo
                delete dead;
                //Se termina el proceso
                return;
            }

            //Caso 2.2: Solo el hijo derecho del nodo a borrar no es nulo
            if( dead->left == NULL && dead->right != NULL ) {
                //Se verifica si el nodo a eliminar es el hijo izquierdo de su padre
                if( check_child_side(dead) == LEFT ) {
                    //El nuevo hijo izquierdo del padre, es el hijo derecho del nodo a borrar
                    dead->parent->left = dead->right;
                    //El nuevo padre del hijo derecho del nodo a borrar, es el padre de éste
                    dead->right->parent = dead->parent;
                //o si es el hijo derecho de su padre
                } else {
                    //El nuevo hijo derecho del padre, es el hijo derecho del nodo a borrar
                    dead->parent->right = dead->right;
                    //El nuevo padre del hijo derecho del nodo a borrar, es el padre de éste
                    dead->right->parent = dead->parent;
                }

                //Se elimina el nodo
                delete dead;
                //Se termina el proceso
                return;
            }

            //Caso 3: Los dos hijos del nodo a borrar son no nulos
            //Se encuentra el IN-ORDER Sucessor del nodo a eliminar
            TreeNode* ios = BST_extractIOS(dead->right);
            //Se intercambia los datos del nodo a borrar y del IOS
            swap(dead->data, ios->data);
            //El nuevo nodo a eliminar es el IOS
            dead = ios;
        } while(true); //Acá se reinicia el proceso, pero se sabe que irá a parar ya sea en el Caso 1 o en el Caso 2

    //Si el dato indicado no se encuentra en el BST, se informa
    } else cout << "El dato " << value << " no está en el BST.\n";
}

/* 
    Función para liberar la memoria de todos los nodos de un BST.
    Esta operación forzosamente debe hacerse en POST-ORDER.
*/
void BST_destroy(TreeNode* T) {
    //Si el árbol está vacío, no hay nada que eliminar
    if( T == NULL ) return;
    //Se libera la memoria del subárbol izquierdo
    BST_destroy(T->left);
    //Se libera la memoria del subárbol derecho
    BST_destroy(T->right);
    //Se libera la memoria del nodo actual
    delete T;
}


/**************** Main ******************/
int main() {
    TreeNode* T = NULL;

    BST_show(T, IN);
    T = BST_insert(T, 52);
    BST_show(T, IN);
    T = BST_insert(T, 16);
    BST_show(T, IN);
    T = BST_insert(T, 3);
    BST_show(T, IN);
    T = BST_insert(T, 75);
    BST_show(T, IN);
    T = BST_insert(T, 90);
    BST_show(T, IN);
    T = BST_insert(T, 66);
    BST_show(T, IN);

    BST_delete(T, 52);
    BST_show(T, IN);
    BST_delete(T, 52);
    BST_delete(T, 75);
    BST_show(T, IN);
    BST_delete(T, 3);
    BST_show(T, IN);

    T = BST_insert(BST_insert(BST_insert(BST_insert(T, 5), 33), 71), 100);
    BST_show_with_levels(T, 0);

    BST_destroy(T);

    return 0;
}

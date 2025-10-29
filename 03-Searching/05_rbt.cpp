#include <bits/stdc++.h>
using namespace std;

// Enumeración utilizada para la posición de un nodo con respecto a su padre
enum side {NONE, LEFT, RIGHT};
// Enumeración utilizada para los distintos tipos de recorridos de un árbol binario
enum mode {PRE, IN, POST};
// Enumeración utilizada para los colores de los nodos en un RBT
enum color {RED, BLACK, DOUBLE_BLACK};

// Estructura de un nodo de un RBT
typedef struct Node {
    int data;               // Dato del nodo
    enum color color;       // Color del nodo
    struct Node* left;      // Puntero al hijo izquierdo
    struct Node* right;     // Puntero al hijo derecho
    struct Node* parent;    // Puntero al padre
} TreeNode;

// Variable global que apunta a la raíz del RBT
TreeNode* T = NULL;

/**************** BST functions ****************/

void BST_show_pre_order(TreeNode* T) {
    if( T == NULL ) return;
    cout << T->data << " ";
    BST_show_pre_order(T->left);
    BST_show_pre_order(T->right);
}

void BST_show_post_order(TreeNode* T) {
    if( T == NULL ) return;
    BST_show_post_order(T->left);
    BST_show_post_order(T->right);
    cout << T->data << " ";
}

void BST_show_in_order(TreeNode* T) {
    if( T == NULL ) return;
    BST_show_in_order(T->left);
    cout << T->data << " ";
    BST_show_in_order(T->right);
}

void BST_show(TreeNode* T, enum mode modo) {
    cout << "[ ";
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
    cout << "]\n";
}

void BST_show_with_levels(TreeNode* T, int level) {
    cout << [level](){ string r = ""; for(int i = 0; i < level; ++i) r+="   "; return r; }() << ((T == NULL)?"-":to_string(T->data)) << "\n";
    if( T == NULL ) return;
    BST_show_with_levels(T->left, level + 1);
    BST_show_with_levels(T->right, level + 1);
}

TreeNode* create_node(int n) {
    TreeNode* node = new TreeNode();
    node->data = n;
    node->color = RED;  //Esta es la única adición, ya que los nodos
                        //de un RBT inician de color RED
    node->left = node->right = node->parent = NULL;
    
    return node;
}

bool BST_search(TreeNode* T, int value) {
    if( T == NULL ) return false;
    else
        if( value == T->data ) return true;
        else
            if( value < T->data )
                return BST_search(T->left, value);
            else
                return BST_search(T->right, value);
}

TreeNode* BST_get(TreeNode* T, int value) {
    if( T == NULL ) return NULL;
    else
        if( value == T->data ) return T;
        else
            if( value < T->data )
                return BST_get(T->left, value);
            else
                return BST_get(T->right, value);
}

enum side check_child_side(TreeNode* T) {
    if( T->parent == NULL ) return NONE;
    if( T->parent->left == T ) return LEFT;
    else return RIGHT;
}

TreeNode* BST_extractIOS(TreeNode* T) {
    if( T->left == NULL ) return T;
    return BST_extractIOS(T->left);
}

void BST_destroy(TreeNode* T) {
    if( T == NULL ) return;
    BST_destroy(T->left);
    BST_destroy(T->right);
    delete T;
}

/**************** Updated BST functions ****************/
/*
    - La función BST_insert fue adaptada para manejar la
      variable global T que apunta a la raíz del RBT.
    - La función BST_delete fue adaptada para retornar la
      dirección del hijo único del nodo eliminado (de acuerdo
      a como lo visualiza el algoritmo de borrado de nodos en
      un RBT). Esto permitió además unificar los casos 2.1 y
      2.2 en un solo bloque de código.
*/

/* Función auxiliar para insertar un nuevo nodo */
void BST_insert_aux(TreeNode* T, int value) {
    //Se verifica si debe insertarse en el subárbol
    //izquierdo o el derecho
    if( value <= T->data ) {
        //Se verifica si el hijo izquierdo está vacante
        if( T->left == NULL ) {
            //Se crea el nuevo nodo como el hijo izquierdo
            //del nodo actual
            T->left = create_node(value);
            //El padre del nuevo nodo es el nodo actual
            T->left->parent = T;
        }
        //De lo contrario, se envía el subárbol izquierdo
        //en recursión
        else BST_insert_aux(T->left, value);
    } else {
        //Se verifica si el hijo derecho está vacante
        if( T->right == NULL ) {
            //Se crea el nuevo nodo como el hijo derecho
            //del nodo actual
            T->right = create_node(value);
            //El padre del nuevo nodo es el nodo actual
            T->right->parent = T;
        }
        //De lo contrario, se envía el subárbol derecho
        //en recursión
        else BST_insert_aux(T->right, value);
    }
}

/* Función principal para insertar un nuevo nodo */
void BST_insert(int value) {
    //Si el árbol está vacío, el nuevo nodo será la raíz
    if( T == NULL ) T = create_node(value); //Se crea el nuevo nodo
    //De lo contrario, se delega la inserción a la función auxiliar
    else BST_insert_aux(T, value);
}

/* 
    Función para borrar un nodo que contenga el dato indicado
    Se asume que el dato sí se encuentra dentro del árbol.
    (Es responsabilidad del usuario verificarlo antes de borrar)
*/
TreeNode* BST_delete(int value) {
    //Se extrae el nodo a eliminar
    TreeNode* dead = BST_get(T, value);

    //Se procede a evaluar cuál caso de borrado corresponde.
    //Se encierra el bloque en un DO-WHILE ya que es posible que
    //el proceso reinicie (aunque se sabe que si ocurre, solo
    //ocurriría una vez)
    do{
        //Caso 1: Los dos hijos del nodo a borrar son nulos
        if( dead->left == NULL && dead->right == NULL ) {
            //Si el padre no es nulo, se debe actualizar que uno
            //de sus hijos será eliminado
            if( dead->parent != NULL)
                //Se verifica si el nodo a eliminar es el hijo izquierdo de su padre
                if( check_child_side(dead) == LEFT )
                    dead->parent->left = NULL;  //Se registra la eliminación en el padre
                //o si es el hijo derecho de su padre
                else dead->parent->right = NULL;  //Se registra la eliminación en el padre
            //Si el padre es nulo, entonces el nodo a eliminar es
            //la raíz, por lo que se debe setear T a NULL
            else T = NULL;

            //Se elimina el nodo
            delete dead;
            //Se retorna NULL (NIL) como el hijo único del nodo eliminado
            return NULL;
        }

        //Caso 2: Solo un hijo del nodo a borrar no es nulo
        if( (dead->left != NULL && dead->right == NULL) || ( dead->left == NULL && dead->right != NULL )) {
            //Se extrae la dirección del hijo único (no nulo) del nodo a eliminar
            TreeNode* h = ((dead->left != NULL)?dead->left:dead->right);
            //Si el padre no es nulo, se debe actualizar que uno
            //de sus hijos será eliminado
            if( dead->parent != NULL){
                //Se verifica si el nodo a eliminar es el hijo izquierdo de su padre
                if( check_child_side(dead) == LEFT )
                    dead->parent->left = h;  //Se registra la eliminación en el padre
                //o si es el hijo derecho de su padre
                else dead->parent->right = h;  //Se registra la eliminación en el padre
                //El nuevo padre del hijo único es el padre del nodo a eliminar
                h->parent = dead->parent;
            }
            //Si el padre es nulo, entonces el nodo a eliminar es
            //la raíz, por lo que se debe setear T a NULL
            else T = h;
            
            //Se elimina el nodo
            delete dead;
            //Se retorna el hijo único
            return h;
        }

        //Caso 3: Los dos hijos del nodo a borrar son no nulos
        //Se encuentra el IN-ORDER Sucessor del nodo a eliminar
        TreeNode* ios = BST_extractIOS(dead->right);
        //Se intercambia los datos del nodo a borrar y del IOS
        swap(dead->data, ios->data);
        //El nuevo nodo a eliminar es el IOS
        dead = ios;
    } while(true); //Acá se reinicia el proceso, pero se sabe que irá a parar ya sea en el Caso 1 o en el Caso 2
}

/**************** Rotation functions ****************/

/* 
    Función para ejecutar la Rotación a la Izquierda de los nodos A y B
    Se asume que A es el padre de B
*/
void leftRotation(TreeNode* A, TreeNode* B) {
    /* Corte y Reconexión de la parte superior */

    //Se verifica si A tiene padre
    if( A->parent != NULL ) {
        //Se verifica de qué lado de su padre se encuentra A
        if( check_child_side(A) == LEFT )
            //B será el nuevo hijo izquierdo del padre de A
            A->parent->left = B;
        else
            //B será el nuevo hijo derecho del padre de A
            A->parent->right = B;
    }
    //Si A no tiene padre, A es la raíz del árbol,
    //y después de rotar la nueva raíz será B
    else T = B;
    
    //El nuevo padre de B es el padre de A
    B->parent = A->parent;
    
    /* Corte y Reconexión del "Hijo Huérfano" */

    //El nuevo hijo derecho de A es el hijo izquierdo de B
    A->right = B->left;
    //Si este "huérfano reubicado" no es nulo, se actualiza
    //que su nuevo padre es A
    if( A->right != NULL ) A->right->parent = A;

    /* Corte y reconexión de los nodos involucrados */

    //El nuevo hijo izquierdo de B es A
    B->left = A;
    //El nuevo padre de A es B
    A->parent = B;
}

/* 
    Función para ejecutar la Rotación a la Derecha de los nodos A y B
    Se asume que A es el padre de B
*/
void rightRotation(TreeNode* A, TreeNode* B) {
    /* Corte y Reconexión de la parte superior */

    //Se verifica si A tiene padre
    if( A->parent != NULL ) {
        //Se verifica de qué lado de su padre se encuentra A
        if( check_child_side(A) == LEFT )
            //B será el nuevo hijo izquierdo del padre de A
            A->parent->left = B;
        else
            //B será el nuevo hijo derecho del padre de A
            A->parent->right = B;
        //El nuevo padre de B es el padre de A
        B->parent = A->parent;
    }
    //Si A no tiene padre, A es la raíz del árbol,
    //y después de rotar la nueva raíz será B
    else T = B;
    
    /* Corte y Reconexión del "Hijo Huérfano" */

    //El nuevo hijo izquierdo de A es el hijo derecho de B
    A->left = B->right;
    //Si este "huérfano reubicado" no es nulo, se actualiza
    //que su nuevo padre es A
    if( A->left != NULL ) A->left->parent = A;

    /* Corte y reconexión de los nodos involucrados */

    //El nuevo hijo derecho de B es A
    B->right = A;
    //El nuevo padre de A es B
    A->parent = B;
}

/**************** RBT functions ****************/

/* 
    Función para mostrar el contenido de un RBT de forma jerárquica,
    es decir, dejando explícito cuáles son los hijos de cada nodo y
    a que nivel del árbol se encuentran.
    Esta función hace el recorrido estrictamente en PRE-ORDER.
*/
void RBT_show_with_levels(TreeNode* T, int level) {
    /*
        La siguiente línea coloca el contenido del nodo actual de la siguiente manera:
        - Coloca primero una cantidad de espacio equivalente al nivel actual de
          profundidad en el árbol (indicado por el parámetro level).
        - Coloca después el dato del nodo actual. Si el nodo actual es un nodo nulo,
          coloca entonces un '-' para indicarlo.
        - Por último, coloca una 'B' si el color del nodo actual es BLACK, y coloca una
          'R' si el color del nodo actual es RED.
    */
    cout << [level](){ string r = ""; for(int i = 0; i < level; ++i) r+="   "; return r; }() << ((T == NULL)?"-B":to_string(T->data)+((T->color == RED)?"R":"B")) << "\n";
    //Si el árbol está vacío, ya se indicó en la línea anterior, no hay nada más que hacer
    if( T == NULL ) return;
    //Se muestra el subárbol izquierdo
    RBT_show_with_levels(T->left, level + 1);
    //Se muestra el subárbol derecho
    RBT_show_with_levels(T->right, level + 1);
}

/* Función auxiliar para insertar un nuevo nodo en un RBT  */
void RBT_fixInsertion(TreeNode* n) {
    /* Escenario 1 */
    
    //n es root
    if( T == n ) {
        //n se hace BLACK
        n->color = BLACK;

        //Se termina el proceso
        return;
    }

    /* Escenario 2 */

    //p es BLACK
    //Simplemente se termina el proceso
    if( n->parent->color == BLACK ) return;

    /* Escenario 3 */
    //p es RED

    //Se preparan los demás protagonistas
    TreeNode* p = n->parent;
    TreeNode* g = p->parent;
    TreeNode* u = NULL;
    //Se verifica que el abuelo exista, para poder
    //definir a u, de lo contrario se queda en NULL
    if( g != NULL )
        //Si p es el hijo izquierdo de g, u es el hijo derecho
        if( check_child_side(p) == LEFT ) u = g->right;
        //Si p es el hijo derecho de g, u es el hijo izquierdo
        else u = g->left;

    //u es BLACK
    if( u == NULL || u->color == BLACK ) {
        //n, p y g forman un triángulo
        //Esto ocurre cuando n es hijo de p al lado opuesto del que p es hijo de g
        if( check_child_side(n) != check_child_side(p) ) {
            //Rotar p y n
            //Si n es hijo izquierdo de p, es Right Rotation
            if( check_child_side(n) == LEFT ) rightRotation(p,n);
            //Si n es hijo derecho de p, es Left Rotation
            else leftRotation(p,n);
            //p se hace el nuevo n
            n = p;
            //Se actualiza p como el padre del nuevo n
            p = n->parent;
            //g y u se quedan igual
        }

        /*
            El bloque anterior se encuentra antes del bloque siguiente,
            ya que cuando ocurre que n, p y g están en triángulo, el
            proceso continúa precisamente con el escenario en el que
            están en línea recta.
            Cuando n, p y g estén en línea recta desde un inicio, el
            bloque anterior simplemente no se ejecutará.
        */

        //n, p y g forman una línea recta
        //Rotar g y p
        //Si p es hijo izquierdo de g, es Right Rotation
        if( check_child_side(p) == LEFT ) rightRotation(g,p);
        //Si p es hijo derecho de g, es Left Rotation
        else leftRotation(g,p);
        //p se hace BLACK
        p->color = BLACK;
        //g se hace RED
        //Se verifica primero que g no sea nulo
        if( g != NULL) g->color = RED;
        //Se termina el proceso
    }
    //u es RED
    else {
        //p se hace BLACK
        p->color = BLACK;
        //u se hace BLACK
        //Se verifica primero que u no sea nulo
        if( u != NULL ) u->color = BLACK;
        //g se hace RED
        //Se verifica primero que g no sea nulo
        if( g != NULL ) g->color = RED;
        //g se hace el nuevo n y se reinicia el proceso
        //Esto se hace por recursión enviando g como el nuevo n
        RBT_fixInsertion(g);
    }
}

/*
    Función para insertar un nuevo nodo en un RBT
    Se asume que no hay datos repetidos en el árbol.
*/
void RBT_insert(int value) {
    //Se inserta el nuevo nodo como en un BST
    BST_insert(value);
    //Se extrae el nuevo nodo insertado
    TreeNode* n = BST_get(T, value);
    //Se procede con el algoritmo correspondiente
    //a inserción en RBTs
    RBT_fixInsertion(n);
}

/*
    Función para eliminar un nodo en un RBT
    Se asume que no hay datos repetidos en el árbol.
*/
void RBT_delete(int value) {
    //Se extrae el nodo a eliminar
    TreeNode* d = BST_get(T, value);
    //Se define p, el padre del nodo a eliminar
    TreeNode* p = d->parent;
    //Se extrae de qué lado de su padre está el nodo a eliminar
    enum side deadSide = check_child_side(d);
    //Se extrae el color del nodo a eliminar
    enum color deadColor = d->color;
    //Se prepara s, el hermano del nodo a eliminar
    TreeNode* s = NULL;
    //Se verifica si p no es nulo, si lo es, s se quedará en nulo también
    if( p != NULL )
        //Si nodo a eliminar está a la izquierda de p, s es el hijo derecho de p
        if( deadSide == LEFT ) s = p->right;
        //Si nodo a eliminar está a la derecha de p, s es el hijo izquierdo de p
        else s = p->left;

    //Se procede a eliminar el nodo como en un BST
    //Se obtendrá de retorno la dirección del hijo único del nodo eliminado (h)
    /*
        NOTA: BST_delete se encarga "involuntariamente" de los siguientes pasos:
                - Borrar d
                - h toma el lugar de d
              Esto es válido en cualquier escenario de borrado de nodos en RBT
              donde aparezcan.
    */
    TreeNode* h = BST_delete(value);

    /* Escenario 1 */

    //d es RED o h es RED
    //deadColor contiene el color del nodo eliminado.
    //Se verifica si h no es nulo, en cuyo caso tendría un color BLACK
    if( deadColor == RED || (h != NULL && h->color == RED) ) {
        //h se hace BLACK
        //Se verifica primero que h no sea nulo
        if( h != NULL) h->color = BLACK;
        //Se termina el proceso
        return;
    }

    /* Escenario 2 */
    //d es BLACK y h es BLACK

    //h se hace DOUBLE_BLACK
    //Se verifica que h no sea nulo
    if( h != NULL) h->color = DOUBLE_BLACK;
    
    /*
        Se encierra todo lo siguiente en un DO-WHILE debido a los
        escenarios que retroceden en el procedimiento.
        Se sabe que eventualmente el proceso terminará.
    */
    do{
        /* Escenario 2.1 */
        
        //h es root
        if( T == h ) {
            //h se hace BLACK
            //Se verifica primero que h no sea nulo
            if( h != NULL) h->color = BLACK;
            //Se termina el proceso
            return;
        }

        /* Escenario 2.2 */

        //s es BLACK
        if( s->color == BLACK ) {
            //los dos n son BLACK
            //Todo n que sea nulo es BLACK.
            if( (s->left == NULL || s->left->color == BLACK) && (s->right == NULL || s->right->color == BLACK) ) {
                //h se hace BLACK
                //Se verifica primero que h no sea nulo
                if( h != NULL) h->color = BLACK;
                //s se hace RED
                s->color = RED;

                /* Se procede a checar el color de p */

                //p es BLACK
                if( p->color == BLACK ) {
                    //p se hace DOUBLE_BLACK
                    p->color = DOUBLE_BLACK;
                    //p se hace el nuevo h
                    h = p;
                    //Se actualiza p con el padre del nuevo h
                    p = h->parent;
                    //Se actualiza s con el hermano del nuevo h
                    //Si h está a la izquierda de p, s es el hijo derecho de p
                    if( check_child_side(h) == LEFT) s = p->right;
                    //Si h está a la derecha de p, s es el hijo izquierdo de p
                    else s = p->left;

                    //Se regresa al punto después de que h se hizo DOUBLE_BLACK
                    continue;
                }
                //p es RED
                else {
                    //p se hace BLACK
                    p->color = BLACK;

                    //Se termina el proceso
                    break;
                }
            }
            //al menos un n es RED
            //Si ambos son rojos, se tomará como n el de la izquierda por defecto.
            //Puede añadirse una verificación adicional para que cuando los dos sean rojos,
            //se seleccione el que provoque menor trabajo.
            else {
                //Se prepara n
                TreeNode* n = NULL;
                //Se verifica cuál de los dos hijos de s es RED, para apuntar n hacia él
                if( s->left != NULL && s->left->color == RED ) n = s->left;
                else n = s->right;

                //n, s y p forman un triángulo
                //Esto ocurre cuando n es hijo de s al lado opuesto del que s es hijo de p
                if( check_child_side(n) != check_child_side(s) ) {
                    //Intercambiar colores de s y n
                    swap(s->color, n->color);
                    //Rotar s y n
                    //Si n es hijo izquierdo de s, es Right Rotation
                    if( check_child_side(n) == LEFT ) rightRotation(s,n);
                    //Si n es hijo derecho de s, es Left Rotation
                    else leftRotation(s,n);
                    //s se hace el nuevo n
                    n = s;
                    //Se actualiza s con el padre del nuevo n
                    s = n->parent;
                    //p se mantiene igual
                }

                /*
                    El bloque anterior se encuentra antes del bloque siguiente,
                    ya que cuando ocurre que n, s y p están en triángulo, el
                    proceso continúa precisamente con el escenario en el que
                    están en línea recta.
                    Cuando n, s y p estén en línea recta desde un inicio, el
                    bloque anterior simplemente no se ejecutará.
                */

                //n, s y p forman una línea recta
                //Intercambiar colores de p y s
                swap(p->color, s->color);
                //Rotar p y s
                //Si s es hijo izquierdo de p, es Right Rotation
                if( check_child_side(s) == LEFT ) rightRotation(p,s);
                //Si s es hijo derecho de p, es Left Rotation
                else leftRotation(p,s);
                //p se hace BLACK
                p->color = BLACK;
                //n se hace BLACK
                n->color = BLACK;
                //h se hace BLACK
                //Se verifica primero que no sea nulo
                if( h != NULL) h->color = BLACK;

                //Se termina el proceso
                break;
            }
        }

        /* Escenario 2.3 */

        //s es RED
        else {
            //Intercambiar colores de p y s
            swap(p->color, s->color);
            //Rotar p y s
            //Si s es hijo izquierdo de p, es Right Rotation
            if( check_child_side(s) == LEFT ){
                rightRotation(p,s);
                //Se actualiza s con el hijo izquierdo de p
                //(el nuevo hermano de h después de rotar)
                s = p->left;
            }
            //Si s es hijo derecho de p, es Left Rotation
            else{
                leftRotation(p,s);
                //Se actualiza s con el hijo derecho de p
                //(el nuevo hermano de h después de rotar)
                s = p->right;
            }

            //Se regresa al punto después de que h se hizo DOUBLE_BLACK
            continue;
        }
    }while(true);
}


/********** Main *********/

int main() {

    /*
        Los bloques de pruebas en este Main son mutuamente
        excluyentes, si se desea utilizar uno de ellos, debe
        descomentarse y comentar los demás.

        El bloque que inicia descomentado por defecto es el de
        borrado de nodos en RBT.
    */

/***** Prueba de inserción y borrado en BST *****/

    /*
    BST_insert(50);
    BST_insert(10);
    BST_insert(0);
    BST_insert(60);
    BST_insert(55);
    BST_show_with_levels(T, 0);
    
    // Los siguientes ejemplos de borrado son mutuamente excluyentes,
    // para probar uno, descomentarlo y comentar los otros.

    //BST_delete(55);
    //BST_delete(10);
    BST_delete(50);

    BST_show_with_levels(T, 0);
    */
    
/***** Prueba de inserción en RBT *****/

    /*
    RBT_insert(50);
    RBT_show_with_levels(T, 0);
    RBT_insert(40);
    RBT_show_with_levels(T, 0);
    RBT_insert(30);
    RBT_show_with_levels(T, 0);
    RBT_insert(35);
    RBT_show_with_levels(T, 0);
    RBT_insert(33);
    RBT_show_with_levels(T, 0);
    */

/***** Prueba de borrado de la raíz en RBT *****/

    /*
    RBT_insert(50);
    RBT_delete(50);
    RBT_show_with_levels(T, 0);
    */
    
/***** Pruebas de borrado de BST *****/

    int values[18] = {20,12,40,10,15,30,45,5,11,13,18,28,35,2,6,14,31,38};
    for(int i = 0; i < 18; ++i)
        RBT_insert(values[i]);
    //RBT_show_with_levels(T, 0);

    // Los siguientes ejemplos de borrado son mutuamente excluyentes,
    // para probar uno, descomentarlo y comentar los otros.

    //Caso: d es RED, h es BLACK
    RBT_delete(14);

    //Caso: d es BLACK, h es RED
    //RBT_delete(13);

    //Caso: d es BLACK, h es BLACK, s es BLACK, el n que es RED está en línea recta con s y p
    //RBT_delete(6); RBT_delete(11);

    //Caso: d es BLACK, h es BLACK, s es BLACK, el n que es RED está en triángulo con s y p
    //RBT_delete(18);

    //Caso: d es BLACK, h es BLACK, s es BLACK, los dos n son BLACK, p es BLACK
    //RBT_delete(2); RBT_delete(6); RBT_delete(5); RBT_delete(11); RBT_delete(13); RBT_delete(18); RBT_delete(14); RBT_delete(15);

    //Caso: d es BLACK, h es BLACK, s es BLACK, los dos n son BLACK, p es RED
    //RBT_delete(2); RBT_delete(6); RBT_delete(5);

    //Caso: d es BLACK, h es BLACK, s es RED
    //RBT_delete(45);
    
    RBT_show_with_levels(T, 0);


/**************************************************************/
/***** Destrución del árbol antes de terminar el programa *****/

    BST_destroy(T);


    return 0;
}

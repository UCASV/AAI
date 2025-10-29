#include <bits/stdc++.h>
using namespace std;

enum side {NONE, LEFT, RIGHT};
enum mode {PRE, IN, POST};
enum color {RED, BLACK, DOUBLE_BLACK};

typedef struct Node {
    int data;
    enum color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} TreeNode;

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
    node->color = RED;
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

void BST_insert_aux(TreeNode* T, int value) {
    if( value <= T->data ) {
        if( T->left == NULL ) {
            T->left = create_node(value);
            T->left->parent = T;
        } else BST_insert_aux(T->left, value);
    } else {
        if( T->right == NULL ) {
            T->right = create_node(value);
            T->right->parent = T;
        } else BST_insert_aux(T->right, value);
    }
}

void BST_insert(int value) {
    if( T == NULL ) T = create_node(value);
    else BST_insert_aux(T, value);
}

TreeNode* BST_delete(int value) {
    TreeNode* dead = BST_get(T, value);
    do{
        //Caso 1
        if( dead->left == NULL && dead->right == NULL ) {
            if( dead->parent != NULL)
                if( check_child_side(dead) == LEFT )
                    dead->parent->left = NULL;
                else dead->parent->right = NULL;
            else T = NULL;

            delete dead;
            return NULL;
        }

        //Caso 2
        if( (dead->left != NULL && dead->right == NULL) || ( dead->left == NULL && dead->right != NULL )) {
            TreeNode* h = ((dead->left != NULL)?dead->left:dead->right);
            if( dead->parent != NULL){
                if( check_child_side(dead) == LEFT ) dead->parent->left = h;
                else dead->parent->right = h;
                h->parent = dead->parent;
            } else T = h;

            delete dead;
            return h;
        }

        //Caso 3
        TreeNode* ios = BST_extractIOS(dead->right);
        swap(dead->data, ios->data);
        dead = ios;
    } while(true);
}

/**************** Rotation functions ****************/

void leftRotation(TreeNode* A, TreeNode* B) {
    if( A->parent != NULL ) {
        if( check_child_side(A) == LEFT ){
            A->parent->left = B;
        } else {
            A->parent->right = B;
        }
        B->parent = A->parent;
    } else T = B;
    
    A->right = B->left;
    if( A->right != NULL ) A->right->parent = A;

    B->left = A;
    A->parent = B;
}

void rightRotation(TreeNode* A, TreeNode* B) {
    if( A->parent != NULL ) {
        if( check_child_side(A) == LEFT ){
            A->parent->left = B;
        } else {
            A->parent->right = B;
        }
        B->parent = A->parent;
    } else T = B;
    
    A->left = B->right;
    if( A->left != NULL ) A->left->parent = A;

    B->right = A;
    A->parent = B;
}

/**************** RBT functions ****************/

void RBT_show_with_levels(TreeNode* T, int level) {
    cout << [level](){ string r = ""; for(int i = 0; i < level; ++i) r+="   "; return r; }() << ((T == NULL)?"-B":to_string(T->data)+((T->color == RED)?"R":"B")) << "\n";
    if( T == NULL ) return;
    RBT_show_with_levels(T->left, level + 1);
    RBT_show_with_levels(T->right, level + 1);
}

void RBT_fixInsertion(TreeNode* n) {
    if( T == n ) {
        n->color = BLACK;
        return;
    }

    if( n->parent->color == BLACK ) return;

    TreeNode* p = n->parent;
    TreeNode* g = p->parent;
    TreeNode* u = NULL;
    if( g != NULL )
        if( check_child_side(p) == LEFT ) u = g->right;
        else u = g->left;
    
    if( u == NULL || u->color == BLACK ) {
        if( check_child_side(n) != check_child_side(p) ) {
            if( check_child_side(n) == LEFT ) rightRotation(p,n);
            else leftRotation(p,n);
            n = p;
            p = n->parent;
            //g y u se quedan igual
        }
        if( check_child_side(p) == LEFT ) rightRotation(g,p);
        else leftRotation(g,p);
        p->color = BLACK;
        if( g != NULL) g->color = RED;
    } else {
        p->color = BLACK;
        if( u != NULL ) u->color = BLACK;
        if( g != NULL ) g->color = RED;
        RBT_fixInsertion(g);
    }
}

void RBT_insert(int value) {
    BST_insert(value);
    TreeNode* n = BST_get(T, value);
    RBT_fixInsertion(n);
}

void RBT_delete(int value) {
    TreeNode* d = BST_get(T, value);
    TreeNode* p = d->parent;
    enum side deadSide = check_child_side(d);
    enum color deadColor = d->color;    
    TreeNode* s = NULL;
    if( p != NULL )
        if( deadSide == LEFT ) s = p->right;
        else s = p->left;

    TreeNode* h = BST_delete(value);

    if( deadColor == RED || (h != NULL && h->color == RED) ) {
        if( h != NULL) h->color = BLACK;
        return;
    }

    if( h != NULL) h->color = DOUBLE_BLACK;
    
    do{
        if( T == h ) {
            if( h != NULL) h->color = BLACK;
            return;
        }

        if( s == NULL || s->color == BLACK ) {
            if( (s == NULL) || ((s->left == NULL || s->left->color == BLACK) && (s->right == NULL || s->right->color == BLACK)) ) {
                if( h != NULL) h->color = BLACK;
                if( s != NULL ) s->color = RED;
                if( p->color == BLACK ) {
                    p->color = DOUBLE_BLACK;
                    h = p;
                    p = h->parent;
                    if( check_child_side(h) == LEFT) s = p->right;
                    else s = p->left;
                    continue;
                } else {
                    p->color = BLACK;
                    break;
                }
            } else {
                TreeNode* n = NULL;
                if( s->left != NULL && s->left->color == RED ) n = s->left;
                else n = s->right;

                if( check_child_side(n) != check_child_side(s) ) {
                    swap(s->color, n->color);
                    if( check_child_side(n) == LEFT ) rightRotation(s,n);
                    else leftRotation(s,n);
                    n = s;
                    s = n->parent;
                }
                swap(p->color, s->color);
                if( check_child_side(s) == LEFT ) rightRotation(p,s);
                else leftRotation(p,s);
                p->color = BLACK;
                n->color = BLACK;
                if( h != NULL) h->color = BLACK;
                break;
            }
        } else {
            swap(p->color, s->color);
            if( check_child_side(s) == LEFT ){
                rightRotation(p,s);
                s = p->left;
            } else{
                leftRotation(p,s);
                s = p->right;
            }
            continue;
        }
    }while(true);
}

int main() {
    /*
    BST_insert(50);
    BST_insert(10);
    BST_insert(0);
    BST_insert(60);
    BST_insert(55);
    BST_show_with_levels(T, 0);
    //BST_delete(55);
    //BST_delete(10);
    BST_delete(50);
    BST_show_with_levels(T, 0);
    */
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
    /*
    RBT_insert(50);
    RBT_delete(50);
    RBT_show_with_levels(T, 0);
    */
    
    int values[18] = {20,12,40,10,15,30,45,5,11,13,18,28,35,2,6,14,31,38};
    for(int i = 0; i < 18; ++i)
        RBT_insert(values[i]);
    //RBT_show_with_levels(T, 0);
    //RBT_delete(14);
    //RBT_delete(13);
    //RBT_delete(6);RBT_delete(11);
    //RBT_delete(18);
    //RBT_delete(2); RBT_delete(6); RBT_delete(5); RBT_delete(11); RBT_delete(13); RBT_delete(18); RBT_delete(14); RBT_delete(15);
    //RBT_delete(2); RBT_delete(6); RBT_delete(5);
    RBT_delete(45);
    RBT_show_with_levels(T, 0);
    
    
    BST_destroy(T);

    return 0;
}

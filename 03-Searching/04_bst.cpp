#include <bits/stdc++.h>
using namespace std;

enum side {LEFT, RIGHT};
enum mode {PRE, IN, POST};

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} TreeNode;

typedef int entero;

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
    if( T == NULL ) return;
    cout << [level](){ string r = ""; for(int i = 0; i < level; ++i) r+="   "; return r; }() << T->data << "\n";
    BST_show_with_levels(T->left, level + 1);
    BST_show_with_levels(T->right, level + 1);
}

TreeNode* create_node(int n) {
    TreeNode* node = new TreeNode();
    node->data = n;
    node->left = node->right = node->parent = NULL;
    
    return node;
}

TreeNode* BST_insert(TreeNode* T, int value) {
    if( T == NULL ) T = create_node(value);
    else
        if( value <= T->data ) {
            T->left = BST_insert(T->left, value);
            T->left->parent = T;
        } else {
            T->right = BST_insert(T->right, value);
            T->right->parent = T;
        }
    return T;
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
    if( T->parent->left == T ) return LEFT;
    else return RIGHT;
}

TreeNode* BST_extractIOS(TreeNode* T) {
    if( T->left == NULL ) return T;
    return BST_extractIOS(T->left);
}

void BST_delete(TreeNode* T, int value) {
    if( BST_search(T,value) ) {
        TreeNode* dead = BST_get(T, value);
        do{
            //Caso 1
            if( dead->left == NULL && dead->right == NULL ) {
                if( check_child_side(dead) == LEFT )
                    dead->parent->left = NULL;
                else dead->parent->right = NULL;

                delete dead;
                return;
            }

            //Caso 2.1
            if( dead->left != NULL && dead->right == NULL ) {
                if( check_child_side(dead) == LEFT ) {
                    dead->parent->left = dead->left;
                    dead->left->parent = dead->parent;
                } else {
                    dead->parent->right = dead->left;
                    dead->left->parent = dead->parent;
                }

                delete dead;
                return;
            }

            //Caso 2.2
            if( dead->left == NULL && dead->right != NULL ) {
                if( check_child_side(dead) == LEFT ) {
                    dead->parent->left = dead->right;
                    dead->right->parent = dead->parent;
                } else {
                    dead->parent->right = dead->right;
                    dead->right->parent = dead->parent;
                }

                delete dead;
                return;
            }

            //Caso 3
            TreeNode* ios = BST_extractIOS(dead->right);
            swap(dead->data, ios->data);
            dead = ios;
        } while(true);
    } else cout << "El dato " << value << " no está en el BST.\n";
}

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

    return 0;
}

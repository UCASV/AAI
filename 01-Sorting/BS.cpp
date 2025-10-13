#include <bits/stdc++.h>
using namespace std;

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

bool binary_search(int A[], int n, int value) {
    bool ans = false;
    
    int p = 0;
    int r = n - 1;

    quicksort(A, 0, n - 1);

    while(p <= r) {
        int q = (p + r) / 2;
        if( value == A[q] ) {
            ans = true;
            break;
        } else {
            if( value < A[q] ) {
                r = q - 1;
            } else {
                p = q + 1;
            }
        }
    }

    return ans;
}

bool binary_search_recursive_aux(int A[], int p, int r, int value) {
    if( p <= r ){
        int q = (p + r) / 2;
        if( value == A[q] ) return true;
        else
            if( value < A[q] )
                return binary_search_recursive_aux(A, p, q - 1, value);
            else
                return binary_search_recursive_aux(A, q + 1, r, value);
    }

    return false;
}

bool binary_search_recursive(int A[], int n, int value) {
    quicksort(A, 0, n - 1);

    return binary_search_recursive_aux(A, 0, n - 1, value);
}

int main() {

    return 0;
}
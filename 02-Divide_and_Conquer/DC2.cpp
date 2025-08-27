#include <bits/stdc++.h>
using namespace std;

//Naive approach
//Brute Force approach
int max_range_sum(int A[], int l, int r){
    //Se inicializa la variable que contendrá la suma máxima
    //Se inicializa con un valor que nunca ganará una comparación
    //que busque el dato más grande
    int max_sum = INT_MIN;

    //Se recorre el arreglo de principio (l) a fin (r)
    for(int i = l; i <= r; i++){
        //Se inicia un acumulador para el subarreglo actual
        int sum = 0;

        //Se recorre desde la posición actual del recorrido principal
        //y hasta el final del arreglo
        for(int j = i; j <= r; j++){
            //El subarreglo actual queda definido como [i,j]
            //Se actualiza la suma para el subarreglo actual
            sum += A[j];

            //Se verifica si la suma actual sobrepasa a la actual
            //suma máxima
            max_sum = max(max_sum, sum);
        }
    }

    //Se retorna la suma máxima encontrada
    return max_sum;
}

//Divide & Conquer

int crossSum(int A[], int l, int m, int r){
    //Se inicializan las variables que contendrán la suma máxima
    //de la mitad izquierda y la de la mitad derecha.
    //Se inicializan ambas con un valor que nunca ganará una comparación
    //que busque el dato más grande
    int maxLeft = INT_MIN;
    int maxRight = INT_MIN;
    
    /*** Mitad Izquierda ***/
    //Se inicializa la sumatoria en 0
    int sum = 0;
    //Se recorre desde la mitad hacia la izquierda
    for(int i = m; i >= l; i--){
        //Cada vez que se encuentra un dato se añade a la sumatoria total
        sum += A[i];

        //Si la sumatoria actual es más grande que la mayor registrada
        //hasta el momento para la mitad izquierda, se actualiza
        if(sum > maxLeft)
            maxLeft = sum;
    }

    /*** Mitad Derecha ***/
    //Se reinicia la sumatoria en 0
    sum = 0;
    //Se recorre desde la mitad+1 hacia la derecha
    for(int i = m + 1; i <= r; i++){
        //Cada vez que se encuentra un dato se añade a la sumatoria total
        sum += A[i];

        //Si la sumatoria actual es más grande que la mayor registrada
        //hasta el momento para la mitad derecha, se actualiza
        if(sum > maxRight)
            maxRight = sum;
    }

    //La suma del total más grande obtenible yendo desde la mitad hacia la izquierda
    //con el total más grande obtenible yendo desde la mitad hacia la derecha
    //corresponde a la suma más grande posible de todos los 'Cross Subarrays'
    return maxLeft + maxRight;
}

int max_range_sum_DC(int A[], int l, int r){
    //Etapa III: Caso trivial
    //Acá es tener un subarreglo de longitud 1
    if(l == r) return A[l];

    //Etapa I: Dividir el problema
    //Acá se parte el arreglo a la mitad
    int m = (l + r) / 2;

    //Etapa II: Continuar dividiendo el problema (recursión)
    //Acá se envía a recursión cada mitad del arreglo
    int leftMaxSum = max_range_sum_DC(A, l, m);
    int rightMaxSum = max_range_sum_DC(A, m + 1, r);

    //Etapa IV: Mezclar las soluciones y retornar resultado
    //Acá consiste en dos pasos:

    //Paso 1: Encontrar la suma máxima de todos los
    //'Cross Subarrays'
    int crossMaxSum = crossSum(A, l, m, r);

    //Paso 2: Determinar el ganador entre la respuesta de la
    //mitad izquierda, la respuesta de la mitad derecha, y la
    //respuesta de los 'Cross Subarrays'
    return max(max(leftMaxSum, rightMaxSum), crossMaxSum);
}

int main(){
    //Ejemplo 1
    //int n = 8;
    //int A[n] = {2, -4, 3, -1, 2, -4, -1, 6};

    //Ejemplo 2
    //int n = 8;
    //int A[n] = {4, -2, -8, 5, -2, 7, 1, -3};

    //Ejemplo 3
    int n = 10;
    int A[n] = {3, -1, -2, 5, -3, 2, 4, -6, 1, 3};

    cout << max_range_sum(A, 0, n-1) << "\n";
    cout << max_range_sum_DC(A, 0, n-1) << "\n";

    return 0;
}

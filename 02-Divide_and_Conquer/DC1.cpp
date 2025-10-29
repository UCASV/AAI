#include <bits/stdc++.h>
using namespace std;

//Naive approach / Brute Force approach
double power_function(double a, int b){
    //Acumulador
    double acum = 1;

    //Se hacen b iteraciones
    for(int i = 0; i < b; i++)
        //Cada iteración añade un factor a
        acum *= a;
    
    //Se retorna el acumulador, que contendrá a^b
    return acum;
}

//Divide & Conquer
double power_function_DC(double a, int b){
    //Etapa III: Caso trivial
    //Acá es tener a elevado a la 1
    if(b == 1) return a;

    //Etapa I: Dividir el problema
    //Acá es dividir el exponente b en b/2 y b/2
    int b_half = b / 2;

    //Etapa II: Continuar dividiendo el problema (recursión)
    //Acá se envía a recursión a^{b/2}
    double partial_result = power_function_DC(a, b_half);

    //Etapa IV: Mezclar las soluciones y retornar resultado
    //Acá es multiplicar a^{b/2} por sí mismo
    return partial_result * partial_result;
}

int main(){
    double a = 45;
    int b = 32;
    cout << power_function(a, b) << "\n";
    cout << power_function_DC(a, b) << "\n";

    return 0;
}
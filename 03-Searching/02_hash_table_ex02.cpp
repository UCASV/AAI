#include "test_array2.hpp"

//Datos de referencia para el algoritmo FNV-1a
#define FNV_OFFSET_BASIS 14695981039346656037UL //UL al final indica que el valor es Unsigned y Long
#define FNV_PRIME 1099511628211UL

//Estructura para cada celda de la Hash Table
//Cada celda tendrá una llave y su correspondiente dato
typedef struct {
    string key;
    int value;
} HTCell;

//Renombramiento de long unsigned int
typedef long unsigned int lui;

/*
    Implementación del algoritmo FNV-1a
*/
lui hash_function(string str){
    lui hash = FNV_OFFSET_BASIS;

    //Se recorre la cadena caracter por caracter.
    //Como cada caracter pesa 1 byte, se recorre
    //la cadena byte por byte
    for (int i = 0; i < str.length(); i++) {
        hash ^= str[i];
        hash *= FNV_PRIME;
    }

    return hash;
}

//Búsqueda en la Hash Table
bool search_hash_table(HTCell HT[], int size, string key){
    //Se calcula el hash para la llave proporcionada
    //Se aplica el modulo para traducir a un índice válido
    int hash = hash_function(key) % size;

    //Se verifica la existencia de la llave en la Hash Table
    return HT[hash].key == key;
}

//Obtención de dato en la Hash Table
int get_hash_table(HTCell HT[], int size, string key){
    //Si la llave existe en la Hash Table, se procede a extraer
    //su correspondiente valor
    if(search_hash_table(HT, size, key)) {
        //Se calcula el hash para la llave proporcionada
        //Se aplica el modulo para traducir a un índice válido
        int hash = hash_function(key) % size;
        //Se retorna el valor solicitado
        return HT[hash].value;
    } else
        //Se envía INT_MIN como un indicador de error
        return INT_MIN;
}

void set_hash_table(HTCell A[], int size, string key, int value) {
    //Se calcula el hash para la llave proporcionada
    //Se aplica el modulo para traducir a un índice válido
    int hash = hash_function(key) % size;
    
    //En la celda obtenida se asignan la llave y el valor proporcionados
    //(Esta versión no incluye tratamiento de colisiones, se opta por
    //sobreescribir datos)
    A[hash].key = key;
    A[hash].value = value;
}

/* Main */
int main(int argc, char** argv){
    //Se verifica que se haya invocado el programa proporcionando la llave del dato a buscar
    if( argc != 2 ){
        cout << "El programa debe ejecutarse colocando la llave del dato a buscar. >:|\n";
        exit(EXIT_FAILURE);
    }

    //Se extrae la llave del dato a buscar del segundo argumento
    string key = argv[1];

    //Se prepara la Hash Table para un máximo de <nmax> valores
    HTCell HT[nmax];

    //Se colocan los datos en la Hash Table utilizando la Hash Function
    for(int i = 0; i < n; i++)
        set_hash_table(HT, nmax, K[i], A[i]);

    //Se busca el dato en la Hash Table
    if(search_hash_table(HT, nmax, key)) cout << "El dato fue encontrado! :)\nY el dato es: " << get_hash_table(HT, nmax, key) << "\n";
    else cout << "El dato NO fue encontrado! :(\n";

    //Ilustración de las consecuencias de una de las muchas colisiones ocurridas
    cout << "\nLo siguiente no será igual a 'vdc': " << HT[hash_function("vdc") % nmax].key << "\n";

    return 0;
}

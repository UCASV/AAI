#include <bits/stdc++.h>
using namespace std;

//Se utilizan macros para definir todas las operaciones sobre bits
#define multiply_by_two(n)              (n << 1)
#define divide_by_two(n)                (n >> 1)
#define multiply_by_power_of_two(n, p)  (n << p)
#define divide_by_power_of_two(n, p)    (n >> p)
#define check_jth_bit(n, j)             (n & (1 << j))
#define activate_jth_bit(n, j)          (n | (1 << j))
#define deactivate_jth_bit(n, j)        (n & ~(1 << j))
#define toggle_jth_bit(n, j)            (n ^ (1 << j))
#define LSB(n)                          (n & (-n))
#define get_full_set(n)                 ((1 << n) - 1)
#define modulo(n, m)                    (n & (m - 1))
#define is_power_of_two(n)              !(n & (n - 1))
#define turn_off_last_bit(n)            (n & (n - 1))
#define turn_on_last_zero(n)            (n | (n + 1))
#define turn_off_last_oneblock(n)       (n & (n + 1))
#define turn_on_last_zeroblock(n)       (n | (n - 1))

/*
    Función para calcular y mostrar en pantalla todos los subsets válidos
    de una bitmask.
*/
void print_subsets(int n) {
    //El primer subset válido es la máscara misma.
    //El proceso se detiene al llegar a 0.
    for(int subset = n; subset; subset = (n & (subset - 1))) {
        //Se muestra el subset actual en base 2 y en base 10
        bitset<8> n_bits(subset);
        cout << n_bits << " - " << subset << "\n";
    }
}

/*
    Función que, dada una bitmask y un subset, verifica si el subset dado
    es un subset válido de la bitmask.
    Se retorna true si es un subset válido, y false en caso contrario.
*/
bool validate_subset(int n, int s) {
    //Se inicializa la flag de respuesta
    bool ans = false;

    //El primer subset válido es la máscara misma.
    //El proceso se detiene al llegar a 0.
    for(int subset = n; subset; subset = (n & (subset - 1)))
        //Se verifica si el subset actual es el proporcionado,
        //en cuyo caso se levanta la flag.
        if( subset == s ) ans = true;

    //Se retorna la flag
    return ans;
}

/************ Main ***********/

int main() {
    /* Prueba de operaciones aritméticas */
    cout << "17 * 2 = " << multiply_by_two(17) << "\n";
    cout << "54 / 2 = " << divide_by_two(54) << "\n";
    cout << "38 * 8 = " << multiply_by_power_of_two(38,3) << "\n";
    cout << "120 / 4 = " << divide_by_power_of_two(120,2) << "\n";
    cout << "155 % 8 = " << modulo(155, 8) << "\n";
    cout << "¿Es 32 una potencia de 2? " << ( is_power_of_two(32) ? "Sí lo es.\n" : "No lo es.\n" );
    cout << "¿Es 57 una potencia de 2? " << ( is_power_of_two(57) ? "Sí lo es.\n" : "No lo es.\n" );
    cout << "\n";

    /* Ilustración de aplicación de las operaciones de bits a un contexto real */

    /* 
        Estados de un videojuego:
            - RUNNING (R)   - ATTACKING (A)     - CHARGING (C)      - SHOOTING (Sh)
            - BLOCKING (B)  - HAS_SHIELD (hS)   - RELOADING (rL)    - USING_MAGIC (M)
            - DAMAGED (D)   - INVINCIBLE (I)    - STUNNED (St)      - POISONED (Po)
            - BURNED (Bu)   - FROZEN (Fr)       - DEAD (De)         - TRANSFORMED (T)
        
        16 Flags -> 16 bits
        0 0 0 0  0 0  0  0 0 0 0  0  0  0  0  0
        R A C Sh B hS rL M D I St Po Bu Fr De T
    */
    int player = 42129; //1010010010010001
    cout << "Máscara actual: " << player << " [" << bitset<16>(player) << "]\n\n";

    cout << "¿El jugador está envenenado?\n";
    cout << ( check_jth_bit(player,4) ? "Lo está\n\n" : "No lo está\n\n" );

    cout << "¿El jugador está paralizado?\n";
    cout << ( check_jth_bit(player,5) ? "Lo está\n\n" : "No lo está\n\n" );

    cout << "¿El jugador está corriendo y disparando?\n";
    cout << ( (check_jth_bit(player,15) & check_jth_bit(player,12)) ? "Lo está\n\n" : "No lo está\n\n" );

    cout << "El jugador recibe un ataque y se quema.\n";
    player = activate_jth_bit(player, 3);
    cout << "Nueva máscara: " << player << " [" << bitset<16>(player) << "]\n\n";
    
    cout << "El jugador se toma una poción y cura su envenenamiento.\n";
    player = deactivate_jth_bit(player, 4);
    cout << "Nueva máscara: " << player << " [" << bitset<16>(player) << "]\n\n";
    
    cout << "El jugador usa un ataque de su otra forma, provocando una transformación.\n";
    player = activate_jth_bit(player, 14);
    player = toggle_jth_bit(player, 0);
    cout << "Nueva máscara: " << player << " [" << bitset<16>(player) << "]\n\n";
    
    cout << "Se añade al juego una mochila con 10 items consumibles, en un primer momento está llena.\n";
    int bag = get_full_set(10); //1111111111
    cout << "Máscara de la bag: " << bag << " [" << bitset<10>(bag) << "]\n\n";
    
    cout << "Se añade la regla: los items de la mochila deben ser consumidos en orden (aka funciona como un stack).\n";
    cout << "Se consume el siguiente item de la mochila.\n";
    bag = turn_off_last_bit(bag);
    cout << "Máscara de la bag: " << bag << " [" << bitset<10>(bag) << "]\n\n";
    
    cout << "Se consumen dos items más.\n";
    bag = turn_off_last_bit(bag);
    bag = turn_off_last_bit(bag);
    cout << "Máscara de la bag: " << bag << " [" << bitset<10>(bag) << "]\n\n";
    
    cout << "Se usa un hechizo que restaura toda la mochila.\n";
    bag = turn_on_last_zeroblock(bag);
    cout << "Máscara de la bag: " << bag << " [" << bitset<10>(bag) << "]\n\n";
    
    cout << "Se consumen de una sola vez toda la mochila.\n";
    bag = turn_off_last_oneblock(bag);
    cout << "Máscara de la bag: " << bag << " [" << bitset<10>(bag) << "]\n\n";
    
    cout << "Se hace que la mochila se restaure progresivamente comenzando desde \"arriba del stack\".\n";
    bag = turn_on_last_zero(bag);
    cout << "Máscara de la bag: " << bag << " [" << bitset<10>(bag) << "]\n";
    cout << "Pasan dos ciclos más de tiempo.\n";
    bag = turn_on_last_zero(bag);
    bag = turn_on_last_zero(bag);
    cout << "Máscara de la bag: " << bag << " [" << bitset<10>(bag) << "]\n\n";
    
    cout << "Se añade un arma que tiene 4 niveles de cargado, comienza en el nivel 1.\n";
    int weapon = 1; //0001
    cout << "Máscara de la weapon: " << weapon << " [" << bitset<4>(weapon) << "]\n\n";
    
    cout << "El arma sube de nivel: \n";
    weapon = multiply_by_two(weapon);
    cout << "Máscara de la weapon: " << weapon << " [" << bitset<4>(weapon) << "]\n\n";
    
    cout << "¿En qué nivel está el arma?\n";
    switch(LSB(weapon)) {
        case  1: cout << "Nivel 1\n\n"; break;
        case  2: cout << "Nivel 2\n\n"; break;
        case  8: cout << "Nivel 3\n\n"; break;
        case 16: cout << "Nivel 4\n\n"; break;
    }
    
    cout << "El arma sube otro nivel.\n";
    weapon = multiply_by_two(weapon);
    cout << "Máscara de la weapon: " << weapon << " [" << bitset<4>(weapon) << "]\n";
    cout << "¿En qué nivel está ahora?\n";
    switch(LSB(weapon)) {
        case 1: cout << "Nivel 1\n\n"; break;
        case 2: cout << "Nivel 2\n\n"; break;
        case 4: cout << "Nivel 3\n\n"; break;
        case 8: cout << "Nivel 4\n\n"; break;
    }

    /* Prueba de función para mostrar subsets de una bitmask */

    print_subsets(18);
    cout << "\n";
    print_subsets(29);
    cout << "\n";

    /* Ilustración del uso de la generación de subsets */

    /*
        En el juego hay 6 ciudades que el jugador puede visitar: Otraigend,
        Vidburg, Yhaaver, Bralens, Piybridge, y Dard.
        Sin embargo, Vidburg y Piybridge solo pueden visitarse después de
        haber terminado la historia principal.
        Dado el registro de las ciudades visitadas de un jugador, se quiere
        poder detectar si ha jugado limpiamente, o si ha hecho trampa de algún
        modo para visitar antes de tiempo esas dos ciudades.
    */
    int cities = 45; //101101
    cout << "Máscara de las ciudades: " << cities << " [" << bitset<6>(cities) << "]\n\n";

    int cities_playerA = 9; //001001
    cout << "Evaluando estado de Player A: ";
    if( validate_subset(cities, cities_playerA) ) cout << "Todo bien.\n";
    else cout << "Ha hecho trampa! >:|\n";

    int cities_playerB = 21; //010101
    cout << "Evaluando estado de Player B: ";
    if( validate_subset(cities, cities_playerB) ) cout << "Todo bien.\n";
    else cout << "Ha hecho trampa! >:|\n";

    return 0;
}
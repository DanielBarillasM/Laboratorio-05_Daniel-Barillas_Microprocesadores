// -------------------------------------------------------------------------------------------------
// Nombre: Pablo Daniel Barillas Moreno
// Universidad: Universidad del Valle de Guatemala
// Curso: Programación de microprocesadores
// Programa: Manipulación de Variables en Paralelo con OpenMP - Laboratorio 05
// Versión: 1.0
// Fecha: 21/08/2024
// Descripción: Este programa en C utiliza OpenMP para modificar y manejar dos variables dentro 
//              de un ciclo `for` paralelo. Se demuestra el uso de las cláusulas `shared` y `private` 
//              para gestionar el acceso a las variables dentro del ciclo. 
//              - `variable1` es compartida entre todos los hilos y su valor final refleja las 
//                modificaciones realizadas por todos los hilos.
//              - `variable2` es privada para cada hilo, lo que significa que cada hilo tiene 
//                su propia copia independiente, y su valor no es consistente fuera del ciclo paralelo.
//              Este programa ilustra cómo manejar correctamente variables compartidas y privadas 
//              en un entorno de paralelización para evitar condiciones de carrera y asegurar 
//              la integridad de los datos.
// -------------------------------------------------------------------------------------------------
#include <stdio.h>     // Biblioteca estándar para entrada/salida
#include <omp.h>       // Biblioteca para paralelización con OpenMP

int main() {
    // Declaración e inicialización de variables
    int variable1 = 0;  // variable1 es compartida entre todos los hilos
    int variable2 = 0;  // variable2 será privada para cada hilo

    // Paralelizar el ciclo for usando OpenMP
    // 'shared(variable1)' indica que variable1 es compartida entre los hilos
    // 'private(variable2)' indica que cada hilo tendrá su propia copia de variable2
    #pragma omp parallel for shared(variable1) private(variable2)
    for (int i = 0; i < 10; i++) {  // Bucle iterando 10 veces
        variable1 += i;  // variable1 es modificada por todos los hilos (compartida)
        variable2 += i;  // variable2 es modificada independientemente por cada hilo (privada)

        // Imprimir el número de hilo, la iteración y los valores actuales de las variables
        printf("\nThread %d | Iteration %d | variable1 (shared): %d | variable2 (private): %d\n", 
               omp_get_thread_num(), i, variable1, variable2);
    }

    // Imprimir el valor final de variable1 después de que todos los hilos hayan completado el bucle
    printf("\n-----------------------------------------------------------\n");
    printf("Valor final de variable1 (compartida): %d\n", variable1);
    printf("-----------------------------------------------------------\n");

    // Nota: variable2 no se imprime aquí porque es privada para cada hilo 
    // y su valor no es consistente fuera del ciclo paralelo

    return 0;  // Finalizar el programa y retornar 0, indicando ejecución exitosa
}
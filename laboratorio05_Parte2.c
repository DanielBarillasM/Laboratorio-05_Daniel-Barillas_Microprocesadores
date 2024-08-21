// -------------------------------------------------------------------------------------------------
// Nombre: Pablo Daniel Barillas Moreno
// Universidad: Universidad del Valle de Guatemala
// Curso: Programación de microprocesadores
// Programa: calculo de la suma de los primeros N números naturales utilizando un ciclo for paralelo - Parte 2 - Laboratorio 05
// Versión: 1.0
// Fecha: 21/08/2024
// Descripción: Este programa en C calcula la suma de los primeros N números naturales utilizando OpenMP para paralelizar 
//              el bucle for. La cláusula `reduction(+:sum)` se emplea para acumular la suma de forma segura entre múltiples 
//              hilos. El tiempo de ejecución se mide usando `omp_get_wtime()` y se imprime junto con el resultado de la suma.
// -------------------------------------------------------------------------------------------------

#include <stdio.h>  // Incluir la biblioteca estándar de entrada y salida para utilizar printf
#include <omp.h>    // Incluir la biblioteca de OpenMP para utilizar funciones de paralelización

#define N 1000000   // Definir N como una constante grande con un valor de 1,000,000

int main() {
    int sum = 0;    // Declarar e inicializar la variable sum, que almacenará la suma de los primeros N números naturales

     // Medir el tiempo de inicio usando omp_get_wtime(), que devuelve el tiempo actual en segundos
    double start_time = omp_get_wtime();

    // Paralelizar el ciclo for utilizando la cláusula reduction para acumular la suma
    // La cláusula 'reduction(+:sum)' asegura que cada hilo acumule su parte de la suma de forma segura
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;    // En cada iteración, se suma el valor de i a la variable sum
    }

    // Medir el tiempo de finalización usando omp_get_wtime() para calcular el tiempo total de ejecución
    double end_time = omp_get_wtime();

    // Imprimir el resultado
    printf("\n-----Suma de los primeros números naturales-----\n");
    // Imprimir el resultado de la suma de los primeros N números naturales
    printf("\nLa suma de los primeros %d números naturales es: %d\n", N, sum);
    // Imprimir el tiempo total de ejecución del ciclo for paralelo
    printf("\nTiempo de ejecución: %f segundos\n\n", end_time - start_time);

    return 0; // Finalizar el programa con un valor de retorno 0, indicando que todo salió correctamente
}
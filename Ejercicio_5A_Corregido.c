// -------------------------------------------------------------------------------------------------
// Nombre: Pablo Daniel Barillas Moreno
// Universidad: Universidad del Valle de Guatemala
// Curso: Programación de microprocesadores
// Programa: Conteo Paralelo de Apariciones de un Valor en un Arreglo - Laboratorio 05
// Versión: 1.0
// Fecha: 21/08/2024
// Descripción: Este programa en C cuenta cuántas veces aparece un valor específico ('key') en un 
//              arreglo de números aleatorios utilizando OpenMP para paralelizar la operación. 
//              Se emplea una descomposición de tareas recursiva que genera tantas tareas como 
//              hilos disponibles, dividiendo el arreglo en subarreglos más pequeños y combinando 
//              los resultados. Esto demuestra un uso eficiente de OpenMP para tareas de conteo 
//              paralelizadas, mejorando el rendimiento en sistemas con múltiples núcleos.
// -------------------------------------------------------------------------------------------------

#include <stdio.h>     // Incluir la biblioteca estándar de entrada/salida para usar printf
#include <stdlib.h>    // Incluir la biblioteca estándar para usar funciones como rand()
#include <omp.h>       // Incluir la biblioteca OpenMP para paralelización

#define N 131072       // Definir el tamaño del arreglo como una constante (131072)


// Función recursiva para contar las apariciones de 'key' en un subarreglo
long parallel_count_key(long *a, long key, long start, long end) {
    long count = 0;  // Inicializar contador para las apariciones de 'key'

    // Si el subarreglo es pequeño, realizar la cuenta secuencialmente
    if (end - start < N / omp_get_max_threads()) {
        // Bucle para recorrer el subarreglo y contar las apariciones de 'key'
        for (long i = start; i < end; i++) {
            if (a[i] == key) count++;  // Incrementar el contador si se encuentra 'key'
        }
        return count;  // Retornar el número de apariciones encontradas en este subarreglo
    } else {
        // Si el subarreglo es grande, dividirlo en dos mitades
        long mid = start + (end - start) / 2;
        long left_count = 0, right_count = 0;  // Inicializar contadores para ambas mitades

        // Generar tarea recursiva para contar en la primera mitad del subarreglo
        #pragma omp task shared(left_count)
        left_count = parallel_count_key(a, key, start, mid);

        // Generar tarea recursiva para contar en la segunda mitad del subarreglo
        #pragma omp task shared(right_count)
        right_count = parallel_count_key(a, key, mid, end);

        // Esperar a que ambas tareas terminen
        #pragma omp taskwait

        // Combinar los resultados de las tareas y retornar el total
        return left_count + right_count;
    }
}

int main() {
    long a[N], key = 42, nkey = 0;  // Declarar el arreglo, la clave a buscar, y el contador de apariciones

    // Llenar el arreglo con valores aleatorios
    for (long i = 0; i < N; i++) a[i] = rand() % N;

    // Insertar manualmente 'key' en tres posiciones específicas del arreglo
    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;

    // Contar las apariciones de 'key' en paralelo usando OpenMP y la función recursiva
    #pragma omp parallel  // Iniciar una región paralela
    {
        #pragma omp single  // Asegurar que solo un hilo inicie la tarea recursiva inicial
        nkey = parallel_count_key(a, key, 0, N);
    }

    // Imprimir el número de veces que 'key' aparece en el arreglo
    printf("\nNumero de veces que 'key' aparece en paralelo: %ld\n\n", nkey);

    return 0;  // Finalizar el programa y devolver 0, indicando que todo salió correctamente
}

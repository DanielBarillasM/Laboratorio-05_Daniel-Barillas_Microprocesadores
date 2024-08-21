// -------------------------------------------------------------------------------------------------
// Nombre: Pablo Daniel Barillas Moreno
// Universidad: Universidad del Valle de Guatemala
// Curso: Programación de microprocesadores
// Programa: Operaciones Matemáticas Paralelas - Parte 3 - Laboratorio 05
// Versión: 1.0
// Fecha: 21/08/2024
// Descripción: Este programa en C utiliza OpenMP para ejecutar tres funciones matemáticas diferentes
//              en paralelo. Las funciones incluyen: el cálculo del factorial de un número, la
//              generación de la serie de Fibonacci, y la búsqueda del valor máximo en un arreglo. 
//              Cada función se ejecuta en su propia sección paralela, demostrando el uso eficiente de 
//              la directiva #pragma omp sections para dividir el trabajo entre múltiples hilos.
// -------------------------------------------------------------------------------------------------

#include <stdio.h>      // Incluir la biblioteca estándar de entrada y salida para usar printf
#include <omp.h>        // Incluir la biblioteca OpenMP para la paralelización

// -------------------------------------------------------------------------------------------------
// Función para calcular el factorial de un número
// -------------------------------------------------------------------------------------------------
unsigned long long factorial(int n) {
    unsigned long long result = 1;  // Inicializar la variable result en 1 para el cálculo del factorial
    for (int i = 2; i <= n; i++) {  // Bucle desde 2 hasta n para multiplicar todos los enteros positivos
        result *= i;  // Multiplicar result por el valor de i en cada iteración para calcular el factorial
    }
    return result;  // Retornar el resultado del factorial
}

// -------------------------------------------------------------------------------------------------
// Función para generar la serie de Fibonacci hasta n
// -------------------------------------------------------------------------------------------------
void fibonacci(int n) {
    unsigned long long a = 0, b = 1, temp;  // Inicializar las variables para la serie de Fibonacci
    printf("\nSerie de Fibonacci: ");  // Imprimir el encabezado para la serie de Fibonacci
    for (int i = 1; i <= n; i++) {  // Bucle desde 1 hasta n para generar la serie
        printf("%llu ", a);  // Imprimir el número actual en la serie de Fibonacci
        temp = a + b;  // Calcular el siguiente número en la serie
        a = b;  // Actualizar a al valor de b
        b = temp;  // Actualizar b al nuevo valor calculado
    }
    printf("\n");  // Imprimir un salto de línea después de la serie
}

// -------------------------------------------------------------------------------------------------
// Función para encontrar el máximo en un arreglo
// -------------------------------------------------------------------------------------------------
int find_max(int arr[], int size) {
    int max = arr[0];  // Inicializar max con el primer elemento del arreglo
    for (int i = 1; i < size; i++) {  // Bucle desde el segundo elemento hasta el final del arreglo
        if (arr[i] > max) {  // Comparar el elemento actual con el valor máximo encontrado hasta ahora
            max = arr[i];  // Si el elemento actual es mayor, actualizar max
        }
    }
    return max;  // Retornar el valor máximo encontrado en el arreglo
}

int main() {
    int n = 10;  // Definir el valor de n, que se utilizará en las funciones de factorial y Fibonacci
    int arr[] = {3, 5, 7, 2, 8, -1, 4, 10, 12};  // Definir el arreglo de enteros para la función de máximo
    int size = sizeof(arr) / sizeof(arr[0]);  // Calcular el tamaño del arreglo

    // -------------------------------------------------------------------------------------------------
    // Ejecutar las funciones en paralelo usando OpenMP sections
    // -------------------------------------------------------------------------------------------------
    #pragma omp parallel sections  // Iniciar una región paralela dividiendo el trabajo en secciones
    {
        #pragma omp section  // Iniciar la primera sección paralela
        {
            unsigned long long fact = factorial(n);  // Llamar a la función factorial y almacenar el resultado
            printf("\n--------------------------------------------\n");
            printf("Factorial de %d es: %llu\n", n, fact);  // Imprimir el resultado del factorial
            printf("--------------------------------------------\n");
        }

        #pragma omp section  // Iniciar la segunda sección paralela
        {
            printf("\n--------------------------------------------\n");
            fibonacci(n);  // Llamar a la función fibonacci para generar e imprimir la serie
            printf("--------------------------------------------\n");
        }

        #pragma omp section  // Iniciar la tercera sección paralela
        {
            int max = find_max(arr, size);  // Llamar a la función find_max y almacenar el valor máximo
            printf("\n--------------------------------------------\n");
            printf("El máximo valor en el arreglo es: %d\n", max);  // Imprimir el valor máximo encontrado
            printf("--------------------------------------------\n");
        }
    }

    return 0;  // Finalizar el programa con un valor de retorno 0, indicando que todo salió correctamente
}
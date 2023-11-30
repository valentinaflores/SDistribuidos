
// Multiplicación de vector por matriz de forma paralela
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>  // Inclusión para gettimeofday

//Función de multiplicación
void Multiplication(const double *vector, const double *matrix, double *result, int rows, int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; ++i) {
        result[i] = 0.0;
        for (int j = 0; j < cols; ++j) {
            result[i] += vector[j] * matrix[i * cols + j];
        }
    }
}

int main() {
	//Se definen las dimensiones
    const int rows = 3;
    const int cols = 3;

	//Se declaran arreglos para c/u
    double vector[cols];
    double matrix[rows][cols];
    double result[rows];

    // Se inicializan vector y matriz
    for (int i = 0; i < cols; ++i) {
        vector[i] = 2.0;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = 3.0;
        }
    }
    
	// Medir el tiempo inicial
	struct timespec start_time, end_time;
	clock_gettime(CLOCK_MONOTONIC, &start_time);


    // Realiza la multiplicación de forma paralela
    Multiplication(vector, (double *)matrix, result, rows, cols);
    
	// Medir el tiempo final
	clock_gettime(CLOCK_MONOTONIC, &end_time);

 	// Calcular el tiempo transcurrido en segundos
	double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
   
    // Mostrar el resultado
    printf("Resultado de la multiplicacion:\n");
    for (int i = 0; i < rows; ++i) {
        printf("%f ", result[i]);
    }
    printf("\n");
    
// Mostrar el tiempo transcurrido por iteración
printf("Tiempo transcurrido: %f segundos\n", elapsed_time);
    
    return 0;
}

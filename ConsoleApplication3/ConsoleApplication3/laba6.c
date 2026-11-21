#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void inputIntMatrix(int rows, int cols, int matrix[MAX][MAX]) {
    printf("Введіть елементи цілої матриці (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void printIntMatrix(int rows, int cols, int matrix[MAX][MAX]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
}

void printIntArray(int size, int arr[]) {
    if (size == 0) {
        printf("Масив порожній.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%5d", arr[i]);
    }
    printf("\n");
}

void inputDoubleMatrix(int size, double matrix[MAX][MAX]) {
    printf("Введіть елементи матриці дійсних чисел (%d x %d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void printDoubleMatrix(int size, double matrix[MAX][MAX]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%8.2lf", matrix[i][j]);
        }
        printf("\n");
    }
}



int getColumnCharacteristic(int rows, int matrix[MAX][MAX], int col) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix[i][col] < 0 && abs(matrix[i][col]) % 2 != 0) {
            sum += abs(matrix[i][col]);
        }
    }
    return sum;
}

void swapColumns(int rows, int matrix[MAX][MAX], int col1, int col2) {
    for (int i = 0; i < rows; i++) {
        int temp = matrix[i][col1];
        matrix[i][col1] = matrix[i][col2];
        matrix[i][col2] = temp;
    }
}

void Task1011() {
    int rows, cols;
    int matrix[MAX][MAX];
    int characteristics[MAX];

    printf("\n--- Задача 1011 ---\n");
    printf("Введіть кількість рядків та стовпців матриці (до %d): ", MAX);
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 || rows > MAX || cols > MAX) {
        printf("Помилка: некоректні розміри матриці.\n");
        return;
    }

    inputIntMatrix(rows, cols, matrix);

    printf("\nПочаткова матриця:\n");
    printIntMatrix(rows, cols, matrix);

    for (int j = 0; j < cols; j++) {
        characteristics[j] = getColumnCharacteristic(rows, matrix, j);
    }

    printf("\nХарактеристики стовпців до сортування:\n");
    for (int j = 0; j < cols; j++) {
        printf("%5d", characteristics[j]);
    }
    printf("\n");

    for (int i = 0; i < cols - 1; i++) {
        for (int j = 0; j < cols - i - 1; j++) {
            if (characteristics[j] > characteristics[j + 1]) {
                int tempChar = characteristics[j];
                characteristics[j] = characteristics[j + 1];
                characteristics[j + 1] = tempChar;

                swapColumns(rows, matrix, j, j + 1);
            }
        }
    }

    printf("\nВідсортована матриця:\n");
    printIntMatrix(rows, cols, matrix);

    printf("\nХарактеристики стовпців після сортування:\n");
    for (int j = 0; j < cols; j++) {
        printf("%5d", characteristics[j]);
    }
    printf("\n");
}



void Task908() {
    int n;
    double matrix[MAX][MAX];

    printf("\n--- Задача 908 ---\n");
    printf("Введіть розмір квадратної матриці n (від 2 до %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 1 || n > MAX) {
        printf("Помилка: некоректний розмір матриці.\n");
        return;
    }

    inputDoubleMatrix(n, matrix);

    printf("\nВведена матриця:\n");
    printDoubleMatrix(n, matrix);

    printf("\nСуми елементів на лініях, паралельних головній діагоналі та вище неї:\n");
    for (int k = 1; k < n; k++) {
        double sum = 0.0;
        for (int i = 0; i < n - k; i++) {
            sum += matrix[i][i + k];
        }
        printf("Діагональ №%d (починається з [0][%d]): %.2lf\n", k, k, sum);
    }
}


void Task934() {
    int n, m;
    int A[MAX][MAX];

    printf("\n--- Задача 934 ---\n");
    printf("Введіть кількість рядків (n) та стовпців (m) масиву A (до %d): ", MAX);
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0 || n > MAX || m > MAX) {
        printf("Помилка: некоректні розміри масиву.\n");
        return;
    }

    inputIntMatrix(n, m, A);

    printf("\nВведений масив A:\n");
    printIntMatrix(n, m, A);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (A[i][j] <= A[i][j + 1]) {
                printf("\nПопередження: порушено умову спадання в рядку %d (A[%d][%d] <= A[%d][%d]).\n",
                    i + 1, i + 1, j + 1, i + 1, j + 2);
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (A[i][m - 1] <= A[i + 1][m - 1]) {
            printf("\nПопередження: порушено умову спадання в останньому стовпці (A[%d][%d] <= A[%d][%d]).\n",
                i + 1, m, i + 2, m);
        }
    }

    int found = 0;
    printf("\nРезультати пошуку елементів A[i, j] = i + j (індексація з 1):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int row1 = i + 1;
            int col1 = j + 1;
            if (A[i][j] == row1 + col1) {
                printf("Знайдено: A[%d, %d] = %d\n", row1, col1, A[i][j]);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Елементів, рівних сумі своїх індексів (i + j), немає.\n");
    }
}


void Task978() {
    int n;
    double src[MAX][MAX];
    double dst[MAX][MAX];

    printf("\n--- Задача 978 ---\n");
    printf("Введіть параметр n (розмір матриці буде 2n x 2n, до %d): ", MAX / 2);
    if (scanf("%d", &n) != 1 || n <= 0 || 2 * n > MAX) {
        printf("Помилка: некоректний параметр n.\n");
        return;
    }

    int size = 2 * n;
    inputDoubleMatrix(size, src);

    printf("\nПочаткова матриця (%d x %d):\n", size, size);
    printDoubleMatrix(size, src);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i + n][j + n] = src[i][j];
            dst[i][j] = src[i + n][j + n];

            dst[i + n][j] = src[i][j + n];
            dst[i][j + n] = src[i + n][j];
        }
    }

    printf("\nНова матриця після перестановки блоків %d x %d хрест-навхрест:\n", n, n);
    printDoubleMatrix(size, dst);
}

void Task929() {
    int rows, cols;
    int matrix[MAX][MAX];
    int nonNegArr[MAX * MAX];
    int negArr[MAX * MAX];
    int nonNegCount = 0;
    int negCount = 0;

    printf("\n--- Задача 929 ---\n");
    printf("Введіть кількість рядків та стовпців двовимірного масиву (до %d): ", MAX);
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 || rows > MAX || cols > MAX) {
        printf("Помилка: некоректні розміри масиву.\n");
        return;
    }

    inputIntMatrix(rows, cols, matrix);

    printf("\nПочатковий двовимірний масив:\n");
    printIntMatrix(rows, cols, matrix);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] >= 0) {
                nonNegArr[nonNegCount] = matrix[i][j];
                nonNegCount++;
            }
            else {
                negArr[negCount] = matrix[i][j];
                negCount++;
            }
        }
    }

    printf("\nМасив позитивних та нульових елементів (%d шт.):\n", nonNegCount);
    printIntArray(nonNegCount, nonNegArr);

    printf("\nМасив негативних елементів (%d шт.):\n", negCount);
    printIntArray(negCount, negArr);
}


int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;

    do {
        printf("\n==============================\n");
        printf("Оберіть задачу для виконання:\n");
        printf("1. Задача 1011 (Сортування стовпців матриці за характеристиками)\n");
        printf("2. Задача 908 (Суми діагоналей вище головної)\n");
        printf("3. Задача 934 (Пошук елементів A[i, j] = i + j)\n");
        printf("4. Задача 978 (Перестановка блоків n x n хрест-навхрест)\n");
        printf("5. Задача 929 (Розділення на позитивні/нульові та негативні масиви)\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &choice) != 1) {
            printf("Некоректне введення. Завершення роботи.\n");
            break;
        }

        switch (choice) {
        case 1:
            Task1011();
            break;
        case 2:
            Task908();
            break;
        case 3:
            Task934();
            break;
        case 4:
            Task978();
            break;
        case 5:
            Task929();
            break;
        case 0:
            printf("Вихід з програми.\n");
            break;
        default:
            printf("Невірний вибір. Спробуйте ще раз.\n");
        }
    } while (choice != 0);

    return 0;
}
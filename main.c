#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisons = 0;
int swaps = 0;

// Функция для вывода текущего состояния массива и информации о перестановках
void print_step(int *a, int n, int i, int j, int debug){
    if (debug){
        printf("Swapped i%d and i%d: ", i, j);
        for (int k = 0; k < n; k++)
            printf("%d ", a[k]);
        printf("\n");
    }
}

void order_mas(int n, int *a){
    for (int i = 0; i < n; i++)
        a[i] = n - i;
}

void reverse_mas(int n, int *a){
    for (int i = 0; i < n; i++)
        a[i] = i;
}

void random_mas(int n, int *a){
    for (int i = 0; i < n; i++){
        if (rand() % 2 == 0)
            a[i] = rand() * rand();
        else 
            a[i] = -(rand() * rand());
    }
}

void random_mas_debug(int n, int *a) {
    for (int i = 0; i < n; i++)
        a[i] = rand() % 100; // Ограничим диапазон для удобства вывода
}

int is_sorted(int n, int *a){
    for (int i = 0; i < n - 1; i++){
        if (a[i + 1] > a[i])
            return 0;
    }
    return 1;
}


void bubble_sort(int *a, int n, int debug){
    comparisons = 0;
    swaps = 0;
    int swapped;
    for (int i = 0; i < n - 1; i++){
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++){
            comparisons++;
            if (a[j] < a[j + 1]){
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swaps++;
                swapped = 1;
                print_step(a, n, j, j + 1, debug); // Вывод текущего состояния
            }
        }
        if (!swapped) 
            break;
    }
}

// Построение кучи
void heapify(int *a, int n, int i, int debug) {
    int smallest = i; // Изначально предполагаем, что текущий элемент - наименьший
    int left = 2 * i + 1; // Левый потомок
    int right = 2 * i + 2; // Правый потомок
    comparisons++;
    // Проверяем, является ли левый потомок меньше наименьшего элемента
    if (left < n && a[left] < a[smallest])
        smallest = left;
    comparisons++;
    // Проверяем, является ли правый потомок меньше наименьшего элемента
    if (right < n && a[right] < a[smallest])
        smallest = right;
    // Если наименьший элемент не корень
    if (smallest != i) {
        // Меняем местами корень и наименьший элемент
        int temp = a[i];
        a[i] = a[smallest];
        a[smallest] = temp;
        swaps++; // Увеличиваем счетчик обменов
        // Рекурсивно восстанавливаем кучу для затронутого поддерева
        print_step(a, n, i, smallest, debug); // Вывод текущего состояния
        heapify(a, n, smallest, debug);
    }
}

// Пирамидальная сортировка по невозрастанию
void heap_sort(int *a, int n, int debug){
    comparisons = 0;
    swaps = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i, debug);
    for (int i = n - 1; i > 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        swaps++;
        print_step(a, n, 0, i, debug); // Вывод текущего состояния
        heapify(a, i, 0, debug);
    }
}

void print_mas(int n, int *a){
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// Тестирование сортировки пузырьком
void test_bubble_sort(int n, int debug) {
    int *a = malloc(n * sizeof(int));
    printf("Testing Bubble Sort (n = %d):\n", n);
    random_mas_debug(n, a);
    printf("Initial array: ");
    print_mas(n, a);
    bubble_sort(a, n, debug);
    printf("Sorted array: ");
    print_mas(n, a);
    printf("Comparisons: %d, Swaps: %d\n", comparisons, swaps);
    free(a);
}

// Тестирование пирамидальной сортировки
void test_heap_sort(int n, int debug) {
    int *a = malloc(n * sizeof(int));
    printf("Testing Heap Sort (n = %d):\n", n);
    random_mas_debug(n, a);
    printf("Initial array: ");
    print_mas(n, a);
    heap_sort(a, n, debug);
    printf("Sorted array: ");
    print_mas(n, a);
    printf("Comparisons: %d, Swaps: %d\n", comparisons, swaps);
    free(a);
}

int main(void){
    srand(time(NULL));

    // Включаем отладочный вывод только для одного случайного массива длиной 10
    printf("Debug output for Bubble Sort:\n");
    test_bubble_sort(10, 1);
    printf("\nDebug output for Heap Sort:\n");
    test_heap_sort(10, 1);

    int sizes[] = {10, 100, 1000, 10000};
    int **rand_mas = calloc(8, sizeof(int*));
    printf("Метод «пузырька»\n");
    printf("n\tТип массива\t1\t\t2\t\t3\t\t4\t\tСреднее значение\n");
    for (int i = 0; i < 4; i++){
        int n = sizes[i];
        int *mas = malloc(n * sizeof(int));
        int comparisons_bubble[4] = {0};
        int swaps_bubble[4] = {0};
        // Типы массивов: 1 - упорядоченный, 2 - обратный, 3 и 4 - случайные
        for (int type = 1; type <= 4; type++){
            if (type == 1)
                order_mas(n, mas);
            else if (type == 2)
                reverse_mas(n, mas);
            else{
                random_mas(n, mas);
                rand_mas[i * 2 + type - 3] = calloc(n, sizeof(int));
                for (int j = 0; j < n; j++){
                    rand_mas[i * 2 + type -3][j] = mas[j];
                }
            }
            bubble_sort(mas, n, 0);
            comparisons_bubble[type - 1] = comparisons;
            swaps_bubble[type - 1] = swaps;
        }
        if (!is_sorted(n, mas)){
            printf("ERROR\n");
            return 0;
        }
        // Вывод результатов для пузырьковой сортировки
        printf("%d\tСравнения\t%-10d\t%-10d\t%-10d\t%-10d\t%.2f\n", n, comparisons_bubble[0], comparisons_bubble[1], comparisons_bubble[2], comparisons_bubble[3],
               (comparisons_bubble[0] + comparisons_bubble[1] + comparisons_bubble[2] + comparisons_bubble[3]) / 4.0);
        printf("\tПеремещения\t%-10d\t%-10d\t%-10d\t%-10d\t%.2f\n", swaps_bubble[0], swaps_bubble[1], swaps_bubble[2], swaps_bubble[3],
               (swaps_bubble[0] + swaps_bubble[1] + swaps_bubble[2] + swaps_bubble[3]) / 4.0);

        free(mas);
    }
    printf("\nПирамидальная сортировка\n");
    printf("n\tТип массива\t1\t\t2\t\t3\t\t4\t\tСреднее значение\n");
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];
        int *mas = malloc(n * sizeof(int));
        int comparisons_heap[4] = {0};
        int swaps_heap[4] = {0};
        // Типы массивов: 1 - упорядоченный, 2 - обратный, 3 и 4 - случайные
        for (int type = 1; type <= 4; type++) {
            if (type == 1){
                order_mas(n, mas);
                heap_sort(mas, n, 0);
                if (!is_sorted(n, mas)){
                    printf("ERROR\n");
                    return 0;
                }
            }
            else if (type == 2){
                reverse_mas(n, mas);
                heap_sort(mas, n, 0);
                if (!is_sorted(n, mas)){
                    printf("ERROR\n");
                    return 0;
                }
            }
            else{
                random_mas(n, mas);
                heap_sort(rand_mas[i * 2 + type - 3], n, 0);
                if (!is_sorted(n, rand_mas[i * 2 + type - 3])){
                    printf("ERROR\n");
                    return 0;
                }
            }
            //print_mas(n, mas);
            comparisons_heap[type - 1] = comparisons;
            swaps_heap[type - 1] = swaps;
        }
        // Вывод результатов для пирамидальной сортировки
        printf("%d\tСравнения\t%-10d\t%-10d\t%-10d\t%-10d\t%.2f\n", n, comparisons_heap[0], comparisons_heap[1], comparisons_heap[2], comparisons_heap[3],
               (comparisons_heap[0] + comparisons_heap[1] + comparisons_heap[2] + comparisons_heap[3]) / 4.0);
        printf("\tПеремещения\t%-10d\t%-10d\t%-10d\t%-10d\t%.2f\n", swaps_heap[0], swaps_heap[1], swaps_heap[2], swaps_heap[3],
               (swaps_heap[0] + swaps_heap[1] + swaps_heap[2] + swaps_heap[3]) / 4.0);
        free(mas);
    }
    return 0;
}
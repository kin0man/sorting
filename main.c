#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisons = 0;
int swaps = 0;

void order_mas(int n, int *a){
    for (int i = 0; i < n; i++)
        a[i] = i;
}

void reverse_mas(int n, int *a){
    for (int i = 0; i < n; i++)
        a[i] = n - i;
}

void random_mas(int n, int *a){
    for (int i = 0; i < n; i++)
        a[i] = rand();
}

int is_sorted(int n, int *a){
    for (int i = 0; i < n; i++){
        if (a[i + 1] > a[i])
            return 0;
    }
    return 1;
}

void bubble_sort(int *a, int n){
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            comparisons++;
            if (a[j] < a[j + 1]){
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swaps++;
            }
        }
    }
}

// Построение кучи
void heapify(int *a, int n, int i) {
    int largest = i; // Изначально предполагаем, что текущий элемент - наибольший
    int left = 2 * i + 1; // Левый потомок
    int right = 2 * i + 2; // Правый потомок
    comparisons++;
    // Проверяем, является ли левый потомок больше наибольшего элемента
    if (left < n && a[left] > a[largest])
        largest = left;
    comparisons++;
    // Проверяем, является ли правый потомок больше наибольшего элемента
    if (right < n && a[right] > a[largest])
        largest = right;
    // Если наибольший элемент не корень
    if (largest != i) {
        // Меняем местами корень и наибольший элемент
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        swaps++; // Увеличиваем счетчик обменов
        // Рекурсивно восстанавливаем кучу для затронутого поддерева
        heapify(a, n, largest);
    }
}

// Пирамидальная сортировка
void heap_sort(int *a, int n) {
    comparisons = 0;
    swaps = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i > 0; i--) {
        // Меняем местами корень (максимальный элемент) с последним элементом
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        swaps++;
        // Восстанавливаем кучу на уменьшенной куче
        heapify(a, i, 0);
    }
}

int main(void){
    srand(time(NULL));
    int sizes[] = {10, 100, 1000, 10000};
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
            else
                random_mas(n, mas);
            bubble_sort(mas, n);
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
            if (type == 1)
                order_mas(n, mas);
            else if (type == 2)
                reverse_mas(n, mas);
            else
                random_mas(n, mas);
            heap_sort(mas, n);
            comparisons_heap[type - 1] = comparisons;
            swaps_heap[type - 1] = swaps;
        }
        if (!is_sorted(n, mas)){
            printf("ERROR\n");
            return 0;
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
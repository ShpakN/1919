#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define TIME_TEST(testCode, time) { \
clock_t start_time = clock(); \
testCode \
clock_t end_time = clock();\
clock_t sort_time = end_time - start_time; \
time = (double) sort_time / CLOCKS_PER_SEC;\
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
// функция сортировки
typedef struct SortFunc {
    void (*sort)(int *a, size_t n); // указатель на функцию

// сортировки
    char name[64]; // имя сортировки,
// используемое при выводе

} SortFunc;
// функция генерации

typedef struct GeneratingFunc {
    void (*generate)(int *a, size_t n); // указатель на функцию
// генерации последоват.
    char name[64]; // имя генератора,
// используемое при выводе

} GeneratingFunc;

void (*generateOrderedBackwards)(int *, size_t);

bool isOrdered(int pInt[100000], size_t size);

static int getMinIndex(int *pInt, size_t unsorted);

double getTime() {
    clock_t start_time = clock();
// фрагмент кода
// время которого измеряется
    clock_t end_time = clock();\
clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}


void outputArray_(const int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}


void checkTime(void(*sortFunc)(int *, size_t),
               void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName) {

    static size_t runCounter = 1;
// генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);

    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  sortFunc(innerBuffer, size);
              }, time);
    // результаты замера
    printf("Status: ");

    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
// запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

// вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);
        exit(1);
    }
}

bool isOrdered(int pInt[100000], size_t size) {
    return 0;
}


void swap(int a, int b) {
    int t = a;
    a = b;
    b = t;
}


static void selectionSort(int *unsortedPart, size_t nUnsorted) {
    if (nUnsorted == 1) // массив из одного элемента является

// упорядоченным и так

        return;
    else {
        int minElementIndex = getMinIndex(unsortedPart, nUnsorted);

        swap(unsortedPart[0], unsortedPart[minElementIndex]);
        selectionSort(unsortedPart + 1, nUnsorted - 1);
    }
}

static int getMinIndex(int *pInt, size_t unsorted) {
    return 0;
}


void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        int j = i;

        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }

        a[j] = t;
    }
}


long long getBubbleSort(int *a, size_t n) {
    long long nComps = 0;

    for (int i = 0; ++nComps && i < n; i++) {
        int min = a[i];
        int minIndex = i;

        for (int j = i + 1; ++nComps && j < n; j++)
            if (++nComps && a[j] > a[j + 1]) {
                min = a[j];
                a[j] = a[j + 1];
                a[j + 1] = min;
                minIndex = j;
            }

        if (++nComps && i != minIndex)
            swap(a[i], a[minIndex]);
    }

    return nComps;
}


long long getChoiceSort(int *a, size_t n) {
    long long nComps = 0;
    int tmp = 0;

    for (int i = 0; i < n; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
            if (++nComps && a[minIndex] > a[j]) {
                minIndex = j;
                tmp = a[minIndex];
                a[minIndex] = a[j];
                a[j] = tmp;
            }
        return nComps;
    }
}


void getInsertionSort(int *a, size_t n) {
    int newElement, location;

    for (int i = 1; i < n; i++) {
        newElement = a[i];
        location = i - 1;

        while (location >= 0 && a[location] > newElement) {
            a[location + 1] = a[location];
            location = location - 1;
        }
        a[location + 1] = newElement;
    }
}


void getCombSort(int *a, size_t n) {
    if (a && n) {
        size_t jump = n, i;
        int swapped = 1;
        while (jump > 1 || swapped) {
            if (jump > 1)
                jump /= 1.24733;
            swapped = 0;
            for (i = 0; i + jump < n; ++i)
                if (a[i + jump] > a[i]) {
                    int tmp;
                    tmp = a[i];
                    a[i] = a[i + jump];
                    a[i + jump] = tmp;
                    swapped = 1;
                }
        }
    }
}


void ShellSort(int *a, size_t n) {
    int i, j, step;
    int tmp;

    for (step = n / 2; step > 0; step /= 2)

        for (i = step; i < n; i++) {
            tmp = a[i];

            for (j = i; j >= step; j -= step) {
                if (tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }

            a[j] = tmp;
        }
}

typedef unsigned uint;
#define each(i, x) for (i = 0; i < x; i++)


static void radSortU(uint *from, uint *to, uint bit) {
    if (!bit || to < from + 1) return;

    uint *ll = from, *rr = to - 1, tmp;
    while (1) {
        while (ll < rr && !(*ll & bit)) ll++;
        while (ll < rr && (*rr & bit)) rr--;
        if (ll >= rr) break;
        swap(*ll, *rr);
    }

    if (!(bit & *ll) && ll < to) ll++;
    bit >>= 1;

    radSortU(from, ll, bit);
    radSortU(ll, to, bit);
}


static void getRadixSort(int *a, const size_t n) {
    size_t i;
    uint *x = (uint *) a;

    each(i, n);
    x[i] ^= INT_MIN;
    radSortU(x, x + n, INT_MIN);
    each(i, n);
    x[i] ^= INT_MIN;
}

static inline void getRadixSortUnsigned(uint *a, const size_t n) {
    radSortU(a, a + n, (uint) INT_MIN);
}


void checkTimeBubble(void(*sortFunc)(int *, size_t),
                     void (*generateFunc)(int *, size_t),
                     size_t size, char *experimentName) {

    static size_t runCounter = 1;
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);

    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  getBubbleSort(innerBuffer, size);
              }, time);

    printf("Status: ");

    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray_(innerBuffer, size);
        exit(1);
    }
}


void checkTimeChoice(void(*sortFunc)(int *, size_t),
                     void (*generateFunc)(int *, size_t),
                     size_t size, char *experimentName) {

    static size_t runCounter = 1;
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);

    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  getChoiceSort(innerBuffer, size);
              }, time);

    printf("Status: ");

    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray_(innerBuffer, size);
        exit(1);
    }
}


void checkTimeInsertion(void(*sortFunc)(int *, size_t),
                        void (*generateFunc)(int *, size_t),
                        size_t size, char *experimentName) {

    static size_t runCounter = 1;
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);

    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  getInsertionSort(innerBuffer, size);
              }, time);

    printf("Status: ");

    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray_(innerBuffer, size);
        exit(1);
    }
}


void checkTimeComb(void(*sortFunc)(int *, size_t),
                   void (*generateFunc)(int *, size_t),
                   size_t size, char *experimentName) {

    static size_t runCounter = 1;
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);

    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  getCombSort(innerBuffer, size);
              }, time);

    printf("Status: ");

    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray_(innerBuffer, size);
        exit(1);
    }
}


void checkTimeShell(void(*sortFunc)(int *, size_t),
                    void (*generateFunc)(int *, size_t),
                    size_t size, char *experimentName) {

    static size_t runCounter = 1;
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);

    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  ShellSort(innerBuffer, size);
              }, time);

    printf("Status: ");

    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray_(innerBuffer, size);
        exit(1);
    }
}


void timeExperiment() {
// описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
// вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);
// описание функций генерации
    void (*generateRandomArray)(int *, size_t) = 0;
    GeneratingFunc generatingFuncs[] = {
// генерируется случайный массив
            {generateRandomArray,      "random"},
// генерируется массив 0, 1, 2, ..., n - 1
            {generateRandomArray,      "ordered"},
// генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };

    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

// запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("------------------------------\n");
        printf("Size: %zu\n", size);

        for (int i = 0; i < FUNCS_N; i++) {

            for (int j = 0; j < CASES_N; j++) {
// генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,

                          generatingFuncs[j].generate,
                          size, filename);

                checkTimeBubble(sorts[i].sort,

                                generatingFuncs[j].generate,
                                size, filename);

                checkTimeChoice(sorts[i].sort,

                                generatingFuncs[j].generate,
                                size, filename);

                checkTimeComb(sorts[i].sort,

                              generatingFuncs[j].generate,
                              size, filename);

                checkTimeInsertion(sorts[i].sort,

                                   generatingFuncs[j].generate,
                                   size, filename);

                checkTimeShell(sorts[i].sort,

                               generatingFuncs[j].generate,
                               size, filename);
            }
        }

        printf("\n");
    }
}

int main() {
    timeExperiment();

    return 0;
}
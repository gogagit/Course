#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_SIZE 100
//Объявление структуры
struct software {
    int number;
    int year;
    int month;
    int day;
    char client[20];
    double sum;
    char status[20];
};
// Прототипы функций
int searchByNumber(struct software programs[], int size);
struct software* sortByDate(struct software programs[], int size);
int writeToFile(struct software programs[], int size);
int openFile(struct software programs[], int* size);
int newRecord(struct software* programs, int* size);
void record(struct software programs[], int i);
void table();
int main() {
    setlocale(LC_ALL, "RUS");
    //Создание рамки
    printf("+----------------------------------------------+\n");
    printf("| Выполнил: Семенютин Илья Игоревич            |\n");
    printf("| Группа: бИСТ-232                             |\n");
    printf("| Программа: работа с файловой БД «Заказ ПО»   |\n");
    printf("+----------------------------------------------+\n");
    struct software programs[MAX_SIZE];
    int size = 0;
    int choice,index;
    system("chcp 1251");
    do {
        //Создание меню
        printf("Меню:\n");
        printf("1) Добавить запись\n");
        printf("2) Поиск по номеру заказа\n");
        printf("3) Сортировка по дате заказа\n");
        printf("4) Записать в файл\n");
        printf("5) Загрузить из файла\n");
        printf("6) Выход из программы\n");
        printf("Выберите пункт меню: ");
        scanf("%d", &choice);
        //Реализация меню
        switch (choice) {
        case 1:
            newRecord(programs, &size);
            break;
        case 2:
            printf("Введите номер заказа: ");
            record(programs, searchByNumber(programs, size));
            break;
        case 3:
            printf("\nОтсортированные данные по дате:\n");
            table();
            for (int i = 0; i < size; ++i) {
                record(sortByDate(programs, size), i);
            }
            break;
        case 4:
            if (writeToFile(programs, size) == 1) {
                printf("\nБаза данных успешно записана в файл.\n");
            }
            else {
                printf("Ошибка записи в файл.\n");
            }
            break;
        case 5:
            if (openFile(programs, &size) == 1) {
                printf("База данных успешно загружена из файла.\n");
            }
            else {
                printf("Ошибка записи из файла.\n");
            }
            break;
        case 6:
            printf("Программа завершена.\n");
            break;
        default:
            printf("Некорректный ввод. Пожалуйста, выберите существующий пункт меню.\n");
        }

    } while (choice != 6);
}
//Функция для добавления новой записи
int newRecord(struct software* programs, int* size) {
    if (*size < MAX_SIZE) {
        printf("Введите данные для программы:\n");
        printf("Номер заказа: ");
        scanf(" %d", &programs[*size].number);
        printf("Дата заказа(Формат ввода:День.Месяц.Год): ");
        scanf(" %d.%d.%d", &programs[*size].day, &programs[*size].month, &programs[*size].year);
        printf("Клиент(Например:И.И.Иванов): ");
        scanf(" %s", programs[*size].client);
        printf("Сумма заказа: ");
        scanf("%lf", &programs[*size].sum);
        printf("Статус заказа: ");
        scanf(" %s", programs[*size].status);
        (*size)++;
        return 1;
    }
    else {
        printf("База данных полна.\n");
        return 0;
    }
}
//Функция табулирования
void table() {
    printf("|  Номер заказа |  Дата заказа  |    Клиент     |  Сумма заказа | Статус заказа |\n");
}
//Функция вывода элемента БД
void record(struct software programs[], int i) {
    printf("|%15d|  %2d.%2d.%4d   |%15s|%13.2lf|%15s|\n", programs[i].number, programs[i].day, programs[i].month, programs[i].year, programs[i].client, programs[i].sum, programs[i].status);
}
//Функция поиска элемента БД по номеру заказа
int searchByNumber(struct software programs[], int size) {
    if (size > 0) {
        int searchNumber, index;
        scanf("%d", &searchNumber);
        for (int i = 0; i < size; ++i) {
            if (programs[i].number == searchNumber) {
                index = i;
            }
        }
        return index;
    }
    else {
        return 0;
    }
}
//Функция для сортировки БД по дате
struct software* sortByDate(struct software programs[], int size) {
    if (size > 0) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if ((programs[j].year > programs[j + 1].year) ||
                    (programs[j].year == programs[j + 1].year && programs[j].month > programs[j + 1].month) ||
                    (programs[j].year == programs[j + 1].year && programs[j].month == programs[j + 1].month && programs[j].day > programs[j + 1].day)) {
                    struct software temp = programs[j];
                    programs[j] = programs[j + 1];
                    programs[j + 1] = temp;
                }
            }
        }
        return programs;
    }
    else {
        return 0;
    }
}
//Функция для записи БД в файл
int writeToFile(struct software programs[], int size) {
    if (size > 0) {
        FILE* file;
        file = fopen("data.txt", "a");
        if (file == NULL) {
            return 0;
        }
        for (int i = 0; i < size; ++i) {
            fprintf(file, "%d %d %d %d %s %lf %s\n", programs[i].number, programs[i].day, programs[i].month, programs[i].year, programs[i].client, programs[i].sum, programs[i].status);
        }
        fclose(file);
        return 1;
    }
    else {
        return 0;
    }
}
//Функция для загрузки БД из файла
int openFile(struct software programs[], int* size) {
    if (*size < MAX_SIZE) {
        FILE* file;
        file = fopen("data.txt", "r");
        if (file == NULL) {
            return 0;
        }
        while (fscanf(file, "%d %d %d %d %s %lf %s", &programs[*size].number, &programs[*size].day,
            &programs[*size].month, &programs[*size].year, programs[*size].client, &programs[*size].sum,
            programs[*size].status) == 7) {
            (*size)++;
        }
        fclose(file);
        return 1;
    }
    else {
        return 0;
    }
}



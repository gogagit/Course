#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_SIZE 100
//���������� ���������
struct software {
    int number;
    int year;
    int month;
    int day;
    char client[20];
    double sum;
    char status[20];
};
// ��������� �������
int searchByNumber(struct software programs[], int size);
struct software* sortByDate(struct software programs[], int size);
int writeToFile(struct software programs[], int size);
int openFile(struct software programs[], int* size);
int newRecord(struct software* programs, int* size);
void record(struct software programs[], int i);
void table();
int main() {
    setlocale(LC_ALL, "RUS");
    //�������� �����
    printf("+----------------------------------------------+\n");
    printf("| ��������: ��������� ���� ��������            |\n");
    printf("| ������: ����-232                             |\n");
    printf("| ���������: ������ � �������� �� ������ �λ   |\n");
    printf("+----------------------------------------------+\n");
    struct software programs[MAX_SIZE];
    int size = 0;
    int choice,index;
    system("chcp 1251");
    do {
        //�������� ����
        printf("����:\n");
        printf("1) �������� ������\n");
        printf("2) ����� �� ������ ������\n");
        printf("3) ���������� �� ���� ������\n");
        printf("4) �������� � ����\n");
        printf("5) ��������� �� �����\n");
        printf("6) ����� �� ���������\n");
        printf("�������� ����� ����: ");
        scanf("%d", &choice);
        //���������� ����
        switch (choice) {
        case 1:
            newRecord(programs, &size);
            break;
        case 2:
            printf("������� ����� ������: ");
            record(programs, searchByNumber(programs, size));
            break;
        case 3:
            printf("\n��������������� ������ �� ����:\n");
            table();
            for (int i = 0; i < size; ++i) {
                record(sortByDate(programs, size), i);
            }
            break;
        case 4:
            if (writeToFile(programs, size) == 1) {
                printf("\n���� ������ ������� �������� � ����.\n");
            }
            else {
                printf("������ ������ � ����.\n");
            }
            break;
        case 5:
            if (openFile(programs, &size) == 1) {
                printf("���� ������ ������� ��������� �� �����.\n");
            }
            else {
                printf("������ ������ �� �����.\n");
            }
            break;
        case 6:
            printf("��������� ���������.\n");
            break;
        default:
            printf("������������ ����. ����������, �������� ������������ ����� ����.\n");
        }

    } while (choice != 6);
}
//������� ��� ���������� ����� ������
int newRecord(struct software* programs, int* size) {
    if (*size < MAX_SIZE) {
        printf("������� ������ ��� ���������:\n");
        printf("����� ������: ");
        scanf(" %d", &programs[*size].number);
        printf("���� ������(������ �����:����.�����.���): ");
        scanf(" %d.%d.%d", &programs[*size].day, &programs[*size].month, &programs[*size].year);
        printf("������(��������:�.�.������): ");
        scanf(" %s", programs[*size].client);
        printf("����� ������: ");
        scanf("%lf", &programs[*size].sum);
        printf("������ ������: ");
        scanf(" %s", programs[*size].status);
        (*size)++;
        return 1;
    }
    else {
        printf("���� ������ �����.\n");
        return 0;
    }
}
//������� �������������
void table() {
    printf("|  ����� ������ |  ���� ������  |    ������     |  ����� ������ | ������ ������ |\n");
}
//������� ������ �������� ��
void record(struct software programs[], int i) {
    printf("|%15d|  %2d.%2d.%4d   |%15s|%13.2lf|%15s|\n", programs[i].number, programs[i].day, programs[i].month, programs[i].year, programs[i].client, programs[i].sum, programs[i].status);
}
//������� ������ �������� �� �� ������ ������
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
//������� ��� ���������� �� �� ����
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
//������� ��� ������ �� � ����
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
//������� ��� �������� �� �� �����
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



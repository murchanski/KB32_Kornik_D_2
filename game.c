#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

void playGame() {
    system("chcp 65001");
    srand(time(NULL));
    int coins = 100;

    printf("Ласкаво просимо до гри \"Однорукий бандит\"!\n");
    printf("Правила гри:\n");
    printf("- Ви маєте певну кількість монет.\n");
    printf("- Ви ставите певну кількість монет і вводите довжину послідовності цифр.\n");
    printf("- Якщо у послідовності є хоча б одна цифра 7, ви виграєте свою ставку назад.\n");
    printf("- Якщо всі цифри у послідовності однакові, ви виграєте додатково.\n");
    printf("- Якщо хоча б одна третина цифр однакова, ви виграєте свою ставку назад.\n");
    printf("Виграші:\n");
    printf("- Якщо є хоча б одна 7: повернення ставки.\n");
    printf("- Якщо всі цифри однакові: ставка помножується на 2 (подвоюється).\n");
    printf("- Якщо хоча б одна третина цифр однакова: повернення ставки.\n");
    int length;
    printf("Введіть довжину послідовності: ");
    scanf("%d", &length);

    while (coins > 0) {
        int bet, win = 0;
        printf("У вас є %d монет\n", coins);
        printf("Введіть вашу ставку (0 для виходу): ");
        scanf("%d", &bet);

        if (bet == 0)
            break;
        if (bet > coins) {
            printf("Ви не можете зробити ставку більше, ніж у вас є монет!\n");
            continue;
        }

        int *sequence = malloc(length * sizeof(int));
        if (sequence == NULL) {
            printf("Помилка виділення пам'яті!\n");
            return;
        }

        printf("Послідовність: ");
        for (int i = 0; i < length; i++) {
            sequence[i] = rand() % 10;
            printf("%d ", sequence[i]);
            if (sequence[i] == 7)
                win = bet;
        }
        printf("\n");

        int *frequency = calloc(10, sizeof(int));
        if (frequency == NULL) {
            free(sequence);
            printf("Помилка виділення пам'яті!\n");
            return;
        }

        for (int i = 0; i < length; i++) {
            frequency[sequence[i]]++;
        }

        for (int i = 0; i < 10; i++) {
            if (frequency[i] == length) {
                win = i == 7 ? bet * 3 : bet * 2;
                printf("Всі цифри однакові! Виграш: %d\n", win);
                break;
            }
        }

        for (int i = 0; i < 10; i++) {
            if (frequency[i] >= (length + 2) / 3) {
                if (win == 0) {
                    win = bet;
                    printf("Хоча б одна третина цифр однакова! Виграш: %d\n", win);
                }
                break;
            }
        }

        coins = coins - bet + win;

        if (win) {
            printf("Вітаємо! Ви виграли %d монет\n", win);
        } else {
            printf("Вибачте! Ви втратили свою ставку!\n");
        }

        free(sequence);
        free(frequency);

        if (coins == 0) {
            printf("Ви витратили всі монети!\n");
        }
    }
    printf("Гра завершена!\n");
    printf("Ви залишились з %d монетами\n", coins);
}

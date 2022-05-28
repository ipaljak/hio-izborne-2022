#include <stdio.h>

int main() {
    int n, odgovor;
    scanf("%d", &n);

    printf("? 1 1\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("? 2 3\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("? 2 4\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("? 3 5\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("? 1 5\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("! 5\n");
    fflush(stdout);

    return 0;
}

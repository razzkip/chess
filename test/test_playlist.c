#include "chess.h"
#include "test.h"

int main(int argc, char** argv) {
    printf("starting test playlist...\n");

    int pass = 0;
    int total = sizeof(tests) / 8;

    for (int i = 0; i < total; i++) {
        printf("##[ TEST %05d ]------------------------------\n", i + 1);
        int result = (*tests[i])();
        if (result) {
            printf("no errors found...\n");
            pass++;
        }
    }

    printf("##[ RESULTS ]---------------------------------\n");
    printf("%5d PASSED (%0.4f%)\n", pass, (pass / total));
    printf("%5d TOTAL\n", total);

    return 0;
}

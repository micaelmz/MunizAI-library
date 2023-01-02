#include <stdio.h>
#include "pandas.c"
#include "ai.c"

int main() {
    int len_lines = 0;
    int len_column = 0;
    /*
    printf("CSV ORIGINAL:\n");
    double **csv = read_csv("data.csv", &len_lines, &len_column);
    print_csv(csv, len_lines, len_column);

    printf("Resultados:\n");
    double *result = copy_column(csv, len_lines, len_column, -1);
    print_csv(result, len_lines, 1);

    printf("Dados");
    remove_column(csv, &len_lines, &len_column,-1);
    print_csv(csv, len_lines, len_column);

    float nums[5] = {2, 2, 3};
    float pesos[5] = {10, 5, 10};

    printf("%f", weighted_mean(&nums, &pesos, 3));
        */

    printf("%d ", rand_int(1, 10));
    return 0;
}

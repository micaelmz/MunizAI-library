#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 9999
#define dataframe double**


// Check if a float is an integer.
// Input: num = number.
int is_float(float num){
    if (num == (int)num){
        return 0;
    }else{
        return 1;
    }
}

void initialize_vector(void *vector, int size, int type){
    if (type == 0){
        int *v = (int *)vector;
        for (int i = 0; i < size; i++){
            v[i] = 0;
        }
    }else if (type == 1){
        float *v = (float *)vector;
        for (int i = 0; i < size; i++){
            v[i] = 0;
        }
    }else if (type == 2){
        char *v = (char *)vector;
        for (int i = 0; i < size; i++){
            v[i] = 0;
        }
    }
}

// Prints a message error and exits the program.
// Input: message = message that will be printed.
void message_error(char message[]) {
    fprintf(stderr, "\n%s", message);
    system("pause");
    exit(1);
}

void calculate_columns_space(dataframe df, int len_lines, int len_column, int *columns_space){
    for (int i = 0; i < len_lines; i++){
        for (int j = 0; j < len_column; j++){
            int num = df[i][j];
            int space = 1;
            while (num > 10) {
                num /= 10;
                space = space + 1;
            }
            if (space > columns_space[j])
                columns_space[j] = space;
        }
    }
}

void print_matrix(dataframe df, int len_lines, int len_column, int limiter){
    int index_space = 1;

    int num = len_lines;
    while (num > 10) {
        num /= 10;
        index_space = index_space + 1;
    }

    // TODO - BUG: o limiter ta como 3 e não ta printando do mesmo jeito que tava printando antes com o limiter em 3, bugn nos pontinhos
    int is_float_column[len_column];
    int is_at_least_two_digits_column[len_column];
    int columns_space[len_column];
    initialize_vector(columns_space, len_column, 0);
    initialize_vector(is_at_least_two_digits_column, len_column, 0);
    initialize_vector(is_float_column, len_column, 0);

    calculate_columns_space(df, len_lines, len_column, columns_space);

    // define o limite
    if (len_lines < 5)
        limiter = len_lines;

    // prints the matrix
    // TODO - instead of using a if for not print while loop, but loop even if isnt printing, just push the loop to the end of the matrix, making it faster
    for (int i = 0; i < len_lines; i++) {
        if (i < limiter || i >= len_lines - 5) {
            printf("%-*d   ", index_space, i);
            for (int j = 0; j < len_column; j++) {
                if (df[i][j] >= 10)
                    is_at_least_two_digits_column[j] = 1;
                if (is_float(df[i][j]))
                    is_float_column[j] = 1;
                if (is_float_column[j]) {
                    if (is_at_least_two_digits_column[j] && df[i][j] < 10)
                        printf("0");
                    printf("%*.2f  ", columns_space[j], df[i][j]);
                }else{
                    printf("%*.0f  ", columns_space[j], df[i][j]);
                }
            }
            printf("\n");
        }
        else if (i == limiter) {
            for (int j = 0; j < len_column; j++) {
                if (is_float(df[i][j]) || is_float_column[j]) {
                    // TODO - This if isnt 100% right, because it's only checking the first number after the limiter, should check all the numbers after the limiter.
                    if (df[i][j] >= 10)
                        printf("%-*s  ", columns_space[j] + 2, "...");
                    else
                        printf("%-*s  ", columns_space[j] + 1, "...");
                } else {
                    printf("%*s  ", columns_space[j], "...");
                }
            }
            printf("\n");
        }
    }
}

//
void head(dataframe df, int len_column, int num_lines) {
    print_matrix(df, num_lines, len_column, num_lines);
}

// Reads a CSV file and returns a matrix with the data in double format. (It doesn't work with strings).
// Entradas: filename = nome do arquivo .csv, len_lines = ponteiro para a variavel que armazenará o numero de linhas do arquivo, len_column = ponteiro para a variavel que armazenará o numero de colunas do arquivo.
double **read_csv(const char *filename, int *len_lines, int *len_column) {
    // TODO - Type number or string

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        message_error("Error while opening the file.\n");
    }

    double **csv = NULL;
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, fp) != NULL) {
        *len_lines += 1;
        csv = realloc(csv, (*len_lines) * sizeof(double *));

        // Find the end of the line
        char *newline = strchr(line, '\n');
        if (newline) {
            *newline = '\0';
        }

        // Make a copy of the line to use with strtok
        char line_copy[MAX_LINE];
        strcpy(line_copy, line);

        // Reset len_column for the current line
        *len_column = 0;

        // Conta o número de colunas da linha atual
        char *token = strtok(line_copy, ",");
        while (token != NULL) {
            *len_column += 1;
            token = strtok(NULL, ",");
        }
        // Aloca um vetor para armazenar os dados da linha atual
        csv[*len_lines - 1] = malloc(*len_column * sizeof(double));

        // Lê os dados da line e armazena na matrix
        token = strtok(line, ",");
        int i = 0;
        while (token != NULL) {
            csv[*len_lines - 1][i++] = atof(token);
            token = strtok(NULL, ",");
        }
        // Resize the memory block to the actual number of elements in the line
        csv[*len_lines - 1] = realloc(csv[*len_lines - 1], i * sizeof(double));
    }
    fclose(fp);

    print_matrix(csv, *len_lines, *len_column, 5);
    // TODO - quebrar se tiver muitas colunas também (mais de 10)

    printf("\n[%d rows x %d columns]\n", *len_lines, *len_column);

    return csv;
}

// Imprime a matriz do df em um formato semelhante ao pandas
// Entradas: df = matriz com os dados do arquivo df, len_lines = numero de linhas da matriz, len_column = numero de colunas da matriz
void print_csv(dataframe df, int len_lines, int len_column) {
    if (!df)
        message_error("Error while printing the df.\n");

    int i = 0;
    if (len_column == 1) {
        for (i = 0; i < len_lines; i++) {
            printf("%d| %f |", i, df[i]);
            printf("\n");
        }
    }else{
        for (int i = 0; i < len_lines; i++) {
            printf("%d| ", i);
            for (int j = 0; j < len_column; j++) {
                printf("%.2f| ", df[i][j]);
            }
            printf("\n");
        }
    }
}

// Embaralha as linhas da matriz do df
// Entradas: df = matriz com os dados do arquivo df, len_lines = numero de linhas da matriz, len_column = numero de colunas da matriz
void shuffle(dataframe df, int len_lines, int len_column) {
    if (!df)
        message_error("Error while shuffling the df.\n");

    int *index = malloc(len_lines * sizeof(int));
    for (int i = 0; i < len_lines; i++) {
        index[i] = i;
    }

    srand(time(NULL));
    for (int i = len_lines - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = index[i];
        index[i] = index[j];
        index[j] = temp;
    }

    // Percorre o vetor de índices embaralhados e embaralha a matriz diretamente no ponteiro
    for (int i = 0; i < len_lines; i++) {
        for (int j = 0; j < len_column; j++) {
            double temp = df[i][j];
            df[i][j] = df[index[i]][j];
            df[index[i]][j] = temp;
        }
    }

    free(index);
}

// Remove uma coluna da matriz do df
// Entradas df = matriz com os dados do arquivo df, len_lines = numero de linhas da matriz, len_column = numero de colunas da matriz, column = coluna a ser removida
double **remove_column(dataframe df, int *len_lines, int *len_column, int column) {
    if (!df)
        message_error("Error while removing the column.\n");
    if (column >= *len_column) {
        message_error("Error while removing the column, the column number is bigger than the number of columns.\n");
    }

    if (column < 0){
        column = *len_column - column;
    }

    double **new_csv = malloc(*len_lines * sizeof(double *));

    for (int i = 0; i < *len_lines; i++) {
        new_csv[i] = malloc((*len_column - 1) * sizeof(double));
        int j = 0;
        for (int k = 0; k < *len_column; k++) {
            if (k != column) {
                new_csv[i][j++] = df[i][k];
            }
        }
    }

    *len_column -= 1;
    //printf("len_lines: %d, len_column: %d\n", *len_lines, *len_column);
    return new_csv;
}

// Copia uma coluna da matriz do df
// Entradas df = matriz com os dados do arquivo df, len_lines = numero de linhas da matriz, len_column = numero de colunas da matriz, column = coluna a ser copiada
double *copy_column(dataframe df, int len_lines, int len_column, int column) {
    if (!df)
        message_error("Error while copying the column.\n");
    if (column >= len_column) {
        message_error("Error while copying the column, the column number is bigger than the number of columns.\n");
    }

    if (column < 0){
        column = len_column + column;
    }
    double *new_column = malloc(len_lines * sizeof(double));
    for (int i = 0; i < len_lines; i++) {
        new_column[i] = df[i][column];
    }
    return new_column;
}

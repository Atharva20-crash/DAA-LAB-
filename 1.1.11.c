 #include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, W;

    if (scanf("%d", &n) != 1) return 0;

    int *values = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(n * sizeof(int));


    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }


    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }


    scanf("%d", &W);


    int *dp = (int *)calloc(W + 1, sizeof(int));


    for (int i = 0; i < n; i++) {
        int current_weight = weights[i];
        int current_value = values[i];
        

        for (int j = W; j >= current_weight; j--) {
            dp[j] = max(dp[j], dp[j - current_weight] + current_value);
        }
    }


    printf("%d\n", dp[W]);

    free(values);
    free(weights);
    free(dp);

    return 0;
}
 

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int bottom_up_dp(int n, int *s, int *v, int C)
{
    //write your code here
    // Create and initialize the memory for the memoization table
    int **M = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        M[i] = (int *)malloc((C + 1) * sizeof(int));
        // Initialize the first row to 0
        M[i][0] = 0;
    }

    // Initialize the first column to 0
    for (int j = 0; j <= C; j++) {
        M[0][j] = 0;
    }

    // Fill the memoization table using bottom-up dynamic programming
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= C; j++) {
            if (s[i] <= j) {
                // If the current item can fit into the knapsack, choose the maximum between
                // taking the current item and not taking it
                M[i][j] = (v[i] + M[i - 1][j - s[i]]) > M[i - 1][j] ? (v[i] + M[i - 1][j - s[i]]) : M[i - 1][j];
            } else {
                // If the current item cannot fit into the knapsack, just take the value from the previous row
                M[i][j] = M[i - 1][j];
            }
        }
    }

    // Store the maximum value in the knapsack
    int max_value = M[n][C];

    // Free the memory allocated for the memoization table
    for (int i = 0; i <= n; i++) {
        free(M[i]);
    }
    free(M);

    return max_value;
}

 
int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
        
}

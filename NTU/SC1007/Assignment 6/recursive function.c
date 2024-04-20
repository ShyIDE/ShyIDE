#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int memo[1000] = {0};

int F(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    
    // If value of F(n) is already computed, return it from memo array
    if (memo[n] != 0)
        return memo[n];
    
    // Compute F(n) recursively and store it in memo array
    memo[n] = F(n-1) + 2*F(n-2) - 3*F(n-3);
    return memo[n];
}

int top_down_dp(int n) {
    return F(n);
}

 
int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
        
}

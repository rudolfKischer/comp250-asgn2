#include <iostream>
#include <limits>
#include <cmath>



float choose(float n, float k) {
    if (k == 0 || k == n) {
        return 1;
    }
    return choose(n - 1, k - 1) + choose(n - 1, k);
}

float choose_iterative(float n, float k) {
    float result = 1;
    for (int i = 1; i <= k; i++) {
        result *= (n - k + i) / i;
    }
    return result;
}

float binomial( float p, float k, float n) {
    return choose_iterative(n, k) * pow(p, k) * pow(1 - p, n - k);
}

float X(float p, float k, float N) {
    float x = 1.0f;
    for (int j = 1 ; j <= k ; j++) {
        x *= (N + 1-j);
    }

    for (int j = 1 ; j <= k ; j++) {
        x /= j;
    }

    for (int j = 1 ; j <= k ; j++) {
        x *= p;
    }

    float q = 1 - p;

    for (int j = (k+1) ; j <= N ; j++) {
        x *= q;
    }

    return x;

}

float numerical_upkeep(float x, float b, int* b_count) {
    float s = 1.0f / b;
    if (x >= b) {
        (*b_count)++;
        x *= s;
    }
    if (x <= s) {
        (*b_count)--;
        x *= b;
    }
    return x;
}

float X_fixed(float p, float k, float N) {

    float x = 1.0f;
    int b_count = 0;
    float b = pow(2, 100);
    float s = 1.0f / b;
    
    //max: 2 ^ 117
    //min : 2 ^ -115
    for (int j = 1 ; j <= k ; j++) {
        x *= (N + 1-j);
        x = numerical_upkeep(x, b, &b_count);
    }

    for (int j = 1 ; j <= k ; j++) {
        x /= j;
        x = numerical_upkeep(x, b, &b_count);
    }

    for (int j = 1 ; j <= k ; j++) {
        x *= p;
        x = numerical_upkeep(x, b, &b_count);
    }

    float q = 1.0f - p;

    for (int j = (k+1) ; j <= N ; j++) {
        x *= q;
        x = numerical_upkeep(x, b, &b_count);
    }

    printf("b_count: %d\n", b_count);

    for (int i = 0; i < b_count; i++) {
        x *= b;
    }

    return x;

}



int main() {

    // Question a)
    std::cout << "ASGN-1" << std::endl;
    float x = X_fixed(0.1f,200.0f,2000.0f);
    printf("X(0.1,200,2000) =  %.12f\n", x);


    return 0;
}
#include <iostream>
#include <unordered_map>

// double x_0 = 1.0;
double x0 = 1.0;


std::unordered_map<int, double> memo;
std::unordered_map<int, double> memo_fixed;
double f(int n) {
  if (memo.find(n) != memo.end()) {
    return memo[n];
  }

  if (n == 0) {
    memo[0] = x0;
    return x0;
  }
  float under_sqrt = 1.0 + pow(2.0, -(n-1)) * f(n-1);
  printf("under_sqrt = %.30f\n", under_sqrt);

  memo[n] = pow(2.0, n) * (sqrt(under_sqrt) -1.0);
  return memo[n];
}

double f_fixed(int n) {
  if (memo_fixed.find(n) != memo_fixed.end()) {
    return memo_fixed[n];
  }

  if (n == 0) {
    memo_fixed[0] = x0;
    return x0;
  }

  float x_n = f_fixed(n-1);

  float under_sqrt = 1.0 + pow(2.0, -(n-1)) * x_n;
  // printf("under_sqrt = %.30f\n", under_sqrt);

  memo_fixed[n] = (2.0 * x_n) / (sqrt(under_sqrt) + 1.0);
  return memo_fixed[n];
}



double h(int n) {
  return f(n) - log(x0 + 1.0);
}

double h_fixed(int n) {
  return f_fixed(n) - log(x0 + 1.0);
}


int main() {

    int m = 60;

    // Question a)

    for (int i = 0; i <= m; i++) {
        printf("f(%d) = %.30f\n", i, f(i));
    }

    for (int i = 0; i <= m; i++) {

        
        printf("h(%d) = %.30f\n", i, h(i));
    }

    //question b)

    for (int i = 0; i <= m; i++) {
        // printf("f(%d) = %.30f\n", i, f(i));
        // printf("f_fixed(%d) = %.30f\n", i, f_fixed(i));
        
        printf("h_fixed(%d) = %.30f\n", i, h_fixed(i));
    }




    return 0;
}
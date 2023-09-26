# Assignment 2

## Numerical Computing

*Rudolf C. Kischer*

*260956107*

### Floating point in C, Overflow and Underflow, numerical cancellation

---
#### Q1.

- a) Write a program according to this pseudocode to compute 𝑋(0.1,200,2000)
. Notice the true value of 𝑋(0.1,200,2000)
 is approximately equal to 0.03
. Comment on the difficulties you encounter.

```c++
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
```

#### Computed Result

**Input:**
```c
int main() {

    // Question a)
    std::cout << "ASGN-1" << std::endl;
    printf("Part A\n");
    float x = X(0.1f,200.0f,2000.0f);
    printf("X(0.1,200,2000) =  %.12f\n", x);
}
```

**Output:**
```
ASGN-1
Part A
X(0.1,200,2000) =  inf
```


**Explanation**: 
- The trouble with this code and these inputs , is that at certain parts of the computation, our intermediate result exceeds the largest number that can be represented by a float. This is called an overflow. 
- When this happens, the result is set to infinity. This is what we see in the output. 
- This is interesting because our final result is representable by a float, because as a the calculation continues the result is divided by a large number, which brings it back down to a representable number. 
- Most operations that include infinity, will result in infinity. This means that there is no way to recover from this error.

- Note: If we performed our operations in a different order we may get an underflow, Nan, or a 0, which is might also not be recoverable.


- b) **Question:** Modify your program and try it on the problem in 1(a).The final result for 𝑋(𝑝,𝑘,𝑁)
 should be a floating point number (in decimal exponent format)

**Answer:**

This code is responsible for growing or shrinking the number to keep it in the range of representable numbers. We also keep track of how often this is done with the b_count variable.

```c++
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
```
Here we have modified the original code so that we perform the house keeping on the number after each operation. This ensures that the number is always in the range of representable numbers. At the end we multiply the number by `b` to get the final result.

 ```c++
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
 ```

 **Input**:


 ```c++
int main() {

    // Question b)
    printf("Part B\n");
    float x_fixed = X_fixed(0.1f,200.0f,2000.0f);
    printf("X_fixed(0.1,200,2000) =  %.8e\n", x_fixed);

    return 0;
}
 ```

 **Output:**

 ```
Part B
b_count: 0
X_fixed(0.1,200,2000) =  2.97215302e-02
 ```

 **Explanation:** Here we can see that the numerical answer is no longer an `inf` calue and is within the range of the expected answer which was `0.03`







---
#### Q2.




For any 𝑥0>−1
, the sequence defined recursively by

$$x_{n+1}=2^{n+1}(\sqrt{1+2^{-n}x_n}-1), \qquad (n\geq 0)$$

converges to ln(𝑥0+1)

**Question:**
a)Let $x_0 = 1$.Use the  formula to compute $x_n-\ln(x_0+1)$ 𝑛=1,2,…,60 in double precision. Explain your results

**Answer:**

**Recursive Fuction Definition**

```c++
double x0 = 1.0;


std::unordered_map<int, double> memo;
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
```

**Difference from convergent Value**
```c++
double h(int n) {
  return f(n) - log(x0 + 1.0);
}
```

**Input:**

```c++
int main() {

    int m = 60;

    // Question a)
    for (int i = 0; i <= m; i++) {
        printf("h(%d) = %.8e\n", i, h(i));
    }
}
```

**Output:**

```
f(0) = 1.000000000000000000000000000000e+00
f(1) = 8.284270763397216796875000000000e-01
f(2) = 7.568283081054687500000000000000e-01
...
f(58) = 0.000000000000000000000000000000e+00
f(59) = 0.000000000000000000000000000000e+00
f(60) = 0.000000000000000000000000000000e+00
```

```
h(0) = 3.06852819e-01
h(1) = 1.35279896e-01
h(2) = 6.36811275e-02
h(3) = 3.09147854e-02
h(4) = 1.52325649e-02
...
h(57) = -6.93147181e-01
h(58) = -6.93147181e-01
h(59) = -6.93147181e-01
h(60) = -6.93147181e-01
```

See the attached file `q2a.txt` for the full output.

**Explanation:** 
- We can see clearly that we did not get the result we wanted. We can deduce by our formula for `h(x)` that our value for `f(x)` wen to zero at some point during our computation. The computed result for `f(x)` also demonstrates that. 

- This is because our the value under the square root becomes a number that is very close to 1, but not exactly 1. The difference becomes so small, that it cannot be properly represented and is rounded down. This cancled out with the negative 1, which is why we get 0. 

- Although the value for one intermediate part of our computed result is not representable in our floating point system, the final result should still be representable. This is because the final result is the product of a large number ($2^{n+1}$) and a very small number.

- This is not the case however, because the intermediate result is rounded down to 0, this means that the final result is also 0.

**Question:**

b)  Improve the formula to avoid the difficulty you encountered in 2(a). Again compute $x_n - \ln(x_0+1)$ for 𝑛=1,2,…,60 in double precision.

**Answer:**

**Solution**: As seen in class , a technique to avoid this is by multiplying by the conjugate, also known as rationalization. This is done by multiplying by the conjugate of the numerator and denominator. 

$$x_{n+1}=2^{n+1}(\sqrt{1+2^{-n}x_n}-1) \cdot \frac{\sqrt{1+2^{-n}x_n}+1}{\sqrt{1+2^{-n}x_n}+1}$$

$$\implies x_{n+1} = \frac{2 \cdot x_n}{\sqrt{1+2^{-n}x_n}+1}$$

We can see that this formula is much more stable, because we dont have intermediate values that cancel out.


Below is the code to support that change.
```c++

std::unordered_map<int, double> memo_fixed;
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

  memo_fixed[n] = (2.0 * x_n) / (sqrt(under_sqrt) + 1.0);
  return memo_fixed[n];
}
```

```c++
double h_fixed(int n) {
  return f_fixed(n) - log(x0 + 1.0);
}
```

**Input:**

```c++
int main() {

    int m = 60;
    for (int i = 0; i <= m; i++) {
        printf("f_fixed(%d) = %.12e\n", i, f_fixed(i));
    }
    for (int i = 0; i <= m; i++) {
        printf("h_fixed(%d) = %.12e\n", i, h_fixed(i));
    }
    return 0;
}
```

**Output:**
```
f_fixed(0) = 1.000000000000e+00
f_fixed(1) = 8.284271330514e-01
f_fixed(2) = 7.568284833700e-01
...
f_fixed(58) = 6.931475400925e-01
f_fixed(59) = 6.931475400925e-01
f_fixed(60) = 6.931475400925e-01
```


```
h_fixed(0) = 3.068528194401e-01
h_fixed(1) = 1.352799524915e-01
h_fixed(2) = 6.368130281005e-02
...
h_fixed(58) = 3.595325229755e-07
h_fixed(59) = 3.595325229755e-07
h_fixed(60) = 3.595325229755e-07
```

See the attached file `q2b.txt` for the full output.

**Explanation:** Now the error stabilizes, and does not increase as we continue to compute. This is because by rationalizing we have avoided the intermediate values that cancel out. The final result of `f(x)` is also very close to the expected value of `ln(2)`.  

---
#### Q3.


$$1 + \frac{1}{4} + \frac{1}{9} + \frac{1}{16} + ...$$

converges to $\frac{\pi^2}{6}$

**Question:**

a)  Write a C program to sum the series, terminating if the sum is unchanged by the addition of a term. How good is the result using single precision?


**Answer:**


Summation Function:

```c++
float sum_square_reciprocals(int n){
    float sum = 0.0f;
    for(int i=1; i<=n; i++) {
        sum += 1.0f / pow(i, 2.0f);
    }
    return sum;
}
```

Approximation Function:

```c++
float approach_congergent_value() {
    float convergent_value = pow(M_PI,2) / 6.0f;
    float prev_diff = MAXFLOAT;
    int i = 0;

    while (true) {
      float sum = sum_square_reciprocals(i);
      printf("i = %d, sum = %.30f\n", i, sum);
      //difference between convergent value and sum
      float diff = fabs(convergent_value - sum);
      if (diff >= prev_diff) {
        break;
      }
      prev_diff = diff;
      i++;
    }
    return sum_square_reciprocals(i-1);
}
```

**Input:**

```c++
int main() {

    float sum = approach_congergent_value();

    return 0;
}
```

**Output:**

```
i = 0, sum = 0.0000000000000000000000000e+00
i = 1, sum = 1.0000000000000000000000000e+00
i = 2, sum = 1.2500000000000000000000000e+00
...
i = 4095, sum = 1.6447252035140991210937500e+00
i = 4096, sum = 1.6447253227233886718750000e+00
i = 4097, sum = 1.6447253227233886718750000e+00
```

`True convergent_value = 1.644934058189392089843750000000`

**Explanation:** The appoximation takes many iterations, to reach a value which does not change. We can see that the value, although approaching the convergent value, only is accurate to 3 decimal places. This is a poor result in the context of numerical computing. 

**Question:**
b) Give an explanation for the poor result. Suppose we want to get higher accuracy based on the above series still using single precision. How do you solve this problem?

**Answer:**
- Although this series is said to converge, it converges at the limit as n goes to infinity. However, the series converges slowly, because the terms become very small fast as because the denominator increases by the square of the index. This means that we need to add many terms to get a good approximation. 

- Because the terms become increasingly small, they eventually reach a point where each new term is no longer representable in the range of single precision floating point numbers, When it reaches this point, we can no longer add to the sum, because the new term is rounded down to 0.

- There are a couple cop out solutions. One of them being directly computing the convergent value. The series can be rearranged to the convergent value, and then we can compute PI use many other methods, which might not have this problem.

- Another solution to get higher accuracy is to use double precision. This will allow us to add more terms to the sum, before we reach the limit of representable numbers.

- Both of these solutions are not ideal, because they do not directly solve the problem.
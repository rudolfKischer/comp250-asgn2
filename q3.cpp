#include <iostream>
#include <cmath>

float geometric_sum(int n){

    float sum = 0.0f;
    for(int i=1; i<=n; i++) {
        sum += 1.0f / pow(i, 2.0f);
    }

    return sum;

}

int main() {

  float convergent_value = pow(M_PI,2) / 6.0f;

  float prev_diff = MAXFLOAT;
  // for (int i = 1; i <= 5000; i++) {

  //   float sum = geometric_sum(i);
  //   // printf("i = %d, sum = %.30f\n", i, sum);
  //   //difference between convergent value and sum
  //   float diff = fabs(convergent_value - sum);
  //   printf("i = %d, diff = %.30f\n", i, diff);


  // }

  int i = 0;

  while (true) {
    float sum = geometric_sum(i);
    printf("i = %d, sum = %.30f\n", i, sum);
    //difference between convergent value and sum
    float diff = fabs(convergent_value - sum);
    // printf("i = %d, diff = %.30f\n", i, diff);

    if (diff >= prev_diff) {
      break;
    }

    prev_diff = diff;
    i++;
  }

  printf("convergent_value = %.30f\n", convergent_value);

  



    return 0;
}
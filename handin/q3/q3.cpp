#include <iostream>
#include <cmath>

float sum_square_reciprocals(int n){
    float sum = 0.0f;
    for(int i=1; i<=n; i++) {
        sum += 1.0f / pow(i, 2.0f);
    }
    return sum;
}

//alternative sum
// trying to avoid underflow truncation
float sum_square_reciprocals_alternative(int n){
    float b = pow(2.0f, 100.0f);
    float sum = 0.0f;

    


    for(int i=1; i<=n; i++) {
        if ((1 / (pow(i, 2.0f))) == 0.0f) {
          sum += 1 / (pow(i, 2.0f) * b);

        } else {
          sum += 1 / (pow(i, 2.0f));
        }

    }
    return sum;
}

float approach_congergent_value() {

    float convergent_value = pow(M_PI,2) / 6.0f;
    float prev_diff = MAXFLOAT;

    int i = 0;

    while (true) {
      float sum = sum_square_reciprocals(i);
      printf("i = %d, sum = %.25e\n", i, sum);
      //difference between convergent value and sum


      float diff = fabs(convergent_value - sum);
      // printf("i = %d, diff = %.30f\n", i, diff);




      if (diff >= prev_diff) {
        break;
      }

      prev_diff = diff;
      i++;
    }

    return sum_square_reciprocals(i-1);
}



float approach_congergent_value_alternative() {

    float convergent_value = pow(M_PI,2) / 6.0f;
    float prev_diff = MAXFLOAT;

    int i = 0;

    while (true) {
      float sum = sum_square_reciprocals_alternative(i);
      printf("i = %d, sum = %.25e\n", i, sum);
      //difference between convergent value and sum
      float diff = fabs(convergent_value - sum);
      // printf("i = %d, diff = %.30f\n", i, diff);


      if (diff >= prev_diff) {
        break;
      }

      prev_diff = diff;
      i++;
    }

    return sum_square_reciprocals_alternative(i-1);
}

int main() {
    float convergent_value = pow(M_PI,2) / 6.0f;
    // float sum = approach_congergent_value();
    // printf("True convergent_value = %.30f\n", convergent_value);

    float sum = approach_congergent_value_alternative();
    printf("True convergent_value = %.30f\n", convergent_value);
    return 0;
}
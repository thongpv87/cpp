#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint>
#include<limits>

/* Problem 1: reverse 32 bit number
 * Idea:
 *   - Convert the number to array of its digit
 *   - Compute the reversed number after from the array
 */

std::int32_t problem1(std::int32_t m) {
  if (m > 2147447412)
    return 0;
  auto n = std::abs(m);
  std::int32_t sign = m > 0 ? 1 : -1;
  int arr[10];

  int l = 0;
  do {
    arr[l] = n % 10;
    n = n / 10;
    l++;
  } while (n > 0);

  std::int32_t s = 0;
  for (int i = 0; i < l-1; i++) {
    s = s * 10 + arr[i];
  }
  if (s > (std::numeric_limits<std::int32_t>::max() - arr[l-1])/10) {
    return 0;
  }
  s = s * 10 + arr[l-1];
  return s * sign;
}


/* Problem 2: find lonely number
Idea:
  - There are 2n + 1 numbers, if n == 1 return the number the only number
  - Chose a number at position m near the middle that are even
  - The list is divided into two sublist, from [0 , m] contains m+1 numbers, and from [m + 2, len-1] contains m-1 numbers
  - If arr[m] != arr[m+1], find the result in the first list, otherwise find the result in the second list
   */
int problem2(const int * arr, int len) {
  if (len == 1)
    return arr[0];
  auto m = len / 2;
  if (m % 2 == 1) {
    m--;
  }
  if (arr[m] != arr[m + 1]) {
    return problem2(arr, m+1);
  }
  return problem2(arr+m + 2, len - m -2);
}

/* Problem3: divide number */
std::int32_t problem3(std::int32_t dividend, std::int32_t divisor) {
    //handle the edge case where -2^31/-1 = 2^31
    if (dividend == std::numeric_limits<std::int32_t>::min() && divisor == -1) {
        return std::numeric_limits<std::int32_t>::max();
    }

    std::int32_t sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;
    dividend = abs(dividend);
    divisor = abs(divisor);

    std::int32_t q = 0;
    while (dividend >= divisor) {
        dividend -= divisor;
        q++;
    }

    return sign * q;
}

void test_problem1();
void test_problem2();
void test_problem3();


int main() {
  test_problem1();
  test_problem2();
  return 0;
}

void test_problem1() {
  assert(problem1(12345) == 54321);
  assert(problem1(-12345) == -54321);
  assert(problem1(2147483648) == 0);
  assert(problem1(2112222222) == 0);
  assert(problem1(2147447412) == 2147447412);
  assert(problem1(-2147447412) == -2147447412);
  assert(problem1(-2137447512) == 0);
}

void test_problem2(){
  std::vector<int> a{1};
  auto x = std::vector<int> {1, 2, 2, 3, 3, 4, 4, 5, 5};
  auto y = std::vector<int> {1, 1, 2, 3, 3, 4, 4, 5, 5};
  auto z = std::vector<int> {1, 1, 2, 2, 3, 4, 4, 5, 5};
  auto k = std::vector<int> {1, 1, 2, 2, 3, 3, 4, 5, 5};
  auto t = std::vector<int> {1, 1, 2, 2, 3, 3, 4, 4, 5};
  auto x1 = std::vector<int> {1, 2, 2, 3, 3, 4, 4};
  auto y1 = std::vector<int> {1, 1, 2, 3, 3, 4, 4};
  auto z1 = std::vector<int> {1, 1, 2, 2, 3, 4, 4};
  auto k1 = std::vector<int> {1, 1, 2, 2, 3, 3, 4};


  assert(problem2(a.data(), a.size()) == 1);
  assert(problem2(x.data(), x.size()) == 1);
  assert(problem2(y.data(), y.size()) == 2);
  assert(problem2(z.data(), z.size()) == 3);
  assert(problem2(k.data(), k.size()) == 4);
  assert(problem2(t.data(), t.size()) == 5);
  assert(problem2(x1.data(), x1.size()) == 1);
  assert(problem2(y1.data(), y1.size()) == 2);
  assert(problem2(z1.data(), z1.size()) == 3);
  assert(problem2(k1.data(), k1.size()) == 4);
}

void test_problem3() {
  assert((problem3(7, 2) == 3));
  assert((problem3(-7, 2) == -3));
  assert((problem3(std::numeric_limits<std::int32_t>::min(), -1) == std::numeric_limits<std::int32_t>::max()));
  assert((problem3(std::numeric_limits<std::int32_t>::min() + 1, -1) == std::numeric_limits<std::int32_t>::max()));
  assert((problem3(std::numeric_limits<std::int32_t>::max(), 1) == std::numeric_limits<std::int32_t>::max()));
}

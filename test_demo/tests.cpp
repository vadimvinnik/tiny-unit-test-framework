/*

Tiny unit test framework for C++

Vadim Vinnik, 2013
e-mail: vadim.vinnik@gmail.com

*/

/*
This project demonstrates how to define tests and link them to a test harness
application.
*/

#include "test_implementation.h"

UNIT_TEST(Integer_Multiplication)
  TEST_ASSERTION(7 * 8 == 56)
END_UNIT_TEST

UNIT_TEST(Integer_Addition)
  int x = 9;
  int y = 4;
  TEST_ASSERTION(x + y == 13)
END_UNIT_TEST

UNIT_TEST(Must_Fail)
  int x = 5;
  TEST_ASSERTION(x * x == x)
END_UNIT_TEST

void TEST_CASE_Complicated(int x, int y) {
  TEST_ASSERTION(x * x == y)
}

UNIT_TEST(Complicated)
  TEST_CASE_Complicated(2, 4);
  TEST_CASE_Complicated(3, 9);
  TEST_CASE_Complicated(5, 25);
END_UNIT_TEST

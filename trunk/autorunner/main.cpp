/*

Tiny unit test framework for C++

Vadim Vinnik, 2013
e-mail: vadim.vinnik@gmail.com

*/

/*
Thiis file defines a common (and, probably, general enough) empty test harness
application template.

Note that it is a library that nevertheless has main(). Therefore, the actual
test harness application should only contain test definitions and link this
library.

The template reports about each test to stdout right after it is finished.
After processing all tests, it writes detailed information about each failed
test (if any).

The template reports each completed test to stdout right after it is finished.
After processing all tests, it prints detailed report about all failed tests.
Exit codes (0 for success and -1 for failure) makes it suitable for using in
automated build scripts.
*/

#include <iostream>
#include <iomanip>
#include "test_interface.h"

using std::cout;
using std::endl;
using UnitTestFramework::UnitTestsSummary;
using UnitTestFramework::UnitTestResultInfo;

QUIET_TEST_START

ON_TEST_COMPLETION(result) {
  static const int test_name_width = 60;
  static const int test_result_width = 10;
  static const char message_ok[] = "Passed";
  static const char message_failed[] = "FAIL!";

  cout
    << std::setw(test_name_width)
    << std::left
    << result.name()
    << std::setw(test_result_width)
    << (result.success() ? message_ok : message_failed)
    << endl;
}

void printFailedTestDetails(UnitTestResultInfo const& info) {
  cout
    << endl
    << info.name()
    << endl
    << "\tAt line "
    << info.line()
    << endl
    << "\t("
    << info.condition()
    << ")"
    << endl;
}

int main() {
  if (0 != UnitTestsSummary::failedCount()) {
    cout
      << endl
      << UnitTestsSummary::failedCount()
      << " of "
      << UnitTestsSummary::count()
      << " tests failed. See details below"
      << endl;

    UnitTestsSummary::for_each_failed(printFailedTestDetails);

    return -1;
  }

  std::cout
    << std::endl
    << "All "
    << UnitTestsSummary::count()
    << "tests passed"
    << std::endl;

  return 0;
}

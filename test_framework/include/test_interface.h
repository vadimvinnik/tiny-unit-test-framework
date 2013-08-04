/*

Tiny unit test framework for C++

Vadim Vinnik, 2013
e-mail: vadim.vinnik@gmail.com

*/

/*
This header file is to be included into a test harness application to
- pass there notifications about each started and finished test;
- access summary information when all tests are finished.

ON_TEST_START(some_name) { body } defines a callback that notifies about
a started test, some_name is a user-defined name for an std::string parameter
that contains the name of the test and can be used in the body.

ON_TEST_COMPLETION(some_name) { body } defines a callback that notifies about
a finished test, some_name is a user-defined name for an parameter of type
UnitTestResultInfo const& that carries information abut test success status,
failed condition and its line number (if failed).

Since all tests are executed before entering main(), callbacks must not depend
on any initialization performed in it.

To suppress notifications about started or finished tests, use, respectively,
QUIET_TEST_START or QUIET_TEST_COMPLETION in the harness application. Use
QUIET_TEST_PROGRESS to suppress both kinds of notifications. Each of the two
callbacks must be either defined or suppressed.

Processing results should be implemented in or called from main(). Use static
methods of UnitTestsSummary class to get count of tests (total and failed), to
iterate through all test results and through failed tests.
*/

#ifndef _TEST_INTERFACE_
#define _TEST_INTERFACE_

#include <algorithm>
#include <functional>
#include <list>
#include <string>

namespace UnitTestFramework {

class UnitTestResultInfo {
public:
  UnitTestResultInfo(std::string name_, bool success_ = true, std::string condition_ = std::string(), int line_ = -1) :
    m_name(name_),
    m_success(success_),
    m_condition(condition_),
    m_line(line_)
  {}

  std::string name() const { return m_name; }
  bool success() const { return m_success; }
  std::string condition() const { return m_condition; }
  int line() const { return m_line; }

protected:
  std::string m_name;
  bool m_success;
  std::string m_condition;
  int m_line;
};


// to be defined by the user
void OnTestStart(std::string);
void OnTestCompletion(UnitTestResultInfo const&);


typedef std::list<UnitTestResultInfo> UnitTestResultsList;
typedef UnitTestResultsList::const_iterator UnitTestResultsIterator;


class UnitTestsSummary {
public:
  static int count();
  static int failedCount();
  static UnitTestResultsIterator begin();
  static UnitTestResultsIterator end();
  static void for_each_failed(std::function<void(UnitTestResultInfo const&)> function);
};

}

#define ON_TEST_START(_name) \
  void UnitTestFramework::OnTestStart(std::string _name)

#define ON_TEST_COMPLETION(_name) \
  void UnitTestFramework::OnTestCompletion(UnitTestResultInfo const& _name) 

#define QUIET_TEST_START \
  ON_TEST_START(_) {}

#define QUIET_TEST_COMPLETION \
  ON_TEST_COMPLETION(_) {}

#define QUIET_TEST_PROGRESS \
  QUIET_TEST_START \
  QUIET_TEST_COMPLETION

#endif

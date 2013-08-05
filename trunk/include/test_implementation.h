/*

Tiny unit test framework for C++

Vadim Vinnik, 2013
e-mail: vadim.vinnik@gmail.com

*/

/*
This header file is to be included into each source file that contains test
definitions. A test definition has the following form:

UNIT_TEST(test_name)
  ...
  TEST_ASSERTION(condition)
  ...
END_UNIT_TEST

where test_name is a user-defined unique identifier (supposed to describe the
meaning of the test to a human), condition is any C++ expression that can be
used as a condition (i.e. it should have bool, integer, pointer type, a class
that supports and implicit conversion to one of these types, etc.). There can
be multiple TEST_ASSERTION clauses in one test.

In complicated cases, TEST_ASSERTIONs can be used outside a UNIT_TEST, in
helper functions called from it.

No action or code is needed to run the tests: they will start automatically
when the test harness application is started, before it enters its main().
*/

#ifndef _TEST_IMPLEMENTATION_
#define _TEST_IMPLEMENTATION_

#include "test_interface.h"

namespace UnitTestFramework {

class UnitTestBase {
public:
  UnitTestBase(std::string name_);

protected:
  std::string name() const { return m_name; }
  void reportError(std::string condition, int line);
  void reportSuccess();

private:
  std::string m_name;
};

class UnitTestFailedException {
public:
  UnitTestFailedException(std::string condition_, int line_) :
    m_condition(condition_),
    m_line(line_)
  {}

  std::string condition() const { return m_condition; }
  int line() const { return m_line; }
private:
  std::string m_condition;
  int m_line;
};

}

#define UNIT_TEST_CLASS_NAME(_test_name) Unit_Test_Implementation_##_test_name

#define TEST_ASSERTION(_condition) if (!(_condition)) throw UnitTestFramework::UnitTestFailedException(#_condition, __LINE__);

#define UNIT_TEST(_test_name) \
  class UNIT_TEST_CLASS_NAME(_test_name) : public UnitTestFramework::UnitTestBase { \
  public: \
    UNIT_TEST_CLASS_NAME(_test_name) (); \
  private: \
    static UNIT_TEST_CLASS_NAME(_test_name) m_instance; \
  }; \
  UNIT_TEST_CLASS_NAME(_test_name) UNIT_TEST_CLASS_NAME(_test_name)::m_instance; \
  UNIT_TEST_CLASS_NAME(_test_name)::UNIT_TEST_CLASS_NAME(_test_name) () : UnitTestBase(#_test_name) { \
    try {

#define END_UNIT_TEST \
    } \
    catch (UnitTestFramework::UnitTestFailedException failure) { \
      reportError(failure.condition(), failure.line()); \
      return; \
    } \
    catch (...) { \
      reportError("Unexpected exception", -1); \
      return; \
    } \
    reportSuccess(); \
  }

#endif

/*

Tiny unit test framework for C++

Vadim Vinnik, 2013
e-mail: vadim.vinnik@gmail.com

*/

/*
This file implements a unit test manager that receives notifications from
finished tests, collects their results and provides an interface to results
*/

#include "test_implementation.h"

namespace UnitTestFramework {

UnitTestBase::UnitTestBase(std::string name_) :
m_name(name_)
{
  OnTestStart(name_);
}

class UnitTestManager {
public:
  static UnitTestManager *instance() {
    static UnitTestManager *_instance = NULL;

    if (NULL == _instance)
      _instance = new UnitTestManager;

    return _instance;
  }

  void registerResult(UnitTestResultInfo const& result) {
    m_results.push_back(result);
    if (!result.success())
      ++m_failedCount;

    OnTestCompletion(result);
  }

  int count() const { return m_results.size(); }
  int failedCount() const { return m_failedCount; }
  UnitTestResultsIterator begin() const { return m_results.begin(); }
  UnitTestResultsIterator end() const { return m_results.end(); }

private:
  UnitTestManager() : m_failedCount(0) {}

  UnitTestResultsList m_results;
  int m_failedCount;
};


void UnitTestBase::reportError(std::string condition, int line) {
  UnitTestManager::instance() -> registerResult(
    UnitTestResultInfo(
      name(),
      false,
      condition,
      line
    )
  );
}

void UnitTestBase::reportSuccess() {
  UnitTestManager::instance() -> registerResult(UnitTestResultInfo(name()));
}


int UnitTestsSummary::count() {
  return UnitTestManager::instance() -> count();
}

int UnitTestsSummary::failedCount() {
  return UnitTestManager::instance() -> failedCount();
}

UnitTestResultsIterator UnitTestsSummary::begin() {
  return UnitTestManager::instance() -> begin();
}


UnitTestResultsIterator UnitTestsSummary::end() {
  return UnitTestManager::instance() -> end();
}

void UnitTestsSummary::for_each_failed(std::function<void(UnitTestResultInfo const&)> function) {
  std::for_each(
    begin(),
    end(),
    [=](UnitTestResultInfo const& info) {
      if (!info.success())
        function(info);
    }
  );
}

}

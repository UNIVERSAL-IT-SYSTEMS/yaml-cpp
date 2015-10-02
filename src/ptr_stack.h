#pragma once

#include <cstddef>
#include <cstdlib>
#include <memory>
#include <vector>

#include "yaml-cpp/noncopyable.h"

template <typename T>
class ptr_stack : private YAML::noncopyable {
 public:
  ptr_stack() {}

  void clear() {
    m_data.clear();
  }

  std::size_t size() const { return m_data.size(); }
  bool empty() const { return m_data.empty(); }

  void push(std::unique_ptr<T>&& t) {
    m_data.push_back(std::move(t));
  }
  std::unique_ptr<T> pop() {
   std::unique_ptr<T> t(std::move(m_data.back()));
    m_data.pop_back();
    return t;
  }

  T& top() {
    return *(m_data.back().get());
  }
  const T& top() const {
    return *(m_data.back().get());
  }

  T& top(std::ptrdiff_t diff) {
    return *((m_data.end() - 1 + diff)->get());
  }

  const T& top(std::ptrdiff_t diff) const {
    return *((m_data.end() - 1 + diff)->get());
  }

 private:
    std::vector<std::unique_ptr<T>> m_data;
};

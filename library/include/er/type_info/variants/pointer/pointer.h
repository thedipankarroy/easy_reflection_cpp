#pragma once

#include "ipointer.h"
#include "std_shared_ptr.h"
#include "std_unique_ptr.h"

namespace er {

struct Pointer {
  template <typename T>
  Pointer(std::shared_ptr<T>* value, bool is_const) {
    new (_mem) StdSharedPtr<T>(value, is_const);
  }

  template <typename T>
  Pointer(std::unique_ptr<T>* value, bool is_const) {
    new (_mem) StdUniquePtr<T>(value, is_const);
  }

  Expected<None> assign(Var var) {
    return impl()->assign(var);
  }

  void unsafe_assign(void* ptr) {
    impl()->unsafe_assign(ptr);
  }

  Var var() const {
    return impl()->var();
  }

  bool is_null() const {
    return impl()->is_null();
  }

  void init() {
    impl()->init();
  }

  Expected<Var> get_nested() const {
    return impl()->get_nested();
  }

 private:
  // a little hack to reduce dynamic memory allocation
  // this approach is little faster then use shared_ptr but still faster
  //
  // it's just a memory bunch for a pointer and is_const flag
  // all kinds of Pointer wrapper has the same sizeof()
  char _mem[sizeof(StdSharedPtr<int>)];

  inline const IPointer* impl() const {
    return reinterpret_cast<const IPointer*>(&_mem[0]);
  }

  inline IPointer* impl() {
    return reinterpret_cast<IPointer*>(&_mem[0]);
  }
};

}  // namespace er

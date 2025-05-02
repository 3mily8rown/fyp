#ifndef GOOGLE_PROTOBUF_STUBS_MUTEX_H_
#define GOOGLE_PROTOBUF_STUBS_MUTEX_H_

namespace google {
namespace protobuf {

class Mutex {
 public:
  Mutex() {}
  ~Mutex() {}
  void Lock() {}
  void Unlock() {}
  void AssertHeld() {}
};

class MutexLock {
 public:
  explicit MutexLock(Mutex* mu) : mu_(mu) { mu_->Lock(); }
  ~MutexLock() { mu_->Unlock(); }

 private:
  Mutex* mu_;
};

}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_STUBS_MUTEX_H_

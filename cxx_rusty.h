/// Make your C/C++ code look like `Rust`!
/// Disclaimer: The limitation is that no variables can have the same name as these macros. Do not use this in actual projects.
///
/// usage(C):
/// #define CXX_RUSTY_CONFIG_EXTRA_INCLUDE "extra.h"
/// #include "cxx_rusty.h"
///
/// usage(C++):
/// #define CXX_RUSTY_CONFIG_USIZE_IS_SIZE_T 0
/// #define CXX_RUSTY_CONFIG_ENABLE_STL_OPTIONAL
/// #define CXX_RUSTY_CONFIG_ENABLE_STL_SPAN
/// #define CXX_RUSTY_CONFIG_EXTRA_INCLUDE "extra.h"
/// #include "cxx_rusty.h"
///
/// use cxx_rusty;
/// use cxx_rusty::collections;
///

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

/* C */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

#ifdef __cplusplus

/* C++ STL */
#include <string>

#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#include <utility>
#include <tuple>

#include <memory>

#ifdef CXX_RUSTY_CONFIG_ENABLE_STL_OPTIONAL
// since C++17
#include <optional>
#endif

#ifdef CXX_RUSTY_CONFIG_ENABLE_STL_SPAN
// since C++20
#include <span>
#endif

#include <chrono>
#include <thread>

#include <iostream>
#include <functional>

#ifdef CXX_RUSTY_CONFIG_ENABLE_128BIT_INTEGER
#include <__msvc_int128.hpp>
#endif

#endif

#if defined(__cplusplus)
namespace cxx_rusty {
#endif

/* Types */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#ifndef CXX_RUSTY_CONFIG_USIZE_IS_SIZE_T
#define CXX_RUSTY_CONFIG_USIZE_IS_SIZE_T 1
#endif

#if (CXX_RUSTY_CONFIG_USIZE_IS_SIZE_T == 1)

typedef ptrdiff_t isize;
typedef size_t usize;

#ifndef ISIZE_MAX
#define ISIZE_MAX                                       PTRDIFF_MAX
#endif

#ifndef USIZE_MAX
#define USIZE_MAX                                       SIZE_MAX
#endif

#else

typedef intptr_t isize;
typedef uintptr_t usize;

#ifndef ISIZE_MAX
#define ISIZE_MAX                                       INTPTR_MAX
#endif

#ifndef USIZE_MAX
#define USIZE_MAX                                       UINTPTR_MAX
#endif

#endif

// string literal
typedef const char *const str;

#ifdef CXX_RUSTY_CONFIG_ENABLE_COMPAT_HEADER
/* Compatibility header, in C defines alternative operator(and, or, not...) representations which are keywords in C++. */
#include <iso646.h>
#endif

#ifdef CXX_RUSTY_CONFIG_ENABLE_128BIT_INTEGER

#ifdef _MSC_VER

#if defined(__cplusplus)
typedef std::_Signed128 i128;
typedef std::_Unsigned128 u128;
#endif

#elif defined(__clang__) || defined(__GNUC__)

using i128 = __int128_t;
using u128 = __uint128_t;

#else

#error "i128 and u128 types are not supported on this compiler"

#endif

#endif

#define print(fmt, ...)                                 fprintf(stdout, fmt, __VA_ARGS__)
#define println(fmt, ...)                               fprintf(stdout, fmt "\n", __VA_ARGS__)

#define eprint(fmt, ...)                                fprintf(stderr, fmt, __VA_ARGS__)
#define eprintln(fmt, ...)                              fprintf(stderr, fmt "\n", __VA_ARGS__)

#define match                                           switch

#define assert_eq(expected, actual)                     assert((expected) == (actual))

#define panic(msg)                                      do { eprintln("panicked: %s", msg); abort(); } while(false)

#ifdef __cplusplus

#define let                                             const auto
#define let_mut                                         auto
#define fn                                              auto
#define self                                            this
#define pub                                             public
#define prot                                            protected
#define pri                                             private
#define mod                                             namespace
#define use                                             using namespace
#define as(x, type_)                                    static_cast<type_>((x))

/// prelude start
namespace marker {
    struct Copy {};
    struct Send {};
    struct Sized {};
    struct Sync {};
    struct Unpin {};
}

namespace ops {
    struct Drop {};
    
    /// NOTE: std::unction cannot simply correspond to Rust's Fn, FnMut, and FnOnce. Fn is used here for conciseness only
    template<typename F>
    using Fn = std::function<F>;

    template<typename TRet, typename... Args>
    using _Fn = std::function<TRet(Args...)>;
    
    struct FnMut {};
    struct FnOnce {};
}

namespace mem {
    template<typename T>
    fn drop(T *&ptr) {
        if (ptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
    
    template<typename T>
    fn drop_array(T *&ptr) {
        if (ptr) {
            delete[] ptr;
            ptr = nullptr;
        }
    }
}

namespace boxed {
    template<typename T>
    using Box = std::unique_ptr<T>;

    template<typename T, typename... Args>
    Box<T> BoxNew(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}

namespace borrow {
    struct ToOwned {};
}

namespace clone {
    struct Clone {};
}

namespace cmp {
    struct PartialEq {};
    struct PartialOrd {};
    struct Eq {};
    struct Ord {};
}

namespace convert {
    struct AsRef {};
    struct AsMut {};
    struct Into {};
    struct From {};
}

namespace default_ {
    struct Default {};
}

namespace iter {
    struct Iterator {};
    struct Extend {};
    struct IntoIterator {};
    struct DoubleEndedIterator {};
    struct ExactSizeIterator {};
}

namespace option {
#ifdef CXX_RUSTY_CONFIG_ENABLE_STL_OPTIONAL
    template<typename T>
    using Option = std::optional<T>;
    
    struct Some {};
    struct None {};
#else
    enum class Option {
        Some,
        None,
    };
#endif
}

namespace result {
    enum class Result {
        Ok,
        Err,
    };
}

namespace string {
    using String = std::string;
    
    struct ToString {};
}

namespace vec {
    template<typename T>
    using Vec = std::vector<T>;
}

use ops;
use mem;
use boxed;
use string;
use vec;
/// prelude end

namespace slice {
#ifdef CXX_RUSTY_CONFIG_ENABLE_STL_SPAN
    template<class T, std::size_t Extent = std::dynamic_extent>
    using Slice = std::span<T, Extent>;
#endif
}

namespace collections {
    template<typename T>
    using LinkedList = std::list<T>;
    
    template<typename K, typename V>
    using BTreeMap = std::map<K, V>;
    
    template<typename K, typename V>
    using HashMap = std::unordered_map<K, V>;
}

namespace sync {
    template<typename T>
    using Arc = std::shared_ptr<T>;

    template<typename T>
    using Weak = std::weak_ptr<T>;
    
    template<typename T, typename... Args>
    Arc<T> ArcNew(Args &&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

namespace time {
    using _HighResClock = std::chrono::high_resolution_clock;
    using _HighResDuration = std::chrono::duration<float>;
    using _HighResTimePoint = std::chrono::time_point<_HighResClock, _HighResDuration>;
    
    struct Instant {
        static _HighResTimePoint now() {
            return _HighResClock::now();
        }
    };
    
    struct Duration {
        Duration(_HighResDuration d) : duration(d) {
            
        }
        
        static Duration from_millis(u64 millis) {
            return Duration(std::chrono::milliseconds(millis));
        }
        
        f32 as_secs_f32() const {
            return self->duration.count();
        }
        
        _HighResDuration _as_duration() const {
            return self->duration;
        }
        
        operator f32() const {
            return self->as_secs_f32();
        }
        
        operator _HighResDuration() const {
            return self->duration;
        }
        
    private:
        _HighResDuration duration;
    };
}

namespace thread {
    template<typename T>
    struct JoinHandle {
        void join() {
            
        }
    };
    
    template<typename T>
    JoinHandle<T> spawn(Fn<void()> func) {
        return JoinHandle<T> {};
    }
    
    void sleep(const time::Duration &dur) {
        std::this_thread::sleep_for(dur._as_duration());
    }
}

template<typename T, typename U>
using Pair = std::pair<T, U>;

template<typename... Args>
using Tuple = std::tuple<Args...>;

template<typename T, typename U>
Pair<T, U> PairNew(T &&t, U &&u) {
    return std::make_pair(std::forward<T>(t), std::forward<U>(u));
}

template<typename... Args>
Tuple<Args...> TupleNew(Args &&... args) {
    return std::make_tuple(std::forward<Args>(args)...);
}
}

namespace std {
    template<>
    struct hash<cxx_rusty::str> {
        size_t operator()(cxx_rusty::str value) const {
            std::hash<const char *> h;
            return h(value);
        }
    };
}

#else

#define as(x, type_)                                    (type_) (x)

#endif

/* Extra header */
#ifdef CXX_RUSTY_CONFIG_EXTRA_INCLUDE
#include CXX_RUSTY_CONFIG_EXTRA_INCLUDE
#endif
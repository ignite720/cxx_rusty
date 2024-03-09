# cxx_rusty

## Make your C/C++ code look like `Rust`!

#### Disclaimer:
The limitation is that the variable names in the project cannot have the same name as these macros.  
It is recommended not to use them in real projects.

### Example: C
```c
#include "cxx_rusty.h"

int main() {
    i32 a = 10;
    f64 b = 20.0;
    i64 c = (as(b, i64) * 30 + a);
}
```

### Example: C++
```c++
#define CXX_RUSTY_CONFIG_EXTRA_INCLUDE "extra.h"
#include "cxx_rusty.h"

use cxx_rusty;
use cxx_rusty::collections;
use cxx_rusty::time;

struct Foo {
    i8 a;
    i16 b;
    i32 c;
    i64 d;

    u8 e;
    u16 f;
    u32 g;
    u64 h;

    f32 i;
    f64 j;

    String k;
};

struct Bar {
    fn a() -> i32 {
        return self->a_;
    }

    fn test(i32 a) const -> f32 {
        return 0.0f;
    }

pub:
    i32 a_;

prot:
    f32 b_;

pri:
    u64 c_;
};

fn test() -> i32 {
    return 0;
}

mod foo{
    mod bar {
        fn test2() -> u32 {
            return 1;
        }
    }
}

fn main() -> i32 {
    //panic("simple test");

    assert_eq(3, 3);

    println("%u", foo::bar::test2());

    {
        let s = String("hello");
        let foo = Foo{
            -1, -2, -3, -4,
            5, 6, 7, 8,
            9.0f, 10.0,
            s,
        };
    }

    {
        let *ptr = new f64;
        drop(ptr);
    }

    {
        let_mut v = Vec<f32>{ 1.0f, 2.0f, 3.0f };
        for (usize i = 0; i < 10; ++i) {
            let value = as(i + 100, f32);
            v.push_back(value);
        }
    }

    {
        let_mut list1 = LinkedList<f64>{};
        for (usize i = 0; i < 10; ++i) {
            let value = as(i + 100, f64);
            list1.push_back(value);
        }
    }

    {
        let ptr = "hello map";

        {
            let_mut m = BTreeMap<str, u64>();
            for (usize i = 0; i < 10000; ++i) {
                m.insert(PairNew(ptr, as(i, u64)));
            }
        }

        {
            let[a, b, c, d] = TupleNew(1000, 2000.0f, 3000.0, String("4000"));
            println("a=%d, b=%f, c=%f, d=%s", a, b, c, d.c_str());
        }

        {
            let_mut m = HashMap<str, u64>();
            for (usize i = 0; i < 10000; ++i) {
                m[ptr] = as(i, u64);
            }
        }
    }

    {
        let a = 5;
        //a = 10;       //  error C3892: 'a': you cannot assign to a variable that is const

        match(a) {
            case 1: {
                println("a is 1 => {}");
            } break;
            case 5: {
                println("a is 5 => {}");
            } break;
        }

        let_mut b = 5.0;
        b = 20.0;

        let c = as(b, i32), c2 = as(b, i32);
        let d = (as(b, i32) * 3 + a);
    }

    {
        let b = Box<f64>(new f64(999.0));
        let b2 = BoxNew<f64>(999.0);

        let a = sync::ArcNew<Foo>();
    }

    {
#ifdef CXX_RUSTY_CONFIG_ENABLE_STL_SPAN
        i32 arr[] = { 1, 2, 3, 4, 5 };
        slice::Slice slice2{ arr, 4 };
#endif
    }

    {
        usize i = 100;
        Fn func = [](i32 i, f64 j) {
            println("%d %f", i, j);
        };
        func(123, 456.0);
    }

    {
        let now = Instant::now();
        thread::sleep(Duration::from_millis(200));
        let end = Instant::now();
        let diff = Duration(end - now);

        println("%fs", diff.as_secs_f32());
        thread::sleep(Duration::from_millis(1500));
    }
    return 0;
}
```
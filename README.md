# Restaurant

In this exercise the menu of a fictional restaurant shall be populated with
dishes. From this menu orders can be generated based on the inputs from a
potential customer.

The solution shall demonstrate the use of:

- Construction, copying and moving of objects.
- Smart pointers.
- Templates.

# Exercise

The sources in `src/menu.hpp` and `src/menu.cpp` shall be updated to make the
unit tests defined in `tests/unit.cpp` pass.

The unit tests shall not be modified and can be run like this:

```
$ cmake -B build
$ cmake --build build
$ ctest --test-dir build
```

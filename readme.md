# BetterTest - A Modern Testing Library

BetterTest is a modern, macro free, extensible testing library.

For building, exporting and installing please refer to the [build instructions](build_instructions.md).

## Macro Free

BetterTest has no macros. BetterTest needs no macros.

## No Print? No Problem!

Some testing libraries refuse to compile when comparing two objects that can't be converted to a string. BetterTest
doesn't mind. It will happily compile and run, just with a slightly less informative error message when there is a
failure.

## Early Termination

Sometimes a failed check should result in immediate termination of a test. For example, inspecting the contents of a
list should always be preceded by a check of that list's size. Accessing non-existing elements would result in
misleading out of bounds errors. Some testing libraries handle this by providing a terminating and non-terminating
version of the same function, e.g. `requireEQ` and `expectEQ`. This is not very elegant. BetterTest solves
this problem by returning an object that has a `fatal` method. If the check failed, calling this method will end
the test with an error message:

```cpp
std::vector<int32_t> list = {1, 2, 3};
compareEQ(list.size(), 3).fatal("List has wrong size.");
compareEQ(list[0], 1);
compareEQ(list[1], 2);
compareEQ(list[2], 3);
```

## Output Formats

BetterTest ships with exporters for 2 broadly used formats: JSON and XML. There is also experimental support for writing
to a Sqlite database. Additionally, implementing your own exporter is trivial.

## Parallel Runs

BetterTest has native support for running tests in parallel using `std::async`. No need to write silly scripts
that simulate this by running the same executable multiple times with different parameters.

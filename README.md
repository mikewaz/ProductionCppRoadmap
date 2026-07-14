# ProductionCppRoadmap

- `explicit` prevents implicit conversion of an argument to an object;
- direct initialisation works with `explicit` as well;
- copy initialisation using `T value = argument` does not compile with `explicit`;
- `static_assert` allows type properties to be checked at compile-time.
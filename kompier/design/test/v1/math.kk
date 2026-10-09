export module math;

// v1 goal: keep syntax minimal but parser-complete.

export add(a: int, b: int) -> int
{
    return a + b;
}

export mul<T>(x: T, y: T)
{
    return x * y;
}

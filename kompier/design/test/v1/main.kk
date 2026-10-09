// v1 test program: should be fully parseable by the v0 grammar skeleton.

import math as m;

simple_literals() -> void
{
    const dec = 1_000_000;
    const hex = 0xDEAD'BEEF;
    const bin = 0b1010_0101;
    const oct = 0o755;

    const f1 = 3.14;
    const f2 = 1.;
    const f3 = .5;
    const f4 = 3.14e+2f;
    const f5 = 1e-7;

    const c1 = 'A';
    const c2 = '\n';
    const c3 = '\x41';

    const s1 = "Hello\\nWorld";
    const s2 = "quote: \\\" and slash: \\\\";
}

simple_ctors() -> void
{
    uninit_i = int{};
    pi_f = float{3.14};

    arr0 = [int; 10]{};
    arr1 = [int; 10]{ 0 };

    tup0 = (int, double){};
    tup1 = (int, double){ 1, 2.0 };
}

main() -> int
{
    x = 2;
    y = 4;
    z = m::add(x, y);
    return z;
}

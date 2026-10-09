# kompier - 一个我内心的现代编译器

## build

```bash
cmake -S . -B build-ninja -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-ninja
```

## dev commands

```bash
./build-ninja/src/kk lex design/test/v1/main.kk
ctest --test-dir build-ninja --output-on-failure
```

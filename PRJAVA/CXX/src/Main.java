



auto main() -> int
{
    int n;
    std::cin >> n;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }


    return 0;
}
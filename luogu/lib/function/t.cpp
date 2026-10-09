


struct clock
{
    using time_t = decltype(std::chrono::high_resolution_clock::now());

    fun static start()
    { start_ = std::chrono::high_resolution_clock::now(); }
    fun static end()
    { end_ = std::chrono::high_resolution_clock::now(); }
    fun static time()
    { return std::chrono::high_resolution_clock::now(); }

    static time_t start_;
    static time_t end_;
};
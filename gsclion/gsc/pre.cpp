
import std;

namespace 
{

	auto _ = std::invoke([] {
		auto ifs = std::ifstream("stdin.in");
		std::cin.rdbuf(ifs.rdbuf());
		return ifs;
	});

}
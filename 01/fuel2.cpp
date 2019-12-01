#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <chrono>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

size_t fuel_requirement(int64_t w) {
    int64_t result = -w;
    while (w > 0) {
        result += w;
        w = w / 3 - 2;
    }
    return result;
}

size_t fuel_sum(const auto& weights) {
    return accumulate(begin(weights), end(weights), 0, [](auto acc, auto w) {
        return acc + fuel_requirement(w);
    });
}

//------------------------------------------------------------------------------
#define TEST_EQ(a, b) { std::cout << #a << " == " << #b << " == " << ((a) == (b)) << std::endl; assert((a) == (b)); }

void test() {
    TEST_EQ(fuel_requirement(12), 2);
    TEST_EQ(fuel_requirement(1969), 966);
    TEST_EQ(fuel_requirement(100756), 50346);
}

void run() {
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();

    std::vector<size_t> weights;
    copy(
        std::istream_iterator<size_t>(std::cin),
        std::istream_iterator<size_t>(),
        back_inserter(weights));

    high_resolution_clock::time_point t_io = high_resolution_clock::now();

    auto answer = fuel_sum(weights);

    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    auto io_duration = duration_cast<microseconds>(t_io - t_start).count();
    auto all_duration = duration_cast<microseconds>(t_end - t_start).count();

    std::cout << answer << " in " << all_duration << "us (io: "
              << io_duration << "us)" << std::endl;
}

int main() {
    test();
    run();
}


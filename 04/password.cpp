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

size_t count_passwords(size_t so_far, size_t bottom, size_t up, bool pair_seen, size_t deleter) {
    if (so_far >= bottom && so_far <= up && pair_seen) return 1;
    if (so_far > up) return 0;
    if (deleter > 0 && so_far > up / deleter) return 0;
    size_t answer = 0;
    size_t last = so_far % 10;
    size_t i = last == 0 ? 1 : last;
    for (; i < 10; ++i) {
        answer += count_passwords(so_far * 10 + i, bottom, up, pair_seen || i == last, deleter / 10);
    }
    return answer;
}

//------------------------------------------------------------------------------
#define TEST_EQ(a, b) { std::cout << #a << " == " << (a) << " == " << #b << " == " << ((a) == (b)) << std::endl; assert((a) == (b)); }

void test() {
    TEST_EQ(count_passwords(0, 111111, 111120, false, 1000000), 9)
}

void run() {
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();

    size_t bottom, up;
    char c;
    std::cin >> bottom >> c >> up;

    high_resolution_clock::time_point t_io = high_resolution_clock::now();

    auto answer = count_passwords(0, bottom, up, false, 1000000);

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


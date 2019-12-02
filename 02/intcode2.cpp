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

auto parse_input(auto input) {
    std::vector<size_t> program;
    size_t intcode;
    char c;
    std::stringstream ss(input);
    while (ss >> intcode >> c) program.push_back(intcode);
    return program;
}

void execute(auto& program) {
    for (size_t i = 0; program[i] == 1 || program[i] == 2; i += 4) {
        if (program[i] == 1) {
            program[program[i+3]] = program[program[i+1]] + program[program[i+2]];
        }
        else {
            program[program[i+3]] = program[program[i+1]] * program[program[i+2]];
        }
    }
}

void find_output(auto& program, size_t output) {
    auto init_program = program;
    for (size_t i = 0; i < 100; ++i) {
        for (size_t j = 0; j < 100; ++j) {
            program = init_program;
            program[1] = i;
            program[2] = j;
            execute(program);
            if (program[0] == output) return;
        }
    }
}

//------------------------------------------------------------------------------
#define TEST_EQ(a, b) { std::cout << #a << " == " << #b << " == " << ((a) == (b)) << std::endl; assert((a) == (b)); }

void test() {
    auto program1 = parse_input("1,1,1,4,99,5,6,0,99");
    TEST_EQ(program1[0], 1);
    TEST_EQ(program1[2], 1);
    TEST_EQ(program1[3], 4);
    TEST_EQ(program1[4], 99);

    execute(program1);
    TEST_EQ(program1[0], 30);
    TEST_EQ(program1[4], 2);
}

void run() {
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();

    std::string input; std::cin >> input;
    input += ',';
    auto program = parse_input(input);

    high_resolution_clock::time_point t_io = high_resolution_clock::now();

    find_output(program, 19690720);
    auto answer = 100 * program[1] + program[2];

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


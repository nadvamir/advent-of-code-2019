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

struct Point {
    int x, y;

    int distance() {
        return std::abs(x) + std::abs(y);
    }
};

struct Line {
    Point a, b;

    void rotate() {
        if (a.x > b.x) {
            std::swap(a, b);
        }
        if (a.y > b.y) {
            std::swap(a, b);
        }
    }

    Point cross(const Line& o) const {
        int x = (a.x == b.x) ? a.x : o.a.x;
        int y = (a.y == b.y) ? a.y : o.a.y;

        if (x < a.x || x < o.a.x) return Point{0, 0};
        if (x > b.x || x > o.b.x) return Point{0, 0};
        if (y < a.y || y < o.a.y) return Point{0, 0};
        if (y > b.y || y > o.b.y) return Point{0, 0};
        return {x, y};
    }
};

std::vector<Line> parse_wire(std::string input) {
    std::vector<Line> res;

    std::stringstream ss(input + ",");
    char direction, comma;
    int magnitude;

    Point a{0, 0}, b;
    while (ss >> direction >> magnitude >> comma) {
        switch (direction) {
        case 'R': b = Point{a.x + magnitude, a.y}; break;
        case 'D': b = Point{a.x, a.y - magnitude}; break;
        case 'L': b = Point{a.x - magnitude, a.y}; break;
        case 'U': b = Point{a.x, a.y + magnitude}; break;
        }
        Line l{a, b};
        l.rotate();
        res.push_back(l);
        a = b;
    }
    return res;
}

size_t crossing_point(const std::string& w1, const std::string& w2) {
    auto w1_lines = parse_wire(w1);
    auto w2_lines = parse_wire(w2);

    Point res = w1_lines.front().cross(w2_lines.back());
    for (const auto& l1 : w1_lines) {
        for (const auto& l2 : w2_lines) {
            auto x = l1.cross(l2);
            if (res.distance() == 0 || x.distance() != 0 && x.distance() < res.distance()) res = x;
        }
    }
    return res.distance();
}

//------------------------------------------------------------------------------
#define TEST_EQ(a, b) { std::cout << #a << " == " << (a) << " == " << #b << " == " << ((a) == (b)) << std::endl; assert((a) == (b)); }

void test() {
    Point p = Line{{3, 8}, {9, 8}}.cross(Line{{5, 4}, {5, 10}});
    TEST_EQ(p.x, 5);
    TEST_EQ(p.y, 8);
    TEST_EQ(p.distance(), 13);

    TEST_EQ(crossing_point("R8,U5,L5,D3", "U7,R6,D4,L4"), 6);
    TEST_EQ(crossing_point("R75,D30,R83,U83,L12,D49,R71,U7,L72", "U62,R66,U55,R34,D71,R55,D58,R83"), 159);
    TEST_EQ(crossing_point("R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51", "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7"), 135);
}

void run() {
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();

    std::string w1, w2;
    std::getline(std::cin, w1);
    std::getline(std::cin, w2);

    high_resolution_clock::time_point t_io = high_resolution_clock::now();

    auto answer = crossing_point(w1, w2);

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


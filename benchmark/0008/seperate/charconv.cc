﻿#include <fast_io.h>
#include <fast_io_device.h>
#include <fast_io_driver/timer.h>
#include <charconv>
#include <random>
#include <vector>
#include <cfloat>
using namespace fast_io::io;

constexpr int buf_size = 25;

inline void charconv_fast_io(std::vector<double> const &vec)
{
    fast_io::timer t(u8"charconv2");
    fast_io::obuf_file file{u8"charconv2.txt"};
    for (auto const e : vec)
    {
        char buf[buf_size]{0};
        std::to_chars(buf, buf + buf_size, e, std::chars_format::scientific);
        println(file, fast_io::mnp::os_c_str(buf));
    }
}

int main()
{
    constexpr std::size_t N = 10'000'000;

    std::mt19937_64 eng{};
    std::uniform_real_distribution<double> dis(DBL_MIN, DBL_MAX);
    std::vector<double> vec;
    vec.reserve(N);
    for (std::size_t i{}; i != N; ++i)
    {
        vec.emplace_back(dis(eng));
    }
    charconv_fast_io(vec);
}

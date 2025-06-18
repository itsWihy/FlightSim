#pragma once

#include <array>
#include <cmath>
#include <cstdint>

inline double fractalNoise(const double x, const double y, const int octaves = 4, const double persistence = 0.5) {
    static constexpr std::array<uint8_t, 256> perm = {
        151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
        190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,149,56,87,174,
        20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,
        220,105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,18,169,200,
        196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,5,202,38,147,118,126,
        255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,
        221,153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
        228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,107,49,192,214,31,181,
        199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,
        128,195,78,66,215,61,156,180
    };

    auto fade = [](const double t) noexcept {
        return t * t * t * (t * (t * 6 - 15) + 10);
    };

    auto grad = [](const uint8_t hash, const double x, const double y) noexcept {
        const uint8_t h = hash & 3;
        const double u = h & 1 ? -x : x;
        const double v = h & 2 ? -y : y;
        return u + v;
    };

    auto noise2D = [&](double x, double y) noexcept {
        const int X = static_cast<int>(std::floor(x)) & 255;
        const int Y = static_cast<int>(std::floor(y)) & 255;
        x -= std::floor(x);
        y -= std::floor(y);

        const double u = fade(x);
        const double v = fade(y);

        const uint8_t A = perm[X] + Y & 255;
        const uint8_t B = perm[X+1 & 255] + Y & 255;

        const double p0 = grad(perm[A], x, y);
        const double p1 = grad(perm[B], x-1, y);
        const double p2 = grad(perm[A+1 & 255], x, y-1);
        const double p3 = grad(perm[B+1 & 255], x-1, y-1);

        return p0 + u*(p1-p0) + v*(p2 + u*(p3-p2) - (p0 + u*(p1-p0)));
    };

    double total = 0.0;
    double maxAmplitude = 0.0;
    double amplitude = 1.0;
    double frequency = 1.0;

    for (int i = 0; i < octaves; ++i) {
        total += noise2D(x * frequency, y * frequency) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= persistence;
        frequency *= 2.0;
    }

    const double value = total / maxAmplitude * 0.5 + 0.5;
    return value < 0.0 ? 0.0 : value > 1.0 ? 1.0 : value;
}
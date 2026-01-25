//==============================================================================
// File        : RandomAPI.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-12
// Last Update : 2025-12-12
//------------------------------------------------------------------------------
// Overview :
// rand_api is a utility class that provides unified random number generation 
// processing across the entire game.
// It internally utilizes the Mersenne Twister engine,
// generating high-quality random numbers at high speed after initialization.
// It comprehensively provides all random number patterns frequently used in game logic,
// including floating-point numbers, integers, random numbers between 0 and 1,
// probability checks, and vector-range random numbers.
// Using the same engine globally ensures consistent behavior and reproducibility.
//==============================================================================
#ifndef RANDOM_API_H
#define RANDOM_API_H

#include <Windows.h>
#include <random>
#include <optional>
#include <algorithm>

#include "MathTransform.h"

namespace ix_util {

	class rand_api {
	private:
		static inline std::mt19937 m_Engine;

	public:
        // one-time initialization
		static void initialize() {
			std::random_device rd;
            m_Engine.seed(rd());
		}

        // get engine
        static std::mt19937& get_engine() {
            return m_Engine;
        }

        // real number
        template<typename T>
        IX_NODISCARD static T real(T a, T b) {
            std::uniform_real_distribution<T> dist(a, b);
            return dist(m_Engine);
        }

        // integer
        IX_NODISCARD static int integer(int a, int b) {
            std::uniform_int_distribution<int> dist(a, b);
            return dist(m_Engine);
        }

        // real number 0~1
        IX_NODISCARD static float real01() {
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);
            return dist(m_Engine);
        }

        // probability check
        IX_NODISCARD static bool chance(float p) {
            std::bernoulli_distribution dist(p);
            return dist(m_Engine);
        }

        // vector <float>
        IX_NODISCARD static math::vector2f vector2(const math::vector2f& a, const math::vector2f& b) {
            return { real(a.x, b.x), real(a.y, b.y) };
        }
        IX_NODISCARD static math::vector3f vector3(const math::vector3f& a, const math::vector3f& b) {
            return { real(a.x, b.x), real(a.y, b.y), real(a.z, b.z) };
        }
        IX_NODISCARD static math::vector4f vector4(const math::vector4f& a, const math::vector4f& b) {
            return { real(a.x, b.x), real(a.y, b.y), real(a.z, b.z), real(a.w, b.w) };
        }

        // integer (multiple of N)
        template<int Multiple>
        IX_NODISCARD static int integer_multiple(int a, int b, int fallback = 0) {
            static_assert(2 <= Multiple && Multiple <= 9, "Multiple must be 2..9");

            if (a > b) std::swap(a, b);

            int first = ((a + Multiple - 1) / Multiple) * Multiple;
            int last = (b / Multiple) * Multiple;

            if (first > last)
                return fallback;

            int count = (last - first) / Multiple + 1;
            std::uniform_int_distribution<int> dist(0, count - 1);
            return first + dist(m_Engine) * Multiple;
        }
	};
}

#endif // RANDOM_API_H
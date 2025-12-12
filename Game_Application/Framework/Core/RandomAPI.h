//==============================================================================
// File        : RandomAPI.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-12
// Last Update : 2025-12-12
//------------------------------------------------------------------------------
// Overview :
//==============================================================================
#ifndef RANDOM_API_H
#define RANDOM_API_H

#include <Windows.h>
#include <random>
#include <cmath>

namespace ix_util {

	class rand_api {
	private:
		static inline std::mt19937 m_RandomAPI;

	public:
        // One-time initialization
		static void initialize() {
			std::random_device rd;
			m_RandomAPI.seed(rd());
		}

        // real number
        template<typename T>
        static T real(T a, T b) {
            std::uniform_real_distribution<T> dist(a, b);
            return dist(m_RandomAPI);
        }

        // integer
        static int integer(int a, int b) {
            std::uniform_int_distribution<int> dist(a, b);
            return dist(m_RandomAPI);
        }

        // real number 0~1
        static float real01() {
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);
            return dist(m_RandomAPI);
        }

        // Probability Check
        static bool chance(float p) {
            std::bernoulli_distribution dist(p);
            return dist(m_RandomAPI);
        }

	};
}

#endif // RANDOM_API_H
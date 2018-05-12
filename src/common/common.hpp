#pragma once
#include <vector>
#include <cstdint>


struct float32_t
{
    uint8_t arr[4];
    float32_t() {
        arr[0] = -1;
        arr[1] = -1;
        arr[2] = -1;
        arr[3] = -1;
    }
    float32_t(uint8_t input[4])
    {
        arr[0] = input[0];
        arr[1] = input[1];
        arr[2] = input[2];
        arr[3] = input[3];
    }
    void operator=(const float32_t& input)
    {
        arr[0] = input.arr[0];
        arr[1] = input.arr[1];
        arr[2] = input.arr[2];
        arr[3] = input.arr[3];
    }
};


// template<c>
// float32_t ave(std::vector<c> vect)
// {
	// float32_t output;
	// for (auto n : vect)
	// {
		// output.push_back(n);
	// }
	// output /= output.size();
	// return output;
// }
//
// float32_t integrate(float32_t accel)
// {
	// float32_t velocity = accel;
	// return velocity;
// }

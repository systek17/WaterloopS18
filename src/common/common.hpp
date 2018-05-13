#pragma once
#include <vector>

typedef float float32_t;
typedef uint8_t Byte;

float32_t ave(std::vector<float32_t> vect)
{
	float32_t output = 0;
    for (auto n : vect)
    {
        output += n;
    }
    output /= vect.size();
    return output;
}

float32_t integrate(float32_t accel)
{
    float32_t velocity = accel;

    /* integral code for the Arduino from the math library */

    return velocity;
}

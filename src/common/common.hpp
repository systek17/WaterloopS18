#pragma once
#include <vector>

struct float32_t
{
    uint8_t arr[4];
    float32_t() {
        arr[0] = -1;
        arr[1] = -1;
        arr[2] = -1;
        arr[3] = -1;
    }
    float32_t(int i)
    {
        arr[0] = i;
        arr[1] = i;
        arr[2] = i;
        arr[3] = i;
    }
    float32_t(uint8_t input[4])
    {
        arr[0] = input[0];
        arr[1] = input[1];
        arr[2] = input[2];
        arr[3] = input[3];
    }
    float32_t& operator=(const float32_t& input)
    {
        arr[0] = input.arr[0];
        arr[1] = input.arr[1];
        arr[2] = input.arr[2];
        arr[3] = input.arr[3];
        return *this;
    }

    void operator+=(const float32_t& input)
    {
        arr[0] += input.arr[0];
        arr[1] += input.arr[1];
        arr[2] += input.arr[2];
        arr[3] += input.arr[3];
    }

    void operator/=(const unsigned& num)
    {
        arr[0] /= num;
        arr[1] /= num;
        arr[2] /= num;
        arr[3] /= num;
    }
    bool operator==(const float32_t& input)
    {
        return arr[0] == input.arr[0]
            && arr[1] == input.arr[1]
            && arr[2] == input.arr[2]
            && arr[3] == input.arr[3];
    }
};


float32_t ave(std::vector<float32_t> vect)
{
    float32_t output = float32_t(0);
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
    return velocity;
}

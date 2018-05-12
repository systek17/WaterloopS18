#pragma once
#include <vector>

template<c>
float32_t ave(vector<c> vect)
{
	float32_t output;
	for (auto n : vect)
	{
		output.push_back(n);
	}
	output /= output.size();
	return output;
}

float32_t integrate(float32_t accel)
{
	float32_t velocity = accel;
	return velocity;
}

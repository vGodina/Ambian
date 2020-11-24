#pragma once
#include <vector>
#include "Types.h"

/* It's expected that input audio is 4 channel float32 B-format in order W-X-Y-Z.
 * Azimuth and Elevation angles are in radians.
 * The output is one channel with same sample rate as the input.
 * Directivity is [0..1]
 * 0 is figure-of-eight
 * 0.5 is cardioid
 * 1 is omni
 */

class B2Mono
{
public:
	B2Mono();
	void SetAzimuth(double InAzimuth);
	void SetElevation(double InElevation);
	void SetDirectivity(double InDirectivity);
	float Process(const BSample& Sample);

private:
	Angle FocusTo;
	double Directivity;
};

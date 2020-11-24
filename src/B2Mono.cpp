#include "B2Mono.h"

B2Mono::B2Mono() : FocusTo{}, Directivity{}
{
}

void B2Mono::SetAzimuth(double InAzimuth)
{
	FocusTo.Azimuth = InAzimuth;
}

void B2Mono::SetElevation(double InElevation)
{
	FocusTo.Elevation = InElevation;
}

void B2Mono::SetDirectivity(double InDirectivity)
{
	Directivity = InDirectivity;
}

float B2Mono::Process(const BSample& Input)
{
	return static_cast<float>(Directivity * sqrt(2) * Input.W +
		(1 - Directivity) * (cos(FocusTo.Azimuth) * cos(FocusTo.Elevation) * Input.X +
		sin(FocusTo.Azimuth) * cos(FocusTo.Elevation) * Input.Y + sin(FocusTo.Elevation) * Input.Z)
		);
}

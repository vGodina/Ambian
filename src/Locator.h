#pragma once
#include <vector>
#include "Types.h"

class Locator
{
public:
	void CaptureAudio(const BWaveform& InSignal);
	void CalculateSoundField();
	Angle GetMainDirection();

private:
	uint32_t FFTSize;
	BWaveform InputSignal;
	std::vector<IntensityInPolar> PolarSoundField;
};

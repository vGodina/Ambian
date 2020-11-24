#pragma once
#include "Types.h"

class BSignalGenerator
{
public:
	void ImportSignal(const Waveform& InSignal);
	void SetSourcePosition(IntensityInPolar SoundSource);
	BWaveform GetBSignal();
private:
	IntensityInPolar SourcePosition;
	std::shared_ptr<Waveform> Signal;
	BWaveform BSignal;
};

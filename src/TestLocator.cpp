#include "TestLocator.h"

int Test::TestLocator()
{
	
	constexpr uint32_t SampleRate = 48000;
	constexpr uint32_t DurationInSamples = 512;

	Waveform Signal;
	constexpr double SignalDuration = static_cast<double>(DurationInSamples) / static_cast<double>(SampleRate);
	Signal.resize(DurationInSamples);
	constexpr double SignalFreq = 1500;
	constexpr double Intensity = 0.5;

	constexpr double PI = 3.141592653589793116;
	for (int i = 0; i < Signal.size(); ++i)
	{
		Signal[i] = static_cast<float>(Intensity * sin(2 * PI * SignalFreq * i / SampleRate));
	}

	
	BSignalGenerator BSignal;
	BSignal.ImportSignal(Signal);
	Angle SrcAngle{PI/4, PI/4};
	IntensityInPolar SoundSource{ SrcAngle,Intensity };
	BSignal.SetSourcePosition(SoundSource);

	Locator TestLocator;
	TestLocator.CaptureAudio(BSignal.GetBSignal());
	TestLocator.CalculateSoundField();
	auto ResultAngle = TestLocator.GetMainDirection();

	int FailedTests = 0;

	return FailedTests;
}

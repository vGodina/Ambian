#include "BSignalGenerator.h"

void BSignalGenerator::ImportSignal(const Waveform& InSignal)
{
	Signal = std::make_shared<Waveform>(InSignal);
}

void BSignalGenerator::SetSourcePosition(IntensityInPolar InSoundSource)
{
	SourcePosition = InSoundSource;
}

BWaveform BSignalGenerator::GetBSignal()
{
	BSignal.resize(Signal->size());

	for (int i = 0; i < Signal->size(); ++i)
	{
		auto SignalSample = (*Signal)[i];
		BSignal.W[i] = static_cast<float>(SignalSample / sqrt(2));
		BSignal.X[i] = static_cast<float>(SignalSample * cos(SourcePosition.Direction.Azimuth) * cos(SourcePosition.Direction.Elevation));
		BSignal.Y[i] = static_cast<float>(SignalSample * sin(SourcePosition.Direction.Azimuth) * cos(SourcePosition.Direction.Elevation));
		BSignal.Z[i] = static_cast<float>(SignalSample * sin(SourcePosition.Direction.Elevation));
	}
	return BSignal;
}

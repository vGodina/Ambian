#include <algorithm>
#include "locator.h"
#include "AudioFFT.h"

namespace LocatorImpl
{

void ToSpectrum(Spectrum& DestSpectrum, const Waveform& SourceWaveform, int FFTSize)
{
	audiofft::AudioFFT Fft;
	Fft.init(FFTSize);
	Fft.fft(SourceWaveform.data(), DestSpectrum.Re.data(), DestSpectrum.Im.data());
}

void CrossPowerSpectrum(const Spectrum& First, const Spectrum& Second, std::vector<float>& Output)
{
	/*the function implements Ix = Real(conj(Ws) * Xs).
	  Optimization is in partial calculation of conjugate multiply with 2nd complex number. */

	for (uint32_t i = 0; i < Output.size(); ++i)
	{
		Output[i] = First.Re[i] * Second.Re[i] + First.Im[i] * Second.Im[i];
	}
}

void ToBSpectrum(BSpectrum& DestBSpectrum, const BWaveform& SourceBWaveform, int FFTSize)
{
	ToSpectrum(DestBSpectrum.Ws, SourceBWaveform.W, FFTSize);
	ToSpectrum(DestBSpectrum.Xs, SourceBWaveform.X, FFTSize);
	ToSpectrum(DestBSpectrum.Ys, SourceBWaveform.Y, FFTSize);
	ToSpectrum(DestBSpectrum.Zs, SourceBWaveform.Z, FFTSize);
}

IntensityInCart Intensity(BSpectrum& InBSpectrum)
{
	IntensityInCart IntensityField(static_cast<uint32_t>(InBSpectrum.size()));

	CrossPowerSpectrum(InBSpectrum.Ws, InBSpectrum.Xs, IntensityField.X);
	CrossPowerSpectrum(InBSpectrum.Ws, InBSpectrum.Ys, IntensityField.Y);
	CrossPowerSpectrum(InBSpectrum.Ws, InBSpectrum.Zs, IntensityField.Z);

	return IntensityField;
}

void CartToPolar(std::vector<IntensityInPolar>& DstSoundField, IntensityInCart& SrcIntens)
{
	DstSoundField.resize(SrcIntens.size());

	for (uint32_t i = 0; i < DstSoundField.size(); ++i)
	{
		DstSoundField[i].Intensity = sqrt(pow(SrcIntens.X[i], 2) + pow(SrcIntens.Y[i], 2) + pow(SrcIntens.Z[i], 2));
		if (SrcIntens.X[i] != 0.0f)
		{
			DstSoundField[i].Direction.Azimuth = atan(SrcIntens.Y[i] / SrcIntens.X[i]);
			DstSoundField[i].Direction.Elevation = atan(SrcIntens.Z[i] / sqrt(pow(SrcIntens.X[i], 2) + pow(SrcIntens.Y[i], 2)));
		}
	}
}

} // namespace LocatorImpl

void Locator::CaptureAudio(const BWaveform& InSignal)
{
	InputSignal = InSignal;
	FFTSize = static_cast<uint32_t>(InputSignal.size());
}

void Locator::CalculateSoundField()
{
	BSpectrum BSpectra(FFTSize/2 + 1);
	LocatorImpl::ToBSpectrum(BSpectra, InputSignal, FFTSize);
	auto SoundFieldInCart = LocatorImpl::Intensity(BSpectra);
	LocatorImpl::CartToPolar(PolarSoundField, SoundFieldInCart);
}

Angle Locator::GetMainDirection()
{
	return std::max_element(PolarSoundField.begin(), PolarSoundField.end(),
		[](const IntensityInPolar& s1, const IntensityInPolar& s2) { return s1.Intensity < s2.Intensity; }
	)->Direction;
}

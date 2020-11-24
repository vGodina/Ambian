#pragma once
#include <complex>
#include <vector>

using Waveform = std::vector<float>;

struct Angle
{
	double Azimuth;
	double Elevation;
};

struct IntensityInPolar
{
	Angle Direction;
	double Intensity;
};

struct IntensityInCart
{
	IntensityInCart(int Size)
	{
		X.resize(Size);
		Y.resize(Size);
		Z.resize(Size);
	}

	std::vector<float> X;
	std::vector<float> Y;
	std::vector<float> Z;
	const size_t size() { return X.size(); }
};

struct BWaveform
{
	Waveform W;
	Waveform X;
	Waveform Y;
	Waveform Z;

	const size_t size() { return W.size(); }
	
	void resize(size_t Size)
	{
		W.resize(Size);
		X.resize(Size);
		Y.resize(Size);
		Z.resize(Size);
	}
};

struct BSample
{
	Waveform::value_type W;
	Waveform::value_type X;
	Waveform::value_type Y;
	Waveform::value_type Z;
};

struct Spectrum
{
	std::vector<float> Re;
	std::vector<float> Im;

	void resize(int FFTSize) 
	{
		Re.resize(FFTSize);
		Im.resize(FFTSize);
	}

	const size_t size() { return Re.size(); }

};

struct BSpectrum
{
	BSpectrum(int SpectrumSize)
	{
		Ws.resize(SpectrumSize);
		Xs.resize(SpectrumSize);
		Ys.resize(SpectrumSize);
		Zs.resize(SpectrumSize);
	}

	Spectrum Ws;
	Spectrum Xs;
	Spectrum Ys;
	Spectrum Zs;

	const size_t size()  { return Ws.size(); }
};

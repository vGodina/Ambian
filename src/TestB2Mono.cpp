#include <iostream>
#include "TestB2Mono.h"

void Test(double Expected, BSample Input, double Azimuth, double Elevation, double Directivity, int& Passed, int& Failed)
{
	B2Mono DUT;
	DUT.SetAzimuth(Azimuth);
	DUT.SetElevation(Elevation);
	DUT.SetDirectivity(Directivity);
	float Result = DUT.Process(Input);
	if (abs(Result - Expected) < 10e-8)
		++Passed;
	else
	{
		++Failed;
		std::cout << "Test failed with input: {" << Input.W << ", "<< Input.X << ", " << Input.Y << ", " << Input.Z << "}, " <<
			"azimuth: " << Azimuth << " , elevation: " << Elevation << " , directivity: " << Directivity << "\n" <<
			"Expected: " << Expected << "\n Actual: " << Result << "\n";
	}
}

int RunB2MonoTest()
{
	constexpr double PI = 3.141592653589793116;
	float OmniLevel = sqrt(0.5f);
	int Passed = 0;
	int Failed = 0;

	BSample Omni{ OmniLevel, 0.0, 0.0, 0.0 };
	BSample XPlus{ OmniLevel, 1.0, 0.0, 0.0 };
	BSample XMinus{ OmniLevel, -1.0, 0.0, 0.0 };

	BSample YPlus{ OmniLevel, 0.0, 1.0, 0.0 };
	BSample YMinus{ OmniLevel, 0.0, -1.0, 0.0 };
	
	BSample ZPlus{ OmniLevel, 0.0, 0.0, 1.0 };
	BSample ZMinus{ OmniLevel, 0.0, 0.0, -1.0 };

	double Null = 0.0;
	double FullPlus = 1.0;

	double Fig8Dir = 0.0;

	double Elevation = 0.0;
	// test null-response of X-oriented Figure-of-eight
	double Azimuth = 0;
	Test(Null, YPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, YMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, ZPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, ZMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	Test(1.0, XPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(-1.0, XMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	Azimuth = PI;
	Test(Null, YPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, YMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, ZPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, ZMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	// test null-response of Y-oriented Figure-of-eight
	Azimuth = PI / 2;
	Test(Null, XPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, XMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, ZPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, ZMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	
	Test(FullPlus, YPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	Azimuth = -PI / 2;
	Test(Null, XPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, XMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, ZPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, ZMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	Test(FullPlus, YMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	// test null-response of Z-oriented Figure-of-eight
	Elevation = PI / 2;
	Azimuth = 0;
	Test(Null, XPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, XMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, YPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, YMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	Test(FullPlus, ZPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	Elevation = -PI / 2;
	Test(Null, XPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, XMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, YPlus, Azimuth, Elevation, Fig8Dir, Passed, Failed);
	Test(Null, YMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	Test(FullPlus, ZMinus, Azimuth, Elevation, Fig8Dir, Passed, Failed);

	// test null-response of X-oriented Cardioid
	Azimuth = 0.0;
	Elevation = 0.0;
	double CardioidDir = 0.5;

	Test(Null, XMinus , Azimuth, Elevation, CardioidDir, Passed, Failed);


	std::cout << Passed << " tests passed OK.\n" << Failed << " test failed.\n";
	return Failed;
}

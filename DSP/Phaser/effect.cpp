#include "effect.h"


void Effect::setDryWet(float wetInput)
{
	// making sure input cannot go outside of range
	if(wetInput > 1)
	{
		wetInput = 1;
	}
	else if(wetInput < 0)
	{
		wetInput = 0;
	}
	// dry is the opposite of wet
	wet = wetInput;
	dry = 1 - wetInput;
}
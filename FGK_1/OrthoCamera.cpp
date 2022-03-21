#include "OrthoCamera.h"

void OrthoCamera::renderScene()
{
	for(unsigned int y = 0; y < getRenderHeight(); y++)
	{
		for(unsigned int x = 0; x < getRenderWidth(); x++)
		{
			LightIntensity pixelLight;
			
			int horizontalSection = getRenderWidth() / 6;
			int verticalSection = getRenderHeight() / 6;
			
			if(x < horizontalSection or x >= horizontalSection * 3 and x < horizontalSection * 4)
			{
				pixelLight.add(1., 0., 0.);
			}
			if(x >= horizontalSection and x < horizontalSection * 2 or
			   x >= horizontalSection * 4 and x < horizontalSection * 5)
			{
				pixelLight.add(0., 1., 0.);
			}
			if(x >= horizontalSection * 2 and x < horizontalSection * 3 or
			   x >= horizontalSection * 5 and x < horizontalSection * 6)
			{
				pixelLight.add(0., 0., 1.);
			}
			
			pixelLight *= float(y) / float(getRenderHeight());
			
			setPixel(x, y, pixelLight);
		}
	}
}

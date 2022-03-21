#include "Camera.h"

Camera::Camera(unsigned int imageWidth, unsigned int imageHeight):
	Camera(imageWidth, imageHeight, float3(0, 0, 0), float3(0, 0, 1))
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////

Camera::Camera(unsigned int imageWidth, unsigned int imageHeight, float3 position, float3 target):
	image(nullptr), renderWidth(imageWidth), renderHeight(imageHeight),
	position(position), target(target)
{
	nearPlane = 1;
	farPlane = 1000;
	up = float3(0, 1, 0);
	
	image = new LightIntensity[renderWidth * renderHeight];
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Camera::~Camera()
{
	if(image != nullptr)
	{
		delete[] image;
		image = nullptr;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::setPixel(unsigned int x, unsigned int y, LightIntensity &light)
{
	image[x + y * renderWidth] = light;
}

LightIntensity Camera::getPixel(unsigned int x, unsigned int y)
{
	return image[x + y * renderWidth];
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::getRGBImage(void *data)
{
	uint8_t *surface = reinterpret_cast<uint8_t*>(data);
	
	for(unsigned int y = 0; y < renderHeight; y++)
	{
		for(unsigned int x = 0; x < renderWidth; x++)
		{
			//TODO light normalization
			surface[x * 3 + y * renderWidth * 3 + 0] = image[x + y * renderWidth].gRed() * 255;
			surface[x * 3 + y * renderWidth * 3 + 1] = image[x + y * renderWidth].gGreen() * 255;
			surface[x * 3 + y * renderWidth * 3 + 2] = image[x + y * renderWidth].gBlue() * 255;
		}
	}
}

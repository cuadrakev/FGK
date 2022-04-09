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
	
	image = new float3[renderWidth * renderHeight];
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

void Camera::setPixel(unsigned int x, unsigned int y, float3 &light)
{
	image[x + (renderHeight - y - 1) * renderWidth] = light;
}

float3 Camera::getPixel(unsigned int x, unsigned int y)
{
	return image[x + (renderHeight - y - 1) * renderWidth];
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::getRGBImage(void *data)
{
	uint8_t *surface = reinterpret_cast<uint8_t*>(data);
	
	for(unsigned int y = 0; y < renderHeight; y++)
	{
		for(unsigned int x = 0; x < renderWidth; x++)
		{
			float3 color = image[x + y * renderWidth];
			float m = std::max(color.x, std::max(color.y, color.z));
			if(m > 1.)
				color = color / m;
			
			surface[x * 3 + y * renderWidth * 3 + 0] = color.x * 255;
			surface[x * 3 + y * renderWidth * 3 + 1] = color.y * 255;
			surface[x * 3 + y * renderWidth * 3 + 2] = color.z * 255;
		}
	}
}

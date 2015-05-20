#pragma once

//#include "..\Renderer\Cubemap.hpp"

class PointLight
{
private:
	//Cubemap *shadowMap;

public:
	float position[3];
	float diffuseColor[3];
	float diffuseIntensity;
	float specularIntensity;
	float specularPower;
	float attenuation[3]; // constant, linear, exponent

	~PointLight();

	bool create();

	void beginDrawingToShadowMap();
};
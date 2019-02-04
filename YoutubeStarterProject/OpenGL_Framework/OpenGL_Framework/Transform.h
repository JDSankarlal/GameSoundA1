#pragma once

#include <MiniMath/Core.h>
#include <string>
#include <vector>

class Transform
{
public:
	float m_pScale = 1.0f;
	float m_pRotX = 0.0f;
	float m_pRotY = 0.0f;
	float m_pRotZ = 0.0f;

	vec3 m_pLocalPosition;

	// TODO: Compute these matrices in the Update function
	mat4 m_pLocalRotation;
	mat4 m_pLocalToWorldMatrix;

	Transform();

	void setPosition(vec3 newPosition);
	void setRotationAngleX(float newAngle);
	void setRotationAngleY(float newAngle);
	void setRotationAngleZ(float newAngle);
	void setScale(float newScale);

	vec3 getPosition();
	float getRotationAngleY();

	mat4 getLocalToWorldMatrix();
	void addChild(Transform*);
	// TODO: Implement this update function
	virtual void update(float dt);	
	
	std::vector<Transform*>children;
	Transform* parent;
	// Other Properties
	std::string name;
	vec4 color; 
};
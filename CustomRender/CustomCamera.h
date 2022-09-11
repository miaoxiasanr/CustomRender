#ifndef CUSTOMCAMERA_H
#define CUSTOMCAMERA_H
#include "CustomTransform.h"
#include "Configure.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
class Camera
{
public:
	vector3f Position;
	vector3f Front;
	vector3f Up;
	vector3f Right;
	vector3f WorldUp;
	
	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
public:
	Camera(vector3f position=vector3f(0.f,3.f,0.f),vector3f up=vector3f(0.f,1.f,0.f),float yaw=YAW,float pitch=PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	Matrix GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction,float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
private:
	void updateCameraVectors();





};
#endif // CUSTOMCAMERA_H



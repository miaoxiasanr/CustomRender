#include "CustomCamera.h"





Camera::Camera(vector3f position/*=vector3f(0.f,3.f,0.f)*/, vector3f up/*=vector3f(0.f,1.f,0.f)*/, float yaw/*=YAW*/, float pitch/*=PITCH*/)
	:Front(vector3f(0.f,0.f,-1.f)),MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	:Front(vector3f(0.f, 0.f, -1.f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = vector3f(posX, posY, posZ);
	WorldUp = vector3f(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Matrix Camera::GetViewMatrix()
{
	return LookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		Position =Position+ Front * velocity;
	if (direction == Camera_Movement::BACKWARD)
		Position =Position- Front * velocity;
	if (direction == Camera_Movement::LEFT)
		Position =Position- Right * velocity;
	if (direction == Camera_Movement::RIGHT)
		Position =Position+ Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch /*= true*/)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	//Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	//if (Zoom > 45.0f)
		//Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	vector3f front;
	front.x = cos(Radians(Yaw)) * cos(Radians(Pitch));
	front.y = sin(Radians(Pitch));
	front.z = sin(Radians(Yaw)) * cos(Radians(Pitch));
	Front = front.Normalize();
	Right = vector3f::Cross(Front, WorldUp).Normalize();
	Up= vector3f::Cross(Right, Front).Normalize();
}


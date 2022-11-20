#ifndef CAMERA_h

#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


// Constantes

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;
const float SENSIBILITY = 0.1f;
const float SPEED = 2.5f;


enum class MOVEMENT {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Camera
{
public:
	//Euler angle
	float Yaw_;
	float Pitch_;

	//Camera attributes
	glm::vec3 Position_;
	glm::vec3 Front_;
	glm::vec3 Right_;
	glm::vec3 WorldUp_;
	glm::vec3 Up_;

	// Camera options
	float Zoom_;
	float MovementSpeed_;
	float MouseSensibility_;
	GLboolean constrainPitch_ = true;

	Camera(glm::vec3 position, glm::vec3 front, float yaw, float pitch, float zoom);
	~Camera();

	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(MOVEMENT direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset);
	void ProcessMouseScroll(float yOffset);

private:

	void UpdateCameraVectors();


};

#endif


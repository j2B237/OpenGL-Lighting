#include "Camera.h"


/***********************************************/
Camera::Camera(glm::vec3 position, glm::vec3 front, float yaw, float pitch, float zoom)
{
	Position_			= position;
	Front_				= front;
	WorldUp_			= glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw_				= yaw;
	Pitch_				= pitch;
	Zoom_				= ZOOM;
	MovementSpeed_		= SPEED;
	MouseSensibility_	= SENSIBILITY;
	
	UpdateCameraVectors();
}

/***********************************************/

Camera::~Camera(){}				// Destructeur

/************************************************/

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position_, Position_ + Front_, Up_);
}

/**************************************************/

void Camera::ProcessKeyboard(MOVEMENT direction, float deltaTime)
{
	float velocity = MovementSpeed_ * deltaTime;

	if (direction == MOVEMENT::FORWARD)
	{
		Position_ += Front_ * velocity;
	}
	if (direction == MOVEMENT::BACKWARD)
	{
		Position_ -= Front_ * velocity;
	}
	if (direction == MOVEMENT::LEFT)
	{
		Position_ += Right_ * velocity;
	}
	if (direction == MOVEMENT::RIGHT)
	{
		Position_ -= Right_ * velocity;
	}
}

/****************************************************/

void Camera::ProcessMouseMovement(float xOffset, float yOffset)
{
	xOffset *= MouseSensibility_;
	yOffset *= MouseSensibility_;

	Yaw_ += xOffset;
	Pitch_ += yOffset;

	if (constrainPitch_)
	{
		if (Pitch_ > 89.0f)		{ Pitch_ = 89.0f; }
		if (Pitch_ < -89.0f)	{ Pitch_ = -89.0f; }
	}

	UpdateCameraVectors();
}

/****************************************************/

void Camera::ProcessMouseScroll(float yOffset)
{
	Zoom_ -= static_cast<float>(yOffset);

	if (Zoom_ < 1.0f)	{ Zoom_ = 1.0f; }
	if (Zoom_ > 45.0f)	{ Zoom_ = 45.0f; }
}


/****************************************/
// private

void Camera::UpdateCameraVectors()
{
	// Calculate the new front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw_)) * cos(glm::radians(Pitch_));
	front.y = sin(glm::radians(Pitch_));
	front.z = sin(glm::radians(Yaw_)) * cos(glm::radians(Pitch_));

	Front_	= glm::normalize(front);
	Right_	= glm::normalize(glm::cross(Front_, WorldUp_));
	Up_		= glm::normalize(glm::cross(Right_, Front_));

}

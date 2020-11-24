#pragma once

#include <iostream>
#include <GameObject.h>
#include <Input.h>
#include <Texture.h>


class UIButton : public CoreEngineNS::GameObject
{
private:
	enum STATE
	{
		IDLE,
		HIGHLIGHTED,
		PRESSED	
	};

	STATE m_currentState;
	float m_Vertices[12];
	float m_TextCoord[8];
	int indices[6];

	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;
	
	RenderEngineNS::Texture* texture;

	int m_Width;
	int m_Height;
	bool m_IsPressed;

public:
	UIButton() = default;
	UIButton(int p_width, int p_height, int p_PosX, int p_PosY);
	~UIButton();

	void Draw();
	void OnClick();
	void isHighLighted();

	void SetTexture(std::string&& texture_name);

	//GETTERS
	glm::vec3 getPosition();
	int getHeight();
	int getWidth();
	bool isPressed();

	//SETTERS
	void setPressed(bool p_pressed);
};





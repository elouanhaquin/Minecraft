#include "stdafx.h"
#include "UIButton.h"
#include <ResourceManager.h>




UIButton::UIButton(int p_width, int p_height, int p_PosX, int p_PosY) : texture(nullptr)
{

	m_Vertices[0] = p_PosX - (p_width / 2); m_Vertices[1] = p_PosY - (p_height / 2);  m_Vertices[2] = -10.0f;
	m_Vertices[3] = p_PosX + (p_width / 2); m_Vertices[4] = p_PosY - (p_height / 2);  m_Vertices[5] = -10.0f;
	m_Vertices[6] = p_PosX - (p_width / 2); m_Vertices[7] = p_PosY + (p_height / 2);  m_Vertices[8] = -10.0f;
	m_Vertices[9] = p_PosX + (p_width / 2); m_Vertices[10] = p_PosY + (p_height / 2); m_Vertices[11] = -10.0f;

	m_TextCoord[0] = 0; m_TextCoord[1] = 0;		//Bottom left	
	m_TextCoord[2] = 1; m_TextCoord[3] = 0;		//Bottom R
	m_TextCoord[4] = 0; m_TextCoord[5] = 1;		//Top L
	m_TextCoord[6] = 1; m_TextCoord[7] = 1;		// Top R

	float fin[20];

	for (int i = 0; i < 20; ++i)
	{
		if (i < 12)
			fin[i] = m_Vertices[i];
		else
			fin[i] = m_TextCoord[(i - 12)];
	}

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 1;

	m_Width = p_width;
	m_Height = p_height;

	glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 10.0f);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fin), fin, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(12 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO);

}

void UIButton::SetTexture(std::string&& texture_name)
{
	texture = CoreEngineNS::ResourceManager::Instance().GetTexture(texture_name.c_str());
}

UIButton::~UIButton()
{
	//if(m_Vertices != nullptr)
	//	delete m_Vertices;
}

void UIButton::Draw()
{
	glActiveTexture(GL_TEXTURE0);

	Shader* s = nullptr;
	s = CoreEngineNS::ResourceManager::Instance().GetShader("Nano");
	if (texture != nullptr && s != nullptr)	s->SetUniform1i("texture_diffuse1", 0);
	if (texture != nullptr)	glBindTexture(GL_TEXTURE_2D, texture->m_id);

	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0,6);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	if (texture != nullptr) glActiveTexture(GL_TEXTURE0);
}

void UIButton::OnClick()
{

	if (m_currentState != STATE::PRESSED) 
	{
		m_currentState = STATE::PRESSED;
		m_IsPressed = true;
	}

}

void UIButton::isHighLighted()
{
	float mousePositionX = CoreEngineNS::Input::MouseX() / 1280 * 30 - 15;		//DIRTY CHANGE HERE
	float mousePositionY = -(CoreEngineNS::Input::MouseY() / 720 * 16 - 8 );	//SAME HERE

	bool inside = 
		   mousePositionX < getPosition().x + (getWidth() * 0.5f)
		&& mousePositionX > getPosition().x - (getWidth() * 0.5f)
		&& mousePositionY < getPosition().y + (getHeight() * 0.5f)
		&& mousePositionY > getPosition().y - (getHeight() * 0.5f);

	if (inside)
	{
		if(m_currentState != STATE::HIGHLIGHTED)
			m_currentState = STATE::HIGHLIGHTED;

		if (CoreEngineNS::Input::isClick())
				OnClick();	

	}
	else if(!inside && m_currentState != STATE::IDLE)
	{
		m_currentState = STATE::IDLE;
		m_IsPressed = false;
	}	
}

glm::vec3 UIButton::getPosition()
{
	return glm::vec3((m_Vertices[0] + m_Vertices[3]) / 2, (m_Vertices[1] + m_Vertices[7]) / 2, m_Vertices[2]);
}

int UIButton::getHeight()
{
	return m_Height;
}

int UIButton::getWidth()
{
	return m_Width;
}

bool UIButton::isPressed()
{
	isHighLighted();
	return m_IsPressed;
}

void UIButton::setPressed(bool p_pressed)
{
	m_IsPressed = p_pressed;
}

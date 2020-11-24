#include "stdafx.h"
#include "UIMenu.h"


UIMenu::UIMenu(uint8_t p_NumberOfButton, bool IsBackground)
{
	m_CurrentState = State::MENU;
	for(int i = 0; i < p_NumberOfButton; ++i)
	{
		int posY = (16 / p_NumberOfButton) - (i * 5);
		m_Buttons.emplace_back(new UIButton(10, 3, 0, posY));
	}

	m_NumberOfButtons = p_NumberOfButton;
}

UIMenu::~UIMenu()
{

}

void UIMenu::Render()
{
	for (int i = 0; i < m_NumberOfButtons; ++i)
		m_Buttons[i]->Draw();
	
}


UIButton& UIMenu::GetButton(int p_number)
{
	return *m_Buttons[p_number];
}

void UIMenu::SetState(State p_CurrentState)
{
	m_CurrentState = p_CurrentState;
}

#pragma once
#include "Stdafx.h"
#include "UIButton.h"

class UIMenu
{
private:
	enum State
	{
		MENU,
		INGAMEMENU,
	};

	std::vector<UIButton*> m_Buttons;
	State m_CurrentState;
	uint8_t m_NumberOfButtons;
public:
	UIMenu(uint8_t p_NumberOfButton, bool IsBackground);
	~UIMenu();

	void Render();

	UIButton& GetButton(int p_number);
	State getState() { return m_CurrentState; }

	void SetState(State p_CurrentState);
	
};


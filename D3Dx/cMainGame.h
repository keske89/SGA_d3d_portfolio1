#pragma once
#include "cGameNode.h"



class cCamera;
<<<<<<< HEAD

=======
>>>>>>> 445e560e1e64f13ec5bf15aa0ff98005c21d0744


class cMainGame : public cGameNode
{
private:
	cCamera *	m_pCamera;


public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();

	
};


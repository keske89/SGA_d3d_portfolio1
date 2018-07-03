#pragma once

class cIGObj;
class cKinfe;
class cTomato;


class cIGObjManager
{
public:
	cIGObj*					m_Knife;
	cIGObj*					m_Tomato;
	std::vector<cIGObj*>	m_vecObj;


public:
	cIGObjManager();
	~cIGObjManager();

	void Setup();
	void Update();
	void Render();


};


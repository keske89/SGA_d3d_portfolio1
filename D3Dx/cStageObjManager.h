#pragma once
#include "cIGObj.h"

class cIGObj;
class cCharacter;
class cCrate;
class cKnife;
class cPot;
class cSink;
class cCooker;
class cPass;
class cPassScroll;


enum BUTTONSELECT
{
	BUTTON_1,
	BUTTON_2,
	BUTTON_END
};

class cStageObjManager : public cActionDelegate
{
private:

	cCrate * m_crate;
	cSink*					 m_Sink;
	cCooker*				 m_Cooker;

	int m_buttonSelect;

	SYNTHESIZE(cCharacter*, m_player1, Player1);
	SYNTHESIZE(cCharacter*, m_player2, Player2);
	SYNTHESIZE(std::vector<cIGObj*>, m_vecObj, vecObj);


public:
	cStageObjManager();
	~cStageObjManager();

	void Setup();
	void Update();
	void Render();
	void AddObject(cIGObj* object) { m_vecObj.push_back(object); };
	void DeleteObject(cIGObj* object);

	void ActionControl();

	// cActionDelegate을(를) 통해 상속됨

	virtual void OnAction(cIGObj* pSender) override;

};


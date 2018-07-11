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

enum OBJECTTYPE
{
	// CRATE = 10~ 
	//CRATE_LID = 10,
	CRATE_TOMATO = 11,
	CRATE_POTATO = 12,
	CRATE_MUSHROOM = 13,
	CRATE_ONION = 14,

	// ACTION OBJ 20~

	AOBJ_BIN = 20,
	AOBJ_CHOPPIGNBOARD = 21,
	AOBJ_COOKER = 22,
	//AOBJ_KNIFE = 23,
	AOBJ_PASS = 23,
	//AOBJ_PASSSCROLL = 25,
	AOBJ_PLATE = 24,
	AOBJ_PLATERETURNBOX = 25,
	AOBJ_POT = 26,
	AOBJ_SINK = 27,

	// FOOD OBJ 30~
	FOBJ_POTATO = 30,
	FOBJ_TOMATO = 31,
	FOBJ_MUSHROOM = 32,
	FOBJ_ONION = 33,

};

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

	void SetIngameObject(OBJECTTYPE objtype, D3DXMATRIX matWorld);
};


#pragma once

class cIGObj;
class cCharacter;
class cCrate;
class cKnife;
class cPot;
class cSink;


class cStageObjManager
{
private:
	
	cCrate*					 m_crate;

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

};


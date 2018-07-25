#pragma once
#include "IDisplayObject.h"
#include "cWMDefinition.h"

class UIObject;
class cSphere;

class cWMStarBoard : public IDisplayObject
{
private:

	UIObject * m_pStarBoard;
	cSphere* m_pSphere;
	int m_nScore;	//score

	cParticles*		m_pParticle;
	vector<cEffectObject*> m_vecEffect;

public:
	cWMStarBoard();
	virtual ~cWMStarBoard();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	//Effect
	void EffectSetup();
	void Effect();

	void Animation(int score = 0);

	D3DXVECTOR2 Convert3DTo2D(D3DXVECTOR3 v);
	void SetAddressLinkWithSphere(cSphere* sphere) { m_pSphere = sphere; }

	void setScore(int score) { m_nScore = score; }
	int getScore() { return m_nScore; }
};




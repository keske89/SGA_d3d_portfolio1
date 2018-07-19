#pragma once
#include "cWMDefinition.h"

#include "IDisplayObject.h"

class cWorldMapObj;

class cWMBorder : public IDisplayObject
{
private:
	cWorldMapObj * m_Border;

public:
	cWMBorder();
	virtual ~cWMBorder();

	//IDisplayObject Inherited
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};


#include "stdafx.h"
#include "cKnife.h"
#include "cProgressbar.h"


cKnife::cKnife()
	:progressbar(NULL)
{
	m_vPos = D3DXVECTOR3(0, 0, 0);
}


cKnife::~cKnife()
{
	SAFE_DELETE(progressbar);
}

void cKnife::Setup()
{
	progressbar = new cProgressbar;
	progressbar->Setup(m_vPos);
}

void cKnife::Update()
{
	progressbar->Update(m_vPos);

	if(KEYMANAGER->isStayKeyDown('F'))
	{
		m_bIsUse = true;
	}
	else
	{
		m_bIsUse = false;
	}
	
	if (m_bIsUse)
	{
		progressbar->SetProgress();
	}
	
}

void cKnife::Render()
{
	progressbar->Render(m_vPos);
}

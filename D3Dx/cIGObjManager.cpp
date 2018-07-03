#include "stdafx.h"
#include "cIGObjManager.h"
#include "cTomato.h"



cIGObjManager::cIGObjManager()
{
}


cIGObjManager::~cIGObjManager()
{
}

void cIGObjManager::Setup()
{
	m_Tomato = new cTomato;
	m_Tomato->Setup();

	m_vecObj.push_back(m_Tomato);
	
}

void cIGObjManager::Update()
{
}

void cIGObjManager::Render()
{
	
}

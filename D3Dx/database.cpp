#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{
}

void database::Release()
{
}

void database::Setup()
{
	for (int i = 0; i < 10; ++i)
	{
		m_bIsStageclear[i] = true;
		m_nStageStar[i] = 2;
	}

}

void database::Update()
{
	//
	//for (int i = 0; i < 8; ++i)
	//{
	//	char temp[32];
	//	sprintf(temp, "��������%d", (i + 1));
	//	stageManager* tempScene = (stageManager*)SCENEMANAGER->findScene(temp);
	//	_isStageClear[i] = tempScene->getIsWin();
	//}
}

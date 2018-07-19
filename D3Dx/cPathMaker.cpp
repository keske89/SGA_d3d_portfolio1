#include "stdafx.h"
#include "cPathMaker.h"


cPathMaker::cPathMaker()
{
}


cPathMaker::~cPathMaker()
{
}

void cPathMaker::CreatePath(PATH_TYPE type, D3DXVECTOR3 From, D3DXVECTOR3 To, vector<cPath*>& vec)
{
	if (type == PATH_STRAIGHT)
	{
		cPath* v = new cPath;
		v->SetType(PATH_STRAIGHT);
		v->Setup();
		v->setTrack(From, To);
		v->SetAnimation(false);
		vec.push_back(v);
	}
	else if (type == PATH_CURVED)
	{
		cPath* v1 = new cPath;
		cPath* v2 = new cPath;
		cPath* v3 = new cPath;
		v1->SetType(PATH_STRAIGHT);
		v1->Setup();
		v1->setTrack(From, D3DXVECTOR3(To.x, To.y, From.z));
		v1->SetAnimation(false);
		vec.push_back(v1);

		v2->SetType(PATH_STRAIGHT);
		v2->Setup();
		v2->setTrack(D3DXVECTOR3(To.x, To.y, From.z), To);
		v2->SetAnimation(false);
		vec.push_back(v2);

		v3->SetType(PATH_CURVED);
		v3->Setup();
		v3->setTrack(From, To);
		v3->SetAnimation(false);
		vec.push_back(v3);

	}

}

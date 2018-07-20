#pragma once
#include"cChefRoot.h"
enum IMAGENUM
{
	IMAGENUM_BRAR,
	IMAGENUM_BRARD,
	IMAGENUM_BLACKCAT,
	IMAGENUM_BOOF,
	IMAGENUM_BOX,
	IMAGENUM_BUCK,
	IMAGENUM_DINO,
	IMAGENUM_DOG
};
class cChefHead :public cChefRoot
{
private:
	IMAGENUM chageNum;
public:
	cChefHead();
	virtual~cChefHead();
	virtual void SetUp();
	void SetChageNum(int imageChageNum) { chageNum = (IMAGENUM)imageChageNum; }
};


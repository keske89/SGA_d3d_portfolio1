#pragma once

template <typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase(){};
	~singletonBase(){};

public:

	static T* getSingleton(void);

	void releaseSingleton(void);

};

//싱글톤 초기화
template <typename T>
T* singletonBase<T>::singleton = 0;

//싱글톤 불러오는 함수
template <typename T>
T* singletonBase<T>::getSingleton()
{
	//싱글톤이 없으면 싱글톤을 생성해라
	if (!singleton) singleton = new T;

	return singleton;
}

//싱글톤 해제 함수

template <typename T>
void singletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}

#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameNode.h"


cSceneManager::cSceneManager()
{
	m_pCurrentScene = NULL;
	m_pLoadingScene = NULL;
	m_pReadyScene = NULL;
	m_dwLoadingThreadID = 0;
}


cSceneManager::~cSceneManager()
{
}


DWORD CALLBACK LoadingThread(LPVOID prc)
{
	//바꿔줄 씬을 미리 초기화해 둔다
	cSceneManager::m_pReadyScene->Setup();

	//현재 씬으로 교체 해준다
	cSceneManager::m_pCurrentScene = cSceneManager::m_pReadyScene;

	//로딩에 쓰인 씬을 해제해주고, 대기시켜놨던 씬도 해제
	SAFE_DELETE(cSceneManager::m_pLoadingScene);
	cSceneManager::m_pLoadingScene = NULL;
	cSceneManager::m_pReadyScene = NULL;

	//중요한건 아마 쓸일 없다는거 또르르르르...

	return 0;
}

//스태틱으로 선언 되어있으므로 초기화는 여기서
cGameNode* cSceneManager::m_pCurrentScene = NULL;
cGameNode* cSceneManager::m_pLoadingScene = NULL;
cGameNode* cSceneManager::m_pReadyScene = NULL;

void cSceneManager::Setup()
{
}

void cSceneManager::Destroy()
{
	mapSceneIter miSceneList = m_mapSceneList.begin();

	for (; miSceneList != m_mapSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == m_pCurrentScene) miSceneList->second->Destroy();
			SAFE_DELETE(miSceneList->second);
			miSceneList = m_mapSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	m_mapSceneList.clear();
}

void cSceneManager::Update()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Update();
}

void cSceneManager::Render()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
}

void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrentScene)
		m_pCurrentScene->WndProc(hWnd, message, wParam, lParam);
}

cGameNode* cSceneManager::AddScene(string sceneName, cGameNode * scene)
{
	//씬이 없다면 널값 반환
	if (!scene) return NULL;

	//씬에 키 값을 부여해서 map컨테이너에 담아준다
	m_mapSceneList.insert(make_pair(sceneName, scene));

	//반환
	return scene;
}

cGameNode* cSceneManager::AddLoadingScene(string loadingSceneName, cGameNode * scene)
{
	//역시 씬이 없다면 NULL값 반환
	if (!scene) return NULL;

	//로딩씬에 키값을 붙여서 맵컨테이너에 담아준다
	m_mapSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT cSceneManager::ChangeScene(string sceneName)
{
	//이터레이터에 찾고자하는 씬의 키 값을 대입
	mapSceneIter find = m_mapSceneList.find(sceneName);

	//이터레이터가 맵의 끝까지 갔다 == 찾고자하는게 없다 실패 반환
	if (find == m_mapSceneList.end()) return E_FAIL;

	//만약 바꾸려는 씬이 현재 씬이면 그냥 둔다
	if (find->second == m_pCurrentScene) return S_OK;

	//성공적으로 씬이 바뀐다면 init함수 실행 
	if (find->second != NULL)
	{
		//만약 현재씬에 다른 씬이 있다면 해제 해주고
		if (m_pCurrentScene) 
			m_pCurrentScene->Destroy();

		//바꾸려는 씬으로 체인지 한다
		m_pCurrentScene = find->second;
		m_pCurrentScene->Setup();

		//지금 씬 변환하는 이 구조는 여러분이 입맛에 따라 바꿔도 된다
		//디폴트로 만들어 놨지만 위에 구조의 단점이 딱 하나 있는데
		//스테이지1 -> 스테이지2로 씬이 바뀌었을때 스테이지1의 데이터를
		//넘기려고 할때 릴리즈가 먼저 호출이 되서 조금 신경을 써줘야한다

		//뭐 그렇다고.. ㅎ _ㅎ)

		return S_OK;
	}

	return E_FAIL;
}

HRESULT cSceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	//이터레이터에 찾고자하는 씬의 키 값을 대입
	mapSceneIter find = m_mapSceneList.find(sceneName);


	if (find == m_mapSceneList.end()) return E_FAIL;
	if (find->second == m_pCurrentScene) return S_OK;

	//로딩하려는 씬을 찾는다
	mapSceneIter findLoading = m_mapLoadingSceneList.find(loadingSceneName);

	//예외처리 알죠?
	if (find == m_mapLoadingSceneList.end()) return ChangeScene(loadingSceneName);

	//성공적으로 씬이 바뀐다면 init함수 실행 
	if (find->second != NULL)
	{
		//만약 현재씬에 다른 씬이 있다면 해제 해주고
		if (m_pCurrentScene) m_pCurrentScene->Destroy();

		//로딩씬을 찾아서 대입하고
		m_pLoadingScene = findLoading->second;
		//바꾸려는 씬을 준비시켜둔다
		m_pReadyScene = find->second;

		//로딩에 쓰인 쓰레드 꺼준다
		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &m_dwLoadingThreadID));

		return S_OK;
	}

	return E_FAIL;
}

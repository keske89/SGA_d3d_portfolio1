#pragma once

class cGameNode;

#define SCENEMANAGER cSceneManager::GetInstance()

class cSceneManager
{
	SINGLETONE(cSceneManager)

public:
	typedef map<string, cGameNode*>				mapSceneList;
	typedef map<string, cGameNode*>::iterator	mapSceneIter;

private:
	static cGameNode*	m_pCurrentScene;		//현재 씬
	static cGameNode*	m_pLoadingScene;		//로딩 씬(안쓰일듯)
	static cGameNode*	m_pReadyScene;			//대기 씬

	mapSceneList		m_mapSceneList;
	mapSceneList		m_mapLoadingSceneList;

	DWORD				m_dwLoadingThreadID;	//혹시 몰라 넣어놓는 쓰레드용 ID

public:
	void Setup();
	void Destroy();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//씬 추가 함수
	cGameNode* AddScene(string sceneName, cGameNode* scene);
	cGameNode* AddLoadingScene(string loadingSceneName, cGameNode* scene);

	//씬 변경
	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	//friend란 선언하면 클래스의 private까지 그냥 접근 가능케 한다
	//남발하면 안되는데, 구조상 왠지 1~2개정도는 해두면 좋을 것 같으면 해도됨
	friend DWORD CALLBACK LoadingThread(LPVOID prc);
};


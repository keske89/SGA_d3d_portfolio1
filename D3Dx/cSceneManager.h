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
	static cGameNode*	m_pCurrentScene;		//���� ��
	static cGameNode*	m_pLoadingScene;		//�ε� ��(�Ⱦ��ϵ�)
	static cGameNode*	m_pReadyScene;			//��� ��

	mapSceneList		m_mapSceneList;
	mapSceneList		m_mapLoadingSceneList;

	DWORD				m_dwLoadingThreadID;	//Ȥ�� ���� �־���� ������� ID

public:
	void Setup();
	void Destroy();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//�� �߰� �Լ�
	cGameNode* AddScene(string sceneName, cGameNode* scene);
	cGameNode* AddLoadingScene(string loadingSceneName, cGameNode* scene);

	//�� ����
	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	//friend�� �����ϸ� Ŭ������ private���� �׳� ���� ������ �Ѵ�
	//�����ϸ� �ȵǴµ�, ������ ���� 1~2�������� �صθ� ���� �� ������ �ص���
	friend DWORD CALLBACK LoadingThread(LPVOID prc);
};


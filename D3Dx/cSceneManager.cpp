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
	//�ٲ��� ���� �̸� �ʱ�ȭ�� �д�
	cSceneManager::m_pReadyScene->Setup();

	//���� ������ ��ü ���ش�
	cSceneManager::m_pCurrentScene = cSceneManager::m_pReadyScene;

	//�ε��� ���� ���� �������ְ�, �����ѳ��� ���� ����
	SAFE_DELETE(cSceneManager::m_pLoadingScene);
	cSceneManager::m_pLoadingScene = NULL;
	cSceneManager::m_pReadyScene = NULL;

	//�߿��Ѱ� �Ƹ� ���� ���ٴ°� �Ǹ�������...

	return 0;
}

//����ƽ���� ���� �Ǿ������Ƿ� �ʱ�ȭ�� ���⼭
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
	//���� ���ٸ� �ΰ� ��ȯ
	if (!scene) return NULL;

	//���� Ű ���� �ο��ؼ� map�����̳ʿ� ����ش�
	m_mapSceneList.insert(make_pair(sceneName, scene));

	//��ȯ
	return scene;
}

cGameNode* cSceneManager::AddLoadingScene(string loadingSceneName, cGameNode * scene)
{
	//���� ���� ���ٸ� NULL�� ��ȯ
	if (!scene) return NULL;

	//�ε����� Ű���� �ٿ��� �������̳ʿ� ����ش�
	m_mapSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT cSceneManager::ChangeScene(string sceneName)
{
	//���ͷ����Ϳ� ã�����ϴ� ���� Ű ���� ����
	mapSceneIter find = m_mapSceneList.find(sceneName);

	//���ͷ����Ͱ� ���� ������ ���� == ã�����ϴ°� ���� ���� ��ȯ
	if (find == m_mapSceneList.end()) return E_FAIL;

	//���� �ٲٷ��� ���� ���� ���̸� �׳� �д�
	if (find->second == m_pCurrentScene) return S_OK;

	//���������� ���� �ٲ�ٸ� init�Լ� ���� 
	if (find->second != NULL)
	{
		//���� ������� �ٸ� ���� �ִٸ� ���� ���ְ�
		if (m_pCurrentScene) 
			m_pCurrentScene->Destroy();

		//�ٲٷ��� ������ ü���� �Ѵ�
		m_pCurrentScene = find->second;
		m_pCurrentScene->Setup();

		//���� �� ��ȯ�ϴ� �� ������ �������� �Ը��� ���� �ٲ㵵 �ȴ�
		//����Ʈ�� ����� ������ ���� ������ ������ �� �ϳ� �ִµ�
		//��������1 -> ��������2�� ���� �ٲ������ ��������1�� �����͸�
		//�ѱ���� �Ҷ� ����� ���� ȣ���� �Ǽ� ���� �Ű��� ������Ѵ�

		//�� �׷��ٰ�.. �� _��)

		return S_OK;
	}

	return E_FAIL;
}

HRESULT cSceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	//���ͷ����Ϳ� ã�����ϴ� ���� Ű ���� ����
	mapSceneIter find = m_mapSceneList.find(sceneName);


	if (find == m_mapSceneList.end()) return E_FAIL;
	if (find->second == m_pCurrentScene) return S_OK;

	//�ε��Ϸ��� ���� ã�´�
	mapSceneIter findLoading = m_mapLoadingSceneList.find(loadingSceneName);

	//����ó�� ����?
	if (find == m_mapLoadingSceneList.end()) return ChangeScene(loadingSceneName);

	//���������� ���� �ٲ�ٸ� init�Լ� ���� 
	if (find->second != NULL)
	{
		//���� ������� �ٸ� ���� �ִٸ� ���� ���ְ�
		if (m_pCurrentScene) m_pCurrentScene->Destroy();

		//�ε����� ã�Ƽ� �����ϰ�
		m_pLoadingScene = findLoading->second;
		//�ٲٷ��� ���� �غ���ѵд�
		m_pReadyScene = find->second;

		//�ε��� ���� ������ ���ش�
		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &m_dwLoadingThreadID));

		return S_OK;
	}

	return E_FAIL;
}

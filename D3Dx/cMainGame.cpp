#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"

//WM
#include "cWorldMapScene.h"
#include "cIntroScene.h"
//

#include "cStageMapTool.h"
#include "cStageScene.h"
#include "cTestScene0.h"
#include "cTestScene1.h"
#include "cTestScene2.h"
#include "cTestScene3.h"


cMainGame::cMainGame()
	: m_pCamera(NULL)
{
}


cMainGame::~cMainGame()
{

	TIMEMANAGER->Destroy();
	SCENEMANAGER->Destroy();

	//WM
	delete m_pCamera;
	Assets::Delete();
	SAFE_RELEASE(SPRITE);
	IMAGEMANAGER->release();
	TEXTUREMANAGER->release();
	DATABASE->Release();
	//

	ObJMANAGER->Destroy();
	g_pTextureManager->Destroy();
	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	DATABASE->Setup();
	SetLight();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);


	//WM
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pWMScene = new cWorldMapScene;
	//
	SCENEMANAGER->AddScene("StageMapTool", new cStageMapTool);
	SCENEMANAGER->AddScene("StageScene", new cStageScene);
	SCENEMANAGER->AddScene("TestScene0", new cTestScene0);
	SCENEMANAGER->AddScene("TestScene1", new cTestScene1);
	SCENEMANAGER->AddScene("TestScene2", new cTestScene2);
	SCENEMANAGER->AddScene("WMScene", m_pWMScene);
	SCENEMANAGER->AddScene("IntroScene", new cIntroScene);
	
	SCENEMANAGER->ChangeScene("IntroScene");



	m_pWMScene->setCamera(m_pCamera);


}

void cMainGame::Update()
{
	m_pCamera->Update();
	SCENEMANAGER->Update();
	DATABASE->Update();

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(67, 111, 114), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	TIMEMANAGER->Render();
	SCENEMANAGER->Render();

	SCENEMANAGER->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	cGameNode::WndProc(hWnd, message, wParam, lParam);

	SCENEMANAGER->WndProc(hWnd, message, wParam, lParam);
	
}

void cMainGame::SetLight()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);

	g_pD3DDevice->LightEnable(0, false);
}



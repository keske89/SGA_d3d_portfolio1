#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"

#include "cTestScene3.h"
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
	delete m_pCamera;

	TIMEMANAGER->Destroy();
	SCENEMANAGER->Destroy();
	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	SetLight();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	SCENEMANAGER->AddScene("TestScene3", new cTestScene3);
	SCENEMANAGER->AddScene("TestScene0", new cTestScene0);
<<<<<<< HEAD
	SCENEMANAGER->AddScene("TestScene1", new cTestScene1);
	SCENEMANAGER->AddScene("TestScene2", new cTestScene2);
	SCENEMANAGER->AddScene("TestScene3", new cTestScene3);
	
	SCENEMANAGER->ChangeScene("TestScene1");
=======
	SCENEMANAGER->ChangeScene("TestScene3");

>>>>>>> 445e560e1e64f13ec5bf15aa0ff98005c21d0744

	m_pCamera = new cCamera;
	m_pCamera->Setup();


}

void cMainGame::Update()
{
	m_pCamera->Update();
	SCENEMANAGER->Update();

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	TIMEMANAGER->Render();
	SCENEMANAGER->Render();

	SCENEMANAGER->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	
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

	g_pD3DDevice->LightEnable(0, true);
}



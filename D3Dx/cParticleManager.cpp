#include "stdafx.h"
#include "cParticleManager.h"


cParticleManager::cParticleManager()
{
}


cParticleManager::~cParticleManager()
{
}

cParticleSystem::cParticleSystem()
	:m_pTexture(NULL)
	, m_pVB(NULL)
{
}

cParticleSystem::~cParticleSystem()
{
	SAFE_RELEASE(m_pVB);
	for (auto p : m_lAttribute)
	{
		SAFE_DELETE(p);
	}
}

void cParticleSystem::Setup(LPDIRECT3DTEXTURE9 texture, float size, int count, ST_PARTICLE_ATTRIBUTE * orig, ST_PARTICLE_ATTRIBUTE_VARIABLE * var)
{
	m_pTexture = texture;
	m_fParticleSize = size;
	m_nParticleCount = count;

	m_nVBSize = 2048;
	m_nVBBatchSize = m_nVBSize / 4;
	m_nVBOffset = 0;

	SAFE_DELETE(m_pVB);
	g_pD3DDevice->CreateVertexBuffer(
		m_nVBSize * sizeof(ST_PARTICLE),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		ST_PARTICLE::FVF,
		D3DPOOL_DEFAULT,
		&m_pVB, NULL);

	m_pOrigAttribute = orig;
	m_pVarAttribute = var;

	m_isRegen = true;

	D3DXMatrixIdentity(&m_matWorld);

	for (int i = 0; i < m_nParticleCount; i++)
		m_lAttribute.push_back(new ST_PARTICLE_ATTRIBUTE(ResetParticle(0)));

	TimeReset();
}

float FRand(float low, float high)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}

ST_PARTICLE_ATTRIBUTE cParticleSystem::ResetParticle(int loop)
{
	ST_PARTICLE_ATTRIBUTE att = *m_pOrigAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE var = *m_pVarAttribute;

	att.nLoop = loop;
	att.nLoop++;

	if (att.nLoop > att.nMaxLoop && att.nMaxLoop > 0 || !m_isRegen) att.isAlive = false;
	else att.isAlive = true;

	att.fLifeTime += FRand(-var.fLifeTimeVar, var.fLifeTimeVar);
	att.vPos.x += FRand(-var.vPosVar.x, var.vPosVar.x);
	att.vPos.y += FRand(-var.vPosVar.y, var.vPosVar.y);
	att.vPos.z += FRand(-var.vPosVar.z, var.vPosVar.z);

	att.vVelocity.x += FRand(-var.vVelocityVar.x, var.vVelocityVar.x);
	att.vVelocity.y += FRand(-var.vVelocityVar.y, var.vVelocityVar.y);
	att.vVelocity.z += FRand(-var.vVelocityVar.z, var.vVelocityVar.z);

	att.vAcceleration.x += FRand(-var.vAccelerationVar.x, var.vAccelerationVar.x);
	att.vAcceleration.y += FRand(-var.vAccelerationVar.y, var.vAccelerationVar.y);
	att.vAcceleration.z += FRand(-var.vAccelerationVar.z, var.vAccelerationVar.z);

	att.fStartRadius += FRand(-var.fStartRadiusVar, var.fStartRadiusVar);
	att.fEndRadius += FRand(-var.fEndRadiusVar, var.fEndRadiusVar);
	att.fRadiusSpeed += FRand(-var.fRadiusSpeedVar, var.fRadiusSpeedVar);

	return att;
}

void cParticleSystem::Attribute(ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var)
{
	*m_pOrigAttribute = orig;
	*m_pVarAttribute = var;
}

void cParticleSystem::TimeReset()
{
	auto iter = m_lAttribute.begin();
	for (; iter != m_lAttribute.end(); iter++)
	{
		(*iter)->nLoop = 0;
		(*iter)->isAlive = true;
	}

	iter = m_lAttribute.begin();
	for (;; iter++)
	{
		if (iter == m_lAttribute.end())
			iter = m_lAttribute.begin();
		(*iter)->fAge += 0.1;

		if ((*iter)->fAge > (*iter)->fLifeTime)
			break;
	}
}

void cParticleSystem::Update()
{
	auto iter = m_lAttribute.begin();
	int count = 0;
	for (; iter != m_lAttribute.end(); iter++)
	{
		if (!(*iter)->isAlive) continue;
		count++;

		float dist = D3DXVec3Length(&((*iter)->vGravityPos - (*iter)->vPos));
		if (dist > 1.0f && dist < (*iter)->fGravityRadius)
		{
			D3DXVECTOR3 dir = (*iter)->vGravityPos - (*iter)->vPos;
			D3DXVec3Normalize(&dir, &dir);
			float f = (*iter)->fGravityForce *(pow(m_fParticleSize, 2) / pow(dist, 2));
			(*iter)->vGravity += dir * f;
		}

		(*iter)->vPos +=
			(*iter)->vVelocity * TIMEMANAGER->getElapsedTime() + (*iter)->vAcceleration * TIMEMANAGER->getElapsedTime() + (*iter)->vGravity * TIMEMANAGER->getElapsedTime();

		(*iter)->vAcceleration += (*iter)->vAcceleration * TIMEMANAGER->getElapsedTime();
		(*iter)->fCurrentRadiusSpeed += (*iter)->fRadiusSpeed * TIMEMANAGER->getElapsedTime();
		(*iter)->fAge += TIMEMANAGER->getElapsedTime();

		if ((*iter)->fAge > (*iter)->fLifeTime) *(*iter) = ResetParticle((*iter)->nLoop);
	}
	if (count == 0) m_isDie = true;
	else m_isDie = false;
}

void cParticleSystem::ForceUpdate(int count, float time)
{
	for (int i = 0; i < count; i++)
	{
		auto iter = m_lAttribute.begin();
		for (; iter != m_lAttribute.end(); iter++)
		{
			if (!(*iter)->isAlive) continue;

			float dist = D3DXVec3Length(&((*iter)->vGravityPos - (*iter)->vPos));
			if (dist > 1.0f && dist < (*iter)->fGravityRadius)
			{
				D3DXVECTOR3 dir = (*iter)->vGravityPos - (*iter)->vPos;
				D3DXVec3Normalize(&dir, &dir);
				float f = (*iter)->fGravityForce * (m_fParticleSize / pow(dist, 2));
				(*iter)->vGravity += dir * f;
			}

			(*iter)->vPos +=
				(*iter)->vVelocity * time + (*iter)->vAcceleration * time + (*iter)->vGravity * time;

			(*iter)->vAcceleration += (*iter)->vAcceleration * time;

			(*iter)->fCurrentRadiusSpeed += (*iter)->fRadiusSpeed * time;

			(*iter)->fAge += time;

			if ((*iter)->fAge > (*iter)->fLifeTime)
			{
				*(*iter) = ResetParticle((*iter)->nLoop);
			}
		}
	}
}

void cParticleSystem::PreRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	DWORD b = FtoDw(m_fParticleSize);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, b);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

}

void cParticleSystem::Render()
{
	PreRender();

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PARTICLE::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PARTICLE));

	if (m_nVBOffset >= m_nVBSize)
		m_nVBOffset = 0;

	ST_PARTICLE* pV = NULL;
	m_pVB->Lock(
		m_nVBOffset * sizeof(ST_PARTICLE),
		m_nVBBatchSize * sizeof(ST_PARTICLE),
		(void**)&pV,
		m_nVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	int numParticleInBatch = 0;

	auto iter = m_lAttribute.begin();
	for (; iter != m_lAttribute.end(); iter++)
	{
		if ((*iter)->isAlive && (*iter)->nLoop > 0)
		{
			float rate = (*iter)->fAge / (*iter)->fLifeTime;

			float radius = (*iter)->fStartRadius + (*iter)->fEndRadius * rate;
			D3DXVECTOR3 vRad = D3DXVECTOR3(0, 0, 0);
			vRad.x = cos((*iter)->fCurrentRadiusSpeed) * radius;
			vRad.z = -sin((*iter)->fCurrentRadiusSpeed)* radius;
			pV->p = (*iter)->vPos + vRad;

			D3DXCOLOR currentColor = (*iter)->colorFade - (*iter)->color;
			currentColor *= rate;
			currentColor += (*iter)->color;
			pV->c = D3DCOLOR_ARGB(
				(int)(255 - 255 * rate),
				(int)(currentColor.r * 255),
				(int)(currentColor.g * 255),
				(int)(currentColor.b * 255));

			pV++;

			numParticleInBatch++;

			if (numParticleInBatch == m_nVBBatchSize)
			{
				m_pVB->Unlock();

				g_pD3DDevice->DrawPrimitive(D3DPT_POINTLIST, m_nVBOffset, m_nVBBatchSize);

				m_nVBOffset += m_nVBBatchSize;

				if (m_nVBOffset >= m_nVBSize)
					m_nVBOffset = 0;

				m_pVB->Lock(
					m_nVBOffset * sizeof(ST_PARTICLE),
					m_nVBBatchSize * sizeof(ST_PARTICLE),
					(void**)&pV,
					m_nVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				numParticleInBatch = 0;
			}
		}
	}

	m_pVB->Unlock();

	if (numParticleInBatch)
		g_pD3DDevice->DrawPrimitive(D3DPT_POINTLIST, m_nVBOffset, numParticleInBatch);

	m_nVBOffset += m_nVBBatchSize;

	PostRender();
}

void cParticleSystem::PostRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
}

void cParticleManager::AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, float size, int count, ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var)
{
	if (m_mapParticle.find(keyName) != m_mapParticle.end()) return;
	ST_PARTICLE_INFO info;
	info.fParticleSize = size;
	info.nParticleCount = count;
	info.origAttribute = orig;
	info.varAttribute = var;
	info.pTexture = texture;
	m_mapParticle.insert(make_pair(keyName, info));
}

void cParticleManager::AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, string fullPath)
{
	if (m_mapParticle.find(keyName) != m_mapParticle.end()) return;

	FILE * fp;
	fopen_s(&fp, fullPath.c_str(), "r");

	ST_PARTICLE_ATTRIBUTE orig;
	ST_PARTICLE_ATTRIBUTE_VARIABLE var;
	int count;
	float size;

	ZeroMemory(&orig, sizeof(ST_PARTICLE_ATTRIBUTE));
	ZeroMemory(&var, sizeof(ST_PARTICLE_ATTRIBUTE_VARIABLE));

	char line[256];
	while (true)
	{
		fgets(line, 256, fp);
		if (feof(fp)) break;

		char * context;
		char * tok = strtok_s(line, "\t\n", &context);
		if (strcmp(tok, "A_CNT") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%d", &count);
		}
		if (strcmp(tok, "A_SIZ") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &size);
		}
		if (strcmp(tok, "A_POS") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &orig.vPos.x, &orig.vPos.y, &orig.vPos.z);
		}
		if (strcmp(tok, "A_VEL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &orig.vVelocity.x, &orig.vVelocity.y, &orig.vVelocity.z);
		}
		if (strcmp(tok, "A_ACL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &orig.vAcceleration.x, &orig.vAcceleration.y, &orig.vAcceleration.z);
		}
		if (strcmp(tok, "A_GRV") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f %f %f", &orig.vGravityPos.x, &orig.vGravityPos.y, &orig.vGravityPos.z,
				&orig.fGravityForce, &orig.fGravityRadius);
		}
		if (strcmp(tok, "A_STR") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &orig.fStartRadius);
		}
		if (strcmp(tok, "A_EDR") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &orig.fEndRadius);
		}
		if (strcmp(tok, "A_RSD") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &orig.fRadiusSpeed);
		}
		if (strcmp(tok, "A_LIF") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &orig.fLifeTime);
		}
		if (strcmp(tok, "A_COL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			DWORD temp;
			sscanf_s(tok, "%d", &temp);
			orig.color = D3DXCOLOR(temp);
		}
		if (strcmp(tok, "A_CLF") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			DWORD temp;
			sscanf_s(tok, "%d", &temp);
			orig.colorFade = D3DXCOLOR(temp);
		}
		if (strcmp(tok, "A_LOP") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%d", &orig.nMaxLoop);
		}

		if (strcmp(tok, "V_POS") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &var.vPosVar.x, &var.vPosVar.y, &var.vPosVar.z);
		}
		if (strcmp(tok, "V_VEL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &var.vVelocityVar.x, &var.vVelocityVar.y, &var.vVelocityVar.z);
		}
		if (strcmp(tok, "V_ACL") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f %f %f", &var.vAccelerationVar.x, &var.vAccelerationVar.y, &var.vAccelerationVar.z);
		}
		if (strcmp(tok, "V_STR") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &var.fStartRadiusVar);
		}
		if (strcmp(tok, "V_EDR") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &var.fEndRadiusVar);
		}
		if (strcmp(tok, "V_RSD") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &var.fRadiusSpeedVar);
		}
		if (strcmp(tok, "V_LIF") == 0)
		{
			tok = strtok_s(NULL, "\t\n", &context);
			sscanf_s(tok, "%f", &var.fLifeTimeVar);
		}
	}

	fclose(fp);

	ST_PARTICLE_INFO info;
	info.fParticleSize = size;
	info.nParticleCount = count;
	info.pTexture = texture;
	info.origAttribute = orig;
	info.varAttribute = var;

	m_mapParticle.insert(make_pair(keyName, info));
}

cParticles * cParticleManager::GetParticle(string keyName)
{
	if (m_mapParticle.find(keyName) == m_mapParticle.end())
		return NULL;

	cParticles * particle = new cParticles;
	particle->Setup(&m_mapParticle[keyName]);
	return particle;
}

void cParticleManager::Release()
{
	m_mapParticle.clear();
}

cParticles::cParticles()
	: m_pParticleSystem(NULL)
{
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vRotation = D3DXVECTOR3(0, 0, 0);
	m_vScale = D3DXVECTOR3(1, 1, 1);
}

cParticles::~cParticles()
{
	SAFE_DELETE(m_pParticleSystem);
}

void cParticles::Setup(ST_PARTICLE_INFO * info)
{
	SAFE_DELETE(m_pParticleSystem);
	m_pParticleSystem = new cParticleSystem;
	m_pParticleSystem->Setup(info->pTexture, info->fParticleSize, info->nParticleCount,
		&info->origAttribute, &info->varAttribute);
}

void cParticles::World()
{
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_pParticleSystem->SetWorld(matS * matR * matT);
}
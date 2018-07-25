#pragma once

class cParticleSystem
{
private:
	D3DXMATRIX m_matWorld;

private:
	LPDIRECT3DTEXTURE9			m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

	float		m_fParticleSize;
	int			m_nParticleCount;

	int			m_nVBSize;
	int			m_nVBBatchSize;
	int			m_nVBOffset;

	bool		m_isRegen;
	bool		m_isDie;

	ST_PARTICLE_ATTRIBUTE*			m_pOrigAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE*	m_pVarAttribute;

	list<ST_PARTICLE_ATTRIBUTE*>	m_lAttribute;
public:

	cParticleSystem();
	~cParticleSystem();

	void Setup(LPDIRECT3DTEXTURE9 texture, float size, int count, ST_PARTICLE_ATTRIBUTE* orig, ST_PARTICLE_ATTRIBUTE_VARIABLE* var);

	ST_PARTICLE_ATTRIBUTE ResetParticle(int loop);
	void SetRegen(bool regen) { m_isRegen = regen; }

	void Attribute(ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var);

	void TimeReset();
	void Update();
	void ForceUpdate(int count, float time);
	bool IsDie() { return m_isDie; }

	void PreRender();
	void Render();
	void PostRender();

	DWORD FtoDw(float f) { return *((DWORD*)&f); }

	D3DXMATRIX* GetWorld() { return &m_matWorld; }
	void SetWorld(D3DXMATRIX mat) { m_matWorld = mat; }

};

class cParticles
{
private:
	D3DXVECTOR3 m_vRotation;
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vScale;

private:
	cParticleSystem * m_pParticleSystem;

public:
	cParticles();
	~cParticles();

	void Setup(ST_PARTICLE_INFO* info);
	void World();
	void TimeReset() { m_pParticleSystem->TimeReset(); }
	void Update() { m_pParticleSystem->Update(); }
	void ForceUpdate(int count, float time) { m_pParticleSystem->ForceUpdate(count, time); }
	void Render() { m_pParticleSystem->Render(); }
	void SetRegen(bool regen) { m_pParticleSystem->SetRegen(regen); }
	bool IsDie() { return m_pParticleSystem->IsDie(); }

	D3DXVECTOR3* GetRot() { return &m_vRotation; }
	void SetRot(D3DXVECTOR3 rot) { m_vRotation = rot; }
	D3DXVECTOR3* GetPos() { return &m_vPosition; }
	void SetPos(D3DXVECTOR3 pos) { m_vPosition = pos; }
	D3DXVECTOR3* GetScale() { return &m_vScale; }
	void SetScale(D3DXVECTOR3 scale) { m_vScale = scale; }
};

class cParticleManager
{
	SINGLETONE(cParticleManager);

private:
	map<string, ST_PARTICLE_INFO> m_mapParticle;

public:
	void AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, float size, int count, ST_PARTICLE_ATTRIBUTE orig, ST_PARTICLE_ATTRIBUTE_VARIABLE var);
	void AddParticle(string keyName, LPDIRECT3DTEXTURE9 texture, string fullPath);

	cParticles* GetParticle(string keyName);

	void Release();
};

#define PARTICLE cParticleManager::GetInstance()


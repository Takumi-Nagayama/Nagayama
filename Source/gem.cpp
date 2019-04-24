//=============================================================================
//
// ��Ώ��� [gem.cpp]
// Author : ���R���
//
//=============================================================================
#include "gem.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "coin.h"
#include "particle3D.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GEM_NAME			"data\\MODEL\\gem.x"	// ��΂̃��f����
#define GEM_ROTATION		(0.05f)					// ��΂̉�]�X�s�[�h
#define GEM_PARTICLE_MAX	(3)						// �p�[�e�B�N���̏o���
#define GEM_PARTICLE_COLOR	(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f))	// �p�[�e�B�N���̐F
#define GEM_PARTICLE_SIZE	(10.0f)					// �p�[�e�B�N���̃T�C�Y
#define GEM_PARTICLE_LIFE	(20)					// �p�[�e�B�N���̏o������

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CGem::m_pMesh = NULL;		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CGem::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CGem::m_nNumMat = 0;			// �}�e���A�����̐�
bool CGem::m_bGet = false;			// �l���ł��邩�ǂ���

//=============================================================================
// ��΃N���X�̃R���X�g���N�^
//=============================================================================
CGem::CGem() : CSceneX(GEM_PRIORITY)
{
	// �l���N���A
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGem::~CGem()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CGem *CGem::Create(D3DXVECTOR3 pos)
{
	CGem *pGem = NULL;

	if (pGem == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pGem = new CGem;

		if (pGem != NULL)
		{
			pGem->SetPosition(pos);
			pGem->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pGem->Init();
		}
	}

	return pGem;
}

//=============================================================================
// ��Ώ���������
//=============================================================================
HRESULT CGem::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_GEM);

	// ����������
	CSceneX::Init();

	m_bGet = false;			// �l���ł��邩�ǂ���
	m_bSound = true;

	return S_OK;
}

//=============================================================================
// ��ΏI������
//=============================================================================
void CGem::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// ��΍X�V����
//=============================================================================
void CGem::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���̃��[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	if (CCoin::GetNumCoin() <= 0)
	{// �l���ł����Ԃɂ���
		if (m_bSound == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_TIMEGEM);
			m_bSound = false;
		}
		m_bGet = true;
	}

	// ��]
	m_rot.y += GEM_ROTATION;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	if (CCamera::GetGem() == true)
	{
		for (int nCntParticle = 0; nCntParticle < GEM_PARTICLE_MAX; nCntParticle++)
		{
			CParticle3D::Create(D3DXVECTOR3(CSceneX::GetPosition().x, CSceneX::GetPosition().y - 10.0f, CSceneX::GetPosition().z),
				D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1))),
				GEM_PARTICLE_COLOR,
				GEM_PARTICLE_SIZE,
				GEM_PARTICLE_SIZE,
				GEM_PARTICLE_LIFE,
				CParticle3D::TYPE_UP,
				CParticle3D::TYPE_EFFECT);
		}
	}

	SetRot(m_rot);
}

//=============================================================================
// ��Ε`�揈��
//=============================================================================
void CGem::Draw(void)
{
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�@���̎������K��	�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);


	if (m_bGet == false)
	{
		CSceneX::Draw();

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pMat[nCntMat].MatD3D.Diffuse.a = 0.4f;
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
	else
	{
		CSceneX::Draw();

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}

	// ���_�@���̎������K��	�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// ��΂Ƃ̓����蔻�菈��
//=============================================================================
bool CGem::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// �������Ă��Ȃ����

	if (m_bGet == true)
	{
		// ���S�ƒ��S�̍������߂�
		D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - CSceneX::GetPosition().x, pos->y - CSceneX::GetPosition().y - 20.0f, pos->z - CSceneX::GetPosition().z);

		// ���S���璆�S�̃x�N�g���̒������Z�o
		float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

		if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
		{// ���������a�̘a��菬������Γ������Ă���
			bHit = true;
		}
	}

	return bHit;	// ��΂ɓ������Ă��邩�ǂ�����Ԃ�
}

//=============================================================================
// ��΂̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CGem::LoadModel(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(GEM_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// ��΂̃��f���������
//=============================================================================
void CGem::UnloadModel(void)
{
	// ���b�V���̊J��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̊J��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CGem::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CGem::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �l���ł��邩�ǂ����̎擾
//=============================================================================
bool CGem::GetGem(void)
{
	return m_bGet;
}
//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author : ���R���
//
//=============================================================================
#include "block.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "particle3D.h"
#include "particleX.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCK_NAME	"data\\MODEL\\woodBox.x"	// �u���b�N�̃��f����
#define COUNT_FALL	(20)						// 20�t���[���𒴂��܂ŗ�����
#define SPEED_FALL	(50.0f)						// ������X�s�[�h
#define UNINIT_TIME0	(100)					// ������X�s�[�h
#define UNINIT_TIME1	(90)					// ������T�C��
#define NUM_PARTICLE_X	(100)					// �j��p�[�e�B�N���̐�
#define LIFE_PARTICLE_X	(20)					// �j��p�[�e�B�N���̏o������
#define NUM_PARTICLE_3D	(50)					// ���ŃT�C���p�[�e�B�N���̐�
#define LIFE_PARTICLE_3D	(20)				// ���ŃT�C���p�[�e�B�N���̏o������
#define SIZE_PARTICLE_3D	(5.0f)				// ���ŃT�C���p�[�e�B�N���̃T�C�Y

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CBlock::m_pMesh = NULL;		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CBlock::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CBlock::m_nNumMat = 0;			// �}�e���A�����̐�
LPDIRECT3DTEXTURE9 *CBlock::m_pTexture = 0;			// �e�N�X�`�����

//=============================================================================
// �u���b�N�N���X�̃R���X�g���N�^
//=============================================================================
CBlock::CBlock()
{
	// �l���N���A
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bFall = true;
	m_nCntFall = 0;
	m_State = STATE_NORMAL;
	m_nCntTime = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBlock::~CBlock()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, STATE state)
{
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pBlock = new CBlock;

		if (pBlock != NULL)
		{
			pBlock->SetPosition(pos);
			pBlock->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBlock->BindMat(m_pTexture);
			pBlock->Init();
			pBlock->m_State = state;
		}
	}

	return pBlock;
}

//=============================================================================
// �u���b�N����������
//=============================================================================
HRESULT CBlock::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BLOCK);

	// ����������
	CSceneX::Init();

	m_bFall = true;

	m_nCntFall = 0;

	m_State = STATE_NORMAL;
	m_nCntTime = 0;

	return S_OK;
}

//=============================================================================
// �u���b�N�I������
//=============================================================================
void CBlock::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �u���b�N�X�V����
//=============================================================================
void CBlock::Update(void)
{
	// �Q�[���̃��[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �ʒu���擾
	m_pos = CSceneX::GetPosition();

	if (m_State == STATE_NORMAL)
	{
		StateNormal();
	}
	else if (m_State == STATE_PLAYER)
	{
		StatePlayer();
	}

	SetPosition(m_pos);
}

//=============================================================================
// �u���b�N�`�揈��
//=============================================================================
void CBlock::Draw(void)
{
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	CManager::MODE mode;
	mode = CManager::GetMode();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�@���̎������K��	�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	if (m_State == STATE_PLAYER)
	{
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pMat[nCntMat].MatD3D.Diffuse.a = 0.5f;
		}

		CSceneX::Draw();
	}
	else if(m_State == STATE_NORMAL)
	{
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
		}

		CSceneX::Draw();
	}

	// ���_�@���̎������K��	�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CBlock::CollisionBreak(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// �������Ă��Ȃ����

	// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y - 20.0f, pos->z - m_pos.z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
	{// ���������a�̘a��菬������Γ������Ă���
		if (m_State == STATE_NORMAL)
		{
			bHit = true;
		}
	}

	return bHit;	// �u���b�N�ɓ������Ă��邩�ǂ�����Ԃ�
}

//=============================================================================
// �u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CBlock::LoadModel(void)
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
	D3DXLoadMeshFromX(BLOCK_NAME,
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
// �u���b�N�̃��f���������
//=============================================================================
void CBlock::UnloadModel(void)
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
// �u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CBlock::LoadMat(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �}�e���A���̐����e�N�X�`����������̂𓮓I�Ɋm��
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �����O�ɋ�ɂ���
		m_pTexture[nCntMat] = NULL;

		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �e�N�X�`���̐���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
		}
	}

	return S_OK;
}

//=============================================================================
// �u���b�N�̃��f���������
//=============================================================================
void CBlock::UnloadMat(void)
{
	if (m_pTexture != NULL)
	{// �e�N�X�`���̃|�C���^��NULL�`�F�b�N(��)
		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			if (m_pTexture[nCntMat] != NULL)
			{// �|�C���^�̒���NULL�`�F�b�N(�Ƌ�)
				m_pTexture[nCntMat]->Release();
				m_pTexture[nCntMat] = NULL;
			}
		}

		// �������̊J��(���)
		delete[] m_pTexture;
		// NULL�ɂ���(�X�n)
		m_pTexture = NULL;
	}
}

//=============================================================================
// �ʏ�
//=============================================================================
void CBlock::StateNormal(void)
{
	// �Q�[���̃��[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	if (mode == CManager::MODE_TITLE || mode == CManager::MODE_RANKING)
	{
		if (m_bFall == true)
		{
			m_nCntFall++;
			m_pos.y -= SPEED_FALL;

			if (m_nCntFall > COUNT_FALL)
			{
				m_bFall = false;
				m_nCntFall = 0;
			}
		}
	}
	if (mode == CManager::MODE_GAME || mode == CManager::MODE_TUTORIAL)
	{
		m_nCntTime++;

		if (m_nCntTime / 60 > UNINIT_TIME0)
		{
			for (int nCntParticle = 0; nCntParticle < NUM_PARTICLE_X; nCntParticle++)
			{
				CParticleX::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z),
					D3DXVECTOR3(sinf(D3DX_PI * PARTICLE_ROT), cosf(D3DX_PI * PARTICLE_ROT), cosf(D3DX_PI * PARTICLE_ROT)),
					D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 7 + 1)), cosf(PARTICLE_ROT) * ((rand() % 7 + 1)), cosf(PARTICLE_ROT) * ((rand() % 7 + 1))),
					LIFE_PARTICLE_X,
					CParticleX::TYPE_DOWN);
			}

			Uninit();

			m_nCntTime = 0;
		}

		if (m_nCntTime / 60 > UNINIT_TIME1)
		{
			if ((m_nCntTime % 60) == 0)
			{
				for (int nCntParticle = 0; nCntParticle < NUM_PARTICLE_3D; nCntParticle++)
				{
					CParticle3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z),
						D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1))),
						D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.7f),
						SIZE_PARTICLE_3D,
						SIZE_PARTICLE_3D,
						LIFE_PARTICLE_3D,
						CParticle3D::TYPE_NORMAL,
						CParticle3D::TYPE_EFFECT);
				}
			}
		}
	}
}

//=============================================================================
// �v���C���[
//=============================================================================
void CBlock::StatePlayer(void)
{
	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾(���f���̗D�揇�ʂ�1������A1�ɂ���I�u�W�F�N�g�����ׂČ���)
	pScene = CScene::GetTop(PLAYER_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				m_pos = ((CPlayer*)pScene)->GetBlockPos();
			}
		}
		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CBlock::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CBlock::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �����Ă��邩�ǂ����̎擾
//=============================================================================
bool CBlock::GetFall(void)
{
	return m_bFall;
}

//=============================================================================
// �����Ă��邩�ǂ����̐ݒ�
//=============================================================================
void CBlock::SetFall(bool bFall)
{
	m_bFall = bFall;
}

//=============================================================================
// ��Ԃ̎擾
//=============================================================================
CBlock::STATE CBlock::GetState(void)
{
	return m_State;
}
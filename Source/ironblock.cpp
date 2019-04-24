//=============================================================================
//
// �S�u���b�N���� [block.cpp]
// Author : ���R���
//
//=============================================================================
#include "ironblock.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define IRONBLOCK_NAME	"data\\MODEL\\ironBox.x"	// �S�u���b�N�̃��f����

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CIronBlock::m_pMesh = NULL;		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CIronBlock::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CIronBlock::m_nNumMat = 0;			// �}�e���A�����̐�
LPDIRECT3DTEXTURE9 *CIronBlock::m_pTexture = 0;			// �e�N�X�`�����

//=============================================================================
// �S�u���b�N�N���X�̃R���X�g���N�^
//=============================================================================
CIronBlock::CIronBlock()
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
CIronBlock::~CIronBlock()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CIronBlock *CIronBlock::Create(D3DXVECTOR3 pos)
{
	CIronBlock *pBlock = NULL;

	if (pBlock == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pBlock = new CIronBlock;

		if (pBlock != NULL)
		{
			pBlock->SetPosition(pos);
			pBlock->m_pos = pos;
			pBlock->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBlock->BindMat(m_pTexture);
			pBlock->Init();
		}
	}

	return pBlock;
}

//=============================================================================
// �S�u���b�N����������
//=============================================================================
HRESULT CIronBlock::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_IRONBLOCK);

	// ����������
	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// �S�u���b�N�I������
//=============================================================================
void CIronBlock::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �S�u���b�N�X�V����
//=============================================================================
void CIronBlock::Update(void)
{
}

//=============================================================================
// �S�u���b�N�`�揈��
//=============================================================================
void CIronBlock::Draw(void)
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

	// ���_�@���̎������K��	�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// ���_�@���̎������K��	�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// �S�u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CIronBlock::CollisionBreak(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// �������Ă��Ȃ����

	// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y - 20.0f, pos->z - m_pos.z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float distance = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (distance < fRadius + m_VtxMax.x && distance < fRadius + m_VtxMax.y && distance < fRadius + m_VtxMax.z)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
	}

	return bHit;	// �S�u���b�N�ɓ������Ă��邩�ǂ�����Ԃ�
}

//=============================================================================
// �S�u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CIronBlock::LoadModel(void)
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
	D3DXLoadMeshFromX(IRONBLOCK_NAME,
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
// �S�u���b�N�̃��f���������
//=============================================================================
void CIronBlock::UnloadModel(void)
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
// �S�u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CIronBlock::LoadMat(void)
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
// �S�u���b�N�̃��f���������
//=============================================================================
void CIronBlock::UnloadMat(void)
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
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CIronBlock::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CIronBlock::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
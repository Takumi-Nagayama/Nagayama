//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author : ���R���
//
//=============================================================================
#include "blockPos.h"
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
#define BLOCK_ALPHA		(0.7f)				// �����x
#define BLOCK_ALPHASPEED		(0.01f)				// �����x

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CBlockPos::m_pMesh = NULL;		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CBlockPos::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CBlockPos::m_nNumMat = 0;			// �}�e���A�����̐�
LPDIRECT3DTEXTURE9 *CBlockPos::m_pTexture = 0;			// �e�N�X�`�����

//=============================================================================
// �u���b�N�N���X�̃R���X�g���N�^
//=============================================================================
CBlockPos::CBlockPos() : CSceneX(5)
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
	m_nCntTime = 0;
	m_fAlpha = 0.0f;
	m_fAlphaSpeed = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBlockPos::~CBlockPos()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CBlockPos *CBlockPos::Create(D3DXVECTOR3 pos)
{
	CBlockPos *pBlock = NULL;

	if (pBlock == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pBlock = new CBlockPos;

		if (pBlock != NULL)
		{
			pBlock->SetPosition(pos);
			pBlock->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBlock->BindMat(m_pTexture);
			pBlock->Init();
		}
	}

	return pBlock;
}

//=============================================================================
// �u���b�N����������
//=============================================================================
HRESULT CBlockPos::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BLOCK);

	// ����������
	CSceneX::Init();

	m_bFall = true;

	m_nCntFall = 0;
	m_nCntTime = 0;
	m_fAlpha = BLOCK_ALPHA;
	m_fAlphaSpeed = BLOCK_ALPHASPEED;

	return S_OK;
}

//=============================================================================
// �u���b�N�I������
//=============================================================================
void CBlockPos::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �u���b�N�X�V����
//=============================================================================
void CBlockPos::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���̃��[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �ʒu���擾
	m_pos = CSceneX::GetPosition();

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

	SetPosition(m_pos);

	m_fAlpha -= m_fAlphaSpeed;

	if (m_fAlpha <= 0.2f)
	{
		m_fAlphaSpeed *= -1.0f;
	}
	if (m_fAlpha > BLOCK_ALPHA)
	{
		m_fAlphaSpeed *= -1.0f;
	}
}

//=============================================================================
// �u���b�N�`�揈��
//=============================================================================
void CBlockPos::Draw(void)
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

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pMat[nCntMat].MatD3D.Diffuse.a = m_fAlpha;
	}

	CSceneX::Draw();

	// ���_�@���̎������K��	�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// �u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CBlockPos::LoadModel(void)
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
void CBlockPos::UnloadModel(void)
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
HRESULT CBlockPos::LoadMat(void)
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
void CBlockPos::UnloadMat(void)
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
D3DXVECTOR3 CBlockPos::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CBlockPos::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
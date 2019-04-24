//=============================================================================
//
// ��Q���̏��� [obstacle.cpp]
// Author : ���R���
//
//=============================================================================
#include "obstacle.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "bullet.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBSTACLE_NAME	"data\\MODEL\\obstacle.x"	// ��Q���̃��f����
#define OBSTACLESIZE	(15.0f)					// ��Q���̃T�C�Y

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CObstacle::m_pMesh = NULL;		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CObstacle::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CObstacle::m_nNumMat = 0;			// �}�e���A�����̐�

//=============================================================================
// �v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
CObstacle::CObstacle() : CSceneX(3)
{
	// �l���N���A
	m_pTexture = NULL;						// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObstacle::~CObstacle()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CObstacle *CObstacle::Create(D3DXVECTOR3 pos)
{
	CObstacle *pObstacle = NULL;

	if (pObstacle == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pObstacle = new CObstacle;

		if (pObstacle != NULL)
		{
			pObstacle->SetPosition(pos);
			pObstacle->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pObstacle->Init();
		}
	}

	return pObstacle;
}

//=============================================================================
// ��Q������������
//=============================================================================
HRESULT CObstacle::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_OBSTACLE);

	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// ��Q���I������
//=============================================================================
void CObstacle::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// ��Q���X�V����
//=============================================================================
void CObstacle::Update(void)
{
}

//=============================================================================
// ��Q���`�揈��
//=============================================================================
void CObstacle::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// ��Q���̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CObstacle::LoadObstacle(void)
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
	D3DXLoadMeshFromX(OBSTACLE_NAME,
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
// ��Q���̃��f���������
//=============================================================================
void CObstacle::UnloadObstacle(void)
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
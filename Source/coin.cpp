//=============================================================================
//
// �R�C������ [coin.cpp]
// Author : ���R���
//
//=============================================================================
#include "coin.h"
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
#define COIN_NAME		"data\\MODEL\\coin.x"	// �R�C���̃��f����
#define ROTATION_SPEED	(0.05f)					// �R�C���̉�]�X�s�[�h

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CCoin::m_pMesh = NULL;		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CCoin::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CCoin::m_nNumMat = 0;			// �}�e���A�����̐�
int CCoin::m_nNumCoin = 0;			// �R�C���̐�

//=============================================================================
// �R�C���N���X�̃R���X�g���N�^
//=============================================================================
CCoin::CCoin() : CSceneX(COIN_PRIORITY)
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
CCoin::~CCoin()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CCoin *CCoin::Create(D3DXVECTOR3 pos)
{
	CCoin *pCoin = NULL;

	if (pCoin == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pCoin = new CCoin;

		if (pCoin != NULL)
		{
			pCoin->SetPosition(pos);
			pCoin->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pCoin->Init();

			m_nNumCoin++;
		}
	}

	return pCoin;
}

//=============================================================================
// �R�C������������
//=============================================================================
HRESULT CCoin::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_COIN);

	// ����������
	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// �R�C���I������
//=============================================================================
void CCoin::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �R�C���X�V����
//=============================================================================
void CCoin::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���̃��[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �ʒu���擾
	m_pos = CSceneX::GetPosition();

	m_rot.y += ROTATION_SPEED;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	
	SetRot(m_rot);
	
	SetPosition(m_pos);

#ifdef _DEBUG
	//CDebugProc::Print("cn", "�R�C���̐� : ", m_nNumCoin);
#endif
}

//=============================================================================
// �R�C���`�揈��
//=============================================================================
void CCoin::Draw(void)
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
// �R�C���Ƃ̓����蔻�菈��
//=============================================================================
bool CCoin::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// �������Ă��Ȃ����

	// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - CSceneX::GetPosition().x, pos->y - CSceneX::GetPosition().y - 20.0f, pos->z - CSceneX::GetPosition().z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
	}

	return bHit;	// �R�C���ɓ������Ă��邩�ǂ�����Ԃ�
}

//=============================================================================
// �R�C���̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CCoin::LoadModel(void)
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
	D3DXLoadMeshFromX(COIN_NAME,
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
// �R�C���̃��f���������
//=============================================================================
void CCoin::UnloadModel(void)
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
D3DXVECTOR3 CCoin::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CCoin::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �R�C���̐��̎擾
//=============================================================================
int CCoin::GetNumCoin(void)
{
	return m_nNumCoin;
}

//=============================================================================
// �R�C���̐��̐ݒ�
//=============================================================================
void CCoin::SetNumCoin(int nNumCoin)
{
	m_nNumCoin = nNumCoin;
}
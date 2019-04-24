//=============================================================================
//
// �u���b�N�̏o���ʒu�\������ [blockPos.cpp]
// Author : ���R���
//
//=============================================================================
#include "blockPos.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			"data\\TEXTURE\\woodBox.jpg"	//�e�N�X�`���̃t�@�C����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9	CBlockPos::m_pTexture = NULL;

//--------------------------------------------
// �u���b�N�̏o���ʒu�\���R���X�g���N�^
//--------------------------------------------
CBlockPos::CBlockPos()
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//�ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);		//����
	D3DXMatrixIdentity(&m_mtxWorld);	//���[���h�}�g���b�N�X
}

//--------------------------------------------
// �u���b�N�̏o���ʒu�\���f�X�g���N�^
//--------------------------------------------
CBlockPos::~CBlockPos()
{
}

//=============================================================================
// ��������
//=============================================================================
CBlockPos * CBlockPos::Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV, D3DXCOLOR col)
{
	CBlockPos *pBlockPos = NULL;

	if (pBlockPos == NULL)
	{
		// �n�ʃN���X�̐���
		pBlockPos = new CBlockPos;

		if (pBlockPos != NULL)
		{
			pBlockPos->SetDepth(fDepth);
			pBlockPos->SetWidth(fWifth);
			pBlockPos->SetTextureU(fTextureU);
			pBlockPos->SetTextureV(fTextureV);
			pBlockPos->SetPos(pos);
			pBlockPos->Init();								// ����������
			pBlockPos->SetCol(col);				// ��ނ̐ݒ�
			pBlockPos->BindTexture(m_pTexture);				// ��ނ̐ݒ�
		}
	}
	return pBlockPos;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBlockPos::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CPolygon::Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BLOCKPOS);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBlockPos::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CPolygon::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBlockPos::Update(void)
{
	// �Q�[���̃��[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �ʒu���擾
	m_pos = CPolygon::GetPos();

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


	SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBlockPos::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CPolygon::Draw();
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CBlockPos::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBlockPos::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CBlockPos::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

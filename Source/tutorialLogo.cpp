//=============================================================================
//
// �`���[�g���A���Ŏg�����S�̏��� [tutorialLogo.cpp]
// Author : ���R���
//
//=============================================================================
#include "tutorialLogo.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorialLogo::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// �n�ʂ̐�������
//=============================================================================
CTutorialLogo *CTutorialLogo::Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV, TEX_TYPE type)
{
	CTutorialLogo *pTutorialLogo = NULL;

	if (pTutorialLogo == NULL)
	{
		// �n�ʃN���X�̐���
		pTutorialLogo = new CTutorialLogo;

		if (pTutorialLogo != NULL)
		{
			pTutorialLogo->SetDepth(fDepth);
			pTutorialLogo->SetWidth(fWifth);
			pTutorialLogo->SetTextureU(fTextureU);
			pTutorialLogo->SetTextureV(fTextureV);
			pTutorialLogo->SetPos(pos);
			pTutorialLogo->Init();								// ����������
			pTutorialLogo->SetRot(D3DXVECTOR3(-1.0f,0.0f,0.0f));								// �����̐ݒ�
			pTutorialLogo->BindTexture(m_apTexture[type]);				// ��ނ̐ݒ�
			pTutorialLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));				// ��ނ̐ݒ�
		}
	}
	return pTutorialLogo;
}

//=============================================================================
// �n�ʃN���X�̃R���X�g���N�^
//=============================================================================
CTutorialLogo::CTutorialLogo() : CPolygon(TUTORIALLOGO_PRIORITY)
{
	// �l���N���A
}

//=============================================================================
// �n�ʃN���X�̃f�X�g���N�^
//=============================================================================
CTutorialLogo::~CTutorialLogo()
{
}

//=============================================================================
// �n�ʂ̏���������
//=============================================================================
HRESULT CTutorialLogo::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CPolygon::Init();

	return S_OK;
}

//=============================================================================
// �n�ʂ̏I������
//=============================================================================
void CTutorialLogo::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CPolygon::Uninit();
}

//=============================================================================
// �n�ʂ̍X�V����
//=============================================================================
void CTutorialLogo::Update(void)
{
}

//=============================================================================
// �n�ʂ̕`�揈��
//=============================================================================
void CTutorialLogo::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CPolygon::Draw();
}

//=============================================================================
// �n�ʂ̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CTutorialLogo::Load(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, MOVE_TEXTURE_NAME, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, JUMP_TEXTURE_NAME, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, SET_TEXTURE_NAME, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, DESTROY_TEXTURE_NAME, &m_apTexture[3]);
	D3DXCreateTextureFromFile(pDevice, END_TEXTURE_NAME, &m_apTexture[4]);

	return S_OK;
}

//=============================================================================
// �n�ʂ̃e�N�X�`���������
//=============================================================================
void CTutorialLogo::Unload(void)
{
	for (int nCntTex = 0; nCntTex < TYPE_MAX; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
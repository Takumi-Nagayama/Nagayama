//=============================================================================
//
// �Q�[���I�[�o�[���S�̏��� [gameoverLogo.cpp]
// Author : ���R���
//
//=============================================================================
#include "gameoverLogo.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CGameOverLogo::m_pTexture = NULL;

//=============================================================================
// �Q�[���I�[�o�[���S�̐�������
//=============================================================================
CGameOverLogo *CGameOverLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CGameOverLogo *pGameOverLogo = NULL;

	if (pGameOverLogo == NULL)
	{
		// �Q�[���I�[�o�[���S�N���X�̐���
		pGameOverLogo = new CGameOverLogo;

		if (pGameOverLogo != NULL)
		{
			pGameOverLogo->SetPosition(pos);
			pGameOverLogo->SetWidth(fWidth);
			pGameOverLogo->SetHeight(fHeight);
			pGameOverLogo->Init();
			pGameOverLogo->BindTexture(m_pTexture);
		}
	}

	return pGameOverLogo;
}

//=============================================================================
// �Q�[���I�[�o�[���S�N���X�̃R���X�g���N�^
//=============================================================================
CGameOverLogo::CGameOverLogo() : CLogo(6)
{
	// �l���N���A
}

//=============================================================================
// �Q�[���I�[�o�[���S�N���X�̃f�X�g���N�^
//=============================================================================
CGameOverLogo::~CGameOverLogo()
{
}

//=============================================================================
// �Q�[���I�[�o�[���S����������
//=============================================================================
HRESULT CGameOverLogo::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CLogo::Init();

	CLogo::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �Q�[���I�[�o�[���S�I������
//=============================================================================
void CGameOverLogo::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CLogo::Uninit();
}

//=============================================================================
// �Q�[���I�[�o�[���S�X�V����
//=============================================================================
void CGameOverLogo::Update(void)
{
}

//=============================================================================
// �Q�[���I�[�o�[���S�`�揈��
//=============================================================================
void CGameOverLogo::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CLogo::Draw();
}

//=============================================================================
// �Q�[���I�[�o�[���S�̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CGameOverLogo::Load(void)
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
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_LOGO_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �Q�[���I�[�o�[���S�̃e�N�X�`���������
//=============================================================================
void CGameOverLogo::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
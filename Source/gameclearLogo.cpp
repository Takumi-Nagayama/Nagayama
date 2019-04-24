//=============================================================================
//
// �Q�[���N���A���S�̏��� [tutorialLogo.cpp]
// Author : ���R���
//
//=============================================================================
#include "gameclearLogo.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CGameClearLogo::m_pTexture = NULL;

//=============================================================================
// �Q�[���N���A���S�̐�������
//=============================================================================
CGameClearLogo *CGameClearLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CGameClearLogo *pGameClearLogo = NULL;

	if (pGameClearLogo == NULL)
	{
		// �Q�[���N���A���S�N���X�̐���
		pGameClearLogo = new CGameClearLogo;

		if (pGameClearLogo != NULL)
		{
			pGameClearLogo->SetPosition(pos);
			pGameClearLogo->SetWidth(fWidth);
			pGameClearLogo->SetHeight(fHeight);
			pGameClearLogo->Init();
			pGameClearLogo->BindTexture(m_pTexture);
		}
	}

	return pGameClearLogo;
}

//=============================================================================
// �Q�[���N���A���S�N���X�̃R���X�g���N�^
//=============================================================================
CGameClearLogo::CGameClearLogo() : CLogo(6)
{
	// �l���N���A
}

//=============================================================================
// �Q�[���N���A���S�N���X�̃f�X�g���N�^
//=============================================================================
CGameClearLogo::~CGameClearLogo()
{
}

//=============================================================================
// �Q�[���N���A���S����������
//=============================================================================
HRESULT CGameClearLogo::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CLogo::Init();

	CLogo::SetCol(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �Q�[���N���A���S�I������
//=============================================================================
void CGameClearLogo::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CLogo::Uninit();
}

//=============================================================================
// �Q�[���N���A���S�X�V����
//=============================================================================
void CGameClearLogo::Update(void)
{
}

//=============================================================================
// �Q�[���N���A���S�`�揈��
//=============================================================================
void CGameClearLogo::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CLogo::Draw();
}

//=============================================================================
// �Q�[���N���A���S�̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CGameClearLogo::Load(void)
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
	D3DXCreateTextureFromFile(pDevice, GAMECLEAR_LOGO_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �Q�[���N���A���S�̃e�N�X�`���������
//=============================================================================
void CGameClearLogo::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
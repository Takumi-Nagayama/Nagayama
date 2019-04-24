//=============================================================================
//
// �v���X�G�j�[�{�^���̏��� [pressAnyButton.cpp]
// Author : ���R���
//
//=============================================================================
#include "pressAnyButton.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BUTTON_COLOR		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))
#define BLINK_COUNT			(60)
#define BLINK_COUNT_FAST	(2)

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPressAnyButton::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// �v���X�G�j�[�{�^���̐�������
//=============================================================================
CPressAnyButton *CPressAnyButton::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LOGOTYPE type)
{
	CPressAnyButton *pGameOverLogo = NULL;

	if (pGameOverLogo == NULL)
	{
		// �v���X�G�j�[�{�^���N���X�̐���
		pGameOverLogo = new CPressAnyButton;

		if (pGameOverLogo != NULL)
		{
			pGameOverLogo->SetPosition(pos);
			pGameOverLogo->SetWidth(fWidth);
			pGameOverLogo->SetHeight(fHeight);
			pGameOverLogo->m_type = type;
			pGameOverLogo->Init();
			pGameOverLogo->BindTexture(m_apTexture[type]);
		}
	}

	return pGameOverLogo;
}

//=============================================================================
// �v���X�G�j�[�{�^���N���X�̃R���X�g���N�^
//=============================================================================
CPressAnyButton::CPressAnyButton()
{
	// �l���N���A
	m_nCntEnter = 0;
	m_fEnterTimer = 1.0f;
	m_bPress = false;
	m_type = TYPE_ANY;
}

//=============================================================================
// �v���X�G�j�[�{�^���N���X�̃f�X�g���N�^
//=============================================================================
CPressAnyButton::~CPressAnyButton()
{
}

//=============================================================================
// �v���X�G�j�[�{�^������������
//=============================================================================
HRESULT CPressAnyButton::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CLogo::Init();

	m_nCntEnter = 0;
	m_fEnterTimer = 1.0f;
	m_bPress = false;

	CLogo::SetCol(BUTTON_COLOR);

	return S_OK;
}

//=============================================================================
// �v���X�G�j�[�{�^���I������
//=============================================================================
void CPressAnyButton::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CLogo::Uninit();
}

//=============================================================================
// �v���X�G�j�[�{�^���X�V����
//=============================================================================
void CPressAnyButton::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// �t�F�[�h�̏�Ԃ��擾
	CFade::FADE fade;
	fade = CFade::GetFade();


	m_nCntEnter++;

	int nCount = 0;	// �_�ł̊Ԋu

	if (CFade::GetFade() != CFade::FADE_IN)
	{
		if (m_type == TYPE_ANY)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true
				|| pInputJoypad->GetAnyButton(0) == true)
			{//	�_�ł𑁂�����
				m_bPress = true;
			}
		}
		else if(m_type == TYPE_ENTER)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true
				|| pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
			{//	�_�ł𑁂�����
				m_bPress = true;
			}
		}
	}

	if (m_bPress == false)
	{//	�_�ł����ʂ̎�
		nCount = BLINK_COUNT;
	}
	else
	{// �_�ł������Ƃ�
		nCount = BLINK_COUNT_FAST;
	}

	if (m_nCntEnter >= nCount)
	{
		if (m_fEnterTimer == 1)
		{
			m_fEnterTimer = 0.0f;
		}
		else if (m_fEnterTimer == 0)
		{
			m_fEnterTimer = 1.0f;
		}

		SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer));

		m_nCntEnter = 0;
	}
}

//=============================================================================
// �v���X�G�j�[�{�^���`�揈��
//=============================================================================
void CPressAnyButton::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CLogo::Draw();
}

//=============================================================================
// �v���X�G�j�[�{�^���̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CPressAnyButton::Load(void)
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
	D3DXCreateTextureFromFile(pDevice, BUTTON_LOGO_NAME, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BUTTON_LOGO_NAME01, &m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �v���X�G�j�[�{�^���̃e�N�X�`���������
//=============================================================================
void CPressAnyButton::Unload(void)
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
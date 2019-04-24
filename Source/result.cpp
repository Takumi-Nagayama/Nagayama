//=============================================================================
//
// ���U���g�̏��� [result.cpp]
// Author : ���R���
//
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
//#include "bg.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
//CScore *CResult::m_pScore = 0;
//CRenderer *CResult::m_pRenderer = NULL;

//=============================================================================
// ���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	// �l���N���A
}

//=============================================================================
// ���U���g�̐�������
//=============================================================================
CResult *CResult::Create()
{
	CResult *pResult = NULL;

	if (pResult == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pResult = new CResult;

		if (pResult != NULL)
		{
			pResult->Init();
		}
	}
	return pResult;
}

//=============================================================================
// ���U���g�N���X�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// ���U���g�̏���������
//=============================================================================
HRESULT CResult::Init()
{
	// �w�i�̐���
	//CBg::Load();
	//CBg::Create(0.0005f);

	// ���S�̐���
	//CResultLogo::Load();
	//CResultLogo::Create(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 200.0f, 100.0f);

	int nScore = 0;

	/*if (m_pScore == NULL)
	{
		nScore = CManager::SetScore();

		m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, SCREEN_HEIGHT / 2, 0.0f), 30.0f);
		m_pScore->AddScore(nScore);
	}*/

	return S_OK;
}

//=============================================================================
// ���U���g�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	// �e�N�X�`�������
	//CBg::Unload();			// �w�i
	//CResultLogo::Unload();		// ���S

	//m_pScore = NULL;

	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// ���U���g�̍X�V����
//=============================================================================
void CResult::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �t�F�[�h�擾
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// ���肵���Ƃ���SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			/*CManager::ReleaseScore();*/
			pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		}
	}
}

//=============================================================================
// ���U���g�̕`�揈��
//=============================================================================
void CResult::Draw(void)
{
}
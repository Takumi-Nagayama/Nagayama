//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "camerabace.h"
#include "light.h"
#include "debugproc.h"
#include "result.h"
#include "tutorial.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CSound *CManager::m_pSound = NULL;
CInputKeyBoard *CManager::m_pInputKeyBoard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CInputJoypad *CManager::m_pJoyPad = NULL;
CInputXPad *CManager::m_pXPad = NULL;
//CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CResult *CManager::m_pResult = NULL;
CRanking *CManager::m_pRanking = NULL;
CSelect  *CManager::m_pSelect = NULL;
CTutorial * CManager::m_pTutorial = NULL;
bool CManager::m_bInput = true;

//�Q�[���̈�ԍŏ�
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CManager::CManager()
{}

//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CManager::~CManager()
{}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindows)
{
	//NULL�`�F�b�N
	if (m_pRenderer == NULL)
	{
		//���I�m��
		m_pRenderer = new CRenderer;

		//NULL�`�F�b�N
		if (m_pRenderer != NULL)
		{
			// ����������
			if (FAILED(m_pRenderer->Init(hWnd, bWindows)))		//FALSE.TRUE
			{
				return -1;
			}
		}
		else
		{//�x����
			MessageBox(0, "�x���F���������Ȃ��ł�", "�x��", MB_OK);
		}
	}
	else
	{//�x����
		MessageBox(0, "�x���F�����������Ă܂�", "�x��", MB_OK);
	}

	//�L�[�{�[�h����
	m_pInputKeyBoard = CInputKeyBoard::Create(hInstance, hWnd);

	//�}�E�X����
	m_pInputMouse = CInputMouse::Create(hInstance, hWnd);

	//�W���C�p�b�h����
	m_pJoyPad = CInputJoypad::Create(hInstance, hWnd);

	// XInput�N���X�̐���
	if (m_pXPad == NULL)
	{
		m_pXPad = new CInputXPad;

		if (FAILED(m_pXPad->Init(hInstance, hWnd)))
		{
			m_pXPad->Uninit();			// �I������

			delete m_pXPad;				// �������J��
			m_pXPad = NULL;				// NULL
		}
	}

	//NULL�`�F�b�N
	if (m_pSound == NULL)
	{
		//�T�E���h�̓��I�m��
		m_pSound = new CSound;

		//NULL�`�F�b�N
		if (m_pSound != NULL)
		{
			//�T�E���h�̏���������
			m_pSound->InitSound(hWnd);
		}
	}

	//NULL�`�F�b�N
	//if (m_pCamera == NULL)
	//{
	//	//�J�����̓��I�m��
	//	m_pCamera = new CCamera;

	//	//NULL�`�F�b�N
	//	if (m_pCamera != NULL)
	//	{
	//		//�T�E���h�̏���������
	//		m_pCamera->Init();
	//	}
	//}

	//NULL�`�F�b�N
	if (m_pLight == NULL)
	{
		//���C�g�̓��I�m��
		m_pLight = new CLight;

		//NULL�`�F�b�N
		if (m_pLight != NULL)
		{
			//�T�E���h�̏���������
			m_pLight->Init(hInstance, hWnd);
		}
	}

	//NULL�`�F�b�N
	if (m_pDebugProc == NULL)
	{
		//�f�o�b�N�t�H���g
		m_pDebugProc = new CDebugProc;

		//NULL�`�F�b�N
		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}

	//���[�h�̐ݒ�
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//��ʂ̔j��
	switch (m_mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_TUTORIAL:	//�`���[�g���A��
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:		//�Q�[��
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:	//���U���g
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
	case MODE_RANKING:	// �����L���O
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	case MODE_SELECT:	// �Z���N�g
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();
			delete m_pSelect;
			m_pSelect = NULL;
		}
		break;
	}

	//�S�Ă̍폜
	CScene::ReleseAll();

	//Sound�@NULL�`�F�b�N
	if (m_pSound != NULL)
	{
		//�T�E���h�̏I������
		m_pSound->UninitSound();
		//�������̉��
		delete m_pSound;
		m_pSound = NULL;
	}

	//Renderer NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		//�������̉��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//pCInput NULL�`�F�b�N
	if (m_pInputKeyBoard != NULL)
	{
		// �I������
		m_pInputKeyBoard->Uninit();
		//�������̉��
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}

	//�}�E�XInput�� NULL�`�F�b�N
	if (m_pInputMouse != NULL)
	{
		// �I������
		m_pInputMouse->Uninit();
		//�������̉��
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//�}�E�XInput�� NULL�`�F�b�N
	if (m_pJoyPad != NULL)
	{
		// �I������
		m_pJoyPad->Uninit();
		//�������̉��
		delete m_pJoyPad;
		m_pJoyPad = NULL;
	}

	if (m_pXPad != NULL)
	{// XInput�̔j��
		m_pXPad->Uninit();			// �I������

		delete m_pXPad;				// �������J��
		m_pXPad = NULL;				// NULL
	}

	//�J�����̏I������
	//if(m_pCamera != NULL)
	//{
	//	// �I������
	//	m_pCamera->Uninit();
	//	//�������̉��
	//	delete m_pCamera;
	//	m_pCamera = NULL;
	//}

	//���C�g�̏I������
	if (m_pLight != NULL)
	{
		// �I������
		m_pLight->Uninit();
		//�������̉��
		delete m_pLight;
		m_pLight = NULL;
	}

	//�t�H���g�̏I������
	if (m_pDebugProc != NULL)
	{
		// �I������
		m_pDebugProc->Uninit();
		//�������̉��
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �X�V����
	m_pRenderer->Update();

	// �L�[�{�[�h�X�V����
	m_pInputKeyBoard->Update();

	//�}�E�X�X�V����
	m_pInputMouse->Update();

	//�W���C�p�b�h�X�V����
	m_pJoyPad->Update();

	// XInput�̍X�V����
	if (m_pXPad != NULL)
		m_pXPad->Update();

	//���C�g�̍X�V����
	m_pLight->Update();

	//�J�����̍X�V����
	//m_pCamera->Update();

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�f�o�b�N�p
	//CDebugProc::Print("F1 ���C���[�t���[���@F2�@�ʏ�\n");

	switch (m_mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE_TUTORIAL: //�`���[�g���A��
		if (m_pTutorial != NULL) { m_pTutorial->Update(); }
		break;

	case MODE_GAME:		//�Q�[��
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:	//���U���g
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	case MODE_RANKING:	// �����L���O
		if (m_pRanking != NULL)
		{
			m_pRanking->Update();
		}
		break;
	case MODE_SELECT:	// �Z���N�g
		if (m_pSelect != NULL)
		{
			m_pSelect->Update();
		}
		break;
	}

	//���[�h�̐؂�ւ�莞�A���̒���ReleaseAll���Ă��܂��B
}
//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �`�揈��
	m_pRenderer->Draw();
}
//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL: //�`���[�g���A��
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:		//�Q�[��
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:	//���U���g
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_RANKING:	// �����L���O
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();
			delete m_pSelect;
			m_pSelect = NULL;
		}
		break;
	}

	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle == NULL)
		{//�������𓮓I�m��
			m_pTitle = new CTitle;

			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
				m_pSound->StopSound();
				m_pSound->SetVolume(CSound::SOUND_LABEL_BGM_TITLE, 1.0f);

				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
			}
		}
		break;

	case MODE_TUTORIAL: //�`���[�g���A��
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;

			if (m_pTutorial != NULL)
			{
				m_pTutorial->Init();
				m_pSound->StopSound();
				m_pSound->SetVolume(CSound::SOUND_LABEL_BGM_GAME, 0.5f);
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
			}
		}
		break;

	case MODE_GAME:		//�Q�[��
		if (m_pGame == NULL)
		{//�������𓮓I�m��
			m_pGame = new CGame;

			if (m_pGame != NULL)
			{
				m_pGame->Init();
			}
		}
		break;

	case MODE_RESULT:	//���U���g
		if (m_pResult == NULL)
		{//�������𓮓I�m��
			m_pResult = new CResult;

			if (m_pResult != NULL)
			{
				m_pResult->Init();
				m_pSound->StopSound();
				//m_pSound->SetVolume(CSound::SOUND_LABEL_BGM_RESULT, 0.8f);

				//m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);
			}
		}
		break;
	case MODE_RANKING:	//�����L���O
		if (m_pRanking == NULL)
		{//�������𓮓I�m��
			m_pRanking = new CRanking;

			if (m_pRanking != NULL)
			{
				m_pRanking->Init();
				m_pSound->StopSound();
				//m_pSound->SetVolume(CSound::SOUND_LABEL_BGM_RESULT, 0.8f);

				//m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);
			}
		}
		break;

	case MODE_SELECT:	// �Z���N�g
		if (m_pSelect == NULL)
		{	// �������̓��I�m��
			m_pSelect = new CSelect;

			if (m_pSelect != NULL)
			{
				m_pSelect->Init();
				m_pSound->StopSound();
				//m_pSound->SetVolume(CSound::SOUND_LABEL_BGM_SELECT, 1.1f);
				//m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_SELECT);
			}
		}
	}
}
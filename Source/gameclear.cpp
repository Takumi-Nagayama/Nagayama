//=============================================================================
//
// �Q�[���N���A�̏��� [gameclear.cpp]
// Author : ���R���
//
//=============================================================================
#include "gameclear.h"
#include "manager.h"
#include "renderer.h"
#include "block.h"
#include "input.h"
#include "fade.h"
#include "object.h"
#include "meshCylinder.h"
#include "score.h"
#include "particleX.h"
#include "sound.h"
#include "pressAnyButton.h"
#include "number.h"
#include "text.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CBlock *CGameClear::m_pBlock[MAX_BLOCK] = {};
CScore *CGameClear::m_pScore = NULL;

//=============================================================================
// ���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CGameClear::CGameClear()
{
	// �l���N���A
	m_nCntTimer = 0;

	m_nNumModel = 0;
	m_nBlockTimer = 0;
	m_nCntBlock = 0;
	m_bSetBlock = true;
	for (int nCntBlock = 0; nCntBlock < 1000; nCntBlock++)
	{
		m_BlockPpos[nCntBlock] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// ���U���g�̐�������
//=============================================================================
CGameClear *CGameClear::Create()
{
	CGameClear *pResult = NULL;

	if (pResult == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pResult = new CGameClear;

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
CGameClear::~CGameClear()
{
}

//=============================================================================
// ���U���g�̏���������
//=============================================================================
HRESULT CGameClear::Init(void)
{
	// �l�̏�����
	m_nCntTimer = 0;

	m_nNumModel = 0;
	m_nBlockTimer = 0;
	m_bSetBlock = true;
	m_nCntBlock = 0;

	// �u���b�N�̃��f���̓ǂݍ���
	CBlock::LoadModel();
	CBlock::LoadMat();

	// �p�[�e�B�N���̃��f���̃��[�h
	CParticleX::LoadModel();
	CParticleX::LoadMat();

	CPressAnyButton::Load();
	// �e�N�X�`���̉��
	CNumber::Load();


	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), 200.0f, 170.0f, CPressAnyButton::TYPE_ANY);

	if (m_pScore == NULL)
	{
		int nScore = 0;

		nScore = CManager::SetScore();

		m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 280.0f, SCREEN_HEIGHT / 2 + 70.0f, 0.0f), 70.0f, 120.0f);
		m_pScore->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_pScore->AddScore(nScore);
	}

	int nCnt = 0;

	for (int nCntCharX = 0; nCntCharX < NUM_BLOCK_X; nCntCharX++)
	{
		for (int nCntCharY = 0; nCntCharY < NUM_BLOCK_Y; nCntCharY++)
		{
			m_pBlock[nCnt] = CBlock::Create(D3DXVECTOR3(-440.0f + 50.0f * nCntCharX, 50.0f * nCntCharY, -450.0f), CBlock::STATE_NORMAL);

			nCnt++;
		}
	}

	LoadCharFall();

	// ���b�V���V�����_�[�̐���
	CMeshCylinder::Create(D3DXVECTOR3(700.0f, 1700.0f, 0.0f), 2000.0, 30.0f);

	return S_OK;
}

//=============================================================================
// ���U���g�̏I������
//=============================================================================
void CGameClear::Uninit(void)
{
	CBlock::UnloadModel();		// �u���b�N
	CBlock::UnloadMat();

	// �p�[�e�B�N��
	CParticleX::UnloadModel();
	CParticleX::UnloadMat();

	// �e�N�X�`���̉��
	CNumber::UnLoad();

	CPressAnyButton::Unload();

	m_pScore = NULL;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK + 1 ; nCntBlock++)
	{
		m_pBlock[nCntBlock] = NULL;
	}

	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// ���U���g�̍X�V����
//=============================================================================
void CGameClear::Update(void)
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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true || pInputJoypad->GetAnyButton(0) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// ���肵���Ƃ���SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			CManager::ReleaseScore();
			pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		}
	}

	// �f�o�b�N�p
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_TITLE, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAMECLEAR, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_5) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAMEOVER, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_6) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		}
	}

	m_nCntTimer++;

	if (m_nCntTimer >= 600)
	{
		pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		m_nCntTimer = 0;
	}

	if (m_bSetBlock == true)
	{
		m_nBlockTimer++;

		if (m_nBlockTimer > 1)
		{
			if (m_nCntBlock < NUM_BLOCK_X * NUM_BLOCK_Y)
			{
				if (m_nCntBlock % 10 == 0)
				{
					pSound->PlaySound(CSound::SOUND_LABEL_SE_BREAK);
				}
				for (int nCntParticle = 0; nCntParticle < 10; nCntParticle++)
				{
					CParticleX::Create(D3DXVECTOR3(m_pBlock[m_nCntBlock]->GetPosition().x, m_pBlock[m_nCntBlock]->GetPosition().y + 30.0f, m_pBlock[m_nCntBlock]->GetPosition().z),
						D3DXVECTOR3(sinf(D3DX_PI * (rand() % 628) / 100.0f), cosf(D3DX_PI * (rand() % 628) / 100.0f), cosf(D3DX_PI * (rand() % 618) / 100.0f)),
						D3DXVECTOR3(sinf((rand() % 628) / 100.0f) * ((rand() % 7 + 1)), cosf((rand() % 628) / 100.0f) * ((rand() % 7 + 1)), cosf((rand() % 618) / 100.0f) * ((rand() % 7 + 1))),
						100,
						CParticleX::TYPE_DOWN);
				}

				if (m_pBlock[m_nCntBlock] != NULL)
				{
					m_pBlock[m_nCntBlock]->Uninit();
					m_pBlock[m_nCntBlock] = NULL;
				}
				if (m_pBlock[m_nCntBlock + 1] != NULL)
				{
					m_pBlock[m_nCntBlock + 1]->Uninit();
					m_pBlock[m_nCntBlock + 1] = NULL;
				}

				m_nCntBlock += 2;
				m_nBlockTimer = 0;
			}
		}
		if (m_nCntBlock >= NUM_BLOCK_X * NUM_BLOCK_Y)
		{
			m_bSetBlock = false;
		}
	}
}

//=============================================================================
// ���U���g�̕`�揈��
//=============================================================================
void CGameClear::Draw(void)
{
}

//=============================================================================
// ���f���̃��[�h
//=============================================================================
void CGameClear::LoadCharFall()
{
	FILE *pFile = NULL;

	CManager::MODE mode;
	mode = CManager::GetMode();

	CText *pText;
	pText = CManager::GetText();

	int nCharType = 0;

	pFile = fopen(OBJECT_FILE_GAMECLEAR, "r");

	if (pFile != NULL)
	{
		char *pStrCur;		// ������̐擪�ւ̃|�C���^
		char aLine[256];	// ������ǂݍ��ݗp�i1�s���j
		char aStr[256];		// �����񔲂��o���p

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
		pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
		strcpy(&aStr[0], pStrCur);

		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			while (1)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
				pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
				strcpy(&aStr[0], pStrCur);


				if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
				{
					pStrCur += strlen("NUM_MODEL =");	// ���o��

					m_nNumModel = atoi(pStrCur);	// �������l�ɕϊ�


					for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
						strcpy(&aStr[0], pStrCur);

						D3DXVECTOR3 pos;
						D3DXVECTOR3 rot;

						if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
						{// �ʒu
							pStrCur += strlen("POS =");	// ���o��
							int nWord;

							// float�ɕϊ����đ��
							pos.x = (float)atof(pStrCur);

							// aStr[0]�ɉ����������Ă��邩���m���߂�
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// ���܂Ői�߂�
							pStrCur += nWord;

							// float�ɕϊ����đ��
							pos.y = (float)atof(pStrCur);

							// aStr[0]�ɉ����������Ă��邩���m���߂�
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// ���܂Ői�߂�
							pStrCur += nWord;

							// float�ɕϊ����đ��
							pos.z = (float)atof(pStrCur);
						}

						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
						strcpy(&aStr[0], pStrCur);

						if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
						{// �ʒu
							pStrCur += strlen("ROT =");	// ���o��

							int nWord;

							// float�ɕϊ����đ��
							rot.x = (float)atof(pStrCur);

							// aStr[0]�ɉ����������Ă��邩���m���߂�
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// ���܂Ői�߂�
							pStrCur += nWord;

							// float�ɕϊ����đ��
							rot.y = (float)atof(pStrCur);

							// aStr[0]�ɉ����������Ă��邩���m���߂�
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// ���܂Ői�߂�
							pStrCur += nWord;

							// float�ɕϊ����đ��
							rot.z = (float)atof(pStrCur);
						}

						// �ʒu������Ă���
						m_BlockPpos[nCntModel] = pos;

						// �u���b�N����
						CBlock::Create(D3DXVECTOR3(m_BlockPpos[nCntModel].x - 440.0f, m_BlockPpos[nCntModel].y, m_BlockPpos[nCntModel].z - 450.0f), CBlock::STATE_NORMAL);
					}
				}

				if (memcmp(&aStr[0], "ENDSCRIPT", strlen("ENDSCRIPT")) == 0)
				{
					break;
				}
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : ���R���
//
//=============================================================================
#include "tutorial.h"
#include "tutorialLogo.h"
#include "main.h"
#include "player.h"
#include "scene2D.h"
#include "input.h"
#include "fade.h"
#include "meshCylinder.h"
#include "manager.h"
#include "field.h"
#include "block.h"
#include "score.h"
#include "numBlock.h"
#include "particle2D.h"
#include "particle3D.h"
#include "particleX.h"
#include "logoBack.h"
#include "scoreLogo.h"
#include "blockLogo.h"
#include "blockCross.h"
#include "goal.h"
#include "object.h"
#include "ironBlock.h"
#include "woodBlock.h"
#include "hole.h"
#include "gem.h"
#include "pressAnyButton.h"
#include "sound.h"
#include "number.h"
#include "playerCross.h"
#include "lifeLogo.h"
#include "life.h"
#include "blockPos.h"
#include "text.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScore *CTutorial::m_pScore = NULL;
CNumBlock *CTutorial::m_pNumBlock = NULL;
CLife *CTutorial::m_pLife = NULL;

//=============================================================================
// �`���[�g���A���̐�������
//=============================================================================
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;

	if (pTutorial == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pTutorial = new CTutorial;

		if (pTutorial != NULL)
		{
			pTutorial->Init();
		}
	}

	return pTutorial;
}

//=============================================================================
// �`���[�g���A���̃R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
// �`���[�g���A���̃f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// �Q�[������������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	// �e�N�X�`����ǂݍ���
	// �n�ʃe�N�X�`��
	CFeild::Load();
	CHole::Load();
	// �p�[�e�B�N��
	CParticle2D::Load();
	CParticle3D::Load();
	// �w�i���S
	CLogoBack::Load();
	// �X�R�A���S
	CScoreLogo::Load();
	// �u���b�N���S
	CBlockLogo::Load();
	// �c�@���S
	CLifeLogo::Load();
	// �u���b�N�̌����S
	CBlockCross::Load();
	// �v���C���[�̎c�@���S
	CPlayerCross::Load();
	// �`���[�g���A���̃��S
	CTutorialLogo::Load();
	// �e�N�X�`���̃��[�h
	CNumber::Load();
	// �u���b�N�o���ʒu
	CBlockPos::LoadModel();
	CBlockPos::LoadMat();

	// ���f����ǂݍ���
	// �u���b�N�̃��f���̓ǂݍ���
	CBlock::LoadModel();
	CBlock::LoadMat();
	CIronBlock::LoadModel();
	CIronBlock::LoadMat();
	CWoodBlock::LoadModel();
	CWoodBlock::LoadMat();
	// �p�[�e�B�N���̃��f���̃��[�h
	CParticleX::LoadModel();
	CParticleX::LoadMat();
	// �S�[���̃��f���̓ǂݍ���
	CGoal::LoadModel();
	CPressAnyButton::Load();

	// �v���C���[�̐���
	CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 220.0f));

	// �`���[�g���A�����S
	CTutorialLogo::Create(D3DXVECTOR3(100.0f, 50.0f, 280.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_MOVE);
	CTutorialLogo::Create(D3DXVECTOR3(-100.0f, 50.0f, 500.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_JUMP);
	CTutorialLogo::Create(D3DXVECTOR3(100.0f, 50.0f, 850.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_SET);
	CTutorialLogo::Create(D3DXVECTOR3(-100.0f, 50.0f, 1300.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_DESTROY);
	CTutorialLogo::Create(D3DXVECTOR3(0.0f, 50.0f, 1650.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_END);

	// �}�b�v�̃��[�h
	CObject *pObject = NULL;
	pObject->LoadFile(1);
	LoadIronBlock();			// �S�u���b�N
	LoadWoodBlock();			// �؃u���b�N

	if (m_pScore == NULL)
	{
		// �X�R�A�̐���
		m_pScore = CScore::Create(D3DXVECTOR3(800.0f, 70.0f, 0.0f), 37.0f, 60.0f);
	}

	if (m_pNumBlock == NULL)
	{
		// �u���b�N�̐��̐���
		m_pNumBlock = CNumBlock::Create(D3DXVECTOR3(1170.0f, 70.0f, 0.0f), 37.0f);
	}

	if (m_pLife == NULL)
	{
		// �u���b�N�̐��̐���
		m_pLife = CLife::Create(D3DXVECTOR3(260.0f, 75.0f, 0.0f), 40.0f);
	}

	// �v���C���[�̎c�@���S�̐���
	CPlayerCross::Create(D3DXVECTOR3(150.0f, 70.0f, 0.0f), 70.0f, 50.0f);

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 650.0f, 0.0f), 150.0f, 100.0f, CPressAnyButton::TYPE_ENTER);

	// ���b�V���V�����_�[�̐���
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 1500.0f, 0.0f), 3000.0f, 30.0f);

	// ���|���S���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 1600.0f), 1000.0f, 4000.0f, 40.0f, 10.0f);
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 220.0f), 300.0f, 4000.0f, 20.0f, 1.0f);
	CHole::Create(D3DXVECTOR3(1200.0f, -0.5f, 600.0f), 3000.0f, 3000.0f);

	// �u���b�N�̌����S�̐���
	CBlockCross::Create(D3DXVECTOR3(1030.0f, 70.0f, 0.0f), 50.0f, 30.0f);

	// �S�[���̐���
	CGoal::Create(D3DXVECTOR3(0.0f, 0.0f, 1800.0f));

	// ��
	CScene3D::Create(D3DXVECTOR3(0.0f, 0.0f, 700.0f), 1000.0f, 1000.0f, 80.0f, 80.0f);

	// �w�i���S�̐���
	CLogoBack::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 10.0f, 50.0f, 0.0f), 190.0f, 60.0f);
	CLogoBack::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450.0f, 50.0f, 0.0f), 130.0f, 60.0f);
	CScoreLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 10.0f, 25.0f, 0.0f), 80.0f, 30.0f);
	CBlockLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450.0f, 25.0f, 0.0f), 80.0f, 30.0f);
	CLifeLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450.0f, 20.0f, 0.0f), 70.0f, 20.0f);
	CLogoBack::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450.0f, 50.0f, 0.0f), 130.0f, 60.0f);

	return S_OK;
}

//=============================================================================
// �`���[�g���A���I������
//=============================================================================
void CTutorial::Uninit(void)
{
	// ���f���̉��
	CBlock::UnloadModel();		// �u���b�N
	CBlock::UnloadMat();
	CIronBlock::UnloadModel();		// �S�u���b�N
	CIronBlock::UnloadMat();
	CWoodBlock::UnloadModel();		// �؃u���b�N
	CWoodBlock::UnloadMat();
	CBlockPos::UnloadModel();		// �u���b�N�o���ʒu
	CBlockPos::UnloadMat();

	// �p�[�e�B�N��
	CParticleX::UnloadModel();
	CParticleX::UnloadMat();
	CGoal::UnloadModel();		// �S�[��
	
	// �e�N�X�`���̉��
	CFeild::Unload();			// �n�ʃe�N�X�`��
	CHole::Unload();
	CTutorialLogo::Unload();	// �`���[�g���A�����S
	CParticle2D::Unload();		// 2D�p�[�e�B�N��
	CParticle3D::Unload();		// 3D�p�[�e�B�N��
	CLogoBack::Unload();		// �w�i���S
	CScoreLogo::Unload();		// �X�R�A���S
	CBlockLogo::Unload();		// �u���b�N���S
	CBlockCross::Unload();		// �u���b�N�̌����S
	CPlayerCross::Unload();		// �v���C���[�̎c�@���S
	CPressAnyButton::Unload();
	CLifeLogo::Unload();			// �c�@���S

	// �e�N�X�`���̉��
	CNumber::UnLoad();

	// ������ɂ���
	m_pScore = NULL;
	m_pNumBlock = NULL;
	m_pLife = NULL;

	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// �`���[�g���A���X�V����
//=============================================================================
void CTutorial::Update(void)
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

	if (CPlayer::GetGoal() == true)
	{// �S�[��������
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �Q�[���ɑJ��
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
	else if (CPlayer::GetGameOver() == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �Q�[���I�[�o�[�ɑJ��
			pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// ���肵���Ƃ���SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			// �t�F�[�h�����擾
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
}

//=============================================================================
// �`���[�g���A���`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}

//=============================================================================
// ���f���̃��[�h
//=============================================================================
void CTutorial::LoadIronBlock()
{
	FILE *pFile = NULL;

	CManager::MODE mode;
	mode = CManager::GetMode();

	CText *pText;
	pText = CManager::GetText();

	int nNumModel = 0;

	pFile = fopen(IRON_FILE_GAME, "r");

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

					nNumModel = atoi(pStrCur);	// �������l�ɕϊ�
				}

				if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
				{
					for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
						strcpy(&aStr[0], pStrCur);

						int nCntTimer = 0;

						if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
						{
							pStrCur += strlen("ModelType");	// ���o��

							int nType = atoi(pStrCur);	// �������l�ɕϊ�

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

							// ����
							CIronBlock::Create(pos);
						}
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

//=============================================================================
// ���f���̃��[�h
//=============================================================================
void CTutorial::LoadWoodBlock()
{
	FILE *pFile = NULL;

	CManager::MODE mode;
	mode = CManager::GetMode();

	CText *pText;
	pText = CManager::GetText();

	int nNumModel = 0;

	pFile = fopen(WOOD_FILE_GAME, "r");

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

					nNumModel = atoi(pStrCur);	// �������l�ɕϊ�
				}

				if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
				{
					for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
						strcpy(&aStr[0], pStrCur);

						int nCntTimer = 0;

						if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
						{
							pStrCur += strlen("ModelType");	// ���o��

							int nType = atoi(pStrCur);	// �������l�ɕϊ�

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

							// ����
							CWoodBlock::Create(pos);
						}
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

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore *CTutorial::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �u���b�N�̐��̎擾
//=============================================================================
CNumBlock *CTutorial::GetNumBlock(void)
{
	return m_pNumBlock;
}

//=============================================================================
// �c�@�̎擾
//=============================================================================
CLife *CTutorial::GetLife(void)
{
	return m_pLife;
}
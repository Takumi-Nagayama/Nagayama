//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : ���R���
//
//=============================================================================
#include "game.h"
#include "manager.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "billboard.h"
#include "input.h"
#include "debugProc.h"
#include "player.h"
#include "scene.h"
#include "meshField.h"
#include "meshCylinder.h"
#include "fade.h"
#include "block.h"
#include "goal.h"
#include "pause.h"
#include "score.h"
#include "particle2D.h"
#include "particle3D.h"
#include "particleX.h"
#include "object.h"
#include "logoBack.h"
#include "numBlock.h"
#include "scoreLogo.h"
#include "blockLogo.h"
#include "lifeLogo.h"
#include "blockCross.h"
#include "playerCross.h"
#include "polygon.h"
#include "hole.h"
#include "coin.h"
#include "gem.h"
#include "field.h"
#include "woodblock.h"
#include "ironblock.h"
#include "pebble.h"
#include "number.h"
#include "life.h"
#include "blockPos.h"
#include "text.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COIN_FILE_GAME	"data\\TEXT\\modelCoin.txt"			// �ݒu�������f���������o���e�L�X�g
#define SCORE_POS		(D3DXVECTOR3(800.0f, 70.0f, 0.0f))	// �X�R�A�̈ʒu
#define SCORE_HEIGHT	(37.0f)								// �X�R�A�̃T�C�Y
#define SCORE_WIDTH		(60.0f)								// �X�R�A�̃T�C�Y
#define NUMBLOCK_POS	(D3DXVECTOR3(1170.0f, 70.0f, 0.0f))	// �u���b�N�̌��̈ʒu
#define NUMBLOCK_SIZE	(37.0f)								// �u���b�N�̌��̃T�C�Y
#define NUMCOIN_POS	(D3DXVECTOR3(1170.0f, 200.0f, 0.0f))	// �R�C���̌��̈ʒu
#define NUMCOIN_SIZE	(37.0f)								// �R�C���̌��̃T�C�Y
#define NUMBLOCKLOGO_POS	(D3DXVECTOR3(1030.0f, 70.0f, 0.0f))	// �u���b�N�̌����S�̈ʒu
#define NUMBLOCKLOGO_WIDTH	(50.0f)								// �u���b�N�̌����S�̃T�C�Y
#define NUMBLOCKLOGO_HEIGHT	(30.0f)								// �u���b�N�̌����S�̃T�C�Y
#define LIFE_POS		(D3DXVECTOR3(260.0f, 75.0f, 0.0f))	// ���C�t�̈ʒu
#define LIFE_SIZE		(40.0f)								// ���C�t�̃T�C�Y
#define PLAYERCROSS_POS	(D3DXVECTOR3(150.0f, 70.0f, 0.0f))	// �c�@���S�̈ʒu
#define PLAYERCROSS_WIDTH	(70.0f)							// �c�@���S�̃T�C�Y
#define PLAYERCROSS_HEIGHT	(50.0f)							// �c�@���S�̃T�C�Y

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScore *CGame::m_pScore = NULL;
CNumBlock *CGame::m_pNumBlock = NULL;
CLife *CGame::m_pLife = NULL;

//=============================================================================
// �Q�[���N���X�̃R���X�g���N�^
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// �Q�[���̐�������
//=============================================================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pGame = new CGame;

		if (pGame != NULL)
		{
			pGame->Init();
		}
	}

	return pGame;
}

//=============================================================================
// �Q�[������������
//=============================================================================
HRESULT CGame::Init(void)
{
	LoadTexture();
	LoadModel();
	LoadMat();

	// �R�C������
	LoadCoin();

	// �v���C���[�̐���
	CPlayer::Create(D3DXVECTOR3(80.0f, 50.0f, 250.0f));

	// ��΂̐���
	CGem::Create(D3DXVECTOR3(1160.0f, 0.0f, 720.0f));

	// �}�b�v�̃��[�h
	CObject *pObject = NULL;
	pObject->LoadFile(0);

	BlockCreate();
	FieldCreate();

	if (m_pScore == NULL)
	{
		// �X�R�A�̐���
		m_pScore = CScore::Create(SCORE_POS, SCORE_HEIGHT, SCORE_WIDTH);
	}

	if (m_pNumBlock == NULL)
	{
		// �u���b�N�̐��̐���
		m_pNumBlock = CNumBlock::Create(NUMBLOCK_POS, NUMBLOCK_SIZE);
	}

	if (m_pLife == NULL)
	{
		// ���C�t�̐���
		m_pLife = CLife::Create(LIFE_POS, LIFE_SIZE);
	}

	// �v���C���[�̎c�@���S�̐���
	CPlayerCross::Create(PLAYERCROSS_POS, PLAYERCROSS_WIDTH, PLAYERCROSS_HEIGHT);

	// �u���b�N�̌����S�̐���
	CBlockCross::Create(NUMBLOCKLOGO_POS, NUMBLOCKLOGO_WIDTH, NUMBLOCKLOGO_HEIGHT);

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
// �Q�[���I������
//=============================================================================
void CGame::Uninit(void)
{
	CCoin::SetNumCoin(0);

	// ���f���̉��
	UnLoadModel();
	
	// �e�N�X�`���̉��
	UnLoadTexture();

	// �}�e���A���̉��
	UnLoadMat();

	// ������ɂ���
	m_pScore = NULL;
	m_pNumBlock = NULL;
	m_pLife = NULL;
	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// �Q�[���X�V����
//=============================================================================
void CGame::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �t�F�[�h�擾
	CFade *pFade = CManager::GetFade();

	if (CPlayer::GetGoal() == true)
	{// �S�[��������
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �Q�[���N���A�ɑJ��
			CManager::GetRankingScore(m_pScore->GetScore());
			CManager::GetScore(m_pScore->GetScore());

			pFade->SetFade(CManager::MODE_GAMECLEAR, CFade::FADE_OUT);
		}
	}
	else if (CPlayer::GetGameOver() == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �Q�[���I�[�o�[�ɑJ��
			CManager::GetRankingScore(m_pScore->GetScore());
			CManager::GetScore(m_pScore->GetScore());
			pFade->SetFade(CManager::MODE_GAMEOVER, CFade::FADE_OUT);
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
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �u���b�N�̐��̎擾
//=============================================================================
CNumBlock *CGame::GetNumBlock(void)
{
	return m_pNumBlock;
}

//=============================================================================
// �c�@�̎擾
//=============================================================================
CLife *CGame::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// ���f���̃��[�h
//=============================================================================
void CGame::LoadCoin()
{
	FILE *pFile = NULL;

	CManager::MODE mode;
	mode = CManager::GetMode();

	CText *pText;
	pText = CManager::GetText();

	int nNumModel = 0;

	pFile = fopen(COIN_FILE_GAME, "r");

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

							// �R�C������
							CCoin::Create(pos);
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

	// �R�C������
	CCoin::Create(D3DXVECTOR3(450.0f, 65.0f, 1240.0f));
	CCoin::Create(D3DXVECTOR3(880.0f, 130.0f, 1300.0f));
	CCoin::Create(D3DXVECTOR3(880.0f, 130.0f, 1250.0f));
	CCoin::Create(D3DXVECTOR3(880.0f, 130.0f, 1350.0f));

	CCoin::Create(D3DXVECTOR3(450.0f, 150.0f, 120.0f));
	CCoin::Create(D3DXVECTOR3(400.0f, 150.0f, 120.0f));
	CCoin::Create(D3DXVECTOR3(500.0f, 150.0f, 120.0f));
	CCoin::Create(D3DXVECTOR3(430.0f, 150.0f, 280.0f));
	CCoin::Create(D3DXVECTOR3(480.0f, 150.0f, 280.0f));
	CCoin::Create(D3DXVECTOR3(250.0f, 20.0f, 430.0f));
	CCoin::Create(D3DXVECTOR3(250.0f, 20.0f, 400.0f));
	CCoin::Create(D3DXVECTOR3(250.0f, 20.0f, 460.0f));
	CCoin::Create(D3DXVECTOR3(70.0f, 10.0f, 400.0f));
	CCoin::Create(D3DXVECTOR3(70.0f, 10.0f, 500.0f));
}

//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
void CGame::LoadTexture()
{
	// �e�N�X�`����ǂݍ���
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
	// �n�ʃe�N�X�`��
	CHole::Load();
	CFeild::Load();
	// �e�N�X�`���̉��
	CNumber::Load();
}

//=============================================================================
// �e�N�X�`���̊J��
//=============================================================================
void CGame::UnLoadTexture()
{
	CParticle2D::Unload();		// 2D�p�[�e�B�N��
	CParticle3D::Unload();		// 3D�p�[�e�B�N��
	CLogoBack::Unload();		// �w�i���S
	CScoreLogo::Unload();		// �X�R�A���S
	CBlockLogo::Unload();		// �u���b�N���S
	CLifeLogo::Unload();			// �c�@���S
	CBlockCross::Unload();		// �u���b�N�̌����S
	CPlayerCross::Unload();		// �v���C���[�̎c�@���S
	CHole::Unload();				// �n�ʃe�N�X�`��
	CFeild::Unload();
	CNumber::UnLoad();			// �e�N�X�`���̉��
}

//=============================================================================
// ���f���̃��[�h
//=============================================================================
void CGame::LoadModel()
{
	CBlock::LoadModel();
	CWoodBlock::LoadModel();
	CIronBlock::LoadModel();
	CBlockPos::LoadModel();
	CParticleX::LoadModel();
	CCoin::LoadModel();
	CGem::LoadModel();
	CPebble::LoadModel();
	CGoal::LoadModel();
}

//=============================================================================
// ���f���̊J��
//=============================================================================
void CGame::UnLoadModel()
{
	CBlock::UnloadModel();		// �u���b�N
	CGoal::UnloadModel();		// �S�[��
	CObject::UnloadModel();			// �w�i�I�u�W�F�N�g
	CCoin::UnloadModel();				// �R�C��
	CGem::UnloadModel();				// ���
	CWoodBlock::UnloadModel();		// �؃u���b�N
	CIronBlock::UnloadModel();		// �؃u���b�N
	CBlockPos::UnloadModel();		// �u���b�N�o���ʒu
	CPebble::UnloadModel();			// ���΂̃��f��
	CParticleX::UnloadModel();
}

//=============================================================================
// �}�e���A���̃��[�h
//=============================================================================
void CGame::LoadMat()
{
	CBlock::LoadMat();
	CWoodBlock::LoadMat();
	CIronBlock::LoadMat();
	CBlockPos::LoadMat();
	CParticleX::LoadMat();
}

//=============================================================================
// �}�e���A���̊J��
//=============================================================================
void CGame::UnLoadMat()
{
	CWoodBlock::UnloadMat();
	CIronBlock::UnloadMat();
	CBlockPos::UnloadMat();
	CParticleX::UnloadMat();
	CBlock::UnloadMat();
}

//=============================================================================
// �u���b�N�̐���
//=============================================================================
void CGame::BlockCreate()
{
	// �؂̃u���b�N����
	CWoodBlock::Create(D3DXVECTOR3(250.0f, 0.0f, 430.0f));
	CWoodBlock::Create(D3DXVECTOR3(1000.0f, 0.0f, 280.0f));
	CWoodBlock::Create(D3DXVECTOR3(1000.0f, 0.0f, 160.0f));

	// �S�u���b�N����
	CIronBlock::Create(D3DXVECTOR3(830.0f, 0.0f, 1250.0f));
	CIronBlock::Create(D3DXVECTOR3(830.0f, 0.0f, 1300.0f));
	CIronBlock::Create(D3DXVECTOR3(830.0f, 0.0f, 1350.0f));
	CIronBlock::Create(D3DXVECTOR3(880.0f, 0.0f, 1250.0f));
	CIronBlock::Create(D3DXVECTOR3(880.0f, 0.0f, 1300.0f));
	CIronBlock::Create(D3DXVECTOR3(880.0f, 0.0f, 1350.0f));
	CIronBlock::Create(D3DXVECTOR3(830.0f, 50.0f, 1250.0f));
	CIronBlock::Create(D3DXVECTOR3(830.0f, 50.0f, 1300.0f));
	CIronBlock::Create(D3DXVECTOR3(830.0f, 50.0f, 1350.0f));
	CIronBlock::Create(D3DXVECTOR3(880.0f, 50.0f, 1250.0f));
	CIronBlock::Create(D3DXVECTOR3(880.0f, 50.0f, 1300.0f));
	CIronBlock::Create(D3DXVECTOR3(880.0f, 50.0f, 1350.0f));
	CIronBlock::Create(D3DXVECTOR3(450.0f, 80.0f, 280.0f));
	CIronBlock::Create(D3DXVECTOR3(400.0f, 80.0f, 280.0f));
	CIronBlock::Create(D3DXVECTOR3(500.0f, 80.0f, 280.0f));
	CIronBlock::Create(D3DXVECTOR3(450.0f, 80.0f, 120.0f));
	CIronBlock::Create(D3DXVECTOR3(400.0f, 80.0f, 120.0f));
	CIronBlock::Create(D3DXVECTOR3(500.0f, 80.0f, 120.0f));
}

//=============================================================================
// �t�B�[���h�̐���
//=============================================================================
void CGame::FieldCreate()
{
	CPebble::Create(D3DXVECTOR3(50.0f, 0.0f, 890.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(140.0f, 0.0f, 880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(-20.0f, 0.0f, 880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(50.0f, 0.0f, 890.0f + 270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(140.0f, 0.0f, 880.0f + 270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(-20.0f, 0.0f, 880.0f + 270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(285.0f, 0.0f, 1230.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	CPebble::Create(D3DXVECTOR3(280.0f, 0.0f, 1320.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	CPebble::Create(D3DXVECTOR3(300.0f, 0.0f, 1120.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	CPebble::Create(D3DXVECTOR3(285.0f + 300.0f, 0.0f, 1230.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	CPebble::Create(D3DXVECTOR3(280.0f + 300.0f, 0.0f, 1320.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	CPebble::Create(D3DXVECTOR3(500.0f, 0.0f, 1060.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(420.0f, 0.0f, 1060.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(370.0f, 0.0f, 1060.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(875.0f, 0.0f, 744.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(825.0f, 0.0f, 734.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(785.0f, 0.0f, 754.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(747.0f, 0.0f, 730.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(900.0f, 0.0f, 744.0f - 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(825.0f, 0.0f, 734.0f - 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(785.0f, 0.0f, 754.0f - 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPebble::Create(D3DXVECTOR3(747.0f, 0.0f, 730.0f - 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���b�V���t�B�[���h�̐���
	CMeshField::Create(D3DXVECTOR3(-200.0f, -1.5f, 1700.0f));

	// ���b�V���V�����_�[�̐���
	CMeshCylinder::Create(D3DXVECTOR3(-150.0f, 1500.0f, 500.0f), 2000.0f, 30.0f);

	// �S�[���̐���
	CGoal::Create(D3DXVECTOR3(1166.0f, 0.0f, 533.0f));

	// ���|���S���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 220.0f), 700.0f, 700.0f, 10.0f, 10.0f);
	CFeild::Create(D3DXVECTOR3(30.0f, 0.5f, 1430.0f), 300.0f, 300.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1050.0f, 0.4f, 1200.0f), 500.0f, 500.0f, 8.0f, 8.0f);
	CFeild::Create(D3DXVECTOR3(450.0f, 0.5f, 1000.0f), 90.0f, 270.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1000.0f, 0.5f, 200.0f), 300.0f, 300.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1200.0f, 0.5f, 600.0f), 200.0f, 200.0f, 5.0f, 5.0f);
	CHole::Create(D3DXVECTOR3(1200.0f, -0.5f, 600.0f), 3000.0f, 3000.0f);

	// ��
	CScene3D::Create(D3DXVECTOR3(550.0f, 0.0f, 700.0f), 700.0f, 700.0f, 1.0f, 1.0f);
}
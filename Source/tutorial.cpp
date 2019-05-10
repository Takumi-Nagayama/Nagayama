//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : 長山拓実
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
// 静的メンバ変数宣言
//=============================================================================
CScore *CTutorial::m_pScore = NULL;
CNumBlock *CTutorial::m_pNumBlock = NULL;
CLife *CTutorial::m_pLife = NULL;

//=============================================================================
// チュートリアルの生成処理
//=============================================================================
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;

	if (pTutorial == NULL)
	{
		// オブジェクトクラスの生成
		pTutorial = new CTutorial;

		if (pTutorial != NULL)
		{
			pTutorial->Init();
		}
	}

	return pTutorial;
}

//=============================================================================
// チュートリアルのコンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
// チュートリアルのデストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// ゲーム初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	// テクスチャを読み込む
	// 地面テクスチャ
	CFeild::Load();
	CHole::Load();
	// パーティクル
	CParticle2D::Load();
	CParticle3D::Load();
	// 背景ロゴ
	CLogoBack::Load();
	// スコアロゴ
	CScoreLogo::Load();
	// ブロックロゴ
	CBlockLogo::Load();
	// 残機ロゴ
	CLifeLogo::Load();
	// ブロックの個数ロゴ
	CBlockCross::Load();
	// プレイヤーの残機ロゴ
	CPlayerCross::Load();
	// チュートリアルのロゴ
	CTutorialLogo::Load();
	// テクスチャのロード
	CNumber::Load();
	// ブロック出現位置
	CBlockPos::LoadModel();
	CBlockPos::LoadMat();

	// モデルを読み込む
	// ブロックのモデルの読み込み
	CBlock::LoadModel();
	CBlock::LoadMat();
	CIronBlock::LoadModel();
	CIronBlock::LoadMat();
	CWoodBlock::LoadModel();
	CWoodBlock::LoadMat();
	// パーティクルのモデルのロード
	CParticleX::LoadModel();
	CParticleX::LoadMat();
	// ゴールのモデルの読み込み
	CGoal::LoadModel();
	CPressAnyButton::Load();

	// プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 220.0f));

	// チュートリアルロゴ
	CTutorialLogo::Create(D3DXVECTOR3(100.0f, 50.0f, 280.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_MOVE);
	CTutorialLogo::Create(D3DXVECTOR3(-100.0f, 50.0f, 500.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_JUMP);
	CTutorialLogo::Create(D3DXVECTOR3(100.0f, 50.0f, 850.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_SET);
	CTutorialLogo::Create(D3DXVECTOR3(-100.0f, 50.0f, 1300.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_DESTROY);
	CTutorialLogo::Create(D3DXVECTOR3(0.0f, 50.0f, 1650.0f), 50.0f, 80.0f, 1.0f, 1.0f, CTutorialLogo::TYPE_END);

	// マップのロード
	CObject *pObject = NULL;
	pObject->LoadFile(1);
	LoadIronBlock();			// 鉄ブロック
	LoadWoodBlock();			// 木ブロック

	if (m_pScore == NULL)
	{
		// スコアの生成
		m_pScore = CScore::Create(D3DXVECTOR3(800.0f, 70.0f, 0.0f), 37.0f, 60.0f);
	}

	if (m_pNumBlock == NULL)
	{
		// ブロックの数の生成
		m_pNumBlock = CNumBlock::Create(D3DXVECTOR3(1170.0f, 70.0f, 0.0f), 37.0f);
	}

	if (m_pLife == NULL)
	{
		// ブロックの数の生成
		m_pLife = CLife::Create(D3DXVECTOR3(260.0f, 75.0f, 0.0f), 40.0f);
	}

	// プレイヤーの残機ロゴの生成
	CPlayerCross::Create(D3DXVECTOR3(150.0f, 70.0f, 0.0f), 70.0f, 50.0f);

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 650.0f, 0.0f), 150.0f, 100.0f, CPressAnyButton::TYPE_ENTER);

	// メッシュシリンダーの生成
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 1500.0f, 0.0f), 3000.0f, 30.0f);

	// 床ポリゴンの生成
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 1600.0f), 1000.0f, 4000.0f, 40.0f, 10.0f);
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 220.0f), 300.0f, 4000.0f, 20.0f, 1.0f);
	CHole::Create(D3DXVECTOR3(1200.0f, -0.5f, 600.0f), 3000.0f, 3000.0f);

	// ブロックの個数ロゴの生成
	CBlockCross::Create(D3DXVECTOR3(1030.0f, 70.0f, 0.0f), 50.0f, 30.0f);

	// ゴールの生成
	CGoal::Create(D3DXVECTOR3(0.0f, 0.0f, 1800.0f));

	// 穴
	CScene3D::Create(D3DXVECTOR3(0.0f, 0.0f, 700.0f), 1000.0f, 1000.0f, 80.0f, 80.0f);

	// 背景ロゴの生成
	CLogoBack::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 10.0f, 50.0f, 0.0f), 190.0f, 60.0f);
	CLogoBack::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450.0f, 50.0f, 0.0f), 130.0f, 60.0f);
	CScoreLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 10.0f, 25.0f, 0.0f), 80.0f, 30.0f);
	CBlockLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450.0f, 25.0f, 0.0f), 80.0f, 30.0f);
	CLifeLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450.0f, 20.0f, 0.0f), 70.0f, 20.0f);
	CLogoBack::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450.0f, 50.0f, 0.0f), 130.0f, 60.0f);

	return S_OK;
}

//=============================================================================
// チュートリアル終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	// モデルの解放
	CBlock::UnloadModel();		// ブロック
	CBlock::UnloadMat();
	CIronBlock::UnloadModel();		// 鉄ブロック
	CIronBlock::UnloadMat();
	CWoodBlock::UnloadModel();		// 木ブロック
	CWoodBlock::UnloadMat();
	CBlockPos::UnloadModel();		// ブロック出現位置
	CBlockPos::UnloadMat();

	// パーティクル
	CParticleX::UnloadModel();
	CParticleX::UnloadMat();
	CGoal::UnloadModel();		// ゴール
	
	// テクスチャの解放
	CFeild::Unload();			// 地面テクスチャ
	CHole::Unload();
	CTutorialLogo::Unload();	// チュートリアルロゴ
	CParticle2D::Unload();		// 2Dパーティクル
	CParticle3D::Unload();		// 3Dパーティクル
	CLogoBack::Unload();		// 背景ロゴ
	CScoreLogo::Unload();		// スコアロゴ
	CBlockLogo::Unload();		// ブロックロゴ
	CBlockCross::Unload();		// ブロックの個数ロゴ
	CPlayerCross::Unload();		// プレイヤーの残機ロゴ
	CPressAnyButton::Unload();
	CLifeLogo::Unload();			// 残機ロゴ

	// テクスチャの解放
	CNumber::UnLoad();

	// 情報を空にする
	m_pScore = NULL;
	m_pNumBlock = NULL;
	m_pLife = NULL;

	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// チュートリアル更新処理
//=============================================================================
void CTutorial::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 入力情報を取得
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// フェード取得
	CFade *pFade = CManager::GetFade();

	if (CPlayer::GetGoal() == true)
	{// ゴールしたら
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// ゲームに遷移
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
	else if (CPlayer::GetGameOver() == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// ゲームオーバーに遷移
			pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
		}
	}

	// デバック用
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
			// 決定したときのSE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			// フェード情報を取得
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
}

//=============================================================================
// チュートリアル描画処理
//=============================================================================
void CTutorial::Draw(void)
{
}

//=============================================================================
// モデルのロード
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
		char *pStrCur;		// 文字列の先頭へのポインタ
		char aLine[256];	// 文字列読み込み用（1行分）
		char aStr[256];		// 文字列抜き出し用

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
		pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
		strcpy(&aStr[0], pStrCur);

		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			while (1)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
				{
					pStrCur += strlen("NUM_MODEL =");	// 頭出し

					nNumModel = atoi(pStrCur);	// 文字列を値に変換
				}

				if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
				{
					for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
						strcpy(&aStr[0], pStrCur);

						int nCntTimer = 0;

						if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
						{
							pStrCur += strlen("ModelType");	// 頭出し

							int nType = atoi(pStrCur);	// 文字列を値に変換

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
							strcpy(&aStr[0], pStrCur);

							D3DXVECTOR3 pos;
							D3DXVECTOR3 rot;

							if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
							{// 位置
								pStrCur += strlen("POS =");	// 頭出し
								int nWord;

								// floatに変換して代入
								pos.x = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								pos.y = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								pos.z = (float)atof(pStrCur);
							}

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
							strcpy(&aStr[0], pStrCur);

							if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
							{// 位置
								pStrCur += strlen("ROT =");	// 頭出し

								int nWord;

								// floatに変換して代入
								rot.x = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								rot.y = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								rot.z = (float)atof(pStrCur);
							}

							// 生成
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
// モデルのロード
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
		char *pStrCur;		// 文字列の先頭へのポインタ
		char aLine[256];	// 文字列読み込み用（1行分）
		char aStr[256];		// 文字列抜き出し用

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
		pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
		strcpy(&aStr[0], pStrCur);

		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			while (1)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
				{
					pStrCur += strlen("NUM_MODEL =");	// 頭出し

					nNumModel = atoi(pStrCur);	// 文字列を値に変換
				}

				if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
				{
					for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
						strcpy(&aStr[0], pStrCur);

						int nCntTimer = 0;

						if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
						{
							pStrCur += strlen("ModelType");	// 頭出し

							int nType = atoi(pStrCur);	// 文字列を値に変換

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
							strcpy(&aStr[0], pStrCur);

							D3DXVECTOR3 pos;
							D3DXVECTOR3 rot;

							if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
							{// 位置
								pStrCur += strlen("POS =");	// 頭出し
								int nWord;

								// floatに変換して代入
								pos.x = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								pos.y = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								pos.z = (float)atof(pStrCur);
							}

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
							strcpy(&aStr[0], pStrCur);

							if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
							{// 位置
								pStrCur += strlen("ROT =");	// 頭出し

								int nWord;

								// floatに変換して代入
								rot.x = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								rot.y = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								rot.z = (float)atof(pStrCur);
							}

							// 生成
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
// スコアの取得
//=============================================================================
CScore *CTutorial::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ブロックの数の取得
//=============================================================================
CNumBlock *CTutorial::GetNumBlock(void)
{
	return m_pNumBlock;
}

//=============================================================================
// 残機の取得
//=============================================================================
CLife *CTutorial::GetLife(void)
{
	return m_pLife;
}
//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 長山拓実
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
// マクロ定義
//*****************************************************************************
#define COIN_FILE_GAME	"data\\TEXT\\modelCoin.txt"			// 設置したモデルを書き出すテキスト
#define SCORE_POS		(D3DXVECTOR3(800.0f, 70.0f, 0.0f))	// スコアの位置
#define SCORE_HEIGHT	(37.0f)								// スコアのサイズ
#define SCORE_WIDTH		(60.0f)								// スコアのサイズ
#define NUMBLOCK_POS	(D3DXVECTOR3(1170.0f, 70.0f, 0.0f))	// ブロックの個数の位置
#define NUMBLOCK_SIZE	(37.0f)								// ブロックの個数のサイズ
#define NUMCOIN_POS	(D3DXVECTOR3(1170.0f, 200.0f, 0.0f))	// コインの個数の位置
#define NUMCOIN_SIZE	(37.0f)								// コインの個数のサイズ
#define NUMBLOCKLOGO_POS	(D3DXVECTOR3(1030.0f, 70.0f, 0.0f))	// ブロックの個数ロゴの位置
#define NUMBLOCKLOGO_WIDTH	(50.0f)								// ブロックの個数ロゴのサイズ
#define NUMBLOCKLOGO_HEIGHT	(30.0f)								// ブロックの個数ロゴのサイズ
#define LIFE_POS		(D3DXVECTOR3(260.0f, 75.0f, 0.0f))	// ライフの位置
#define LIFE_SIZE		(40.0f)								// ライフのサイズ
#define PLAYERCROSS_POS	(D3DXVECTOR3(150.0f, 70.0f, 0.0f))	// 残機ロゴの位置
#define PLAYERCROSS_WIDTH	(70.0f)							// 残機ロゴのサイズ
#define PLAYERCROSS_HEIGHT	(50.0f)							// 残機ロゴのサイズ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScore *CGame::m_pScore = NULL;
CNumBlock *CGame::m_pNumBlock = NULL;
CLife *CGame::m_pLife = NULL;

//=============================================================================
// ゲームクラスのコンストラクタ
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ゲームの生成処理
//=============================================================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		// オブジェクトクラスの生成
		pGame = new CGame;

		if (pGame != NULL)
		{
			pGame->Init();
		}
	}

	return pGame;
}

//=============================================================================
// ゲーム初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	LoadTexture();
	LoadModel();
	LoadMat();

	// コイン生成
	LoadCoin();

	// プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(80.0f, 50.0f, 250.0f));

	// 宝石の生成
	CGem::Create(D3DXVECTOR3(1160.0f, 0.0f, 720.0f));

	// マップのロード
	CObject *pObject = NULL;
	pObject->LoadFile(0);

	BlockCreate();
	FieldCreate();

	if (m_pScore == NULL)
	{
		// スコアの生成
		m_pScore = CScore::Create(SCORE_POS, SCORE_HEIGHT, SCORE_WIDTH);
	}

	if (m_pNumBlock == NULL)
	{
		// ブロックの数の生成
		m_pNumBlock = CNumBlock::Create(NUMBLOCK_POS, NUMBLOCK_SIZE);
	}

	if (m_pLife == NULL)
	{
		// ライフの生成
		m_pLife = CLife::Create(LIFE_POS, LIFE_SIZE);
	}

	// プレイヤーの残機ロゴの生成
	CPlayerCross::Create(PLAYERCROSS_POS, PLAYERCROSS_WIDTH, PLAYERCROSS_HEIGHT);

	// ブロックの個数ロゴの生成
	CBlockCross::Create(NUMBLOCKLOGO_POS, NUMBLOCKLOGO_WIDTH, NUMBLOCKLOGO_HEIGHT);

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
// ゲーム終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CCoin::SetNumCoin(0);

	// モデルの解放
	UnLoadModel();
	
	// テクスチャの解放
	UnLoadTexture();

	// マテリアルの解放
	UnLoadMat();

	// 情報を空にする
	m_pScore = NULL;
	m_pNumBlock = NULL;
	m_pLife = NULL;
	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// ゲーム更新処理
//=============================================================================
void CGame::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// フェード取得
	CFade *pFade = CManager::GetFade();

	if (CPlayer::GetGoal() == true)
	{// ゴールしたら
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// ゲームクリアに遷移
			CManager::GetRankingScore(m_pScore->GetScore());
			CManager::GetScore(m_pScore->GetScore());

			pFade->SetFade(CManager::MODE_GAMECLEAR, CFade::FADE_OUT);
		}
	}
	else if (CPlayer::GetGameOver() == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// ゲームオーバーに遷移
			CManager::GetRankingScore(m_pScore->GetScore());
			CManager::GetScore(m_pScore->GetScore());
			pFade->SetFade(CManager::MODE_GAMEOVER, CFade::FADE_OUT);
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
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// スコアの取得
//=============================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ブロックの数の取得
//=============================================================================
CNumBlock *CGame::GetNumBlock(void)
{
	return m_pNumBlock;
}

//=============================================================================
// 残機の取得
//=============================================================================
CLife *CGame::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// モデルのロード
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

							// コイン生成
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

	// コイン生成
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
// テクスチャのロード
//=============================================================================
void CGame::LoadTexture()
{
	// テクスチャを読み込む
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
	// 地面テクスチャ
	CHole::Load();
	CFeild::Load();
	// テクスチャの解放
	CNumber::Load();
}

//=============================================================================
// テクスチャの開放
//=============================================================================
void CGame::UnLoadTexture()
{
	CParticle2D::Unload();		// 2Dパーティクル
	CParticle3D::Unload();		// 3Dパーティクル
	CLogoBack::Unload();		// 背景ロゴ
	CScoreLogo::Unload();		// スコアロゴ
	CBlockLogo::Unload();		// ブロックロゴ
	CLifeLogo::Unload();			// 残機ロゴ
	CBlockCross::Unload();		// ブロックの個数ロゴ
	CPlayerCross::Unload();		// プレイヤーの残機ロゴ
	CHole::Unload();				// 地面テクスチャ
	CFeild::Unload();
	CNumber::UnLoad();			// テクスチャの解放
}

//=============================================================================
// モデルのロード
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
// モデルの開放
//=============================================================================
void CGame::UnLoadModel()
{
	CBlock::UnloadModel();		// ブロック
	CGoal::UnloadModel();		// ゴール
	CObject::UnloadModel();			// 背景オブジェクト
	CCoin::UnloadModel();				// コイン
	CGem::UnloadModel();				// 宝石
	CWoodBlock::UnloadModel();		// 木ブロック
	CIronBlock::UnloadModel();		// 木ブロック
	CBlockPos::UnloadModel();		// ブロック出現位置
	CPebble::UnloadModel();			// 小石のモデル
	CParticleX::UnloadModel();
}

//=============================================================================
// マテリアルのロード
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
// マテリアルの開放
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
// ブロックの生成
//=============================================================================
void CGame::BlockCreate()
{
	// 木のブロック生成
	CWoodBlock::Create(D3DXVECTOR3(250.0f, 0.0f, 430.0f));
	CWoodBlock::Create(D3DXVECTOR3(1000.0f, 0.0f, 280.0f));
	CWoodBlock::Create(D3DXVECTOR3(1000.0f, 0.0f, 160.0f));

	// 鉄ブロック生成
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
// フィールドの生成
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

	// メッシュフィールドの生成
	CMeshField::Create(D3DXVECTOR3(-200.0f, -1.5f, 1700.0f));

	// メッシュシリンダーの生成
	CMeshCylinder::Create(D3DXVECTOR3(-150.0f, 1500.0f, 500.0f), 2000.0f, 30.0f);

	// ゴールの生成
	CGoal::Create(D3DXVECTOR3(1166.0f, 0.0f, 533.0f));

	// 床ポリゴンの生成
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 220.0f), 700.0f, 700.0f, 10.0f, 10.0f);
	CFeild::Create(D3DXVECTOR3(30.0f, 0.5f, 1430.0f), 300.0f, 300.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1050.0f, 0.4f, 1200.0f), 500.0f, 500.0f, 8.0f, 8.0f);
	CFeild::Create(D3DXVECTOR3(450.0f, 0.5f, 1000.0f), 90.0f, 270.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1000.0f, 0.5f, 200.0f), 300.0f, 300.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1200.0f, 0.5f, 600.0f), 200.0f, 200.0f, 5.0f, 5.0f);
	CHole::Create(D3DXVECTOR3(1200.0f, -0.5f, 600.0f), 3000.0f, 3000.0f);

	// 穴
	CScene3D::Create(D3DXVECTOR3(550.0f, 0.0f, 700.0f), 700.0f, 700.0f, 1.0f, 1.0f);
}
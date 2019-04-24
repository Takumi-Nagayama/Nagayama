//=============================================================================
//
// リザルトの処理 [result.cpp]
// Author : 長山拓実
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
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
//CScore *CResult::m_pScore = 0;
//CRenderer *CResult::m_pRenderer = NULL;

//=============================================================================
// リザルトクラスのコンストラクタ
//=============================================================================
CResult::CResult()
{
	// 値をクリア
}

//=============================================================================
// リザルトの生成処理
//=============================================================================
CResult *CResult::Create()
{
	CResult *pResult = NULL;

	if (pResult == NULL)
	{
		// オブジェクトクラスの生成
		pResult = new CResult;

		if (pResult != NULL)
		{
			pResult->Init();
		}
	}
	return pResult;
}

//=============================================================================
// リザルトクラスのデストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// リザルトの初期化処理
//=============================================================================
HRESULT CResult::Init()
{
	// 背景の生成
	//CBg::Load();
	//CBg::Create(0.0005f);

	// ロゴの生成
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
// リザルトの終了処理
//=============================================================================
void CResult::Uninit(void)
{
	// テクスチャを解放
	//CBg::Unload();			// 背景
	//CResultLogo::Unload();		// ロゴ

	//m_pScore = NULL;

	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// リザルトの更新処理
//=============================================================================
void CResult::Update(void)
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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// 決定したときのSE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			/*CManager::ReleaseScore();*/
			pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		}
	}
}

//=============================================================================
// リザルトの描画処理
//=============================================================================
void CResult::Draw(void)
{
}
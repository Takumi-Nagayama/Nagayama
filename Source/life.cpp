//=============================================================================
//
// ブロックの数処理 [NumBlock.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "life.h"
#include "manager.h"
#include "number.h"
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LIFE	(3)	//ライフの初期値

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
//int CLife::m_nScore = 0;
//CNumber *CLife::m_apLife[MAX_NUMLIFE] = {};

//=============================================================================
// スコアの生成処理
//=============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos, float fSize)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{
		// オブジェクトクラスの生成
		pLife = new CLife;

		if (pLife != NULL)
		{
			pLife->m_pos = pos;
			pLife->m_fSize = fSize;
			pLife->Init();
		}
	}

	return pLife;
}

//=============================================================================
// スコアクラスのコンストラクタ
//=============================================================================
CLife::CLife(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	for (int nCntScore = 0; nCntScore < MAX_NUMLIFE; nCntScore++)
	{
		m_apLife[nCntScore] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumLife = 0;
}

//=============================================================================
// スコアクラスのデストラクタ
//=============================================================================
CLife::~CLife()
{
}

//=============================================================================
// スコアの初期化処理
//=============================================================================
HRESULT CLife::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_SCORE);

	for (int nCntScore = 0; nCntScore < MAX_NUMLIFE; nCntScore++)
	{
		m_apLife[nCntScore] = CNumber::Create(D3DXVECTOR3(m_pos.x - nCntScore * 60, m_pos.y, 0.0f), m_fSize);
	}

	m_nNumLife = 0;

	AddLife(MAX_LIFE);

	return S_OK;
}

//=============================================================================
// スコアの終了処理
//=============================================================================
void CLife::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_NUMLIFE; nCntBg++)
	{
		if (m_apLife[nCntBg] != NULL)
		{
			m_apLife[nCntBg]->Uninit();

			// メモリを開放
			delete m_apLife[nCntBg];
			m_apLife[nCntBg] = NULL;
		}
	}

	// スコア自体の解放
	Release();
}

//=============================================================================
// スコアの更新処理
//=============================================================================
void CLife::Update(void)
{

}

//=============================================================================
// スコアの更新処理
//=============================================================================
void CLife::Draw(void)
{
	for (int nCntBg = 0; nCntBg < MAX_NUMLIFE; nCntBg++)
	{
		if (m_apLife[nCntBg] != NULL)
		{
			m_apLife[nCntBg]->Draw();
		}
	}
}

//=============================================================================
// スコアの加算
//=============================================================================
void CLife::AddLife(int nValue)
{
	int nAnswer = 1;
	int nCntScore;
	int nScore;

	m_nNumLife += nValue;

	for (nCntScore = 0; nCntScore < MAX_NUMLIFE; nCntScore++)
	{
		// スコアを表示するための計算
		nScore = m_nNumLife % (nAnswer * 10) / nAnswer;

		m_apLife[nCntScore]->SetNumber(nScore);

		nAnswer *= 10;
	}

}

//=============================================================================
// スコアの設定処理
//=============================================================================
void CLife::SetLife(int nScore)
{
	m_nNumLife = nScore;
}

//=============================================================================
// スコアの取得
//=============================================================================
int CLife::GetLife(void)
{
	return m_nNumLife;
}

//=============================================================================
// スコアの色の設定処理
//=============================================================================
void CLife::SetColor(D3DXCOLOR color)
{
	for (int nCntScore = 0; nCntScore < MAX_NUMLIFE; nCntScore++)
	{
		m_apLife[nCntScore]->SetColor(color);
	}
}
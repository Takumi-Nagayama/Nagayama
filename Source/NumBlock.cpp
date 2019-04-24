//=============================================================================
//
// ブロックの数処理 [NumBlock.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "NumBlock.h"
#include "manager.h"
#include "number.h"
#include "scene2D.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
//int CNumBlock::m_nScore = 0;
//CNumber *CNumBlock::m_apNumber[MAX_NUMBLOCK] = {};

//=============================================================================
// スコアの生成処理
//=============================================================================
CNumBlock *CNumBlock::Create(D3DXVECTOR3 pos, float fSize)
{
	CNumBlock *pNumber = NULL;

	if (pNumber == NULL)
	{
		// オブジェクトクラスの生成
		pNumber = new CNumBlock;

		if (pNumber != NULL)
		{
			pNumber->m_pos = pos;
			pNumber->m_fSize = fSize;
			pNumber->Init();
		}
	}

	return pNumber;
}

//=============================================================================
// スコアクラスのコンストラクタ
//=============================================================================
CNumBlock::CNumBlock(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	for (int nCntScore = 0; nCntScore < MAX_NUMBLOCK; nCntScore++)
	{
		m_apNumber[nCntScore] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumBlock = 10;
}

//=============================================================================
// スコアクラスのデストラクタ
//=============================================================================
CNumBlock::~CNumBlock()
{
}

//=============================================================================
// スコアの初期化処理
//=============================================================================
HRESULT CNumBlock::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_SCORE);

	for (int nCntScore = 0; nCntScore < MAX_NUMBLOCK; nCntScore++)
	{
		m_apNumber[nCntScore] = CNumber::Create(D3DXVECTOR3(m_pos.x - nCntScore * 60, m_pos.y, 0.0f), m_fSize);
	}

	m_nNumBlock = 0;

	AddBlock(10);

	return S_OK;
}

//=============================================================================
// スコアの終了処理
//=============================================================================
void CNumBlock::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_NUMBLOCK; nCntBg++)
	{
		if (m_apNumber[nCntBg] != NULL)
		{
			m_apNumber[nCntBg]->Uninit();

			// メモリを開放
			delete m_apNumber[nCntBg];
			m_apNumber[nCntBg] = NULL;
		}
	}

	// スコア自体の解放
	Release();
}

//=============================================================================
// スコアの更新処理
//=============================================================================
void CNumBlock::Update(void)
{

}

//=============================================================================
// スコアの更新処理
//=============================================================================
void CNumBlock::Draw(void)
{
	for (int nCntBg = 0; nCntBg < MAX_NUMBLOCK; nCntBg++)
	{
		if (m_apNumber[nCntBg] != NULL)
		{
			m_apNumber[nCntBg]->Draw();
		}
	}
}

//=============================================================================
// スコアの加算
//=============================================================================
void CNumBlock::AddBlock(int nValue)
{
	int nAnswer = 1;
	int nCntScore;
	int nScore;

	m_nNumBlock += nValue;

	for (nCntScore = 0; nCntScore < MAX_NUMBLOCK; nCntScore++)
	{
		// スコアを表示するための計算
		nScore = m_nNumBlock % (nAnswer * 10) / nAnswer;

		m_apNumber[nCntScore]->SetNumber(nScore);

		nAnswer *= 10;
	}

}

//=============================================================================
// スコアの設定処理
//=============================================================================
void CNumBlock::SetBlock(int nBlock)
{
	m_nNumBlock = nBlock;
}

//=============================================================================
// スコアの取得
//=============================================================================
int CNumBlock::GetBlock(void)
{
	return m_nNumBlock;
}

//=============================================================================
// スコアの色の設定処理
//=============================================================================
void CNumBlock::SetColor(D3DXCOLOR color)
{
	for (int nCntScore = 0; nCntScore < MAX_NUMBLOCK; nCntScore++)
	{
		m_apNumber[nCntScore]->SetColor(color);
	}
}
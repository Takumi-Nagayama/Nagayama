//=============================================================================
//
// ブロックロゴの処理 [blockLogo.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "blockLogo.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BLOCK_LOGO_COLOR	(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBlockLogo::m_pTexture = NULL;

//=============================================================================
// ブロックロゴの生成処理
//=============================================================================
CBlockLogo *CBlockLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CBlockLogo *pBlockLogo = NULL;

	if (pBlockLogo == NULL)
	{
		// ブロックロゴクラスの生成
		pBlockLogo = new CBlockLogo;

		if (pBlockLogo != NULL)
		{
			pBlockLogo->SetPosition(pos);
			pBlockLogo->SetWidth(fWidth);
			pBlockLogo->SetHeight(fHeight);
			pBlockLogo->Init();
			pBlockLogo->BindTexture(m_pTexture);
		}
	}

	return pBlockLogo;
}

//=============================================================================
// ブロックロゴクラスのコンストラクタ
//=============================================================================
CBlockLogo::CBlockLogo()
{
}

//=============================================================================
// ブロックロゴクラスのデストラクタ
//=============================================================================
CBlockLogo::~CBlockLogo()
{
}

//=============================================================================
// ブロックロゴ初期化処理
//=============================================================================
HRESULT CBlockLogo::Init(void)
{
	// 2Dオブジェクト初期化処理
	CLogo::Init();

	CLogo::SetCol(BLOCK_LOGO_COLOR);

	return S_OK;
}

//=============================================================================
// ブロックロゴ終了処理
//=============================================================================
void CBlockLogo::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CLogo::Uninit();
}

//=============================================================================
// ブロックロゴ更新処理
//=============================================================================
void CBlockLogo::Update(void)
{
}

//=============================================================================
// ブロックロゴ描画処理
//=============================================================================
void CBlockLogo::Draw(void)
{
	// 2Dオブジェクト描画処理
	CLogo::Draw();
}

//=============================================================================
// ブロックロゴのテクスチャ読み込み処理
//=============================================================================
HRESULT CBlockLogo::Load(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BLOCK_LOGO_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ブロックロゴのテクスチャ解放処理
//=============================================================================
void CBlockLogo::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
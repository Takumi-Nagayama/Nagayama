//=============================================================================
//
// 残機ロゴの処理 [lifeLogo.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "lifeLogo.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LIFE_LOGO_COLOR	(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CLifeLogo::m_pTexture = NULL;

//=============================================================================
// ブロックロゴの生成処理
//=============================================================================
CLifeLogo *CLifeLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CLifeLogo *pLifeLogo = NULL;

	if (pLifeLogo == NULL)
	{
		// ブロックロゴクラスの生成
		pLifeLogo = new CLifeLogo;

		if (pLifeLogo != NULL)
		{
			pLifeLogo->SetPosition(pos);
			pLifeLogo->SetWidth(fWidth);
			pLifeLogo->SetHeight(fHeight);
			pLifeLogo->Init();
			pLifeLogo->BindTexture(m_pTexture);
		}
	}

	return pLifeLogo;
}

//=============================================================================
// ブロックロゴクラスのコンストラクタ
//=============================================================================
CLifeLogo::CLifeLogo()
{
	// 値をクリア
}

//=============================================================================
// ブロックロゴクラスのデストラクタ
//=============================================================================
CLifeLogo::~CLifeLogo()
{
}

//=============================================================================
// ブロックロゴ初期化処理
//=============================================================================
HRESULT CLifeLogo::Init(void)
{
	// 2Dオブジェクト初期化処理
	CLogo::Init();

	CLogo::SetCol(LIFE_LOGO_COLOR);

	return S_OK;
}

//=============================================================================
// ブロックロゴ終了処理
//=============================================================================
void CLifeLogo::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CLogo::Uninit();
}

//=============================================================================
// ブロックロゴ更新処理
//=============================================================================
void CLifeLogo::Update(void)
{
}

//=============================================================================
// ブロックロゴ描画処理
//=============================================================================
void CLifeLogo::Draw(void)
{
	// 2Dオブジェクト描画処理
	CLogo::Draw();
}

//=============================================================================
// ブロックロゴのテクスチャ読み込み処理
//=============================================================================
HRESULT CLifeLogo::Load(void)
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
	D3DXCreateTextureFromFile(pDevice, LIFE_LOGO_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ブロックロゴのテクスチャ解放処理
//=============================================================================
void CLifeLogo::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
//
// 背景ロゴの処理 [logoBack.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "logoBack.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CLogoBack::m_pTexture = NULL;

//=============================================================================
// チュートリアルロゴの生成処理
//=============================================================================
CLogoBack *CLogoBack::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CLogoBack *pLogoBack = NULL;

	if (pLogoBack == NULL)
	{
		// チュートリアルロゴクラスの生成
		pLogoBack = new CLogoBack;

		if (pLogoBack != NULL)
		{
			pLogoBack->SetPosition(pos);
			pLogoBack->SetWidth(fWidth);
			pLogoBack->SetHeight(fHeight);
			pLogoBack->Init();
			pLogoBack->BindTexture(m_pTexture);
		}
	}

	return pLogoBack;
}

//=============================================================================
// チュートリアルロゴクラスのコンストラクタ
//=============================================================================
CLogoBack::CLogoBack() : CLogo(LOGOBACK_PRIORITY)
{
	// 値をクリア
}

//=============================================================================
// チュートリアルロゴクラスのデストラクタ
//=============================================================================
CLogoBack::~CLogoBack()
{
}

//=============================================================================
// チュートリアルロゴ初期化処理
//=============================================================================
HRESULT CLogoBack::Init(void)
{
	// 2Dオブジェクト初期化処理
	CLogo::Init();

	CLogo::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// チュートリアルロゴ終了処理
//=============================================================================
void CLogoBack::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CLogo::Uninit();
}

//=============================================================================
// チュートリアルロゴ更新処理
//=============================================================================
void CLogoBack::Update(void)
{
}

//=============================================================================
// チュートリアルロゴ描画処理
//=============================================================================
void CLogoBack::Draw(void)
{
	// 2Dオブジェクト描画処理
	CLogo::Draw();
}

//=============================================================================
// チュートリアルロゴのテクスチャ読み込み処理
//=============================================================================
HRESULT CLogoBack::Load(void)
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
	D3DXCreateTextureFromFile(pDevice, LOGOBACK_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// チュートリアルロゴのテクスチャ解放処理
//=============================================================================
void CLogoBack::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
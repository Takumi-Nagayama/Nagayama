//=============================================================================
//
// チュートリアルで使うロゴの処理 [tutorialLogo.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "tutorialLogo.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorialLogo::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// 地面の生成処理
//=============================================================================
CTutorialLogo *CTutorialLogo::Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV, TEX_TYPE type)
{
	CTutorialLogo *pTutorialLogo = NULL;

	if (pTutorialLogo == NULL)
	{
		// 地面クラスの生成
		pTutorialLogo = new CTutorialLogo;

		if (pTutorialLogo != NULL)
		{
			pTutorialLogo->SetDepth(fDepth);
			pTutorialLogo->SetWidth(fWifth);
			pTutorialLogo->SetTextureU(fTextureU);
			pTutorialLogo->SetTextureV(fTextureV);
			pTutorialLogo->SetPos(pos);
			pTutorialLogo->Init();								// 初期化処理
			pTutorialLogo->SetRot(D3DXVECTOR3(-1.0f,0.0f,0.0f));								// 向きの設定
			pTutorialLogo->BindTexture(m_apTexture[type]);				// 種類の設定
			pTutorialLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));				// 種類の設定
		}
	}
	return pTutorialLogo;
}

//=============================================================================
// 地面クラスのコンストラクタ
//=============================================================================
CTutorialLogo::CTutorialLogo() : CPolygon(TUTORIALLOGO_PRIORITY)
{
	// 値をクリア
}

//=============================================================================
// 地面クラスのデストラクタ
//=============================================================================
CTutorialLogo::~CTutorialLogo()
{
}

//=============================================================================
// 地面の初期化処理
//=============================================================================
HRESULT CTutorialLogo::Init(void)
{
	// 2Dオブジェクト初期化処理
	CPolygon::Init();

	return S_OK;
}

//=============================================================================
// 地面の終了処理
//=============================================================================
void CTutorialLogo::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CPolygon::Uninit();
}

//=============================================================================
// 地面の更新処理
//=============================================================================
void CTutorialLogo::Update(void)
{
}

//=============================================================================
// 地面の描画処理
//=============================================================================
void CTutorialLogo::Draw(void)
{
	// 2Dオブジェクト描画処理
	CPolygon::Draw();
}

//=============================================================================
// 地面のテクスチャ読み込み処理
//=============================================================================
HRESULT CTutorialLogo::Load(void)
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
	D3DXCreateTextureFromFile(pDevice, MOVE_TEXTURE_NAME, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, JUMP_TEXTURE_NAME, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, SET_TEXTURE_NAME, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, DESTROY_TEXTURE_NAME, &m_apTexture[3]);
	D3DXCreateTextureFromFile(pDevice, END_TEXTURE_NAME, &m_apTexture[4]);

	return S_OK;
}

//=============================================================================
// 地面のテクスチャ解放処理
//=============================================================================
void CTutorialLogo::Unload(void)
{
	for (int nCntTex = 0; nCntTex < TYPE_MAX; nCntTex++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
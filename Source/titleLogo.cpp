//=============================================================================
//
// タイトルロゴの処理 [titleLogo.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "titleLogo.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTitleLogo::m_pTexture = NULL;

//=============================================================================
// タイトルロゴの生成処理
//=============================================================================
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTitleLogo *pTitleLogo = NULL;

	if (pTitleLogo == NULL)
	{
		// タイトルロゴクラスの生成
		pTitleLogo = new CTitleLogo;

		if (pTitleLogo != NULL)
		{
			pTitleLogo->SetPosition(pos);
			pTitleLogo->SetWidth(fWidth);
			pTitleLogo->SetHeight(fHeight);
			pTitleLogo->Init();
			pTitleLogo->BindTexture(m_pTexture);
		}
	}

	return pTitleLogo;
}

//=============================================================================
// タイトルロゴクラスのコンストラクタ
//=============================================================================
CTitleLogo::CTitleLogo() : CLogo(6)
{
	// 値をクリア
}

//=============================================================================
// タイトルロゴクラスのデストラクタ
//=============================================================================
CTitleLogo::~CTitleLogo()
{
}

//=============================================================================
// タイトルロゴ初期化処理
//=============================================================================
HRESULT CTitleLogo::Init(void)
{
	// 2Dオブジェクト初期化処理
	CLogo::Init();

	CLogo::SetCol(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// タイトルロゴ終了処理
//=============================================================================
void CTitleLogo::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CLogo::Uninit();
}

//=============================================================================
// タイトルロゴ更新処理
//=============================================================================
void CTitleLogo::Update(void)
{
	//// 位置を取得
	//D3DXVECTOR3 pos;
	//pos = CLogo::GetPosition();

	//// 頂点バッファを取得
	//LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	//VtxBuff = CLogo::GetVtxBuff();

	//// 入力情報を取得
	//CInputKeyboard *pInputKeyboard;
	//pInputKeyboard = CManager::GetInputKeyboard();

	//// 入力情報を取得
	//CInputJoypad *pInputJoypad;
	//pInputJoypad = CManager::GetInputJoypad();

	//VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	//					// 頂点バッファをロックし、頂点データへのポインタを取得
	//VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//// 頂点情報を更新
	//pVtx[0].pos = D3DXVECTOR3(pos.x - 400.0f, pos.y - 200.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + 400.0f, pos.y - 200.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - 400.0f, pos.y + 200.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + 400.0f, pos.y + 200.0f, 0.0f);

	//if (pos.x > SCREEN_WIDTH / 2)
	//{
	//	pos.x -= 3.0f;
	//}
	//else if (pos.x <= SCREEN_WIDTH / 2)
	//{
	//	pos.x = SCREEN_WIDTH / 2;
	//}

	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
	//{
	//	pos.x = SCREEN_WIDTH / 2;
	//}

	//// 頂点バッファをアンロック
	//VtxBuff->Unlock();

	//// 位置の設定
	//CLogo::SetPosition(pos);
	//// 頂点バッファの設定
	//CLogo::SetVtxBuff(VtxBuff);
}

//=============================================================================
// タイトルロゴ描画処理
//=============================================================================
void CTitleLogo::Draw(void)
{
	// 2Dオブジェクト描画処理
	CLogo::Draw();
}

//=============================================================================
// タイトルロゴのテクスチャ読み込み処理
//=============================================================================
HRESULT CTitleLogo::Load(void)
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
	D3DXCreateTextureFromFile(pDevice, TITLE_LOGO_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// タイトルロゴのテクスチャ解放処理
//=============================================================================
void CTitleLogo::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
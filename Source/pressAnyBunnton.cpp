//=============================================================================
//
// プレスエニーボタンの処理 [pressAnyButton.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "pressAnyButton.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BUTTON_COLOR		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))
#define BLINK_COUNT			(60)
#define BLINK_COUNT_FAST	(2)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPressAnyButton::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// プレスエニーボタンの生成処理
//=============================================================================
CPressAnyButton *CPressAnyButton::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LOGOTYPE type)
{
	CPressAnyButton *pGameOverLogo = NULL;

	if (pGameOverLogo == NULL)
	{
		// プレスエニーボタンクラスの生成
		pGameOverLogo = new CPressAnyButton;

		if (pGameOverLogo != NULL)
		{
			pGameOverLogo->SetPosition(pos);
			pGameOverLogo->SetWidth(fWidth);
			pGameOverLogo->SetHeight(fHeight);
			pGameOverLogo->m_type = type;
			pGameOverLogo->Init();
			pGameOverLogo->BindTexture(m_apTexture[type]);
		}
	}

	return pGameOverLogo;
}

//=============================================================================
// プレスエニーボタンクラスのコンストラクタ
//=============================================================================
CPressAnyButton::CPressAnyButton()
{
	// 値をクリア
	m_nCntEnter = 0;
	m_fEnterTimer = 1.0f;
	m_bPress = false;
	m_type = TYPE_ANY;
}

//=============================================================================
// プレスエニーボタンクラスのデストラクタ
//=============================================================================
CPressAnyButton::~CPressAnyButton()
{
}

//=============================================================================
// プレスエニーボタン初期化処理
//=============================================================================
HRESULT CPressAnyButton::Init(void)
{
	// 2Dオブジェクト初期化処理
	CLogo::Init();

	m_nCntEnter = 0;
	m_fEnterTimer = 1.0f;
	m_bPress = false;

	CLogo::SetCol(BUTTON_COLOR);

	return S_OK;
}

//=============================================================================
// プレスエニーボタン終了処理
//=============================================================================
void CPressAnyButton::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CLogo::Uninit();
}

//=============================================================================
// プレスエニーボタン更新処理
//=============================================================================
void CPressAnyButton::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 入力情報を取得
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// フェードの状態を取得
	CFade::FADE fade;
	fade = CFade::GetFade();


	m_nCntEnter++;

	int nCount = 0;	// 点滅の間隔

	if (CFade::GetFade() != CFade::FADE_IN)
	{
		if (m_type == TYPE_ANY)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true
				|| pInputJoypad->GetAnyButton(0) == true)
			{//	点滅を早くする
				m_bPress = true;
			}
		}
		else if(m_type == TYPE_ENTER)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true
				|| pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
			{//	点滅を早くする
				m_bPress = true;
			}
		}
	}

	if (m_bPress == false)
	{//	点滅が普通の時
		nCount = BLINK_COUNT;
	}
	else
	{// 点滅が早いとき
		nCount = BLINK_COUNT_FAST;
	}

	if (m_nCntEnter >= nCount)
	{
		if (m_fEnterTimer == 1)
		{
			m_fEnterTimer = 0.0f;
		}
		else if (m_fEnterTimer == 0)
		{
			m_fEnterTimer = 1.0f;
		}

		SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fEnterTimer));

		m_nCntEnter = 0;
	}
}

//=============================================================================
// プレスエニーボタン描画処理
//=============================================================================
void CPressAnyButton::Draw(void)
{
	// 2Dオブジェクト描画処理
	CLogo::Draw();
}

//=============================================================================
// プレスエニーボタンのテクスチャ読み込み処理
//=============================================================================
HRESULT CPressAnyButton::Load(void)
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
	D3DXCreateTextureFromFile(pDevice, BUTTON_LOGO_NAME, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BUTTON_LOGO_NAME01, &m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// プレスエニーボタンのテクスチャ解放処理
//=============================================================================
void CPressAnyButton::Unload(void)
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
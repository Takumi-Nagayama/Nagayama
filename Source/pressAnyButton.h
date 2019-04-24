//=============================================================================
//
// プレスエニーボタンの処理 [pressAnyButton.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PRESSANYBUTTON_H_
#define _PRESSANYBUTTON_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BUTTON_LOGO_NAME		"data/TEXTURE/UI/PressAnyButton.png"			// プレスエニーボタンロゴのテクスチャ名
#define BUTTON_LOGO_NAME01		"data/TEXTURE/UI/enter.png"					// エンターボタンロゴのテクスチャ名

//=========================
// プレスエニーボタンロゴクラス
//=========================
class CPressAnyButton : public CLogo
{
public:
	typedef enum
	{// プレイヤーの状態
		TYPE_ANY = 0,	// 通常状態
		TYPE_ENTER,		// 移動状態
		TYPE_MAX		// ロゴの種類の総数
	} LOGOTYPE;

	CPressAnyButton();															// コンストラクタ
	~CPressAnyButton();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CPressAnyButton *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LOGOTYPE type);	// オブジェクトの生成

	HRESULT Init(void);															// プレスエニーボタンロゴ初期化処理
	void Uninit(void);															// プレスエニーボタンロゴ終了処理
	void Update(void);															// プレスエニーボタンロゴ更新処理
	void Draw(void);															// プレスエニーボタンロゴ描x画処理

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];
	LOGOTYPE m_type;
	int	m_nCntEnter;
	float m_fEnterTimer;
	bool m_bPress;
};

#endif
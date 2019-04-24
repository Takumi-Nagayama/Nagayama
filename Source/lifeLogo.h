//=============================================================================
//
// 残機ロゴの処理 [lifeLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _LIFELOGO_H_
#define _LIFELOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LIFE_LOGO_NAME		"data/TEXTURE/UI/LIFE.png"			// 残機ロゴのテクスチャ名

//=========================
// スコアロゴクラス
//=========================
class CLifeLogo : public CLogo
{
public:
	CLifeLogo();															// コンストラクタ
	~CLifeLogo();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CLifeLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// ブロックロゴ初期化処理
	void Uninit(void);															// ブロックロゴ終了処理
	void Update(void);															// ブロックロゴ更新処理
	void Draw(void);															// ブロックロゴ描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
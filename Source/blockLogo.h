//=============================================================================
//
// ブロックロゴの処理 [blocLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _BLOCKLOGO_H_
#define _BLOCKLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BLOCK_LOGO_NAME		"data/TEXTURE/UI/BLOCK.png"			// ブロックロゴのテクスチャ名

//=========================
// スコアロゴクラス
//=========================
class CBlockLogo : public CLogo
{
public:
	CBlockLogo();															// コンストラクタ
	~CBlockLogo();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CBlockLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// ブロックロゴ初期化処理
	void Uninit(void);															// ブロックロゴ終了処理
	void Update(void);															// ブロックロゴ更新処理
	void Draw(void);															// ブロックロゴ描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
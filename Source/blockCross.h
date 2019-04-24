//=============================================================================
//
// ブロックの個数ロゴの処理 [blocCross.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _BLOCKCROSS_H_
#define _BLOCKCROSS_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BLOCKCROSS_LOGO_NAME		"data/TEXTURE/UI/blockCross.png"			// ブロックの個数ロゴのテクスチャ名

//=========================
// スコアロゴクラス
//=========================
class CBlockCross : public CLogo
{
public:
	CBlockCross();															// コンストラクタ
	~CBlockCross();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CBlockCross *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// ブロックロゴ初期化処理
	void Uninit(void);															// ブロックロゴ終了処理
	void Update(void);															// ブロックロゴ更新処理
	void Draw(void);															// ブロックロゴ描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
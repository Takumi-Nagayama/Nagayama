//=============================================================================
//
// ランキングのテクスチャの処理 [rankTex.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _RANKTEX_H_
#define _RANKTEX_H_

#include "main.h"
#include "logo.h"

//=============================================================================
// 前方宣言
//=============================================================================

//=====================
// リザルトロゴクラス
//=====================
class CRankTex : public CLogo
{
public:
	CRankTex();																// コンストラクタ
	~CRankTex();															// デストラクタ

	static HRESULT Load(void);												// テクスチャ読み込み
	static void Unload(void);												// テクスチャ解放

	static CRankTex *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// ランキングのテクスチャを生成

	HRESULT Init(void);				// ランキングのテクスチャ初期化処理
	void Uninit(void);														// ランキングのテクスチャ終了処理
	void Update(void);														// ランキングのテクスチャ更新処理
	void Draw(void);														// ランキングのテクスチャ描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
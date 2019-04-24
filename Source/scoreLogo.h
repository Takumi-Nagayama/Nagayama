//=============================================================================
//
// スコアロゴの処理 [scoreLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _SCORELOGO_H_
#define _SCORELOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_LOGO_NAME		"data/TEXTURE/UI/SCORE.png"			// チュートリアルロゴのテクスチャ名

//=========================
// スコアロゴクラス
//=========================
class CScoreLogo : public CLogo
{
public:
	CScoreLogo();															// コンストラクタ
	~CScoreLogo();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CScoreLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// スコアロゴ初期化処理
	void Uninit(void);															// スコアロゴ終了処理
	void Update(void);															// スコアロゴ更新処理
	void Draw(void);															// スコアロゴ描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
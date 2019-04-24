//=============================================================================
//
// ランキングロゴの処理 [rankingLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _RANKINGLOGO_H_
#define _RANKINGLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKING_LOGO_NAME		"data/TEXTURE/RANKING/ranking.png"			// チュートリアルロゴのテクスチャ名

//=========================
// チュートリアルロゴクラス
//=========================
class CRankingLogo : public CLogo
{
public:
	CRankingLogo();															// コンストラクタ
	~CRankingLogo();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CRankingLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// チュートリアルロゴ初期化処理
	void Uninit(void);															// チュートリアルロゴ終了処理
	void Update(void);															// チュートリアルロゴ更新処理
	void Draw(void);															// チュートリアルロゴ描x画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
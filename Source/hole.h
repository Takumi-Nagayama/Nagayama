//=============================================================================
//
// 穴の処理 [hole.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _HOLE_H_
#define _HOLE_H_

#include "main.h"
#include "polygon.h"
#include "scene3D.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_DEBRIS		"data/TEXTURE/woodDebris.png"	// 木の破片のテクスチャ
#define EFFECT_STAR_NAME	"data/TEXTURE/effect001.jpg"	// 星エフェクトのテクスチャ名

//========================================
// クラスの定義
//========================================
//=====================
// 穴クラス
//=====================
class CHole : public CPolygon
{
public:
	CHole();	// コンストラクタ
	~CHole();	// デストラクタ

	HRESULT Init(void);	// 穴初期化処理
	void Uninit(void);	// 穴終了処理
	void Update(void);	// 穴更新処理
	void Draw(void);	// 穴描画処理

	static CHole *Create(D3DXVECTOR3 pos, float fDepth, float fWifth);	// オブジェクトの生成
	static HRESULT Load(void);	// テクスチャ読み込み
	static void Unload(void);	// テクスチャ解放

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nLife;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
};

#endif
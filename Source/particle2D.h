//=============================================================================
//
// パーティクルの処理 [particle2D.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PARTICLE2D_H_
#define _PARTICLE2D_H_

#include "main.h"
#include "scene2D.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PARTICLE2D	(126)							// パーティクルの数
#define EFFECT_NAME		"data/TEXTURE/effect000.jpg"	// エフェクトのテクスチャ名

//========================================
// クラスの定義
//========================================
//=====================
// パーティクルクラス
//=====================
class CParticle2D : public CScene2D
{
public:
	CParticle2D(int nPriority = PARTICLE_PRIORITY, OBJTYPE objType = OBJTYPE_PARTICLE);	// コンストラクタ
	~CParticle2D();	// デストラクタ

	HRESULT Init(void);	// プレイヤー初期化処理
	void Uninit(void);	// プレイヤー終了処理
	void Update(void);	// プレイヤー更新処理
	void Draw(void);	// プレイヤー描画処理

	static CParticle2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight);	// オブジェクトの生成
	static HRESULT Load(void);	// テクスチャ読み込み
	static void Unload(void);	// テクスチャ解放

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nLife;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;
};

#endif
//=============================================================================
//
// 地面ポリゴン処理 [field.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GROUND_TEXTURE_NAME			"data\\TEXTURE\\soil001.jpg"	// 地面のテクスチャ名
#define NUM_VTX						(4)								// 頂点の数
//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CFeild : public CPolygon
{
public:
	CFeild();											// コンストラクタ
	~CFeild();										// デストラクタ

	HRESULT Init(void);							// 3Dオブジェクト初期化処理
	void Uninit(void);							// 3Dオブジェクト終了処理
	void Update(void);							// 3Dオブジェクト更新処理
	void Draw(void);							// 3Dオブジェクト描画処理

	static CFeild *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV);			// オブジェクトの生成
	static HRESULT Load(void);	// テクスチャ読み込み
	static void Unload(void);	// テクスチャ解放

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;					// ワールドマトリックス
};

#endif
//=============================================================================
//
// ナンバー処理 [number.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	SCORE_NAME	"data/TEXTURE/number_02.png"		// スコアのテクスチャ名

//========================================
// クラスの定義
//========================================
//=====================
// ナンバークラス
//=====================
class CNumber
{
public:
	CNumber();												// コンストラクタ
	~CNumber();												// デストラクタ

	static HRESULT Load(void);								// テクスチャ読み込み
	static void UnLoad(void);								// テクスチャ解放

	static CNumber *Create(D3DXVECTOR3 pos, float fSize);	// ナンバーの生成

	HRESULT Init(D3DXVECTOR3 pos, float fSize);				// 初期化
	void Uninit(void);										// 終了
	void Update(void);										// 更新
	void Draw(void);										// 描画
	void SetNumber(int nNumber);							// テクスチャ設定
	void SetColor(D3DXCOLOR color);							// 色の設定

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;					// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;
};

#endif
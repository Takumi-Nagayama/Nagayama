//=============================================================================
//
// ブロックの数処理 [NumBlock.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _NUMBLOCK_H_
#define _NUMBLOCK_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUMBLOCK	(2)	// テクスチャの数
#define MAX_SET_BLOCK	(10)									// ブロック最大数

//=============================================================================
// 前方宣言
//=============================================================================
class CNumber;

//========================================
// クラスの定義
//========================================
//=====================
// ブロックの数クラス
//=====================
class CNumBlock : public CScene
{
public:
	CNumBlock(int nPriority = 5, OBJTYPE objType = OBJTYPE_SCORE);	// コンストラクタ
	~CNumBlock();													// デストラクタ

	static CNumBlock *Create(D3DXVECTOR3 pos, float fSize);

	HRESULT Init(void);							// ブロックの数の初期化処理
	void Uninit(void);							// ブロックの数の終了処理
	void Update(void);							// ブロックの数の更新処理
	void Draw(void);							// ブロックの数の描画処理

	void SetBlock(int nBlock);					// ブロックの数の設定
	int GetBlock(void);							// ブロックの数の取得
	void AddBlock(int nValue);					// ブロックの数加算
	void SetColor(D3DXCOLOR color);				// 色の設定

private:
	CNumber *m_apNumber[MAX_NUMBLOCK];
	D3DXVECTOR3 m_pos;
	int m_nNumBlock;
	float m_fSize;
};

#endif
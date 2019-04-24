//=============================================================================
//
// チュートリアルで使うロゴの処理 [tutorialLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _TUTORIALLOGO_H_
#define _TUTORIALLOGO_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_TEXTURE_NAME			"data\\TEXTURE\\TUTORIAL\\move.png"		// 移動方法のテクスチャ名
#define JUMP_TEXTURE_NAME			"data\\TEXTURE\\TUTORIAL\\jump.png"		// ジャンプ方法のテクスチャ名
#define SET_TEXTURE_NAME			"data\\TEXTURE\\TUTORIAL\\set.png"		// 設置方法のテクスチャ名
#define DESTROY_TEXTURE_NAME		"data\\TEXTURE\\TUTORIAL\\destroy.png"	// 破壊方法のテクスチャ名
#define END_TEXTURE_NAME			"data\\TEXTURE\\TUTORIAL\\end.png"		// 終了のテクスチャ名
#define NUM_VTX						(4)										// 頂点の数

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CTutorialLogo : public CPolygon
{
public:
	typedef enum
	{// プレイヤーの状態
		TYPE_MOVE = 0,	// 移動方法のテクスチャ
		TYPE_JUMP,		// ジャンプ方法のテクスチャ
		TYPE_SET,		// 設置方法のテクスチャ
		TYPE_DESTROY,	// 破壊方法のテクスチャ
		TYPE_END,		// 終了のテクスチャ
		TYPE_MAX		// テクスチャの種類の総数
	} TEX_TYPE;

	CTutorialLogo();											// コンストラクタ
	~CTutorialLogo();										// デストラクタ

	HRESULT Init(void);							// チュートリアルで使うロゴ初期化処理
	void Uninit(void);							// チュートリアルで使うロゴ終了処理
	void Update(void);							// チュートリアルで使うロゴ更新処理
	void Draw(void);							// チュートリアルで使うロゴ描画処理

	static CTutorialLogo *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV, TEX_TYPE type);			// オブジェクトの生成
	static HRESULT Load(void);	// テクスチャ読み込み
	static void Unload(void);	// テクスチャ解放

private:
	static LPDIRECT3DTEXTURE9		m_apTexture[TYPE_MAX];					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;					// ワールドマトリックス
	TEX_TYPE				m_Type;
};

#endif
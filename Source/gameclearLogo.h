//=============================================================================
//
// ゲームクリアロゴの処理 [gameclearLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _GAMECLEARLOGO_H_
#define _GAMECLEARLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMECLEAR_LOGO_NAME		"data/TEXTURE/RESULT/gameclear.png"			// ゲームクリアロゴのテクスチャ名

//=========================
// ゲームクリアロゴクラス
//=========================
class CGameClearLogo : public CLogo
{
public:
	CGameClearLogo();															// コンストラクタ
	~CGameClearLogo();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CGameClearLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// ゲームクリアロゴ初期化処理
	void Uninit(void);															// ゲームクリアロゴ終了処理
	void Update(void);															// ゲームクリアロゴ更新処理
	void Draw(void);															// ゲームクリアロゴ描x画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
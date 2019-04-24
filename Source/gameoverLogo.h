//=============================================================================
//
// ゲームオーバーロゴの処理 [gameoverLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _GAMEOVERLOGO_H_
#define _GAMEOVERLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMEOVER_LOGO_NAME		"data/TEXTURE/RESULT/gameover.png"			// ゲームオーバーロゴのテクスチャ名

//=========================
// ゲームオーバーロゴクラス
//=========================
class CGameOverLogo : public CLogo
{
public:
	CGameOverLogo();															// コンストラクタ
	~CGameOverLogo();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CGameOverLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// ゲームオーバーロゴ初期化処理
	void Uninit(void);															// ゲームオーバーロゴ終了処理
	void Update(void);															// ゲームオーバーロゴ更新処理
	void Draw(void);															// ゲームオーバーロゴ描x画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
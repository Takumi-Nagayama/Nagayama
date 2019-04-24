//=============================================================================
//
// タイトルロゴの処理 [titleLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_LOGO_NAME			"data/TEXTURE/TITLE/title001.png"		// タイトルロゴのテクスチャ名

//=====================
// タイトルロゴクラス
//=====================
class CTitleLogo : public CLogo
{
public:
	CTitleLogo();																// コンストラクタ
	~CTitleLogo();																// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CTitleLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init();																// タイトルロゴ初期化処理
	void Uninit(void);															// タイトルロゴ終了処理
	void Update(void);															// タイトルロゴ更新処理
	void Draw(void);															// タイトルロゴ描x画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
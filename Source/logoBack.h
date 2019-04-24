//=============================================================================
//
// 背景ロゴの処理 [logoBack.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _LOGOBACK_H_
#define _LOGOBACK_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOGOBACK_NAME		"data/TEXTURE/logoBack001.png"			// 背景ロゴのテクスチャ名

//=========================
// チュートリアルロゴクラス
//=========================
class CLogoBack : public CLogo
{
public:
	CLogoBack();															// コンストラクタ
	~CLogoBack();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CLogoBack *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// チュートリアルロゴ初期化処理
	void Uninit(void);															// チュートリアルロゴ終了処理
	void Update(void);															// チュートリアルロゴ更新処理
	void Draw(void);															// チュートリアルロゴ描x画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPause;

//========================================
// クラスの定義
//========================================
//=====================
// レンダリングクラス
//=====================
class CRenderer
{
public:
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ
	
	HRESULT Init(HWND hWnd, bool bWindow);	// レンダラーの初期化処理
	void Uninit(void);						// レンダラーの終了処理
	void Update(void);						// レンダラーの更新処理
	void Draw(void);						// レンダラーの描画処理

	LPDIRECT3DDEVICE9 GetDevice(void); /*{ return m_pD3DDevice; }*/

private:
//#ifdef _DEBUG
//	void DrawFPS(void);
//#endif

	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	static CPause *m_pPause;
	bool m_bPause;
//#ifdef _DEBUG
//	LPD3DXFONT				m_pFont;			// フォントへのポインタ
//#endif
};

#endif
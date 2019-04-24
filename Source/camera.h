//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//========================================
// クラスの定義
//========================================
//=====================
// カメラクラス
//=====================
class CCamera
{
public:

	CCamera();		// コンストラクタ
	~CCamera();		// デストラクタ

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	D3DXVECTOR3 GetRot(void);						// 位置の取得
	static bool GetGem(void);						// 宝石を取れる状態かの取得

private:
	D3DXVECTOR3 m_posV;				// 視点
	D3DXVECTOR3 m_posR;				// 注視点
	D3DXVECTOR3 m_posVDest;			// 目的の視点
	D3DXVECTOR3 m_posRDest;			// 目的の注視点
	D3DXVECTOR3 m_recU;				// 上方向ベクトル
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 m_rotDest;			// 目標の向き
	D3DXVECTOR3 m_DiffAngle;			// 角度の差分
	float m_fLength;				// 注視点からの距離
	static bool m_bGem;					// 宝石を獲得しているか状態どうか
	int m_nGemTimer;				// カメラワークに使うカウンター
	//float fAngle;				
	D3DXMATRIX	m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX	m_mtxView;			// ビューマトリックス
};

#endif
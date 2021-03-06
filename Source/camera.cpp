//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "player.h"
#include "game.h"
#include "gem.h"
#include "coin.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_SPEED	(4.0f)
#define GEM_TIMER		(100)
#define GEM_V			(D3DXVECTOR3(1160.0f, 100.0f, 1000.0f))	// 宝石のカメラの位置
#define GEM_R			(D3DXVECTOR3(1160.0f, 20.0f, 720.0f))	// 宝石のカメラの位置
#define DEST_R			(20.0f)	// 注視点のずれ
#define DEST_R_Y		(40.0f)	// 注視点のずれ

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
bool CCamera::m_bGem = false;

//=============================================================================
// カメラクラスのコンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 注視点
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的の視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的の注視点
	m_recU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的の向き
	m_fLength = 0.0f;
	m_nGemTimer = 0;
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 120.0f, -220.0f);	// 視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 注視点
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的の視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的の注視点
	m_recU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的の向き
	m_DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));
	m_nGemTimer = 0;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Update(void)
{
	CManager::MODE mode;
	mode = CManager::GetMode();

	if (mode == CManager::MODE_GAME || mode == CManager::MODE_TUTORIAL)
	{
		if (m_bGem == true && mode == CManager::MODE_GAME)
		{ 
			GemCamera();
		}
		else
		{// 宝石が取れる状態じゃないとき

			if (mode == CManager::MODE_GAME)
			{
				if (m_nGemTimer < GEM_TIMER)
				{
					int nNumCoin = CCoin::GetNumCoin();

					if (nNumCoin <= 0)
					{
						m_bGem = true;

						m_nGemTimer = 0;
					}
				}
			}

			PlayerCamera();
		}
	}

	if (mode == CManager::MODE_TITLE)
	{
		m_posV = D3DXVECTOR3(700.0f, -100.0f, -1500.0f);	// 視点
		m_posR = D3DXVECTOR3(700.0f, -100.0f, 0.0f);		// 注視点
	}
	if (mode == CManager::MODE_RANKING)
	{
		m_posV = D3DXVECTOR3(1010.0f, -330.0f, -1600.0f);	// 視点
		m_posR = D3DXVECTOR3(1010.0f, -330.0f, -100.0f);		// 注視点
	}
	if (mode == CManager::MODE_GAMECLEAR || mode == CManager::MODE_GAMEOVER)
	{
		m_posV = D3DXVECTOR3(1010.0f, -330.0f, -2500.0f);	// 視点
		m_posR = D3DXVECTOR3(1010.0f, -330.0f, -1000.0f);		// 注視点
	}
#ifdef _DEBUG
	CDebugProc::Print("cfccfccfc", "posV     : x", m_posV.x, "f", "   y", m_posV.y, "f", " z", m_posV.z, "f");
#endif
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	// デバイスの取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),						// 視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// 画面比率	
		100.0f,										// カメラからの距離（手前）
		10000.0f);									// カメラからの距離（奥）

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_recU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================================================================
// 宝石を映す
//=============================================================================
void CCamera::GemCamera(void)
{
	CManager::MODE mode;
	mode = CManager::GetMode();

	m_nGemTimer++;

	if (m_nGemTimer < GEM_TIMER)
	{
		if (mode == CManager::MODE_GAME)
		{
			m_posV = GEM_V;	// 視点
			m_posR = GEM_R;		// 注視点
		}
		else if (mode == CManager::MODE_TUTORIAL)
		{
			//m_posV = D3DXVECTOR3(100.0f, 200.0f, 1700.0f);	// 視点
			//m_posR = D3DXVECTOR3(0.0f, 20.0f, 1500.0f);		// 注視点
		}
	}
	else
	{
		m_bGem = false;
	}
}

//=============================================================================
// 角度の設定
//=============================================================================
void CCamera::SetAngle(void)
{
	if (m_DiffAngle.y > D3DX_PI)
	{
		m_DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (m_DiffAngle.y < -D3DX_PI)
	{
		m_DiffAngle.y += D3DX_PI * 2.0f;
	}
	//
	m_rot.y += m_DiffAngle.y * 0.2f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// プレイヤー追従処理
//=============================================================================
void CCamera::PlayerCamera(void)
{
	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得(モデルの優先順位が1だから、1にあるオブジェクトをすべて見る)
	pScene = CScene::GetTop(PLAYER_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
			{// オブジェクトの種類を確かめる
			 // デバック用
#if 0
				if (pInputKeyboard->GetPress(DIK_LEFT) == true)
				{// 左方向に移動
					if (pInputKeyboard->GetPress(DIK_UP) == true)
					{// 左奥に移動
						m_posV.x -= sinf(m_rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;
						m_posV.z -= cosf(m_rot.y + D3DX_PI * 0.75f) * CAMERA_SPEED;

						m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
						m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
					}
					else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
					{// 左手前移動
						m_posV.x -= sinf(m_rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;
						m_posV.z -= cosf(m_rot.y + D3DX_PI * 0.25f) * CAMERA_SPEED;

						m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
						m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
					}
					else
					{// 左
						m_posV.x -= sinf(m_rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;
						m_posV.z -= cosf(m_rot.y + D3DX_PI * 0.5f) * CAMERA_SPEED;

						m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
						m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
					}
				}
				else if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
				{// 右方向に移動
					if (pInputKeyboard->GetPress(DIK_UP) == true)
					{// 右前移動
						m_posV.x -= sinf(m_rot.y - D3DX_PI * 0.75f) * CAMERA_SPEED;
						m_posV.z -= cosf(m_rot.y - D3DX_PI * 0.75f) * CAMERA_SPEED;

						m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
						m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
					}
					else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
					{// 右後ろ移動
						m_posV.x -= sinf(m_rot.y - D3DX_PI * 0.25f) * CAMERA_SPEED;
						m_posV.z -= cosf(m_rot.y - D3DX_PI * 0.25f) * CAMERA_SPEED;

						m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
						m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
					}
					else
					{// 右
						m_posV.x -= sinf(m_rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;
						m_posV.z -= cosf(m_rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;

						m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
						m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
					}
				}
				else if (pInputKeyboard->GetPress(DIK_UP) == true)
				{// 前方向に移動
					m_posV.x += sinf(m_rot.y) * CAMERA_SPEED;
					m_posV.z += cosf(m_rot.y) * CAMERA_SPEED;

					m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
					m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
				}
				else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
				{// 手前方向に移動
					m_posV.x -= sinf(m_rot.y) * CAMERA_SPEED;
					m_posV.z -= cosf(m_rot.y) * CAMERA_SPEED;

					m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
					m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
				}

				// 注視点回転
				if (pInputKeyboard->GetPress(DIK_Q) == true)
				{// 左方向に回転
					m_rot.y -= 0.03f;

					if (m_rot.y < -D3DX_PI)
					{
						m_rot.y += D3DX_PI * 2.0f;
					}

					m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
					m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
				}
				else if (pInputKeyboard->GetPress(DIK_E) == true)
				{// 左方向に回転
					m_rot.y += 0.03f;

					if (m_rot.y > D3DX_PI)
					{
						m_rot.y -= D3DX_PI * 2.0f;
					}

					m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
					m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
				}
				else if (pInputKeyboard->GetPress(DIK_T) == true)
				{// 上
					m_rot.x += 3.0f;

					m_posR.y = m_rot.x;
				}
				else if (pInputKeyboard->GetPress(DIK_B) == true)
				{// 下
					m_rot.x -= 3.0f;

					m_posR.y = m_rot.x;
				}

				// 視点回転
				if (pInputKeyboard->GetPress(DIK_Z) == true)
				{// 左方向に回転
					m_rot.y -= 0.03f;

					if (m_rot.y < -D3DX_PI)
					{
						m_rot.y += D3DX_PI * 2.0f;
					}

					m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y) * m_fLength;
					m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y) * m_fLength;
				}
				else if (pInputKeyboard->GetPress(DIK_C) == true)
				{// 左方向に回転
					m_rot.y += 0.03f;

					if (m_rot.y > D3DX_PI)
					{
						m_rot.y -= D3DX_PI * 2.0f;
					}

					m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y) * m_fLength;
					m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y) * m_fLength;
				}
				else if (pInputKeyboard->GetPress(DIK_Y) == true)
				{// 上
					m_posV.y += 3.0f;
				}
				else if (pInputKeyboard->GetPress(DIK_N) == true)
				{// 下
					m_posV.y -= 3.0f;
				}
#endif
#if 1
				m_posRDest.x = ((CPlayer*)pScene)->GetPos().x - sinf(((CPlayer*)pScene)->GetRot().y) * DEST_R;
				m_posRDest.z = ((CPlayer*)pScene)->GetPos().z - cosf(((CPlayer*)pScene)->GetRot().y) * DEST_R;
				//
				m_posVDest.x = ((CPlayer*)pScene)->GetPos().x - sinf(m_rot.y) * m_fLength;
				m_posVDest.y = ((CPlayer*)pScene)->GetPos().y - sinf(m_rot.x) * m_fLength;
				m_posVDest.z = ((CPlayer*)pScene)->GetPos().z - cosf(m_rot.y) * m_fLength;

				//減速
				m_posR.x += (m_posRDest.x - m_posR.x) * 0.2f + ((CPlayer*)pScene)->GetMove().x;
				m_posR.z += (m_posRDest.z - m_posR.z) * 0.2f + ((CPlayer*)pScene)->GetMove().z;

				if (((CPlayer*)pScene)->GetPos().y > -100.0f)
				{
					m_posRDest.y = ((CPlayer*)pScene)->GetPos().y - sinf(((CPlayer*)pScene)->GetRot().x) * DEST_R_Y;
					m_posR.y += (m_posRDest.y - m_posR.y) * 0.2f + 10.0f;
					m_posV.y += ((m_posVDest.y - m_posV.y) * 0.2f) + 20.0f;
				}

				m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y) * m_fLength;
				m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y) * m_fLength;

				// 入力情報を取得
				CInputJoypad *pInputJoypad;
				pInputJoypad = CManager::GetInputJoypad();

				// 入力情報を取得
				CInputKeyboard *pInputKeyboard;
				pInputKeyboard = CManager::GetInputKeyboard();

				// 視点回転
				if (pInputKeyboard->GetPress(DIK_Q) == true || pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_RS_RIGHT) == true)
				{// 左方向に回転
					m_rotDest.y -= 0.03f;

					if (m_rotDest.y < -D3DX_PI)
					{
						m_rotDest.y += D3DX_PI * 2.0f;
					}

					m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y) * m_fLength;
					m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y) * m_fLength;
				}
				else if (pInputKeyboard->GetPress(DIK_E) == true || pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_RS_LEFT) == true)
				{// 左方向に回転
					m_rotDest.y += 0.03f;

					if (m_rotDest.y > D3DX_PI)
					{
						m_rotDest.y -= D3DX_PI * 2.0f;
					}

					m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y) * m_fLength;
					m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y) * m_fLength;
				}

				if (pInputKeyboard->GetTrigger(DIK_C) == true)
				{
					//カメラをプレイヤーの後ろにする
					m_rotDest.y = (((CPlayer*)pScene)->GetRot().y + D3DX_PI);
					m_rotDest.x = (((CPlayer*)pScene)->GetRot().x + D3DX_PI);
					m_rotDest.z = (((CPlayer*)pScene)->GetRot().z + D3DX_PI);


					//カメラとプレイヤーの距離を求める		
					m_DiffAngle.x = m_rotDest.x - m_rot.x;
					m_DiffAngle.y = m_rotDest.y - m_rot.y;
					m_DiffAngle.z = m_rotDest.z - m_rot.z;

					//角度の設定
					SetAngle();
				}

				//向きの慣性
				m_DiffAngle.y = m_rotDest.y - m_rot.y;

				//角度の設定
				SetAngle();
#endif
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}
}

//=============================================================================
// 向きの取得
//=============================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 宝石を取れる状態かの取得
//=============================================================================
bool CCamera::GetGem(void)
{
	return m_bGem;
}
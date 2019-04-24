//=============================================================================
//
// コイン処理 [coin.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "coin.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COIN_NAME		"data\\MODEL\\coin.x"	// コインのモデル名
#define ROTATION_SPEED	(0.05f)					// コインの回転スピード

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CCoin::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CCoin::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CCoin::m_nNumMat = 0;			// マテリアル情報の数
int CCoin::m_nNumCoin = 0;			// コインの数

//=============================================================================
// コインクラスのコンストラクタ
//=============================================================================
CCoin::CCoin() : CSceneX(COIN_PRIORITY)
{
	// 値をクリア
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CCoin::~CCoin()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CCoin *CCoin::Create(D3DXVECTOR3 pos)
{
	CCoin *pCoin = NULL;

	if (pCoin == NULL)
	{
		// オブジェクトクラスの生成
		pCoin = new CCoin;

		if (pCoin != NULL)
		{
			pCoin->SetPosition(pos);
			pCoin->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pCoin->Init();

			m_nNumCoin++;
		}
	}

	return pCoin;
}

//=============================================================================
// コイン初期化処理
//=============================================================================
HRESULT CCoin::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_COIN);

	// 初期化処理
	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// コイン終了処理
//=============================================================================
void CCoin::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// コイン更新処理
//=============================================================================
void CCoin::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームのモードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 位置を取得
	m_pos = CSceneX::GetPosition();

	m_rot.y += ROTATION_SPEED;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	
	SetRot(m_rot);
	
	SetPosition(m_pos);

#ifdef _DEBUG
	//CDebugProc::Print("cn", "コインの数 : ", m_nNumCoin);
#endif
}

//=============================================================================
// コイン描画処理
//=============================================================================
void CCoin::Draw(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点法線の自動正規化	開始
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// 頂点法線の自動正規化	終了
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// コインとの当たり判定処理
//=============================================================================
bool CCoin::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// 当たっていない状態

	// 中心と中心の差を求める
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - CSceneX::GetPosition().x, pos->y - CSceneX::GetPosition().y - 20.0f, pos->z - CSceneX::GetPosition().z);

	// 中心から中心のベクトルの長さを算出
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
	{// 長さが半径の和より小さければ当たっている
		bHit = true;
	}

	return bHit;	// コインに当たっているかどうかを返す
}

//=============================================================================
// コインのモデル読み込み処理
//=============================================================================
HRESULT CCoin::LoadModel(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(COIN_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// コインのモデル解放処理
//=============================================================================
void CCoin::UnloadModel(void)
{
	// メッシュの開放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの開放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CCoin::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CCoin::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// コインの数の取得
//=============================================================================
int CCoin::GetNumCoin(void)
{
	return m_nNumCoin;
}

//=============================================================================
// コインの数の設定
//=============================================================================
void CCoin::SetNumCoin(int nNumCoin)
{
	m_nNumCoin = nNumCoin;
}
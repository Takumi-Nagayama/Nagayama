//=============================================================================
//
// 障害物の処理 [obstacle.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "obstacle.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "bullet.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBSTACLE_NAME	"data\\MODEL\\obstacle.x"	// 障害物のモデル名
#define OBSTACLESIZE	(15.0f)					// 障害物のサイズ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CObstacle::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CObstacle::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CObstacle::m_nNumMat = 0;			// マテリアル情報の数

//=============================================================================
// プレイヤークラスのコンストラクタ
//=============================================================================
CObstacle::CObstacle() : CSceneX(3)
{
	// 値をクリア
	m_pTexture = NULL;						// テクスチャへのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックス
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CObstacle::~CObstacle()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CObstacle *CObstacle::Create(D3DXVECTOR3 pos)
{
	CObstacle *pObstacle = NULL;

	if (pObstacle == NULL)
	{
		// オブジェクトクラスの生成
		pObstacle = new CObstacle;

		if (pObstacle != NULL)
		{
			pObstacle->SetPosition(pos);
			pObstacle->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pObstacle->Init();
		}
	}

	return pObstacle;
}

//=============================================================================
// 障害物初期化処理
//=============================================================================
HRESULT CObstacle::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_OBSTACLE);

	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// 障害物終了処理
//=============================================================================
void CObstacle::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// 障害物更新処理
//=============================================================================
void CObstacle::Update(void)
{
}

//=============================================================================
// 障害物描画処理
//=============================================================================
void CObstacle::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// 障害物のモデル読み込み処理
//=============================================================================
HRESULT CObstacle::LoadObstacle(void)
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
	D3DXLoadMeshFromX(OBSTACLE_NAME,
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
// 障害物のモデル解放処理
//=============================================================================
void CObstacle::UnloadObstacle(void)
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
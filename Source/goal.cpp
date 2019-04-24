//=============================================================================
//
// ゴール処理 [goal.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "goal.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GOAL_NAME	"data\\MODEL\\goal.x"	// ゴールのモデル名
#define GOAL_SIZE	(5.0f)					// ゴールの大きさの微調節

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CGoal::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CGoal::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CGoal::m_nNumMat = 0;				// マテリアル情報の数

//=============================================================================
// ゴールクラスのコンストラクタ
//=============================================================================
CGoal::CGoal() : CSceneX(GOAL_PRIORITY)
{
	// 値をクリア
	m_pTexture = NULL;						// テクスチャへのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックス
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
}

//=============================================================================
// デストラクタ
//=============================================================================
CGoal::~CGoal()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos)
{
	CGoal *pGoal = NULL;

	if (pGoal == NULL)
	{
		// オブジェクトクラスの生成
		pGoal = new CGoal;

		if (pGoal != NULL)
		{
			pGoal->SetPosition(pos);
			pGoal->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pGoal->Init();
		}
	}

	return pGoal;
}

//=============================================================================
// ゴール初期化処理
//=============================================================================
HRESULT CGoal::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_GOAL);

	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// ゴール終了処理
//=============================================================================
void CGoal::Uninit(void)
{
	CSceneX::Uninit();

	// プレイヤー自体の解放
	Release();
}

//=============================================================================
// ゴール更新処理
//=============================================================================
void CGoal::Update(void)
{
}

//=============================================================================
// ゴール描画処理
//=============================================================================
void CGoal::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// ゴールのモデル読み込み処理
//=============================================================================
HRESULT CGoal::LoadModel(void)
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
	D3DXLoadMeshFromX(GOAL_NAME,
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
// ゴールのモデル解放処理
//=============================================================================
void CGoal::UnloadModel(void)
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
// ゴールとの当たり判定処理
//=============================================================================
bool CGoal::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{
	bool bGoal = false;	// ゴールしていない状態

	D3DXVECTOR3 GoalPos = CSceneX::GetPosition();
	D3DXVECTOR3 GoalMax = CSceneX::GetVtxMax();
	D3DXVECTOR3 GoalMin = CSceneX::GetVtxMin();

	if (pos->y <= GoalPos.y + GoalMax.y - GOAL_SIZE && pos->y + radius.y >= GoalPos.y + GoalMax.y - GOAL_SIZE
		|| pos->y + radius.y >= GoalPos.y + GoalMin.y && pos->y <= GoalPos.y + GoalMin.y
		|| pos->y + radius.y <= GoalPos.y + GoalMax.y - GOAL_SIZE && pos->y >= GoalPos.y + GoalMin.y)
	{// yの範囲の中
		if (pos->z - radius.z <= GoalPos.z + GoalMax.z && pos->z + radius.z >= GoalPos.z + GoalMin.z)
		{// zの範囲の中
			if (posOld->x + radius.x <= GoalPos.x + GoalMin.x
				&& pos->x + radius.x > GoalPos.x + GoalMin.x)
			{// X座標の中に左から入った
				bGoal = true;
				pos->x = posOld->x;
				move->x = 0.0f;
			}
			else if (posOld->x - radius.x >= GoalPos.x + GoalMax.x
				&& pos->x - radius.x < GoalPos.x + GoalMax.x)
			{// X座標の中に右から入った
				bGoal = true;
				pos->x = posOld->x;
				move->x = 0.0f;
			}
		}
		if (pos->x - radius.x <= GoalPos.x + GoalMax.x && pos->x + radius.x >= GoalPos.x + GoalMin.x)
		{// xの範囲の中
			if (posOld->z + radius.z <= GoalPos.z + GoalMin.z
				&& pos->z + radius.z > GoalPos.z + GoalMin.z)
			{// Z座標の中に手前から入った
				bGoal = true;
				pos->z = posOld->z;
				move->z = 0.0f;
			}
			else if (posOld->z - radius.z >= GoalPos.z + GoalMax.z
				&& pos->z - radius.z < GoalPos.z + GoalMax.z)
			{// Z座標の中に後ろから入った
				bGoal = true;
				pos->z = posOld->z;
				move->z = 0.0f;
			}
		}
	}

	if (pos->x - radius.x < GoalPos.x + GoalMax.x - GOAL_SIZE && pos->x + radius.x > GoalPos.x + GoalMin.x + GOAL_SIZE
		&& pos->z - radius.z <= GoalPos.z + GoalMax.z - GOAL_SIZE && pos->z + radius.x >= GoalPos.z + GoalMin.z + GOAL_SIZE)
	{// 障害物の内側に乗った
		if (posOld->y >= GoalPos.y + GoalMax.y && pos->y < GoalPos.y + GoalMax.y
			|| pos->y <= GoalPos.y + GoalMax.y && posOld->y > GoalPos.y + GoalMax.y)
		{// 上からブロックに当たったとき
			bGoal = true;
			pos->y = GoalPos.y + GoalMax.y;
			move->y = 0.0f;  // 移動量をなくす
		}

		if (posOld->y + radius.y < GoalPos.y + GoalMin.y && pos->y + radius.y >= GoalPos.y + GoalMin.y
			|| pos->y + radius.y > GoalPos.y + GoalMin.y && posOld->y + radius.y <= GoalPos.y + GoalMin.y)
		{// 下からブロックに当たったとき
			bGoal = true;
			pos->y = GoalPos.y + GoalMin.y - radius.y;
			move->y = 0.0f;  // 移動量をなくす
		}
	}

	return bGoal;	// ブロックに乗っているかどうかを返す
}
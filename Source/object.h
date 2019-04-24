//=============================================================================
//
// 3Dモデル処理 [object.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "sceneObject.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SETOBJECT	(200)	// 置けるモデルの最大数
#define OBJECT_FILE_GAME	"data\\TEXT\\modelGame.txt"	// 設置したモデルを書き出すテキスト
#define OBJECT_FILE_TUTORIAL	"data\\TEXT\\modelTutorial.txt"	// 設置したモデルを書き出すテキスト
#define OBJECT_FILE_TITLE	"data\\TEXT\\modelTitle.txt"	// 設置したモデルを書き出すテキスト
#define OBJECT_FILE_GAMECLEAR	"data\\TEXT\\modelGameClear.txt"	// 設置したモデルを書き出すテキスト
#define OBJECT_FILE_GAMEOVER	"data\\TEXT\\modelGameOver.txt"	// 設置したモデルを書き出すテキスト
#define OBJECTNAME_FILE	"data\\TEXT\\modelName.txt"	// 設置したいモデルの名前を書く
#define MODEL_FILENAME	"MODEL_FILENAME = "	// 設置したいモデルの名前を書く

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CObject : public CSceneObject
{
public:
	typedef enum
	{// オブジェクトの種類
		SETOBJTYPE_BLOCK = 0,
		SETOBJTYPE_OBSTACLE,								// 障害物
		SETOBJTYPE_TREE,									// 木
		SETOBJTYPE_PLAMTREE,									// 木
		SETOBJTYPE_ROCK,									// 岩
		SETOBJTYPE_ROCK1,									// 岩
		SETOBJTYPE_ROCK2,									// 岩
		SETOBJTYPE_ROCK3,									// 岩
		SETOBJTYPE_ROCK4,									// 岩
		SETOBJTYPE_ROCK5,									// 岩
		SETOBJTYPE_ROCK6,									// 岩
		SETOBJTYPE_WOODBOX,									// 木箱
		SETOBJTYPE_LONGSTONE001,									// 木箱
		SETOBJTYPE_LONGSTONE002,									// 木箱
		SETOBJTYPE_DELETE,									// 消しゴム
		SETOBJTYPE_MAX										// 総数
	} SETOBJTYPE;

	CObject();												// コンストラクタ
	~CObject();												// デストラクタ

	HRESULT Init(void);										// 3Dオブジェクト初期化処理
	void Uninit(void);										// 3Dオブジェクト終了処理
	void Update(void);										// 3Dオブジェクト更新処理
	void Draw(void);										// 3Dオブジェクト描画処理

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SETOBJTYPE SetObjType);				// オブジェクトの生成

	D3DXVECTOR3 GetPos(void);								// 位置の取得
	void SetPos(D3DXVECTOR3 pos);							// 位置の設定

	D3DXVECTOR3 GetRot(void);								// 向きの取得
	void SetRot(D3DXVECTOR3 rot);							// 向きの設定

	void LoadFile(int nMode);

	static SETOBJTYPE GetObjType(void);

	HRESULT LoadModel(void);							// テクスチャ読み込み
	static void UnloadModel(void);							// テクスチャ解放

	static LPD3DXMESH GetMesh(SETOBJTYPE SetObjType);
	static LPD3DXBUFFER GetBuffMat(SETOBJTYPE SetObjType);
	static DWORD GetNumMat(SETOBJTYPE SetObjType);
	static LPDIRECT3DTEXTURE9 GetTexture(SETOBJTYPE SetObjType);

private:
	static LPDIRECT3DTEXTURE9	m_apTexture[SETOBJTYPE_MAX];	// テクスチャへのポインタ
	static LPD3DXMESH			m_apMesh[SETOBJTYPE_MAX];	// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER			m_apBuffMat[SETOBJTYPE_MAX];	// マテリアル情報へのポインタ
	static DWORD				m_anNumMat[SETOBJTYPE_MAX];	// マテリアル情報の数
	static SETOBJTYPE			m_SetObjType;
	static int					m_nModel;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXMATRIX					m_mtxWorld;					// ワールドマトリックス

	bool						m_bCollision;				// 設置したオブジェクトと当たっているかどうかに使う

	D3DXVECTOR3					m_pos;						// ポリゴンの位置
	D3DXVECTOR3					m_rot;						// 上方向ベクトル
	static char m_aFilenameModel[SETOBJTYPE_MAX][256];
};

#endif
//=============================================================================
//
// ブロックの出現位置表示処理 [blockPos.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _BLOCKPOS_H_
#define _BLOCKPOS_H_

#include "main.h"
#include "scene.h"
#include "polygon.h"

//*********************************************************************
// ブロックの出現位置表示クラスの定義
//*********************************************************************
class CBlockPos : public  CPolygon
{
public:

	CBlockPos();
	~CBlockPos();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CBlockPos *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV, D3DXCOLOR col);
	static HRESULT Load(void);
	static void UnLoad(void);

	//メンバ変数
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9			m_pTexture;	//テクスチャへのポインタ
	float								m_Height;

	D3DXVECTOR3							m_pos;							//位置
	D3DXVECTOR3							m_rot;							//向き
	D3DXCOLOR							m_col;
	D3DXMATRIX							m_mtxWorld;						//ワールドマトリックス
	float								m_fWidth, m_fDepth;				//幅　奥行き
};

#endif

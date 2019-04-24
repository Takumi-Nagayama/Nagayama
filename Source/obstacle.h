//=============================================================================
//
// ��Q���̏��� [obstacle.h]
// Author : ���R���
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"
#include "sceneX.h"

//========================================
// �N���X�̒�`
//========================================
//=====================
// �u���b�N�N���X
//=====================
class CObstacle : public CSceneX
{
public:
	CObstacle();								// �R���X�g���N�^
	~CObstacle();								// �f�X�g���N�^

	HRESULT Init(void);						// �v���C���[����������
	void Uninit(void);						// �v���C���[�I������
	void Update(void);						// �v���C���[�X�V����
	void Draw(void);						// �v���C���[�`�揈��

	static HRESULT LoadObstacle(void);				// �e�N�X�`���ǂݍ���
	static void UnloadObstacle(void);				// �e�N�X�`�����

	static CObstacle *Create(D3DXVECTOR3 pos);	// �I�u�W�F�N�g�̐���

private:
	static LPD3DXMESH		m_pMesh;			// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMat;			// �}�e���A�����̐�
	D3DXVECTOR3				m_rot;				// ����
	LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// �u���b�N�̍ŏ��l�A�ő�l
	bool					m_bLand;			// �u���b�N�ɏ���Ă��邩�ǂ���

	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
};

#endif
//=============================================================================
//
// ���Ώ��� [pebble.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PEBBLE_H_
#define _PEBBLE_H_

#include "main.h"
#include "sceneX.h"

//========================================
// �N���X�̒�`
//========================================
//=====================
// �u���b�N�N���X
//=====================
class CPebble : public CSceneX
{
public:
	CPebble();								// �R���X�g���N�^
	~CPebble();								// �f�X�g���N�^

	HRESULT Init(void);						// �v���C���[����������
	void Uninit(void);						// �v���C���[�I������
	void Update(void);						// �v���C���[�X�V����
	void Draw(void);						// �v���C���[�`�揈��

	static HRESULT LoadModel(void);				// �e�N�X�`���ǂݍ���
	static void UnloadModel(void);				// �e�N�X�`�����

	static HRESULT LoadMat(void);				// �}�e���A���ǂݍ���
	static void UnloadMat(void);				// �}�e���A�����

	static CPebble *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �I�u�W�F�N�g�̐���

private:
	static LPD3DXMESH		m_pMesh;			// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMat;			// �}�e���A�����̐�
	static LPDIRECT3DTEXTURE9		*m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;				// �ʒu
	D3DXVECTOR3				m_move;				// �ړ���
	D3DXVECTOR3				m_rot;				// ����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// �u���b�N�̍ŏ��l�A�ő�l

	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
};

#endif
//=============================================================================
//
// 3D���f������ [sceneObject.h]
// Author : ���R���
//
//=============================================================================
#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CSceneObject : public CScene
{
public:
	CSceneObject(int nPriority = SCENEOBJ_PRIORITY, OBJTYPE objType = OBJTYPE_OBJECT);		// �R���X�g���N�^
	~CSceneObject();														// �f�X�g���N�^

	HRESULT Init(void);														// 3D�I�u�W�F�N�g����������
	void Uninit(void);														// 3D�I�u�W�F�N�g�I������
	void Update(void);														// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);														// 3D�I�u�W�F�N�g�`�揈��
	
	static CSceneObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);			// �I�u�W�F�N�g�̐���

	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);					// �����蔻��
	void SetVtx(void);														// ���_���W�̐ݒ�

	D3DXVECTOR3 GetPos(void);												// �ʒu�̎擾
	void SetPos(D3DXVECTOR3 pos);											// �ʒu�̐ݒ�

	D3DXVECTOR3 GetRot(void);												// �����̎擾
	void SetRot(D3DXVECTOR3 rot);											// �����̐ݒ�

	int GetType(void);														// �^�C�v�̎擾
	void SetType(int nType);

	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);	// ���f�������蓖�Ă�
private:
	LPDIRECT3DTEXTURE9		*m_pTexture;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH				m_pMesh;										// ���b�V�����i���_���j�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;										// �}�e���A�����ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;										// ���[���h�}�g���b�N�X
	DWORD					m_nNumMat;										// �}�e���A�����̐�
	bool					m_bCollision;									// �������Ă��邩�ǂ���
	int						m_nType;
	D3DXVECTOR3				m_VtxMin, m_VtxMax;								// ���f���̍ŏ��l�A�ő�l

	D3DXVECTOR3				m_pos;											// �|���S���̈ʒu
	D3DXVECTOR3				m_rot;											// ������x�N�g��
};

#endif
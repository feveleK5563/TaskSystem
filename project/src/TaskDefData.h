#pragma once

//�g�嗦
namespace Ratio
{
    const float layer_main      (3.f);
};

//�`�揇
enum Priority
{
    CAMERA = 0, //�J����

    BACK,       //�w�i
    CIRCLE,     //�~�`�u�����Ɣw�i
    MAP,        //�}�b�v
    ENEMY,      //�G
    PLAYER,     //�v���C���[
    MUDRA,      //�C��
    JOUETSU,    //�W���E�G�c����
    MLINE,      //���C��

    ALL_TASK_TYPE_NUM,
};

//���̑��̃f�[�^
namespace Physic
{
	const float gravity	(0.5f);
}
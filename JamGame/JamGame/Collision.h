#pragma once
#include<DirectXMath.h>
class Collision
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
public:
	/// <summary>
	/// ��`���m�̓����蔻��
	/// </summary>
	/// <param name="pos1">��ڂ̋�`�̍�����W</param>
	/// <param name="pos2">��ڂ̋�`�̍�����W</param>
	/// <param name="size1">��ڂ̋�`�̑傫��</param>
	/// <param name="size2">��ڂ̋�`�̑傫��</param>
	/// <returns>�������Ă�����true�������Ă��Ȃ�������false</returns>
	bool CubeToCubeCollision(const XMFLOAT2 &pos1, const XMFLOAT2 &pos2, const XMFLOAT2 &size1, const XMFLOAT2 &size2)
	{
		if (pos1.x <= pos2.x + size2.x && pos2.x <= pos1.x + size1.x)
		{
			if (pos1.y <= pos2.y + size2.y && pos2.y <= pos1.y + size1.y)
			{
				return true;
			}
		}
		return false;
	}
};


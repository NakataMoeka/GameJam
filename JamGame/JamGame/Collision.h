#pragma once
#include<DirectXMath.h>
class Collision
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
public:
	/// <summary>
	/// 矩形同士の当たり判定
	/// </summary>
	/// <param name="pos1">一つ目の矩形の左上座標</param>
	/// <param name="pos2">二つ目の矩形の左上座標</param>
	/// <param name="size1">一つ目の矩形の大きさ</param>
	/// <param name="size2">二つ目の矩形の大きさ</param>
	/// <returns>当たっていたらtrue当たっていなかったらfalse</returns>
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


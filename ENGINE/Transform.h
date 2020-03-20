#pragma once
#include "Component.h"
#include <Maths.h>


class Actor;
class Transform : public Component
{
private:
	enum DIRECTION
	{
		LEFT,
		CENTER,
		RIGHT,
	};
	Vector4 direction;

public:
	DIRECTION DIRECTION;

	void SetDirection(Vector4 _Direction)
	{
		direction = _Direction;
	}

	Vector4 GetDirection()
	{
		return direction;
	}


public:
	friend Actor;

public:
	bool radianCheck;
	bool posCheck;
	bool scaleCheck;

protected:
#pragma region Member Variable
	//LOCAL
	Vector4 localScale;
	Vector4 localRadian;
	Vector4 localPosition;

	Vector4 scale;
	Vector4 radian;
	Vector4 position;

	Matrix scaleMatrix;

	Matrix rotatedRadianX;
	Matrix rotatedRadianY;
	Matrix rotatedRadianZ;
	Matrix radianMatrix;

	Matrix positionMatrix;

	Matrix parentWoldMatrix;
	Matrix worldMatrix;
#pragma endregion


	
	bool update; //부모자식 구조

protected:
	Transform* parentTransform;
	void SetParentTransform(Transform* _ParentTransform) 
	{
		parentTransform = _ParentTransform; 
	}
	
#pragma region LOCAL

public:
	Vector4 GetLocalPosition()
	{
		return localPosition;
	}

	void SetLocalPosition(const Vector4& _Pos)
	{
		localPosition = _Pos;
		posCheck = true;
	}
	void LocalMove(const Vector4& _Pos)
	{
		localPosition += _Pos.vector3;
		posCheck = true;
	}


	Vector4 GetLocalRadian()
	{
		return localRadian;
	}
	Vector4 LocalConvertRadian()
	{
		return localRadian * (Constant::PI / 180.0f);
	}

	void LocalRotZPlus(const float& _RotZ)
	{
		localRadian.z += _RotZ;
		radianCheck = true;
	}

	void LocalRot(const float& _RotZ)
	{
		localRadian.z = _RotZ;
		radianCheck = true;
	}

	void SetLocalRadian(const Vector4& _Radian)
	{
		localRadian = _Radian;
		radianCheck = true;
	}

	Vector4 GetLocalScale()
	{
		return localScale;
	}

	void SetLocalScale(const Vector4& _Scale)
	{
		localScale = _Scale;
		scaleCheck = true;
	}
	void LocalScalePlus(const float _Scale)
	{
		localScale += _Scale;
		scaleCheck = true;
	}
	void LocalScaleMultiple(const float _Scale)
	{
		localScale *= _Scale;
		scaleCheck = true;
	}


	// 행렬 내가 헛했다.
	Vector4 LocalLookForward()
	{
		return radianMatrix.Vector[2];
	}

	Vector4 LocalLookUp()
	{
		return radianMatrix.Vector[1];
	}

	Vector4 LocalLookRight()
	{
		return radianMatrix.Vector[0];
	}

	virtual bool UpdateOn()
	{
		UpdateCheck();
		return isUpdate = true;
	}
	virtual bool UpdateOff()
	{
		return isUpdate = false;
	}

	void UpdateCheck();

	

	/*void LocalMove(const Vector4& _Pos)
	{
		position += _Pos;
		posCheck = true;
	}*/






#pragma endregion
	
#pragma region WORLD
public:

	//// POS
	Vector4 GetPosition()
	{
		return position;
	}

	Vector4 Get2DPosition()
	{
		Vector4 Pos;
		Pos.x = position.x;
		Pos.y = position.y;

		return Pos;
	}

	void SetPosition(const Vector4& _Pos)
	{
		if (nullptr == parentTransform) //부모가 없을때  -> 내가 부모이다.
		{
			localPosition = _Pos;
			posCheck = true;

			return;
		}

		//내가 자식일떄
		Vector4 scale			= parentTransform->GetLocalScale();
		Vector4 pivotPostion	= _Pos - parentTransform->GetLocalPosition();
		
		position = _Pos;
		//localPosition = { pivotPostion.x / scale.x, pivotPostion.y / scale.y, pivotPostion.z / scale.z };

		localPosition = Vector4(
			scale.x != 0.0f ? pivotPostion.x / scale.x : pivotPostion.x,
			scale.y != 0.0f ? pivotPostion.y / scale.y : pivotPostion.y,
			scale.z != 0.0f ? pivotPostion.z / scale.z : pivotPostion.z
		);

		posCheck = true;

		// 부모 Scale 2, 2, 2
		// 부모 LPos	  2, 0, 0
		// 나는 Scale 2, 2, 2
		// 나의 LPos 3, 0, 0
		// 나의 월드 Pos 2 + 6 
		// 나의 월드 scale 4, 4, 4
		// 나의 월드 Pos 10, 0, 0
		// 부모 LPos 2, 0, 0
		// 로컬포지션은 4, 0, 0
		// 10, 0.0f, 0.0f - 2.0f, 0.0f, 0.0f
	}


	void Move2D(const Vector4& _Pos, const float _Value)
	{
		localPosition += _Pos.vector3;
		localPosition.z = _Value;
		posCheck = true;
	}

	void MoveZ(const float& _Value)
	{
		localPosition.z = _Value;
		posCheck = true;
	}
	
	//void LocalMove(const Vector4& _Pos)
	//{
	//	localPosition += _Pos.vector3;
	//	posCheck = true;
	//}

	/*void WMove3D(const HVEC4& _Pos)
	{
	}*/

	/////	RADIAN


	Vector4 GetRadian()
	{
		return radian;
	}
	
	void SetRadian(const Vector4& _Radian)
	{
		// 내가 20 도 돌았다.
		// 부모가 20 도 돌았어
		// lOCALROT은????????????

		// 나의 LOCALROTX 20

		// 부모의 LOCALROTX 45
		// 새로운 각도는 무조건 135

		if (nullptr == parentTransform)
		{
			localRadian = _Radian;
			radianCheck = true;

			return;
		}

		Vector4 parentRadian = parentTransform->GetLocalRadian();

		radian = _Radian;
		localRadian = { _Radian.x - parentRadian.x, _Radian.y - parentRadian.y, _Radian.z - parentRadian.z };
		radianCheck = true;		
	}
	Vector4 ConvertRadian()
	{
		return radian * (Constant::PI / 180.0f);
	}
	Vector4 ConvertDegree()
	{
		return radian * (180.0f / Constant::PI);
	}



	/////	SCALE

	void SetScale(const Vector4& _Scale)
	{
		if (nullptr == parentTransform)
		{
			localScale = _Scale;
			scaleCheck = true;
			return;
		}

		Vector4 parentScale = parentTransform->GetLocalScale();

		scale = _Scale;
		//localScale = { _Scale.x / parentScale.x, _Scale.y / parentScale.y, _Scale.z / parentScale.z };

		localPosition = Vector4(
			parentScale.x != 0 ? _Scale.x / parentScale.x : _Scale.x,
			parentScale.y != 0 ? _Scale.y / parentScale.y : _Scale.y,
			parentScale.z != 0 ? _Scale.z / parentScale.z : _Scale.z
		);

		scaleCheck = true;		
	}

	Vector4 GetScale()
	{
		return scale;
	}

	void PlusScale(const float _Scale)
	{
		if (nullptr == parentTransform)
		{
			LocalScalePlus(_Scale);
		}
		else
		{
			Vector4 scaleCheck = GetScale();
			scaleCheck += _Scale;
			SetScale(scaleCheck);
		}		
	}

	void MultipleScale(const float _Scale)
	{
		scale *= _Scale;
		scaleCheck = true;
	}

	void SetWindowSizeUV();

	Vector4 LookUp()
	{
		return radianMatrix.Vector[1].ReturnNormalization();
	}

	Vector4 LookRight()
	{
		return radianMatrix.Vector[0].ReturnNormalization();
	}
	Vector4 LookForward()
	{
		return radianMatrix.Vector[2].ReturnNormalization();
	}


public:
	Matrix GetWorldMatrix()
	{
		return worldMatrix;
	}

	Matrix GetWorldMatrix(bool _Scale, bool _Rotate, bool _Position)
	{
		Matrix worldMatrix = Matrix();
		if (_Scale)
		{
			worldMatrix *= scaleMatrix;
		}
		if (_Rotate)
		{
			worldMatrix *= radianMatrix;
		}
		if (_Position)
		{
			worldMatrix *= positionMatrix;
		}

		return worldMatrix;		
	}


#pragma endregion

#pragma region RADIAN - ROTATE
	void RadianPlus_X(const float& _Radian)
	{
		Vector4 radian = GetRadian();

		radian.x += _Radian;
		SetRadian(radian);
	}
	void RadianPlus_Y(const float& _Radian)
	{
		Vector4 radian = GetRadian();

		radian.y += _Radian;
		SetRadian(radian);
	}
	void RadianPlus_Z(const float& _Radian)
	{
		Vector4 radian = GetRadian();

		radian.z += _Radian;
		SetRadian(radian);		
	}


	void SetRadian_Z(const float& _Radian)
	{
		radian.z = _Radian;
		radianCheck = true;
	}
	void SetRadian_X(const float& _Radian)
	{
		radian.x = _Radian;
		radianCheck = true;
	}
	void SetRadian_Y(const float& _Radian)
	{
		radian.y = _Radian;
		radianCheck = true;
	}
#pragma endregion
	

public:
	void Init() override;

protected:
	virtual void UpdateTransform();
	virtual void UpdateTransforms(bool _Scale, bool _Rotate, bool _Position);

public:
	void RenderObjBefore() override;
	void RenderObjAfter() override;
	

public:
	Transform();
	~Transform();
};


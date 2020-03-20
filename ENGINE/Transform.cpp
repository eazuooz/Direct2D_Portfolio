#include "Transform.h"
#include <MyWindow.h>


Transform::Transform() : localScale(1.0f), posCheck(true), radianCheck(true), scaleCheck(true), update(false), parentTransform(nullptr)
{
	SetName(L"Transform");
}


Transform::~Transform()
{
}

void Transform::SetWindowSizeUV()
{
	//SetScale({ 55.0f / Window::MainWindow()->GetWindowSize().y , 25.0f / Window::MainWindow()->GetWindowSize().y });
	//ScaleMul(/*4.8f*/ Window::MainWindow()->GetWindowSize().y / 100.0f);
}

void Transform::Init()
{
	if (nullptr != GetActor()->GetTransform())
	{
		BOOM;
	}

	GetActor()->SetTransform(this);
}

void Transform::UpdateCheck()
{
	posCheck = true;
	radianCheck = true;
	scaleCheck = true;
	update = true;

	if (nullptr != GetActor()->parentActor &&
		true == GetActor()->parentActor->IsUpdate() &&
		nullptr != GetActor()->parentActor->GetTransform())
	{
		GetActor()->parentActor->GetTransform()->UpdateCheck();
	}
}

void Transform::UpdateTransform()
{
	if (true == IsDebug())
	{
		int a = 0;
	}

	if (true == scaleCheck)
	{
		scaleMatrix.Scaling(localScale);
		update = true;
		scaleCheck = false;
	}

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			if (true == std::isnan(positionMatrix.Arr2D[y][x]))
			{
				int a = 0;
			}
		}
	}

	if (true == radianCheck)
	{
		rotatedRadianX.RotateX_Degree(localRadian.x);
		rotatedRadianY.RotateY_Degree(localRadian.y);
		rotatedRadianZ.RotateZ_Degree(localRadian.z);
		//rot_Matrix = rot_X * rot_Y * rot_Z;

		radianMatrix.QuaternionRoation_Radian(localRadian);

		update = true;
		radianCheck = false;
	}
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			if (true == std::isnan(positionMatrix.Arr2D[y][x]))
			{
				int a = 0;
			}
		}
	}

	if (true == posCheck)
	{
		positionMatrix.Translation(localPosition);

		update = true;
		posCheck = false;
	}


	if (true == update && nullptr == parentTransform)
	{
		worldMatrix = scaleMatrix * radianMatrix * positionMatrix;
	}
	else if (nullptr != parentTransform && true == parentTransform->update)
	{
		parentWoldMatrix = parentTransform->GetWorldMatrix();
		worldMatrix = scaleMatrix * radianMatrix * positionMatrix * parentWoldMatrix;
	}


	if (nullptr != parentTransform && true == parentTransform->update)
	{
		position = worldMatrix.Vector[3];
		radian = parentTransform->GetLocalRadian() + GetLocalRadian();
		scale = parentTransform->GetLocalScale() * GetLocalScale();

		update = true;
	}
	else if (true == update && nullptr == parentTransform)
	{
		position = worldMatrix.Vector[3];
		radian = GetLocalRadian();
		scale = GetLocalScale();

		update = true;
	}

}

void Transform::UpdateTransforms(bool _Scale, bool _Rotate, bool _Position)
{
	if (true == scaleCheck)
	{
		scaleMatrix.Scaling(localScale);
		update = true;
		scaleCheck = false;
	}

	if (true == radianCheck)
	{
		rotatedRadianX.RotateX_Degree(localRadian.x);
		rotatedRadianY.RotateY_Degree(localRadian.y);
		rotatedRadianZ.RotateZ_Degree(localRadian.z);
		//rot_Matrix = rot_X * rot_Y * rot_Z;

		radianMatrix.QuaternionRoation_Radian(localRadian);

		update = true;
		radianCheck = false;
	}

	if (true == posCheck)
	{
		positionMatrix.Translation(localPosition);

		update = true;
		posCheck = false;
	}

	if (true == update && nullptr == parentTransform)
	{
		worldMatrix = scaleMatrix * radianMatrix * positionMatrix;
	}
	else if (nullptr != parentTransform && true == parentTransform->update)
	{
		parentWoldMatrix = parentTransform->GetWorldMatrix(_Scale, _Rotate, _Position);
		worldMatrix = scaleMatrix * radianMatrix * positionMatrix * parentWoldMatrix;
	}

	if (nullptr != parentTransform && parentTransform->update)
	{
		position = worldMatrix.Vector[3];
		radian = parentTransform->GetLocalRadian() + GetLocalRadian();
		scale = parentTransform->GetLocalScale() * GetLocalScale();

		update = true;
	}
	else if (true == update && nullptr == parentTransform)
	{
		position = worldMatrix.Vector[3];
		radian = GetLocalRadian();
		scale = GetLocalScale();

		update = true;
	}
}


void Transform::RenderObjBefore()
{
	//scaleMatrix.Scaling(scale);
	UpdateTransform();


}

void Transform::RenderObjAfter()
{
	update = false;
	//Pos_Matrix.PrintMatrix();
}
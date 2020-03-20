#pragma once

#define ITERFOR(Start, End, List, FuncName) \
if(0 != List##.size())\
{\
	Start = List##.begin(); \
	End = List##.end(); \
	for (; Start != End; ++Start) \
	{ \
		if(true == (*##Start##)->##IsUpdate##())\
		{\
			(*##Start##)->##FuncName##(); \
		}\
	}\
}




class UpdaterBase
{
protected:
	bool isUpdate;
	bool isDeath;

public:
	inline virtual bool UpdateOn()
	{
		return isUpdate = true;
	}

	inline virtual bool UpdateOff()
	{
		return isUpdate = false;
	}

	inline virtual bool IsUpdate()
	{
		return true == isUpdate && false == isDeath;
	}
	inline virtual bool IsDeath()
	{
		return isDeath;
	}	
	inline virtual void Die()
	{
		isDeath = true;
	}

public:
	virtual void UpdateAfter();
	virtual void Update();
	virtual void UpdateBefore();
	virtual void FinalUpdate();
	virtual void RenderObjBefore();
	//virtual void RenderObj();
	virtual void RenderObjAfter();
	virtual void ColBefore();
	virtual void Col();
	virtual void ColAfter();
	virtual void Release();
	virtual void ReleaseAfter();

public:
	UpdaterBase();
	~UpdaterBase();
};


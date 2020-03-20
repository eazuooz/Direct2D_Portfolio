#include "UpdaterBase.h"



UpdaterBase::UpdaterBase() :isUpdate(true), isDeath(false)
{
}


UpdaterBase::~UpdaterBase()
{
}

void UpdaterBase::UpdateAfter() {}
void UpdaterBase::Update() {}
void UpdaterBase::UpdateBefore() {}
void UpdaterBase::FinalUpdate() {}
void UpdaterBase::RenderObjBefore() {}
//void UpdaterBase::RenderObj() {}
void UpdaterBase::RenderObjAfter() {}
void UpdaterBase::ColBefore() {}
void UpdaterBase::Col() {}
void UpdaterBase::ColAfter() {}
void UpdaterBase::Release() {}
void UpdaterBase::ReleaseAfter() {}
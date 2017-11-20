#include "NBaseDrawable.h"

NBaseDrawable::NBaseDrawable() :
	needMatrixUpdate(true),
	worldMatrix(1.0f) { }

NBaseDrawable::~NBaseDrawable() {
	mCurrentShader = nullptr;
	mRenderCamera = nullptr;
}

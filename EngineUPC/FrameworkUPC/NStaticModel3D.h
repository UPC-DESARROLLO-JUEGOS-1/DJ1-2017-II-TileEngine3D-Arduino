#pragma once

#include <string>
#include <vector>

#include "dtModelObjMesh.h"
#include "NMeshRenderer3D.h"
#include "ContentManager.h"
#include "NBaseDrawable.h"

class NStaticModel3D : public NBaseDrawable
{
public:
	NStaticModel3D();
	~NStaticModel3D() {

	}

	Vector3 GetPosition()	{ return mMeshRenderer->GetPosition(); }
	Vector3 GetScale()		{ return mMeshRenderer->GetScale(); }
	Vector3 GetRotation()	{ return mMeshRenderer->GetRotation(); }

	void SetPosition(float x, float y, float z) {
		mMeshRenderer->SetX(x);
		mMeshRenderer->SetY(y);
		mMeshRenderer->SetZ(z);
	}

	void SetRotationX(float x) { mMeshRenderer->SetRotationX(x); }
	void SetRotationY(float y) { mMeshRenderer->SetRotationY(y); }
	void SetRotationZ(float z) { mMeshRenderer->SetRotationZ(z); }

	void SetRotation(float x, float y, float z) {
		mMeshRenderer->SetRotationX(x);
		mMeshRenderer->SetRotationY(y);
		mMeshRenderer->SetRotationZ(z);
	}

	void SetScaleX(float x) { mMeshRenderer->SetScaleX(x); }
	void SetScaleY(float y) { mMeshRenderer->SetScaleY(y); }
	void SetScaleZ(float z) { mMeshRenderer->SetScaleZ(z); }

	void SetScale(float x, float y, float z) {
		mMeshRenderer->SetScaleX(x);
		mMeshRenderer->SetScaleY(y);
		mMeshRenderer->SetScaleZ(z);
	}

	void Initialize(std::string folder, std::string modelPath,
		float x, float y, float z);
	void Update(float dt);
	void Draw(float dt);

	void SetRenderCamera(BaseCamera* renderCamera) { 
		mRenderCamera = renderCamera; 

		if (mMeshRenderer != nullptr) {
			mMeshRenderer->SetRenderCamera(mRenderCamera);
		}
	}

protected:
	std::string mFolder;

	BaseCamera* mRenderCamera;
	NMeshRenderer3D* mMeshRenderer;
	ContentManager* mContentManager;
	std::vector<dtModelObjMesh> mMeshes;
};


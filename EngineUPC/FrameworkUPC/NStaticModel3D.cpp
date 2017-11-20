#include "NStaticModel3D.h"

#include "OBJ_Loader.h"
#include "GameFramework.h"

NStaticModel3D::NStaticModel3D()
{
}

void NStaticModel3D::Initialize(std::string folder, std::string modelPath, 
	float x, float y, float z) {
	
	mFolder = folder;

	// Initialize Loader
	objl::Loader* objLoader = new objl::Loader();
	// Load .obj File
	bool loadout = objLoader->LoadFile(folder + modelPath);
	
	if (loadout) {
		for (int i = 0; i < objLoader->LoadedMeshes.size(); i++)
		{
			objl::Mesh currentMesh = objLoader->LoadedMeshes[i];

			dtModelObjMesh mesh;
			mesh.texturePath = currentMesh.MeshMaterial.map_Kd;
			mesh.DiffuseColor.x = currentMesh.MeshMaterial.Kd.X;
			mesh.DiffuseColor.y = currentMesh.MeshMaterial.Kd.Y;
			mesh.DiffuseColor.z = currentMesh.MeshMaterial.Kd.Z;

			for (int j = 0; j < currentMesh.Vertices.size(); j++) {
				objl::Vertex vertex = currentMesh.Vertices[j];

				dtModelObjVertex newVertex;
				newVertex.Position.x = vertex.Position.X;
				newVertex.Position.y = vertex.Position.Y;
				newVertex.Position.z = vertex.Position.Z;
				newVertex.Normal.x = vertex.Normal.X;
				newVertex.Normal.y = vertex.Normal.Y;
				newVertex.Normal.z = vertex.Normal.Z;
				newVertex.TextCoord.x = vertex.TextureCoordinate.X;
				newVertex.TextCoord.y = 1.0f - vertex.TextureCoordinate.Y;
				
				mesh.Vertices.push_back(newVertex);
			}

			for (int j = 0; j < currentMesh.Indices.size(); j += 3) {
				mesh.Triangles.push_back(currentMesh.Indices[j]);
				mesh.Triangles.push_back(currentMesh.Indices[j + 1]);
				mesh.Triangles.push_back(currentMesh.Indices[j + 2]);
			}

			mMeshes.push_back(mesh);
		}
	}
	
	mContentManager = GameFramework::GET_FRAMEWORK()->GetContentManager();

	 // Initialize Mesh Renderer
	mMeshRenderer = new NMeshRenderer3D();
	mMeshRenderer->Initialize(x, y, z);
	mMeshRenderer->SetRenderCamera(mRenderCamera);

	objLoader->~Loader();
	objLoader = nullptr;
}

void NStaticModel3D::Update(float dt) {
	mMeshRenderer->Update(dt);
}

void NStaticModel3D::Draw(float dt) {
	for (int i = 0, count = mMeshes.size(); i < count; i++)
	{
		dtModelObjMesh mesh = mMeshes[i];

		mMeshRenderer->Begin();

		for (int j = 0; j < mesh.Vertices.size(); j++)
		{
			dtModelObjVertex vertex = mesh.Vertices[j];

			// mandamos solo la posicion del vertices, normales, uv
			mMeshRenderer->PushVertex(vertex.Position, vertex.Normal,
				vertex.TextCoord);
		}

		// mandamos los indices
		mMeshRenderer->PushTriangles(mesh.Triangles);

		if (mesh.texturePath.size() > 0) {
			ImageContent* content = mContentManager->LoadAndGetContent<ImageContent>(
				mFolder + mesh.texturePath);
			mMeshRenderer->End(content);
		}
		else {
			mMeshRenderer->End(mesh.DiffuseColor);
		}
		
		mMeshRenderer->Draw(dt);
	}
}
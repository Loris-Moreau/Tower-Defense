#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Vector2.h"
#include "Shader.h"
#include <vector>
#include "DirectionalLight.h"
using std::vector;

class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void endDraw();
	void close();
	IRenderer::Type type() { return Type::OGL; }

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const class Actor& actor, const class Texture& tex, struct Rectangle srcRect, Vector2 origin, Flip flip) const;

	void addMesh(class MeshComponent* mesh);
	void removeMesh(class MeshComponent* mesh);

	DirectionalLight& getDirectionalLight() { return dirLight; }
	Vector3 getAmbientLight() const { return ambientLight; }

	void setViewMatrix(const Matrix4& viewP);
	void setLightUniforms(Shader& shader);
	void setAmbientLight(const Vector3& ambientP);

	// Given a screen space point, unprojects it into world space,
	// based on the current 3D view/projection matrices
	// Expected ranges:
	// x = [-screenWidth/2, +screenWidth/2]
	// y = [-screenHeight/2, +screenHeight/2]
	// z = [0, 1) -- 0 is closer to camera, 1 is further
	Vector3 unproject(const Vector3& screenPoint) const;
	void getScreenDirection(Vector3& outStart, Vector3& outDir) const;

	bool createMirrorTarget();
	void draw3dScene(unsigned int frameBuffer, const Matrix4& view, const Matrix4& proj, float viewportScale, bool lit);
	Texture* getMirrorTexture() { return mirrorTexture; }
	void setMirrorView(const Matrix4& view);
	void initializeGBuffer();
	void drawFromGBuffer();

	void addPointLight(class PointLightComponent* light);
	void removePointLight(class PointLightComponent* light);
	void initializeGPointLight();

private:
	void drawMeshes(const Matrix4& currentView);
	void drawSprites();
	void drawUI();

	Window* window;
	SDL_GLContext context;
	VertexArray* spriteVertexArray;
	Matrix4 spriteViewProj;
	Matrix4 view;
	Matrix4 projection;

	vector<class MeshComponent*> meshes;
	vector<class SpriteComponent*> sprites;
	vector<class SkeletalMeshComponent*> skMeshes;

	Vector3 ambientLight;
	DirectionalLight dirLight;

	unsigned int mirrorBuffer; // Framebuffer object
	class Texture* mirrorTexture;
	Matrix4 mirrorView;

	class GBuffer* gBuffer;
	vector<class PointLightComponent*> pointLights;
};


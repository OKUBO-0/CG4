#pragma once
#include "KamataEngine.h"
#include "Particle.h"

class GameScene
{
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();
	
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// パーティクル発生
	void ParticleBorn(KamataEngine::Vector3 position);

	// 描画
	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// パーティクル
	KamataEngine::Model* modelParticle_ = nullptr;
	std::list<Particle*> particles_;
	};
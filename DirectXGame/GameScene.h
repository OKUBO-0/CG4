#pragma once
#include "KamataEngine.h"
#include "Effect.h"

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

	// エフェクト発生
	void EffectBorn(KamataEngine::Vector3 position);

	// 描画
	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// エフェクト
	KamataEngine::Model* modelEffect_ = nullptr;
	std::list<Effect*> effects_;
};
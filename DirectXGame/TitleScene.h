#pragma once
#include "KamataEngine.h"
#include "Stage.h"

class TitleScene
{
public:
	// コンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 終了フラグ
	bool IsFinished() const { return finished_; }

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// タイトルスプライト
	uint32_t titleSpriteHandle_ = 0;
	KamataEngine::Sprite* titleSprite_ = nullptr;

	// 終了フラグ
	bool finished_ = false;

	// ステージ
	Stage* stage_ = nullptr;
};
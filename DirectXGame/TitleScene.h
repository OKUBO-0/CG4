#pragma once
#include "KamataEngine.h"

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

	// 背景スプライト
	uint32_t backgroundSpriteHandle_ = 0;
	KamataEngine::Sprite* backgroundSprite_ = nullptr;

	// タイトルスプライト
	uint32_t titleSpriteHandle_ = 0;
	KamataEngine::Sprite* titleSprite_ = nullptr;

	// PushEnter スプライト
	uint32_t hitEnterSpriteHandle_ = 0;
	KamataEngine::Sprite* hitEnterSprite_ = nullptr;

	// 終了フラグ
	bool finished_ = false;
};
#pragma once
#include "KamataEngine.h"

class Stage {
public:
	Stage();
	~Stage();

	void Initialize();
	void Update();
	void Draw();

private:
	uint32_t backgroundHandle_;
	KamataEngine::Sprite* background1_ = nullptr;
	KamataEngine::Sprite* background2_ = nullptr;

	KamataEngine::Vector2 position1_;
	KamataEngine::Vector2 position2_;

	const float scrollSpeed_ = 2.0f;
};
#pragma once
#include "KamataEngine.h"

class Effect
{
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 scale, KamataEngine::Vector3 rotation, KamataEngine::Vector3 position);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

	// デスフラグ
	bool IsFinished() const { return isFinished_; }

private:
	// ワールド変換行列
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;

	// 終了フラグ
	bool isFinished_ = false;
	// 経過時間カウント
	float counter_ = 0.0f;
	// 存続時間 (消滅までの時間) <秒>
	const float kDuration = 1.0f;
};
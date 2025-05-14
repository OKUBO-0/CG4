#include "Particle.h"

using namespace KamataEngine;
using namespace MathUtility;

void Particle::Initialize(Model* model, Vector3 position, Vector3 velocity) {
	// NULLポインタチェック
	assert(model); 
	model_ = model;

	// 色の設定
	objectColor_.Initialize();
	color_ = { 1, 0, 0, 1 };

	// 移動量
	velocity_ = velocity;

	// 大きさ
	worldTransform_.scale_ = { 0.2f, 0.2f, 0.2f };

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Particle::Update() {
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	// 移動
	worldTransform_.translation_ += velocity_;

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(Camera& camera_) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera_, &objectColor_);
}
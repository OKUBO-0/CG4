#include "Particle.h"

using namespace KamataEngine;

void Particle::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model); 
	model_ = model;

	//ワールド変換の初期化
	worldTransform_.Initialize();
}

void Particle::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Particle::Draw(Camera& camera_) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera_);
}
#include "Effect.h"

void Effect::Initialize(KamataEngine::Model* model) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	//ワールド変換の初期化
	worldTransform_.Initialize();
}

void Effect::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) {
	// モデルを描画
	model_->Draw(worldTransform_, camera);
}
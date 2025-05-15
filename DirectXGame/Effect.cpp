#include "Effect.h"

using namespace KamataEngine;

void Effect::Initialize(Model* model, Vector3 scale, Vector3 rotation) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	//ワールド変換の初期化
	worldTransform_.Initialize();

	// 大きさ
	worldTransform_.scale_ = scale;

	// 回転
	worldTransform_.rotation_ = rotation;
}

void Effect::Update() {
	// ワールド変換行列の更新
	worldTransform_.UpdateMatrix();

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Effect::Draw(Camera& camera) {
	// モデルを描画
	model_->Draw(worldTransform_, camera);
}
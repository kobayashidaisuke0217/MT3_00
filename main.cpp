#include <Novice.h>

#include<math.h>

const char kWindowTitle[] = "LE2B_12_コバヤシダイスケ";

struct Vector3 {
	float x;
	float y;
	float z;
};
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	return{ v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };

}
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}
Vector3 Multiply(float scalar, const Vector3& v) {
	return { v.x * scalar,v.y * scalar,v.z * scalar };
}
float Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
float Length(const Vector3& v) {
	return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

}
Vector3 Normalise(const Vector3& v) {
	float len = Length(v);
	if (len != 0) {
		return { v.x / len,v.y / len,v.z / len };
	}
	return v;
}
static const int kcolumnwidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3& v, const char* label) {
	Novice::ScreenPrintf(x, y, "%.2f", v.x);
	Novice::ScreenPrintf(x + kcolumnwidth, y, "%.2f", v.y);
	Novice::ScreenPrintf(x + kcolumnwidth * 2, y, "%.2f", v.z);
	Novice::ScreenPrintf(x + kcolumnwidth * 3, y, "%s", label);

}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	Vector3 v1, v2;
	v1 = { 1.0f,3.0f,-5.0f };
	v2 = { 4.0f,-1.0f,2.0f };
	float k = { 4.0f };
	int krowHeight = 30;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Vector3 resultAdd = Add(v1, v2);
		Vector3 resultSubtract = Subtract(v1, v2);
		Vector3 resultMultiply = Multiply(k, v1);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormlize = Normalise(v2);
		///
		/// ↑更新処理ここまで
		///
		VectorScreenPrintf(0, 0, resultAdd, " : Add");
		VectorScreenPrintf(0, krowHeight, resultSubtract, " : Subtract");
		VectorScreenPrintf(0, krowHeight * 2, resultMultiply, " : Multiply");
		Novice::ScreenPrintf(0, krowHeight * 3, "%0.2f : Dot", resultDot);
		Novice::ScreenPrintf(0, krowHeight * 4, "%0.2f : Length", resultLength);
		VectorScreenPrintf(0, krowHeight * 5, resultNormlize, " : Normlise");
		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

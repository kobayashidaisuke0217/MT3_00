#include <Novice.h>
#include <assert.h>
#include <math.h>

struct Matrix4x4
{
	float m[4][4];
};

struct Vector3
{
	float x;
	float y;
	float z;
};

const char kWindowTitle[] = "LE2B_12_コバヤシ_ダイスケ";
Matrix4x4 MakeRotateMatrix(float theta) {
	Matrix4x4 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 0;
	result.m[1][2] = 1;
	result.m[1][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 0;
	result.m[1][2] = 0;
	result.m[1][3] = 1;
	return result;
}

static const int kRowHeight = 20;
static const int kColummWidth = 60;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "% .02f", vector.x);
	Novice::ScreenPrintf(x + kColummWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColummWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColummWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int columm = 0; columm < 4; ++columm)
		{
			Novice::ScreenPrintf(
				x + columm * kColummWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][columm], label);
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateMatrix(rotate.y);


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
		
		///
		/// ↑更新処理ここまで
		///

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

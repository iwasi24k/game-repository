//==============================================================================
//
// ◆ Logger.h
// ログ管理クラス（シングルトン風ユーティリティ）
//
// ファイル出力を基本とし、アプリケーション実行中の各種ログを
// Info / Warning / Error の3段階で記録可能です。
// DebugTool.h のマクロ群から呼び出すことで、呼び出し元の
// ファイル名・行番号・関数名付きのログ出力にも対応します。
//
//-------------------------------------------------------------------------------
// 
// ver：1.0.0
// 作成者 : iwasi
// 作成日 : 2025-08-19
// 最終更新日 : 2025-08-19
//
//==============================================================================
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
public:
    // ログレベルを示す列挙型
    enum class LogLevel { Info, Warning, Error };

    //-------------------------------------------------------------------------
    // ◆ 初期化・終了処理
    //-------------------------------------------------------------------------
    // Initialize : ログ出力先のファイルをオープンする
    // Shutdown   : ファイルをクローズしリソースを解放する
    static void Initialize(const std::wstring& logFilePath = L"log.txt");
    static void Shutdown();

    //-------------------------------------------------------------------------
    // ◆ ログ出力 (基本形)
    //-------------------------------------------------------------------------
    // message : 出力したい文字列
    // level   : 出力レベル (デフォルト Info)
    //
    // 文字コードに応じて std::string / std::wstring 両方に対応
    static void Log(const std::string& message, LogLevel level = LogLevel::Info);
    static void Log(const std::wstring& message, LogLevel level = LogLevel::Info);

    //-------------------------------------------------------------------------
    // ◆ ログ出力 (ファイル名・行番号付き)
    //-------------------------------------------------------------------------
    // file : 呼び出し元ファイル名 (__FILE__)
    // line : 呼び出し元行番号 (__LINE__)
    static void Log(const std::string& message, LogLevel level, const char* file, int line);
    static void Log(const std::wstring& message, LogLevel level, const char* file, int line);

    //-------------------------------------------------------------------------
    // ◆ ログ出力 (ファイル名・行番号・関数名付き)
    //-------------------------------------------------------------------------
    // func : 呼び出し元関数名 (__func__)
    static void Log(const std::string& message, LogLevel level, const char* file, int line, const char* func);
    static void Log(const std::wstring& message, LogLevel level, const char* file, int line, const char* func);

private:
    //-------------------------------------------------------------------------
    // ◆ 内部処理
    //-------------------------------------------------------------------------
    // WriteLine : 実際にファイルへログを書き込む
    static void WriteLine(const std::wstring& message);

    //-------------------------------------------------------------------------
    // ◆ インスタンス化禁止
    //-------------------------------------------------------------------------
    Logger() = delete;                // インスタンス生成不可
    ~Logger() = delete;               // デストラクタ禁止
    Logger(const Logger&) = delete;   // コピー禁止
    Logger(Logger&&) = delete;        // ムーブ禁止
    Logger& operator=(const Logger&) = delete; // 代入禁止
    Logger& operator=(Logger&&) = delete;      // ムーブ代入禁止
};

#endif // LOGGER_H

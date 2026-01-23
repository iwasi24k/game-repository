//==============================================================================
// File        : GlobalGameData.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-16
// Last Update : 2026-1-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef GLOBAL_GAME_DATA_H
#define GLOBAL_GAME_DATA_H

namespace Global {
	class GlobalGameData {
	private:
		bool m_IsGameFinished = false;
		int m_Score = 0;

		GlobalGameData() {}
		~GlobalGameData() {}
		GlobalGameData(const GlobalGameData&) = delete;
		GlobalGameData& operator=(const GlobalGameData&) = delete;

	public:
		static GlobalGameData& GetInstance() {
			static GlobalGameData instance;
			return instance;
		}

		void SetGameFinished(bool isFinished) { m_IsGameFinished = isFinished; }
		bool IsGameFinished() const { return m_IsGameFinished; }

		void AddScore(int score) { m_Score += score; }
		int GetScore() const { return m_Score; }
	};
}

#endif // GLOBAL_GAME_DATA_H
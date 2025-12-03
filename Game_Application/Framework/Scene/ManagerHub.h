//==============================================================================
// File        : ManagerHub.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-03
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef MANAGER_HUB_H
#define MANAGER_HUB_H

#include <memory>
#include <unordered_map>
#include <typeindex>
#include "ObjectManager.h"

namespace Framework {

	class ManagerHub {
	private:
		std::unordered_map<std::type_index, std::unique_ptr<ObjectManager>> m_Managers;

	public:
		template<typename T>
		void AddManager(std::unique_ptr<T> manager) {
			const std::type_index index(typeid(T));
			m_Managers[index] = std::move(manager);
		}

		template<typename T>
		T* FindManager() {
			const std::type_index index(typeid(T));
			auto it = m_Managers.find(index);
			if (it != m_Managers.end()) {
				return static_cast<T*>(it->second.get());
			}
			return nullptr;
		};

		void CreateAll() {
			for (auto& [_, mgr] : m_Managers) mgr->Create();
		}

		void StartAll() {
			for (auto& [_, mgr] : m_Managers) mgr->Start();
		}

		void UpdateAll() {
			for (auto& [_, mgr] : m_Managers) mgr->Update();
		}
	};
}

#endif // MANAGER_HUB_H
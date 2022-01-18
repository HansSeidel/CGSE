#pragma once

#include <vector>
#include <string>
#include <functional>

#include <iostream>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}

		//H-IAMGUI TODO: Delete later if possible ################## 
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);

		//H-IAMGUI TODO: Delete later if possible ################## 
		void OnImGuiRender() override;
		//H-IAMGUI TODO: Delete later if possible ################## 

		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test: " << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T();}));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}
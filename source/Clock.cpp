#include "Clock.hpp"

namespace Trn {
	Clock::Clock() {
		m_currentTime = glfwGetTime();
		m_previousTime = glfwGetTime();
		m_deltaTime = 0.0;
	}
	void Clock::update() {
		m_previousTime = m_currentTime;
		m_currentTime = glfwGetTime();
		m_deltaTime = m_currentTime - m_previousTime;
	}
	double Clock::currentTime() const { return m_currentTime; }
	double Clock::previousTime() const { return m_previousTime; }
	double Clock::deltaTime() const { return m_deltaTime; }
}  // namespace Trn
#include <SFML/Graphics.hpp>
#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

class PhysicsSystem
{
public:
	static PhysicsSystem& getInstance() {
		static PhysicsSystem instance;
		return instance;
	}

	void applyForces() {

	}


private:
	PhysicsSystem() = default;
	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(const PhysicsSystem&) = delete;
};

#endif // !PHYSICS_SYSTEM_HPP

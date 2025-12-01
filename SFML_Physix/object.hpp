#include <SFML/Graphics.hpp>
#include "transformComponent.hpp"
#include "physicsComponent.hpp"
#include "coliderComponent.hpp"
#include "renderComponent.hpp"
#ifndef OBJECT_HPP
#define OBJECT_HPP

enum class ObjectType {
	CIRCLE,
	RECTANGLE
};

class Object {
public:
	Object(const TransformComponent& transform = {}, const PhysicsComponent& physics = {},
		const ColiderComponent& colider = {}, const RenderComponent& render = {})
		: transform(transform), physics(physics), colider(colider), render(render) {}

	const TransformComponent& getTransform() const { return transform; }
	const PhysicsComponent& getPhysics() const { return physics; }
	const ColiderComponent& getColider() const { return colider; }
	const RenderComponent& getRender() const { return render; }

	TransformComponent& getTransform() { return transform; }
	PhysicsComponent& getPhysics() { return physics; }
	ColiderComponent& getColider() { return colider; }
	RenderComponent& getRender() { return render; }

	virtual ObjectType getType() const = 0;

private:
	TransformComponent transform;
	PhysicsComponent physics;
	ColiderComponent colider;
	RenderComponent render;
};
#endif // !OBJECT_HPP
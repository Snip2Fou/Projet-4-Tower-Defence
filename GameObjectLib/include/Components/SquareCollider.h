#pragma once
#include <unordered_map>

#include "Component.h"

class SquareCollider : public Component
{
public:
	SquareCollider() = default;
	~SquareCollider() override = default;

	float width = 1.0f;
	float height = 1.0f;

	float GetWidth() const { return width; }
	float GetHeight() const { return height; }
	std::unordered_map<std::string, bool> GetCanMoving() { return CanMoving; }

	void SetWidth(const float _width) { width = _width; }
	void SetHeight(const float _height) { height = _height; }
	void SetCanMoving(std::string direction, bool move) { CanMoving[direction] = move; }

	bool IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB);

private:
	std::unordered_map<std::string, bool> CanMoving = {{"up", true}, {"down", true}, {"left", true}, {"right", true}};
};

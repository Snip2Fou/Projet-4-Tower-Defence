#include "Components/SquareCollider.h"
#include "Components/SpriteRenderer.h"

bool SquareCollider::IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
	sf::RectangleShape rPlayer;
	sf::RectangleShape rObject;

	rPlayer.setPosition(sf::Vector2f(_colliderA.GetOwner()->GetPosition().GetX(), _colliderA.GetOwner()->GetPosition().GetY()));
	rPlayer.setSize(sf::Vector2f(_colliderA.GetWidth(), _colliderA.GetHeight()));
	rObject.setPosition(sf::Vector2f(_colliderB.GetOwner()->GetPosition().GetX(), _colliderB.GetOwner()->GetPosition().GetY()));
	rObject.setSize(sf::Vector2f(_colliderB.GetWidth(), _colliderB.GetHeight()));

	sf::FloatRect playerBounds = _colliderA.GetOwner()->getBounds(rPlayer);
	sf::FloatRect objectBounds = _colliderB.GetOwner()->getBounds(rObject);

	if (playerBounds.intersects(objectBounds))
	{
		int collisionWidth = std::min(playerBounds.left + playerBounds.width, objectBounds.left + objectBounds.width) - std::max(playerBounds.left, objectBounds.left);
		int collisionHeight = std::min(playerBounds.top + playerBounds.height, objectBounds.top + objectBounds.height) - std::max(playerBounds.top, objectBounds.top);
		// top collision
		if (playerBounds.top > objectBounds.top && playerBounds.top <= objectBounds.top + objectBounds.height && ((playerBounds.left <= objectBounds.left && playerBounds.left + playerBounds.width >= objectBounds.left) || (playerBounds.left >= objectBounds.left && playerBounds.left <= objectBounds.left + objectBounds.width)) && (collisionWidth > collisionHeight && collisionWidth > 5))
		{
			_colliderA.GetOwner()->getComponent<SquareCollider>()->SetCanMoving("up", false);
		}
		// bottom collision
		if (playerBounds.top <= objectBounds.top && playerBounds.top + playerBounds.height >= objectBounds.top && ((playerBounds.left <= objectBounds.left && playerBounds.left + playerBounds.width >= objectBounds.left) || (playerBounds.left >= objectBounds.left && playerBounds.left <= objectBounds.left + objectBounds.width)) && (collisionWidth > collisionHeight && collisionWidth > 5))
		{
			_colliderA.GetOwner()->getComponent<SquareCollider>()->SetCanMoving("down", false);
		}
		//left collision
		if (playerBounds.left >= objectBounds.left && playerBounds.left + playerBounds.width >= objectBounds.left + objectBounds.width && ((playerBounds.top <= objectBounds.top && playerBounds.top + playerBounds.height >= objectBounds.top) || (playerBounds.top >= objectBounds.top && playerBounds.top <= objectBounds.top + objectBounds.height)) && (collisionWidth < collisionHeight && collisionHeight > 5))
		{
			_colliderA.GetOwner()->getComponent<SquareCollider>()->SetCanMoving("left", false);
		}
		//right collision
		if (playerBounds.left <= objectBounds.left && playerBounds.left + playerBounds.width <= objectBounds.left + objectBounds.width && ((playerBounds.top <= objectBounds.top && playerBounds.top + playerBounds.height >= objectBounds.top) || (playerBounds.top >= objectBounds.top && playerBounds.top <= objectBounds.top + objectBounds.height)) && (collisionWidth < collisionHeight && collisionHeight > 5))
		{
			_colliderA.GetOwner()->getComponent<SquareCollider>()->SetCanMoving("right", false);
		}
		return true;
	}
	return false;
}

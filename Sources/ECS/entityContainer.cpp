/**
 * Netero sources under BSD-3-Clause
 * see LICENCE.txt
 */

#include "netero/ECS/entity.hpp"

namespace netero::ecs {

	EntityContainer::EntityContainer(World *world, const std::string &name)
		:	id{name},
			_world(world),
			status(true)
	{}

	EntityContainer::~EntityContainer()
	{}

	World	*EntityContainer::getWorld() {
		return _world;
	}
}
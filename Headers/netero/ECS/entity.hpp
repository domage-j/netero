/**
 * Netero sources under BSD-3-Clause
 * see LICENCE.txt
 */

#pragma once

#include <cstddef>
#include <string>
#include <map>
#include <exception>
#include "netero/ECS/component.hpp"

namespace netero {
	namespace ecs {

		class World;

		class EntityContainer {
			struct id {
				std::string	name;
			};
		public:
			friend World;
			~EntityContainer();

			World	*getWorld();
			template<typename T, typename ...Args>
			T	&addComponent(Args&&... args);
			template<typename T>
			T	&getComponent();
			template<typename T>
			void	deleteComponent();

			bool	status;
		private:
			EntityContainer(World *world, const std::string &name = "unnamed");
			World		*_world;
			id			id;
			std::map<netero::type_id, Component *>	_components;
		};

		template<typename T, typename ...Args>
		T	&EntityContainer::addComponent(Args&&... args) {
			static_assert(std::is_base_of<Component, T>(), "T is not based on Component.");
			std::size_t count = _components.count(CompoentTypeID::getTypeID<T>());
			if (count != 0)
				throw std::runtime_error("One entitie could not own the same component twice.");
			T	*dataPtr = new (std::nothrow) T{ std::forward<Args>(args)... };
			if (!dataPtr)
				throw std::bad_alloc();
			_components[CompoentTypeID::getTypeID<T>()] = dataPtr;
			return *dataPtr;
		}

		template<typename T>
		T	&EntityContainer::getComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not based on Component.");
			std::size_t count = _components.count(CompoentTypeID::getTypeID<T>());
			if (count == 0)
				throw std::runtime_error("Entity does not own T component.");
			return dynamic_cast<T&>(*_components.at(CompoentTypeID::getTypeID<T>()));
		}

		template<typename T>
		void	EntityContainer::deleteComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not based on Component.");
			auto compIt = _components.find(CompoentTypeID::getTypeID<T>());
			if (compIt == _components.end())
				throw std::runtime_error("Entity does not own T component.");
			delete (*compIt).second;
			_components.erase(compIt);
		}

		class Entity
		{
		public:
			Entity();
			Entity(const Entity &rhs);
			Entity(EntityContainer *entityContainer);
			Entity	&operator=(EntityContainer *rhs);
			Entity	&operator=(const Entity &rhs);
			Entity	&operator=(Entity &&rhs);
			bool	operator==(const Entity &rhs);
			bool	operator==(const EntityContainer *rhs);
			EntityContainer	*operator->();
			virtual ~Entity() = default;

			bool	valid() const noexcept;
			void	enable();
			void	disable();
			void	kill();
			void	unregister();

		private:
			EntityContainer		*_base;
		};
	}
}

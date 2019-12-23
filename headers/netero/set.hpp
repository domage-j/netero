/**
 * Netero sources under BSD-3-Clause
 * see LICENCE.txt
 */

#pragma once

#include <set>

namespace netero {

	/**
	 * @brief a set container that follow the math definition
	 * base of the std::set
	 * @tparam value_type - type holder
	 */
	template <typename __Type>
	class set : public std::set<__Type> {
	public:
		set() = default;
		typedef typename std::set<__Type>::iterator iterator;

		// construct from a initializer list
		set(std::initializer_list<__Type> __il) {
			this->insert(__il.begin(), __il.end());
		}

		// copy constructor from std::set
		explicit set(const std::set<__Type> &__copy) {
			this->insert(__copy.begin(), __copy.end());
		}

		/**
		 * @brief check if the actual set is a subset of the given set
		 * @note the given set does not need to be a netero::set
		 * @param other - set to compare
		 * @return true is this is an subset, false otherwise
		 */
		bool	isSubsetOf(const std::set<__Type> &other) const {
			iterator		it_this = this->begin();
			iterator		it_this_end = this->end();
			iterator		it_other = other.begin();
			iterator		it_other_end = other.end();
			if (other.size() == 0)
				return false;
			while (it_this != it_this_end) {
				while (*it_this != *it_other) {
					it_other++;
					if (it_other == it_other_end)
						return false;
				}
				it_this++;
			}
			return true;
		} // O(n) = n, where n is size of other
		// TODO: union -> return new set wich is union of two other set
		// TODO: inter

		bool	interWith(const std::set<__Type>& other) {
			iterator		it_this = this->begin();
			iterator		it_this_end = this->end();
			if (other.size() == 0) {
				return false;
			}
			while (it_this != it_this_end) {
				auto it = other.find(*it_this);
				if (it != other.end()) {
					return true;
				}
				++it_this;
			}
			return false;
		}
	};
}

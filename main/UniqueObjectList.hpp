#pragma once

#include <algorithm>
#include <boost/bind.hpp>
#include <vector>

class WorldObject;

class UniqueObjectList
{
public:
	typedef std::vector<WorldObject*> List;
	typedef List::iterator iterator;

private:
	List objects;

public:
	void add(WorldObject&);
	template<typename Iter>
	inline void addRange(Iter begin, Iter end)
	{
		std::for_each(begin, end, boost::bind(&UniqueObjectList::add, this, _1));
	}
	void remove(WorldObject&);
	template<typename Iter>
	inline void removeRange(Iter begin, Iter end)
	{
		std::for_each(begin, end, boost::bind(&UniqueObjectList::remove, this, _1));
	}

	inline iterator begin()
	{
		return objects.begin();
	}
	inline iterator end()
	{
		return objects.end();
	}
};
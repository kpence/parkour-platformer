#ifndef _RESOURCE_HOLDER_H_
#define _RESOURCE_HOLDER_H_ 1

#include <memory>
#include <stdexcept>
#include <cassert>
#include "Logger.h"

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename);
	Resource& get(Identifier id);
private:
	std::map<Identifier, std::unique_ptr<Resource>> resource_map;
	void insert_resource(Identifier id, std::unique_ptr<Resource> resource);
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(filename)) {
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	insert_resource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
	auto found = resource_map.find(id);
	assert(found != resource_map.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insert_resource(Identifier id, std::unique_ptr<Resource> resource) {
	auto inserted = resource_map.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

#endif

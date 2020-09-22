#include <model/model.h>

size_t Model::getOrCreate(void *reference) {
    const auto value = references.find(reference);
    if (value != references.end())
        return value->second;

    size_t handle = entities.size();
    references[reference] = handle;
    entities.emplace_back();

    return handle;
}
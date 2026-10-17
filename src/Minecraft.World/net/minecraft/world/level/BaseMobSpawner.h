#pragma once

class ResourceLocation;

class BaseMobSpawner {
public:
    virtual ~BaseMobSpawner();
    virtual ResourceLocation getEntityId();
    virtual void setEntityId(const ResourceLocation&);
};

// Copyright (C) 2002-2018 Benjamin Hampe

#ifndef DE_ALPHASONIC_COMMON_CREATE_CYLINDER_HPP
#define DE_ALPHASONIC_COMMON_CREATE_CYLINDER_HPP

#include <common/AutoMeshBuffer.hpp>
#include <common/sinCosTable.hpp>

AutoMeshBuffer*
createCylinderHull(
    glm::vec3 pos,
    float radius,
    float height,
    uint32_t color,
    uint32_t tessCircle = 33,
    uint32_t tessHull = 1);

#endif // DE_ALPHASONIC_COMMON_CREATE_CYLINDER_HPP


#include "collisionitem.h"

#include "visitors/ivisitor.h"

namespace Scene
{

VectorF CollisionItem::projectionOn(VectorF axis) const
{
    float min = std::numeric_limits<float>::infinity();
    float max = -std::numeric_limits<float>::infinity();
    for (auto &vertex : vertices())
    {
        float projection = vertex.dot(axis);
        min = std::min(projection, min);
        max = std::max(projection, max);
    }
    return { min, max };
}

Axes CollisionItem::axes() const
{
    Vertices itemVertices{ vertices() };

    const size_t firstVertexIndex{ 0 };
    const size_t latestVertexIndex{ itemVertices.size() - 1 };

    Axes axes;
    for (size_t index = 0; index < itemVertices.size(); ++index)
    {
        const size_t nextIndex{ index + 1 };

        const PointF start{ itemVertices[index] };
        const PointF end{ index < latestVertexIndex ? itemVertices[nextIndex]
                                                    : itemVertices[firstVertexIndex] };
        const VectorF side{ end - start };
        axes.push_back(side.normal());
    }

    return axes;
}

void CollisionItem::accept(IVisitor *visitor)
{
    visitor->visitSceneCollisionItem(this);
}
} // namespace Scene

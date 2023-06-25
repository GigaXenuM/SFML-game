#include "item.h"

#include "visitors/ivisitor.h"

namespace Scene
{
Item::Item(EventHandler *parent)
{
    if (parent != nullptr)
        parent->addEventHandler(this);
}

void Item::accept(IVisitor *visitor)
{
    visitor->visitSceneItem(this);
}
} // namespace Scene

#ifndef __LEGOFACE_H
#define __LEGOFACE_H

#include "LegoTypes.h"

class LegoStorage;

class LegoFace {
public:
    LegoFace();
    LegoFace(LegoU32* p_vertexIndices);
    LegoU32 GetVertexIndex(LegoU32 i) { return m_vertexIndices[i]; }
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
protected:
    LegoU32 m_vertexIndices[3];
};

#endif // __LEGOFACE_H


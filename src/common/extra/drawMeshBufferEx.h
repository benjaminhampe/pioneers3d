#ifndef __IRR_DRAW_MESHBUFFER_EX_H_INCLUDED__
#define __IRR_DRAW_MESHBUFFER_EX_H_INCLUDED__

#include <IVideoDriver.h>
#include <IMeshBuffer.h>

namespace irr{
namespace video{

inline void drawMeshBufferEx(
	IVideoDriver* driver,
	scene::IMeshBuffer* buffer,
	scene::E_PRIMITIVE_TYPE primType = scene::EPT_TRIANGLES,
	E_VERTEX_TYPE vertexType = EVT_STANDARD,
	E_INDEX_TYPE indexType = EIT_16BIT)
{
	if (!buffer)
		return;

	u32 primCount = 0;

	switch (primType)
	{
		case scene::EPT_POINTS:
				primCount = buffer->getIndexCount();
				break;
		case scene::EPT_LINE_STRIP:
				primCount = buffer->getIndexCount()-1;
				break;
		case scene::EPT_LINE_LOOP:
				primCount = buffer->getIndexCount()-1;
				break;
		case scene::EPT_LINES:
				primCount = buffer->getIndexCount()/2;
				break;
		case scene::EPT_TRIANGLE_STRIP:
				primCount = (buffer->getIndexCount()-2)/3;
				break;
		case scene::EPT_TRIANGLE_FAN:
				primCount = (buffer->getIndexCount()-2)/3;
				break;
		case scene::EPT_TRIANGLES:
				primCount = buffer->getIndexCount()/3;
				break;
		case scene::EPT_QUAD_STRIP:
				primCount = (buffer->getIndexCount()-2)/4;
				break;
		case scene::EPT_QUADS:
				primCount = buffer->getIndexCount()/4;
				break;
		case scene::EPT_POLYGON:
				primCount = buffer->getIndexCount()-1;
				break;
		case scene::EPT_POINT_SPRITES:
				primCount = buffer->getIndexCount();
				break;
		default:
				break;
	}

//	driver->setMaterial(buffer->getMaterial());

	driver->drawVertexPrimitiveList(
			buffer->getVertices(), buffer->getVertexCount(),
			buffer->getIndices(), primCount,
			vertexType, primType, indexType);
}

} // END NAMSPACE VIDEO
} // END NAMSPACE IRR

#endif

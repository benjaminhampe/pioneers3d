#ifndef __IRR_C_SCREEN_QUAD_H__
#define __IRR_C_SCREEN_QUAD_H__

#include <irrlicht.h>

namespace irr
{
namespace video
{

class CScreenQuad : public IReferenceCounted
{
    public:
    CScreenQuad( IVideoDriver* driver)
    : Driver(driver)
	{
		const SColor white(255, 255, 255, 255);
		Vertices[3] = S3DVertex( -1,-1, 0, 0,0,-1,white,0,1);
		Vertices[0] = S3DVertex( -1, 1, 0, 0,0,-1,white,0,0);
		Vertices[1] = S3DVertex(  1, 1, 0, 0,0,-1,white,1,0);
		Vertices[2] = S3DVertex(  1,-1, 0, 0,0,-1,white,1,1);
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;
		Indices[3] = 0;
		Indices[4] = 2;
		Indices[5] = 3;
		Material.Lighting = false;
		Material.ZBuffer = ECFN_ALWAYS;
		Material.ZWriteEnable = false;

		for(u32 c = 0; c < MATERIAL_MAX_TEXTURES; c++)
		{
		   Material.TextureLayer[c].TextureWrapU = ETC_CLAMP_TO_EDGE;
		   Material.TextureLayer[c].TextureWrapV = ETC_CLAMP_TO_EDGE;
		   Material.TextureLayer[c].BilinearFilter = true;
		   Material.TextureLayer[c].TrilinearFilter = false;
		   Material.TextureLayer[c].AnisotropicFilter = 0;

//		   Material.TextureLayer[c].TrilinearFilter = true;
//		   Material.TextureLayer[c].AnisotropicFilter = 8;
		}
    }

    SMaterial& getMaterial()
    {
    	return Material;
	}

	void setTexture( ITexture* tex, u32 layer = 0)
	{
		Material.TextureLayer[layer].Texture = tex;
	}

	ITexture* getTexture(u32 layer = 0)
	{
		return Material.TextureLayer[layer].Texture;
	}

	void setMaterialType( E_MATERIAL_TYPE mt)
	{
		Material.MaterialType = mt;
	}

	void render()
	{
		core::matrix4 oldWorldMatrix = Driver->getTransform( ETS_WORLD );
		core::matrix4 oldViewMatrix = Driver->getTransform( ETS_VIEW );
		core::matrix4 oldProjMatrix = Driver->getTransform( ETS_PROJECTION );

		Driver->setTransform( ETS_WORLD, core::IdentityMatrix);
		Driver->setTransform( ETS_VIEW, core::IdentityMatrix);
		Driver->setTransform( ETS_PROJECTION, core::IdentityMatrix);

		Driver->setMaterial(Material);

		Driver->drawVertexPrimitiveList(Vertices, 4, Indices, 2, EVT_STANDARD, scene::EPT_TRIANGLES, EIT_16BIT);

		Driver->setTransform( ETS_WORLD, oldWorldMatrix);
		Driver->setTransform( ETS_VIEW, oldViewMatrix);
		Driver->setTransform( ETS_PROJECTION, oldProjMatrix);
	}

protected:
private:
	IVideoDriver* Driver;
	SMaterial Material;
	S3DVertex Vertices[4];
	u16 Indices[6];
};

} // end namespace video
} // end namespace irr

#endif // __IRR_C_SCREEN_QUAD_H__

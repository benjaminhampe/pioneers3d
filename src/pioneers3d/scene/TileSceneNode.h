#ifndef CSIEDLERTILE_H
#define CSIEDLERTILE_H

#include <CSiedlerTextures.h>
#include <CSiedlerGeometry.h>
#include <iostream>

/// A hexagon tile is the basic object of a Siedler game
/// It consists of atleast 4 triangles for the top
/// It also can have a border, and a bottom, and additional meshes
// ============================================================================
class Tile : public irr::scene::IMeshSceneNode
// ============================================================================
{
protected:
    float _dx = 10.0f;
    float _dy = 4.0f;
    float _dz = 10.0f;
//    float _x = 0.0f;
//    float _y = 0.0f;
//    float _z = 0.0f;
    E_TILE_TYPE _tileType = E_TILE_TYPE_WASSER;
    int _augen = 0;
    int _winkel = 0;

    irr::scene::SMesh* _mesh = nullptr;
public:

    // x = 0.5*(|j|%2)*dx + i*dx
    // z = j*0.75*dz

    Tile( int i, int j, irr::scene::ISceneNode* parent, irr::scene::ISceneManager* smgr )
        : irr::scene::IMeshSceneNode( parent, smgr, -1 )
    {
        std::cout << "Tile(" << i << "," << j << ")" << std::endl;

        _mesh = new irr::scene::SMesh();
        _mesh->addMeshBuffer( createTop() );
        _mesh->recalculateBoundingBox();

        const float x = (0.50f * _dx) * (std::abs(j) % 2) + _dx * i;
        const float y = _dy * sqrtf( (float)(i*i + j*j) );
        const float z = (0.75f * _dz) * j;

        this->setPosition( irr::core::vector3df(x,y,z) );
        this->setAutomaticCulling( irr::scene::EAC_OFF );

        std::cout << "Tile.pos:\n"
                 << "x = " << this->getAbsolutePosition().X << "\n"
                 << "y = " << this->getAbsolutePosition().Y << "\n"
                 << "z = " << this->getAbsolutePosition().Z << "\n";
    }

    virtual ~Tile()
    {
        std::cout << "~Tile()" << std::endl;
    }

    /// Hexagon MeshBuffer
    // M(x=0,y=0,z=0,u=0.5,v=0.5)
    // A( -.5, 0, 0.25, 0, 0.75 )
    // B( 0.0, 0, 0.50, 0.5, 1 )
    // C( 0.5, 0, 0.25, 1, 0.75 )
    // D( 0.5, 0, -.25, 1, 0.25 )
    // E( 0.0, 0, -.50, 0.5, 0 )
    // F( -.5, 0, -.25, 0, 0.25 )



    irr::scene::SMeshBuffer* createTop()
    {
        _dx = 10.0f;
        _dz = 10.0f;
        irr::scene::SMeshBuffer* p = new irr::scene::SMeshBuffer();
        irr::video::SColor white(255,255,255,255);
        p->Vertices.push_back( irr::video::S3DVertex( -.50f*_dx, 0.f, 0.25f*_dz, 0,1,0, white, 0.00f,0.75f ) ); // A
        p->Vertices.push_back( irr::video::S3DVertex( 0.00f*_dx, 0.f, 0.50f*_dz, 0,1,0, white, 0.50f,1.00f ) ); // B
        p->Vertices.push_back( irr::video::S3DVertex( 0.50f*_dx, 0.f, 0.25f*_dz, 0,1,0, white, 1.00f,0.75f ) ); // C
        p->Vertices.push_back( irr::video::S3DVertex( 0.50f*_dx, 0.f, -.25f*_dz, 0,1,0, white, 1.00f,0.25f ) ); // D
        p->Vertices.push_back( irr::video::S3DVertex( 0.00f*_dx, 0.f, -.50f*_dz, 0,1,0, white, 0.50f,0.00f ) ); // E
        p->Vertices.push_back( irr::video::S3DVertex( -.50f*_dx, 0.f, -.25f*_dz, 0,1,0, white, 0.00f,0.25f ) ); // F
        p->Indices.push_back(0); p->Indices.push_back(1); p->Indices.push_back(2); // ABC
        p->Indices.push_back(0); p->Indices.push_back(2); p->Indices.push_back(3); // ACD
        p->Indices.push_back(0); p->Indices.push_back(3); p->Indices.push_back(5); // ADF
        p->Indices.push_back(5); p->Indices.push_back(3); p->Indices.push_back(4); // FDE
        p->Material.MaterialType = irr::video::EMT_SOLID;
        p->Material.FrontfaceCulling = false;
        p->Material.Lighting = false;
        p->Material.FogEnable = false;
        p->Material.DiffuseColor.set(0xFFFFFFFF);
        p->recalculateBoundingBox();

        p->Material.setTexture( 0, getSceneManager()->getVideoDriver()->getTexture("wasser.png") );
        return p;
    }

    /// INTERFACE: IMeshSceneNode
    virtual void setMesh( irr::scene::IMesh* mesh ) { _mesh = (irr::scene::SMesh*)mesh; }
    virtual irr::scene::IMesh* getMesh() { return _mesh; }
    virtual irr::scene::IShadowVolumeSceneNode* addShadowVolumeSceneNode( const irr::scene::IMesh* shadowMesh=0, irr::s32 id=-1, bool zfailmethod=true, irr::f32 infinity=1000.0f) { return nullptr; }
    virtual void setReadOnlyMaterials( bool readonly ) {}
    virtual bool isReadOnlyMaterials() const { return false; }

    /// INTERFACE: ISceneNode
    virtual irr::u32 getMaterialCount() const override { return _mesh->getMeshBufferCount(); }
    virtual irr::video::SMaterial& getMaterial(irr::u32 num) override { return _mesh->getMeshBuffer(num)->getMaterial(); }
    virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return _mesh->getBoundingBox(); }
    virtual void render()
    {
        irr::video::IVideoDriver* driver = getSceneManager()->getVideoDriver();

        for ( irr::u32 i = 0; i < getMesh()->getMeshBufferCount(); ++i )
        {
            irr::scene::IMeshBuffer* b = getMesh()->getMeshBuffer(i);

            driver->drawVertexPrimitiveList(
                        b->getVertices(), b->getVertexCount(),
                        b->getIndices(), b->getIndexCount(),
                        irr::video::EVT_STANDARD,
                        irr::scene::EPT_TRIANGLES,
                        irr::video::EIT_16BIT );
        }
    }

};

#endif // CSIEDLERTILE_H

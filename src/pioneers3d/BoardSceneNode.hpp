#ifndef CSIEDLERBOARD_H
#define CSIEDLERBOARD_H

#include <Textures.h>
#include <CSiedlerTile.h>

// ============================================================================
class Board
// ============================================================================
{  
public:
    Board( irr::scene::ISceneManager* smgr )
    {
        std::cout << "Board()" << std::endl;
        
        _smgr = smgr;
        _rootNode = _smgr->getRootSceneNode();
        
        /// create default board
        for ( int i = -4; i < 5; ++i )
        {
            for ( int j = -4; j < 5; ++j )
            {
                new Tile( i,j,_rootNode, _smgr );     
            }
        }  
        
        std::cout << "Board() - OK" << std::endl;
    }

    virtual ~Board()
    {
        std::cout << "~Board()" << std::endl;
    }

    // x = 0.5*(|j|%2)*dx + i*dx
    // z = j*0.75*dz


//    virtual void render()
//    {
//        irr::video::IVideoDriver* driver = getSceneManager()->getVideoDriver();
        
//        for ( irr::u32 i = 0; i < getMesh()->getMeshBufferCount(); ++i )
//        {
//            irr::scene::IMeshBuffer* b = getMesh()->getMeshBuffer(i);
            
//            driver->drawVertexPrimitiveList( 
//                        b->getVertices(), b->getVertexCount(), 
//                        b->getIndices(), b->getIndexCount(), 
//                        irr::video::EVT_STANDARD, 
//                        irr::scene::EPT_TRIANGLES,
//                        irr::video::EIT_16BIT );
//        }
//    }
    
protected:
    irr::scene::ISceneManager* _smgr = nullptr;

    irr::scene::ISceneNode* _rootNode = nullptr;
    
    irr::core::array<Tile*> _tiles;
    
};

#endif // CSIEDLERBOARD_H

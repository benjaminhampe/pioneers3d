#ifndef P3DDATA_BOARD_HPP
#define P3DDATA_BOARD_HPP

#include <TextureData.h>
#include <TileData.h>

// ============================================================================
class BoardData
// ============================================================================
{  
public:

	/// create default board
	// x = 0.5*(|j|%2)*dx + i*dx
	// z = j*0.75*dz

    BoardData()
    {
        std::cout << __FUNCTION__ << "()" << std::endl;
        
        for ( int i = -4; i < 5; ++i )
        {
            for ( int j = -4; j < 5; ++j )
            {
                m_Tiles.emplace_back( std::move( TileData( i, j ) ) );     
            }
        }
    }

    virtual ~BoardData()
    {
        std::cout << "~" << __FUNCTION__ << "()" << std::endl;
    }

private:
    std::vector< TileData > m_Tiles;
    
};

#endif // P3DDATA_BOARD_HPP

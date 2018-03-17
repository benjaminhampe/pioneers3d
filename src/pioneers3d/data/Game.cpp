#include "GameData.hpp"

#include <iostream>
#include <time.h>

namespace pioneers3d
{

GameData::GameData( irr::IrrlichtDevice * device )
    : m_Device( device )
{
    std::cout << __FUNCTION__ << "()" << std::endl;

    srand( (unsigned int)time(NULL) );

    m_Board = new BoardData();

    for ( int i = 0; i < 4; ++i )
    {
        m_Players.push_back( new PlayerData( i ) );
    }

    // createAndSave("data");

    // create("data");
/*
    QImage _img[E_SIEDLER_TEX_COUNT];
    _img[E_SIEDLER_TEX_WASSER] = createImage_Wasser( _texW, _texH );
    _img[E_SIEDLER_TEX_HOLZ] = createImage_Holz( _texW, _texH );
    _img[E_SIEDLER_TEX_LEHM] = createImage_Lehm( _texW, _texH );
    _img[E_SIEDLER_TEX_WEIZEN] = createImage_Weizen( _texW, _texH );
    _img[E_SIEDLER_TEX_WOLLE] = createImage_Wolle( _texW, _texH );
    _img[E_SIEDLER_TEX_ERZ] = createImage_Erz( _texW, _texH );
    _img[E_SIEDLER_TEX_AUGEN_2] = createImage_Augen(2,0);
    _img[E_SIEDLER_TEX_AUGEN_3] = createImage_Augen(3,0);
    _img[E_SIEDLER_TEX_AUGEN_4] = createImage_Augen(4,2);
    _img[E_SIEDLER_TEX_AUGEN_5] = createImage_Augen(5,3);
    _img[E_SIEDLER_TEX_AUGEN_6] = createImage_Augen(6,4);
    _img[E_SIEDLER_TEX_AUGEN_7] = createImage_Augen(7,5);
    _img[E_SIEDLER_TEX_AUGEN_8] = createImage_Augen(8,4);
    _img[E_SIEDLER_TEX_AUGEN_9] = createImage_Augen(9,3);
    _img[E_SIEDLER_TEX_AUGEN_10] = createImage_Augen(10,2);
    _img[E_SIEDLER_TEX_AUGEN_11] = createImage_Augen(11,0);
    _img[E_SIEDLER_TEX_AUGEN_12] = createImage_Augen(12,0);
*/
    // save("data");
/*
    QDir().mkpath( baseDir );

    for ( int i = 0; i < E_SIEDLER_TEX_COUNT; ++i )
    {
        QString fileName = baseDir;
        fileName.append( "/" );
        fileName.append( E_SIEDLER_TEX_FILENAMES[i] );

        if (!_img[i].save( fileName ))
        {
            std::cout << "Cannot save image (" << fileName.toStdString() << ")" << std::endl;
        }
    }
*/
    // load("data");
/*
    for ( int i = 0; i < E_SIEDLER_TEX_COUNT; ++i )
    {
        QString fileName = baseDir;
        fileName.append( "/" );
        fileName.append( E_SIEDLER_TEX_FILENAMES[i] );

        _tex[i] = loadTexture( _driver, fileName );

        if (!_tex[i])
        {
            std::cout << "Cannot load texture (" << fileName.toStdString() << ")" << std::endl;
        }
    }
*/
}

GameData::~GameData()
{
    std::cout << "~" << __FUNCTION__ << "()" << std::endl;

    if ( m_Board )
    {
        delete m_Board;
        m_Board = nullptr;
    }

    for ( size_t i = 0; i < m_Players.size(); ++i )
    {
        PlayerData * player = m_Players[ i ];
        if (player)
        {
            delete player;
        }
    }

    m_Players.clear();
}

} // end namespace pioneers3d

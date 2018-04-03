#include <pioneers3d/Game.hpp>

int main_Pioneers3D( int argc, char** argv );

int main( int argc, char** argv )
{
    return main_Pioneers3D( argc, argv );
}

void enumerateTextures( irr::video::IVideoDriver* driver )
{
    std::cout << "TexCount = " << driver->getTextureCount() << "\n";

    for ( uint32_t i = 0; i < driver->getTextureCount(); ++i )
    {
        irr::video::ITexture* tex = driver->getTextureByIndex( i );
        if ( tex )
        {
            std::cout << "Tex[" << i << "] = " << tex->getName().getPath().c_str() << "\n";
        }
    }
}

int main_Pioneers3D( int argc, char** argv )
{
    std::cout << "// ==========================================================\n";
    std::cout << __FUNCTION__ << "\n";
    std::cout << "// ==========================================================\n";

    glm::ivec3 const desktopSize = getDesktopSize();
    std::cout << "DesktopSize.x = " << desktopSize.x << " px\n";
    std::cout << "DesktopSize.y = " << desktopSize.y << " px\n";
    std::cout << "DesktopSize.z = " << desktopSize.z << " bits\n";
    std::cout << "// ==========================================================\n";

    irr::SIrrlichtCreationParameters cfg;
    cfg.DriverType = irr::video::EDT_OPENGL;
    cfg.WindowSize.Width = desktopSize.x;
    cfg.WindowSize.Height = desktopSize.y;
    cfg.AntiAlias = irr::video::EAAM_QUALITY;
    cfg.Bits = 32;
    cfg.Doublebuffer = true;
    cfg.Vsync = true;
    cfg.EventReceiver = nullptr;
    cfg.Fullscreen = false;
    cfg.Stencilbuffer = true;
    irr::IrrlichtDevice* device = irr::createDeviceEx( cfg );
    assert( device );

    std::cout << toXMLElement( cfg );
    std::cout << "// ==========================================================\n";
//    pioneers3d::Game_t game( device );
//    game.create();
//    game.save( "standard_test1.xml" );
//    game.load( "standard_test1.xml" );
//    game.save( "standard_test2.xml" );

    pioneers3d::Game_t game;
    pioneers3d::Game_createStandard( &game, device );

    enumerateTextures( device->getVideoDriver() );

    return pioneers3d::Game_exec( &game );
}

#if 0

    /// create default board

    CSiedlerTextures _texPool( g_Driver );

    irr::scene::SMesh* mesh = new irr::scene::SMesh;

    srand( (unsigned int)time(NULL) );

    int seg_x = 10;
    int seg_z = 10;

    int i_min = -(seg_x>>1);
    int i_max =  (seg_x>>1);

    int j_min = -(seg_z>>1);
    int j_max =  (seg_z>>1);

    float dx = 10.0f;
    float dz = 10.0f;

    for ( int j = j_min; j <= j_max; ++j )
    {
        for ( int i = i_min; i <= i_max; ++i )
        {
            irr::core::vector3df pos = getBoardPositionFromIndex(dx,dz,i,j);

            irr::scene::SMeshBuffer* hexagon = createMeshBuffer_Hexagon(dx,dz,pos.X,pos.Y,pos.Z);

            int tileIndex = E_SIEDLER_TEX_WASSER + (rand() % 6);

            if ((i<=i_min || i>=i_max) || (j<=j_min || j>=j_max))
                tileIndex = E_SIEDLER_TEX_WASSER;

            hexagon->getMaterial().setTexture( 0, _texPool._tex[tileIndex] );
            mesh->addMeshBuffer( hexagon );
            hexagon->drop();

            if (tileIndex != E_SIEDLER_TEX_WASSER)
            {
                irr::scene::SMeshBuffer* chip = createMeshBuffer_Circle(1.5,33,pos.X,pos.Y+.25f,pos.Z);
                int texIndex = E_SIEDLER_TEX_AUGEN_7;
                do
                {
                    texIndex = E_SIEDLER_TEX_AUGEN_2 + (rand() % 11);
                } while ( texIndex == E_SIEDLER_TEX_AUGEN_7 );
                chip->getMaterial().setTexture( 0, _texPool._tex[texIndex] );
                mesh->addMeshBuffer( chip );
                chip->drop();
            }
        }
    }

    irr::scene::IMeshSceneNode* node = g_SceneM->addMeshSceneNode( mesh, rootNode, -1);
    mesh->drop();

    //Board* board = new Board( g_SceneM );
//    g_Ground = g_SceneM->addTerrainSceneNode( "heightmap_simple.png", rootNode );
//    g_Ground->setScale( core::vector3df(1.0,0.1f,1.0f) );
//    g_Ground->getMaterial(0).Lighting = false;
//    g_Ground->getMaterial(0).setTexture(0, g_Driver->getTexture("heightmap_simple.png") );

    while ( _device && _device->run() && g_Driver )
    {
        g_Driver->beginScene( true, true, video::SColor(255,20,20,20) );

        g_SceneM->drawAll();

        g_Driver->endScene();
    }

    return 0;
#endif

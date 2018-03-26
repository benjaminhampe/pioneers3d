/** Geometry Creator

	This Tutorial is more advanced than
	the previous ones. If you are currently just
	playing around with the Irrlicht-Engine,
	you may want to	look at other examples first.
	This tutorials shows how to create various
	shapes using
	the IGeometryCreator interface class.

	All createable shapes are aligned from left to right,
	while there different combinations of parameters get displayed
	from top to bottom. So if one shape has more instances in one column,
	then it means there are more parameters to play with.

	The GeometryCreator got many new features.

	Also it got some new classes:

	CSinTable,
	CCosTable,
	renderToImage (renders a scene to image of any size with AntiAliasing using supersampling technique)

	have fun

*/
#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include <driverChoice.h>

#include "CGeometryCreatorEx.h"

#define MY_LOGO "media/logo/irr_logo4.png"
#define MY_TEXTURE "media/gfx/earth.jpg"
#define MY_SMALL_FONT "media/fonts/Lucida_Console_Regular_8_AA_Alpha.xml"
#define MY_BIG_FONT "media/fonts/bigfont.png"

/// Definitions

namespace irr
{
	core::stringc currentDateString( ITimer * timer )
	{
		core::stringc txt = "";

		if (timer)
		{
			ITimer::RealTimeDate date = timer->getRealTimeAndDate();
			txt += date.Year; txt += "_";
			if ( date.Month < 10 ) txt += "0";
			txt += date.Month; txt += "_";
			if ( date.Day < 10 ) txt += "0";
			txt += date.Day;
		}

		return txt;
	}

	core::stringc currentTimeString( ITimer * timer )
	{
		core::stringc txt = "";

		if (timer)
		{
			ITimer::RealTimeDate date = timer->getRealTimeAndDate();
			if ( date.Hour < 10 ) txt += "0";
			txt += date.Hour; txt += "_";
			if ( date.Minute < 10 ) txt += "0";
			txt += date.Minute; txt += "_";
			if ( date.Second < 10 ) txt += "0";
			txt += date.Second; txt += "_";
			txt += timer->getRealTime();
		}

		return txt;
	}

	core::stringc currentDateTimeString( ITimer * timer )
	{
		core::stringc txt = "";

		if (timer)
		{
			txt = currentDateString( timer );
			txt += "_";
			txt = currentTimeString( timer );
		}

		return txt;
	}

	class BasicEventReceiver : public IEventReceiver
	{
	private:
		IrrlichtDevice* Device;
		gui::IGUIButton* WireframeButton;
	public:
		BasicEventReceiver( IrrlichtDevice* device )
		: Device(device), WireframeButton(0)
		{
			if (Device)
				Device->setEventReceiver(this);

			gui::IGUIEnvironment* env = Device->getGUIEnvironment();
			if (env)
			{
				WireframeButton = env->addButton(core::recti(5,5,5+48,5+48), env->getRootGUIElement(), -1, L"Wireframe", L"toggle wireframe");
			}
		}

		virtual ~BasicEventReceiver( )
		{

		}


		virtual bool OnEvent (const SEvent &event)
		{
			typedef core::list<scene::ISceneNode*> NodeList;
			typedef core::list<scene::ISceneNode*>::ConstIterator NodeListConstIter;

			/// catch event - wireframe toggle button
			if (event.EventType == EET_GUI_EVENT)
			{
				if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED)
				{
					gui::IGUIElement* caller = event.GUIEvent.Caller;
					if (caller)
					{
						/// wireframe toggle button
						if (caller == WireframeButton)
						{
							if (Device)
							{
								NodeList children = Device->getSceneManager()->getRootSceneNode()->getChildren();
								NodeListConstIter it = children.begin();
								while ( it != children.end() )
								{
									scene::ISceneNode* node = *it;
									if (node)
									{
										u32 matCount = node->getMaterialCount();
										for (u32 i=0; i<matCount; i++)
										{
											video::SMaterial& matRef = node->getMaterial(i);
											matRef.Wireframe = !matRef.Wireframe;
										}
									}
									it++;
								}
							}
							return true;
						}

						/// light toggle button

						/// frontface-culling toggle button

						/// backface-culling toggle button

						/// show-help toggle button
					}
				}
			}

			if(event.EventType == EET_KEY_INPUT_EVENT)
			{
				/// escape key - exit program
				if(event.KeyInput.Key == KEY_ESCAPE)
				{
					exit(0); // we exit
				}

				/// print key - create screenshot image with unique name ( timer based )
				if ( (event.KeyInput.Key == KEY_PRINT || event.KeyInput.Key == KEY_SNAPSHOT) && !event.KeyInput.PressedDown)
				{
					if (Device)
					{
						ITimer* timer = Device->getTimer();
						video::IVideoDriver* driver = Device->getVideoDriver();
						if (driver && timer)
						{
							video::IImage* screenshot = driver->createScreenShot();
							if (screenshot)
							{
								/// create filename
								io::path name = "./screenshot_";
								name += currentDateTimeString( timer );
								name += ".png";

								/// save screenshot
								driver->writeImageToFile( screenshot, name);

								/// delete
								screenshot->drop();
							}
						}
					}
					return true;
				}

				/// space key - enable/disable camera eventreceiver
				if (event.KeyInput.Key == KEY_SPACE && !event.KeyInput.PressedDown)
				{
					if (Device)
					{
						scene::ISceneManager* smgr = Device->getSceneManager();
						scene::ICameraSceneNode* camera = smgr->getActiveCamera();
						if (camera)
						{
							camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
						}
					}
					return true;
				}
			}
			return false;
		}
	};

} // end namespace irr

///   +++ Implementation +++

#include <../source/Irrlicht/CColorConverter.cpp>
#include <../source/Irrlicht/CImage.cpp>
#include <../source/Irrlicht/os.cpp>

using namespace irr;

bool renderToImage(
    IrrlichtDevice* device,
    video::IImage* dst,
    s32 nSamples = 1,
    const video::SColor& clearColor = video::SColor(0,0,0,0),
    bool renderGUI = false, bool debugLog = false);

bool blitImageToImage(
	video::IImage* dst,
	core::position2di dstPos,
	video::IImage* src,
	const core::recti& srcRect, bool debugLog = false );

void createText(
	const core::stringw& name,
	scene::ISceneManager* smgr,
	scene::IMeshSceneNode* src,
	f32 x, f32 y, f32 z,
	gui::IGUIFont* font,
	const video::SColor& textColor = video::SColor(255,255,255,0),
	const video::SColor& bgColor = video::SColor(127,0,0,255) );

void createLight(
	scene::ISceneManager* smgr,
	f32 radius,
	f32 x, f32 y, f32 z,
	const video::SColor& color );

enum E_TILE_TYPE
{
	ETT_WATER = 0,
	ETT_LAND_DESERT, ETT_LAND_WOOD, ETT_LAND_CLAY, ETT_LAND_WOOL, ETT_LAND_CORN, ETT_LAND_ORE,
	ETT_PORT, ETT_PORT_WOOD, ETT_PORT_CLAY, ETT_PORT_WOOL, ETT_PORT_CORN, ETT_PORT_ORE,
	ETT_COUNT
};

void createPioneerBoard(
	IrrlichtDevice* device,
	const core::vector3df& pos = core::vector3df(0,0,100),
	const core::dimension2du& tileCount = core::dimension2du(20,30),
	const core::vector2df& tileSize = core::vector2df(40,40));


/**
	main program
*/


s32 main( s32 argc, c8** argv )
{
	// ask user for driver
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	// create device
	IrrlichtDevice *device = createDevice(driverType, core::dimension2du(1024, 768), 32, false);

	// abort, if no device created.
	if (device == 0)
		return 1;

	// set window title
	device->setWindowCaption(L"IGeometryCreator");
	srand( device->getTimer()->getRealTime() );
	BasicEventReceiver receiver( device );

	// create engine and camera
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();

	// bug-report Linuxmint64, if mipmapping enabled, texturing fails -> ATI Driver Problem
	//driver->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, false);
	//driver->setTextureCreationFlag( video::ETCF_ALWAYS_32_BIT, true);
	//driver->setTextureCreationFlag( video::ETCF_ALLOW_NON_POWER_2, true);

	// enable debugging normals
	smgr->getParameters()->setAttribute( scene::DEBUG_NORMAL_LENGTH, 0.3f );
	smgr->getParameters()->setAttribute( scene::DEBUG_NORMAL_COLOR, video::SColor(255,255,0,0) );
	/*
		create camera
	*/
	SKeyMap KeyMapArray[6];
	KeyMapArray[0].Action = EKA_MOVE_FORWARD;
	KeyMapArray[1].Action = EKA_MOVE_BACKWARD;
	KeyMapArray[2].Action = EKA_STRAFE_LEFT;
	KeyMapArray[3].Action = EKA_STRAFE_RIGHT;
	KeyMapArray[4].Action = EKA_CROUCH;
	KeyMapArray[5].Action = EKA_JUMP_UP;
	KeyMapArray[0].KeyCode = KEY_KEY_W;
	KeyMapArray[1].KeyCode = KEY_KEY_S;
	KeyMapArray[2].KeyCode = KEY_KEY_A;
	KeyMapArray[3].KeyCode = KEY_KEY_D;
	KeyMapArray[4].KeyCode = KEY_KEY_C;
	KeyMapArray[5].KeyCode = KEY_SPACE;

	smgr->addCameraSceneNodeFPS(
		smgr->getRootSceneNode(), 100.0f, .1f, -1, KeyMapArray, 6, false, 1, false, true );

	scene::ICameraSceneNode* cam = smgr->getActiveCamera();
	if (cam)
	{
		cam->setNearValue( 1.0f );
		cam->setFarValue( 10000.0f );
//		cam->setPosition( core::vector3df(104,-4,-160) );
//		cam->setTarget( core::vector3df(58,-15,25) );
		cam->setPosition( core::vector3df(35,12,-180) );
		cam->setTarget( core::vector3df(32,-9,2) );
	}

	/*
		GeometryCreator éxamples
	*/
	createPioneerBoard( device );

	/*
		Lights
	*/
	createLight( smgr, 150, 0, -150, -200, video::SColor(255,255,0,0) );
	createLight( smgr, 150, 100, -120, -100, video::SColor(255,0,255,0) );
	createLight( smgr, 150, 0, -100, 0, video::SColor(255,0,0,255) );
	createLight( smgr, 150, -100, -80, -100, video::SColor(255,255,255,0) );
	createLight( smgr, 150, 0, -50, -100, video::SColor(255,255,255,255) );

	/*
		GeometryCreator éxamples
	*/
	scene::CGeometryCreatorEx* geom = new scene::CGeometryCreatorEx();
	video::ITexture* meshTex = driver->getTexture( MY_LOGO );
	scene::IMesh* mesh = 0;
	f32 x,y;
	f32 dx = 20.f;
	bool bWireframe = true;
	bool bLighting = false;
	bool bFogEnable = false;
	u32 debugMode = scene::EDS_NORMALS | scene::EDS_BBOX; // | scene::EDS_MESH_WIRE_OVERLAY;
	video::ITexture* tex = 0;

	// loop y
	for (u32 i=0; i<5; i++)
	{
		x = -120.f;
		if (i==0)
		{
			bWireframe = true;
			bLighting = false;
			bFogEnable = false;
			debugMode = scene::EDS_NORMALS | scene::EDS_BBOX;
			y = 100.0f;
			tex = 0;
		}
		if (i==1)
		{
			bWireframe = true;
			bLighting = false;
			bFogEnable = false;
			debugMode = scene::EDS_BBOX;
			y = 50.0f;
			tex = meshTex;
		}
		else if (i==2)
		{
			bWireframe = false;
			bLighting = false;
			bFogEnable = false;
			debugMode = scene::EDS_NORMALS | scene::EDS_BBOX;
			y = 0.0f;
			tex = meshTex;
		}
		else if (i==3)
		{
			bWireframe = false;
			bLighting = false;
			bFogEnable = false;
			debugMode = scene::EDS_BBOX;
			y = -50.0f;
			tex = meshTex;
		}
		else if (i==4)
		{
			bWireframe = false;
			bLighting = true;
			bFogEnable = false;
			debugMode = scene::EDS_BBOX;
			y = -100.0f;
			tex = meshTex;
		}

		// loop x
		for (u32 k=0; k<18; k++)
		{
			mesh = 0; // reset pointer
			core::stringw name;
			if (k==0) //! triangle
			{
				name = L"Triangle";
				mesh = geom->createTriangleMesh(
					core::vector3df(-5,-5,-10), 		// point a
					core::vector3df(-1,5,-5), 			// point b
					core::vector3df(4,-4,0),			// point c
					video::SColor(255,255,255,255),			// color a
					video::SColor(127,255,255,255), 	// color b
					video::SColor(63,255,255,255));		// color c
			}
			else if (k==1) //! rect
			{
				name = L"Rect";
				mesh = geom->createRectMesh(
					15,									// width
					10,									// height
					video::SColor(255,255,0,0), 		// bottomLeftColor
					video::SColor(191,255,0,0),		// topLeftColor
					video::SColor(127,0,255,0), 		// topRightColor
					video::SColor(63,0,0,255));		// bottomRightColor
			}
			else if (k==2) //! roundrect
			{
				name = L"RoundRect";
				mesh = geom->createRoundRectMesh(
					15,									// width
					10,									// height
					4,									// rx
					4,									// ry
					13, 								// tesselation
					true,								// texture-mode
					video::SColor(63,255,255,255),		// outlineColor
					video::SColor(255,255,255,255));	// centerColor
			}
			else if (k==3) //! hexagon ( used for pioneers/settlers of catan )
			{
				name = L"Pioneer-Hexagon";
				mesh = geom->createHexagonMesh(
					core::vector3df(15,15,1),			// size
					false,								// size
					false,								// size
					video::SColor(127,255,255,255));	// color
			}
			else if (k==4) //! circle
			{
				name = L"Circle";
				mesh = geom->createCircleMesh(
					7.5f,								// radius
					33, 								// segments
					false,								// filled
					video::SColor(63,255,255,255), 		// outerColor
					video::SColor(255,255,255,255));	// innerColor
			}
			else if (k==5) //! ellipse
			{
				name = L"Ellipse";
				mesh = geom->createEllipseMesh(
					7.5f,								// radius x
					5,									// radius y
					33,									// segments
					video::SColor(63,255,255,255), 		// outerColor
					video::SColor(255,255,255,255));	// innerColor
			}
			else if (k==6) //! ring
			{
				name = L"Ring";
				mesh = geom->createRingMesh(
					7.5f,								// outerRadius
					6,									// innerRadius
					33,									// segments
					false,								// texture mode
					video::SColor(255,255,255,255),		// outerColor
					video::SColor(127,255,255,255));	// innerColor
			}
			else if (k==7)	//! arc
			{
				name = L"Arc";
				mesh = geom->createArcMesh(
					7.5f,								// outerRadius
					7, 									// innerRadius
					15,									// angle start
					225, 								// angle end
					33, 								// segments
					false,								// texture mode
					video::SColor(127,255,255,255),		// outerColor
					video::SColor(255,255,255,255));	// innerColor
			}
			else if (k==8)	//! upper sphere half
			{
				name = L"Upper sphere half";
				mesh = geom->createUpperSphereHalfMesh(
					7.5f,								// radius
					33,									// tessCircle
					17, 									// tessRows
					video::SColor(191,255,255,255),		// vertex color
					true );								// close bottom
			}
			else if (k==9)	//! lower sphere half
			{
				name = L"Lower sphere half";
				mesh = geom->createLowerSphereHalfMesh(
					7.5f,								// radius
					33,									// tessCircle
					17, 									// tessRows
					video::SColor(191,255,255,255),		// vertex color
					true );								// clost top
			}
			else if (k==10) //! cylinder
			{
				name = L"Cylinder";
				mesh = geom->createCylinderMesh(
					7.5f,								// radius
					15,									// height
					33,									// circle segments
					13,									// hull segments
					true,								// closeTop
					true,								// closeBottom
					false,								// bOneMaterial
					video::SColor(127,255,255,255),		// color of vertices
					video::SColor(255,255,255,255),		// topColor
					video::SColor(255,255,255,255));	// bottomColor
			}
			else if (k==11) //! capsule
			{
				name = L"Capsule";
				mesh = geom->createCapsuleMesh(
					5,									// radius
					5, 									// height
					33,									// tessCircle
					13,									// tessRows
					8,									// tessHull
					false,								// one material
					video::SColor(255,255,255,255),		// color
					video::SColor(80,255,255,255),		// topColor
					video::SColor(255,100,200,100));		// bottomColor
			}
			else if (k==12) //! tube
			{
				name = L"Tube";
				mesh = geom->createTubeMesh(
					7.5f,								// outerRadius
					5,									// innerRadius
					15,									// height
					33,									// circle segments
					17,									// hull segments ( y direction )
					true,								// closeTop
					true,								// closeBottom
					false,								// bRepeatTextureCircle
					false,								// bRepeatTextureHull
					video::SColor(255,255,255,255));	// color
			}
			else if (k==13) //! ellipsoid (egg)
			{
				name = L"Ellipsoid";
				mesh = geom->createEllipsoidMesh(
					8.5f,								// radiusX
					7.5f,								// radiusY
					8.5f,								// radiusZ
					33,									// polyCountX
					33,									// polyCountY
					0,									// polyCountZ, has no influence yet
					video::SColor(255,255,255,255));	// color
			}
			else if (k==14) //! torus (donut)
			{
				name = L"Torus";
				mesh = geom->createTorusMesh(
					5.5f,								// outerRadius
					4.0f,									// innerRadius
					65,									// outerSegments
					33,									// innerSegments
					video::SColor(255,255,255,255));	// color
			}
			else if (k==15) //! box ( with 6 textures for crates, cargo-containers, etc... )
			{
				name = L"Box";
				mesh = geom->createBoxMesh(
					core::vector3df(15,10,12),			// size
					video::SColor(255,255,255,255),		// color
					6);									// material
			}
			else if (k==16) //! path2d [1]
			{
				//! linear paths
				//	IMesh* createPath2dMesh(
				//		const core::array<core::vector2df>& points,	const video::SColor& color,
				//		f32 thickness, s32 lineJoin, bool bRepeatTexture,
				//		core::rectf* clipRect = 0, bool bZoomData = false) const;

				name = L"Path2d one color";
				core::array<core::vector2df> Points;
				Points.reallocate( 16 );
				Points.set_used( 0 );
				Points.push_back( core::vector2df( 0,0 ) );
				Points.push_back( core::vector2df( 1,2 ) );
				Points.push_back( core::vector2df( 2,3 ) );
				Points.push_back( core::vector2df( 4,6 ) );
				Points.push_back( core::vector2df( 5,3 ) );
				Points.push_back( core::vector2df( 6,5 ) );
				Points.push_back( core::vector2df( 7,4 ) );
				Points.push_back( core::vector2df( 8,0 ) );
				Points.push_back( core::vector2df( 9,2 ) );
				Points.push_back( core::vector2df( 10,3 ) );
				Points.push_back( core::vector2df( 11,6 ) );
				Points.push_back( core::vector2df( 12,3 ) );
				Points.push_back( core::vector2df( 13,5 ) );
				Points.push_back( core::vector2df( 14,4 ) );
				Points.push_back( core::vector2df( 15,0 ) );
				video::SColor white(255,255,255,255);
				core::array<video::SColor> colors; colors.push_back(white);

				mesh = geom->createLine2dMesh( Points, colors,0.55f, 0, 0, true );
			}
			else if (k==17) //! path2d [2]
			{
				//! linear paths
				//	IMesh* createPath2dMesh(
				//		const core::array<core::vector2df>& points,	const core::array<video::SColor>& colors,
				//		f32 thickness, s32 lineJoin, bool bRepeatTexture,
				//		core::rectf* clipRect = 0, bool bZoomData = false) const;
				name = L"Path2d with colorarray";
				core::array<core::vector2df> Points;
				core::array<video::SColor> Colors;

				Points.reallocate(10);
				Points.set_used(0);
				Colors.reallocate(10);
				Colors.set_used(0);

				f32 step = 15.0f/10.0f;
				for (u32 i=0; i<10; i++)
				{
					Points.push_back( core::vector2df( step*i, 0.15f*(rand()%100) ) );
					Colors.push_back( video::SColor(rand()%255,rand()%255,rand()%255,rand()%255) );
				}
				mesh = geom->createLine2dMesh( Points, Colors, 1.0f,0 );
			}
			else
			{

			}

			if (mesh)
			{
				scene::IMeshSceneNode* node = smgr->addMeshSceneNode(
					mesh, smgr->getRootSceneNode(), -1,	core::vector3df(x,y,0),	core::vector3df(0,0,0),	core::vector3df(1,1,1) );

				if (node)
				{
					//
					if (tex)
					{
						if (name == L"Ellipsoid")
						{
							node->setMaterialTexture(0, driver->getTexture( MY_TEXTURE ));
						}
						else
						{
							node->setMaterialTexture(0, tex);
						}
					}

					node->setMaterialFlag( video::EMF_WIREFRAME, bWireframe );
					node->setMaterialFlag( video::EMF_LIGHTING, bLighting );
					node->setMaterialFlag( video::EMF_FOG_ENABLE, bFogEnable );
					node->setDebugDataVisible( debugMode );
					gui::IGUIFont* font = env->getFont( MY_SMALL_FONT );

					// create info text for each IMeshSceneNode
					createText( name, smgr, node, 0, -25, 0, font );
				}
				mesh->drop();
			}

			x+=dx;
		} // END FOR
	} // END FOR

	/*
		Render big image from scene and save to file ( tga is quick but needs much space )
	*/
	{
		core::dimension2du screen = driver->getScreenSize();

		video::IImage* rtt = driver->createImage( video::ECF_A8R8G8B8, core::dimension2du(4*screen.Width,4*screen.Height) );

		if (rtt)
		{
			device->run();

			renderToImage( device, rtt, 4, video::SColor(255,100,100,205), false /* dont render gui */, false);

			driver->beginScene(true, true, video::SColor(255,0,0,255));

			smgr->drawAll();

			gui::IGUIFont* font = env->getFont( MY_SMALL_FONT );

			// driver->setTransform( video::ETS_WORLD, core::IdentityMatrix );
			// driver->setTransform( video::ETS_VIEW, core::IdentityMatrix );

			// virtual void draw(const core::stringw& text, const core::rect<s32>& position,
			// 		video::SColor color, bool hcenter=false, bool vcenter=false,
			// 		const core::rect<s32>* clip=0) = 0;

			font->draw( L"Save image to \"GeometryCreator.png\" ...",
				core::recti( core::position2di(0,0), driver->getScreenSize()),
				video::SColor(255,255,255,255),	true, true);

			driver->endScene();

			driver->writeImageToFile( rtt, io::path("GeometryCreator.png") );

			rtt->drop();
		}
		else
		{
			device->getLogger()->log( "Could not create big image.", ELL_ERROR);
		}
	}

	gui::IGUIStaticText* help = env->addStaticText( L"use WASD for Camera", core::recti(0,0,250,20), true, true, env->getRootGUIElement(), -1, true );
	help->setOverrideFont( env->getFont( MY_SMALL_FONT ) );
	help->setOverrideColor( video::SColor(255,255,255,255) );

	/*
		main loop
	*/
	u32 frames=0;
	while(device->run())
	{
		driver->beginScene(true, true, video::SColor(0,100,100,100));
		smgr->drawAll();
		env->drawAll();
		driver->endScene();

		if (++frames==100)
		{
			core::stringw str = L"GeometryCreator Example using Irrlicht Engine [";
			str += driver->getName();
			str += L"] FPS(";
			str += (s32)driver->getFPS();
			str += L"), Tris(";
			str += (s32)driver->getPrimitiveCountDrawn();
			str += L")";
			scene::ICameraSceneNode* camera = smgr->getActiveCamera();

			if (camera)
			{
				str += L", Cam pos(";
				str += core::round32(camera->getPosition().X);
				str += L", ";
				str += core::round32(camera->getPosition().Y);
				str += L", ";
				str += core::round32(camera->getPosition().Z);
				str += L"), eye(";
				str += core::round32(camera->getTarget().X);
				str += L", ";
				str += core::round32(camera->getTarget().Y);
				str += L", ";
				str += core::round32(camera->getTarget().Z);
				str += L")";
			}

			device->setWindowCaption(str.c_str());
			frames=0;
		}
	}

	device->drop();

	return 0;
}

/**
	creates a ITextSceneNode displaying infos from an IMeshSceneNode
	like BufferCount, VertexCount and IndexCount
*/

void createText(
	const core::stringw& name,
	scene::ISceneManager* smgr,
	scene::IMeshSceneNode* src,
	f32 x, f32 y, f32 z,
	gui::IGUIFont* font,
	const video::SColor& textColor,
	const video::SColor& bgColor )
{
	if (!smgr)
		return;

	if (!src)
		return;

	if (!font)
		return;

	u32 vCount = 0;
	u32 iCount = 0;
	u32 bCount = 0;

	scene::IMesh* mesh = src->getMesh();
	if (mesh)
	{
		bCount = mesh->getMeshBufferCount();
		for (u32 b=0; b<bCount; b++)
		{
			scene::IMeshBuffer* pBuffer = mesh->getMeshBuffer(b);
			if (pBuffer)
			{
				vCount += pBuffer->getVertexCount();
				iCount += pBuffer->getIndexCount();
			}
		}
	}

	core::stringw txt(name); txt+="\n";
	txt += L"b = "; txt+=(s32)bCount; txt+=L"\n";
	txt += L"v = "; txt+=(s32)vCount; txt+=L"\n";
	txt += L"i = "; txt+=(s32)iCount; txt+=L"\n";

	smgr->addTextSceneNode( font, txt.c_str(), textColor, smgr->getRootSceneNode(), src->getAbsolutePosition() + core::vector3df(x,y,z), -1);
}

/**
	creates a light and a sphere at the lights position with color of light
*/
void createLight(
	scene::ISceneManager* smgr,
	f32 radius,
	f32 x, f32 y, f32 z,
	const video::SColor& color )
{
	scene::ILightSceneNode* light = smgr->addLightSceneNode(
		smgr->getRootSceneNode(), core::vector3df(x,y,z), color, radius, -1);

	scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(
		core::vector3df(x,y,z), radius, 0.001f, core::vector3df(0,1,0), 0,0 );

	light->addAnimator( anim );

	scene::IMesh* sphere = smgr->getGeometryCreator()->createSphereMesh( 1, 16,16 );

	scene::IMeshSceneNode* node = smgr->addMeshSceneNode(
		sphere, smgr->getRootSceneNode(), -1, light->getAbsolutePosition());

	sphere->drop();

	if (node)
	{
		node->setMaterialType( video::EMT_SOLID );
		node->setMaterialFlag( video::EMF_WIREFRAME, false );
		node->setMaterialFlag( video::EMF_LIGHTING, false );
		node->setMaterialFlag( video::EMF_FOG_ENABLE, false );
		smgr->getMeshManipulator()->setVertexColors(node->getMesh(), color);
		node->addAnimator( anim );
	}

	anim->drop();
}

/**
	board for pioneers game. ( Die Siedler von Catan )
	with colors instead of textures for now
*/

void createPioneerBoard(
	IrrlichtDevice* device,
	const core::vector3df& pos,
	const core::dimension2du& tileCount,
	const core::vector2df& tileSize)
{
	if (!device)
		return;

	scene::ISceneManager* smgr = device->getSceneManager();
	const scene::IGeometryCreatorEx* geom = new scene::CGeometryCreatorEx();

	if (!geom)
		return;

	video::SColor colors[ETT_COUNT];
	colors[ETT_WATER].set(255,0,0,0);
	colors[ETT_LAND_DESERT].set(255,255,255,200);
	colors[ETT_LAND_WOOD].set(255,0,200,0);
	colors[ETT_LAND_CLAY].set(255,255,0,0);
	colors[ETT_LAND_WOOL].set(255,255,255,255);
	colors[ETT_LAND_CORN].set(255,255,255,0);
	colors[ETT_LAND_ORE].set(255,55,55,55);
	colors[ETT_PORT].set(255,255,255,255);
	colors[ETT_PORT_WOOD].set(255,100,200,100);
	colors[ETT_PORT_CLAY].set(255,255,100,100);
	colors[ETT_PORT_WOOL].set(255,225,225,225);
	colors[ETT_PORT_CORN].set(255,255,255,155);
	colors[ETT_PORT_ORE].set(255,155,155,155);

	srand( device->getTimer()->getRealTime() );

	const f32 offX = -0.5f*tileSize.X*tileCount.Width;
	const f32 offY = -0.5f*tileSize.Y*tileCount.Height;

	for (u32 y=0; y<tileCount.Height; y++)
	{
		for (u32 x=0; x<tileCount.Width; x++)
		{
			E_TILE_TYPE type = ETT_WATER; //rand()%EPTC_COUNT
			video::SColor color = colors[type];

			if (type == ETT_WATER)
			{
				// s32 rgAdd = rand()%50;
				s32 bAdd = 40+rand()%30;
				//color.setRed( color.getRed()+rgAdd );
				//color.setGreen( color.getGreen()+rgAdd );
				//color.setBlue( (u32)((s32)color.getBlue()+bAdd) );
				color.setRed( color.getRed()+bAdd );
				color.setGreen( color.getGreen()+bAdd );
				color.setBlue( color.getBlue()+bAdd );
			}

			scene::IMesh* mesh = geom->createHexagonMesh( core::vector3df(tileSize.X, tileSize.Y, 0), false, false, color );
			if (mesh)
			{
				/*
					code to position pioneer tiles according to 2d indices

					magic: 	- rows have a distance of 0.75 * tileSize.Y
							- add offset to x-coord, when y-index is odd (1,3,...)
				*/

				core::vector3df p( offX+pos.X+x*tileSize.X, offY+pos.Y+y*tileSize.Y*0.75f, pos.Z);

				if (y%2 != 0)
					p.X += 0.5f*tileSize.X;

				/*
					create scene-nodes

					todo: add hexagons to one big mesh, create only one scenenode for gameboard
				*/

				scene::IMeshSceneNode* node = smgr->addMeshSceneNode(
					mesh, smgr->getRootSceneNode(), -1,
					p,
					core::vector3df( 0,0,0 ),
					core::vector3df( 1,1,1 ));

				mesh->drop();

				/*
					set some flags
				*/

				if (node)
				{
					node->setMaterialFlag( video::EMF_WIREFRAME, false );
					node->setMaterialFlag( video::EMF_LIGHTING, false );
					node->setMaterialFlag( video::EMF_FOG_ENABLE, false );
					node->setDebugDataVisible( 0 );
				}
			}
		}
	}

	geom->drop();
}

/**
	renderToImage
*/

bool renderToImage( IrrlichtDevice* device, video::IImage* dst, s32 nSamples, const video::SColor& clearColor, bool renderGUI, bool debugLog)
{
	// print call params
	if (debugLog)
		printf(	"renderToImage( nSamples=%i, clearColor(%i,%i,%i,%i)\n", nSamples,
			clearColor.getAlpha(), clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue() );

	// abort
    if (!device)
	{
		printf("No Irrlicht-Device found.\n");
        return false;
	}

	// abort
    if (!dst)
	{
		printf("No destination image found.\n");
        return false;
	}

	// local pointers
	video::IVideoDriver* driver = device->getVideoDriver();
	gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
	scene::ISceneManager* smgr = device->getSceneManager();
	scene::ICameraSceneNode* camera = smgr->getActiveCamera();

	// abort
	if (!camera)
	{
		printf("No active camera found.\n");
		return false;
	}

	//! decompose camera's projection-matrix in d3d semantics

	core::matrix4 projMat = camera->getProjectionMatrix();

	bool IsOrthogonal = true;

	if ( core::equals( projMat(3,3), 0.f ) )
		IsOrthogonal = false;

	if ( !core::equals( projMat(2,3), 0.f ) )
		IsOrthogonal = false;

    f32 Left;
    f32 Right;
    f32 Bottom;
    f32 Top;
    f32 Near;
    f32 Far;

	if (IsOrthogonal)
	{
		Near = -projMat(3,2)/projMat(2,2);
		Far = -(projMat(3,2)-1.f)/projMat(2,2);
		Left = -(projMat(3,0)+1.f)/projMat(0,0);
		Right = -(projMat(3,0)-1.f)/projMat(0,0);
		Top = -(projMat(3,1)-1.f)/projMat(1,1);
		Bottom = -(projMat(3,1)+1.f)/projMat(1,1);
	}
	else
	{
		Near = -projMat(3,2)/projMat(2,2);
		Far = -projMat(3,2)/(projMat(2,2)-1.f);
		Left = -Near*(projMat(2,0)+1.f)/projMat(0,0);
		Right = -Near*(projMat(2,0)-1.f)/projMat(0,0);
		Top = -Near*(projMat(2,1)-1.f)/projMat(1,1);
		Bottom = -Near*(projMat(2,1)+1.f)/projMat(1,1);
	}
	Near = camera->getNearValue();	// take the values directly from Camera
	Far = camera->getFarValue();	// due to f32 rounding errors

	//! ----------------------------------------------------------------------
	//! calculate Border / get max thickness used by all registered materials
	//! ----------------------------------------------------------------------

	s32 Border = 0;
	f32 thickness = 0.0f;

    const core::list<scene::ISceneNode*>& children = smgr->getRootSceneNode()->getChildren();
    core::list<scene::ISceneNode*>::ConstIterator it = children.begin();

    while (it != children.end())
	{
		scene::ISceneNode* node = (*it);
		if (node)
		{
			u32 matCount = node->getMaterialCount();
			for (u32 m = 0; m < matCount; ++m)
			{
				if (thickness < node->getMaterial(m).Thickness)
					thickness = node->getMaterial(m).Thickness;
			}
		}
		it++;
	}

	Border = core::ceil32( thickness );

	//! ------------------------------------------------------------------------------------------
	//! choose render-mode: offscreen or onscreen depending on AA, nSamples and RTT capabilities
	//! ------------------------------------------------------------------------------------------

	//! @var nSamples - AntiAliasing depth > 1 make bigger rtts or downscale render-result by factor nSamples while having filter-methods enabled
	//! the framebuffer will always be downscaled by fast software bilinear filtering using colorkey/transparency to blend better into final image
	//! hardware-scaling: bilinear, trilinear or anisotropic texture-filtering available with irrlicht-engine
	//! software scaling: nearest, bilinear, bicubic downscaling available:
	//!  				  bilinear has best compromise for downscaling ( there is much more information-loss due to resize than interpolation)
	//! default: 1 (<2) - no AA/downscaling done

	//! @var clearColor - argb32 color, the final image will filled with
	//! before writing into it and be used as colorkey for AA/software bilinear downscaling operation

	//! @var DoOffscreen - default=false, onscreen (framebuffer)
	//! false -	onscreen-rendering using framebuffer/display.
	//! 		doublebuffer is possible, but will not prevent the showing of each rendered tile-texture
	//! true - 	offscreen-rendering using render-target-textures

	bool DoOffscreen = false;

	//! ----------------------------------------------------------------
	//! collect video-driver infos
	//! ----------------------------------------------------------------

	const core::dimension2du ScreenSize = driver->getScreenSize();
	const video::ECOLOR_FORMAT ScreenFormat = driver->getColorFormat();
	const u32 ScreenBits = video::IImage::getBitsPerPixelFromFormat( ScreenFormat );
    const io::IAttributes& info = driver->getDriverAttributes();
    const core::dimension2du MaxRTTSize = driver->getMaxTextureSize();
    const u32 MaxAA = info.getAttributeAsInt( "AntiAlias" );
    const u32 MaxAF = info.getAttributeAsInt( "MaxAnisotropy" );
    const bool HasNPOT = driver->queryFeature( video::EVDF_TEXTURE_NPOT );
    const bool HasNSQR = driver->queryFeature( video::EVDF_TEXTURE_NSQUARE );
	const bool HasRTT = driver->queryFeature( video::EVDF_RENDER_TO_TARGET);
	const bool HasMTT = driver->queryFeature( video::EVDF_MULTITEXTURE);
	const bool HasMRT = driver->queryFeature( video::EVDF_MULTIPLE_RENDER_TARGETS);
	const bool HasATC = driver->queryFeature( video::EVDF_ALPHA_TO_COVERAGE);
	const bool HasBTF = driver->queryFeature( video::EVDF_BILINEAR_FILTER);
	const bool HasCMK = driver->queryFeature( video::EVDF_COLOR_MASK);
	const bool HasMMP = driver->queryFeature( video::EVDF_MIP_MAP);
	const bool HasMMA = driver->queryFeature( video::EVDF_MIP_MAP_AUTO_UPDATE);
	const bool HasOCC = driver->queryFeature( video::EVDF_OCCLUSION_QUERY);
	const bool HasPOF = driver->queryFeature( video::EVDF_POLYGON_OFFSET);

	if (debugLog)
	{
		printf("ScreenSize = %i x %i x %i\n", ScreenSize.Width, ScreenSize.Height, ScreenBits);
		printf("MaxRTTSize = %i x %i\n", MaxRTTSize.Width, MaxRTTSize.Height);
		printf("MaxAA = %i\n", MaxAA);
		printf("MaxAF = %i\n", MaxAF);
		printf("HasNPOT = %s\n", HasNPOT?"true":"false");
		printf("HasNSQR = %s\n", HasNSQR?"true":"false");
		printf("HasRTT = %s\n", HasRTT?"true":"false");
		printf("HasMTT = %s\n", HasMTT?"true":"false");
		printf("HasMRT = %s\n", HasMRT?"true":"false");
		printf("HasATC = %s\n", HasATC?"true":"false");
		printf("HasBTF = %s\n", HasBTF?"true":"false");
		printf("HasCMK = %s\n", HasCMK?"true":"false");
		printf("HasMMP = %s\n", HasMMP?"true":"false");
		printf("HasMMA = %s\n", HasMMA?"true":"false");
		printf("HasOCC = %s\n", HasOCC?"true":"false");
		printf("HasPOF = %s\n", HasPOF?"true":"false");
	}

    s32 RTTWidth = ScreenSize.Width;				// equals the actual rtt size before down scaling factor nSamples AA and writing to final Image
    s32 RTTHeight = ScreenSize.Height;				// the render-target is always a texture (offscreen) or the framebuffer (onscreen)
    s32 RTTWidthNB = RTTWidth - 2*Border;			// the border equals the overlapping during rendering due to material-thickness > 0
    s32 RTTHeightNB = RTTHeight - 2*Border;			// the area that gets written to unique places, while the border regions can overlapp ( same pos, but writing/adding different image-content )

	// so the position increment for the final writing is always RTTWidthNB or RTTHeightNB

    const s32 ImageWidth = (s32)dst->getDimension().Width;		// width of the final image
    const s32 ImageHeight = (s32)dst->getDimension().Height;	// height of the final image
    const video::ECOLOR_FORMAT ImageFormat = dst->getColorFormat();			// color-format of the final image, i.e. video::ECF_A8R8G8B8, ECF_R8G8B8, ECF_R16 for heightmaps ( bilinear, anisotropic )
	const s32 CountX = core::ceil32( (f32)ImageWidth / (f32)RTTWidthNB );
	const s32 CountY = core::ceil32( (f32)ImageHeight / (f32)RTTHeightNB );

	//! ------------------------------------------------------------------------------------------
	//! start render loop
	//! ------------------------------------------------------------------------------------------

    s32 IndexX = 0;
    s32 IndexY = 0;
	s32 dstX = -Border;
	s32 dstY = -Border;

	for ( IndexY = 0; IndexY < CountY; ++IndexY)
	{
		// reset row
		dstX = -Border;

		for ( IndexX = 0; IndexX < CountX; ++IndexX)
		{
			const f32 fLeft = Left + (Right - Left) * (f32)( IndexX * RTTWidthNB - Border )/(f32)ImageWidth;
			const f32 fRight = fLeft + (Right - Left) * (f32)RTTWidth / (f32)ImageWidth;
			const f32 fTop = Top - (Top - Bottom) * (f32)( IndexY * RTTHeightNB - Border )/(f32)ImageHeight;
			const f32 fBottom = fTop - (Top - Bottom) * (f32)RTTHeight / (f32)ImageHeight;
			const f32 fNear = Near;
			const f32 fFar = Far;

			//! ------------------------------------------------------------------------------------------
			//! build and set current projection-matrix
			//! ------------------------------------------------------------------------------------------

			core::matrix4 tmpProj = core::IdentityMatrix;
			if (IsOrthogonal)
			{
				tmpProj(0,0) = 2.f / (fRight - fLeft);
				tmpProj(1,1) = 2.f / (fTop - fBottom);
				tmpProj(2,2) = 1.f / (fFar - fNear);
				tmpProj(3,3) = 1.f;
				tmpProj(3,0) = (fLeft + fRight) / (fLeft - fRight);
				tmpProj(3,1) = (fTop + fBottom) / (fBottom - fTop);
				tmpProj(3,2) = fNear / (fNear - fFar);
			}
			else
			{
				tmpProj(0,0) = 2.f*fNear / (fRight - fLeft);
				tmpProj(1,1) = 2.f*fNear / (fTop - fBottom);
				tmpProj(2,0) = (fLeft + fRight) / (fLeft - fRight);
				tmpProj(2,1) = (fTop + fBottom) / (fBottom - fTop);
				tmpProj(2,2) = fFar / (fFar - fNear);
				tmpProj(2,3) = 1.f;
				tmpProj(3,2) = fNear*fFar / (fNear - fFar);
				tmpProj(3,3) = 0.f;
			}
			camera->setProjectionMatrix(tmpProj);

			//! ------------------------------------------------------------------------------------------
			//! now render all to current render-target
			//! ------------------------------------------------------------------------------------------

			driver->beginScene( true, true, clearColor ); // video::SColor(255,200,200,255)

				smgr->drawAll();
				if (renderGUI)
					guienv->drawAll();

			driver->endScene();

			//! ------------------------------------------------------------------------------------------
			//! write current render-target to final image
			//! ------------------------------------------------------------------------------------------

			video::IImage* src = driver->createScreenShot( ImageFormat, video::ERT_FRAME_BUFFER);
			if (src)
			{
				s32 x2 = src->getDimension().Width;
				s32 y2 = src->getDimension().Height;

				blitImageToImage( dst, core::position2di(dstX, dstY), src, core::recti(Border, Border, x2-Border, y2-Border), debugLog );

				src->drop();
			}
			dstX += RTTWidthNB;
		}
		dstY += RTTHeightNB;
	}

	//! ------------------------------------------------------------------------------------------
	//! reset camera's projection-matrix
	//! ------------------------------------------------------------------------------------------

	camera->setProjectionMatrix( projMat, IsOrthogonal);
    return true;
}

/**
	blitImageToImage, needed for renderToImage for now
*/

bool blitImageToImage(
	video::IImage* dst, core::position2di dstPos,
	video::IImage* src, const core::recti& srcRect, bool debugLog)
{
	if (debugLog)
	{	printf("blitImageToImage(x=%i,y=%i,rect(%i,%i,%i,%i))\n", dstPos.X, dstPos.Y,
			srcRect.UpperLeftCorner.X, srcRect.UpperLeftCorner.Y,srcRect.LowerRightCorner.X, srcRect.LowerRightCorner.Y);
	}

	if (!dst)
	{
		printf("Destination Image does not exist.\n");
		return false;
	}

	if (!src)
	{
		printf("Source Image does not exist.\n");
		return false;
	}

	const core::dimension2du& dstSize = dst->getDimension();
	const core::dimension2du& srcSize = src->getDimension();

	if (dstPos.X >= (s32)dstSize.Width)	// ! if you forget cast to s32 it always fails when X < 0
		return false;

	if (dstPos.Y >= (s32)dstSize.Height) // ! if you forget cast to s32 it always fails when Y < 0
		return false;

	u32 dstPitch = dst->getPitch();
	u32 dstBPP = dst->getBytesPerPixel();
	u8* dstPtr = (u8*)dst->lock();

	u32 srcPitch = src->getPitch();
	u32 srcBPP = src->getBytesPerPixel();
	u8* srcPtr = (u8*)src->lock();

	if (debugLog)
	{
		printf("dst: %i, %i, pos=%i, %i, bpp=%i, pitch=%i\n", dstSize.Width, dstSize.Height, dstPos.X, dstPos.Y, dstBPP, dstPitch);
		printf("src: %i, %i, bpp=%i, pitch=%i\n", srcSize.Width, srcSize.Height, srcBPP, srcPitch);
	}
	// inc dst pointer to start-pos;
	// dstPtr += (u32)dstPos.X*dstBPP + (u32)dstPos.Y*dstPitch;

	// slow and save, can be much optimized, but not now
	for (u32 y=0; y<(u32)srcRect.getHeight(); ++y)
	{
		for (u32 x=0; x<(u32)srcRect.getWidth(); ++x)
		{
			s32 sx = srcRect.UpperLeftCorner.X + x;
			s32 sy = srcRect.UpperLeftCorner.Y + y;
			if (sx>=0 && sy>=0)
			{
				video::SColor color = src->getPixel( (u32)sx, (u32)sy);
				s32 dx = dstPos.X + (s32)x;
				s32 dy = dstPos.Y + (s32)y;
				if (dx>=0 && dy>=0)
					dst->setPixel( (u32)dx, (u32)dy, color);
			}
		}
	}

	src->unlock();
	dst->unlock();
	return true;
}



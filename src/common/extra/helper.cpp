// Copyright (C) 2002-2012 Benjamin Hampe
// For conditions of distribution and use, see copyright notice in DarkGL.h

#include "helper.h"

#include <irrlicht.h>

namespace irr
{

	void showAboutText( gui::IGUIEnvironment* env )
	{
		if (!env)
			return;
		env->addMessageBox(L"MessageBox", L"Hello World.");
	}

	bool hasModalDialog( gui::IGUIEnvironment* env )
	{
		if (!env)
			return false;

		gui::IGUIElement * focused = env->getFocus();
		while ( focused )
		{
			if ( focused->isVisible() && focused->hasType( gui::EGUIET_MODAL_SCREEN ) )
				return true;
			focused = focused->getParent();
		}
		return false;
	}

	void setSkinTransparency( gui::IGUISkin * skin, s32 alpha )
	{
		for (s32 i=0; i<gui::EGDC_COUNT ; ++i)
		{
			video::SColor col = skin->getColor((gui::EGUI_DEFAULT_COLOR)i);
			col.setAlpha(alpha);
			skin->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
		}
	}

	void setActiveCamera(scene::ISceneManager* smgr, scene::ICameraSceneNode* newActive)
	{
		if (!smgr)
			return;

		scene::ICameraSceneNode * active = smgr->getActiveCamera();
		if (active)
			active->setInputReceiverEnabled(false);

		if (newActive)
		{
			newActive->setInputReceiverEnabled(true);
			smgr->setActiveCamera(newActive);
		}
		else
		{
			smgr->setActiveCamera(0);
		}
	}

	void onKillFocus( scene::ISceneManager* smgr )
	{
		if (!smgr)
			return;

		// Avoid that the FPS-camera continues moving when the user presses alt-tab while
		// moving the camera.
		scene::ICameraSceneNode* camera = smgr->getActiveCamera();
		if (camera)
		{
			const core::list<scene::ISceneNodeAnimator*>& animators = camera->getAnimators();
			core::list<irr::scene::ISceneNodeAnimator*>::ConstIterator iter = animators.begin();
			while ( iter != animators.end() )
			{
				if ( (*iter)->getType() == scene::ESNAT_CAMERA_FPS )
				{
					// we send a key-down event for all keys used by this animator
					scene::ISceneNodeAnimatorCameraFPS * fpsAnimator = static_cast<scene::ISceneNodeAnimatorCameraFPS*>(*iter);
					const core::array<SKeyMap>& keyMap = fpsAnimator->getKeyMap();
					for ( irr::u32 i=0; i< keyMap.size(); ++i )
					{
						irr::SEvent event;
						event.EventType = EET_KEY_INPUT_EVENT;
						event.KeyInput.Key = keyMap[i].KeyCode;
						event.KeyInput.PressedDown = false;
						fpsAnimator->OnEvent(event);
					}
				}
				++iter;
			}
		}
	}

	IrrlichtDevice* createDeviceGL()
    {

	    // create null-device
	    IrrlichtDevice* nulldev = createDevice(video::EDT_NULL);
	    bool bHasOpenGL = false;
	    bool bHasBurning = false;
	    bool bHasSoftware = false;

	    SIrrlichtCreationParameters params;
	    params.Fullscreen = false;
	    if (nulldev)
	    {
		    //params.WindowSize = nulldev->getVideoModeList()->getDesktopResolution() - core::dimension2du(100,200);
		    params.WindowSize = nulldev->getVideoModeList()->getDesktopResolution() - core::dimension2du(100,100);
		    //params.WindowSize = core::dimension2du(800,600);
		    params.Bits = nulldev->getVideoModeList()->getDesktopDepth();

		    if (nulldev->isDriverSupported(video::EDT_SOFTWARE))
		    {
			    bHasSoftware = true;
			    params.DriverType = video::EDT_SOFTWARE;
		    }
		    if (nulldev->isDriverSupported(video::EDT_BURNINGSVIDEO))
		    {
			    bHasBurning = true;
			    params.DriverType = video::EDT_BURNINGSVIDEO;
			    params.WithAlphaChannel = true;
			    params.AntiAlias = 0; //video::EAAM_ALPHA_TO_COVERAGE;
			    params.ZBufferBits = 24;
			    params.Vsync = false;
			    params.Bits = 32;
			    params.Doublebuffer = true;
			    params.HighPrecisionFPU = true;
			    params.Stencilbuffer = false;
		    }
		    if (nulldev->isDriverSupported(video::EDT_OPENGL))
		    {
			    bHasOpenGL = true;
			    params.DriverType = video::EDT_OPENGL;
			    params.WithAlphaChannel = false;
			    params.AntiAlias = video::EAAM_ALPHA_TO_COVERAGE;
			    params.ZBufferBits = 24;
			    params.Vsync = false;
			    params.Bits = 32;
			    params.Doublebuffer = true;
			    params.HighPrecisionFPU = true;
			    params.Stencilbuffer = false;
		    }
		    nulldev->drop();
	    }

	    // create opengl-device
	    return createDeviceEx(params);
    }


    //! ----------------------------------------------------------------
    //! create OpenGL device without AA
    //! ----------------------------------------------------------------

    IrrlichtDevice* createDeviceGL( bool userChoice )
    {
	    SIrrlichtCreationParameters params;
	    params.Fullscreen = false;
	    params.Doublebuffer = true;

	    params.DriverType = video::EDT_OPENGL;
	    params.WindowSize = core::dimension2du(1024,768);
	    params.Bits = 32;

    //	params.DriverType = video::EDT_BURNINGSVIDEO;
    //	params.WindowSize = core::dimension2du(640,480);
    //	params.Bits = 16;

    //	params.WithAlphaChannel = false;
    //	params.AntiAlias = video::EAAM_OFF;
	    params.AntiAlias = video::EAAM_ALPHA_TO_COVERAGE;
    //	params.ZBufferBits = 16;
    //	params.ZBufferBits = 24;
    //	params.ZBufferBits = 32;
    //	params.Vsync = false;
    //	params.Vsync = true;

    //	params.HighPrecisionFPU = false;
    //	params.Stencilbuffer = false;

    //    IrrlichtDevice* nulldev = createDevice(video::EDT_NULL);
    //    if (nulldev)
    //    {
    //        params.WindowSize = nulldev->getVideoModeList()->getDesktopResolution() - core::dimension2du(100,200);
    //        params.Bits = nulldev->getVideoModeList()->getDesktopDepth();
    //
    //        if (userChoice)
    //        {
    //            params.DriverType = driverChoiceConsole(true);
    //        }
    //        else
    //        {
    //            if (nulldev->isDriverSupported(video::EDT_SOFTWARE))
    //            {
    //                params.DriverType = video::EDT_SOFTWARE;
    //            }
    //            if (nulldev->isDriverSupported(video::EDT_BURNINGSVIDEO))
    //            {
    //                params.DriverType = video::EDT_BURNINGSVIDEO;
    //            }
    //            if (nulldev->isDriverSupported(video::EDT_OPENGL))
    //            {
    //                params.DriverType = video::EDT_OPENGL;
    //            }
    //        }
    //        nulldev->drop();
    //    }

	    return createDeviceEx(params);
    }

    scene::ICameraSceneNode*  createCameraFPS( scene::ISceneManager* smgr )
    {
        SKeyMap KeyMapArray[6];
	    KeyMapArray[0].Action = EKA_MOVE_FORWARD;
	    KeyMapArray[0].KeyCode = KEY_KEY_W;
	    KeyMapArray[1].Action = EKA_MOVE_BACKWARD;
	    KeyMapArray[1].KeyCode = KEY_KEY_S;
	    KeyMapArray[2].Action = EKA_STRAFE_LEFT;
	    KeyMapArray[2].KeyCode = KEY_KEY_A;
	    KeyMapArray[3].Action = EKA_STRAFE_RIGHT;
	    KeyMapArray[3].KeyCode = KEY_KEY_D;
	    KeyMapArray[4].Action = EKA_CROUCH;
	    KeyMapArray[4].KeyCode = KEY_KEY_C;
	    KeyMapArray[5].Action = EKA_JUMP_UP;
	    KeyMapArray[5].KeyCode = KEY_SPACE;

	    scene::ICameraSceneNode* cam = smgr->addCameraSceneNode(0,core::vector3df(0,50,-50),
		    core::vector3df(0,0,0), -1, true);
        if (cam)
        {

        }

	    return cam;
    }



    gui::IGUISkin* createDarkGLSkin( gui::IGUIEnvironment* guienv )
    {
	    if (!guienv)
		    return 0;

	    gui::IGUISkin* skin = guienv->createSkin( gui::EGST_BURNING_SKIN );
	    if (!skin)
		    return 0;

	    gui::IGUIElement* guiRoot = guienv->getRootGUIElement();
	    video::IVideoDriver* driver = guienv->getVideoDriver();

    //	gui::IGUIFont* fontNormal = gui::CGUITTFont::create(guienv, "../media/siedler/Garton.ttf", 16, true, true);
    //	gui::IGUIFont* fontMedium = gui::CGUITTFont::create(guienv, "../media/siedler/Garton.ttf", 20, true, true);
    //	gui::IGUIFont* fontBig = gui::CGUITTFont::create(guienv, "../media/siedler/carib.otf", 36, true, true);
    //	skin->setFont( fontNormal, gui::EGDF_DEFAULT);
    //	skin->setFont( fontMedium, gui::EGDF_WINDOW);
	    guienv->setSkin(skin);
	    return skin;
    }

//	gui::IGUIContextMenu* createMenuBar( gui::IGUIElement* parent )
//	{
//		if (!mDevice)
//			return;
//
//		mDevice->setEventReceiver(this);
//
//		gui::IGUIEnvironment* guienv = mDevice->getGUIEnvironment();
//		// create menu
//		gui::IGUIContextMenu* menu = guienv->addMenu((parent)?parent:guienv->getRootGUIElement(), -1);
//		menu->addItem(L"File", -1, true, true);
//		menu->addItem(L"View", -1, true, true);
//		menu->addItem(L"Camera", -1, true, true);
//		menu->addItem(L"Help", -1, true, true);
//
//		gui::IGUIContextMenu* submenu;
//		submenu = menu->getSubMenu(0);
//		submenu->addItem(L"Open File...", GUI_ID_OPEN_FILE);
//		submenu->addItem(L"Open Folder...", GUI_ID_OPEN_FOLDER);
//		submenu->addItem(L"Open Archive...", GUI_ID_OPEN_ARCHIVE);
//		submenu->addSeparator();
//		submenu->addItem(L"Save All...", 1010);
//		submenu->addItem(L"Save", 1011);
//		submenu->addItem(L"Save As...", 1012);
//		submenu->addSeparator();
//		submenu->addItem(L"Print...", 1020);
//		submenu->addItem(L"Print Preview...", 1021);
//		submenu->addSeparator();
//		submenu->addItem(L"Properties...", GUI_ID_ABOUT);
//		submenu->addSeparator();
//		submenu->addItem(L"Quit", GUI_ID_QUIT);
//
//		submenu = menu->getSubMenu(1);
//		submenu->addItem(L"sky box visible", GUI_ID_SKY_BOX_VISIBLE, true, false, true);
//		submenu->addItem(L"toggle model debug information", GUI_ID_TOGGLE_DEBUG_INFO, true, true);
//
//		submenu->addItem(L"model material", GUI_ID_ANIMATION_INFO, true, true );
//
//		submenu = submenu->getSubMenu(1);
//		submenu->addItem(L"Debug Off", GUI_ID_DEBUG_OFF);
//		submenu->addItem(L"Bounding Box", GUI_ID_DEBUG_BOUNDING_BOX);
//		submenu->addItem(L"Normals", GUI_ID_DEBUG_NORMALS);
//		submenu->addItem(L"Skeleton", GUI_ID_DEBUG_SKELETON);
//		submenu->addItem(L"Wire overlay", GUI_ID_DEBUG_WIRE_OVERLAY);
//		submenu->addItem(L"Half-Transparent", GUI_ID_DEBUG_HALF_TRANSPARENT);
//		submenu->addItem(L"Buffers bounding boxes", GUI_ID_DEBUG_BUFFERS_BOUNDING_BOXES);
//		submenu->addItem(L"All", GUI_ID_DEBUG_ALL);
//
//		submenu = menu->getSubMenu(1)->getSubMenu(2);
//		submenu->addItem(L"Solid", GUI_ID_MATERIAL_SOLID);
//		submenu->addItem(L"Transparent", GUI_ID_MATERIAL_TRANSPARENT);
//		submenu->addItem(L"Reflection", GUI_ID_MATERIAL_REFLECTION);
//
//		submenu = menu->getSubMenu(2);
//		submenu->addItem(L"Maya Style", GUI_ID_CAMERA_MAYA);
//		submenu->addItem(L"First Person", GUI_ID_CAMERA_FIRST_PERSON);
//
//		submenu = menu->getSubMenu(3);
//		submenu->addItem(L"About", GUI_ID_ABOUT);
//
//		return menu;
//	}
//
//	void OnMenuItemSelected( gui::IGUIContextMenu* menu )
//	{
//		s32 id = menu->getItemCommandId(menu->getSelectedItem());
//		gui::IGUIEnvironment* env = mDevice->getGUIEnvironment();
//
//		switch(id)
//		{
//		case GUI_ID_OPEN_FILE: // FilOnButtonSetScalinge -> Open mModel
//			env->addFileOpenDialog(L"Please select a model file to open");
//			break;
//		case GUI_ID_OPEN_FOLDER: // File -> Set mModel Archive
//			env->addFileOpenDialog(L"Please select your game archive/directory");
//			break;
//		case GUI_ID_OPEN_ARCHIVE: // File -> Set mModel Archive
//			env->addFileOpenDialog(L"Please select your game archive/directory");
//			break;
//		case GUI_ID_OPEN_MODEL: // FilOnButtonSetScalinge -> Open mModel
//			env->addFileOpenDialog(L"Please select a model file to open");
//			break;
//		case GUI_ID_SET_MODEL_ARCHIVE: // File -> Set mModel Archive
//			env->addFileOpenDialog(L"Please select your game archive/directory");
//			break;
////		case GUI_ID_LOAD_AS_OCTREE: // File -> LoadAsOctree
////			Octree = !Octree;
////			menu->setItemChecked(menu->getSelectedItem(), Octree);
////			break;
//		case GUI_ID_QUIT: // File -> Quit
//			mDevice->closeDevice();
//			break;
//		case GUI_ID_SKY_BOX_VISIBLE: // View -> Skybox
//			menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
////			SkyBox->setVisible(!SkyBox->isVisible());
//			break;
//		case GUI_ID_DEBUG_OFF: // View -> Debug Information
//			menu->setItemChecked(menu->getSelectedItem()+1, false);
//			menu->setItemChecked(menu->getSelectedItem()+2, false);
//			menu->setItemChecked(menu->getSelectedItem()+3, false);
//			menu->setItemChecked(menu->getSelectedItem()+4, false);
//			menu->setItemChecked(menu->getSelectedItem()+5, false);
//			menu->setItemChecked(menu->getSelectedItem()+6, false);
//			if (mModel)
//				mModel->setDebugDataVisible(scene::EDS_OFF);
//			break;
//		case GUI_ID_DEBUG_BOUNDING_BOX: // View -> Debug Information
//			menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//			if (mModel)
//				mModel->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(mModel->isDebugDataVisible()^scene::EDS_BBOX));
//			break;
//		case GUI_ID_DEBUG_NORMALS: // View -> Debug Information
//			menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//			if (mModel)
//				mModel->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(mModel->isDebugDataVisible()^scene::EDS_NORMALS));
//			break;
//		case GUI_ID_DEBUG_SKELETON: // View -> Debug Information
//			menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//			if (mModel)
//				mModel->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(mModel->isDebugDataVisible()^scene::EDS_SKELETON));
//			break;
//		case GUI_ID_DEBUG_WIRE_OVERLAY: // View -> Debug Information
//			menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//			if (mModel)
//				mModel->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(mModel->isDebugDataVisible()^scene::EDS_MESH_WIRE_OVERLAY));
//			break;
//		case GUI_ID_DEBUG_HALF_TRANSPARENT: // View -> Debug Information
//			menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//			if (mModel)
//				mModel->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(mModel->isDebugDataVisible()^scene::EDS_HALF_TRANSPARENCY));
//			break;
//		case GUI_ID_DEBUG_BUFFERS_BOUNDING_BOXES: // View -> Debug Information
//			menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//			if (mModel)
//				mModel->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(mModel->isDebugDataVisible()^scene::EDS_BBOX_BUFFERS));
//			break;
//		case GUI_ID_DEBUG_ALL: // View -> Debug Information
//			menu->setItemChecked(menu->getSelectedItem()-1, true);
//			menu->setItemChecked(menu->getSelectedItem()-2, true);
//			menu->setItemChecked(menu->getSelectedItem()-3, true);
//			menu->setItemChecked(menu->getSelectedItem()-4, true);
//			menu->setItemChecked(menu->getSelectedItem()-5, true);
//			menu->setItemChecked(menu->getSelectedItem()-6, true);
//			if (mModel)
//				mModel->setDebugDataVisible(scene::EDS_FULL);
//			break;
//		case GUI_ID_ABOUT: // Help->About
//			showAboutText();
//			break;
//		case GUI_ID_MATERIAL_SOLID: // View -> Material -> Solid
//			if (mModel)
//				mModel->setMaterialType(video::EMT_SOLID);
//			break;
//		case GUI_ID_MATERIAL_TRANSPARENT: // View -> Material -> Transparent
//			if (mModel)
//				mModel->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
//			break;
//		case GUI_ID_MATERIAL_REFLECTION: // View -> Material -> Reflection
//			if (mModel)
//				mModel->setMaterialType(video::EMT_SPHERE_MAP);
//			break;
//
////		case GUI_ID_CAMERA_MAYA:
////			setActiveCamera(Camera[0]);
////			break;
////		case GUI_ID_CAMERA_FIRST_PERSON:
////			setActiveCamera(Camera[1]);
////			break;
//		}
//	}
//
//	bool OnKeyUp(irr::EKEY_CODE keyCode)
//	{
//		// Don't handle keys if we have a modal dialog open as it would lead
//		// to unexpected application behaviour for the user.
//		if ( hasModalDialog() )
//			return false;
//
//		if (keyCode == irr::KEY_ESCAPE)
//		{
//			if (mDevice)
//			{
//				scene::ICameraSceneNode * camera = mDevice->getSceneManager()->getActiveCamera();
//				if (camera)
//				{
//					camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
//				}
//				return true;
//			}
//		}
//		else if (keyCode == irr::KEY_F1)
//		{
//			if (mDevice)
//			{
//				gui::IGUIElement* elem = mDevice->getGUIEnvironment()->getRootGUIElement()->getElementFromId(GUI_ID_POSITION_TEXT);
//				if (elem)
//					elem->setVisible(!elem->isVisible());
//			}
//		}
//		else if (keyCode == irr::KEY_KEY_M)
//		{
//			if (mDevice)
//				mDevice->minimizeWindow();
//		}
//		else if (keyCode == irr::KEY_KEY_L)
//		{
//			mUseLight=!mUseLight;
//			if (mModel)
//			{
//				mModel->setMaterialFlag(video::EMF_LIGHTING, mUseLight);
//				mModel->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, mUseLight);
//			}
//		}
//		return false;
//	}
//
//
//    gui::IGUIElement* getFocused()
//    {
//        return mFocused;
//    }
//
//    gui::IGUIElement* getHovered()
//    {
//        return mHovered;
//    }
//
//    void OnAbout()
//    {
//        if (!mDevice)
//            return;
//
//        gui::IGUIEnvironment* guienv = mDevice->getGUIEnvironment();
//
//        gui::IGUIWindow* winAbout = guienv->addMessageBox(L"About", L"(c) 2008 - 2012 by BenjaminHampe@gm.de", true);
//        if (winAbout->getCloseButton()->isPressed())
//        {
//            winAbout->drop();
//        }
//    }


} // end namespace irr

// Copyright (C) 2002-2012 Benjamin Hampe
// This file is part of the "DarkGDK DarkGL irrExt" irrlicht extensions.
// For conditions of distribution and use, see copyright notice in DarkGL.h

#ifndef __IRR_HELPER_H__
#define __IRR_HELPER_H__

#include <irrlicht.h>

namespace irr
{



	void showAboutText( gui::IGUIEnvironment* env );

	bool hasModalDialog( gui::IGUIEnvironment* env );

	void setSkinTransparency( gui::IGUISkin * skin, s32 alpha );

	void setActiveCamera(scene::ISceneManager* smgr, scene::ICameraSceneNode* newActive = 0);

	void onKillFocus( scene::ISceneManager* smgr );

	//	gui::IGUIContextMenu* createMenuBar( gui::IGUIElement* parent );
	//	void OnMenuItemSelected( gui::IGUIContextMenu* menu );
	//	bool OnKeyUp(irr::EKEY_CODE keyCode);

    IrrlichtDevice* createDeviceGL();

    IrrlichtDevice* createDeviceGL( bool userChoice );

    scene::ICameraSceneNode*  createCameraFPS( scene::ISceneManager* smgr );

    gui::IGUISkin* createDarkGLSkin( gui::IGUIEnvironment* guienv );

} // end namespace irr

#endif // __IRR_HELPER_H__

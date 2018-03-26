#include "CMasterEventReceiver.h"

#include <irrlicht.h>
#include <../source/Irrlicht/os.h>

namespace irr{

CMasterEventReceiver::CMasterEventReceiver( IrrlichtDevice* device )
: Device(device), ScreenSize(640,480), MenuBar(0), ToolBar(0), Hovered(0), Focused(0), Clicked(0)
, Model(0), Camera(0)
, use_light(false), use_wireframe(false), use_fog(false)
{
#if _DEBUG
	os::Printer::log("CMasterEventReceiver::ctr()", ELL_INFORMATION);
#endif
	if (!Device)
	{
		os::Printer::log("No valid pointer to irrlicht-device", ELL_ERROR);
		exit(-3);
	}

	Device->setEventReceiver( this );

	video::IVideoDriver* driver = Device->getVideoDriver();

	ScreenSize = driver->getScreenSize();

//	gui::IGUIEnvironment* env = Device->getGUIEnvironment();
//	gui::IGUISkin* skin = env->createSkin( gui::EGST_BURNING_SKIN );
//	//gui::IGUIFont* font = guienv->getFont("../media/fonts/arial10.png");
//	//if (font)
//	//	skin->setFont(font);
//
//	video::SColor color = skin->getColor( gui::EGDC_APP_WORKSPACE );
//	skin->setColor( gui::EGDC_APP_WORKSPACE, video::SColor(127,color.getRed(), color.getGreen(), color.getBlue()));
//
//	env->setSkin( skin );

	// MenuBar = createMenuBar( env->getRootGUIElement() );

	// scene::ISceneManager* smgr = Device->getSceneManager();
#if _DEBUG
	os::Printer::log("attached CMasterEventReceiver to irrlicht-device", ELL_INFORMATION);
#endif
}

CMasterEventReceiver::~CMasterEventReceiver()
{
	clearReceiver();
}

bool CMasterEventReceiver::clearReceiver( )
{
	for (u32 i=0; i<Receiver.size(); i++)
	{
		IEventReceiver* r = Receiver[i];
		if (r)
		{
			delete r;
			Receiver[i] = 0;
		}
	}
	Receiver.clear();
	return true;
}

bool CMasterEventReceiver::hasReceiver( IEventReceiver* recv ) const
{
	if (!recv)
		return false;

	for (u32 i=0; i<Receiver.size(); i++)
	{
		IEventReceiver* r = Receiver[i];
		if (r && (r == recv))
		{
			return true;
		}
	}

	return false;
}

//	manage EventReceiver
bool CMasterEventReceiver::addReceiver( IEventReceiver* recv )
{
	if (hasReceiver(recv))
		return false;

	u32 count = Receiver.size();
	Receiver.push_back( recv );

	return count != Receiver.size() ? true : false;
}

u32 CMasterEventReceiver::getReceiverCount() const
{
	return Receiver.size();
}

IEventReceiver* CMasterEventReceiver::getReceiver( u32 index )
{
	if (index>=Receiver.size())
		return 0;

	return Receiver[index];
}

bool CMasterEventReceiver::eraseReceiver( u32 index )
{
	if (index>=Receiver.size())
		return false;

	IEventReceiver* r = Receiver[index];
	if (r)
	{
		delete r;
		Receiver[index] = 0;
		Receiver.erase( index );
	}
}

// virtual void setReceiverEnabled( );

bool CMasterEventReceiver::OnEvent(const SEvent& event)
{

	//! Logging
	if (event.EventType == EET_LOG_TEXT_EVENT)
	{
		OnLogEvent( event );
		return true;
	}

	//! KEYBOARD
	else if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		OnKeyEvent( event );
	}

	//! Mouse
	else if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		OnMouseEvent(event);
	}

	//! GUI
	else if (event.EventType == EET_GUI_EVENT)
	{
		OnGUIEvent(event);
	}
	//! Joystick
	else
	{
	}

	for (u32 i=0; i<Receiver.size(); i++)
	{
		IEventReceiver* rcv = Receiver[i];
		if (rcv)
		{
			rcv->OnEvent( event );
		}
	}
	return false;
}

//! process Log events
bool CMasterEventReceiver::OnLogEvent( const SEvent& event )
{
	for (u32 i=0; i<Receiver.size(); i++)
	{
		IEventReceiver* recv = Receiver[i];
		if (recv)
		{
			recv->OnEvent( event );
		}
	}

	if (Device)
		Device->getLogger()->log( event.LogEvent.Text, event.LogEvent.Level );

	return true;
}

//! process KEYBOARD events
bool CMasterEventReceiver::OnKeyEvent( const SEvent& event )
{
	// Don't handle keys if we have a modal dialog open as it would lead
	// to unexpected application behaviour for the user.
	// if ( hasModalDialog() )
	//	return false;


	if (event.EventType != EET_KEY_INPUT_EVENT)
		return false;

	if (!event.KeyInput.PressedDown)
	{
		switch (event.KeyInput.Key)
		{
			case KEY_ESCAPE: {
				if (Device)
				{
					Device->closeDevice();
					return true;
				}
			}
			break;

			case KEY_SPACE:	{
				if (Device)
				{
					scene::ICameraSceneNode* camera = Device->getSceneManager()->getActiveCamera();
					if (camera)
					{
						camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
					}
					return true;
				}
			} break;

//			case KEY_F1: {
//				messageBox->setVisible(true);
//				if (Device)	{
//					Device->closeDevice();
//					Device->drop();
//				}} break;
//
//			case KEY_F4: {}
//				break;

			default:
				break;
		}
	}


//
//	else if (keyCode == irr::KEY_F1)
//	{
//		if (Device)
//		{
//			gui::IGUIElement* elem = Device->getGUIEnvironment()->getRootGUIElement()->getElementFromId(GUI_ID_POSITION_TEXT);
//			if (elem)
//				elem->setVisible(!elem->isVisible());
//		}
//	}
//	else if (keyCode == irr::KEY_KEY_M)
//	{
//		if (Device)
//			Device->minimizeWindow();
//	}
//	else if (keyCode == irr::KEY_KEY_L)
//	{
//		use_light=!use_light;
//		if (Model)
//		{
//			Model->setMaterialFlag(video::EMF_LIGHTING, use_light);
//			Model->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, use_light);
//		}
//	}
	return false;
}

//! process Mouse-Events
bool CMasterEventReceiver::OnMouseEvent( const SEvent& event )
{
	return false;
}

//! process GUI-Events
bool CMasterEventReceiver::OnGUIEvent( const SEvent& event )
{
	if (event.EventType != EET_GUI_EVENT)
		return false;

	gui::IGUIElement* caller = event.GUIEvent.Caller;
	s32 id = caller->getID();

	if (event.GUIEvent.EventType == gui::EGET_MENU_ITEM_SELECTED)
	{
		// OnMenuItemSelected( (gui::IGUIContextMenu*)event.GUIEvent.Caller );
	}
	if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED)
	{
//		if (event.GUIEvent.Caller == (gui::IGUIElement*)messageBox->getCloseButton())
//		{
//			messageBox->setVisible(false);
//		}
	}
//
//	if (event.GUIEvent.Caller == (gui::IGUIElement*)messageBox)
//	{
//		if ((event.GUIEvent.EventType == gui::EGET_MESSAGEBOX_YES) || (event.GUIEvent.EventType == gui::EGET_MESSAGEBOX_OK))
//		{
//			if (Device)
//				Device->closeDevice();
//			return true;
//		}
//	}

	if (event.GUIEvent.EventType == gui::EGET_ELEMENT_FOCUSED)
	{
		Focused = event.GUIEvent.Caller;
	}
	if (event.GUIEvent.EventType == gui::EGET_ELEMENT_FOCUS_LOST)
	{
		if (Focused == event.GUIEvent.Caller)
		{
			Focused = 0;
		}
	}
	if (event.GUIEvent.EventType == gui::EGET_ELEMENT_HOVERED)
	{
		Hovered = event.GUIEvent.Caller;
	}
	if (event.GUIEvent.EventType == gui::EGET_ELEMENT_LEFT)
	{
		if (Hovered == event.GUIEvent.Caller)
		{
			Hovered = 0;
		}
	}
	if (event.GUIEvent.EventType == gui::EGET_ELEMENT_CLOSED)
	{
		if (Hovered == event.GUIEvent.Caller)
		{
			Hovered = 0;
		}
		if (Focused == event.GUIEvent.Caller)
		{
			Focused = 0;
		}
	}
	return false;
}

void CMasterEventReceiver::OnSize( const core::dimension2du& newSize )
{
	if (newSize.Width == 0)
		return;

	if (newSize.Height == 0)
		return;

	if (ScreenSize == newSize)
		return;

	ScreenSize = newSize;

	if (Device)
	{
		scene::ICameraSceneNode* camera = Device->getSceneManager()->getActiveCamera();
		if (camera)
		{
			camera->setAspectRatio( (f32)ScreenSize.Width / (f32)ScreenSize.Height );
		}
	}
}

//	event-processing
// CMasterEventReceiver::update();
// CMasterEventReceiver::updateAll();
// CMasterEventReceiver::updateStates();

// CMasterEventReceiver::OnKeyEvent( const SEvent& keyEvent );
// CMasterEventReceiver::OnMouseEvent( const SEvent& keyEvent );
// CMasterEventReceiver::OnGUIEvent( const SEvent& keyEvent );
// CMasterEventReceiver::OnLogEvent( const SEvent& keyEvent );

//	Keyboard event-processing
bool CMasterEventReceiver::getKeyState( EKEY_CODE keyCode ) const
{
	return false;
}

bool CMasterEventReceiver::isKeyDown( EKEY_CODE keyCode ) const
{
	return false;
}

bool CMasterEventReceiver::isKeyUp( EKEY_CODE keyCode ) const
{
	return false;
}

//	Mouse event-processing
s32 CMasterEventReceiver::getMouseX() const
{
	return 0;
}
s32 CMasterEventReceiver::getMouseY() const
{
	return 0;
}
s32 CMasterEventReceiver::getMouseZ() const
{
	return 0;
}

bool CMasterEventReceiver::isMouseOver( s32 x1, s32 y1, s32 x2, s32 y2 ) const
{
	return false;
}

bool CMasterEventReceiver::isMouseMove() const
{
	return false;
}

bool CMasterEventReceiver::isMouseWheel() const
{
	return false;
}
bool CMasterEventReceiver::isMouseClick() const
{
	return false;
}
bool CMasterEventReceiver::isMouseLeftDown() const
{
	return false;
}
bool CMasterEventReceiver::isMouseLeftUp() const
{
	return false;
}
bool CMasterEventReceiver::isMouseRightDown() const
{
	return false;
}
bool CMasterEventReceiver::isMouseRightUp() const
{
	return false;
}
bool CMasterEventReceiver::isMouseMiddleDown() const
{
	return false;
}
bool CMasterEventReceiver::isMouseMiddleUp() const
{
	return false;
}

// protected:

gui::IGUIContextMenu* CMasterEventReceiver::createMenuBar( gui::IGUIElement* parent )
{
	if (!Device)
		return 0;

	Device->setEventReceiver(this);

	gui::IGUIEnvironment* guienv = Device->getGUIEnvironment();
	// create menu
	gui::IGUIContextMenu* menu = guienv->addMenu((parent)?parent:guienv->getRootGUIElement(), -1);
	menu->addItem(L"File", -1, true, true);
	menu->addItem(L"View", -1, true, true);
	menu->addItem(L"Camera", -1, true, true);
	menu->addItem(L"Help", -1, true, true);

	gui::IGUIContextMenu* submenu;
	submenu = menu->getSubMenu(0);
//	submenu->addItem(L"Open File...", GUI_ID_OPEN_FILE);
//	submenu->addItem(L"Open Folder...", GUI_ID_OPEN_FOLDER);
//	submenu->addItem(L"Open Archive...", GUI_ID_OPEN_ARCHIVE);
//	submenu->addSeparator();
//	submenu->addItem(L"Save All...", 1010);
//	submenu->addItem(L"Save", 1011);
//	submenu->addItem(L"Save As...", 1012);
//	submenu->addSeparator();
//	submenu->addItem(L"Print...", 1020);
//	submenu->addItem(L"Print Preview...", 1021);
//	submenu->addSeparator();
//	submenu->addItem(L"Properties...", GUI_ID_ABOUT);
//	submenu->addSeparator();
//	submenu->addItem(L"Quit", GUI_ID_QUIT);
//
//	submenu = menu->getSubMenu(1);
//	submenu->addItem(L"sky box visible", GUI_ID_SKY_BOX_VISIBLE, true, false, true);
//	submenu->addItem(L"toggle model debug information", GUI_ID_TOGGLE_DEBUG_INFO, true, true);
//
//	submenu->addItem(L"model material", GUI_ID_ANIMATION_INFO, true, true );
//
//	submenu = submenu->getSubMenu(1);
//	submenu->addItem(L"Debug Off", GUI_ID_DEBUG_OFF);
//	submenu->addItem(L"Bounding Box", GUI_ID_DEBUG_BOUNDING_BOX);
//	submenu->addItem(L"Normals", GUI_ID_DEBUG_NORMALS);
//	submenu->addItem(L"Skeleton", GUI_ID_DEBUG_SKELETON);
//	submenu->addItem(L"Wire overlay", GUI_ID_DEBUG_WIRE_OVERLAY);
//	submenu->addItem(L"Half-Transparent", GUI_ID_DEBUG_HALF_TRANSPARENT);
//	submenu->addItem(L"Buffers bounding boxes", GUI_ID_DEBUG_BUFFERS_BOUNDING_BOXES);
//	submenu->addItem(L"All", GUI_ID_DEBUG_ALL);
//
//	submenu = menu->getSubMenu(1)->getSubMenu(2);
//	submenu->addItem(L"Solid", GUI_ID_MATERIAL_SOLID);
//	submenu->addItem(L"Transparent", GUI_ID_MATERIAL_TRANSPARENT);
//	submenu->addItem(L"Reflection", GUI_ID_MATERIAL_REFLECTION);
//
//	submenu = menu->getSubMenu(2);
//	submenu->addItem(L"Maya Style", GUI_ID_CAMERA_MAYA);
//	submenu->addItem(L"First Person", GUI_ID_CAMERA_FIRST_PERSON);
//
//	submenu = menu->getSubMenu(3);
//	submenu->addItem(L"About", GUI_ID_ABOUT);

	return menu;
}

//
//bool CMasterEventReceiver::OnKeyUp(irr::EKEY_CODE keyCode)
//{
//	// Don't handle keys if we have a modal dialog open as it would lead
//	// to unexpected application behaviour for the user.
//	if ( hasModalDialog() )
//		return false;
//
//	if (keyCode == irr::KEY_ESCAPE)
//	{
//		if (Device)
//		{
//			scene::ICameraSceneNode * camera = Device->getSceneManager()->getActiveCamera();
//			if (camera)
//			{
//				camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
//			}
//			return true;
//		}
//	}
//	else if (keyCode == irr::KEY_F1)
//	{
//		if (Device)
//		{
//			gui::IGUIElement* elem = Device->getGUIEnvironment()->getRootGUIElement()->getElementFromId(GUI_ID_POSITION_TEXT);
//			if (elem)
//				elem->setVisible(!elem->isVisible());
//		}
//	}
//	else if (keyCode == irr::KEY_KEY_M)
//	{
//		if (Device)
//			Device->minimizeWindow();
//	}
//	else if (keyCode == irr::KEY_KEY_L)
//	{
//		use_light=!use_light;
//		if (Model)
//		{
//			Model->setMaterialFlag(video::EMF_LIGHTING, use_light);
//			Model->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, use_light);
//		}
//	}
//	return false;
//}

//
//void CMasterEventReceiver::OnMenuItemSelected( gui::IGUIContextMenu* menu )
//{
//	s32 id = menu->getItemCommandId(menu->getSelectedItem());
//	gui::IGUIEnvironment* env = Device->getGUIEnvironment();
//
//	switch(id)
//	{
//	case GUI_ID_OPEN_FILE: // FilOnButtonSetScalinge -> Open Model
//		env->addFileOpenDialog(L"Please select a model file to open");
//		break;
//	case GUI_ID_OPEN_FOLDER: // File -> Set Model Archive
//		env->addFileOpenDialog(L"Please select your game archive/directory");
//		break;
//	case GUI_ID_OPEN_ARCHIVE: // File -> Set Model Archive
//		env->addFileOpenDialog(L"Please select your game archive/directory");
//		break;
//	case GUI_ID_OPEN_MODEL: // FilOnButtonSetScalinge -> Open Model
//		env->addFileOpenDialog(L"Please select a model file to open");
//		break;
//	case GUI_ID_SET_MODEL_ARCHIVE: // File -> Set Model Archive
//		env->addFileOpenDialog(L"Please select your game archive/directory");
//		break;
////		case GUI_ID_LOAD_AS_OCTREE: // File -> LoadAsOctree
////			Octree = !Octree;
////			menu->setItemChecked(menu->getSelectedItem(), Octree);
////			break;
//	case GUI_ID_QUIT: // File -> Quit
//		Device->closeDevice();
//		break;
//	case GUI_ID_SKY_BOX_VISIBLE: // View -> Skybox
//		menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
////			SkyBox->setVisible(!SkyBox->isVisible());
//		break;
//	case GUI_ID_DEBUG_OFF: // View -> Debug Information
//		menu->setItemChecked(menu->getSelectedItem()+1, false);
//		menu->setItemChecked(menu->getSelectedItem()+2, false);
//		menu->setItemChecked(menu->getSelectedItem()+3, false);
//		menu->setItemChecked(menu->getSelectedItem()+4, false);
//		menu->setItemChecked(menu->getSelectedItem()+5, false);
//		menu->setItemChecked(menu->getSelectedItem()+6, false);
//		if (Model)
//			Model->setDebugDataVisible(scene::EDS_OFF);
//		break;
//	case GUI_ID_DEBUG_BOUNDING_BOX: // View -> Debug Information
//		menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//		if (Model)
//			Model->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(Model->isDebugDataVisible()^scene::EDS_BBOX));
//		break;
//	case GUI_ID_DEBUG_NORMALS: // View -> Debug Information
//		menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//		if (Model)
//			Model->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(Model->isDebugDataVisible()^scene::EDS_NORMALS));
//		break;
//	case GUI_ID_DEBUG_SKELETON: // View -> Debug Information
//		menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//		if (Model)
//			Model->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(Model->isDebugDataVisible()^scene::EDS_SKELETON));
//		break;
//	case GUI_ID_DEBUG_WIRE_OVERLAY: // View -> Debug Information
//		menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//		if (Model)
//			Model->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(Model->isDebugDataVisible()^scene::EDS_MESH_WIRE_OVERLAY));
//		break;
//	case GUI_ID_DEBUG_HALF_TRANSPARENT: // View -> Debug Information
//		menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//		if (Model)
//			Model->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(Model->isDebugDataVisible()^scene::EDS_HALF_TRANSPARENCY));
//		break;
//	case GUI_ID_DEBUG_BUFFERS_BOUNDING_BOXES: // View -> Debug Information
//		menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
//		if (Model)
//			Model->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)(Model->isDebugDataVisible()^scene::EDS_BBOX_BUFFERS));
//		break;
//	case GUI_ID_DEBUG_ALL: // View -> Debug Information
//		menu->setItemChecked(menu->getSelectedItem()-1, true);
//		menu->setItemChecked(menu->getSelectedItem()-2, true);
//		menu->setItemChecked(menu->getSelectedItem()-3, true);
//		menu->setItemChecked(menu->getSelectedItem()-4, true);
//		menu->setItemChecked(menu->getSelectedItem()-5, true);
//		menu->setItemChecked(menu->getSelectedItem()-6, true);
//		if (Model)
//			Model->setDebugDataVisible(scene::EDS_FULL);
//		break;
//	case GUI_ID_ABOUT: // Help->About
//		showAboutText();
//		break;
//	case GUI_ID_MATERIAL_SOLID: // View -> Material -> Solid
//		if (Model)
//			Model->setMaterialType(video::EMT_SOLID);
//		break;
//	case GUI_ID_MATERIAL_TRANSPARENT: // View -> Material -> Transparent
//		if (Model)
//			Model->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
//		break;
//	case GUI_ID_MATERIAL_REFLECTION: // View -> Material -> Reflection
//		if (Model)
//			Model->setMaterialType(video::EMT_SPHERE_MAP);
//		break;
//
////		case GUI_ID_CAMERA_MAYA:
////			setActiveCamera(Camera[0]);
////			break;
////		case GUI_ID_CAMERA_FIRST_PERSON:
////			setActiveCamera(Camera[1]);
////			break;
//	}
//}

gui::IGUIElement* CMasterEventReceiver::getFocused() const
{
	return Focused;
}

gui::IGUIElement* CMasterEventReceiver::getHovered() const
{
	return Hovered;
}

void CMasterEventReceiver::OnAbout()
{
	if (!Device)
		return;

	gui::IGUIEnvironment* env = Device->getGUIEnvironment();

	gui::IGUIWindow* winAbout = env->addMessageBox(L"About", L"(c) 2008 - 2012 by BenjaminHampe@gm.de", true);
	if (winAbout->getCloseButton()->isPressed())
	{
		winAbout->drop();
	}
}

} // end namespace irr

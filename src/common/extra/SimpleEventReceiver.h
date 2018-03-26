#ifndef SIMPLE_EVENT_RECEIVER_H_INCLUDED
#define SIMPLE_EVENT_RECEIVER_H_INCLUDED

#include <irrlicht.h>

#include "video/CImageFactory.h"
/*	simple EventReceiver using ESC key to exit application ( copied from forum )	and SPACE key to enable/disable CameraEventReceiver*/

#define _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_

#ifdef _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_
	#include <iostream>
	#include <iomanip>
	#include <fstream>
#endif  // _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_

namespace irr
{

class SimpleEventReceiver : public IEventReceiver
{
public:

private:
	IrrlichtDevice* Device;
	core::dimension2du ScreenSize;
	gui::IGUIWindow* Window;
	gui::IGUIListBox* LogBox;
	gui::IGUIWindow* OptionWindow;
	gui::IGUITabControl* Tabs;
	gui::IGUITab* TabStart;
	gui::IGUITab* TabLogging;
	gui::IGUITab* TabVideo;
	gui::IGUITab* TabScene;
	gui::IGUITab* TabLight;
	gui::IGUITab* TabTexture;
	gui::IGUITab* TabPioneer;
	gui::IGUITab* TabKeyboard;
	gui::IGUITab* TabMouse;
	gui::IGUITab* TabJoystick;
	gui::IGUITab* TabSound;
	gui::IGUITab* TabGamepad;
	gui::IGUITab* TabMidi;


#ifdef _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_
	io::path FileName;
	std::ofstream FileStream;
#endif  // _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_

public:
	SimpleEventReceiver( IrrlichtDevice* device )
	: Device(device), LogBox(0)
	{
	#ifdef _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_
		FileName = "./SimpleEventReceiver.log";
		FileStream.open( FileName.c_str(), std::ios::out );
		FileStream<<"FileLog"<<std::endl;
	#endif  // _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_

		if (Device)
		{
			video::IVideoDriver* driver = Device->getVideoDriver();
			video::IVideoModeList* modeList = Device->getVideoModeList();
			gui::IGUIEnvironment* env = Device->getGUIEnvironment();

			ScreenSize = driver->getScreenSize();

			gui::IGUISkin* skin = env->createSkin( gui::EGST_BURNING_SKIN );
			if (skin)
			{
				// gui::IGUIFont* fontNormal = gui::CGUITTFont::create(guienv, "../media/siedler/Garton.ttf", 16, true, true);
				// gui::IGUIFont* fontNormal = gui::CGUITTFont::create(guienv, "../media/siedler/Garton.ttf", 16, true, true);
				env->setSkin(skin);
				for (u32 i=0; i<gui::EGUI_DEFAULT_COLOR::EGDC_COUNT; i++)
				{
					video::SColor color = skin->getColor( (gui::EGUI_DEFAULT_COLOR)i );
					skin->setColor( (gui::EGUI_DEFAULT_COLOR)i, video::SColor( 240, color.getRed(), color.getGreen(), color.getBlue()) );
				}

			}

			s32 x1,x2,y1,y2;

			// console window
			x1 = (s32)ScreenSize.Width>>1;
			x2 = (s32)ScreenSize.Width-100;
			y1 = (s32)100;
			y2 = (s32)ScreenSize.Height-100;

			Window = env->addWindow(core::recti(x1,y1,x2,y2), false, L"Console Window", env->getRootGUIElement(), -1);
			Window->getCloseButton()->setEnabled(false);
			Window->getMinimizeButton()->setVisible(true);
			Window->getMinimizeButton()->setEnabled(false);
			Window->getMaximizeButton()->setVisible(true);
			Window->getMaximizeButton()->setEnabled(false);
			core::recti clientRect = Window->getClientRect();

			Tabs = env->addTabControl(clientRect, Window, true,true,-1);
			Tabs->setTabHeight(20);
			TabLogging = Tabs->addTab( L"Console", -1 );
			core::recti r = TabLogging->getRelativePosition();
			LogBox = env->addListBox( core::recti(0,0,r.getWidth()-1, r.getHeight()-30), TabLogging, -1, true);
			if (LogBox)
			{
				LogBox->setAutoScrollEnabled( true );
				LogBox->setVisible( true );
			}

			gui::IGUIEditBox* InputBox = env->addEditBox( L"CommandConsole InputBox", core::recti(0,r.getHeight()-30,r.getWidth()-1,r.getHeight()-1), true, TabLogging, -1);

			// options-dialog window
			x1 = 100;
			x2 = (s32)ScreenSize.Width-100;
			y1 = 200;
			y2 = (s32)ScreenSize.Height-50;

			OptionWindow = env->addWindow(core::recti(x1,y1,x2,y2), false, L"MainWindowMenu", env->getRootGUIElement(), -1);
			if (OptionWindow)
			{
			OptionWindow->getCloseButton()->setEnabled(false);
			OptionWindow->getMinimizeButton()->setVisible(true);
			OptionWindow->getMinimizeButton()->setEnabled(false);
			OptionWindow->getMaximizeButton()->setVisible(true);
			OptionWindow->getMaximizeButton()->setEnabled(false);
			clientRect = OptionWindow->getClientRect();

			Tabs = env->addTabControl(clientRect, OptionWindow, true,true,-1);
			Tabs->setTabHeight(20);
			TabStart = Tabs->addTab( L"Render", -1 );
			TabVideo = Tabs->addTab( L"Video", -1 );
			TabScene = Tabs->addTab( L"Scene", -1 );

			gui::IGUITreeView* tvScene = env->addTreeView( core::recti(
				0, 0,
				TabScene->getRelativePosition().getWidth()/2,
				TabScene->getRelativePosition().getHeight()-1), TabScene, -1, false );

			gui::IGUIStaticText* tvInfo = env->addStaticText( L"tvInfo", core::recti(
				TabScene->getRelativePosition().getWidth()/2, 0,
				TabScene->getRelativePosition().getWidth()-1,
				TabScene->getRelativePosition().getHeight()-1),  true, true, TabScene, -1, true );

			gui::IGUITreeViewNode* tvRoot = tvScene->getRoot();
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			tvRoot->addChildBack( L"Node");
			TabLight = Tabs->addTab( L"Light", -1 );
			TabTexture = Tabs->addTab( L"Gfx", -1 );
			// TabPaint = Tabs->addTab( L"Paint", -1 );
			TabPioneer = Tabs->addTab( L"Pioneer-Editor", -1 );
			TabMouse = Tabs->addTab( L"Mouse", -1 );
			TabKeyboard = Tabs->addTab( L"Keyboard", -1 );
			TabSound = Tabs->addTab( L"Sound", -1 );
			TabJoystick = Tabs->addTab( L"Joystick", -1 );
			TabGamepad = Tabs->addTab( L"Gamepad", -1 );
			TabMidi = Tabs->addTab( L"Midi", -1 );

			core::stringw txt;
			s32 x=0;
			s32 y=0;
			s32 w=TabVideo->getRelativePosition().getSize().Width;
			s32 h=14;
			{
				txt=L"OS-Version [ "; txt+=device->getOSOperator()->getOperatingSystemVersion(); txt+=L" ]";
				gui::IGUIEditBox* edt = env->addEditBox(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, TabVideo, -1);
				if (edt)
				{
					edt->setEnabled(false);
				}
				y+=h;
			}
			w=200;
			{
				txt=L"Irrlicht Engine Version [ "; txt+=device->getVersion(); txt+=L" ]";
				gui::IGUIEditBox* edt = env->addEditBox(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, TabVideo, -1);
				if (edt)
				{
					edt->setEnabled(false);
				}
				y+=h;
			}
			txt=L"Irrlicht Device Type "; txt+=device->getType(); txt+=L" [ "; txt+=E_DEVICE_TYPE_STRINGS[device->getType()]; txt+=L" ]";
			env->addStaticText(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, true, TabVideo, -1, true); y+=h;
			txt=L"Vendor [ "; txt+=driver->getVendorInfo(); txt+=L" ]";
			env->addStaticText(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, true, TabVideo, -1, true); y+=h;

			txt=L"Driver [ "; txt+=driver->getName(); txt+=L" ]";
			env->addStaticText(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, true, TabVideo, -1, true); y+=h;

			u32 RAM_Total, RAM_Avail;
			device->getOSOperator()->getSystemMemory( &RAM_Total, &RAM_Avail);
			txt=L"RAM-Total [ "; txt+=RAM_Total; txt+=L" ]";
			env->addStaticText(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, true, TabVideo, -1, true); y+=h;
			txt=L"RAM-Avail [ "; txt+=RAM_Avail; txt+=L" ]";
			env->addStaticText(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, true, TabVideo, -1, true); y+=h;
			txt=L"Desktop [ "; txt+=modeList->getDesktopResolution().Width;
			txt+=L" x "; txt+=modeList->getDesktopResolution().Height;
			txt+=L" x "; txt+=modeList->getDesktopDepth(); txt+=L" ]";
			env->addStaticText(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, true, TabVideo, -1, true); y+=h;
			txt=L"Screen [ "; txt+=driver->getScreenSize().Width;
			txt+=L" x "; txt+=driver->getScreenSize().Height;
			txt+=L" x "; txt+=video::IImage::getBitsPerPixelFromFormat(driver->getColorFormat()); txt+=L" ]";
			env->addStaticText(txt.c_str(), core::recti(x,y,x+w-1,y+h-1), true, true, TabVideo, -1, true); y+=h;

			x = 200;
			w = 100;
			y = h;
			h = 14;

			{
				txt=L"VideoModeCount = "; txt+=(s32)modeList->getVideoModeCount();
				gui::IGUIEditBox* edt = env->addEditBox( txt.c_str(), core::recti (x,y,x+w-1,y+h-1), true, TabVideo, -1);
				edt->setEnabled(false);
				y+=h;
			}

			gui::IGUIListBox* modeListBox = env->addListBox(core::recti (x,y,x+w-1,300), TabVideo, -1, true);
			if (modeListBox)
			{
				modeListBox->setAutoScrollEnabled(true);
				modeListBox->setItemHeight( 16 );
				for (s32 i=0; i<modeList->getVideoModeCount(); i++)
				{
					core::stringw txt=L"(";
					txt+=i;
					txt+=L") ";
					txt+=(s32)modeList->getVideoModeResolution(i).Width;
					txt+=L" x ";
					txt+=(s32)modeList->getVideoModeResolution(i).Height;
					txt+=L" x ";
					txt+=(s32)modeList->getVideoModeDepth(i);
					txt+=L" ";
					u32 index = modeListBox->addItem( txt.c_str() );
					modeListBox->setItemOverrideColor( index, video::SColor(255,0,0,255) );

				}
				modeListBox->setSelected( modeListBox->getItemCount()-1 );
			}

			x = 300;
			w = 250;
			y = h;
			h = 14;

			{
				txt=L"DriverFeatureCount = "; txt+=(s32)video::EVDF_COUNT;
				gui::IGUIEditBox* edt = env->addEditBox( txt.c_str(), core::recti (x,y,TabVideo->getRelativePosition().getWidth()-1,y+h-1), true, TabVideo, -1);
				edt->setEnabled(false);
				y+=h;
			}

			gui::IGUIListBox* lbox = env->addListBox( core::recti(x,y,x+w-1, TabVideo->getRelativePosition().getHeight() ), TabVideo, -1, true);
			lbox->setAutoScrollEnabled(true);
			lbox->setItemHeight( 10 );

			for (s32 i=0; i<(s32)video::EVDF_COUNT; i++)
			{
				txt=L"("; txt+=i; txt+=L") ";
				txt+=video::E_VIDEO_DRIVER_FEATURE_STRINGS[i]; txt+=L" [ ";
				bool result = driver->queryFeature( (video::E_VIDEO_DRIVER_FEATURE)i );
				txt+=(result)?L"Yes":L"No";
				txt+=L" ]";
				u32 index = lbox->addItem(txt.c_str());
				if (result)
				{
					lbox->setItemOverrideColor( index, video::SColor(255,30,140,30) );
				}
				else
				{
					lbox->setItemOverrideColor( index, video::SColor(255,255,40,40) );
				}

//				gui::IGUIStaticText* lb1 = env->addStaticText(txt.c_str(), core::recti(x,y,x+w-1-40,y+h-1), true, true, TabVideo, -1, true);
//				lb1->setOverrideColor( video::SColor(255,0,0,0) );
//
//				gui::IGUIStaticText* lb2 = env->addStaticText(txt.c_str(), core::recti(x+w-40,y,x+w-1,y+h-1), true, true, TabVideo, -1, true);
//				if (result)
//				{
//					lb2->setOverrideColor( video::SColor(255,0,200,0) );
//				}
//				else
//				{
//					lb2->setOverrideColor( video::SColor(255,255,0,0) );
//				}
//				y+=h;
			}
			lbox->setSelected(lbox->getItemCount()-1);

			}

			Window->setVisible(false);
			OptionWindow->setVisible(false);

			Device->setEventReceiver( this );
			Device->run();
			Device->getLogger()->log("SimpleEventReceiver attached to IrrlichtDevice", ELL_INFORMATION);
		}
	}

	virtual ~SimpleEventReceiver()
	{
	#ifdef _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_
		if (FileStream.is_open())
			FileStream.close();
	#endif  // _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_
	}

    virtual bool OnEvent (const SEvent &event)
    {
        if(event.EventType == EET_LOG_TEXT_EVENT)
        {
			//! save string in tmp
			core::stringc tmp = event.LogEvent.Text;

			//! standard console print
			printf("%s\n", tmp.c_str());

			//! filelogging
			#ifdef _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_
			switch (event.LogEvent.Level)
			{
				case ELL_NONE: FileStream<<"OK: "; break;
				case ELL_DEBUG: FileStream<<"DEBUG: "; break;
				case ELL_INFORMATION: FileStream<<"INFORMATION: "; break;
				case ELL_WARNING: FileStream<<"WARNING: "; break;
				case ELL_ERROR: FileStream<<"ERROR: "; break;
				default: break;
			}
            FileStream<<tmp.c_str()<<std::endl;
			#endif  // _IRR_COMPILE_WITH_EVENT_RECEIVER_FILELOG_

			//! logbox
			if (LogBox)
			{
				u32 index = LogBox->addItem( core::stringw(tmp).c_str() );
				switch (event.LogEvent.Level)
				{
					case ELL_NONE: LogBox->setItemOverrideColor(index, gui::EGUI_LBC_TEXT, video::SColor(255,0,200,0)); break;
					case ELL_DEBUG: LogBox->setItemOverrideColor(index, gui::EGUI_LBC_TEXT, video::SColor(255,255,0,200)); break;
					case ELL_INFORMATION: LogBox->setItemOverrideColor(index, gui::EGUI_LBC_TEXT, video::SColor(255,255,255,255)); break;
					case ELL_WARNING: LogBox->setItemOverrideColor(index, gui::EGUI_LBC_TEXT, video::SColor(255,255,160,0)); break;
					case ELL_ERROR: LogBox->setItemOverrideColor(index, gui::EGUI_LBC_TEXT, video::SColor(255,255,0,0)); break;
					default: break;
				}

				LogBox->setSelected( index );
			}
            return true;
		}


		if (event.EventType == EET_GUI_EVENT)
		{
			if (event.GUIEvent.EventType == gui::EGET_ELEMENT_CLOSED)
			{
				if( Window->isMyChild(event.GUIEvent.Caller) )
				{
					return true;
				}
			}
			return false;
		}
		//! ESC + Space
        if(event.EventType == EET_KEY_INPUT_EVENT)
        {
            if(event.KeyInput.Key == KEY_ESCAPE)
            {
                if (Device)
                {
					Device->closeDevice();
					Device = 0;
                }
                return true;
            }
            if(event.KeyInput.Key == KEY_SPACE && !event.KeyInput.PressedDown)
            {
                if (Device)
                {
					scene::ICameraSceneNode* camera = Device->getSceneManager()->getActiveCamera();
					if (camera)
					{
						core::dimension2du scr = Device->getVideoDriver()->getScreenSize();
						if ((scr.Width != ScreenSize.Width) || (scr.Height != ScreenSize.Height))
						{
							ScreenSize = scr;
							camera->setAspectRatio( (f32)ScreenSize.Width / ScreenSize.Height );
						}

						if (!camera->isInputReceiverEnabled())
						{
//							if (LogBox)
//							{
//								if (LogBox->isVisible())
//								{
//									LogBox->setVisible(false);
//								}
//							}
							if (Window)
							{
								Window->setVisible(false);
								OptionWindow->setVisible(false);
							}

							Device->getCursorControl()->setPosition( core::position2di(scr.Width/2, scr.Height/2) );
						}
						else
						{
							if (Window)
							{
								Window->setVisible(true);
								OptionWindow->setVisible(true);
							}
						}
						camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
					}
                }
            }
        }

        //! none
        return false;
    }
};

}


#endif

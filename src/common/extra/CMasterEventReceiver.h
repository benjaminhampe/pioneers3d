/***************************************************************
 * Name:      eventReceiver.h
 * Author:    Benjamin Hampe (BenjaminHampe@gmx.de)
 * License:	  LGPL
 **************************************************************/

#ifndef __IRR_C_MASTER_EVENT_RECEIVER_H__
#define __IRR_C_MASTER_EVENT_RECEIVER_H__

#include <irrlicht.h>

namespace irr{

class CMasterEventReceiver : public IEventReceiver
{
public:
    CMasterEventReceiver( IrrlichtDevice* device );

    virtual ~CMasterEventReceiver();

//	manage EventReceiver
	virtual bool addReceiver( IEventReceiver* recv );

	virtual u32 getReceiverCount() const;

	virtual IEventReceiver* getReceiver( u32 index );

	virtual bool eraseReceiver( u32 index );

	virtual bool clearReceiver( );

	virtual bool hasReceiver( IEventReceiver* recv ) const;

	// virtual void setReceiverEnabled( );

//	main Event processing
	virtual bool OnEvent(const SEvent& event);

	virtual bool OnLogEvent( const SEvent& logEvent );

	virtual bool OnKeyEvent( const SEvent& keyEvent );

	virtual bool OnMouseEvent( const SEvent& mouseEvent );

	virtual bool OnGUIEvent( const SEvent& guiEvent );

	virtual void OnSize( const core::dimension2du& newSize );

//	get keyboard states
	virtual bool getKeyState( EKEY_CODE keyCode ) const;

	virtual bool isKeyDown( EKEY_CODE keyCode ) const;

	virtual bool isKeyUp( EKEY_CODE keyCode ) const;

//	get mouse states
	virtual s32 getMouseX() const;

	virtual s32 getMouseY() const;

	virtual s32 getMouseZ() const;

	virtual bool isMouseOver( s32 x1, s32 y1, s32 x2, s32 y2 ) const;

	virtual bool isMouseMove() const;

	virtual bool isMouseWheel() const;

	virtual bool isMouseClick() const;

	virtual bool isMouseLeftDown() const;

	virtual bool isMouseLeftUp() const;

	virtual bool isMouseRightDown() const;

	virtual bool isMouseRightUp() const;

	virtual bool isMouseMiddleDown() const;

	virtual bool isMouseMiddleUp() const;

	virtual gui::IGUIElement* getFocused() const;

	virtual gui::IGUIElement* getHovered() const;

protected:

	virtual gui::IGUIContextMenu* createMenuBar( gui::IGUIElement* parent );

	virtual void OnAbout();

	// virtual void OnMenuItemSelected( gui::IGUIContextMenu* menu );

private:

//	pointer to main Irrlicht-Device
    IrrlichtDevice* Device;

//	saves Screen Resolution and tests for resize-event
    core::dimension2du ScreenSize;

//	Keyboard Keystates, 0 == none, 1==down, 2==hold, 3==up
	core::array<s8> KeyStates[ KEY_KEY_CODES_COUNT ];

//	Internal EventReceiver list
    core::array<IEventReceiver*> Receiver;

//	GUI-Control
	gui::IGUIContextMenu* MenuBar;
	gui::IGUIToolBar* ToolBar;
    gui::IGUIElement* Hovered;
    gui::IGUIElement* Focused;
    gui::IGUIElement* Clicked;

//	Scene-Control
	scene::ISceneNode* Model;
	scene::ICameraSceneNode* Camera;
	bool use_light;
	bool use_wireframe;
	bool use_fog;

};

} // end namespace irr

#endif // __IRR_C_SSD_3D_MASTER_EVENT_RECEIVER_H__

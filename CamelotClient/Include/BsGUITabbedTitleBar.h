#pragma once

#include "BsEditorPrerequisites.h"
#include "BsGUIElementContainer.h"
#include "CmRectI.h"
#include <boost/signal.hpp>

namespace BansheeEditor
{
	class GUITabbedTitleBar : public BS::GUIElementContainer
	{
	public:
		static const CM::String& getGUITypeName();

		static GUITabbedTitleBar* create(BS::GUIWidget& parent, CM::RenderWindow* parentWindow,
			BS::GUIElementStyle* backgroundStyle = nullptr, BS::GUIElementStyle* tabBtnStyle = nullptr, 
			BS::GUIElementStyle* minBtnStyle = nullptr, BS::GUIElementStyle* closeBtnStyle = nullptr);

		static GUITabbedTitleBar* create(BS::GUIWidget& parent, CM::RenderWindow* parentWindow, const BS::GUILayoutOptions& layoutOptions);
		static GUITabbedTitleBar* create(BS::GUIWidget& parent, CM::RenderWindow* parentWindow, const BS::GUILayoutOptions& layoutOptions, 
			BS::GUIElementStyle* backgroundStyle = nullptr, BS::GUIElementStyle* tabBtnStyle = nullptr, 
			BS::GUIElementStyle* minBtnStyle = nullptr, BS::GUIElementStyle* closeBtnStyle = nullptr);

		void addTab(const CM::HString& name);
		void insertTab(CM::UINT32 idx, const CM::HString& name);
		void removeTab(CM::UINT32 idx);

		boost::signal<void(CM::UINT32)> onTabActivated;
		boost::signal<void(CM::UINT32)> onTabClosed;
		boost::signal<void(CM::UINT32)> onTabDraggedOff;
		boost::signal<void(CM::UINT32)> onTabDraggedOn;

	protected:
		virtual ~GUITabbedTitleBar();

		void updateClippedBounds();

		void _updateLayoutInternal(CM::INT32 x, CM::INT32 y, CM::UINT32 width, CM::UINT32 height,
			CM::RectI clipRect, CM::UINT8 widgetDepth, CM::UINT16 areaDepth);
	protected:
		static const CM::UINT32 TAB_SPACING;
		static const CM::UINT32 OPTION_BTN_SPACING;

		CM::Vector<GUITabButton*>::type mTabButtons;

		CM::UINT32 mUniqueTabIdx;
		CM::UINT32 mActiveTabIdx;
		BS::GUITexture* mBackgroundImage;
		BS::GUIButton* mMinBtn;
		BS::GUIButton* mCloseBtn;
		BS::GUIToggleGroupPtr mTabToggleGroup;
		CM::RenderWindow* mParentWindow;

		EditorWidget* mTempDraggedWidget;
		CM::UINT32 mTempDraggedTabIdx;

		bool mDragInProgress;
		GUITabButton* mDraggedBtn;
		CM::INT32 mDragBtnOffset;
		CM::INT32 mInitialDragOffset;

		const BS::GUIElementStyle* mBackgroundStyle;
		const BS::GUIElementStyle* mCloseBtnStyle;
		const BS::GUIElementStyle* mMinimizeBtnStyle;
		const BS::GUIElementStyle* mTabBtnStyle;

		GUITabbedTitleBar(BS::GUIWidget& parent, CM::RenderWindow* parentWindow, BS::GUIElementStyle* backgroundStyle, BS::GUIElementStyle* tabBtnStyle, 
			BS::GUIElementStyle* minBtnStyle, BS::GUIElementStyle* closeBtnStyle, const BS::GUILayoutOptions& layoutOptions);

		virtual bool mouseEvent(const BS::GUIMouseEvent& ev);
		virtual CM::UINT32 getNumChildElements() const;
		virtual GUIElement* getChildElement(CM::UINT32 idx) const;

		void tabToggled(CM::UINT32 tabIdx);
		void tabClosed();
		void tabDragged(CM::UINT32 tabIdx, const CM::Vector2I& dragPos);
		void tabDragEnd(CM::UINT32 tabIdx, const CM::Vector2I& dragPos);

		CM::INT32 uniqueIdxToSeqIdx(CM::UINT32 uniqueIdx) const;
	};
}
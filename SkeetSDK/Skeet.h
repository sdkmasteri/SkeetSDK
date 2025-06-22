#ifndef SKEET_H
#define SKEET_H

#pragma pack(1)

typedef struct Menu;
typedef struct CTab;
typedef struct Child;
typedef struct Hotkey;
typedef union Element;

typedef void(__thiscall* CallbackFn)(void*);
typedef int(__fastcall* SetKeyFn)(void*, unsigned int, unsigned int);
typedef void(__thiscall* TabSwitchFn)(void*, int);
typedef unsigned int(__fastcall* HashFn)(const wchar_t*);
typedef void(__fastcall* SetModeFn)(void*, void*, int);
typedef void(__fastcall* SetCheckFn)(void*, int, int);
typedef void(__fastcall* HideUiFn)(void*, void*, bool);

enum Tab
{
	Rage,
	AA,
	Legit,
	Visuals,
	Misc,
	Skins,
	Plist,
	Config,
	Lua
};

enum MenuStatus
{
	MenuClosed,
	MenuOpened,
	MenuDragged = 5,
	MenuScaled = 8
};

enum ChildStatus
{
	ChildIdle,
	ChildDragged,
	ChildResized
};

enum MouseStatus
{
	MouseIdle,
	LClick,
	RClick
};

enum PickerStatus
{
	PickerIdle,
	PickerClicked,
	PickerTint,
	PickerHue,
	PickerAlpha
};

enum UiType : unsigned char
{
	UiNone = 0,
	UiTab,
	UiButton,
	UiCheckbox,
	UiCombobox,
	UiSlider,
	UiListbox,
	UiChild,
	UiLabel,
	UiHotkey,
	UiTextbox,
	UiColorPicker = 12,
	UiMultiselect
};

enum HotkeyMode
{
	Inherit = -1,
	AlwaysOn,
	OnHotkey,
	Toggle,
	OffHotkey
};

typedef struct
{
	int x;
	int y;
} Vec2;

typedef struct
{
	unsigned char X;
	unsigned char y;
	unsigned char z;
	unsigned char w;
} Vec4_8t;

typedef struct
{
	MouseStatus Status;
	Vec2		Pos;
	Vec2		LastMenuPos;
} MouseInfo;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} VecCol;

typedef struct
{
	bool Editable;
	bool Visible;
	bool Hovered;
	bool AllowMouseInput;
	bool SameLine;
} Flags;

template <typename T>
struct Header
{
	char	pad1[0x10];
	T*		Parent;		// 0x10
	Flags	Flags;		// 0x14
	UiType	Type;		// 0x19
	char	pad2[0x6];
};

typedef struct
{
	Header<Child>	Header;
	Vec2			Pos;			// 0x20
	Vec2			Size;			// 0x28
	char			pad1[0x8];
	unsigned int*	HashedName;		// 0x38
	char			pad2[0x14];
	VecCol			Color;			// 0x50
	int				LeftPaddign;	// 0x54
	char			pad3[0x4];
	int*			Value;			// 0x5C
	Vec2			DefSize;		// 0x60
	bool			Active;			// 0x68
	bool			Tooltip;		// 0x69
	char			pad4[0x27];
	int				Max;			// 0x90
	int				Min;			// 0x94
	float			Step;			// 0x98
	int				MaxLen;			// 0x9C
} Slider;

typedef struct
{
	Header<Child>	Header;
	Vec2			Pos;			// 0x20
	Vec2			ActivateSize;	// 0x28
	char			pad1[0x8];
	unsigned int*	HashedName;		// 0x38
	char			pad2[0x14];
	VecCol			Color;			// 0x50
	int				LeftPaddign;	// 0x54
	char			pad3[0x4];
	int*			Value;			// 0x5C
	Vec2			Size;			// 0x60
	int				TextPadding;	// 0x68
} Checkbox;

typedef struct
{
	Header<Child>	Header;
	Vec2			Pos;				// 0x20
	Vec2			Size;				// 0x28
	Vec2			OuterPadding;		// 0x30
	unsigned int*	HashedName;			// 0x38
	char			pad1[0x14];
	VecCol			Color;				// 0x50
	int				LeftPaddign;		// 0x54
	char			pad2[0x4];
	int*			Value;				// 0x5C
	int				Height;				// 0x60
	char			pad3[0x4];
	bool			Popup;				// 0x68
	bool			Clicked;			// 0x69
	bool			NotNull;			// 0x6A
	char			pad4;
	int				HoveredItem;		// 0x6C
	char*			StringValue;		// 0x70
	char*			StringValueEnd;		// 0x74
	int*			StringValueChunkEnd;// 0x78
} Multiselect;

typedef struct
{
	char		pad1[0x10];
	int			Key;		// 0x10
	HotkeyMode	Mode;		// 0x14
} HotkeyInfo;

typedef struct
{
	wchar_t* data;
	int	len;
} wchar_str;

typedef struct
{
	Header<Hotkey>	Header;
	Vec4_8t			XAxis;			// 0x20
	Vec4_8t			YAxis;			// 0x24
	Vec2			Size;			// 0x28
	char			pad3[0x20];
	VecCol			Color;			// 0x50
	char			pad4[0x14];
	int				HoveredItem;	// 0x68
	int				SelectedItem;	// 0x6C
	SetModeFn		SetMode;		// 0x70
	wchar_str		Variants[4];	// 0x74
} HotkeyPopup;

struct Hotkey
{
	Header<Child>	Header;
	Vec2			Pos;					// 0x20
	Vec2			ActivateSize;			// 0x28
	Vec2			DefaultActivateSize;	// 0x30
	unsigned int*	HashedName;				// 0x38
	char			pad1[0x14];
	VecCol			Color;					// 0x50
	int				LeftPaddign;			// 0x54
	char			pad2[0x4];
	HotkeyInfo*		Info;					// 0x5C
	bool			SetingKey;				// 0x60
	char			pad3[0x2];
	wchar_t			KeyText[4];				// 0x62
	char			pad4;
	HotkeyPopup*	Popup;					// 0x6C
};

typedef struct Button
{
	Header<Child>	Header;
	Vec2			Pos;				// 0x20
	Vec2			Size;				// 0x28
	Vec2			DefSize;			// 0x30
	unsigned int*	HashedName;			// 0x38
	char			pad1[0x14];
	VecCol			Color;				// 0x50
	int				LeftPaddign;		// 0x54
};

typedef struct
{
	int		XAxis;			// 0x64
	Vec2	Size;			// 0x68
	Vec2	TintPos;		// 0x70
	Vec2	TintSize;		// 0x78
	Vec2	HuePos;			// 0x80
	Vec2	HueSize;		// 0x88
	Vec2	AlphaPos;		// 0x90
	Vec2	AlphaSize;		// 0x98
} ColorPopup;

typedef struct
{
	float	Hue;
	float	Saturation;
	float	Brightness;
} HSV, HSB;

typedef struct
{
	Header<Child>	Header;
	Vec2			Pos;			// 0x20
	Vec2			Size;			// 0x28
	Vec2			DefSize;		// 0x30
	char			pad1[0x18];
	VecCol			Color;			// 0x50
	int				LeftPaddign;	// 0x54
	char			pad2[0x4];
	VecCol*			Value;			// 0x5C
	char			pad3[0x4];
	ColorPopup		Popup;			// 0x64
	char			pad4[0x88];
	PickerStatus	Status;			// 0x128
	HSV				HSV;			// 0x12C
} ColorPicker;

typedef struct
{
	Header<Child>	Header;
	Vec2			Pos;				// 0x20
	Vec2			InnerPadding;		// 0x28
	Vec2			OuterPadding;		// 0x30
	unsigned int*	HashedName;			// 0x38
	char			pad1[0x14];
	VecCol			Color;				// 0x50
	Vec2			BoxPos;				// 0x54
	int*			Value;				// 0x5C
	int				DefHeight;			// 0x60
	int				Height;				// 0x64
	int				DefInteractOffset;	// 0x68
	int				InteractOffset;		// 0x6C
	bool			Open;				// 0x70
	bool			Clicked;			// 0x71
	char			pad2[0x2];
	int				HoveredItem;		// 0x74
	int				SelectedItem;		// 0x78
} Combobox;

typedef struct
{
	Header<Child>	Header;
	Vec2			Pos;				// 0x20
	Vec2			OuterPadding;		// 0x28
	Vec2			DefOuterPadding;	// 0x30
	unsigned int*	HashedName;			// 0x38
	char			pad1[0x18];
	VecCol			Color;				// 0x50
	int				LeftPaddign;		// 0x54
} Label;

typedef struct
{
	char		pad1[0x4];
	int			SelectedItem;
} ListboxInfo;

typedef struct
{
	Header<Child>	Header;
	Vec2			Pos;				// 0x20
	Vec2			Size;				// 0x28
	char			pad1[0x8];
	unsigned int*	HashedName;			// 0x38
	char			pad2[0x14];
	VecCol			Color;				// 0x50
	int				LeftPaddign;		// 0x54
	char			pad3[0x8];
	int				ElementSize;		// 0x60
	ListboxInfo*	Info;				// 0x64
} Listbox;

typedef struct
{
	Header<Child>	Header;
	Vec2			Pos;				// 0x20
	Vec2			Size;				// 0x28
	char			pad1[0x8];
	unsigned int*	HashedName;			// 0x38
	char			pad2[0x14];
	VecCol			Color;				// 0x50
	int				LeftPaddign;		// 0x54
	char			pad3[0xC];
	int				Length;				// 0x64
	wchar_t			Text[0x3F];			// 0x68
} Textbox;

union Element
{
	Header<Child>	header;
	Slider			slider;
	Checkbox		checkbox;
	Multiselect		multiselect;
	Hotkey			hotkey;
	Button			button;
	ColorPicker		colorpicker;
	Combobox		combobox;
	Label			label;
	Listbox			listbox;
	Textbox			textbox;
};

struct Child
{
	Header<CTab>	Header;
	Vec2			Pos;			// 0x20
	Vec2			Size;			// 0x28
	Vec2			DefSize;		// 0x30
	char			pad3[0x18];
	VecCol			Color;			// 0x50
	char			pad4[0x14];
	int				InnerPadding;	// 0x68
	int				OuterPadding;	// 0x6C
	Vec4_8t			PosSizePadd;	// 0x70
	Vec2			MouseLastPos;	// 0x74
	ChildStatus		Status;			// 0x7C
	Element**		Elements;		// 0x80
};

struct CTab
{
	Header<void>	Header;			// actualy CTab has no parent
	Vec2			Pos;			// 0x20
	Vec2			Size;			// 0x28
	Vec2			DefSize;		// 0x30
	char			pad4[0x18];
	VecCol			Color;			// 0x50
	char			pad5[0xC];
	Menu*			Parent;			// 0x60
	char			pad6[0xC];
	Child**			Childs;			// 0x70
};

typedef struct
{
	CTab* Rage;
	CTab* AA;
	CTab* Legit;
	CTab* Visuals;
	CTab* Misc;
	CTab* Skins;
	CTab* Plist;
	CTab* Config;
	CTab* Lua;
} Tabs;

struct Menu
{
	char		pad1[0xC];
	Vec2		Pos;				// 0xC
	Vec2		Size;				// 0x14
	Vec2		MinSize;			// 0x1C
	Vec2		TabStartPadding;	// 0x24
	Vec2		TabEndPadding;		// 0x2C
	MenuStatus	MenuStatus;			// 0x34
	MouseInfo	Mouse;				// 0x38
	char		pad2[0x8];
	Tabs*		Tabs;				// 0x54
};


static struct SkeetSDK
{
	static Menu* menu;
	static TabSwitchFn	TabSwitch;
	static CallbackFn	Callback;
	static HashFn		Hash;
	static SetKeyFn		SetKey;
	static SetCheckFn	SetCheck;
	static HideUiFn		HideUi;
	static void WaitForMenu()
	{
		while (!menu->Size.x) Sleep(50);
	};
	static void	SetTab(Tab tab)
	{
		TabSwitch(menu, tab);
	};
	static void	SetVisible(Element* element, bool value)
	{
		HideUi(element, element, value);
	};
	static void SetCheckbox(Checkbox* checkbox, int value)
	{
		SetCheck(checkbox, checkbox->Value[0], value);
	};
	static void SetColorRGBA(ColorPicker picker, VecCol Color)
	{
		picker.Value[0] = Color;
		Callback(&picker);
	};
	static void SetColorHSV(ColorPicker picker, HSV Color)
	{
		picker.HSV = Color;
		Callback(&picker);
	};
	static void SetSlider(Slider slider, int value)
	{
		slider.Value[0] = value;
		Callback(&slider);
	};
	static void SetCombobox(Combobox combobox, int value)
	{
		combobox.SelectedItem = value;
		Callback(&combobox);
	};
	static void SetListbox(Listbox listbox, int value)
	{
		listbox.Info->SelectedItem = value;
		Callback(&listbox);
	};
	static void SetHotkey(Hotkey* hotkey, int key, HotkeyMode mode = Inherit)
	{
		SetKey(hotkey, key, 0);
		if (mode != Inherit)
			hotkey->Popup->SetMode(hotkey, hotkey->Popup, mode);
	};
	static int ExtractKey(Hotkey hotkey)
	{
		return hotkey.Info->Key >> 2;
	};
	static int HotkeyState(Hotkey hotkey)
	{
		return (hotkey.Info->Key >> 1) & 1;
	};
	static void LoadCfg(int index = -1)
	{
		if (index >= 0)
			SetListbox(menu->Tabs->Config->Childs[0]->Elements[0]->listbox, index);
		Callback(menu->Tabs->Config->Childs[0]->Elements[3]);
	}
	template <typename Fn, UiType T = UiNone>
	static void ForEach(Element** elements, Fn func)
	{
		while (*elements)
		{
			if (T == UiNone)
			{
				func(*elements);
			}
			else if ((*elements)->header.Type == T)
			{
				func(*elements);
			}
			elements++;
		}
	}
} Skeet;

Menu*		SkeetSDK::menu		= (Menu*)0x434799AC;
TabSwitchFn SkeetSDK::TabSwitch	= (TabSwitchFn)0x433B75D3;
CallbackFn	SkeetSDK::Callback	= (CallbackFn)0x4334E09F;
HashFn		SkeetSDK::Hash		= (HashFn)0x4334ADB0;
SetKeyFn	SkeetSDK::SetKey	= (SetKeyFn)0x4341859F;
SetCheckFn	SkeetSDK::SetCheck	= (SetCheckFn)0x433AD3C8;
HideUiFn	SkeetSDK::HideUi	= (HideUiFn)0x433E000B;

#endif // SKEET_H
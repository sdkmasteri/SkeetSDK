#ifndef SKEET_H
#define SKEET_H

#define LABEL_SIZE		0x60
#define HOTKEY_SIZE		0x70
#define HOTKEYINFO_SIZE	0x28
#define SLIDER_SIZE		0x124
#define TEXTBOX_SIZE	0xE8
#define CHECKBOX_SIZE	0x78

#pragma pack(1)

typedef struct XorW;
typedef struct CTab;
typedef struct CMenu;
typedef struct Child;
typedef struct Label;
typedef struct Hotkey;
typedef struct HotkeyInfo;
typedef struct Slider;
typedef struct Textbox;
typedef struct Combobox;
typedef struct Checkbox;

typedef union Element;


typedef void* (__cdecl* CFn)(void);	//__cdecl ptr return
typedef void(__thiscall* ThisFn)(void*);
typedef bool(__fastcall* LoadLuaFn)(wchar_t*, void*);
typedef int(__fastcall* SetKeyFn)(void*, unsigned int, unsigned int);
typedef void(__thiscall* ThisIntFn)(void*, int);
typedef unsigned int(__fastcall* HashFn)(const wchar_t*);
typedef void(__fastcall* SetModeFn)(void*, void*, int);
typedef void(__fastcall* SetCheckFn)(void*, int, int);
typedef void(__fastcall* HideUiFn)(void*, void*, bool);
typedef void(__fastcall* F2PFn)(void*, void*);	//__fascall 2 pointers
typedef int(__fastcall* DecryptFn)(XorW*, int, wchar_t*, int);
typedef void* (__thiscall* AddLabelFn)(void*, bool, const wchar_t*);
typedef void(__thiscall* InsertFn)(void*, bool, void*);
typedef void* (__thiscall* AllocatorFn)(int);
typedef void* (__thiscall* TBConstFn)(void*, void*); // Textbox constructor
typedef void* (__thiscall* LConstFn)(void*, void*, const wchar_t*); // Label constructor
typedef void* (__thiscall* CConstFn)(void*, void*, wchar_t*, int*);	// Checkbox constructor
typedef void* (__thiscall* SConstFn)(void*, void*, wchar_t*, int, int, int*, bool, unsigned int, float); // Slider constructor
typedef void* (__thiscall* HKConstFn)(void*, void*, void*, bool); // Hotkey constructor

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
	UiMultiselect,
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

struct XorW
{
	unsigned short key;
	unsigned short bsize;
	wchar_t data[];
};

// Not all elements have correct pointer to this struct and ChunkEnd, so check ts for NULL
typedef struct
{
	CMenu*	Menu;
	F2PFn	function;	// function(Menu, elementptr)

} Call;

// T = ParentType, ST = IndexType
template <typename T, typename ST>
struct Header
{
	void*	Vtable;		// honestly I dont even know whats inside
	char	pad1[0x8];
	ST		Index;		// 0xC	int CTab - tab index. in Childs - first element index. in Elements - element index
	T*		Parent;		// 0x10
	Flags	Flags;		// 0x14
	UiType	Type;		// 0x19
	char	pad2[0x6];
};

// Slider is 0x124 bytes long
struct Slider
{
	Header<Child, int>	Header;
	Vec2				Pos;			// 0x20
	Vec2				Size;			// 0x28
	char				pad1[0x8];
	XorW*				CryptedName;	// 0x38
	char				pad2[0x14];
	VecCol				Color;			// 0x50
	int					LeftPaddign;	// 0x54
	char				pad3[0x4];
	int*				Value;			// 0x5C
	Vec2				DefSize;		// 0x60
	bool				Active;			// 0x68
	bool				Tooltip;		// 0x69
	char				pad4[0x26];
	int					Max;			// 0x90
	int					Min;			// 0x94
	float				Step;			// 0x98
	int					MaxLen;			// 0x9C
	char				pad5[0x84];
};

// Checkbox is 0x78 bytes long
struct Checkbox
{
	Header<Child, int>	Header;
	Vec2				Pos;			// 0x20
	Vec2				ActivateSize;	// 0x28
	char				pad1[0x8];
	XorW*				CryptedName;	// 0x38
	char				pad2[0x14];
	VecCol				Color;			// 0x50
	int					LeftPaddign;	// 0x54
	char				pad3[0x4];
	int*				Value;			// 0x5C
	Vec2				Size;			// 0x60
	int					TextPadding;	// 0x68
	char				pad4[0xC];
};

typedef struct
{
	Header<Child, int>	Header;
	Vec2				Pos;				// 0x20
	Vec2				Size;				// 0x28
	Vec2				OuterPadding;		// 0x30
	XorW*				CryptedName;		// 0x38
	char				pad1[0x14];
	VecCol				Color;				// 0x50
	int					LeftPaddign;		// 0x54
	char				pad2[0x4];
	int*				Value;				// 0x5C
	int					Height;				// 0x60
	char				pad3[0x4];
	bool				Popup;				// 0x68
	bool				Clicked;			// 0x69
	bool				NotNull;			// 0x6A
	char				pad4;
	int					HoveredItem;		// 0x6C
	char*				StringValue;		// 0x70
	char*				StringValueEnd;		// 0x74
	int*				StringValueChunkEnd;// 0x78
} Multiselect;

typedef struct
{
	wchar_t* data;
	int	len;
} wchar_str;

typedef struct
{
	short	 index;
	short	 active; //8000 if active?? 
	wchar_t* start;
	void*	 end;
	char	 pad2[0x8];
} wchar_set;

typedef struct
{
	Header<Hotkey, int>	Header;
	Vec4_8t				XAxis;			// 0x20
	Vec4_8t				YAxis;			// 0x24
	Vec2				Size;			// 0x28
	char				pad3[0x20];
	VecCol				Color;			// 0x50
	char				pad4[0x14];
	int					HoveredItem;	// 0x68
	int					SelectedItem;	// 0x6C
	SetModeFn			SetMode;		// 0x70
	wchar_str			Variants[4];	// 0x74
} HotkeyPopup;

// HotkeyInfo is 0x28 bytes long
struct HotkeyInfo
{
	char			pad1[0x10];
	int				Key;		// 0x10
	HotkeyMode		Mode;		// 0x14
	char			pad[0x10];
};

// Hotkey is 0x70 bytes long
struct Hotkey
{
	Header<Child, int>	Header;
	Vec2				Pos;					// 0x20
	Vec2				ActivateSize;			// 0x28
	Vec2				DefaultActivateSize;	// 0x30
	XorW*				CryptedName;			// 0x38
	char				pad1[0x14];
	VecCol				Color;					// 0x50
	int					LeftPaddign;			// 0x54
	char				pad2[0x4];
	HotkeyInfo*			Info;					// 0x5C
	bool				SetingKey;				// 0x60
	char				pad3;
	wchar_t				KeyText[0x4];			// 0x62
	char				pad4[0x2];
	HotkeyPopup*		Popup;					// 0x6C
};

typedef struct Button
{
	Header<Child, int>	Header;
	Vec2				Pos;				// 0x20
	Vec2				Size;				// 0x28
	Vec2				DefSize;			// 0x30
	XorW*				CryptedName;		// 0x38
	char				pad1[0x4];
	Call*				Call;				// 0x40
	void*				CallChunkEnd;		// 0x44
	char				pad2[0x8];
	VecCol				Color;				// 0x50
	int					LeftPaddign;		// 0x54
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
	float	Value;
} HSV, HSB;

typedef struct
{
	Header<Child, int>	Header;
	Vec2				Pos;			// 0x20
	Vec2				Size;			// 0x28
	Vec2				DefSize;		// 0x30
	char				pad1[0x18];
	VecCol				Color;			// 0x50
	int					LeftPaddign;	// 0x54
	char				pad2[0x4];
	VecCol*				Value;			// 0x5C
	char				pad3[0x4];
	ColorPopup			Popup;			// 0x64
	char				pad4[0x88];
	PickerStatus		Status;			// 0x128
	HSV					HSV;			// 0x12C
} ColorPicker;

struct Combobox
{
	Header<Child, int>	Header;
	Vec2				Pos;				// 0x20
	Vec2				InnerPadding;		// 0x28
	Vec2				OuterPadding;		// 0x30
	XorW*				CryptedName;		// 0x38
	char				pad1[0x4];
	Call*				Call;				// 0x40
	void*				CallChunkEnd;		// 0x44
	char				pad2[0x8];
	VecCol				Color;				// 0x50
	Vec2				BoxPos;				// 0x54
	int*				Value;				// 0x5C
	int					DefHeight;			// 0x60
	int					Height;				// 0x64
	int					DefInteractOffset;	// 0x68
	int					InteractOffset;		// 0x6C
	bool				Open;				// 0x70
	bool				Clicked;			// 0x71
	char				pad3[0x2];
	int					HoveredItem;		// 0x74
	int					SelectedItem;		// 0x78
};

// Label 0x60 bytes long
struct Label
{
	Header<Child, int>	Header;
	Vec2				Pos;				// 0x20
	Vec2				OuterPadding;		// 0x28
	Vec2				DefOuterPadding;	// 0x30
	XorW*				CryptedName;		// 0x38
	char				pad1[0x4];
	Call*				Call;				// 0x40
	void*				CallChunkEnd;		// 0x44
	char				pad2[0x8];
	VecCol				Color;				// 0x50
	int					LeftPaddign;		// 0x54
	char				pad3[0x8];
};

typedef struct
{
	char		pad1[0x4];
	int			SelectedItem;	// 0x4
	char		pad2[0x4];
	wchar_set*	Items;			// 0xC
	void*		ItemsChunkEnd;	// 0x10
	char		pad3[0x4];
} ListboxInfo;

typedef struct
{
	Header<Child, int>	Header;
	Vec2				Pos;				// 0x20
	Vec2				Size;				// 0x28
	char				pad1[0x8];
	XorW*				CryptedName;		// 0x38
	char				pad2[0x4];
	Call*				Call;				// 0x40
	void*				CallChunkEnd;		// 0x44
	char				pad3[0x8];
	VecCol				Color;				// 0x50
	int					LeftPaddign;		// 0x54
	char				pad4[0x8];
	int					ElementSize;		// 0x60
	ListboxInfo*		PInfo;				// 0x64
	char				pad5[0x1C];
	ListboxInfo			Info;				// 0x84
} Listbox;

// Textbox is 0xE8 bytes long
struct Textbox
{
	Header<Child, int>	Header;
	Vec2				Pos;				// 0x20
	Vec2				Size;				// 0x28
	char				pad1[0x8];
	XorW*				CryptedName;		// 0x38
	char				pad2[0x4];
	Call*				Call;				// 0x40
	void*				CallChunkEnd;		// 0x44
	char				pad3[0x8];
	VecCol				Color;				// 0x50
	int					LeftPaddign;		// 0x54
	char				pad4[0xC];
	int					Length;				// 0x64
	wchar_t				Text[0x40];			// 0x68
};

typedef struct
{
	char pad1[0x5C];
	void* ptr;
} Inspector;

union Element
{
	Header<Child, int>	header;
	Slider				slider;
	Checkbox			checkbox;
	Multiselect			multiselect;
	Hotkey				hotkey;
	Button				button;
	ColorPicker			colorpicker;
	Combobox			combobox;
	Label				label;
	Listbox				listbox;
	Textbox				textbox;
	Inspector			inspector;
};

struct Child
{
	Header<CTab, int>	Header;
	Vec2				Pos;				// 0x20
	Vec2				Size;				// 0x28
	Vec2				DefSize;			// 0x30
	XorW*				CryptedName;		// 0x38
	char				pad1[0x4];
	Call*				Call;				// 0x40
	void*				CallChunkEnd;		// 0x44
	char				pad2[0x8];
	VecCol				Color;				// 0x50
	char				pad4[0x14];
	int					InnerPadding;		// 0x68
	int					OuterPadding;		// 0x6C
	Vec4_8t				PosSizePadd;		// 0x70
	Vec2				MouseLastPos;		// 0x74
	ChildStatus			Status;				// 0x7C
	Element**			Elements;			// 0x80
	void*				ElementsChunkEnd;	// 0x84
};
typedef struct
{
	char			pad4[0x8];
	int				IconType;	// 0x80
	int				IconOffset;	// 0x84
	char			pad5[0x4];	
	Vec2			Size;		// 0x8C
} TabIcon;

struct CTab
{
	Header<void, Tab>	Header;			// actualy CTab has no parent
	Vec2				Pos;			// 0x20
	Vec2				Size;			// 0x28
	Vec2				DefSize;		// 0x30
	char				pad1[0x18];
	VecCol				Color;			// 0x50
	char				pad2[0xC];
	CMenu*				Parent;			// 0x60
	char				pad3[0xC];
	Child**				Childs;			// 0x70
	void*				ChildsChunkEnd;	// 0x74
	TabIcon				Icon;			// 0x78
	char				pad4[0x4];
	void*				Chunk;			// 0x98
	void*				ChunkEnd;		// 0x9C
};

//0x20 Struct for lua listbox chunk in Config tab
typedef struct
{
	char		pad1[0x8];
	int			OnStartup;		// 0x8
	wchar_t*	Name;			// 0xC
	void*		NameChunkEnd;	// 0x10
	char		pad2[0xC];
} LuaChunk;

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

struct CMenu
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
	void*		TabsChunkEnd;		// 0x58
};

typedef struct
{
	char	pad1[0x44];
	void*	LuaState;		// 0x44
	char	pad2[0x24];
	int		LoadedCount;	// 0x6C
} CLua;

static class SkeetSDK final
{
	static ThisIntFn	TabSwitch;
	static ThisIntFn	SetList;
	static ThisFn		Callback;
	static ThisFn		ChildLayout;
	static ThisFn		KeyInit;
	static HashFn		Hash;
	static SetKeyFn		SetKey;
	static SetCheckFn	SetCheck;
	static HideUiFn		HideUi;
	static LoadLuaFn	LoadLua;
	static DecryptFn	Decrypt;
	static F2PFn		DeleteUi;
	static ThisFn		InitTab;
	static CFn			InitState;
	static CLua**		LuaInfo;
	static AllocatorFn	Allocator;
	static InsertFn		InsertElem;
	static AddLabelFn	AddLabel;
	static LConstFn		LabelCon;
	static TBConstFn	TextboxCon;
	static CConstFn		CheckboxCon;
	static SConstFn		SliderCon;
	static HKConstFn	HotkeyCon;
public:
	static CMenu* Menu;

	static void WaitForMenu()
	{
		while (!Menu->Size.x) Sleep(50);
	};

	static void InitConfig()
	{
		InitTab(Menu->Tabs->Config);
	};

	static void	SetTab(Tab tab)
	{
		TabSwitch(Menu, tab);
	};

	static Tab GetActiveTab()
	{
		return *(Tab*)0x43479A10;
	}

	static CTab* GetActiveCTab()
	{
		return ((CTab**)Menu->Tabs)[GetActiveTab()];
	}

	static CLua* GetLuaInfo()
	{
		return *LuaInfo;
	};

	static void	SetVisible(Element* element, bool value)
	{
		HideUi(element, element, value);
	};

	static void SetInput(Element* elemen, bool val)
	{
		Header<Child, int>* head = &elemen->header;
		head->Flags.AllowMouseInput = val;
		head->Flags.Editable = val;
	};

	static void* TieValue(Element* element, void* ptr)
	{
		void* oldptr = element->inspector.ptr;
		element->inspector.ptr = ptr;
		return oldptr;
	};

	static void DeleteElement(Element* element)
	{
		DeleteUi(element, element->header.Parent->Header.Parent);
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

	static void SetListbox(Listbox* listbox, int value)
	{
		SetList(listbox, value);
		Callback(listbox);
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
			SetListbox(&Menu->Tabs->Config->Childs[0]->Elements[0]->listbox, index);
		Callback(Menu->Tabs->Config->Childs[0]->Elements[3]);
	};

	static int LuaCount()
	{
		int diff = (int)Menu->Tabs->Config->ChunkEnd - (int)Menu->Tabs->Config->Chunk;

		return diff >> 5;
	};

	static wchar_t* LuaName(int index)
	{
		if (index >= LuaCount()) return NULL;
		return Menu->Tabs->Config->Childs[1]->Elements[3]->listbox.PInfo->Items[index].start;
	};

	static const wchar_t* CurrentConfig()
	{
		unsigned int hashed = *(unsigned int*)0x4347C9F8;
		if (!hashed) return L"Default";
		size_t count = ((unsigned int)Menu->Tabs->Config->Childs[0]->Elements[0]->listbox.PInfo->ItemsChunkEnd - (unsigned int)Menu->Tabs->Config->Childs[0]->Elements[0]->listbox.PInfo->Items) / sizeof(wchar_set);
		for (size_t i = 0; i < count; i++)
		{
			if (Hash(Menu->Tabs->Config->Childs[0]->Elements[0]->listbox.PInfo->Items[i].start) == hashed)
				return Menu->Tabs->Config->Childs[0]->Elements[0]->listbox.PInfo->Items[i].start;
		}
	};

	static int CurrentConfigIndex()
	{
		unsigned int hashed = *(unsigned int*)0x4347C9F8;
		if (!hashed) return -1;
		size_t count = ((unsigned int)Menu->Tabs->Config->Childs[0]->Elements[0]->listbox.PInfo->ItemsChunkEnd - (unsigned int)Menu->Tabs->Config->Childs[0]->Elements[0]->listbox.PInfo->Items) / sizeof(wchar_set);
		for (size_t i = 0; i < count; i++)
		{
			if (Hash(Menu->Tabs->Config->Childs[0]->Elements[0]->listbox.PInfo->Items[i].start) == hashed)
				return i;
		}
	};

	static bool LoadScript(int index)
	{
		wchar_t* name = LuaName(index);
		if (name == NULL) return false;
		return LoadLua(name, GetChunkAs<LuaChunk*>(GetTab(Config)));
	};

	static bool LoadScript(wchar_t* name)
	{
		return LoadLua(name, GetChunkAs<LuaChunk*>(GetTab(Config)));
	};

	static void AllowUnsafe(int value)
	{
		SetCheckbox(&Menu->Tabs->Config->Childs[1]->Elements[1]->checkbox, value);
	};

	static wchar_t* GetName(Element* element)
	{
		wchar_t name[128];
		Decrypt(element->slider.CryptedName, 2, name, 128);
		return name;
	};

	static Element* GetByName(Child* child, const wchar_t* name)
	{
		Element** elements = child->Elements;
		while (*elements)
		{
			wchar_t* elementName = GetName(*elements);
			if (wcscmp(elementName, name) == 0)
				return *elements;
			elements++;
		}
		return NULL;
	};

	static CTab* GetTab(Tab tab)
	{
		return ((CTab**)Menu->Tabs)[tab];
	};

	static Child* GetChild(Tab tab, int index)
	{
		index -= 1;
		CTab* tabPtr = GetTab(tab);
		if (index < 0 || index >= ChildsCount(tabPtr)) return NULL;
		return tabPtr->Childs[index];
	};

	static unsigned int ChildsCount(CTab* tab)
	{
		return ((unsigned int)tab->ChildsChunkEnd - (unsigned int)tab->Childs) / sizeof(void*);
	};

	static unsigned int ElementsCount(Child* child)
	{
		return ((unsigned int)child->ElementsChunkEnd - (unsigned int)child->Elements) / sizeof(void*);
	};

	static void* LuaState()
	{
		return InitState();
	}
	
	static void InsertElement(Child* child, void* element)
	{
		InsertElem(child, 0, element);
	};
	
	static Label* CreateLabel(Child* child, wchar_t* name)
	{
		Label* ptr = (Label*)AddLabel(child, 0, name);
		ChildLayout(child);
		return ptr;
	};

	static Textbox* CreateTextbox(Child* child)
	{
		Textbox* ptr = (Textbox*)Allocator(TEXTBOX_SIZE);
		TextboxCon(ptr, child);
		InsertElement(child, ptr);
		ChildLayout(child);
		return ptr;
	};
	
	static Checkbox* CreateCheckbox(Child* child, wchar_t* name, int* value)
	{
		Checkbox* ptr = (Checkbox*)Allocator(CHECKBOX_SIZE);
		CheckboxCon(ptr, child, name, value);
		InsertElement(child, ptr);
		ChildLayout(child);
		return ptr;
	};

	static Slider* CreateSlider(Child* child, wchar_t* name, int min, int max, int* value, bool tooltip = true, wchar_t* tip = NULL, float step = 1.f)
	{
		Slider* ptr = (Slider*)Allocator(SLIDER_SIZE);
		unsigned int tipch = 0;
		if (tip != NULL)
			tipch = tip[0] | tip[1] << 16;
		SliderCon(ptr, child, name, min, max, value, tooltip, tipch, step);
		InsertElement(child, ptr);
		ChildLayout(child);
		return ptr;
	};

	static Hotkey* CreateHotkey(Child* child, wchar_t* name, bool sameline = false, int vkey = 0x00, HotkeyMode mode = AlwaysOn)
	{
		if (!sameline)
			CreateLabel(child, name);
		HotkeyInfo* info = (HotkeyInfo*)Allocator(HOTKEYINFO_SIZE);
		KeyInit(info);
		Hotkey* ptr = (Hotkey*)Allocator(HOTKEY_SIZE);
		printf("HK: %p\n", ptr);
		HotkeyCon(ptr, child, info, true);
		SetHotkey((Hotkey*)ptr, vkey, mode);
		InsertElement(child, ptr);
		ChildLayout(child);
		return ptr;
	};


	template <typename T>
	static T GetChunkAs(CTab* tab)
	{
		return reinterpret_cast<T>(tab->Chunk);
	};
	
	template <typename T>
	static T GetVFunc(void* ptr, int index)
	{
		void** vtable = (void**)(*(int*)ptr);
		return reinterpret_cast<T>(vtable[index]);
	};

	template <typename Fn, UiType T = UiNone>
	static void ForEach(Element** elements, Fn func)
	{
		while (*elements)
		{
			if (T == UiNone || (*elements)->header.Type == T)
			{
				func(*elements);
			}
			elements++;
		}
	};
	
} Skeet;

CMenu*		SkeetSDK::Menu			= (CMenu*)0x434799AC;
CLua**		SkeetSDK::LuaInfo		= (CLua**)0x43475B00;
ThisIntFn	SkeetSDK::TabSwitch		= (ThisIntFn)0x433B75D3;
ThisIntFn	SkeetSDK::SetList		= (ThisIntFn)0x433B0844;
ThisFn		SkeetSDK::Callback		= (ThisFn)0x4334E09F;
ThisFn		SkeetSDK::ChildLayout	= (ThisFn)0x433AD23F;
ThisFn		SkeetSDK::KeyInit		= (ThisFn)0x4333CA03;
HashFn		SkeetSDK::Hash			= (HashFn)0x4334ADB0;
SetKeyFn	SkeetSDK::SetKey		= (SetKeyFn)0x4341859F;
SetCheckFn	SkeetSDK::SetCheck		= (SetCheckFn)0x433AD3C8;
HideUiFn	SkeetSDK::HideUi		= (HideUiFn)0x433E000B;
LoadLuaFn	SkeetSDK::LoadLua		= (LoadLuaFn)0x43419B27;
DecryptFn	SkeetSDK::Decrypt		= (DecryptFn)0x43418122;
F2PFn		SkeetSDK::DeleteUi		= (F2PFn)0x4338AB2D;
ThisFn		SkeetSDK::InitTab		= (ThisFn)0x4336D863;
CFn			SkeetSDK::InitState		= (CFn)0x433C05F9;
InsertFn	SkeetSDK::InsertElem	= (InsertFn)0x4336C436;
AddLabelFn	SkeetSDK::AddLabel		= (AddLabelFn)0x43388DDC;
AllocatorFn SkeetSDK::Allocator		= (AllocatorFn)0x43387448;
LConstFn	SkeetSDK::LabelCon		= (LConstFn)0x43328C61;
TBConstFn	SkeetSDK::TextboxCon	= (TBConstFn)0x4336A72D;
CConstFn	SkeetSDK::CheckboxCon	= (CConstFn)0x433ADF35;
SConstFn	SkeetSDK::SliderCon		= (SConstFn)0x433CF6B2;
HKConstFn	SkeetSDK::HotkeyCon		= (HKConstFn)0x4334DD58;
#endif // SKEET_H
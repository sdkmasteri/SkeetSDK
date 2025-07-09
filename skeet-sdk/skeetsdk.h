#ifndef SKEET_H
#define SKEET_H

// Its better to restrict inline in some heavy function (MSVC goes crazy and inline every function that being member of static class)
#if defined(__GNUC__) || defined(__GNUG__)
#define FORCECALL __attribute__((noinline))
#else
#define FORCECALL __declspec(noinline)
#endif

#define CHILD_SIZE			0xC8
#define LABEL_SIZE			0x60
#define BUTTON_SIZE			0x64
#define HOTKEY_SIZE			0x70
#define HOTKEYINFO_SIZE		0x28
#define SLIDER_SIZE			0x124
#define TEXTBOX_SIZE		0xE8
#define LISTBOX_SIZE		0xC0
#define CHECKBOX_SIZE		0x78
#define COMBOBOX_SIZE		0xA8
#define COLORPICKER_SIZE	0x138
#define MULTISELECT_SIZE	0x32C

#pragma pack(1)

typedef struct XorW;
typedef struct CTab;
typedef struct CMenu;
typedef struct Child;
typedef struct Label;
typedef struct Button;
typedef struct Hotkey;
typedef struct HotkeyInfo;
typedef struct Slider;
typedef struct Textbox;
typedef struct Listbox;
typedef struct Checkbox;
typedef struct Combobox;
typedef struct Multiselect;
typedef struct ColorPicker;

typedef union Element;


typedef void* (__cdecl* CFn)(void);	//__cdecl ptr return
typedef void(__thiscall* ThisFn)(void*);
typedef	void(__thiscall* T2PFn)(void*, void*); // __thiscall 2 pointers
typedef bool(__fastcall* LoadLuaFn)(wchar_t*, void*);
typedef int(__fastcall* SetKeyFn)(void*, unsigned int, unsigned int);
typedef void(__thiscall* ThisIntFn)(void*, int);
typedef unsigned int(__fastcall* HashFn)(const wchar_t*);
typedef void(__fastcall* SetModeFn)(void*, void*, int);
typedef void(__fastcall* SetCheckFn)(void*, int, int);
typedef void(__fastcall* HideUiFn)(void*, void*, bool);
typedef void(__fastcall* F2PFn)(void*, void*);	//__fascall 2 pointers
typedef int(__fastcall* DecryptFn)(XorW*, int, wchar_t*, int);
typedef void* (__fastcall* CryptFn)(wchar_t*, size_t, int);
typedef void(__thiscall* InsertFn)(void*, bool, void*);
typedef void* (__thiscall* AllocatorFn)(int);
typedef void* (__thiscall* AddLabelFn)(void*, bool, wchar_t*);
typedef void* (__thiscall* AddButtonFn)(void*, void*, wchar_t*, void*, void*);
typedef void* (__thiscall* TBConFn)(void*, void*); // Textbox constructor
typedef void* (__thiscall* CPConFn)(void*, void*, void*); // ColorPicker constructor
typedef void* (__thiscall* LConFn)(void*, void*, wchar_t*); // Label constructor
typedef void* (__thiscall* TCConFn)(void*, void*, wchar_t*, int*); // Tab and Checkbox constructor
typedef void* (__thiscall* SConFn)(void*, void*, wchar_t*, int, int, int*, bool, unsigned int, float); // Slider constructor
typedef void* (__thiscall* HKConFn)(void*, void*, void*, bool); // Hotkey constructor
typedef void* (__thiscall* BConFn)(void*, void*, wchar_t*, int, void*, void*, int); // Button constructor
typedef void* (__thiscall* CBConFn)(void*, void*, wchar_t*, int*, bool); // Combobox constructor
typedef void* (__thiscall* MConFn)(void*, void*, wchar_t*, int*, int, bool); // Multiselect constructor
typedef void* (__thiscall* LBConFn)(void*, void*, wchar_t*, int, int, int*, bool); // Listbox constructor
typedef void* (__thiscall* CHConFn)(void*, void*, wchar_t*, int, int, bool); // Child constructor

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

typedef struct Vec2f_t
{
	float x;
	float y;
	Vec2f_t(float x, float y) : x(x), y(y) {};
	Vec2f_t operator-(float min)
	{
		return Vec2f_t(this->x - min, this->y - min);
	};
	void clamp(float min, float max = 3.402823466e+38f)
	{
		if (this->x > max) this->x = max;
		if (this->x < min) this->x = min;
		if (this->y > max) this->y = max;
		if (this->y < min) this->y = min;
	};
};

typedef struct Vec2
{
	int x;
	int y;
	Vec2(int x, int y) : x(x), y(y) {};
	Vec2 operator+(Vec2 vec)
	{
		return Vec2(this->x + vec.x, this->y + vec.y);
	};
	Vec2 operator+(int sum)
	{
		return Vec2(this->x + sum, this->y + sum);
	};
	Vec2 operator*(float mul)
	{
		return Vec2(this->x * mul, this->y * mul);
	};
	Vec2 operator*(Vec2f_t mul)
	{
		return Vec2((int)((float)this->x * mul.x), (int)((float)this->y * mul.y));
	};
	Vec2& operator+=(const Vec2& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}
	int* array()
	{
		return reinterpret_cast<int*>(this);
	};
};

typedef struct Vec4_8t
{
	unsigned char x;
	unsigned char y;
	unsigned char z;
	unsigned char w;
	int pack()
	{
		return (this->x | this->y << 8 | this->z << 16 | this->w << 24);
	};
};

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

template <typename T>
struct BoxVars
{
	T*		NameChunk;
	void*	NameChunkEnd;
	void*	CpacityEnd;
	char	pad1[0x4];
	int		Index;
};

template <typename T>
struct Header
{
	void*	Vtable;		// honestly I dont even know whats inside
	char	pad1[0x8];
	int		Index;		// 0xC	in CTab - tab index, in Childs - first element index, in Elements - element index
	T*		Parent;		// 0x10
	Flags	Flags;		// 0x14
	UiType	Type;		// 0x19
	char	pad2[0x2];
	int		Font;
};

// Slider is 0x124 bytes long
struct Slider
{
	Header<Child>		Header;
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
	Header<Child>		Header;
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

// Multiselect is 0x32C bytes long
struct Multiselect
{
	Header<Child>		Header;
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
	void*				StringValueChunkEnd;// 0x78
	char				pad5[0x4];
	BoxVars<char>*		VarsChunk;			// 0x80
	void*				VarsChunkEnd;		// 0x84
	char				pad6[0x8];
	BoxVars<char>		Vars[];		// 0x90
};

typedef struct
{
	wchar_t* data;
	int	len;
} wchar_str;

typedef struct
{
	int			Index;
	wchar_t*	NameChunk;
	void*		NameChunkEnd;
	void*		CapacityEnd;
	char		pad2[0x4];
} wchar_set;

typedef struct
{
	Header<Hotkey>		Header;
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
	Header<Child>		Header;
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

// Button is 0x64 bytes long
struct Button
{
	Header<Child>		Header;
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
	char				pad3[0xC];
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

// ColorPicker is 0x138 bytes long
struct ColorPicker
{
	Header<Child>		Header;
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
};

// Combobox is 0xA8 bytes long
struct Combobox
{
	Header<Child>		Header;
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
	BoxVars<wchar_t>*	VarsChunk;			// 0x7C
	void*				VarsChunkEnd;		// 0x80
	char				pad4[0x24];
};

// Label 0x60 bytes long
struct Label
{
	Header<Child>		Header;
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
	char		pad1[0x8];
	int			SelectedItem;	// 0x88
	char		pad2[0x4];
	wchar_set*	ItemsChunk;		// 0x90
	void*		ItemsChunkEnd;	// 0x94
	char		pad3[0x8];
} ListboxInfo;

typedef struct
{
	short FindedIndex;
	short Indexies[];
} SSpec;

// Listbox is 0xC0 bytes long
struct Listbox
{
	Header<Child>		Header;
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
	char				pad5[0xC];
	int					ItemsCount;			// 0x74
	char				pad6[0x4];
	int					SearchPresent;		// 0x7C
	ListboxInfo			Info;				// 0x80
	wchar_t*			SearchChunk;		// 0xA0
	void*				SearchChunkEnd;		// 0xA4
	void*				SearchCapacityEnd;	// 0xA8
	char				pad7[0x4];
	SSpec*				SSpecChunk;			// 0xB0
	void*				SSpecChunkEnd;		// 0xB4
	void*				SSpecCapacityEnd;	// 0xB8
	char				pad8[0x4];
};

// Textbox is 0xE8 bytes long
struct Textbox
{
	Header<Child>		Header;
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
	char	pad1[0x38];
	XorW*	crypted;		// 0x38
	char	pad2[0x20];
	void*	value;		// 0x5C
} Inspector;

typedef struct
{
	char	pad1[0x8];
	bool	Modifiable;	// 0xB0
	bool	Movable;	// 0xB1
	char	pad2[0x2];
	VecCol	NameCol;	// 0xB4
	VecCol	BorderCol;	// 0xB8
	VecCol	ShadowCol;	// 0xBC
	VecCol	BackCol;	// 0xC0
	int		DrawName;	// 0xC4
} CWidg;

typedef struct
{
	void* ptr;
	int i1;
	int i2;
	XorW* name;
} Unkn;

// Child is 0xC8 bytes long
struct Child
{
	Header<CTab>		Header;
	Vec2				Pos;				// 0x20
	Vec2				Size;				// 0x28
	Vec2				DefSize;			// 0x30
	XorW*				CryptedName;		// 0x38
	Unkn*				Unknown;			// 0x3C
	Call*				Call;				// 0x40
	void*				CallChunkEnd;		// 0x44
	char				pad1[0x8];
	VecCol				Color;				// 0x50
	char				pad2[0x14];
	Vec2				Padding;			// 0x68
	Vec4_8t				PosSize;			// 0x70 block = minimum size child can be resized/moved by, x = blocks moved by X, y = blocks sized by X, z = blocks moved by Y, w = blocks sized by Y
	Vec2				MouseLastPos;		// 0x74
	ChildStatus			Status;				// 0x7C
	Element**			ElementsChunk;		// 0x80
	Element**			ElementsChunkEnd;	// 0x84
	void*				ElementsCapacityEnd;// 0x88
	char				pad3[0x4];
	CWidg*				PWidgets;			// 0x90
	char				pad4[0x4];
	Vec2				CurSize;			// 0x98
	Vec2				MinimizedCapacity;	// 0xA0
	CWidg				Widgets;			// 0xA8
};

union Element
{
	Header<Child>		header;
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
	Child				child;
	Inspector			inspector;
};

typedef struct
{
	char			pad4[0x8];
	int				TextureId;		// 0x80
	int				TextureOffset;	// 0x84
	char			pad5[0x4];	
	Vec2			Size;			// 0x8C
} TabIcon;

struct CTab
{
	Header<void>		Header;
	Vec2				Pos;			// 0x20
	Vec2				Size;			// 0x28
	Vec2				DefSize;		// 0x30
	XorW*				CryptedName;	// 0x38
	char				pad1[0x14];
	VecCol				Color;			// 0x50
	char				pad2[0xC];
	CMenu*				Parent;			// 0x60
	char				pad3[0xC];
	Child**				ChildsChunk;	// 0x70
	Child**				ChildsChunkEnd;	// 0x74
	TabIcon				Icon;			// 0x78
	int					Padding;		// 0x94
	void*				Chunk;			// 0x98
	void*				ChunkEnd;		// 0x9C
	Element*			CEs[0x20];		// 0xA0	childs and some elems lets say it will be 0x20 size for our allocation purposes
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
	Tabs*		TabsChunk;			// 0x54
	CTab**		TabsChunkEnd;		// 0x58
	void*		TabsCapacityEnd;	// 0x5C
	char		pad3[0x4];
	Tab			CurrentTab;			// 0x64
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
	static AllocatorFn	Allocator;
	static ThisIntFn	TabSwitch;
	static ThisIntFn	SetList;
	static ThisFn		TabLyaout;
	static ThisFn		ChildLayout;
	static ThisFn		Callback;
	static ThisFn		KeyInit;
	static HashFn		Hash;
	static SetKeyFn		SetKey;
	static SetCheckFn	SetCheck;
	static HideUiFn		HideUi;
	static LoadLuaFn	LoadLua;
	static DecryptFn	Decrypt;
	static CryptFn		Crypt;
	static F2PFn		DeleteUi;
	static ThisFn		InitTab;
	static CFn			InitState;
	static CLua**		LuaInfo;
	static T2PFn		InsertTab;
	static T2PFn		InsertChildr;
	static InsertFn		InsertElem;
	static AddLabelFn	AddLabel;
	static AddButtonFn	AddButton;
	static LConFn		LabelCon;
	static TBConFn		TextboxCon;
	static TCConFn		CheckboxCon;
	static SConFn		SliderCon;
	static HKConFn		HotkeyCon;
	static BConFn		ButtonCon;
	static CPConFn		CPickerCon;
	static CBConFn		ComboboxCon;
	static MConFn		MultiCon;
	static LBConFn		ListboxCon;
	static CHConFn		ChildCon;
	static TCConFn		TabCon;
public:
	static CMenu*		Menu;

	static void WaitForMenu()
	{
		while (!Menu->Size.x) Sleep(50);
	};

	static void WaitForTabs()
	{
		while (Menu->TabsChunk == NULL || Menu->TabsChunk->Lua == NULL) Sleep(100);
	};

	static void ResetLayout()
	{
		Button* b = (Button*)GetByName(Menu->TabsChunk->Misc->ChildsChunk[2], L"Reset menu layout");
		b->Call->function(Menu, b);
	};

	static void InitConfig()
	{
		InitTab(Menu->TabsChunk->Config);
	};

	static void	SetTab(Tab tab)
	{
		TabSwitch(Menu, tab);
	};

	static Tab GetActiveTab()
	{
		return Menu->CurrentTab;
	}

	static CTab* GetActiveCTab()
	{
		return ((CTab**)Menu->TabsChunk)[Menu->CurrentTab];
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
		Header<Child>* head = &elemen->header;
		head->Flags.AllowMouseInput = val;
		head->Flags.Editable = val;
	};

	static void* TieValue(Element* element, void* ptr)
	{
		void* oldptr = element->inspector.value;
		element->inspector.value = ptr;
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

	static void SetColorRGBA(ColorPicker* picker, VecCol Color)
	{
		picker->Value[0] = Color;
		Callback(&picker);
	};

	static void SetColorHSV(ColorPicker* picker, HSV Color)
	{
		picker->HSV = Color;
		Callback(&picker);
	};

	static void SetSlider(Slider* slider, int value)
	{
		slider->Value[0] = value;
		Callback(&slider);
	};

	static void SetCombobox(Combobox* combobox, int value)
	{
		combobox->SelectedItem = value;
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

	static int ExtractKey(Hotkey* hotkey)
	{
		return hotkey->Info->Key >> 2;
	};

	static int HotkeyState(Hotkey hotkey)
	{
		return (hotkey.Info->Key >> 1) & 1;
	};

	static void LoadCfg(int index = -1)
	{
		if (index >= 0)
			SetListbox(&Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[0]->listbox, index);
		Callback(Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[3]);
	};

	static int LuaCount()
	{
		int diff = (int)Menu->TabsChunk->Config->ChunkEnd - (int)Menu->TabsChunk->Config->Chunk;

		return diff >> 5;
	};

	static wchar_t* LuaName(int index)
	{
		if (index >= LuaCount()) return NULL;
		return Menu->TabsChunk->Config->ChildsChunk[1]->ElementsChunk[3]->listbox.PInfo->ItemsChunk[index].NameChunk;
	};

	static FORCECALL const wchar_t* CurrentConfig()
	{
		unsigned int hashed = *(unsigned int*)0x4347C9F8;
		if (!hashed) return L"Default";
		size_t count = ((unsigned int)Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[0]->listbox.PInfo->ItemsChunkEnd - (unsigned int)Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[0]->listbox.PInfo->ItemsChunk) / sizeof(wchar_set);
		for (size_t i = 0; i < count; i++)
		{
			if (Hash(Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[0]->listbox.PInfo->ItemsChunk[i].NameChunk) == hashed)
				return Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[0]->listbox.PInfo->ItemsChunk[i].NameChunk;
		}
	};

	static FORCECALL int CurrentConfigIndex()
	{
		unsigned int hashed = *(unsigned int*)0x4347C9F8;
		if (!hashed) return -1;
		size_t count = ((unsigned int)Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[0]->listbox.PInfo->ItemsChunkEnd - (unsigned int)Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[0]->listbox.PInfo->ItemsChunk) / sizeof(wchar_set);
		for (size_t i = 0; i < count; i++)
		{
			if (Hash(Menu->TabsChunk->Config->ChildsChunk[0]->ElementsChunk[0]->listbox.PInfo->ItemsChunk[i].NameChunk) == hashed)
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
		SetCheckbox(&Menu->TabsChunk->Config->ChildsChunk[1]->ElementsChunk[1]->checkbox, value);
	};

	static XorW* CryptName(wchar_t* name)
	{
		return (XorW*)Crypt(name, (wcslen(name) + 1) * sizeof(wchar_t), 2);
	};


	static XorW* RenameElement(Element* element, wchar_t* name)
	{
		XorW* old = element->inspector.crypted;
		element->inspector.crypted = CryptName(name);
		return old;
	};

	static wchar_t* GetName(Element* element)
	{
		wchar_t name[128];
		Decrypt(element->slider.CryptedName, 2, name, 128);
		return name;
	};

	static FORCECALL Element* GetByName(Child* child, const wchar_t* name)
	{
		Element** elements = child->ElementsChunk;
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
		return ((CTab**)Menu->TabsChunk)[tab];
	};

	static FORCECALL Child* GetChild(Tab tab, int index)
	{
		CTab* tabPtr = GetTab(tab);
		if (index < 0 || index >= ChildsCount(tabPtr)) return NULL;
		return tabPtr->ChildsChunk[index];
	};

	static unsigned int ChildsCount(CTab* tab)
	{
		return ((unsigned int)tab->ChildsChunkEnd - (unsigned int)tab->ChildsChunk) / sizeof(void*);
	};

	static unsigned int ElementsCount(Child* child)
	{
		return ((unsigned int)child->ElementsChunkEnd - (unsigned int)child->ElementsChunk) / sizeof(void*);
	};

	static void* LuaState()
	{
		return InitState();
	}
	
	static FORCECALL void InsertElement(Child* child, void* element)
	{
		InsertElem(child, 0, element);
		ChildLayout(child);
	};

	static FORCECALL Label* CreateLabel(Child* child, wchar_t* name)
	{
		Label* ptr = (Label*)AddLabel(child, 0, name);
		ChildLayout(child);
		return ptr;
	};

	static FORCECALL Textbox* CreateTextbox(Child* child)
	{
		Textbox* ptr = (Textbox*)Allocator(TEXTBOX_SIZE);
		TextboxCon(ptr, child);
		InsertElement(child, ptr);
		return ptr;
	};
	
	static FORCECALL Checkbox* CreateCheckbox(Child* child, wchar_t* name, int* value)
	{
		Checkbox* ptr = (Checkbox*)Allocator(CHECKBOX_SIZE);
		CheckboxCon(ptr, child, name, value);
		InsertElement(child, ptr);
		return ptr;
	};

	static FORCECALL Slider* CreateSlider(Child* child, wchar_t* name, int min, int max, int* value, bool tooltip = true, wchar_t* tip = NULL, float step = 1.f)
	{
		Slider* ptr = (Slider*)Allocator(SLIDER_SIZE);
		unsigned int tipch = 0;
		if (tip != NULL)
			tipch = tip[0] | tip[1] << 16;
		SliderCon(ptr, child, name, min, max, value, tooltip, tipch, step);
		InsertElement(child, ptr);
		return ptr;
	};

	static FORCECALL Hotkey* CreateHotkey(Child* child, wchar_t* name, bool sameline = false, int vkey = 0x00, HotkeyMode mode = OnHotkey)
	{
		if (!sameline)
			CreateLabel(child, name);
		HotkeyInfo* info = (HotkeyInfo*)Allocator(HOTKEYINFO_SIZE);
		KeyInit(info);
		Hotkey* ptr = (Hotkey*)Allocator(HOTKEY_SIZE);
		HotkeyCon(ptr, child, info, true);
		SetHotkey((Hotkey*)ptr, vkey, mode);
		InsertElement(child, ptr);
		return ptr;
	};

	// ecx = first parameter that function recive, while second one is alway this pointer
	static FORCECALL Button* CreateButton(Child* child, wchar_t* name, F2PFn function, void* ecx = Menu)
	{
		Button* ptr = (Button*)AddButton(child, NULL, name, ecx, function);
		ChildLayout(child);
		return ptr;
	};

	static FORCECALL ColorPicker* CreateColorPicker(Child* child, VecCol* value, bool sameline = true, wchar_t* name = NULL)
	{
		if (!sameline && name != NULL)
			CreateLabel(child, name);
		ColorPicker* ptr = (ColorPicker*)Allocator(COLORPICKER_SIZE);
		CPickerCon(ptr, child, value);
		InsertElement(child, ptr);
		return ptr;
	};

	static FORCECALL Combobox* CreateCombobox(Child* child, wchar_t* name, int* value, wchar_t** arr, size_t arrsize, bool sameline = false)
	{
		Combobox* ptr = (Combobox*)Allocator(COMBOBOX_SIZE);
		ComboboxCon(ptr, child, name, value, sameline);
		BoxVars<wchar_t>* varlist = (BoxVars<wchar_t>*)Allocator(sizeof(BoxVars<wchar_t>) * arrsize);
		for (size_t i = 0; i < arrsize; i++)
		{
			size_t bsize = sizeof(wchar_t) * wcslen(arr[i]);
			varlist[i].NameChunk = (wchar_t*)Allocator(bsize);
			memcpy(varlist[i].NameChunk, arr[i], bsize);
			varlist[i].NameChunkEnd = (void*)((int)varlist[i].NameChunk + bsize + sizeof(wchar_t));
			varlist[i].CpacityEnd = varlist[i].NameChunkEnd;
			varlist[i].Index = i;
		}
		ptr->VarsChunk = varlist;
		ptr->VarsChunkEnd = (void*)((int)varlist + arrsize * sizeof(BoxVars<wchar_t>));
		InsertElement(child, ptr);
		return ptr;
	};

	static FORCECALL Multiselect* CreateMultiselect(Child* child, wchar_t* name, int* value, char** arr, size_t arrsize, bool sameline = false)
	{
		Multiselect* ptr = (Multiselect*)Allocator(MULTISELECT_SIZE);
		MultiCon(ptr, child, name, value, 0, sameline);
		auto varlist = ptr->Vars;
		for (size_t i = 0; i < arrsize; i++)
		{
			size_t bsize = strlen(arr[i]);
			varlist[i].NameChunk = (char*)Allocator(bsize);
			memcpy(varlist[i].NameChunk, arr[i], bsize);
			varlist[i].NameChunkEnd = (void*)((int)varlist[i].NameChunk + bsize);
			varlist[i].CpacityEnd = varlist[i].NameChunkEnd;
			varlist[i].Index = 1 << i;
		}
		ptr->VarsChunk = varlist;
		ptr->VarsChunkEnd = (void*)((int)varlist + arrsize * sizeof(BoxVars<char>));
		InsertElement(child, ptr);
		return ptr;
	};

	static FORCECALL Listbox* CreateLisbox(Child* child, wchar_t* name, int* value, wchar_t** arr, size_t arrsize, bool searchbox = true)
	{
		Listbox* ptr = (Listbox*)Allocator(LISTBOX_SIZE);
		ListboxCon(ptr, child, name, 158, 300, value, searchbox);
		
		wchar_set* set = (wchar_set*)Allocator(sizeof(wchar_set) * arrsize);
		SSpec* spec = (SSpec*)Allocator(sizeof(short) * (arrsize + 1));
		for (size_t i = 0; i < arrsize; i++)
		{
		    size_t bsize = (wcslen(arr[i]) + 1) * sizeof(wchar_t);
		    set[i].Index = i;
		    set[i].NameChunk = (wchar_t*)Allocator(bsize);
		    memcpy(set[i].NameChunk, arr[i], bsize);
		    set[i].NameChunkEnd = (void*)((int)set[i].NameChunk + bsize);
		    set[i].CapacityEnd = set[i].NameChunkEnd;
		    spec->Indexies[i] = i+1;
		}
		spec->FindedIndex = 0;
		ptr->Info.ItemsChunk = set;
		ptr->Info.ItemsChunkEnd = (void*)((int)set + sizeof(wchar_set) * arrsize);
		ptr->ItemsCount = arrsize;
		ptr->SSpecChunk = spec;
		ptr->SSpecChunkEnd = (void*)((int)spec + sizeof(short) * (arrsize + 1));
		ptr->SSpecCapacityEnd = ptr->SSpecChunkEnd;
		InsertElement(child, ptr);
		return ptr;
	};

	static FORCECALL void InsertChild(CTab* tab, void* child)
	{
		InsertChildr(tab, child);
		TabLyaout(tab);
	};

	static FORCECALL Child* CreateChild(CTab* tab, wchar_t* name, Vec4_8t possize, bool modify)
	{
		Child* ptr = (Child*)Allocator(CHILD_SIZE);
		ChildCon(ptr, tab, name, possize.pack(), 0, modify);
		InsertChild(tab, ptr);
		return ptr;
	};

	static FORCECALL CTab* CreateTab(wchar_t* name, Vec2 pos)
	{
		CTab* ptr = (CTab*)Allocator(sizeof(CTab));
		TabCon(ptr, Menu, name, pos.array());
		InsertTab(Menu, ptr);
		return ptr;
	};

	template <typename T>
	static T* GetElement(Child* child, int index)
	{
		return (T*)child->ElementsChunk[index];
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

	template <UiType T = UiNone>
	static void ForEach(Child* child, void(*func)(Element*))
	{
		size_t count = ElementsCount(child);
		for (size_t i = 0; i < count; i++)
		{
			Element* element = child->ElementsChunk[i];
			if (T == UiNone || element->header.Type == T)
			{
				func(element);
			}
		}
	};
	
} Skeet;

CMenu*		SkeetSDK::Menu			= (CMenu*)0x434799AC;
CLua**		SkeetSDK::LuaInfo		= (CLua**)0x43475B00;
ThisIntFn	SkeetSDK::TabSwitch		= (ThisIntFn)0x433B75D3;
ThisIntFn	SkeetSDK::SetList		= (ThisIntFn)0x433B0844;
ThisFn		SkeetSDK::Callback		= (ThisFn)0x4334E09F;
ThisFn		SkeetSDK::ChildLayout	= (ThisFn)0x433AD23F;
ThisFn		SkeetSDK::TabLyaout		= (ThisFn)0x43384477;
ThisFn		SkeetSDK::KeyInit		= (ThisFn)0x4333CA03;
HashFn		SkeetSDK::Hash			= (HashFn)0x4334ADB0;
SetKeyFn	SkeetSDK::SetKey		= (SetKeyFn)0x4341859F;
SetCheckFn	SkeetSDK::SetCheck		= (SetCheckFn)0x433AD3C8;
HideUiFn	SkeetSDK::HideUi		= (HideUiFn)0x433E000B;
LoadLuaFn	SkeetSDK::LoadLua		= (LoadLuaFn)0x43419B27;
DecryptFn	SkeetSDK::Decrypt		= (DecryptFn)0x43418122;
CryptFn		SkeetSDK::Crypt			= (CryptFn)0x4338228D;
F2PFn		SkeetSDK::DeleteUi		= (F2PFn)0x4338AB2D;
ThisFn		SkeetSDK::InitTab		= (ThisFn)0x4336D863;
CFn			SkeetSDK::InitState		= (CFn)0x433C05F9;
T2PFn		SkeetSDK::InsertTab		= (T2PFn)0x43342275;
T2PFn		SkeetSDK::InsertChildr	= (T2PFn)0x4347DE9B;
InsertFn	SkeetSDK::InsertElem	= (InsertFn)0x4336C436;
AllocatorFn SkeetSDK::Allocator		= (AllocatorFn)0x43387448;
AddLabelFn	SkeetSDK::AddLabel		= (AddLabelFn)0x43388DDC;
AddButtonFn SkeetSDK::AddButton		= (AddButtonFn)0x4339E81F;
LConFn		SkeetSDK::LabelCon		= (LConFn)0x43328C61;
TBConFn		SkeetSDK::TextboxCon	= (TBConFn)0x4336A72D;
TCConFn		SkeetSDK::CheckboxCon	= (TCConFn)0x433ADF35;
SConFn		SkeetSDK::SliderCon		= (SConFn)0x433CF6B2;
HKConFn		SkeetSDK::HotkeyCon		= (HKConFn)0x4334DD58;
BConFn		SkeetSDK::ButtonCon		= (BConFn)0x433665D5;
CPConFn		SkeetSDK::CPickerCon	= (CPConFn)0x43406A63;
CBConFn		SkeetSDK::ComboboxCon	= (CBConFn)0x43399927;
MConFn		SkeetSDK::MultiCon		= (MConFn)0x433230AD;
LBConFn		SkeetSDK::ListboxCon	= (LBConFn)0x433EDA39;
CHConFn		SkeetSDK::ChildCon		= (CHConFn)0x4348210C;
TCConFn		SkeetSDK::TabCon		= (TCConFn)0x4348E41D;
#endif // SKEET_H
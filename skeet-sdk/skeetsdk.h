#ifndef SKEET_H
#define SKEET_H
#include <Windows.h>
#include <psapi.h>

#if defined(__GNUC__) || defined(__GNUG__)
#define FORCECALL __attribute__((noinline))
#else
#define FORCECALL __declspec(noinline)
#endif

// Only use if you know what you are doing, incorrect usage of raw functions can cause undefined behavior
#ifdef _SDK_PUBLIC_UNSAFE_MEMBERS
#define MEMBERS_PRIVATE public:
#define MEMBERS_PUBLIC
#else
#define MEMBERS_PRIVATE private:
#define MEMBERS_PUBLIC	public:
#endif

#ifdef SDK_RENDERER_IMP
#define TEXT_FLAG_DPI_SCALED		0x0
#define TEXT_FLAG_BOLD				0x1
#define TEXT_FLAG_LARGE				0x2
#define TEXT_FLAG_SMALL				0x4
#define TEXT_FLAG_CENTRED			0x10
#define TEXT_FLAG_RIGHT_ALIGNED		0x80
#define TEXT_FLAG_DEFAULT			0x100

#define TEXTURE_FLAG_AUTO			0x0
#define TEXTURE_FLAG_FILLED			0x1
#define TEXTURE_FLAG_REPEAT			0x2
#endif

namespace SkeetSDK {
// functions signatures
	// Pulbic signatures
	typedef void* (__cdecl* CFn)(void);	//__cdecl ptr return
	typedef void(__thiscall* ThisFn)(void*);
	typedef	void(__thiscall* T2PFn)(void*, void*); // __thiscall 2 pointers
	typedef void(__fastcall* F2PFn)(void*, void*);	//__fascall 2 pointers
	typedef void(__thiscall* ThisIntFn)(void*, int);
	// Memory signatures
	typedef void* (__thiscall* AllocatorFn)(int);
	// Misc signatures
	typedef bool(__fastcall* LoadLuaFn)(wchar_t*, void*);
	typedef unsigned int(__fastcall* HashFn)(const wchar_t*);
	typedef void* (__fastcall* CryptFn)(wchar_t*, size_t, int);
	typedef int(__fastcall* DecryptFn)(void*, int, wchar_t*, int);
	typedef bool(__fastcall* GetConfigDataFn)(const char*, void*);
	typedef void(__fastcall* LoadConfigFn)(void*, void*, size_t);
	// UI signatures
	typedef int(__fastcall* SetKeyFn)(void*, unsigned int, unsigned int);
	typedef void(__fastcall* SetModeFn)(void*, void*, int);
	typedef void(__fastcall* SetCheckFn)(void*, int, int);
	typedef void(__fastcall* HideUiFn)(void*, void*, bool);
	typedef void(__thiscall* InsertFn)(void*, bool, void*);
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
	typedef size_t(__thiscall* GetTBoxTextFn)(void*, wchar_t*);
	// Renderer signatures
	typedef void(__fastcall* RenderFn)(void*, void*);
	typedef void(__cdecl* RenderEventListenerFn)(void);
	typedef void* (__fastcall* ReadFileFn)(void*, const char*);
	typedef bool(__fastcall* LoadTextureFn)(int, const unsigned char*, int, int*, int*, void*);
	typedef int(__fastcall* LoadSvgFormFileFn)(const char*, int, int, int);
	typedef void(__thiscall* RenderIndicatorFn)(int*, void*, const char*, int, unsigned int, int, float);
	typedef bool(__fastcall* WorldToScreenFn)(float*, int*, int*);
	typedef void(__thiscall* RenderBlurFn)(void*, int, int, int, int);
	// Client signatures
	typedef void(__thiscall* LogFn)(char*);
	typedef void(__cdecl* LogErrorFn)(const char*, ...);
	typedef void(__cdecl* LogColorFn)(void*, int*, char*, ...);
	typedef void(__thiscall* ScreenLogFn)(const char*, int);
	typedef void(__fastcall* SetClanTagFn)(const char*, const char*);
// enums
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

	enum FadeType
	{
		FadeNone,
		FadeOut,
		FadeIn
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
#ifdef SDK_RENDERER_IMP
	enum TextureType
	{
		TEXTURE_RGBA = -1,
		TEXTURE_SVG,
		TEXTURE_PNG,
		TEXTURE_JPG
	};

	enum RenderEventType
	{
		REVENT_RENDER,
		REVENT_MENU,
		REVENT_FINAL
	};
#endif

//vectors
	struct Vec2f_t
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

	struct Vec3f_t
	{
		float x;
		float y;
		float z;
		Vec3f_t() = default;
		float* array()
		{
			return reinterpret_cast<float*>(this);
		};
	};

	struct Vec2
	{
		int x;
		int y;
		Vec2() : x(0), y(0) {};
		Vec2(int x, int y) : x(x), y(y) {};
		Vec2 operator+(Vec2 vec)
		{
			return Vec2(this->x + vec.x, this->y + vec.y);
		};
		Vec2 operator+(int sum)
		{
			return Vec2(this->x + sum, this->y + sum);
		};
		Vec2 operator-(Vec2 vec)
		{
			return Vec2(this->x - vec.x, this->y - vec.y);
		};
		Vec2 operator-(int sub)
		{
			return Vec2(this->x - sub, this->y - sub);
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

	class VecCol
	{
	public:
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
		VecCol(unsigned int hex)
		{
			this->r = (unsigned char)hex;
			this->g = hex >> 8;
			this->b = hex >> 16;
			this->a = hex >> 24;
		}
		VecCol(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {};
		int pack()
		{
			return (this->r | this->g << 8 | this->b << 16 | this->a << 24);
		};
		void invert()
		{
			this->r = 255 - this->r;
			this->g = 255 - this->g;
			this->b = 255 - this->b;
			this->a = 255 - this->a;
		};
		VecCol negate()
		{
			return VecCol(255 - this->r, 255 - this->g, 255 - this->b, this->a);
		};
	};

	struct Vec4_8t
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

	template<typename T>
	class sVec
	{
		T* buffer;
		T* endbuff;
		size_t length;
	public:
		sVec(size_t size) : length(0)
		{
			this->buffer = (T*)malloc(sizeof(T) * size);
			this->endbuff = this->buffer + size;
		}

		~sVec()
		{
			free(this->buffer);
		};

		void insert(T elem, size_t index)
		{
			size_t csize = size();
			T* newbuff = (T*)malloc(sizeof(T) * csize + 1);
			if (!newbuff) return;
			memcpy(newbuff, this->buffer, index * sizeof(T));
			memcpy(newbuff + index + 1, this->buffer + index, (csize - index) * sizeof(T));
			newbuff[index] = elem;
			free(this->buffer);
			this->buffer = newbuff;
			this->endbuff = this->buffer + ++csize;
			this->length++;
		};

		void push_back(T elem)
		{
			if (this->length >= size())
				resize(size() * 2);
			this->buffer[this->length++] = elem;
		};

		T pop(size_t index = 0)
		{
			if (this->length == 0) return T{ 0 };
			if (index >= this->length) return T{ 0 };
			T elem = this->buffer[index];
			remove(index);
			return elem;
		};

		T pop_back()
		{
			return pop(this->length - 1);
		};

		void fill(T val, size_t size)
		{
			if (size > this->size())
				resize(size);
			memset(this->buffer, val, size * sizeof(T));
		};

		void clear()
		{
			memset(this->buffer, 0, bsize());
			this->length = 0;
		};

		void remove(size_t index)
		{
			memcpy(buffer + index, buffer + index + 1, (this->length-- - index) * sizeof(T));
		};

		void removef(size_t index)
		{
			free(buffer[index]);
			memcpy(buffer + index, buffer + index + 1, (this->length-- - index) * sizeof(T));
		};

		void resize(size_t size)
		{
			T* newbuff = (T*)realloc(this->buffer, size);
			if (!newbuff) return;
			if (this->length >= size)
				this->length = size - 1;
			this->buffer = newbuff;
			this->endbuff = this->buffer + size;
		};

		size_t len()
		{
			return this->length;
		};

		size_t bsize()
		{
			return (uintptr_t)this->endbuff - (uintptr_t)this->buffer;
		};

		size_t size()
		{
			return bsize() / sizeof(T);
		};

		size_t cappacity()
		{
			return (uintptr_t)this->endbuff - (uintptr_t)(this->buffer + this->length);
		};

		T& last()
		{
			return this->buffer[this->length - 1];
		};

		T* begin()
		{
			return this->buffer;
		};

		T* end()
		{
			return this->endbuff;
		};

		T& operator[](size_t i)
		{
			return this->buffer[i];
		};

		void operator<<(T elem)
		{
			push_back(elem);
		};

		void operator<<=(T val)
		{
			last() = val;
		};

		void operator>>(T& out)
		{
			out = pop_back();
		};

		void operator >>=(T& out)
		{
			out = last();
		};

	};

//structs class
#pragma pack(push, 1)
	typedef struct Child* PChild, ** PChilds;
	typedef struct CTab* PCTab, ** PCTabs;
	typedef struct Element* PElement, ** PElements;
	typedef struct CMenu* PCMenu;
	typedef struct Hotkey* PHotkey;
	struct MouseInfo
	{
		MouseStatus Status;
		Vec2		Pos;
		Vec2		LastMenuPos;
	};

	struct Flags
	{
		bool Editable;
		bool Visible;
		bool Hovered;
		bool AllowMouseInput;
		bool SameLine;
	} ;

	typedef struct XorW
	{
		unsigned short	key;
		unsigned short	bsize;
		wchar_t			data[];
	} *PXorW;

	typedef struct Call
	{
		void*	ecx;
		F2PFn	function;	// function(ecx, elementptr)
	} *PCall;

	template <typename T>
	struct BoxVars
	{
		T*		NameChunk;
		T*		NameChunkEnd;
		void*	CpacityEnd;
		char	pad1[0x4];
		int		Index;
	};

	template <typename T>
	struct Header
	{
		char	pad1[0x8];
		int		Index;		// 0xC	in CTab - tab index, in Childs - first element index, in Elements - element index
		T*		Parent;		// 0x10
		Flags	Flags;		// 0x14
		UiType	Type;		// 0x19
		char	pad2[0x2];
		int		Font;		// 0x1C
	};

	// placeholed
	class IElement
	{
		virtual void fn0() = 0;
	};

	// Slider is 0x124 bytes long
	typedef struct Slider : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;			// 0x20
		Vec2				Size;			// 0x28
		char				pad1[0x8];
		PXorW				CryptedName;	// 0x38
		char				pad2[0x4];
		PCall				CallChunk;		// 0x40
		PCall				CallChunkEnd;	// 0x44
		char				pad3[0x8];
		VecCol				Color;			// 0x50
		int					LeftPaddign;	// 0x54
		char				pad4[0x4];
		int*				Value;			// 0x5C
		Vec2				DefSize;		// 0x60
		bool				Active;			// 0x68
		bool				Tooltip;		// 0x69
		char				pad5[0x26];
		int					Max;			// 0x90
		int					Min;			// 0x94
		float				Step;			// 0x98
		int					MaxLen;			// 0x9C
		char				pad6[0x84];
	} *PSlider;

	// Checkbox is 0x78 bytes long
	typedef struct Checkbox : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;			// 0x20
		Vec2				ActivateSize;	// 0x28
		char				pad1[0x8];
		PXorW				CryptedName;	// 0x38
		char				pad2[0x4];
		PCall				CallChunk;		// 0x40
		PCall				CallChunkEnd;	// 0x44
		char				pad3[0x8];
		VecCol				Color;			// 0x50
		int					LeftPaddign;	// 0x54
		char				pad4[0x4];
		int*				Value;			// 0x5C
		Vec2				Size;			// 0x60
		int					TextPadding;	// 0x68
		char				pad5[0xC];
	} *PCheckbox;

	// Multiselect is 0x32C bytes long
	typedef struct Multiselect : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;				// 0x20
		Vec2				Size;				// 0x28
		Vec2				OuterPadding;		// 0x30
		PXorW				CryptedName;		// 0x38
		char				pad1[0x4];
		PCall				CallChunk;			// 0x40
		PCall				CallChunkEnd;		// 0x44
		char				pad2[0x8];
		VecCol				Color;				// 0x50
		int					LeftPaddign;		// 0x54
		char				pad3[0x4];
		int*				Value;				// 0x5C
		int					heigth;				// 0x60
		char				pad4[0x4];
		bool				Popup;				// 0x68
		bool				Clicked;			// 0x69
		bool				NotNull;			// 0x6A
		char				pad5;
		int					HoveredItem;		// 0x6C
		char*				StringValue;		// 0x70
		char*				StringValueEnd;		// 0x74
		void*				StringValueChunkEnd;// 0x78
		char				pad6[0x4];
		BoxVars<char>*		VarsChunk;			// 0x80
		BoxVars<char>*		VarsChunkEnd;		// 0x84
		char				pad7[0x8];
		BoxVars<char>		Vars[];				// 0x90
	} *PMultiselect;

	typedef struct
	{
		wchar_t* data;
		int	len;
	} wchar_str;

	struct wchar_set
	{
		int			Index;
		wchar_t*	NameChunk;
		void*		NameChunkEnd;
		void*		CapacityEnd;
		char		pad2[0x4];
	};

	typedef struct HotkeyPopup : IElement
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
	} HotkeyPop, *PHotkeyPop;

	// HotkeyInfo is 0x28 bytes long
	typedef struct HotkeyInfo
	{
		char			pad1[0x10];
		int				Key;		// 0x10
		HotkeyMode		Mode;		// 0x14
		char			pad[0x10];
	} *PHotkeyInfo;

	// Hotkey is 0x70 bytes long
	struct Hotkey : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;					// 0x20
		Vec2				ActivateSize;			// 0x28
		Vec2				DefaultActivateSize;	// 0x30
		PXorW				CryptedName;			// 0x38
		char				pad1[0x4];
		PCall				CallChunk;				// 0x40
		PCall				CallChunkEnd;			// 0x44
		char				pad2[0x8];
		VecCol				Color;					// 0x50
		int					LeftPaddign;			// 0x54
		char				pad3[0x4];
		PHotkeyInfo			Info;					// 0x5C
		bool				SetingKey;				// 0x60
		char				pad4;
		wchar_t				KeyText[0x4];			// 0x62
		char				pad5[0x2];
		PHotkeyPop			Popup;					// 0x6C
	};

	// Button is 0x64 bytes long
	typedef struct Button : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;				// 0x20
		Vec2				Size;				// 0x28
		Vec2				DefSize;			// 0x30
		PXorW				CryptedName;		// 0x38
		char				pad1[0x4];
		PCall				CallChunk;			// 0x40
		PCall				CallChunkEnd;		// 0x44
		char				pad2[0x8];
		VecCol				Color;				// 0x50
		int					LeftPaddign;		// 0x54
		char				pad3[0xC];
	} *PButton;

	struct ColorPopup
	{
		int		XAxis;			// 0x64
		Vec2	Size;			// 0x68
		Vec2	TintPos;		// 0x70
		Vec2	TintSize;		// 0x78
		Vec2	HuePos;			// 0x80
		Vec2	HueSize;		// 0x88
		Vec2	AlphaPos;		// 0x90
		Vec2	AlphaSize;		// 0x98
	};

	typedef struct
	{
		float	Hue;
		float	Saturation;
		float	Value;
	} HSV, HSB;

	// ColorPicker is 0x138 bytes long
	typedef struct ColorPicker : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;			// 0x20
		Vec2				Size;			// 0x28
		Vec2				DefSize;		// 0x30
		PXorW				CryptedName;	// 0x38
		char				pad1[0x4];
		PCall				CallChunk;		// 0x40
		PCall				CallChunkEnd;	// 0x44
		char				pad2[0x8];
		VecCol				Color;			// 0x50
		int					LeftPaddign;	// 0x54
		char				pad3[0x4];
		VecCol* Value;			// 0x5C
		char				pad4[0x4];
		ColorPopup			Popup;			// 0x64
		char				pad5[0x88];
		PickerStatus		Status;			// 0x128
		HSV					HSV;			// 0x12C
	} CPicker, *PCPicker;

	// Combobox is 0xA8 bytes long
	typedef struct Combobox : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;				// 0x20
		Vec2				InnerPadding;		// 0x28
		Vec2				OuterPadding;		// 0x30
		PXorW				CryptedName;		// 0x38
		char				pad1[0x4];
		PCall				CallChunk;			// 0x40
		PCall				CallChunkEnd;		// 0x44
		char				pad2[0x8];
		VecCol				Color;				// 0x50
		Vec2				BoxPos;				// 0x54
		int*				Value;				// 0x5C
		int					Defheigth;			// 0x60
		int					heigth;				// 0x64
		int					DefInteractOffset;	// 0x68
		int					InteractOffset;		// 0x6C
		bool				Open;				// 0x70
		bool				Clicked;			// 0x71
		char				pad3[0x2];
		int					HoveredItem;		// 0x74
		int					SelectedItem;		// 0x78
		BoxVars<wchar_t>*	VarsChunk;			// 0x7C
		BoxVars<wchar_t>*	VarsChunkEnd;		// 0x80
		char				pad4[0x24];
	} *PCombobox;

	// Label 0x60 bytes long
	typedef struct Label : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;				// 0x20
		Vec2				OuterPadding;		// 0x28
		Vec2				DefOuterPadding;	// 0x30
		PXorW				CryptedName;		// 0x38
		char				pad1[0x4];
		PCall				CallChunk;			// 0x40
		PCall				CallChunkEnd;		// 0x44
		char				pad2[0x8];
		VecCol				Color;				// 0x50
		int					LeftPaddign;		// 0x54
		char				pad3[0x8];
	} *PLabel;

	typedef struct ListboxInfo
	{
		char		pad1[0x4];
		int			SelectedItem;	// 0x88
		char		pad2[0x4];
		wchar_set*  ItemsChunk;		// 0x90
		wchar_set*  ItemsChunkEnd;	// 0x94
		char		pad3[0x8];
	} ListInfo, *PListInfo;

	typedef struct SSpec
	{
		short FindedIndex;
		short Indexies[];
	} *PSpec;

	// Listbox is 0xC0 bytes long
	typedef struct Listbox : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;				// 0x20
		Vec2				Size;				// 0x28
		char				pad1[0x8];
		PXorW				CryptedName;		// 0x38
		char				pad2[0x4];
		PCall				CallChunk;			// 0x40
		PCall				CallChunkEnd;		// 0x44
		char				pad3[0x8];
		VecCol				Color;				// 0x50
		int					LeftPaddign;		// 0x54
		char				pad4[0x8];
		int					ElementSize;		// 0x60
		PListInfo			PInfo;				// 0x64
		char				pad5[0xC];
		size_t				ItemsCount;			// 0x74
		char				pad6[0x4];
		int					SearchPresent;		// 0x7C
		int					DisplayedCount;		// 0x80
		ListboxInfo			Info;				// 0x84
		wchar_t*			SearchChunk;		// 0xA0
		wchar_t*			SearchChunkEnd;		// 0xA4
		void*				SearchCapacityEnd;	// 0xA8
		char				pad7[0x4];
		PSpec				SSpecChunk;			// 0xB0
		short*				SSpecChunkEnd;		// 0xB4
		void*				SSpecCapacityEnd;	// 0xB8
		char				pad8[0x4];
	} *PListbox;

	// Textbox is 0xE8 bytes long
	typedef struct Textbox : IElement
	{
		Header<Child>		Header;
		Vec2				Pos;				// 0x20
		Vec2				Size;				// 0x28
		char				pad1[0x8];
		PXorW				CryptedName;		// 0x38
		char				pad2[0x4];
		PCall				CallChunk;			// 0x40
		PCall				CallChunkEnd;		// 0x44
		char				pad3[0x8];
		VecCol				Color;				// 0x50
		int					LeftPaddign;		// 0x54
		char				pad4[0xC];
		int					Length;				// 0x64
		wchar_t				Text[0x40];			// 0x68
	} *PTextbox;

	typedef struct Inspector
	{
		void**	Vtable;			// 0x00
		char	pad1[0x15];
		UiType	Type;			// 0x19
		char	pad2[0x18];
		PXorW	crypted;		// 0x38
		char	pad3[0x4];
		PCall	CallChunk;		// 0x40
		PCall	CallChunkEnd;	// 0x44
		char	pad4[0x14];
		void*	value;			// 0x5C
	} *PInspector;

	typedef struct CWidg
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
	} *PCWidg;

	typedef struct Unkn
	{
		void* ptr;
		int i1;
		int i2;
		PXorW name;
	} *PUnkn;

	// Child is 0xC8 bytes long
	struct Child : IElement
	{
		Header<CTab>		Header;
		Vec2				Pos;				// 0x20
		Vec2				Size;				// 0x28
		Vec2				DefSize;			// 0x30
		PXorW				CryptedName;		// 0x38
		PUnkn				Unknown;			// 0x3C
		PCall				CallChunk;			// 0x40
		PCall				CallChunkEnd;		// 0x44
		char				pad1[0x8];
		VecCol				Color;				// 0x50
		char				pad2[0x14];
		Vec2				Padding;			// 0x68
		Vec4_8t				PosSize;			// 0x70 block = minimum size child can be resized/moved by, x = blocks moved by X, y = blocks sized by X, z = blocks moved by Y, w = blocks sized by Y
		Vec2				MouseLastPos;		// 0x74
		ChildStatus			Status;				// 0x7C
		PElements			ElementsChunk;		// 0x80
		PElements			ElementsChunkEnd;	// 0x84
		void*				ElementsCapacityEnd;// 0x88
		char				pad3[0x4];
		PCWidg				PWidgets;			// 0x90
		char				pad4[0x4];
		Vec2				CurSize;			// 0x98
		Vec2				MinimizedCapacity;	// 0xA0
		CWidg				Widgets;			// 0xA8
	};

	struct Element
	{
		template<typename T>
		T* GetAs() { return reinterpret_cast<T*>(this); };
	};

	typedef struct
	{
		char			pad4[0x8];
		int				TextureId;		// 0x80
		int				TextureOffset;	// 0x84
		char			pad5[0x4];
		Vec2			Size;			// 0x8C
	} TabIcon;


	class ITab
	{
	private:
		virtual void fn0() = 0;
		virtual void fn1() = 0;
		virtual void fn2() = 0;
		virtual void fn3() = 0;
		virtual void fn4() = 0;
		virtual void fn5() = 0;
		virtual void fn6() = 0;
		virtual void fn7() = 0;
		virtual void fn8() = 0;
		virtual void fn9() = 0;
		virtual void fn10() = 0;
		virtual void fn11() = 0;
		virtual void fn12() = 0;
		virtual void fn13() = 0;
	public:
		virtual void ResetLayout();
	};
	struct CTab : public ITab
	{
		Header<void>		Header;
		Vec2				Pos;			// 0x20
		Vec2				Size;			// 0x28
		Vec2				DefSize;		// 0x30
		PXorW				CryptedName;	// 0x38
		char				pad1[0x14];
		VecCol				Color;			// 0x50
		char				pad2[0xC];
		PCMenu				Menu;			// 0x60
		char				pad3[0xC];
		PChilds				ChildsChunk;	// 0x70
		PChilds				ChildsChunkEnd;	// 0x74
		TabIcon				Icon;			// 0x78
		int					Padding;		// 0x94
		void*				Chunk;			// 0x98
		void*				ChunkEnd;		// 0x9C
		PElement			CEs[0x20];		// 0xA0	childs and some elems lets say it will be 0x20 size for our allocation purposes
	};

	//0x20 Struct for lua listbox chunk in Config tab
	typedef struct
	{
		char		pad1[0x8];
		int			OnStartup;		// 0x8
		wchar_t*	NameChunk;		// 0xC
		void*		NameChunkEnd;	// 0x10
		char		pad2[0xC];
	} LuaChunk;

	struct CMenu
	{
		void**			Vtable;				// 0x0
		PCMenu			NextMenu;			// 0x4
		char			pad1[0x4];
		Vec2			Pos;				// 0xC
		Vec2			Size;				// 0x14
		Vec2			MinSize;			// 0x1C
		Vec2			TabStartPadding;	// 0x24
		Vec2			TabEndPadding;		// 0x2C
		MenuStatus		MenuStatus;			// 0x34
		MouseInfo		Mouse;				// 0x38
		char			pad2[0x8];
		PCTabs			TabsChunk;			// 0x54
		PCTabs			TabsChunkEnd;		// 0x58
		void*			TabsCapacityEnd;	// 0x5C
		char			pad3[0x4];
		Tab				CurrentTab;			// 0x64
		char			pad4[0x20];
		unsigned int	MenuFadeTickCount;	// 0x88
		FadeType		MenuFadeType;		// 0x8C
		char			pad5[0x4];
		void*			SomeVT;				// 0x94
		int				SomeInt;			// 0x98
		char			pad6[0x14];
		float			MenuAlpha;			// 0xB0
		PCTab			Tabs[9];			// 0xB4
		char			pad7[0x4];
		int				BackgroundTextureId;// 0xDC

	};

	typedef struct CLua
	{
		char	pad1[0x44];
		void*	LuaState;		// 0x44
		char	pad2[0x24];
		int		LoadedCount;	// 0x6C
	} *PCLua, **PCLuas;

#pragma pack(pop)

	class IRenderer
	{
	private:
		virtual void fn0() = 0;
		virtual bool fn1() = 0; // Ready?
		virtual void fn2() = 0; // Renders menu shadows and scrollbars
		virtual void _guard_check_icall_nop3() = 0; // CFG ret 0 function
	public:
		virtual void Rect(int x, int y, int h, int w, int color) = 0;
	private:
		virtual void fn5() = 0;
	public:
		virtual void GradientV(int x, int y, int h, int w, int color1, int color2) = 0;
		virtual void GradientH(int x, int y, int h, int w, int color1, int color2) = 0;
		virtual void Line(int x1, int y1, int x2, int y2, int color) = 0;
	private:
		virtual void fn9() = 0;
	public:
		virtual void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) = 0;
		virtual void __vectorcall Circle(int x, int y, int color, float rad, float rot, float percent) = 0;
		virtual void __vectorcall CircleOut(int x, int y, int color, float rad, float rot, float percent, float thick) = 0;
	private:
		//struct point { float x1; float y1; int color1; float x2; float y2; int color2; };
		virtual void __fastcall PolyCircle(void* points, size_t count) = 0;
		virtual void fn14() = 0;
	public:
		virtual void __fastcall Text(int flags, int x, int y, int color, size_t maxlen, wchar_t* text, size_t len) = 0;
	private:
		virtual void fn16() = 0;
	public:
		virtual void __fastcall MeasureText(int* out, wchar_t* text, size_t len, int flags) = 0;
		virtual void __fastcall ScreenSize(int* w, int* h) = 0;
		virtual int __fastcall AddTexture(unsigned char* data, int w, int h, size_t bytesize, int i0, int i1) = 0;
	private:
		virtual void fn20() = 0;
		virtual void fn21() = 0;
		virtual void _guard_check_icall_nop22() = 0; // CFG ret 0 function;
	public:
		virtual void __vectorcall Texture(int id, int x, int y, int color, int offset, int i0, int w, int h, int flag, float scale) = 0;
		virtual void __fastcall SetBounds(int bounds[4]) = 0;
		virtual void __fastcall GetBounds(int bounds[4]) = 0;
		virtual void __fastcall ResetBounds(bool reset) = 0;
		virtual bool IsBoundsPresent() = 0;	// returns true if ResetBounds was called
		virtual void __vectorcall SetAlpha(float alpha) = 0;
		virtual void __vectorcall SetZBuff(float z) = 0; // [0.0, 1.0] 0.0 = topmost, 1.0 = doesnt render
		virtual float GetZBuff() = 0; // [0.0, 1.0] 0.0 = topmost, 1.0 = doesnt render
	private:
		virtual void Monochrome(bool state) = 0; // grey if enemy alive?
		virtual void fn32() = 0;
		virtual float __vectorcall GetScale() = 0; // returns render scale aka dpi
		virtual int __fastcall fn34(int i) = 0; // returns render padding?
		virtual void fn35() = 0;
		virtual void fn36() = 0;
		virtual void fn37() = 0;
		virtual void fn38() = 0;
		virtual float __vectorcall fn39() = 0;
		virtual void __fastcall fn40(int, int*, int*) = 0;
	public:
		virtual void __fastcall RectOut(int thick, int x, int y, int w, int h, int color) = 0;
		virtual void __fastcall RectOutlined(int thick, int x, int y, int w, int h, int colorin, int colorout) = 0;
	};
	struct SkeetClass_
	{
		IRenderer* IRenderer;
		void* DefSubclassProc;
		void* RemoveWindowSubclass;
		void* SetWindowSubclass;
		PCMenu Menu;
		void* ThreadInMainThread;
	};

	typedef struct {
		unsigned char* ChunkStart;
		unsigned char* ChunkEnd;
		unsigned char* CappacityEnd;
	} DataChunk;

	namespace Memory {
		class SigFinder
		{
			MODULEINFO info;
			static sVec<int> ida_sig_resolver(const char* sig);
		public:
			SigFinder(const char* module);
			SigFinder(LPVOID lpBaseAdress, DWORD SizeOfImage);
			FORCECALL void* find(const char* sig, int offset = 0);
			FORCECALL void* findr32(const char* sig);
		};

		class CHooked
		{
			bool Status;
			void* Address;
			unsigned char* OriginalBytes;
			size_t BytesSize;
			void* naked;
		public:
			CHooked(void* func, unsigned char* ogbytes, size_t size);
			~CHooked();
			void* Naked();
			void Unhook();
		};

		class DetourHook
		{
			static sVec<CHooked*> Hooked;
		public:
			static CHooked* Hook(void* Dst, void* Src, size_t size = 5);
			static void UnhookAll();
		};
		static SigFinder	CheatChunk((LPVOID)0x43310000, 0x2FC000u);
		static AllocatorFn	Allocator = (AllocatorFn)CheatChunk.find("56 8B F1 33 C0 85");
	} // namespace Memory

//SDK Vars
	static SkeetClass_* SCLASS = *(SkeetClass_**)Memory::CheatChunk.find("A1 ?? ?? ?? ?? 83 64 24 04 00 89 54 24 18 89 44 24 10 53 56", 0x1);
	static PCMenu Menu = SCLASS->Menu;
//SDK Classes
	class Utils final
	{
		friend class UI;
	MEMBERS_PRIVATE
		static GetConfigDataFn	GetConfigData;
		static LoadConfigFn		LoadConfig;
		static CFn				InitState;
		static CFn				GetState;
		static PCLuas			LuaInfo;
		static LoadLuaFn		LoadLua;
		static DecryptFn		Decrypt;
		static CryptFn			Crypt;
		static ThisFn			InitTab;
		static ThisFn			Callback;
		static HashFn			Hash;
	MEMBERS_PUBLIC
		static unsigned int* HashedCfgName;

		static int			LuaCount();
		static wchar_t*		LuaName(int index);
		static bool			LoadScript(int index);
		static bool			LoadScript(wchar_t* name);
		static void			AllowUnsafe(int value);
		static void			LoadCfg(int index = -1);
		static void			LoadCfg(const char* cfgname);
		static PXorW		CryptName(wchar_t* name);
		static void*		LuaState();
		static void*		GetLuaState();
		static void			ForEach(PChild child, void(*func)(PElement), UiType T = UiNone);
		static PCLua		GetLuaInfo();
		static void			InitConfig();
		static unsigned int ChildsCount(PCTab tab);
		static unsigned int ElementsCount(PChild child);
		static FORCECALL const wchar_t* CurrentConfig();
		static FORCECALL int			CurrentConfigIndex();
	};

	class UI final
	{
	MEMBERS_PRIVATE
		static ThisIntFn		TabSwitch;
		static ThisIntFn		SetList;
		static ThisFn			ChildLayout;
		static ThisFn			KeyInit;
		static SetKeyFn			SetKey;
		static SetCheckFn		SetCheck;
		static HideUiFn			HideUi;
		static F2PFn			DeleteUi;
		static T2PFn			InsertTab;
		static T2PFn			InsertChildr;
		static InsertFn			InsertElem;
		static AddLabelFn		AddLabel;
		static AddButtonFn		AddButton;
		static LConFn			LabelCon;
		static BConFn			ButtonCon;
		static TBConFn			TextboxCon;
		static TCConFn			CheckboxCon;
		static SConFn			SliderCon;
		static HKConFn			HotkeyCon;
		static CPConFn			CPickerCon;
		static CBConFn			ComboboxCon;
		static MConFn			MultiCon;
		static LBConFn			ListboxCon;
		static CHConFn			ChildCon;
		static TCConFn			TabCon;
		static GetTBoxTextFn	GetTBoxText;
	MEMBERS_PUBLIC
		static void			ResetLayout();
		static void			SetTab(Tab tab);
		static PCTab		GetTab(Tab tab);
		static Tab			GetActiveTab();
		static PCTab		GetActiveCTab();
		static void			SetVisible(PElement element, bool value);
		static VecCol		GetMenuCol();
		static void			SetInput(PElement elemen, bool val);
		static void*		TieValue(PElement element, void* ptr);
		static size_t		GetCallbacksCount(PElement elem);
		static void			SetCallback(PElement elem, F2PFn func, void* ecx = NULL);
		static void			DeleteElement(PElement element);
		static void			SetCheckbox(PCheckbox checkbox, int value);
		static void			SetColorRGBA(PCPicker picker, VecCol Color);
		static void			SetColorHSV(PCPicker picker, HSV Color);
		static void			SetSlider(PSlider slider, int value);
		static void			SetCombobox(PCombobox combobox, int value);
		static void			SetListbox(PListbox listbox, int value);
		static void			SetHotkey(PHotkey hotkey, int key, HotkeyMode mode = Inherit);
		static int			ExtractKey(PHotkey hotkey);
		static int			HotkeyState(PHotkey hotkey);
		static void			RenameElement(PElement element, wchar_t* name, PXorW oldname);
		static wchar_t*		GetName(PElement element);
		static size_t		GetTextbotText(PTextbox tbox, wchar_t* buffer);
		static void			InsertElement(PChild child, void* element);
		static PLabel		CreateLabel(PChild child, wchar_t* name);
		static PTextbox		CreateTextbox(PChild child, bool sameline = true, wchar_t* name = NULL);
		static PCheckbox	CreateCheckbox(PChild child, wchar_t* name, int* value);
		static PSlider		CreateSlider(PChild child, wchar_t* name, int min, int max, int* value, bool tooltip = true, wchar_t* tip = NULL, float step = 1.f);
		static PHotkey		CreateHotkey(PChild child, wchar_t* name, bool sameline = false, int vkey = 0x00, HotkeyMode mode = OnHotkey);
		static PButton		CreateButton(PChild child, wchar_t* name, F2PFn function, void* ecx = Menu);
		static PCPicker		CreateColorPicker(PChild child, VecCol* value, bool sameline = true, wchar_t* name = NULL);
		static PCombobox	CreateCombobox(PChild child, wchar_t* name, int* value, wchar_t** arr, size_t arrsize, bool sameline = false);
		static PMultiselect CreateMultiselect(PChild child, wchar_t* name, int* value, char** arr, size_t arrsize, bool sameline = false);
		static PListbox		CreateListbox(PChild child, wchar_t* name, int* value, wchar_t** arr, size_t arrsize, bool searchbox = true);
		static void			AddListboxVar(PListbox list, wchar_t* elem, size_t bsize = 0);
		static void			RemoveListboxVar(PListbox list, size_t index);
		static void			InsertChild(PCTab tab, void* child);
		static PChild		CreateChild(PCTab tab, wchar_t* name, Vec4_8t possize, bool modify);
		static PCTab		CreateTab(wchar_t* name, Vec2 pos);

		static FORCECALL PElement		GetByName(PChild child, const wchar_t* name);
		static FORCECALL PChild			GetChild(Tab tab, size_t index);
		template<typename T> static T*	GetElement(PChild, size_t index);
	};

	class EventListener
	{
		size_t index;
		RenderEventType type;
		bool status;
	public:
		EventListener(size_t index, RenderEventType type) : index(index), type(type), status(true) {};
		~EventListener() { remove(); };
		void remove();
	};

	struct CTexture
	{
		int id;
		TextureType type;
		Vec2 Size;
		CTexture(int id, TextureType type, int width, int heigth) : id(id), type(type), Size(width, heigth) {};
	};

	class Renderer final
	{
	MEMBERS_PRIVATE
		static sVec<RenderEventListenerFn> RenderEvents;
		static sVec<RenderEventListenerFn> MenuEvents;
		static sVec<RenderEventListenerFn> FinalEvents;
		static Memory::CHooked* RenderHook;
		static Memory::CHooked* MenuRenderHook;
		static Memory::CHooked* FinalRenderHook;
		static ReadFileFn ExReadFile;
		static LoadTextureFn LoadTexture;
		static LoadSvgFormFileFn LoadSvgFromFile;
		static RenderIndicatorFn RenderIndicator;
		static WorldToScreenFn WorldToScreen;
		static RenderBlurFn RenderBlur;
		static void* RenderBlurCtx;
		static void __fastcall RenderListener(void* ecx, void* edx);
		static void __fastcall MenuRenderListener(void* ecx, void* edx);
		static void __fastcall RenderFinalListener(void* ecx, void* edx);
		static void RemoveEvent(size_t index, RenderEventType type);
		friend class EventListener;
	MEMBERS_PUBLIC
		static void Init();
		static void Term();
		static EventListener* AddEvent(RenderEventType type, RenderEventListenerFn event);
		static Vec2 ScreenSize();
		static int ScreenWidth();
		static int ScreenHeigth();
		static Vec2 MeasureText(wchar_t* text, unsigned int flags);
		static void ToScreen(Vec3f_t pos, int* x, int* y);
		static void Text(Vec2 pos, VecCol color, wchar_t* text, int flags, unsigned int maxlen = 0);
		static void Line(Vec2 p1, Vec2 p2, VecCol color);
		static void Rect(Vec2 pos, Vec2 size, VecCol color);
		static void RectOut(Vec2 pos, Vec2 size, VecCol color, int thickness);
		static void OutlinedRect(Vec2 pos, Vec2 size, VecCol colorin, VecCol colorout, int thickness);
		static void Gradient(Vec2 pos, Vec2 size, VecCol color1, VecCol color2, bool horizontal = true);
		static void Blur(Vec2 pos, Vec2 size);
		static void Triangle(Vec2 p1, Vec2 p2, Vec2 p3, VecCol color);
		static void Indicator(int y, VecCol color, const char* text, int texureid = -1, float circlepercent = -1.f);
		static void __vectorcall Circle(Vec2 pos, VecCol color, float radius, float rotation = 0.f, float percentage = 1.f);
		static void __vectorcall CircleOut(Vec2 pos, VecCol color, float radius, float rotation = 0.f, float percentage = 1.f, float thickness = 1.f);
		static void Texture(int id, Vec2 pos, Vec2 size, VecCol color, int flag, int offset = 0, float scale = 1.f);
		static CTexture* LoadSVGTextureFromFile(const char* filename, int width = 0, int heigth = 0);
		static FORCECALL CTexture* LoadPNGTextureFromFile(const char* filename, int width = 0, int heigth = 0);
		static FORCECALL CTexture* LoadJPGTextureFromFile(const char* filename, int width = 0, int heigth = 0);
		static FORCECALL CTexture* LoadTextureFromMemory(const unsigned char* data, size_t size, TextureType type, int width, int heigth);
	};

#if defined(SDK_GLOBALS_IMP) || defined(SDK_CLIENT_IMP)
	struct CommandsInfo
	{
		unsigned int	LastOutCommand;	// 0x0
		unsigned int	ChokedCommands;	// 0x4
		unsigned int	OldCommandAck;	// 0x8
		char			pad1[0x4];
		unsigned int	CommandAck;		// 0x10
	};

	class CEngine final
	{
		friend class Globals;
		friend class Client;
		static void**** EngineCtx;
		static CommandsInfo** CommandsCtx;
		static SetClanTagFn SetTag;
		static unsigned int* PredComm;
		static bool IsInGame();
		static char* MapName();
		static void ExecCommand(const char* command);
		static void SetClanTag(const char* tag);
	};
#endif
	struct GlobalsInfo
	{
		float			RealTime;		// 0x0
		int				FrameCount;		// 0x4
		float			AbsFrameTime;	// 0x8
		char			pad1[0x4];
		float			CurrentTime;	// 0x10
		float			FrameTime;		// 0x14
		int				MaxPlayers;		// 0x18
		unsigned int	TickCount;		// 0x1С
		float			TickInterval;	// 0x20
	};

	class Globals final
	{
	MEMBERS_PRIVATE
		static GlobalsInfo** GlobalsCtx;
	MEMBERS_PUBLIC
		static bool			IsInGame();
		static char*		MapName();
		static float		RealTime();
		static float		FrameTime(bool abs = false);
		static int			FrameCount();
		static float		CurrentTime();
		static float		TickInterval();
		static unsigned int	TickCount();
		static int			MaxPlayers();
		static unsigned int	LastOutCommand();
		static unsigned int	ChokedCommands();
		static unsigned int	OldCommandAck();
		static unsigned int	CommandAck();
	};

	class Client final
	{
	MEMBERS_PRIVATE
		static LogFn Logger;
		static LogErrorFn LoggerError;
		static void*** LoggerCtx;
		static ScreenLogFn ScreenLogger;
	MEMBERS_PUBLIC
		static void Exec(const char* cmd);
		static void SetClanTag(const char* tag);
		static void LogScreen(const char* text, VecCol color);
		static FORCECALL void Log(const char* fmt, ...);
		static FORCECALL void LogColor(VecCol Color, const char* fmt, ...);
		static FORCECALL void LogError(const char* fmt, ...);
	};	
} // namespace SkeetSDK


// Implementation
namespace SkeetSDK
{
	// Memory Implementaiton
	namespace Memory
	{
		template <typename T>
		T GetChunkAs(PCTab tab)
		{
			return reinterpret_cast<T>(tab->Chunk);
		};

		template <typename T>
		T GetVFunc(PElement ptr, size_t index)
		{
			return reinterpret_cast<T>(ptr->GetAs<Inspector>()->Vtable[index]);
		};

		template <typename T>
		T VtableBind(void** table, size_t index)
		{
			return reinterpret_cast<T>(table[index]);
		};

		HMODULE WaitForSingleHandle(const char* module)
		{
			HMODULE hmod = GetModuleHandleA(module);
			while (!hmod)
			{
				hmod = GetModuleHandleA(module);
				Sleep(100);
			};
			return hmod;
		}

		// SigFinder Implementation
		SigFinder::SigFinder(const char* module)
		{
			info = { 0 };
			GetModuleInformation(GetCurrentProcess(), WaitForSingleHandle(module), &info, sizeof(MODULEINFO));
		};

		SigFinder::SigFinder(LPVOID lpBaseAdress, DWORD SizeOfImage)
		{
			info = { 0 };
			info.lpBaseOfDll = lpBaseAdress;
			info.SizeOfImage = SizeOfImage;
		};

		sVec<int> SigFinder::ida_sig_resolver(const char* sig)
		{
			size_t siglen = strlen(sig);
			sVec<int> vec((siglen + 1) / 3);
			for (size_t i = 0; i < siglen; i += 3)
			{
				if (sig[i] == '?' && sig[i + 1] == '?')
				{
					vec.push_back(-1);
					continue;
				};
				if (sig[i] >= 65 && sig[i] <= 90)
				{
					vec.push_back((sig[i] - 55) << 4);
				}
				else
				{
					vec.push_back((sig[i] - '0') << 4);
				};
				if (sig[i + 1] >= 65 && sig[i + 1] <= 90)
				{
					vec.last() |= (sig[i + 1] - 55);
				}
				else
				{
					vec.last() |= (sig[i + 1] - '0');
				};
			};
			return vec;
		};

		void* SigFinder::find(const char* sig, int offset)
		{
			sVec<int> pattern = ida_sig_resolver(sig);
			for (size_t i = 0; i < info.SizeOfImage; i++)
			{
				for (size_t j = 0; j < pattern.len(); j++)
				{
					if (pattern[j] != -1 && pattern[j] != reinterpret_cast<unsigned char*>(info.lpBaseOfDll)[i + j]) break;
					if (j + 1 == pattern.len())
					{
						return reinterpret_cast<unsigned char*>(info.lpBaseOfDll) + i + offset;
					};
				};
			}
			return NULL;
		};

		void* SigFinder::findr32(const char* sig)
		{
			sVec<int> pattern = ida_sig_resolver(sig);
			if (pattern[0] != 0xE8 && pattern[0] != 0xE9) return NULL;
			for (size_t i = 0; i < info.SizeOfImage; i++)
			{
				for (size_t j = 0; j < pattern.len(); j++)
				{
					if (pattern[j] != -1 && pattern[j] != reinterpret_cast<unsigned char*>(info.lpBaseOfDll)[i + j]) break;
					if (j + 1 == pattern.len())
					{
						return reinterpret_cast<unsigned char*>(info.lpBaseOfDll) + i + 5 + *(int*)((unsigned char*)info.lpBaseOfDll + i + 1);
					};
				};
			}
			return NULL;
		};

		// CHooked Implementation
		CHooked::CHooked(void* func, unsigned char* ogbytes, size_t size)
		{
			Address = func;

			OriginalBytes = ogbytes;

			BytesSize = size;
			Status = true;

			void* heap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BytesSize + 5);
			DWORD OldProto{ 0 };
			VirtualProtect(heap, BytesSize + 5, PAGE_EXECUTE_READWRITE, &OldProto);
			memcpy(heap, OriginalBytes, BytesSize);
			*(char*)((char*)heap + BytesSize) = 0xE9;
			*(int*)((char*)heap + BytesSize + 1) = (int)Address - ((int)heap + (int)BytesSize);
			naked = heap;
		};

		CHooked::~CHooked()
		{
			Unhook();
			free(OriginalBytes);
			HeapFree(GetProcessHeap(), 0, naked);
		};

		void* CHooked::Naked()
		{
			return naked;
		};

		void CHooked::Unhook()
		{
			if (!Status) return;
			memcpy(Address, OriginalBytes, BytesSize);
			Status = false;
		};

		// DetourHook Implementation
		CHooked* DetourHook::Hook(void* Dst, void* Src, size_t size)
		{
			ptrdiff_t rel32 = (int)Src - (int)Dst - 5;
			DWORD OldProto{ 0 };
			unsigned char* ogbytes = (unsigned char*)malloc(size);
			VirtualProtect(Dst, size, PAGE_EXECUTE_READWRITE, &OldProto);
			memcpy(ogbytes, Dst, size);
			*(BYTE*)Dst = 0xE9;
			*(int*)((BYTE*)Dst + 1) = rel32;
			if (size - 5 > 0)
				memset((char*)Dst + 5, 0x90, size - 5);
			VirtualProtect(Dst, size, OldProto, &OldProto);
			CHooked* hook = new CHooked(Dst, ogbytes, size);
			Hooked.push_back(hook);
			return hook;
		};

		void DetourHook::UnhookAll()
		{
			for (size_t i = 0; i < Hooked.len(); i++)
				Hooked[i]->Unhook();
		};

		sVec<CHooked*> DetourHook::Hooked = { 20 };
	}; // Memory namepsace

	// Utils Implementation
	CFn				Utils::GetState			= (CFn)Memory::CheatChunk.find("A1 ?? ?? ?? ?? 85 C0 75 01 C3 83 C0 44 C3");
	PCLuas			Utils::LuaInfo			= *(PCLuas*)Memory::CheatChunk.find("A1 ?? ?? ?? ?? 85 C0 75 01 C3 83 C0 44 C3", 0x1);
	LoadLuaFn		Utils::LoadLua			= (LoadLuaFn)Memory::CheatChunk.find("83 EC 4C 53 55 33");
	DecryptFn		Utils::Decrypt			= (DecryptFn)Memory::CheatChunk.find("51 51 55 56 8B C2");
	CryptFn			Utils::Crypt			= (CryptFn)Memory::CheatChunk.find("51 53 8B 5C 24 0C 55 56 8B E9");
	ThisFn			Utils::InitTab			= (ThisFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 83 EC 30 53 8B");
	ThisFn			Utils::Callback			= (ThisFn)Memory::CheatChunk.find("53 56 57 8B F9 8B 5F 44");
	CFn				Utils::InitState		= (CFn)Memory::CheatChunk.find("55 8B EC 83 EC 2C 56 57 E8");
	GetConfigDataFn Utils::GetConfigData	= (GetConfigDataFn)Memory::CheatChunk.find("55 8B EC 83 EC 18 56 57 89");
	LoadConfigFn	Utils::LoadConfig		= (LoadConfigFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 83 EC 40 56 57 8B FA");
	HashFn			Utils::Hash				= (HashFn)Memory::CheatChunk.find("56 8B F1 BA C5");

	unsigned int*	Utils::HashedCfgName = *(unsigned int**)Memory::CheatChunk.find("A3 ?? ?? ?? ?? 8B CC 8D 44 24 30 89 7C 24 10", 0x1);


	unsigned int Utils::ChildsCount(PCTab tab)
	{
		return tab->ChildsChunkEnd - tab->ChildsChunk;
	};

	unsigned int Utils::ElementsCount(PChild child)
	{
		return child->ElementsChunkEnd - child->ElementsChunk;
	};

	void Utils::InitConfig()
	{
		InitTab(Menu->TabsChunk[Config]);
	};

	PCLua Utils::GetLuaInfo()
	{
		return *LuaInfo;
	};

	void Utils::LoadCfg(int index)
	{
		if (index >= 0)
			UI::SetListbox(Menu->TabsChunk[Config]->ChildsChunk[0]->ElementsChunk[0]->GetAs<Listbox>(), index);
		Callback(Menu->TabsChunk[Config]->ChildsChunk[0]->ElementsChunk[3]);
	};

	void Utils::LoadCfg(const char* cfgname)
	{
		DataChunk cfgchunk{ 0 };
		GetConfigData(cfgname, &cfgchunk);
		if (cfgchunk.ChunkStart)
			LoadConfig(Menu, cfgchunk.ChunkStart, (int)cfgchunk.ChunkEnd - (int)cfgchunk.ChunkStart);
	};

	const wchar_t* Utils::CurrentConfig()
	{
		if (!*HashedCfgName) return L"Default";
		PListbox ptr = Menu->TabsChunk[Config]->ChildsChunk[0]->ElementsChunk[0]->GetAs<Listbox>();
		size_t count = ptr->Info.ItemsChunkEnd - ptr->Info.ItemsChunk;
		for (size_t i = 0; i < count; i++)
		{
			if (Hash(ptr->Info.ItemsChunk[i].NameChunk) == *HashedCfgName)
				return ptr->Info.ItemsChunk[i].NameChunk;
		}
	};

	int Utils::CurrentConfigIndex()
	{
		if (!*HashedCfgName) return -1;
		PListbox ptr = Menu->TabsChunk[Config]->ChildsChunk[0]->ElementsChunk[0]->GetAs<Listbox>();
		size_t count = ptr->Info.ItemsChunkEnd - ptr->Info.ItemsChunk;
		for (size_t i = 0; i < count; i++)
		{
			if (Hash(ptr->Info.ItemsChunk[i].NameChunk) == *HashedCfgName)
				return i;
		}
	};

	int Utils::LuaCount()
	{
		return ((int)Menu->TabsChunk[Config]->ChunkEnd - (int)Menu->TabsChunk[Config]->Chunk) / sizeof(LuaChunk);
	};

	wchar_t* Utils::LuaName(int index)
	{
		if (index >= LuaCount()) return NULL;
		return Menu->TabsChunk[Config]->ChildsChunk[1]->ElementsChunk[3]->GetAs<Listbox>()->Info.ItemsChunk[index].NameChunk;
	};


	bool Utils::LoadScript(int index)
	{
		wchar_t* name = LuaName(index);
		if (name == NULL) return false;
		return LoadLua(name, Memory::GetChunkAs<LuaChunk*>(UI::GetTab(Config)));
	};

	bool Utils::LoadScript(wchar_t* name)
	{
		return LoadLua(name, Memory::GetChunkAs<LuaChunk*>(UI::GetTab(Config)));
	};

	void Utils::AllowUnsafe(int value)
	{
		UI::SetCheckbox(Menu->TabsChunk[Config]->ChildsChunk[1]->ElementsChunk[1]->GetAs<Checkbox>(), value);
	};

	PXorW Utils::CryptName(wchar_t* name)
	{
		return (PXorW)Crypt(name, (wcslen(name) + 1) * sizeof(wchar_t), 2);
	};


	void* Utils::LuaState()
	{
		return InitState();
	}

	void* Utils::GetLuaState()
	{
		return GetState();
	};

	void Utils::ForEach(PChild child, void(*func)(PElement), UiType T)
	{
		size_t count = ElementsCount(child);
		for (size_t i = 0; i < count; i++)
		{
			PElement element = child->ElementsChunk[i];
			if (T == UiNone || element->GetAs<Header<void>>()->Type == T)
			{
				func(element);
			}
		}
	};

	// UI Implementation
	ThisIntFn		UI::TabSwitch		= (ThisIntFn)Memory::CheatChunk.find("56 8B F1 57 8B 7C 24 0C 8B 4E 64");
	ThisIntFn		UI::SetList			= (ThisIntFn)Memory::CheatChunk.find("8B 81 94 00 00 00 2B");
	ThisFn			UI::ChildLayout		= (ThisFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 83 EC 10 53 55");
	ThisFn			UI::KeyInit			= (ThisFn)Memory::CheatChunk.find("8B D1 B9 ?? ?? ?? ?? E9");
	SetKeyFn		UI::SetKey			= (SetKeyFn)Memory::CheatChunk.find("81 EC 08 02 00 00 53");
	SetCheckFn		UI::SetCheck		= (SetCheckFn)Memory::CheatChunk.find("8B 41 5C 53 85");
	HideUiFn		UI::HideUi			= (HideUiFn)Memory::CheatChunk.find("8A 44 24 04 38");
	F2PFn			UI::DeleteUi		= (F2PFn)Memory::CheatChunk.find("83 EC 0C A1 24");
	T2PFn			UI::InsertTab		= (T2PFn)Memory::CheatChunk.find("8B 41 58 83 C1");
	T2PFn			UI::InsertChildr	= (T2PFn)Memory::CheatChunk.find("55 8B EC 8B 45 08 56 8B F1 89");
	InsertFn		UI::InsertElem		= (InsertFn)Memory::CheatChunk.find("56 57 8B F9 8B 4F 10");
	AddLabelFn		UI::AddLabel		= (AddLabelFn)Memory::CheatChunk.find("55 8B EC 56 57 8B F9 6A");
	AddButtonFn		UI::AddButton		= (AddButtonFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 51 51 56 57 8B F9 6A");
	LConFn			UI::LabelCon		= (LConFn)Memory::CheatChunk.find("56 6A 00 6A 08");
	BConFn			UI::ButtonCon		= (BConFn)Memory::CheatChunk.find("55 8B EC 83 EC 0C 56 6A");
	TBConFn			UI::TextboxCon		= (TBConFn)Memory::CheatChunk.find("56 57 33 FF 8B F1 57 6A 0A");
	TCConFn			UI::CheckboxCon		= (TCConFn)Memory::CheatChunk.find("56 FF 74 24 10 8B F1 6A");
	SConFn			UI::SliderCon		= (SConFn)Memory::CheatChunk.find("55 8B EC 53 56 FF");
	HKConFn			UI::HotkeyCon		= (HKConFn)Memory::CheatChunk.find("53 8B 5C 24 0C 56 53");
	CPConFn			UI::CPickerCon		= (CPConFn)Memory::CheatChunk.find("53 56 57 FF 74 24 14 8B D9 6A");
	CBConFn			UI::ComboboxCon		= (CBConFn)Memory::CheatChunk.find("56 57 FF 74 24 14 8B F1 6A 04");
	MConFn			UI::MultiCon		= (MConFn)Memory::CheatChunk.find("56 57 FF 74 24 14 8B F1 6A 0D");
	LBConFn			UI::ListboxCon		= (LBConFn)Memory::CheatChunk.find("55 8B EC 53 56 57 FF 75 18");
	CHConFn			UI::ChildCon		= (CHConFn)Memory::CheatChunk.find("55 8B EC 56 FF 75 18");
	TCConFn			UI::TabCon			= (TCConFn)Memory::CheatChunk.find("56 57 33 FF 8B F1 57 6A 01");
	GetTBoxTextFn	UI::GetTBoxText		= (GetTBoxTextFn)Memory::CheatChunk.find("53 55 8B E9 8B 5D 04 85 DB 74 4B EB 02 F3 90 33 C0 40 87 45 00 85 C0 75 F4 8B 5D 04 83 FB 41");

	void UI::ResetLayout()
	{
		Button* b = (Button*)GetByName(GetChild(Misc, 2), L"Reset menu layout");
		b->CallChunk->function(Menu, b);
	};

	void UI::SetTab(Tab tab)
	{
		TabSwitch(Menu, tab);
	};

	PCTab UI::GetTab(Tab tab)
	{
		return Menu->TabsChunk[tab];
	};

	Tab UI::GetActiveTab()
	{
		return Menu->CurrentTab;
	}

	PCTab UI::GetActiveCTab()
	{
		return Menu->TabsChunk[Menu->CurrentTab];
	}

	void UI::SetVisible(PElement element, bool value)
	{
		HideUi(element, element, value);
	};

	VecCol UI::GetMenuCol()
	{
		return GetChild(Misc, 2)->ElementsChunk[3]->GetAs<CPicker>()->Value[0];
	};

	void UI::SetInput(PElement elemen, bool val)
	{
		Header<Child>* head = elemen->GetAs<Header<Child>>();
		head->Flags.AllowMouseInput = val;
		head->Flags.Editable = val;
	};

	void* UI::TieValue(PElement element, void* ptr)
	{
		void* oldptr = element->GetAs<Inspector>()->value;
		element->GetAs<Inspector>()->value = ptr;
		return oldptr;
	};

	size_t UI::GetCallbacksCount(PElement elem)
	{
		return elem->GetAs<Inspector>()->CallChunkEnd - elem->GetAs<Inspector>()->CallChunk;;
	};

	void UI::SetCallback(PElement elem, F2PFn func, void* ecx)
	{
		size_t index = GetCallbacksCount(elem);
		PInspector ptr = elem->GetAs<Inspector>();
		if (!index)
		{
			ptr->CallChunk = (PCall)Memory::Allocator(sizeof(Call) * 10);
			ptr->CallChunkEnd = ptr->CallChunk;
		}
		ptr->CallChunk[index].ecx = ecx;
		ptr->CallChunk[index].function = func;
		ptr->CallChunkEnd++;
	}

	void UI::DeleteElement(PElement element)
	{
		DeleteUi(element, element->GetAs<Header<Child>>()->Parent->Header.Parent);
	};

	void UI::SetCheckbox(PCheckbox checkbox, int value)
	{
		SetCheck(checkbox, checkbox->Value[0], value);
	};

	void UI::SetColorRGBA(PCPicker picker, VecCol Color)
	{
		picker->Value[0] = Color;
		Utils::Callback(&picker);
	};

	void UI::SetColorHSV(PCPicker picker, HSV Color)
	{
		picker->HSV = Color;
		Utils::Callback(&picker);
	};

	void UI::SetSlider(PSlider slider, int value)
	{
		slider->Value[0] = value;
		Utils::Callback(&slider);
	};

	void UI::SetCombobox(PCombobox combobox, int value)
	{
		combobox->SelectedItem = value;
		Utils::Callback(&combobox);
	};

	void UI::SetListbox(PListbox listbox, int value)
	{
		SetList(listbox, value);
		Utils::Callback(listbox);
	};

	void UI::SetHotkey(PHotkey hotkey, int key, HotkeyMode mode)
	{
		SetKey(hotkey, key, 0);
		if (mode != Inherit)
			hotkey->Popup->SetMode(hotkey, hotkey->Popup, mode);
	};

	int UI::ExtractKey(PHotkey hotkey)
	{
		return hotkey->Info->Key >> 2;
	};

	int UI::HotkeyState(PHotkey hotkey)
	{
		return (hotkey->Info->Key >> 1) & 1;
	};

	void UI::RenameElement(PElement element, wchar_t* name, PXorW oldname)
	{
		if (oldname)
			oldname = element->GetAs<Inspector>()->crypted;
		element->GetAs<Inspector>()->crypted = Utils::CryptName(name);
	};

	wchar_t* UI::GetName(PElement element)
	{
		wchar_t name[128];
		Utils::Decrypt(element->GetAs<Slider>()->CryptedName, 2, name, 128);
		return name;
	};

	size_t UI::GetTextbotText(PTextbox tbox, wchar_t* buffer)
	{
		return GetTBoxText(tbox, buffer);
	};

	PElement UI::GetByName(PChild child, const wchar_t* name)
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

	PChild UI::GetChild(Tab tab, size_t index)
	{
		PCTab tabPtr = GetTab(tab);
		if (index < 0 || index >= Utils::ChildsCount(tabPtr)) return NULL;
		return tabPtr->ChildsChunk[index];
	};

	void UI::InsertElement(PChild child, void* element)
	{
		InsertElem(child, 0, element);
		ChildLayout(child);
	};

	PLabel UI::CreateLabel(PChild child, wchar_t* name)
	{
		PLabel ptr = (PLabel)AddLabel(child, 0, name);
		ChildLayout(child);
		return ptr;
	};

	PTextbox UI::CreateTextbox(PChild child, bool sameline, wchar_t* name)
	{
		if (!sameline && name)
			CreateLabel(child, name);
		PTextbox ptr = (PTextbox)Memory::Allocator(sizeof(Textbox));
		TextboxCon(ptr, child);
		InsertElement(child, ptr);
		return ptr;
	};

	PCheckbox UI::CreateCheckbox(PChild child, wchar_t* name, int* value)
	{
		PCheckbox ptr = (PCheckbox)Memory::Allocator(sizeof(Checkbox));
		CheckboxCon(ptr, child, name, value);
		InsertElement(child, ptr);
		return ptr;
	};

	PSlider UI::CreateSlider(PChild child, wchar_t* name, int min, int max, int* value, bool tooltip, wchar_t* tip, float step)
	{
		PSlider ptr = (PSlider)Memory::Allocator(sizeof(Slider));
		unsigned int tipch = 0;
		if (tip != NULL)
			tipch = tip[0] | tip[1] << 16;
		SliderCon(ptr, child, name, min, max, value, tooltip, tipch, step);
		InsertElement(child, ptr);
		return ptr;
	};

	PHotkey UI::CreateHotkey(PChild child, wchar_t* name, bool sameline, int vkey, HotkeyMode mode)
	{
		if (!sameline)
			CreateLabel(child, name);
		PHotkeyInfo info = (PHotkeyInfo)Memory::Allocator(sizeof(HotkeyInfo));
		KeyInit(info);
		PHotkey ptr = (PHotkey)Memory::Allocator(sizeof(Hotkey));
		HotkeyCon(ptr, child, info, true);
		SetHotkey(ptr, vkey, mode);
		InsertElement(child, ptr);
		return ptr;
	};

	// ecx = first parameter that function recive, while second one is always this pointer
	PButton UI::CreateButton(PChild child, wchar_t* name, F2PFn function, void* ecx)
	{
		PButton ptr = (PButton)AddButton(child, NULL, name, ecx, function);
		ChildLayout(child);
		return ptr;
	};

	PCPicker UI::CreateColorPicker(PChild child, VecCol* value, bool sameline, wchar_t* name)
	{
		if (!sameline && name != NULL)
			CreateLabel(child, name);
		PCPicker ptr = (PCPicker)Memory::Allocator(sizeof(ColorPicker));
		CPickerCon(ptr, child, value);
		InsertElement(child, ptr);
		return ptr;
	};

	PCombobox UI::CreateCombobox(PChild child, wchar_t* name, int* value, wchar_t** arr, size_t arrsize, bool sameline)
	{
		PCombobox ptr = (PCombobox)Memory::Allocator(sizeof(Combobox));
		ComboboxCon(ptr, child, name, value, sameline);
		BoxVars<wchar_t>* varlist = (BoxVars<wchar_t>*)Memory::Allocator(sizeof(BoxVars<wchar_t>) * arrsize);
		for (size_t i = 0; i < arrsize; i++)
		{
			size_t bsize = sizeof(wchar_t) * (wcslen(arr[i]) + 1);
			varlist[i].NameChunk = (wchar_t*)Memory::Allocator(bsize);
			memcpy(varlist[i].NameChunk, arr[i], bsize);
			varlist[i].NameChunkEnd = varlist[i].NameChunk + ++bsize / sizeof(wchar_t);
			varlist[i].CpacityEnd = varlist[i].NameChunkEnd;
			varlist[i].Index = i;
		}
		ptr->VarsChunk = varlist;
		ptr->VarsChunkEnd = varlist + arrsize;
		InsertElement(child, ptr);
		return ptr;
	};

	PMultiselect UI::CreateMultiselect(PChild child, wchar_t* name, int* value, char** arr, size_t arrsize, bool sameline)
	{
		PMultiselect ptr = (PMultiselect)Memory::Allocator(sizeof(Multiselect));
		MultiCon(ptr, child, name, value, 0, sameline);
		auto varlist = ptr->Vars;
		for (size_t i = 0; i < arrsize; i++)
		{
			size_t bsize = strlen(arr[i]);
			varlist[i].NameChunk = (char*)Memory::Allocator(bsize);
			memcpy(varlist[i].NameChunk, arr[i], bsize);
			varlist[i].NameChunkEnd = varlist[i].NameChunk + bsize;
			varlist[i].CpacityEnd = varlist[i].NameChunkEnd;
			varlist[i].Index = 1 << i;
		}
		ptr->VarsChunk = varlist;
		ptr->VarsChunkEnd = varlist + arrsize;
		InsertElement(child, ptr);
		return ptr;
	};

	PListbox UI::CreateListbox(PChild child, wchar_t* name, int* value, wchar_t** arr, size_t arrsize, bool searchbox)
	{
		PListbox ptr = (PListbox)Memory::Allocator(sizeof(Listbox));
		ListboxCon(ptr, child, name, 158, 300, value, searchbox);

		wchar_set* set = (wchar_set*)Memory::Allocator(sizeof(wchar_set) * arrsize);
		PSpec spec = (PSpec)Memory::Allocator(sizeof(short) * (arrsize + 1));
		for (size_t i = 0; i < arrsize; i++)
		{
			size_t bsize = (wcslen(arr[i]) + 1) * sizeof(wchar_t);
			set[i].Index = i;
			set[i].NameChunk = (wchar_t*)Memory::Allocator(bsize);
			memcpy(set[i].NameChunk, arr[i], bsize);
			set[i].NameChunkEnd = (void*)((int)set[i].NameChunk + bsize);
			set[i].CapacityEnd = set[i].NameChunkEnd;
			spec->Indexies[i] = i + 1;
		}
		spec->FindedIndex = 0;
		ptr->Info.ItemsChunk = set;
		ptr->Info.ItemsChunkEnd = set + arrsize;
		ptr->ItemsCount = arrsize;
		ptr->SSpecChunk = spec;
		ptr->SSpecChunkEnd = (short*)((int)spec + sizeof(short) * (arrsize + 1));
		ptr->SSpecCapacityEnd = ptr->SSpecChunkEnd;
		InsertElement(child, ptr);
		return ptr;
	};

	void UI::AddListboxVar(PListbox list, wchar_t* elem, size_t bsize)
	{
		if (!list->ItemsCount)
		{
			list->Info.ItemsChunk = (wchar_set*)Memory::Allocator(sizeof(wchar_set) * 255);
			list->Info.ItemsChunkEnd = list->Info.ItemsChunk;
			list->SSpecChunk = (PSpec)Memory::Allocator(sizeof(short) * 256);
			list->SSpecChunkEnd = (short*)((int)list->SSpecChunk + sizeof(short));
		};
		if (!bsize) bsize = (wcslen(elem) + 1) * sizeof(wchar_t);
		list->Info.ItemsChunk[list->ItemsCount].Index = list->ItemsCount;
		list->Info.ItemsChunk[list->ItemsCount].NameChunk = (wchar_t*)Memory::Allocator(bsize);
		memcpy(list->Info.ItemsChunk[list->ItemsCount].NameChunk, elem, bsize);
		list->Info.ItemsChunk[list->ItemsCount].NameChunkEnd = (void*)((int)list->Info.ItemsChunk[list->ItemsCount].NameChunk + bsize);
		list->Info.ItemsChunk[list->ItemsCount].CapacityEnd = list->Info.ItemsChunk[list->ItemsCount].NameChunkEnd;
		list->Info.ItemsChunkEnd++;
		list->SSpecChunk->Indexies[list->ItemsCount] = list->ItemsCount + 1;
		list->SSpecChunkEnd++;
		list->Info.SelectedItem = list->ItemsCount++;
	};

	void UI::RemoveListboxVar(PListbox list, size_t index)
	{
		if (!list->ItemsCount) return;
		list->SSpecChunkEnd--;
		for (size_t i = index; i < list->ItemsCount; i++)
		{
			list->Info.ItemsChunk[i].Index--;
		};
		memcpy(list->Info.ItemsChunk + index, list->Info.ItemsChunk + index + 1, (list->ItemsCount-- - index) * sizeof(wchar_set));
		list->Info.ItemsChunkEnd--;
		list->Info.SelectedItem = list->ItemsCount - 1;
	};

	void UI::InsertChild(PCTab tab, void* child)
	{
		InsertChildr(tab, child);
		tab->ResetLayout();
	};

	PChild UI::CreateChild(PCTab tab, wchar_t* name, Vec4_8t possize, bool modify)
	{
		PChild ptr = (PChild)Memory::Allocator(sizeof(Child));
		ChildCon(ptr, tab, name, possize.pack(), 0, modify);
		InsertChild(tab, ptr);
		return ptr;
	};

	PCTab UI::CreateTab(wchar_t* name, Vec2 pos)
	{
		PCTab ptr = (PCTab)Memory::Allocator(sizeof(CTab));
		TabCon(ptr, Menu, name, pos.array());
		InsertTab(Menu, ptr);
		return ptr;
	};

	template <typename T>
	T* UI::GetElement(PChild child, size_t index)
	{
		return (T*)child->ElementsChunk[index];
	};

#ifdef SDK_RENDERER_IMP
	Memory::CHooked*	Renderer::RenderHook		= NULL;
	Memory::CHooked*	Renderer::MenuRenderHook	= NULL;
	Memory::CHooked*	Renderer::FinalRenderHook	= NULL;
	ReadFileFn			Renderer::ExReadFile		= NULL;
	LoadTextureFn		Renderer::LoadTexture		= NULL;
	LoadSvgFormFileFn	Renderer::LoadSvgFromFile	= NULL;
	RenderIndicatorFn	Renderer::RenderIndicator	= NULL;
	WorldToScreenFn		Renderer::WorldToScreen		= NULL;
	RenderBlurFn		Renderer::RenderBlur		= NULL;
	void*				Renderer::RenderBlurCtx		= NULL;
	sVec<RenderEventListenerFn> Renderer::RenderEvents(40);
	sVec<RenderEventListenerFn> Renderer::MenuEvents(40);
	sVec<RenderEventListenerFn> Renderer::FinalEvents(40);

	// EventListener Implementation
	void EventListener::remove()
	{
		if (!status) return;
		Renderer::RemoveEvent(index, type);
		status = false;
	};

	// Renderer Implementation
	void Renderer::RenderListener(void* ecx, void* edx)
	{
		for (size_t i = 0; i < RenderEvents.len(); i++)
		{
			RenderEvents[i]();
		};
		reinterpret_cast<RenderFn>(RenderHook->Naked())(ecx, edx);
	};

	void Renderer::MenuRenderListener(void* ecx, void* edx)
	{
		for (size_t i = 0; i < MenuEvents.len(); i++)
		{
			MenuEvents[i]();
		};
		reinterpret_cast<RenderFn>(MenuRenderHook->Naked())(ecx, edx);
	};

	void Renderer::RenderFinalListener(void* ecx, void* edx)
	{
		// Set render alpha to 1.f couz menu fading will fade our render as well.
		SCLASS->IRenderer->SetAlpha(1.f);
		SCLASS->IRenderer->SetZBuff(0.0f);
		for (size_t i = 0; i < FinalEvents.len(); i++)
		{
			FinalEvents[i]();
		};
		reinterpret_cast<RenderFn>(FinalRenderHook->Naked())(ecx, edx);
	};

	void Renderer::Init()
	{
		if (RenderHook != NULL) return;
		LoadTexture		= (LoadTextureFn)Memory::CheatChunk.findr32("E8 ?? ?? ?? ?? 84 C0 74 76 8B 4C 24 14");
		LoadSvgFromFile = (LoadSvgFormFileFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 83 EC 28 56 83 CE FF 83 3D ?? ?? ?? ?? 00 57 8B FA");
		RenderIndicator = (RenderIndicatorFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 81 EC 48 40");
		WorldToScreen	= (WorldToScreenFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 F3 0F 10 71");
		RenderBlur		= (RenderBlurFn)Memory::CheatChunk.find("56 8D 71 28 8B 4E 04 8B C1 2B 06 C1 F8 03 3D 00 20 00 00");
		RenderBlurCtx	= **(void***)Memory::CheatChunk.find("8B 0D ?? ?? ?? ?? 83 C4 20 85 C9 74 09 50 55 53 57 E8", 0x2);
		ExReadFile		= (ReadFileFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 83 EC 14 53 56 57 8B F9 B8");
		RenderHook		= Memory::DetourHook::Hook(Memory::CheatChunk.find("55 8B EC 83 E4 F8 E8 ?? ?? ?? ?? 83 38 00 74 36 89 0D"), RenderListener, 6);
		MenuRenderHook	= Memory::DetourHook::Hook(Memory::CheatChunk.find("56 FF 74 24 08 8B F1 E8"), MenuRenderListener);
		FinalRenderHook = Memory::DetourHook::Hook(Memory::CheatChunk.find("53 56 57 8B F9 8B 57 08 8D 82 A8 00 00 00 F7 DA 1B D2 23 D0 52"), RenderFinalListener); // this is also fn2 IRenderer
	};

	void Renderer::Term()
	{
		if (RenderHook == NULL) return;
		RenderEvents.~sVec();
		MenuEvents.~sVec();
		FinalEvents.~sVec();
		RenderHook->Unhook();
		MenuRenderHook->Unhook();
		FinalRenderHook->Unhook();
	};

	EventListener* Renderer::AddEvent(RenderEventType type, RenderEventListenerFn event)
	{
		auto& Events = (type == REVENT_RENDER ? RenderEvents : type == REVENT_MENU ? MenuEvents : FinalEvents);
		Events.push_back(event);
		return new EventListener(Events.len() - 1, type);
	};

	void Renderer::RemoveEvent(size_t index, RenderEventType type)
	{
		(type == REVENT_RENDER ? RenderEvents : type == REVENT_MENU ? MenuEvents : FinalEvents).remove(index);
	};

	Vec2 Renderer::ScreenSize()
	{
		Vec2 size{};
		SCLASS->IRenderer->ScreenSize(&size.x, &size.y);
		return size;
	};

	int Renderer::ScreenWidth()
	{
		int w = 0;
		SCLASS->IRenderer->ScreenSize(&w, NULL);
		return w;
	};

	int Renderer::ScreenHeigth()
	{
		int h = 0;
		SCLASS->IRenderer->ScreenSize(NULL, &h);
		return h;
	};

	Vec2 Renderer::MeasureText(wchar_t* text, unsigned int flags)
	{
		Vec2 vec{};
		SCLASS->IRenderer->MeasureText(reinterpret_cast<int*>(&vec), text, wcslen(text), flags);
		return vec;
	};

	void Renderer::ToScreen(Vec3f_t pos, int* x, int* y)
	{
		WorldToScreen(pos.array(), x, y);
	};

	void Renderer::Text(Vec2 pos, VecCol color, wchar_t* text, int flags, unsigned int maxlen)
	{
		SCLASS->IRenderer->Text(flags, pos.x, pos.y, color.pack(), 0x8 * maxlen, text, wcslen(text));
	};

	void Renderer::Line(Vec2 p1, Vec2 p2, VecCol color)
	{
		SCLASS->IRenderer->Line(p1.x, p1.y, p2.x, p2.y, color.pack());
	};

	void Renderer::Rect(Vec2 pos, Vec2 size, VecCol color)
	{
		SCLASS->IRenderer->Rect(pos.x, pos.y, size.x, size.y, color.pack());

	};

	void Renderer::RectOut(Vec2 pos, Vec2 size, VecCol color, int thickness)
	{
		SCLASS->IRenderer->RectOut(thickness, pos.x, pos.y, size.x, size.y, color.pack());
	};

	void Renderer::OutlinedRect(Vec2 pos, Vec2 size, VecCol colorin, VecCol colorout, int thickness)
	{
		SCLASS->IRenderer->RectOutlined(thickness, pos.x, pos.y, size.x, size.y, colorin.pack(), colorout.pack());
	};

	void Renderer::Gradient(Vec2 pos, Vec2 size, VecCol color1, VecCol color2, bool horizontal)
	{
		if (horizontal)
			SCLASS->IRenderer->GradientH(pos.x, pos.y, size.x, size.y, color1.pack(), color2.pack());
		else
			SCLASS->IRenderer->GradientV(pos.x, pos.y, size.x, size.y, color1.pack(), color2.pack());
	};

	void Renderer::Blur(Vec2 pos, Vec2 size)
	{
		RenderBlur(RenderBlurCtx, pos.x, pos.y, size.x, size.y);
	};

	void Renderer::Triangle(Vec2 p1, Vec2 p2, Vec2 p3, VecCol color)
	{
		SCLASS->IRenderer->Triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.pack());
	};

	void Renderer::Indicator(int y, VecCol color, const char* text, int texureid, float circlepercent)
	{
		RenderIndicator(&y, SCLASS->IRenderer, text, strlen(text), color.pack(), texureid, circlepercent);
	};

	void Renderer::Circle(Vec2 pos, VecCol color, float radius, float rotation, float percentage)
	{
		SCLASS->IRenderer->Circle(pos.x, pos.y, color.pack(), radius, rotation, percentage);

	};

	void Renderer::CircleOut(Vec2 pos, VecCol color, float radius, float rotation, float percentage, float thickness)
	{
		SCLASS->IRenderer->CircleOut(pos.x, pos.y, color.pack(), radius, rotation, percentage, thickness);
	};

	void Renderer::Texture(int id, Vec2 pos, Vec2 size, VecCol color, int flag, int offset, float scale)
	{
		SCLASS->IRenderer->Texture(id, pos.x, pos.y, color.pack(), offset, 0, size.x, size.y, flag, scale);
	};

	CTexture* Renderer::LoadSVGTextureFromFile(const char* filename, int width, int heigth)
	{
		int id = LoadSvgFromFile(filename, width, heigth, -1);
		if (id < 0) return NULL;
		return new CTexture(id, TEXTURE_SVG, width, heigth);
	};

	CTexture* Renderer::LoadPNGTextureFromFile(const char* filename, int width, int heigth)
	{
		DataChunk textureChunk{ 0 };
		DataChunk rawContent{ 0 };
		ExReadFile(&textureChunk, filename);
		if (textureChunk.ChunkStart == textureChunk.ChunkEnd) return NULL;
		if (Renderer::LoadTexture(TEXTURE_PNG, textureChunk.ChunkStart, textureChunk.ChunkEnd - textureChunk.ChunkStart, &width, &heigth, &rawContent))
		{
			int byteSize = (rawContent.ChunkEnd - rawContent.ChunkStart) >> 2;
			if (byteSize != 0) {
				unsigned int* ptr = (unsigned int*)rawContent.ChunkStart;
				for (int i = 0; i < byteSize; ++i)
					ptr[i] = _rotr(_byteswap_ulong(ptr[i]), 8);
			}
			int id = SCLASS->IRenderer->AddTexture(rawContent.ChunkStart, width, heigth, width * heigth * 4, 0, 0);
			if (id < 0) return NULL;
			return new CTexture(id, TEXTURE_PNG, width, heigth);
		}
		return NULL;
	};

	CTexture* Renderer::LoadJPGTextureFromFile(const char* filename, int width, int heigth)
	{
		DataChunk textureChunk{ 0 };
		DataChunk rawContent{ 0 };
		ExReadFile(&textureChunk, filename);
		if (textureChunk.ChunkStart == textureChunk.ChunkEnd) return NULL;
		if (Renderer::LoadTexture(TEXTURE_JPG, textureChunk.ChunkStart, textureChunk.ChunkEnd - textureChunk.ChunkStart, &width, &heigth, &rawContent))
		{
			int byteSize = (rawContent.ChunkEnd - rawContent.ChunkStart) >> 2;
			if (byteSize != 0) {
				unsigned int* ptr = (unsigned int*)rawContent.ChunkStart;
				for (int i = 0; i < byteSize; ++i)
					ptr[i] = _rotr(_byteswap_ulong(ptr[i]), 8);
			}
			int id = SCLASS->IRenderer->AddTexture(rawContent.ChunkStart, width, heigth, width * heigth * 4, 0, 0);
			if (id < 0) return NULL;
			return new CTexture(id, TEXTURE_JPG, width, heigth);
		}
		return NULL;
	};

	CTexture* Renderer::LoadTextureFromMemory(const unsigned char* data, size_t size, TextureType type, int width, int heigth)
	{
		if (size == 0) return NULL;
		int byteSize;
		DataChunk rawContent{ 0 };
		if (type == TEXTURE_RGBA)
		{
			if (width * heigth * 4 != size) return NULL;
			rawContent.ChunkStart = const_cast<unsigned char*>(data);
			byteSize = width * heigth;
		}
		else
		{
			if (!Renderer::LoadTexture(type, data, size, &width, &heigth, &rawContent))
				return NULL;
			byteSize = (rawContent.ChunkEnd - rawContent.ChunkStart) >> 2;
		}

		if (byteSize == 0) return NULL;
		unsigned int* ptr = (unsigned int*)rawContent.ChunkStart;
		for (int i = 0; i < byteSize; ++i)
			ptr[i] = _rotr(_byteswap_ulong(ptr[i]), 8);
		int id = SCLASS->IRenderer->AddTexture(rawContent.ChunkStart, width, heigth, width * heigth * 4, 0, 0);
		if (id < 0) return NULL;
		return new CTexture(id, type, width, heigth);
	};
#endif // SDK_RENDERER_IMP
#if defined(SDK_GLOBALS_IMP) || defined(SDK_CLIENT_IMP)
	void**** CEngine::EngineCtx = *(void*****)Memory::CheatChunk.find("8B 0D ?? ?? ?? ?? 8D 94 24 B0 02 00 00 52 57", 0x2);
	CommandsInfo** CEngine::CommandsCtx = *(CommandsInfo***)Memory::CheatChunk.find("8B 3D ?? ?? ?? ?? 8B 48 04 3B 0F 7E 07", 0x2);
	SetClanTagFn CEngine::SetTag = **(SetClanTagFn**)Memory::CheatChunk.find("C6 41 0F 00 FF 15 ?? ?? ?? ?? 66 C7 46 20 01 00 EB 4D", 0x6);
	unsigned int* CEngine::PredComm = *(unsigned int**)Memory::CheatChunk.find("A3 ?? ?? ?? ?? E8 ?? ?? ?? ?? 59 85 C0 7E 1D 8B 4D 08 8D 85 00 F0 FF FF", 0x1);

	bool CEngine::IsInGame()
	{
		return Memory::VtableBind<bool(__cdecl*)()>(**EngineCtx, 0x1A)();
	};

	char* CEngine::MapName()
	{
		if (!IsInGame())
			return NULL;
		return Memory::VtableBind<char* (__cdecl*)()>(**EngineCtx, 0x35)();
	};

	void CEngine::ExecCommand(const char* command)
	{
		Memory::VtableBind<void(__stdcall*)(const char*)>(**EngineCtx, 0x6C)(command);
	};

	void CEngine::SetClanTag(const char* tag)
	{
		if (!Memory::VtableBind<bool(__cdecl*)()>(**EngineCtx, 0x52)() && !Memory::VtableBind<bool(__cdecl*)()>(**EngineCtx, 0x5D)())
		{
			if ((*CEngine::CommandsCtx)->LastOutCommand != *PredComm)
			{
				*PredComm = (*CEngine::CommandsCtx)->LastOutCommand;
				SetTag(tag, tag);
			};
		};
	};
#endif // SDK_GLOBALS_IMP || SDK_CLIENT_IMP

#ifdef SDK_GLOBALS_IMP
	GlobalsInfo** Globals::GlobalsCtx = *(GlobalsInfo***)Memory::CheatChunk.find("8B 0D ?? ?? ?? ?? 8B 54 24 20 D8 71 20", 0x2);
	bool Globals::IsInGame()
	{
		return CEngine::IsInGame();
	};

	char* Globals::MapName()
	{
		return CEngine::MapName();
	};

	float Globals::RealTime()
	{
		return (*GlobalsCtx)->RealTime;
	};

	float Globals::FrameTime(bool abs)
	{
		if (abs)
			return (*GlobalsCtx)->AbsFrameTime;
		else
			return (*GlobalsCtx)->FrameTime;
	};

	int Globals::FrameCount()
	{
		return (*GlobalsCtx)->FrameCount;
	};

	float Globals::CurrentTime()
	{
		return (*GlobalsCtx)->CurrentTime;
	};

	float Globals::TickInterval()
	{
		return (*GlobalsCtx)->TickInterval;
	};

	unsigned int Globals::TickCount()
	{
		return (*GlobalsCtx)->TickCount;
	};

	int Globals::MaxPlayers()
	{
		return (*GlobalsCtx)->MaxPlayers;
	};

	unsigned int Globals::LastOutCommand()
	{
		return (*CEngine::CommandsCtx)->LastOutCommand;
	};

	unsigned int Globals::ChokedCommands()
	{
		return (*CEngine::CommandsCtx)->ChokedCommands;
	};

	unsigned int Globals::OldCommandAck()
	{
		return (*CEngine::CommandsCtx)->OldCommandAck;
	};

	unsigned int Globals::CommandAck()
	{
		return (*CEngine::CommandsCtx)->CommandAck;
	};
#endif // SDK_GLOBALS_IMP

#ifdef SDK_CLIENT_IMP
	LogFn		Client::Logger			= (LogFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 83 EC 20 80");
	LogErrorFn	Client::LoggerError		= (LogErrorFn)Memory::CheatChunk.find("55 8B EC 83 E4 F8 81 EC 40 20");
	void***		Client::LoggerCtx		= **(void*****)Memory::CheatChunk.find("A1 ?? ?? ?? ?? 83 C4 0C 8B 08 56 68 ?? ?? ?? ?? 50 FF 51 68", 0x1);
	ScreenLogFn	Client::ScreenLogger	= (ScreenLogFn)Memory::CheatChunk.find("56 8B F1 8B 0D CC");

	void Client::Exec(const char* cmd)
	{
		CEngine::ExecCommand(cmd);
	};

	void Client::SetClanTag(const char* tag)
	{
		CEngine::SetClanTag(tag);
	};

	void Client::LogScreen(const char* text, VecCol color)
	{
		ScreenLogger(text, color.pack());
	};

	void Client::Log(const char* fmt, ...)
	{
		char buffer[975];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buffer, sizeof(buffer), fmt, args);
		va_end(args);
		Logger(buffer);
	};
	void Client::LogColor(VecCol Color, const char* fmt, ...)
	{
		int col = Color.pack();
		va_list vargs;
		va_start(vargs, fmt);
		char msg[989];
		vsprintf(msg, fmt, vargs);
		va_end(vargs);
		((LogColorFn)LoggerCtx[0][0x19])(LoggerCtx, &col, msg);
	};
	void Client::LogError(const char* fmt, ...)
	{
		va_list vargs;
		va_start(vargs, fmt);
		char msg[975];
		vsprintf(msg, fmt, vargs);
		va_end(vargs);
		LoggerError(msg);
	};
#endif // SDK_CLIENT_IMP
};
#endif // SKEET_H
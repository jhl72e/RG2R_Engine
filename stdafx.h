#pragma once
#pragma warning(disable: 4244 4098 4099 4996)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

using Radian = float; // Radian은 float임
using Degree = float; // Degree도 float임

//엔진에서 사용할 사운드 ID 설정
enum SoundID {
	SIDIntro,
	SIDBgm,
	SIDShoot,
};

#define C_STR_BUFFER_SIZE 256

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC

#endif
#include<crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include<Windows.h>
#include<assert.h>
#include<iostream>
#include<algorithm>
#include<functional>
#include<list>
#include<vector>
#include<map>
#include<unordered_map>
#include<random>
#include<typeindex>
#include<variant>
#include<string>
#include<iomanip>
#include<filesystem>
#include<codecvt>
#include<exception>
#include<xaudio2.h>
#include<d2d1.h>
#include<d2d1effects.h>
#include<d2d1_1helper.h>
#include<d3d11.h>
#include<dxgi1_2.h>
#include<dwrite.h>
#include<dinput.h>
#include<wincodec.h>
#include<codec.h>
#include<vorbisfile.h>
#include<mmsystem.h>
#include<dsound.h>

template <typename T>
inline void SafeDelete(T*& p)
{
	delete p;
	p = static_cast<T *>(NULL);
};

inline HRESULT Trace(const std::string& file, DWORD line, HRESULT hr, const std::string& msg)
{
	std::cout << "File : " << file << "\nLine : " << std::to_string(line) << "\nResult : 0x" << std::setfill('0') << std::setw(8) << std::hex << hr << "\nMessage : " << msg << "\n";
	return hr;
}

inline void ApplyListener(std::function<void()> listener)
{
	if (listener != NULL)
		listener();
}

template <typename T>
inline void Log_error(T log)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xc);
	std::cout << "(ERROR) " << log << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
}

template <typename T>
inline void Log_info(T log)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	std::cout << "(INFO) " << log << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
}

template <typename T>
inline void Log(T log)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	std::cout << "(LOG) " << log << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
}

#define HR(hr) if(FAILED(hr)) Trace(__FILE__, __LINE__, hr, "Error")
#define HR_MSG(hr, msg) if(FAILED(hr)) Trace(__FILE__, __LINE__, hr, msg)

#ifndef _DEBUG
template<class Facet>
struct deletable_facet : Facet
{
	template<class ...Args>
	deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
	~deletable_facet() {}
};
#endif

inline std::wstring Widen(const std::string& str)
{
#ifdef _DEBUG
	wchar_t wstr[C_STR_BUFFER_SIZE];
	MultiByteToWideChar(CP_ACP, NULL, str.c_str(), -1, wstr, C_STR_BUFFER_SIZE);
	return wstr;
#else
	typedef deletable_facet<std::codecvt_byname<wchar_t, char, std::mbstate_t>>
		local_facet_t; std::wstring_convert<local_facet_t> wconv(new local_facet_t(""));
	return wconv.from_bytes(str);
#endif
}
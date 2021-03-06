//  Copyright (c) 2009-2015 Fredrik Mellbin
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include "avsutils.h"
#include <string>
#include <algorithm>

extern "C" {
#include <libswscale/swscale.h>
}

#define _stricmp strcasecmp

// Just disable this without removal, so there's an out if the main
// implementation in src/core/utils.cpp ever goes away.
// AvxSynth's resizers are threaded through FFMS2's SWScale()
// function.
#if AVX_SWS_LEGACY
static AVPixelFormat CSNameToPIXFMT(const char *CSName, AVPixelFormat Default) {
	if (!CSName)
		return AV_PIX_FMT_NONE;
	std::string s = CSName;
	std::transform(s.begin(), s.end(), s.begin(), toupper);
	if (s == "")
		return Default;
	if (s == "YV12")
		return AV_PIX_FMT_YUV420P;
	if (s == "YUY2")
		return AV_PIX_FMT_YUYV422;
	if (s == "RGB24")
		return AV_PIX_FMT_BGR24;
	if (s == "RGB32")
		return AV_PIX_FMT_RGB32;
	return AV_PIX_FMT_NONE;
}

int ResizerNameToSWSResizer(const char *ResizerName) {
	if (!ResizerName)
		return 0;
	std::string s = ResizerName;
	std::transform(s.begin(), s.end(), s.begin(), toupper);
	if (s == "FAST_BILINEAR")
		return SWS_FAST_BILINEAR;
	if (s == "BILINEAR")
		return SWS_BILINEAR;
	if (s == "BICUBIC")
		return SWS_BICUBIC;
	if (s == "X")
		return SWS_X;
	if (s == "POINT")
		return SWS_POINT;
	if (s == "AREA")
		return SWS_AREA;
	if (s == "BICUBLIN")
		return SWS_BICUBLIN;
	if (s == "GAUSS")
		return SWS_GAUSS;
	if (s == "SINC")
		return SWS_SINC;
	if (s == "LANCZOS")
		return SWS_LANCZOS;
	if (s == "SPLINE")
		return SWS_SPLINE;
	return 0;
}
#endif // AVX_SWS_LEGACY

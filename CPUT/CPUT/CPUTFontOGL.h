/////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CPUTFONTOGL_H__
#define __CPUTFONTOGL_H__

#include "CPUT.h"
#include "CPUTRefCount.h"
#include "CPUTFont.h"

class CPUTTextureOGL;



class CPUTFontOGL : public CPUTFont
{
protected:
    ~CPUTFontOGL(); // Destructor is not public.  Must release instead of delete.

public:
    CPUTFontOGL();
    static CPUTFont *CreateFont( cString FontName, cString AbsolutePathAndFilename);

    CPUTTextureOGL *GetAtlasTexture();
//    ID3D11ShaderResourceView *GetAtlasTextureResourceView();


private:
    CPUTTextureOGL            *mpTextAtlas;
//    ID3D11ShaderResourceView   *mpTextAtlasView;

    
    CPUTResult LoadGlyphMappingFile(const cString fileName);



    

};

#endif // #ifndef __CPUTFONTOGL_H__
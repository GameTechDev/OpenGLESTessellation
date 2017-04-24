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
#include "CPUTFont.h"
#include "CPUTOSServices.h"
#include "CPUTTexture.h"
#include "CPUTGuiController.h"
#include "CPUTAssetLibrary.h"
#ifdef CPUT_FOR_DX11
	#include "CPUTFontDX11.h"
#elif (defined(CPUT_FOR_OGL) || defined(CPUT_FOR_OGLES))
	// #include "CPUTFontOGL.h"
#else
	#error You must supply a target graphics API (ex: #define CPUT_FOR_DX11), or implement the target API for this file.
#endif

#ifdef CPUT_FOR_DX11

int gFontMap_active[] =
{
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',            // lower
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',            // upper
    '1','2','3','4','5','6','7','8','9','0',                                                                            // numbers
    ',', '.','/',';','\'','[',']','\\','`','~','!','@','#','$','%','^','&','*','(',')','_','+','{','}','|',':','\"','<','>','?','-','=', // symbols
    ' ','\t',                                                                                                                // space, tab
    -1
};

//-----------------------------------------------------------------------------
CPUTFont *CPUTFont::CreateFont( cString FontName, cString AbsolutePathAndFilename )
{
    // TODO: accept DX11/OGL param to control which platform we generate.
    // TODO: be sure to support the case where we want to support only one of them
#ifdef CPUT_FOR_DX11
    return CPUTFontDX11::CreateFont( FontName, AbsolutePathAndFilename );
#elif (defined(CPUT_FOR_OGL) || defined(CPUT_FOR_OGLES))
	return NULL;
	// return CPUTFontOGL::CreateFont( FontName, AbsolutePathAndFilename );
#else
	return NULL;
//    #error You must supply a target graphics API (ex: #define CPUT_FOR_DX11), or implement the target API for this file.
#endif

assert(0);
return NULL;
}

// return the size in pixels of the glyph
//-----------------------------------------------------------------------------
CPUT_SIZE CPUTFont::GetGlyphSize(const char c)
{    
    CPUT_SIZE size;
    size.height=0;
    size.width=0;

    int index = FindGlyphIndex(c);
    if(-1!=index)
    {
#ifdef CPUT_OS_ANDROID
#warning "Need to do something with to really scale based on DPI"
        size.width=mpGlyphSizes[index].width*2;
        size.height=mpGlyphSizes[index].height*2;
#else
        size.width=mpGlyphSizes[index].width;
        size.height=mpGlyphSizes[index].height;
#endif
    }

    return size;
}

// return the uv coordinates for the given glyph
// upper left/lower right
//-----------------------------------------------------------------------------
void CPUTFont::GetGlyphUVS(const char c, const bool bEnabledVersion, float3 &UV1, float3 &UV2)
{
    int index = FindGlyphIndex(c);
    if(-1!=index)
    {
        if(bEnabledVersion)
        {
            UV1.x=mpGlyphUVCoords[4*index+0];
            UV1.y=mpGlyphUVCoords[4*index+1];
            UV2.x=mpGlyphUVCoords[4*index+2];
            UV2.y=mpGlyphUVCoords[4*index+3];        
        }
        else
        {
            UV1.x=mpGlyphUVCoordsDisabled[4*index+0];
            UV1.y=mpGlyphUVCoordsDisabled[4*index+1];
            UV2.x=mpGlyphUVCoordsDisabled[4*index+2];
            UV2.y=mpGlyphUVCoordsDisabled[4*index+3];   
        }
    }    
}

// find the index of the glyph that corresponds to the char passed in
//-----------------------------------------------------------------------------
int CPUTFont::FindGlyphIndex(const char c)
{
    int index=0;
    while(-1 != gFontMap_active[index])
    {
        if(c == gFontMap_active[index])
        {
            return index;
        }
        index++;
    }

    // not found
    return -1;
}

#else

CPUTFont *CPUTFont::CreateFont(cString FontName, cString AbsolutePathAndFilename)
{
#ifdef UNICODE
    char *pName = ws2s(FontName);
    char *pPath = ws2s(AbsolutePathAndFilename);
    CPUTFont *pFont;
    pFont = CPUTFont::LoadFont( pName, pPath );
    delete pName;
    delete pPath;

    return pFont;
#else
    return CPUTFont::LoadFont( FontName, AbsolutePathAndFilename );
#endif
}

CPUTFont *CPUTFont::LoadFont(const std::string& pPath, const std::string& pFileName)
{
    UINT      fileSize   = 0;
    uint8_t  *pData      = NULL;
    uint32_t  currentPos = 0;

    CPUTFont *pNewFont = new CPUTFont();
    //
    // Load font file contents into a local buffer for processing
    //
    std::string fontDescriptionFile(pPath + pFileName);
    CPUTFileSystem::ReadFileContents(fontDescriptionFile.c_str(), &fileSize, (void **) &pData, false, true);

    //
    // Validate the header info for the file
    //
    uint8_t fileIdentifier[3];

    fileIdentifier[0] = *(pData + currentPos++);
    fileIdentifier[1] = *(pData + currentPos++);
    fileIdentifier[2] = *(pData + currentPos++);

    if ((fileIdentifier[0] != 66) || (fileIdentifier[1] != 77) || (fileIdentifier[2] != 70)) {
        DEBUG_PRINT("File Identifier not valid for a BMFont binary file.");
        return NULL;
    }

    uint8_t version;
    version = *(pData + currentPos++);
    if (version != 3) {
        DEBUG_PRINT("BMFont file is not the correct version. Must be version 3.");
        return NULL;
    }

    //
    // Load the various blocks of the BMFont file
    //
    while (currentPos < fileSize) {
        uint8_t  blockType;
        uint32_t blockSize;
        blockType = *(pData + currentPos++);
        memcpy(&blockSize, pData + currentPos, 4);
        currentPos += 4;

        switch (blockType) {
        case 1:
            pNewFont->mpFontInfo = (BMFontInfo *) malloc(blockSize); 
            memcpy(pNewFont->mpFontInfo, pData + currentPos, blockSize);
            currentPos += blockSize;
            break;
        case 2:
            pNewFont->mpFontCommon = (BMFontCommon *) malloc(blockSize);
            memcpy(pNewFont->mpFontCommon, pData + currentPos, blockSize);
            currentPos += blockSize;
            break;
        case 3:
            pNewFont->mpFontPages = (BMFontPages *) malloc(blockSize);
            memcpy(pNewFont->mpFontPages, pData + currentPos, blockSize);
            currentPos += blockSize;
            break;
        case 4:
            pNewFont->mNumChars = blockSize / 20; // could do a check to make sure the block size is evenly divided by 20
            pNewFont->mpFontChars = (BMFontChars *) malloc(blockSize);
            memcpy(pNewFont->mpFontChars, pData + currentPos, blockSize);
            currentPos += blockSize;
            break;
        case 5:
            pNewFont->mNumKerningPairs = blockSize / 10; // could do a check to make sure the block size is evenly divided by 20
            pNewFont->mpFontKerningPairs = (BMFontKerningPairs *) malloc(blockSize);
            memcpy(pNewFont->mpFontKerningPairs, pData + currentPos, blockSize);
            {
            int testSize = sizeof(BMFontKerningPairs);
            
            currentPos += blockSize;
            }
            break;
        default:
            DEBUG_PRINT("Invalid block type");
            break;
        }
    }

    delete pData;

    //
    // Load the atlas for the font
    //

 //   cString atlasFile(s2cs(pNewFont->mpFontPages->pageNames));
 //   cString path(s2cs(pPath));

 //   pNewFont->pTextureAtlas = CPUTTexture::CreateTexture(atlasFile, path + atlasFile, false);

    // add font to the asset library
    CPUTAssetLibrary::GetAssetLibrary()->AddFont( s2cs(pFileName), _L(""), _L(""), pNewFont);

    return pNewFont;
}

void CPUTFont::LayoutText(CPUTGUIVertex *pVtxBuffer, int *pWidth, int *pHeight, const std::string& text, int tlx, int tly)
{
    int x = tlx, y = tly;
    BMFontChars *pPreviousChar = NULL;

    for (int j = 0, index = 0; j < text.length(); j++) {
        int charIndex = -1;
        for (int i = 0; i < mNumChars; i++) {
            if (((BMFontChars *)(((uint8_t *)(mpFontChars)) + (20 * i)))->id == text[j]) {
                charIndex = i;
            }
        }
        if (charIndex == -1) {
            DEBUG_PRINT("Invalid character being searched for %c", text[j]);
        }
        BMFontChars *pChar = ((BMFontChars *)(((uint8_t *)(mpFontChars)) + (20 * charIndex)));

        int kernAmount = 0;
        if (pPreviousChar != NULL) {
            for (int i = 0; i < mNumKerningPairs; i++) {
                if ((((BMFontKerningPairs *)(((uint8_t *)(mpFontKerningPairs)) + (10 * i)))->first == pPreviousChar->id) &&
                   (((BMFontKerningPairs *)(((uint8_t *)(mpFontKerningPairs)) + (10 * i)))->second == pChar->id)) {
                    kernAmount = ((BMFontKerningPairs *)(((uint8_t *)(mpFontKerningPairs)) + (10 * i)))->amount;
                }
            }
        }
        pPreviousChar = pChar;

        CPUTColor4 redColor;
        redColor.r = redColor.a = 1.0f;
        redColor.g = redColor.b = 1.0f;

        float texWidth = (float) mpFontCommon->scaleW;
        float texHeight = (float) mpFontCommon->scaleH;
        pVtxBuffer[index+0].Pos   = float3( x + 0.0f + pChar->xoffset + kernAmount, y + 0.0f + pChar->yoffset, 1.0f);
        pVtxBuffer[index+0].UV    = float2(pChar->x / texWidth, pChar->y / texHeight);
        pVtxBuffer[index+0].Color = redColor;

        pVtxBuffer[index+1].Pos   = float3( x + pChar->width + pChar->xoffset + kernAmount, y + 0.0f + pChar->yoffset, 1.0f);
        pVtxBuffer[index+1].UV    = float2((pChar->x + pChar->width) / texWidth, pChar->y / texHeight);
        pVtxBuffer[index+1].Color = redColor;

        pVtxBuffer[index+2].Pos   = float3( x + 0.0f + pChar->xoffset + kernAmount, y + pChar->height + pChar->yoffset, 1.0f);
        pVtxBuffer[index+2].UV    = float2(pChar->x / texWidth, (pChar->y + pChar->height) / texHeight);
        pVtxBuffer[index+2].Color = redColor;

        pVtxBuffer[index+3].Pos   = float3( x + pChar->width + pChar->xoffset + kernAmount, y + 0.0f + pChar->yoffset, 1.0f);
        pVtxBuffer[index+3].UV    = float2((pChar->x + pChar->width) / texWidth, pChar->y / texHeight);
        pVtxBuffer[index+3].Color = redColor;

        pVtxBuffer[index+4].Pos   = float3( x + pChar->width + pChar->xoffset + kernAmount, y + pChar->height + pChar->yoffset, 1.0f);
        pVtxBuffer[index+4].UV    = float2((pChar->x + pChar->width) / texWidth, (pChar->y + pChar->height) / texHeight);
        pVtxBuffer[index+4].Color = redColor;

        pVtxBuffer[index+5].Pos   = float3( x + 0.0f + pChar->xoffset + kernAmount, y + pChar->height + pChar->yoffset, 1.0f);
        pVtxBuffer[index+5].UV    = float2(pChar->x / texWidth, (pChar->y + pChar->height) / texHeight);
        pVtxBuffer[index+5].Color = redColor;

        x += pChar->xadvance + kernAmount;
        index += 6;
    }

    *pWidth = x - tlx;
    *pHeight = mpFontCommon->lineHeight;
}

// return the uv coordinates for the given glyph
// upper left/lower right
//-----------------------------------------------------------------------------
void CPUTFont::GetGlyphUVS(const char c, const bool bEnabledVersion, float3 &UV1, float3 &UV2)
{
    int charIndex = -1;
    for (int i = 0; i < mNumChars; i++) {
        if (((BMFontChars *)(((uint8_t *)(mpFontChars)) + (20 * i)))->id == c) {
            charIndex = i;
        }
    }
    BMFontChars *pChar = ((BMFontChars *)(((uint8_t *)(mpFontChars)) + (20 * charIndex)));

    if(charIndex != -1)
    {
        UV1.x = (pChar->x) / 256.0f;
        UV1.y = (pChar->y) / 256.0f;
        UV2.x = (pChar->x + pChar->width) / 256.0f;
        UV2.y = (pChar->y + pChar->height) / 256.0f;
    } else {
        DEBUG_PRINT("Invalid character being searched for");
    }
}

// return the size in pixels of the glyph
//-----------------------------------------------------------------------------
CPUT_SIZE CPUTFont::GetGlyphSize(const char c)
{    
    CPUT_SIZE size;
    size.height=0;
    size.width=0;

    int charIndex = -1;
    for (int i = 0; i < mNumChars; i++) {
        if (((BMFontChars *)(((uint8_t *)(mpFontChars)) + (20 * i)))->id == c) {
            charIndex = i;
        }
    }
    BMFontChars *pChar = ((BMFontChars *)(((uint8_t *)(mpFontChars)) + (20 * charIndex)));

    if(charIndex != -1)
    {
#ifdef CPUT_OS_ANDROID
#warning "Need to do something with to really scale based on DPI"
        size.width=pChar->width * 2;
        size.height=pChar->height * 2;
#else
        size.width=pChar->width;
        size.height=pChar->height;
#endif
    } else {
        DEBUG_PRINT("Invalid character being searched for");
    }

    size.width = 12;
    size.height = 12;

    return size;
}

CPUTFont::~CPUTFont()
{
    SAFE_DELETE(mpFontInfo);
    SAFE_DELETE(mpFontCommon);
    SAFE_DELETE(mpFontPages);
    SAFE_DELETE(mpFontChars);
    SAFE_DELETE(mpFontKerningPairs);

    SAFE_RELEASE(pTextureAtlas);
}

#endif CPUT_FOR_DX11
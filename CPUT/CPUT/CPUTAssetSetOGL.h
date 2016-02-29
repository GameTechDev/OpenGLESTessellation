//--------------------------------------------------------------------------------------
// Copyright 2011 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
//--------------------------------------------------------------------------------------
#ifndef CPUTASSETSETOGL_H
#define CPUTASSETSETOGL_H

#include "CPUTAssetSet.h"

class CPUTAssetSetOGL : public CPUTAssetSet
{
public:
    static CPUTAssetSet *CreateAssetSet( const cString &name, const cString &absolutePathAndFilename, int numSystemMaterials=0, cString *pSystemMaterialNames=NULL );

    CPUTAssetSetOGL() : CPUTAssetSet() {}
    virtual ~CPUTAssetSetOGL();
    virtual CPUTResult LoadAssetSet(cString name, int numSystemMaterials=0, cString *pSystemMaterialNames=NULL);
};

#endif // #ifndef __CPUTASSETSETOGL_H__
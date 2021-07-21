#ifndef ONF_H_
#define ONF_H_

#include "VersionNames.h"

#define ONF_VER         ONF_VER_0_0
#define ONF_VER_PATCH   0x0000


namespace ONF
{
    template<class T>
    inline T
    onf_abs(T value) {
        return value < 0 ? -value : value;
    }
}


#include "IdManager.h"
#include "Console_IO.h"
#include "XmlSave/SaveModule.h"
#include "XmlSave/TagStructure.h"
#include "XmlSave/XmlFilter.h"

#endif

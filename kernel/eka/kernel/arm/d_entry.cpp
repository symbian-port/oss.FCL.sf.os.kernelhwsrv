// Copyright (c) 1998-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of the License "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// e32\kernel\arm\d_entry.cpp
// 
//

#include <kernel/klib.h>

GLREF_C TInt KernelModuleEntry(TInt);

extern "C" {

#if defined(__GCC32__)

#if defined(__EABI__) || defined(__ARM_EABI__)
extern "C" void __call_init_array();
#else
typedef void (*PFV)();
extern PFV __CTOR_LIST__[];
extern PFV __DTOR_LIST__[];
#endif

GLDEF_C TInt _E32Dll_Body(TInt aReason)
//
// Call global constructors or destructors
//
	{
	if (aReason==KModuleEntryReasonProcessDetach)
		{
#if !defined(__EABI__) && !defined(__ARM_EABI__)
		TUint i=1;
		while (__DTOR_LIST__[i])
			(*__DTOR_LIST__[i++])();
#endif
		return KErrNone;
		}
	if (aReason==KModuleEntryReasonExtensionInit1 || aReason==KModuleEntryReasonProcessAttach)
		{
#if defined(__EABI__) || defined(__ARM_EABI__)
		__call_init_array();
#else
		TUint i=1;
		while (__CTOR_LIST__[i])
			(*__CTOR_LIST__[i++])();
#endif
		}
	return KernelModuleEntry(aReason);
	}

#elif defined(__ARMCC__)

void __DLL_Export_Table__(void);
void __cpp_initialize__aeabi_(void);
__weak void run_static_dtors(void);

GLDEF_C TInt _E32Dll_Body(TInt aReason)
//
// Call global constructors or destructors
//
	{
	if (aReason==KModuleEntryReasonProcessDetach)
		{
		int call_static_dtors = (int)run_static_dtors;
		if (call_static_dtors) run_static_dtors();
		return KErrNone;
		}
	if (aReason==KModuleEntryReasonExtensionInit1 || aReason==KModuleEntryReasonProcessAttach)
		{
		__DLL_Export_Table__();
		__cpp_initialize__aeabi_();
		}
	return KernelModuleEntry(aReason);
	}

#else
#error not supported
#endif

}


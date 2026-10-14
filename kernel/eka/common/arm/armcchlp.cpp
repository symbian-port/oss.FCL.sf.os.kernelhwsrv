// Copyright (c) 1995-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// e32\nklib\arm\armcchelp.cpp
// 
//

#include "../common.h"
#include <nkern.h>

extern "C" {
EXPORT_C int __aeabi_idiv0 (int return_value)
    {
      FAULT();
      return return_value;
    }

EXPORT_C long long __aeabi_ldiv0 (long long return_value)
    {
      FAULT();
      return return_value;
    }

EXPORT_C int __cxa_pure_virtual()
//
// Gets called for any unreplaced pure virtual methods.
//
	{
#ifdef __STANDALONE_NANOKERNEL__
	__NK_ASSERT_ALWAYS(0);
#else
	Panic(EPureVirtualCalled);
#endif
	return 0;
	}

EXPORT_C int __cxa_guard_acquire(int* aGuard)
	{
	if (*(char*)aGuard == 0)
		return 1;
	return 0;
	}

EXPORT_C void __cxa_guard_release(int* aGuard)
	{
	*(char*)aGuard = 1;
	}

EXPORT_C void __cxa_guard_abort(int* /*aGuard*/)
	{
	}

#ifdef __KERNEL_MODE__

void __cxa_end_catch(){}

void __cxa_begin_catch(){}

void __cxa_rethrow(){}
// std::terminate

void __cxa_call_unexpected() {}

void __aeabi_unwind_cpp_pr0() {}

void __cxa_end_cleanup() {}

#if defined(__GCCE__) || defined(__EABI__)
extern "C" {
__attribute__((visibility("default"))) const void* _ZTVN10__cxxabiv117__class_type_infoE[8] = { 0 };
__attribute__((visibility("default"))) const void* _ZTVN10__cxxabiv120__si_class_type_infoE[8] = { 0 };
__attribute__((visibility("default"))) const void* _ZTVN10__cxxabiv121__vmi_class_type_infoE[8] = { 0 };

EXPORT_C void abort()
{
#ifdef __STANDALONE_NANOKERNEL__
	__NK_ASSERT_ALWAYS(0);
#else
	Panic(EPureVirtualCalled);
#endif
}
}
#endif

#endif
}


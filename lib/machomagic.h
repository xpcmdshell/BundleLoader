#pragma once
#include "debug.h"
#include <mach-o/dyld.h>
#include <mach/mach_vm.h>

/**
 * LoadBundleFromMemory takes a mach-o bundle blob and does mach-o loading and
 *linking.
 * TODO: Detect if the object file supplied is of type MH_DYLIB instead of
 *MH_BUNDLE and try to patch the type so that we can load it. Return: NSModule
 *reference to the loaded && linked bundle
 **/
NSModule LoadBundleFromMemory(unsigned char* macho_blob, unsigned long blob_size, const char* bundle_name)
{
    NSObjectFileImage payload_image;
    NSObjectFileImageReturnCode ret = NSCreateObjectFileImageFromMemory(macho_blob, blob_size, &payload_image);
    if (ret != NSObjectFileImageSuccess) {

        DebugPrint("Failed to create object file image from memory blob: %d\n", ret);
        return NULL;
    }
    DebugPrint("[*] Created object file image from memory blob\n");
    NSModule object_module = NSLinkModule(payload_image, bundle_name, NSLINKMODULE_OPTION_PRIVATE);
    if (!object_module) {
        DebugPrint("Module linking failure\n");
        return NULL;
    }
    DebugPrint("[*] Linked module in memory\n");
    return object_module;
}

/**
 * CallFunctionFromBundle takes a module that has been loaded and linked by
 * LoadbundleFromMemory and calls a function by name from it's symbol table.
 *
 * Return: 0 for failure, nonzero for success
 **/
int CallFunctionFromBundle(NSModule object_module, char* function_name)
{
    NSSymbol symbol = NSLookupSymbolInModule(object_module, function_name);
    if (!symbol) {
        DebugPrint("[-] Failed to locate function symbol: %s\n", function_name);
        return 0;
    }
    int (*func)() = NSAddressOfSymbol(symbol);
    if (!func) {
        return 0;
    }
    DebugPrint("[*] Located function symbol at %p\n", func);
    return func();
}
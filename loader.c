/*
    Author: actae0n
    Description: This loader showcases an example of how to load and link a mach-o bundle in
    memory, and call a function by name from it. 
*/

#include "lib/machomagic.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{

    NSModule loaded_bundle = NULL;
    FILE* fp = NULL;
    char* full_path = NULL;
    struct stat f_info = { 0 };
    void* mod_buf = NULL;
    int func_ret = 0;

    // Print usage / help
    if (argc < 3) {
        DebugPrint("Usage: %s bundlefile function_name\n", argv[0]);
        return -1;
    }

    // Expand path
    full_path = realpath(argv[1], NULL);
    if (!full_path) {
        DebugPrint("[-] Failed to expand path\n");
        return -1;
    }

    // Get size of bundle to load
    if (stat(full_path, &f_info)) {
        DebugPrint("[-] Failed to stat file.\n");
        return -1;
    }

    // Allocate some memory to load the bundle into
    mod_buf = calloc(1, f_info.st_size);
    if (!mod_buf) {
        DebugPrint("[-] Failed to allocate buffer for module\n");
        return -1;
    }
    fp = fopen(full_path, "r");
    if (!fp) {
        DebugPrint("[-] Failed to open module %s for reading\n", argv[1]);
        return -1;
    }

    // Read the bundle into memory
    if (!fread(mod_buf, f_info.st_size, 1, fp)) {
        DebugPrint("[-] Failed to read module into memory\n");
        return -1;
    }

    // Load and link bundle in memory
    loaded_bundle = LoadBundleFromMemory(mod_buf, f_info.st_size, "mybundle");
    if (!loaded_bundle) {
        DebugPrint("Failed to load %s. Are you sure it's a bundle?\n", full_path);
        return -1;
    }

    // Call function with prototype `int func()` from bundle in memory
    func_ret = CallFunctionFromBundle(loaded_bundle, argv[2]);
    DebugPrint("[*] Called %s, return value was %d\n", argv[2], func_ret);
    return 0;
}

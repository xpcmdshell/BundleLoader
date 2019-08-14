# BundleLoader

This repository contains some example code that demonstrates how to load and link a Mach-O bundle in memory on OSX, and call a function from it. This can be useful for building software that needs to dynamically load new code in memory at runtime. 

The key functions to read up on are `NSCreateObjectFileImageFromMemory` and `NSLinkModule`.  Once the `NSModule` is loaded and linked, you can locate symbols using `NSLookupSymbolInModule`, and resolve the address to it with `NSAddressOfSymbol`. Then you can cast that to whatever type you need. 

## Usage
```
[ λ ~/dev/BundleLoader ] make
[*] Cleaning
[*] Building loader (debug)
[*] Building test module
[ λ ~/dev/BundleLoader ] build/loader build/testmod _CallMe
[*] Created object file image from memory blob
[*] Linked module in memory
[*] Located function symbol at 0x100cedf50
Hello from CallMe
[*] Called _CallMe, return value was 99
[ λ ~/dev/BundleLoader ] 
```
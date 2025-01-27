#include <Geode/DefaultInclude.hpp>
#include <Geode/loader/Mod.hpp>

using namespace geode::prelude;

$execute {
    // this replaces the call to __dynamic_cast with a call to our own
    // this is needed because the transitions in cocos uses dynamic cast to check
    // layers, which fail on user layers due to typeinfo not matching

    #if defined(GEODE_IS_MACOS)
        (void)Mod::get()->patch(
            reinterpret_cast<void*>(base::get() + 0x603948), toByteArray(&cast::typeinfoCastInternal)
        );
    #elif defined(GEODE_IS_ANDROID32)
        (void)Mod::get()->addHook(reinterpret_cast<void*>(base::get() + (0x720348 - 0x10000) + 1), &cast::typeinfoCastInternal, "__dynamic_cast");
    #elif defined(GEODE_IS_ANDROID64)
        (void)Mod::get()->addHook(reinterpret_cast<void*>(base::get() + (0xd6cb8c - 0x100000)), &cast::typeinfoCastInternal, "__dynamic_cast");
    #endif


}
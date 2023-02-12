#include "pch.h"

dvar_s* Dvar_FindMalleableVar(const char* name)
{
    return ((dvar_s* (__cdecl*)(const char* name))0x0587B00)(name);

}
dvar_s* Dvar_RegisterNew(const char* name, DvarType type, int flags, const char* description, DvarValue defaultValue, DvarLimits domain)
{
    dvar_s* dvar = Dvar_FindMalleableVar(name);

    if (dvar) {
        Com_Printf(CON_CHANNEL_CONSOLEONLY, "dvar (%s) already exists\n", name);
        return Dvar_Reregister(dvar, name, type, flags, description, defaultValue, domain);
    }

    return ((dvar_s * (*)(const char*, DvarType, int, const char*, DvarValue, DvarLimits))0x588750)(name, type, flags, description, defaultValue, domain);
}
dvar_s* Dvar_Reregister(dvar_s* dvar, const char* name, DvarType type, int flags, const char* description, DvarValue defaultValue, DvarLimits domain)
{
    return ((dvar_s * (*)(dvar_s*, const char*, DvarType, int, const char*, DvarValue, DvarLimits))0x588610)(dvar, name, type, flags, description, defaultValue, domain);
}
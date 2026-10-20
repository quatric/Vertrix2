#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/* The registry, held in memory for the run: keys the game creates and the values it sets there
 * read back; anything else is missing, as on a machine the game was never installed on. */

enum
{
    ERROR_SUCCESS = 0,
    ERROR_FILE_NOT_FOUND = 2,
    ERROR_INVALID_HANDLE = 6,
    ERROR_MORE_DATA = 234,
    KEYS = 64,
    VALUES = 256,
    KEY_BASE = 0x00ce0000u
};

static char keys[KEYS][192];

static struct
{
    char key[192];
    char name[64];
    uint32_t type, size;
    uint8_t *data;
} values[VALUES];

/* The path of a predefined key (HKEY_CLASSES_ROOT..) or of one this module opened. */
static const char *key_path(uint32_t key)
{
    static const char *const roots[] = {"HKCR", "HKCU", "HKLM", "HKU", "HKPD", "HKCC"};
    if (key >= 0x80000000u && key <= 0x80000005u)
    {
        return roots[key - 0x80000000u];
    }
    if (key > KEY_BASE && key <= KEY_BASE + KEYS && keys[key - KEY_BASE - 1u][0])
    {
        return keys[key - KEY_BASE - 1u];
    }
    return NULL;
}

static void sub_path(uint32_t key, uint32_t sub, char *out, size_t size)
{
    const char *parent = key_path(key);
    char name[160] = "";
    if (sub)
    {
        v3_read_string(sub, name, sizeof name);
    }
    snprintf(out, size, "%s%s%s", parent ? parent : "?", name[0] ? "\\" : "", name);
}

static int key_exists(const char *path)
{
    size_t n = strlen(path);
    for (unsigned i = 0; i < KEYS; ++i)
    {
        if (strncasecmp(keys[i], path, n) == 0 && (keys[i][n] == 0 || keys[i][n] == '\\'))
        {
            return 1;
        }
    }
    return 0;
}

/* A handle for `path`, creating the key when `create` is set; 0 when it does not exist. */
static uint32_t open_key(const char *path, int create)
{
    if (!key_exists(path) && !create)
    {
        return 0;
    }
    int free_slot = -1;
    for (unsigned i = 0; i < KEYS; ++i)
    {
        if (strcasecmp(keys[i], path) == 0)
        {
            return KEY_BASE + 1u + i;
        }
        if (!keys[i][0] && free_slot < 0)
        {
            free_slot = (int)i;
        }
    }
    if (free_slot < 0)
    {
        return 0;
    }
    snprintf(keys[free_slot], sizeof keys[free_slot], "%s", path);
    return KEY_BASE + 1u + (uint32_t)free_slot;
}

static int find_value(const char *key, const char *name)
{
    for (int i = 0; i < VALUES; ++i)
    {
        if (values[i].data && strcasecmp(values[i].key, key) == 0 &&
            strcasecmp(values[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

static uint32_t open_into(const char *path, int create, uint32_t out)
{
    uint32_t handle = open_key(path, create);
    v3_log("RegOpenKey(%s) -> %s", path, handle ? "opened" : "not found");
    if (!handle)
    {
        return ERROR_FILE_NOT_FOUND;
    }
    v3_w32(out, handle);
    return ERROR_SUCCESS;
}

static void RegOpenKeyA(Cpu *c)
{
    char path[192];
    sub_path(ARG(0), ARG(1), path, sizeof path);
    STDCALL_RETURN(3, open_into(path, 0, ARG(2)));
}

static void RegOpenKeyExA(Cpu *c)
{
    char path[192];
    sub_path(ARG(0), ARG(1), path, sizeof path);
    STDCALL_RETURN(5, open_into(path, 0, ARG(4)));
}

static void RegCreateKeyExA(Cpu *c)
{
    char path[192];
    sub_path(ARG(0), ARG(1), path, sizeof path);
    int existed = key_exists(path);
    uint32_t result = open_into(path, 1, ARG(7));
    if (result == ERROR_SUCCESS && ARG(8))
    {
        v3_w32(ARG(8), existed ? 2u : 1u); /* REG_OPENED_EXISTING_KEY, REG_CREATED_NEW_KEY */
    }
    STDCALL_RETURN(9, result);
}

static void RegSetValueExA(Cpu *c)
{
    const char *key = key_path(ARG(0));
    char name[64] = "";
    if (!key)
    {
        STDCALL_RETURN(6, ERROR_INVALID_HANDLE);
    }
    if (ARG(1))
    {
        v3_read_string(ARG(1), name, sizeof name);
    }
    int i = find_value(key, name);
    for (int j = 0; i < 0 && j < VALUES; ++j)
    {
        if (!values[j].data)
        {
            i = j;
        }
    }
    if (i < 0)
    {
        STDCALL_RETURN(6, 1450); /* ERROR_NO_SYSTEM_RESOURCES */
    }
    uint32_t size = ARG(5);
    free(values[i].data);
    values[i].data = malloc(size ? size : 1);
    for (uint32_t k = 0; k < size; ++k)
    {
        values[i].data[k] = (uint8_t)v3_r8(ARG(4) + k);
    }
    snprintf(values[i].key, sizeof values[i].key, "%s", key);
    snprintf(values[i].name, sizeof values[i].name, "%s", name);
    values[i].type = ARG(3);
    values[i].size = size;
    STDCALL_RETURN(6, ERROR_SUCCESS);
}

static void RegQueryValueExA(Cpu *c)
{
    const char *key = key_path(ARG(0));
    char name[64] = "";
    if (ARG(1))
    {
        v3_read_string(ARG(1), name, sizeof name);
    }
    int i = key ? find_value(key, name) : -1;
    if (i < 0)
    {
        STDCALL_RETURN(6, ERROR_FILE_NOT_FOUND);
    }
    uint32_t type = ARG(3), data = ARG(4), size = ARG(5);
    if (type)
    {
        v3_w32(type, values[i].type);
    }
    uint32_t room = size ? v3_r32(size) : 0;
    if (size)
    {
        v3_w32(size, values[i].size);
    }
    if (!data)
    {
        STDCALL_RETURN(6, ERROR_SUCCESS);
    }
    if (room < values[i].size)
    {
        STDCALL_RETURN(6, ERROR_MORE_DATA);
    }
    for (uint32_t k = 0; k < values[i].size; ++k)
    {
        v3_w8(data + k, values[i].data[k]);
    }
    STDCALL_RETURN(6, ERROR_SUCCESS);
}

static void RegDeleteValueA(Cpu *c)
{
    const char *key = key_path(ARG(0));
    char name[64] = "";
    if (ARG(1))
    {
        v3_read_string(ARG(1), name, sizeof name);
    }
    int i = key ? find_value(key, name) : -1;
    if (i < 0)
    {
        STDCALL_RETURN(2, ERROR_FILE_NOT_FOUND);
    }
    free(values[i].data);
    values[i].data = NULL;
    STDCALL_RETURN(2, ERROR_SUCCESS);
}

static void RegDeleteKeyA(Cpu *c)
{
    char path[192];
    sub_path(ARG(0), ARG(1), path, sizeof path);
    for (unsigned i = 0; i < KEYS; ++i)
    {
        if (strcasecmp(keys[i], path) == 0)
        {
            keys[i][0] = 0;
            STDCALL_RETURN(2, ERROR_SUCCESS);
        }
    }
    STDCALL_RETURN(2, ERROR_FILE_NOT_FOUND);
}

static void RegCloseKey(Cpu *c)
{
    STDCALL_RETURN(1, ERROR_SUCCESS);
}

static void InitializeSecurityDescriptor(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void SetSecurityDescriptorDacl(Cpu *c)
{
    STDCALL_RETURN(4, 1);
}

const V3Export v3_advapi32[] = {{"RegOpenKeyA", RegOpenKeyA},
                                {"RegOpenKeyExA", RegOpenKeyExA},
                                {"RegCreateKeyExA", RegCreateKeyExA},
                                {"RegSetValueExA", RegSetValueExA},
                                {"RegQueryValueExA", RegQueryValueExA},
                                {"RegDeleteValueA", RegDeleteValueA},
                                {"RegDeleteKeyA", RegDeleteKeyA},
                                {"RegCloseKey", RegCloseKey},
                                {"InitializeSecurityDescriptor", InitializeSecurityDescriptor},
                                {"SetSecurityDescriptorDacl", SetSecurityDescriptorDacl},
                                {NULL, NULL}};

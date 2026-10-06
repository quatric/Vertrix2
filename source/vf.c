#include "vf.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    uint32_t size;
    uint32_t offset;
    char *name;
} VfEntry;

struct VertrixVf
{
    FILE *file;
    uint32_t count;
    VfEntry *entries;
};

/* VF integers are little-endian; Wii PowerPC is big-endian. */
static int read_word(FILE *file, uint32_t *value)
{
    unsigned char bytes[4];
    if (fread(bytes, 1, 4, file) != 4)
    {
        return 0;
    }
    *value = (uint32_t)bytes[0] | (uint32_t)bytes[1] << 8 | (uint32_t)bytes[2] << 16 |
             (uint32_t)bytes[3] << 24;
    return 1;
}

void vertrix_vf_close(VertrixVf *archive)
{
    if (!archive)
    {
        return;
    }
    if (archive->entries)
    {
        for (uint32_t i = 0; i < archive->count; i++)
        {
            free(archive->entries[i].name);
        }
    }
    free(archive->entries);
    if (archive->file)
    {
        fclose(archive->file);
    }
    free(archive);
}

VertrixVf *vertrix_vf_open(const char *path)
{
    VertrixVf *archive = calloc(1, sizeof(*archive));
    uint32_t version;
    long file_size;
    if (!archive)
    {
        return NULL;
    }
    archive->file = path ? fopen(path, "rb") : NULL;
    if (!archive->file || fseek(archive->file, 0, SEEK_END) != 0 ||
        (file_size = ftell(archive->file)) < 8 || fseek(archive->file, 0, SEEK_SET) != 0 ||
        !read_word(archive->file, &version) || version != 10 ||
        !read_word(archive->file, &archive->count) ||
        archive->count > (uint32_t)((file_size - 8) / 13))
    {
        goto failure;
    }
    archive->entries = calloc(archive->count, sizeof(*archive->entries));
    if (archive->count && !archive->entries)
    {
        goto failure;
    }
    for (uint32_t i = 0; i < archive->count; i++)
    {
        VfEntry *entry = &archive->entries[i];
        uint32_t name_length;
        long position;
        if (!read_word(archive->file, &entry->size) || !read_word(archive->file, &entry->offset) ||
            !read_word(archive->file, &name_length) || name_length == 0 ||
            (position = ftell(archive->file)) < 0 ||
            name_length > (uint64_t)file_size - (uint64_t)position ||
            (uint64_t)entry->offset + entry->size > (uint64_t)file_size ||
            (uint64_t)entry->offset > (uint64_t)LONG_MAX ||
            (uint64_t)name_length + 1 > (uint64_t)SIZE_MAX)
        {
            goto failure;
        }
        entry->name = malloc((size_t)name_length + 1);
        if (!entry->name || fread(entry->name, 1, name_length, archive->file) != name_length)
        {
            goto failure;
        }
        for (uint32_t j = 0; j < name_length; j++)
        {
            if (entry->name[j] == '\0')
            {
                goto failure;
            }
        }
        entry->name[name_length] = '\0';
    }
    file_size = ftell(archive->file);
    if (file_size < 0)
    {
        goto failure;
    }
    for (uint32_t i = 0; i < archive->count; i++)
    {
        if (archive->entries[i].offset < (uint64_t)file_size)
        {
            goto failure;
        }
    }
    return archive;

failure:
    vertrix_vf_close(archive);
    return NULL;
}

uint32_t vertrix_vf_count(const VertrixVf *archive)
{
    return archive ? archive->count : 0;
}

const char *vertrix_vf_name(const VertrixVf *archive, uint32_t index)
{
    return archive && index < archive->count ? archive->entries[index].name : NULL;
}

static unsigned char normalize(unsigned char character)
{
    if (character == '\\')
    {
        return '/';
    }
    if (character >= 'A' && character <= 'Z')
    {
        return character + ('a' - 'A');
    }
    return character;
}

static const unsigned char *skip_prefix(const unsigned char *name)
{
    while (name[0] == '.' && (name[1] == '/' || name[1] == '\\'))
    {
        name += 2;
    }
    return name;
}

int vertrix_vf_find(const VertrixVf *archive, const char *name, uint32_t *index)
{
    if (!archive || !name || !index)
    {
        return 0;
    }
    for (uint32_t i = 0; i < archive->count; i++)
    {
        const unsigned char *left = skip_prefix((const unsigned char *)archive->entries[i].name);
        const unsigned char *right = skip_prefix((const unsigned char *)name);
        while (*left && normalize(*left) == normalize(*right))
        {
            left++;
            right++;
        }
        if (!*left && !*right)
        {
            *index = i;
            return 1;
        }
    }
    return 0;
}

int vertrix_vf_size(const VertrixVf *archive, uint32_t index, uint32_t *size)
{
    if (!archive || index >= archive->count || !size)
    {
        return 0;
    }
    *size = archive->entries[index].size;
    return 1;
}

int vertrix_vf_read(VertrixVf *archive, uint32_t index, uint32_t offset, void *buffer,
                    size_t length)
{
    if (!archive || index >= archive->count || (!buffer && length))
    {
        return 0;
    }
    const VfEntry *entry = &archive->entries[index];
    if (offset > entry->size || length > entry->size - offset)
    {
        return 0;
    }
    if (length == 0)
    {
        return 1;
    }
    uint64_t position = (uint64_t)entry->offset + offset;
    return position <= LONG_MAX && fseek(archive->file, (long)position, SEEK_SET) == 0 &&
           fread(buffer, 1, length, archive->file) == length;
}

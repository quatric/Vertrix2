#include "png.h"

#include <stdlib.h>
#include <string.h>

enum
{
    MAX_BITS = 15,
    LITERALS = 288,
    DISTANCES = 30,
    CODE_LENGTHS = 19,
    END_OF_BLOCK = 256
};

typedef struct
{
    const unsigned char *input;
    size_t input_size;
    size_t position;
    uint32_t bit_buffer;
    uint32_t bit_count;
    unsigned char *output;
    size_t output_size;
    size_t written;
    int failed;
} Inflate;

typedef struct
{
    uint16_t counts[MAX_BITS + 1];
    uint16_t symbols[LITERALS];
} Huffman;

static uint32_t bits(Inflate *s, uint32_t need)
{
    while (s->bit_count < need)
    {
        if (s->position >= s->input_size)
        {
            s->failed = 1;
            return 0;
        }
        s->bit_buffer |= (uint32_t)s->input[s->position++] << s->bit_count;
        s->bit_count += 8;
    }
    const uint32_t value = s->bit_buffer & ((1u << need) - 1u);
    s->bit_buffer >>= need;
    s->bit_count -= need;
    return value;
}

/* Canonical codes from lengths; 0 when the lengths over-subscribe the code space. */
static int build(Huffman *h, const unsigned char *lengths, uint32_t count)
{
    uint16_t offsets[MAX_BITS + 1];
    memset(h->counts, 0, sizeof h->counts);
    for (uint32_t i = 0; i < count; ++i)
    {
        ++h->counts[lengths[i]];
    }
    int left = 1;
    for (uint32_t length = 1; length <= MAX_BITS; ++length)
    {
        left <<= 1;
        left -= h->counts[length];
        if (left < 0)
        {
            return 0;
        }
    }
    offsets[1] = 0;
    for (uint32_t length = 1; length < MAX_BITS; ++length)
    {
        offsets[length + 1] = (uint16_t)(offsets[length] + h->counts[length]);
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        if (lengths[i] != 0)
        {
            h->symbols[offsets[lengths[i]]++] = (uint16_t)i;
        }
    }
    return 1;
}

static int decode(Inflate *s, const Huffman *h)
{
    int code = 0;
    int first = 0;
    int index = 0;
    for (uint32_t length = 1; length <= MAX_BITS; ++length)
    {
        code |= (int)bits(s, 1);
        if (s->failed)
        {
            return -1;
        }
        const int count = h->counts[length];
        if (code - count < first)
        {
            return h->symbols[index + (code - first)];
        }
        index += count;
        first += count;
        first <<= 1;
        code <<= 1;
    }
    s->failed = 1;
    return -1;
}

static void put(Inflate *s, unsigned char byte)
{
    if (s->written >= s->output_size)
    {
        s->failed = 1;
        return;
    }
    s->output[s->written++] = byte;
}

static void stored(Inflate *s)
{
    s->bit_buffer = 0;
    s->bit_count = 0;
    if (s->position + 4 > s->input_size)
    {
        s->failed = 1;
        return;
    }
    const uint32_t length = s->input[s->position] | (uint32_t)s->input[s->position + 1] << 8;
    const uint32_t check = s->input[s->position + 2] | (uint32_t)s->input[s->position + 3] << 8;
    s->position += 4;
    if ((length ^ 0xffffu) != check || s->position + length > s->input_size)
    {
        s->failed = 1;
        return;
    }
    for (uint32_t i = 0; i < length && !s->failed; ++i)
    {
        put(s, s->input[s->position++]);
    }
}

static void codes(Inflate *s, const Huffman *literals, const Huffman *distances)
{
    static const uint16_t length_base[29] = {3,  4,  5,  6,   7,   8,   9,   10,  11, 13,
                                             15, 17, 19, 23,  27,  31,  35,  43,  51, 59,
                                             67, 83, 99, 115, 131, 163, 195, 227, 258};
    static const uint8_t length_extra[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2,
                                             2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
    static const uint16_t distance_base[30] = {
        1,   2,   3,   4,   5,   7,    9,    13,   17,   25,   33,   49,   65,    97,    129,
        193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};
    static const uint8_t distance_extra[30] = {0, 0, 0, 0, 1, 1, 2, 2,  3,  3,  4,  4,  5,  5,  6,
                                               6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
    for (;;)
    {
        int symbol = decode(s, literals);
        if (s->failed)
        {
            return;
        }
        if (symbol < END_OF_BLOCK)
        {
            put(s, (unsigned char)symbol);
            continue;
        }
        if (symbol == END_OF_BLOCK)
        {
            return;
        }
        symbol -= END_OF_BLOCK + 1;
        if (symbol >= 29)
        {
            s->failed = 1;
            return;
        }
        const uint32_t length = length_base[symbol] + bits(s, length_extra[symbol]);
        const int distance_symbol = decode(s, distances);
        if (s->failed || distance_symbol < 0 || distance_symbol >= DISTANCES)
        {
            s->failed = 1;
            return;
        }
        const uint32_t distance =
            distance_base[distance_symbol] + bits(s, distance_extra[distance_symbol]);
        if (s->failed || distance > s->written)
        {
            s->failed = 1;
            return;
        }
        for (uint32_t i = 0; i < length && !s->failed; ++i)
        {
            put(s, s->output[s->written - distance]);
        }
    }
}

static void fixed(Inflate *s)
{
    unsigned char lengths[LITERALS + DISTANCES];
    uint32_t i = 0;
    for (; i < 144; ++i)
    {
        lengths[i] = 8;
    }
    for (; i < 256; ++i)
    {
        lengths[i] = 9;
    }
    for (; i < 280; ++i)
    {
        lengths[i] = 7;
    }
    for (; i < LITERALS; ++i)
    {
        lengths[i] = 8;
    }
    for (i = 0; i < DISTANCES; ++i)
    {
        lengths[LITERALS + i] = 5;
    }
    Huffman literals;
    Huffman distances;
    build(&literals, lengths, LITERALS);
    build(&distances, lengths + LITERALS, DISTANCES);
    codes(s, &literals, &distances);
}

static void dynamic(Inflate *s)
{
    static const uint8_t order[CODE_LENGTHS] = {16, 17, 18, 0, 8,  7, 9,  6, 10, 5,
                                                11, 4,  12, 3, 13, 2, 14, 1, 15};
    const uint32_t literal_count = bits(s, 5) + 257;
    const uint32_t distance_count = bits(s, 5) + 1;
    const uint32_t length_count = bits(s, 4) + 4;
    if (s->failed || literal_count > 286 || distance_count > DISTANCES)
    {
        s->failed = 1;
        return;
    }
    unsigned char lengths[LITERALS + DISTANCES];
    memset(lengths, 0, sizeof lengths);
    for (uint32_t i = 0; i < length_count; ++i)
    {
        lengths[order[i]] = (unsigned char)bits(s, 3);
    }
    Huffman lengths_code;
    if (s->failed || !build(&lengths_code, lengths, CODE_LENGTHS))
    {
        s->failed = 1;
        return;
    }
    uint32_t index = 0;
    while (index < literal_count + distance_count && !s->failed)
    {
        const int symbol = decode(s, &lengths_code);
        if (symbol < 0)
        {
            return;
        }
        if (symbol < 16)
        {
            lengths[index++] = (unsigned char)symbol;
            continue;
        }
        unsigned char value = 0;
        uint32_t repeat;
        if (symbol == 16)
        {
            if (index == 0)
            {
                s->failed = 1;
                return;
            }
            value = lengths[index - 1];
            repeat = 3 + bits(s, 2);
        }
        else if (symbol == 17)
        {
            repeat = 3 + bits(s, 3);
        }
        else
        {
            repeat = 11 + bits(s, 7);
        }
        if (index + repeat > literal_count + distance_count)
        {
            s->failed = 1;
            return;
        }
        while (repeat-- != 0)
        {
            lengths[index++] = value;
        }
    }
    Huffman literals;
    Huffman distances;
    unsigned char distance_lengths[DISTANCES];
    memset(distance_lengths, 0, sizeof distance_lengths);
    memcpy(distance_lengths, lengths + literal_count, distance_count);
    if (s->failed || lengths[END_OF_BLOCK] == 0 || !build(&literals, lengths, literal_count) ||
        !build(&distances, distance_lengths, DISTANCES))
    {
        s->failed = 1;
        return;
    }
    codes(s, &literals, &distances);
}

size_t vertrix_inflate(const unsigned char *input, size_t input_size, unsigned char *output,
                       size_t output_size)
{
    if (input_size < 6 || (input[0] & 0x0f) != 8 || (input[0] << 8 | input[1]) % 31 != 0 ||
        (input[1] & 0x20) != 0)
    {
        return 0;
    }
    Inflate s = {input, input_size, 2, 0, 0, output, output_size, 0, 0};
    uint32_t last = 0;
    while (!last && !s.failed)
    {
        last = bits(&s, 1);
        const uint32_t type = bits(&s, 2);
        if (type == 0)
        {
            stored(&s);
        }
        else if (type == 1)
        {
            fixed(&s);
        }
        else if (type == 2)
        {
            dynamic(&s);
        }
        else
        {
            s.failed = 1;
        }
    }
    if (s.failed || s.written != output_size || s.position + 4 > input_size)
    {
        return 0;
    }
    uint32_t a = 1;
    uint32_t b = 0;
    for (size_t i = 0; i < s.written; ++i)
    {
        a = (a + output[i]) % 65521u;
        b = (b + a) % 65521u;
    }
    const unsigned char *adler = input + s.position;
    const uint32_t expected =
        (uint32_t)adler[0] << 24 | (uint32_t)adler[1] << 16 | (uint32_t)adler[2] << 8 | adler[3];
    return expected == (b << 16 | a) ? s.written : 0;
}

static uint32_t big32(const unsigned char *p)
{
    return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3];
}

static unsigned char paeth(unsigned char a, unsigned char b, unsigned char c)
{
    const int p = a + b - c;
    const int pa = abs(p - a);
    const int pb = abs(p - b);
    const int pc = abs(p - c);
    if (pa <= pb && pa <= pc)
    {
        return a;
    }
    return pb <= pc ? b : c;
}

static int unfilter(unsigned char *data, uint32_t width, uint32_t height, uint32_t channels)
{
    const size_t stride = (size_t)width * channels;
    unsigned char *previous = NULL;
    for (uint32_t y = 0; y < height; ++y)
    {
        unsigned char *row = data + y * (stride + 1);
        const unsigned char filter = row[0];
        unsigned char *line = row + 1;
        for (size_t x = 0; x < stride; ++x)
        {
            const unsigned char left = x >= channels ? line[x - channels] : 0;
            const unsigned char up = previous ? previous[x] : 0;
            const unsigned char corner = previous && x >= channels ? previous[x - channels] : 0;
            switch (filter)
            {
                case 0:
                    break;
                case 1:
                    line[x] = (unsigned char)(line[x] + left);
                    break;
                case 2:
                    line[x] = (unsigned char)(line[x] + up);
                    break;
                case 3:
                    line[x] = (unsigned char)(line[x] + ((left + up) >> 1));
                    break;
                case 4:
                    line[x] = (unsigned char)(line[x] + paeth(left, up, corner));
                    break;
                default:
                    return 0;
            }
        }
        previous = line;
    }
    return 1;
}

int vertrix_png_decode(const unsigned char *data, size_t size, VertrixImage *image)
{
    static const unsigned char signature[8] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n'};
    if (!image || image->rgba || !data || size < 8 + 25 || memcmp(data, signature, 8) != 0 ||
        memcmp(data + 12, "IHDR", 4) != 0 || big32(data + 8) != 13)
    {
        return 0;
    }
    const uint32_t width = big32(data + 16);
    const uint32_t height = big32(data + 20);
    const unsigned char depth = data[24];
    const unsigned char type = data[25];
    const uint32_t channels = type == 2 ? 3 : type == 6 ? 4 : 0;
    if (width == 0 || height == 0 || width > 4096 || height > 4096 || depth != 8 || channels == 0 ||
        data[26] != 0 || data[27] != 0 || data[28] != 0)
    {
        return 0;
    }
    /* The image data may be split across IDAT chunks; join them. */
    size_t compressed_size = 0;
    for (size_t at = 8; at + 12 <= size;)
    {
        const uint32_t length = big32(data + at);
        if (length > size - at - 12)
        {
            return 0;
        }
        if (memcmp(data + at + 4, "IDAT", 4) == 0)
        {
            compressed_size += length;
        }
        if (memcmp(data + at + 4, "IEND", 4) == 0)
        {
            break;
        }
        at += 12 + (size_t)length;
    }
    unsigned char *compressed = malloc(compressed_size ? compressed_size : 1);
    const size_t raw_size = (size_t)height * ((size_t)width * channels + 1);
    unsigned char *raw = malloc(raw_size);
    unsigned char *rgba = malloc((size_t)width * height * 4);
    if (!compressed || !raw || !rgba)
    {
        free(compressed);
        free(raw);
        free(rgba);
        return 0;
    }
    size_t joined = 0;
    for (size_t at = 8; at + 12 <= size;)
    {
        const uint32_t length = big32(data + at);
        if (memcmp(data + at + 4, "IDAT", 4) == 0)
        {
            memcpy(compressed + joined, data + at + 8, length);
            joined += length;
        }
        if (memcmp(data + at + 4, "IEND", 4) == 0)
        {
            break;
        }
        at += 12 + (size_t)length;
    }
    int ok = vertrix_inflate(compressed, compressed_size, raw, raw_size) == raw_size &&
             unfilter(raw, width, height, channels);
    if (ok)
    {
        for (uint32_t y = 0; y < height; ++y)
        {
            const unsigned char *line = raw + y * ((size_t)width * channels + 1) + 1;
            unsigned char *out = rgba + (size_t)y * width * 4;
            for (uint32_t x = 0; x < width; ++x)
            {
                out[4 * x] = line[channels * x];
                out[4 * x + 1] = line[channels * x + 1];
                out[4 * x + 2] = line[channels * x + 2];
                out[4 * x + 3] = channels == 4 ? line[channels * x + 3] : 255;
            }
        }
        image->width = width;
        image->height = height;
        image->rgba = rgba;
    }
    else
    {
        free(rgba);
    }
    free(compressed);
    free(raw);
    return ok;
}

int vertrix_image_png(VertrixVf *archive, const char *name, VertrixImage *image)
{
    uint32_t index;
    uint32_t size;
    if (!archive || !name || !image || image->rgba || !vertrix_vf_find(archive, name, &index) ||
        !vertrix_vf_size(archive, index, &size))
    {
        return 0;
    }
    unsigned char *data = malloc(size ? size : 1);
    if (!data)
    {
        return 0;
    }
    const int ok =
        vertrix_vf_read(archive, index, 0, data, size) && vertrix_png_decode(data, size, image);
    free(data);
    return ok;
}

#ifndef VERTRIX_TABLE_RELEASE_H
#define VERTRIX_TABLE_RELEASE_H
#include <stdint.h>

#include "array_list.h"

enum
{
    VERTRIX_LIST_STRIDE = 0x1c
};

/* Original 0x45e740 (0x5464e4), 0x45e810 (0x544a34) and 0x45e820 (0x544a50): release the array
 * list object at the address; 0x45e670 releases 0x544d44 for a null eax and 0x544d60 otherwise;
 * 0x45ed40 (vertrix_table_visit_all) visits the items of 0x544a88 with 0x50. Each returns eax. */
uint32_t vertrix_table_release_one(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t address,
                                   uint32_t edx);
uint32_t vertrix_table_release_by_flag(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t eax,
                                       uint32_t edx);
uint32_t vertrix_table_visit_all(const VertrixCalls *calls, const VertrixFactoryServices *services);

/* Original 0x45e830 (5 objects from 0x546458), 0x45e8f0 (19 from 0x544d7c), 0x45ea80 (7 from
 * 0x544ac0 then 7 from 0x546554) and 0x45e910 (19 rows of 10 from 0x544f90, a row being 0x118
 * bytes): release the consecutive array lists, with edx the address of the next one. Returns the
 * last release's eax. */
uint32_t vertrix_table_release_run(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t first,
                                   uint32_t count);
uint32_t vertrix_table_release_rows(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services);
uint32_t vertrix_table_release_pair(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services);

/* Original 0x45e750 (table 0x5464e4, flag 0, the pushed pair zero) and 0x45e7b0 (table 0x544a34,
 * flag 1, the pair being the caller's ebx and ecx): 0x487660 builds the slot `index` from the
 * record `source` (whose dwords at +4 and +8 are field4 and field8), 0x4877f0 fetches the slot,
 * 0x482e10 applies the record to it and 0x483ed0 finishes it. Returns eax. */
uint32_t vertrix_table_fill_slot(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t table, uint32_t index, uint32_t source, uint32_t field4,
                                 uint32_t field8, uint32_t pair_ebx, uint32_t pair_ecx,
                                 uint32_t flag);
/* Originals 0x45e850 (base 0x546458) and 0x45e9e0 (base 0x544d7c) (ret 4; eax = row, edx = index,
 * ebx = record, ecx, the stack argument): the fill of vertrix_table_fill_slot for the list at
 * base + 28 * row, with the record's dwords at +4 and +8 and flag 1. Returns its eax. */
uint32_t vertrix_table_fill_indexed(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t base,
                                    uint32_t row, uint32_t index, uint32_t record, uint32_t field4,
                                    uint32_t field8, uint32_t ecx, uint32_t argument);

/* Original 0x45e260: releases every table list in a fixed order (0x4874f0 on 32 lists with the
 * entry edx, 0x45e810, 0x45e820, 0x45e8f0, 0x45e740 and 0x45e830 among them). Returns the last eax.
 */
uint32_t vertrix_table_release_everything(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t edx);

/* Original 0x45e440: build the seven array lists at 0x544ac0 (28 bytes apart) with 8 entries of
 * size 0x18 through vertrix_array_list_build. Returns the last build's eax. */
uint32_t vertrix_table_build_pair(const VertrixCalls *calls,
                                  const VertrixFactoryServices *services);
/* Original 0x45e630: build 0x544d44 (eax == 0) or 0x544d60 with edx entries of size 0x30 (ebx
 * 0x78, ecx 0x30). Returns the build's eax. */
uint32_t vertrix_table_build_by_flag(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax,
                                     uint32_t edx);

#endif

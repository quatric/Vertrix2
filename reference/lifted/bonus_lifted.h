#ifndef VERTRIX_BONUS_LIFTED_H
#define VERTRIX_BONUS_LIFTED_H
#include "../../source/lifted_runtime.h"

typedef uint32_t (*VertrixLiftFunction)(LiftContext *, uint32_t, uint32_t, uint32_t, uint32_t,
                                        uint32_t, uint32_t, uint32_t, uint32_t);

/* Number of lifted routines and the lifted routine for an original address (NULL when there
 * is none). Arguments: context, eax, edx, ebx, ecx, esi, edi, ebp, esp. */
uint32_t vertrix_lift_count(void);
VertrixLiftFunction vertrix_lift_find(uint32_t address);

uint32_t vertrix_lift_404480(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_404580(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_404610(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_404680(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4046e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_404730(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_405680(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4056c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_405720(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_405d60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_405e00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_405ea0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_405f30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_405f70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4060e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_407020(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_407720(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_407830(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4083a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40a190(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40a800(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40a860(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40a890(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40a8f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40a950(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40ab10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40acf0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40ad50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40c1c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40c220(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40c260(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40c2a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40c2e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40c320(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40c360(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40c430(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40ede0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40ee30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40ee60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40eea0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40ef00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40ef40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40f170(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_40f9e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_410150(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4108a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4112d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4120a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4122f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_412390(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_412430(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_412510(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4125e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_412650(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_412690(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4138b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_413a40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_413bd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_414a90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_414b10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_414b90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415330(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415350(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4153e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415470(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4154b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415550(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415860(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415b50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415b90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415bd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415c00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415c30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415db0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415e40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415e80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415eb0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_415ed0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4163b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_416500(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417150(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4171a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4171e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417220(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417260(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417290(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4172c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417350(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4173d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417460(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4175b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417620(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417690(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417710(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417930(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417970(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417c80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417cf0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417d10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417d40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417d70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417da0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417df0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417e20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417e60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_417ed0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4189f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_418a10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_418ae0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_418af0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_418d50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4191b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4192a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4193b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_419ef0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41a040(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41a2b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41a320(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41a440(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41a4e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41a940(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41a960(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41a9a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41aa20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41aaa0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41aaf0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41ab00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41ab30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41ab60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41abe0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41ac00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41ac20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41ac40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41ac80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41aca0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41b310(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41c020(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41d640(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41d670(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41d6d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41dd60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41ddf0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41df30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41e280(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_41e5e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_423d70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_423dc0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_423ea0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_425ae0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_425de0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_425f40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_425f60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_427850(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4279b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_429530(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_429600(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_429880(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42a200(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42a310(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42a540(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42a8b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42a8e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42a960(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42a970(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42a9d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42aa20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42aab0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42acf0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42af30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42af80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b000(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b050(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b070(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b0f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b110(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b150(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b370(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b5c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42b6b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ba70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42bab0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ebc0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ebe0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ec00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ec20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ec40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ec60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ec80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42eca0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ecc0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ed40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ed70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42eda0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42edf0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42eee0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ef00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ef10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ef20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ef30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ef40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ef50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ef60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42ef80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f3d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f410(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f7d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f7f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f810(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f830(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f850(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f860(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f870(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f880(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f890(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f8a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f8b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_42f8e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_430850(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_431180(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4311a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4311c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_431280(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_431390(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4314a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_431b80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_431d60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_432110(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_432160(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4321b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4323d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_432980(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_432a30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_432c00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_433840(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_433e20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4344e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4387b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_438b90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_438c60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_438cd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_438dd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_438ef0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_439080(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_439140(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_439190(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4393f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_439510(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_439690(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4398c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43a6f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43ab60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43abd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43ad70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43b260(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43c140(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43d130(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43d260(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43d330(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43d3f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43eab0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43f110(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43f190(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_43f480(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_440fc0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_441600(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_441b70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_441d60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_442140(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4429a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_444e00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_445350(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_445900(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_447f40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4493d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_449460(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_44a720(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_452770(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_452960(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_456d80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_456de0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_456e40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_456ea0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_456f10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_456fa0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457000(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457060(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4570b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457170(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4571f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4572b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457420(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457460(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457550(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4575b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457670(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4576d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457730(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457770(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457890(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457a00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457b70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457c10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457d10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_457f40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4580b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458100(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458150(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458260(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4582d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458330(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4583c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458450(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458490(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4584f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458560(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4585c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458710(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4587a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458880(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4589e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458a70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458c20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458d40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458e30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458f00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_458fd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4590a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459100(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459200(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459290(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4593b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4594a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459760(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4597e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459860(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4598a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459900(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459950(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4599e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459a30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459ab0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459b00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_459b60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45aa20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45abd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ac70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ad20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45aea0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45af40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b0b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b0f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b130(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b150(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b190(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b410(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b710(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b790(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b7f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b860(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b8d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45b950(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45bc00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45bc80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45bd00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45bd60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45bdd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45be40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45beb0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45bf20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45bf80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45bff0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45c2f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45dca0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45e3c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45e400(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45e530(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45e590(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45e6b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45eac0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ec00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ec50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ed10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ed60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ee30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ef40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f020(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f140(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f1f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f250(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f3f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f500(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f590(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f770(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45f9f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45fb00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45fc80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45fe10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45fee0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_45ffb0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4601c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4602a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460440(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460630(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460840(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460a40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460ad0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460b60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460c50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460df0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460ed0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_460fa0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_461090(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_461360(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4614c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_461610(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_461790(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4657f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_465a70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_465af0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_466d60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_469480(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_46a410(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_46a9c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_46b800(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_46b810(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_46c500(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_46c5d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_46f440(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_470960(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_470b20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_470d20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471020(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4711a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471340(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4713c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4717f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471820(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4718a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471920(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471940(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471960(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471980(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4719a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4719e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4719f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471a20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471a40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471a50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471a60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471a90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471aa0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471ab0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471ad0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471ae0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471af0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471b10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471b20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471b30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471b50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471b60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471b70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471b90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471ba0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471c40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471c90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471cd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471d10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471d50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_471ee0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472020(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472090(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472100(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472170(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4721e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472250(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4722c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472330(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472360(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4723a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472440(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472460(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472620(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4726d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472ad0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472bd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472d50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472d90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_472db0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_473490(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_473cd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_473f10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_473fc0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4741a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_474490(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_474540(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_474e00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4754e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475510(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4756d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475700(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475790(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4757e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475840(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475b20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475b80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475be0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475c80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475de0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_475e30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476160(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476400(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476440(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476480(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4764d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476500(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476650(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476720(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476810(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4768e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476a00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476cc0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476d20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476d70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476fb0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_476fe0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477010(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477040(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477070(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4770a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4770d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477100(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477130(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477160(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4772f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477320(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477610(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4776a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477910(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477930(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4779c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477af0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477d10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_477f10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478480(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4784d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478520(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478570(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4785c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478610(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478660(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4786b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478700(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478750(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4787a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478860(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4788f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478910(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478ae0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478b70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478d10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_478d80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_479a40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_479b50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_479d70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47ab70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47bd80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47c250(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47c3b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47c520(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47c710(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47c930(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47cb40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47cd60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47e200(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47e360(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47e780(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47ed30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f160(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f320(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f370(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f3d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f410(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f4b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f750(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f770(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f8f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47f9e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47fa20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47fa40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47fa90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47fce0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47fe20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_47fe50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_480990(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_480b20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_480ff0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_481340(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_481460(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4816f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_481b30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_481e10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4823b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_482550(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4826c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4827c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_482860(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4828a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4828f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_482930(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4829c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_482a60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_482aa0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_482b40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_482d00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_482f80(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4830f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_483110(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_483790(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_484550(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4845d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_484680(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_484700(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4848f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4856d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_485700(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4872f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_487750(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_487790(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4877d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_487860(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_487920(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4879f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_487a10(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_487be0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_487df0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_488050(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4886f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_489170(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_489230(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4893c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_489790(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_489950(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_489b40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_489fa0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48a100(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48a2d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48ac00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48ac50(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48ad00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48ae00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48b240(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48b550(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48b770(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48c390(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48c3b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48c3d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48c460(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48c480(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48c610(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48c9d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48c9f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48d530(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48d600(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48d620(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48d650(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_48d6c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ac1c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ac1e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ac250(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ac2b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ac590(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ac610(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4accc0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4acd30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ad2c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ad630(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ad870(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4adf70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4adfa0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4adfb0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4adfe0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ae110(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ae150(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ae1f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ae250(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4af8c0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b0b70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b17b0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b17e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b2300(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b2340(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b2a00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b2d90(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3100(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3140(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3210(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3340(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3360(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3390(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b34d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3500(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3a00(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3ce0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3d60(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b3fb0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b4cf0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b5050(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b50d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b5150(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b5400(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b5550(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b5580(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b5700(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b5db0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b5fc0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b6070(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b6170(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b65d0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b6800(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b6a30(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b6ea0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b7600(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b78e0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b79a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b7dd0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b8187(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b826f(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b9330(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b9c20(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4b9cf0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4bc050(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4c5400(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4c5a40(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4c5bb0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4c70f0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4c9b6a(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ca060(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4ca5a0(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4cd847(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4cdb70(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4cea15(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_4cf880(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                             uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
#endif

# Slot deal

`slot_deal.c`: `0x415c60` shuffles the 16 slot numbers (0..18) not reserved by the dwords
`0x4f84e0`, `0x4f84cc`, `0x4f84b8` using sixteen draws of `0x4826c0` with limit 16, and fills 15
dwords from `0x53bad8`: first four shuffled numbers, the reserved slots, zeros. Not exact for
reserved slots that are equal or above 18 (stale stack in the original); native returns 0.

Verification: `tools/verify_slot_deal.py`, 4,096 executions with replayed draws. Evidence:
`slot-deal-verification.json`.

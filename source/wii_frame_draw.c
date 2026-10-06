#include "wii_frame_draw.h"

int vertrix_wii_frame_draw(VertrixWiiTexture *texture, int16_t x, int16_t y, uint16_t width,
                           uint16_t height)
{
    if (!texture || !texture->ready || !texture->pixels.data || !width || !height ||
        !(texture->u_limit > 0 && texture->u_limit <= 1) ||
        !(texture->v_limit > 0 && texture->v_limit <= 1))
    {
        return 0;
    }
    GX_SetNumChans(0);
    GX_SetNumTexGens(1);
    GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GX_SetNumTevStages(1);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLORNULL);
    GX_SetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GX_SetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GX_SetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
    GX_SetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GX_SetColorUpdate(GX_TRUE);
    GX_SetAlphaUpdate(GX_FALSE);
    GX_SetCullMode(GX_CULL_NONE);
    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    vertrix_wii_texture_bind(texture, GX_TEXMAP0);
    float left = x, top = y;
    float right = left + width, bottom = top + height;
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    GX_Position3f32(left, top, 0);
    GX_TexCoord2f32(0, 0);
    GX_Position3f32(right, top, 0);
    GX_TexCoord2f32(texture->u_limit, 0);
    GX_Position3f32(right, bottom, 0);
    GX_TexCoord2f32(texture->u_limit, texture->v_limit);
    GX_Position3f32(left, bottom, 0);
    GX_TexCoord2f32(0, texture->v_limit);
    GX_End();
    return 1;
}

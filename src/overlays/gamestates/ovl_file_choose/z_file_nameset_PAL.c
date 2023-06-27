#include "file_select.h"
#include "terminal.h"
#include "assets/textures/title_static/title_static.h"
#include "assets/overlays/ovl_File_Choose/ovl_file_choose.h"

static s16 D_808124C0[] = {
    0x0002, 0x0003, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0002, 0x0000, 0x0001,
    0x0001, 0x0002, 0x0001, 0x0001, 0x0004, 0x0002, 0x0002, 0x0002, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001,
    0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0003,
    0x0002, 0x0002, 0x0004, 0x0003, 0x0002, 0x0004, 0x0001, 0x0002, 0x0002, 0x0001, 0x0001, 0x0002, 0x0002, 0x0003,
    0x0002, 0x0002, 0x0000, 0x0002, 0x0002, 0x0002, 0x0000, 0x0003, 0x0001, 0x0000,
};

static s16 D_80812544[] = {
    0x0001, 0x0002, 0x0000, 0x0001, 0x0001, 0x0002, 0x0001, 0x0001, 0x0004, 0x0002, 0x0002, 0x0002, 0x0001,
    0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001,
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0003, 0x0002, 0x0002, 0x0004, 0x0003, 0x0002, 0x0004, 0x0001,
    0x0002, 0x0002, 0x0001, 0x0001, 0x0002, 0x0002, 0x0003, 0x0002, 0x0002, 0x0000, 0x0002, 0x0002, 0x0002,
    0x0003, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0003,
};

void FileSelect_DrawCharacter(GraphicsContext* gfxCtx, void* texture, s16 vtx) {
    OPEN_DISPS(gfxCtx, "../z_file_nameset_PAL.c", 110);

    gDPLoadTextureBlock_4b(POLY_OPA_DISP++, texture, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, vtx, vtx + 2, vtx + 3, vtx + 1, 0);

    CLOSE_DISPS(gfxCtx, "../z_file_nameset_PAL.c", 119);
}

void FileSelect_SetKeyboardVtx(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 val;
    s16 phi_t2;
    s16 phi_t0;
    s16 phi_t3;
    s16 phi_s1;
    s16 phi_t1;
    s16 phi_s2;

    this->keyboardVtx = Graph_Alloc(this->state.gfxCtx, sizeof(Vtx) * 4 * 5 * 13);

    phi_s1 = 0x26;

    for (phi_t2 = 0, phi_s2 = 0, phi_t3 = 0; phi_s2 < 5; phi_s2++) {
        phi_t0 = -0x60;

        for (phi_t1 = 0; phi_t1 < 13; phi_t1++, phi_t3 += 4, phi_t2++) {
            //! @bug D_80812544 is accessed out of bounds when drawing the empty space character (value of 64). Under
            //! normal circumstances it reads a halfword from sNameLabelTextures.
            this->keyboardVtx[phi_t3].v.vector[0] = this->keyboardVtx[phi_t3 + 2].v.vector[0] = D_80812544[phi_t2] + phi_t0;

            this->keyboardVtx[phi_t3 + 1].v.vector[0] = this->keyboardVtx[phi_t3 + 3].v.vector[0] =
                D_80812544[phi_t2] + phi_t0 + 12;

            this->keyboardVtx[phi_t3].v.vector[1] = this->keyboardVtx[phi_t3 + 1].v.vector[1] = phi_s1;

            this->keyboardVtx[phi_t3 + 2].v.vector[1] = this->keyboardVtx[phi_t3 + 3].v.vector[1] = phi_s1 - 12;

            this->keyboardVtx[phi_t3].v.vector[2] = this->keyboardVtx[phi_t3 + 1].v.vector[2] =
                this->keyboardVtx[phi_t3 + 2].v.vector[2] = this->keyboardVtx[phi_t3 + 3].v.vector[2] = 0;

            this->keyboardVtx[phi_t3].v.flag = this->keyboardVtx[phi_t3 + 1].v.flag =
                this->keyboardVtx[phi_t3 + 2].v.flag = this->keyboardVtx[phi_t3 + 3].v.flag = 0;

            this->keyboardVtx[phi_t3].v.tc[0] = this->keyboardVtx[phi_t3].v.tc[1] =
                this->keyboardVtx[phi_t3 + 1].v.tc[1] = this->keyboardVtx[phi_t3 + 2].v.tc[0] = 0;

            this->keyboardVtx[phi_t3 + 1].v.tc[0] = this->keyboardVtx[phi_t3 + 2].v.tc[1] =
                this->keyboardVtx[phi_t3 + 3].v.tc[0] = this->keyboardVtx[phi_t3 + 3].v.tc[1] = 0x200;

            this->keyboardVtx[phi_t3].v.color[0] = this->keyboardVtx[phi_t3 + 1].v.color[0] =
                this->keyboardVtx[phi_t3 + 2].v.color[0] = this->keyboardVtx[phi_t3 + 3].v.color[0] =
                    this->keyboardVtx[phi_t3].v.color[1] = this->keyboardVtx[phi_t3 + 1].v.color[1] =
                        this->keyboardVtx[phi_t3 + 2].v.color[1] = this->keyboardVtx[phi_t3 + 3].v.color[1] =
                            this->keyboardVtx[phi_t3].v.color[2] = this->keyboardVtx[phi_t3 + 1].v.color[2] =
                                this->keyboardVtx[phi_t3 + 2].v.color[2] = this->keyboardVtx[phi_t3 + 3].v.color[2] =
                                    this->keyboardVtx[phi_t3].v.color[3] = this->keyboardVtx[phi_t3 + 1].v.color[3] =
                                        this->keyboardVtx[phi_t3 + 2].v.color[3] = this->keyboardVtx[phi_t3 + 3].v.color[3] =
                                            255;

            phi_t0 += 0x10;
        }

        phi_s1 -= 0x10;
    }
}

static void* sNameLabelTextures[] = { gFileSelNameENGTex, gFileSelNameENGTex, gFileSelNameENGTex };

static void* sBackspaceEndTextures[][2] = {
    { gFileSelBackspaceButtonTex, gFileSelENDButtonENGTex },
    { gFileSelBackspaceButtonTex, gFileSelENDButtonENGTex },
    { gFileSelBackspaceButtonTex, gFileSelENDButtonENGTex },
};

static u16 sBackspaceEndWidths[] = { 28, 44 };

static s16 D_808125EC[] = {
    0xFFE2, 0xFFF0, 0xFFFA, 0x0004, 0x000E, 0x0018, 0x0022, 0x002C, 0x0036, 0xFFF0, 0xFFF0,
};

static s16 D_80812604[] = {
    0x0048, 0x0045, 0x0045, 0x0045, 0x0045, 0x0045, 0x0045, 0x0045, 0x0045, 0x0045, 0x0045,
};

/**
 * Set vertices used by all elements of the name entry screen that are NOT the keyboard.
 * This includes the cursor highlight, the name entry plate and characters, and the buttons.
 */
void FileSelect_SetNameEntryVtx(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    Font* font = &this->font;
    s16 phi_s0;
    s16 phi_t1;
    u8 temp;
    s16 phi_v0;

    OPEN_DISPS(this->state.gfxCtx, "../z_file_nameset_PAL.c", 205);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->titleAlpha[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
    gSPVertex(POLY_OPA_DISP++, D_80811BB0, 24, 0);
    gDPLoadTextureBlock(POLY_OPA_DISP++, sNameLabelTextures[gSaveContext.language], G_IM_FMT_IA, G_IM_SIZ_8b, 56, 16, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
    gDPPipeSync(POLY_OPA_DISP++);

    phi_s0 = 0x10;
    for (phi_t1 = 0; phi_t1 < 2; phi_t1++, phi_s0 += 4) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2], 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
        gDPLoadTextureBlock(POLY_OPA_DISP++, sBackspaceEndTextures[gSaveContext.language][phi_t1], G_IM_FMT_IA,
                            G_IM_SIZ_16b, sBackspaceEndWidths[phi_t1], 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(POLY_OPA_DISP++, phi_s0, phi_s0 + 2, phi_s0 + 3, phi_s0 + 1, 0);
    }

    this->nameEntryVtx = Graph_Alloc(this->state.gfxCtx, 44 * sizeof(Vtx));

    for (phi_s0 = 0, phi_t1 = 0; phi_t1 < 44; phi_t1 += 4, phi_s0++) {
        if ((phi_s0 > 0) && (phi_s0 < 9)) {
            temp = this->fileNames[this->buttonIndex][phi_s0 - 1];

            this->nameEntryVtx[phi_t1].v.vector[0] = this->nameEntryVtx[phi_t1 + 2].v.vector[0] =
                D_808125EC[phi_s0] + this->nameEntryBoxPosX + D_808124C0[temp];

            this->nameEntryVtx[phi_t1 + 1].v.vector[0] = this->nameEntryVtx[phi_t1 + 3].v.vector[0] =
                this->nameEntryVtx[phi_t1].v.vector[0] + 0xA;
        } else {
            this->nameEntryVtx[phi_t1].v.vector[0] = this->nameEntryVtx[phi_t1 + 2].v.vector[0] =
                D_808125EC[phi_s0] + this->nameEntryBoxPosX;

            this->nameEntryVtx[phi_t1 + 1].v.vector[0] = this->nameEntryVtx[phi_t1 + 3].v.vector[0] =
                this->nameEntryVtx[phi_t1].v.vector[0] + 0xA;
        }

        this->nameEntryVtx[phi_t1].v.vector[1] = this->nameEntryVtx[phi_t1 + 1].v.vector[1] = D_80812604[phi_s0];

        this->nameEntryVtx[phi_t1 + 2].v.vector[1] = this->nameEntryVtx[phi_t1 + 3].v.vector[1] =
            this->nameEntryVtx[phi_t1].v.vector[1] - 0xA;

        this->nameEntryVtx[phi_t1].v.vector[2] = this->nameEntryVtx[phi_t1 + 1].v.vector[2] =
            this->nameEntryVtx[phi_t1 + 2].v.vector[2] = this->nameEntryVtx[phi_t1 + 3].v.vector[2] = 0;

        this->nameEntryVtx[phi_t1].v.flag = this->nameEntryVtx[phi_t1 + 1].v.flag =
            this->nameEntryVtx[phi_t1 + 2].v.flag = this->nameEntryVtx[phi_t1 + 3].v.flag = 0;

        this->nameEntryVtx[phi_t1].v.tc[0] = this->nameEntryVtx[phi_t1].v.tc[1] =
            this->nameEntryVtx[phi_t1 + 1].v.tc[1] = this->nameEntryVtx[phi_t1 + 2].v.tc[0] = 0;

        this->nameEntryVtx[phi_t1 + 1].v.tc[0] = this->nameEntryVtx[phi_t1 + 2].v.tc[1] =
            this->nameEntryVtx[phi_t1 + 3].v.tc[0] = this->nameEntryVtx[phi_t1 + 3].v.tc[1] = 0x200;

        this->nameEntryVtx[phi_t1].v.color[0] = this->nameEntryVtx[phi_t1 + 1].v.color[0] =
            this->nameEntryVtx[phi_t1 + 2].v.color[0] = this->nameEntryVtx[phi_t1 + 3].v.color[0] =
                this->nameEntryVtx[phi_t1].v.color[1] = this->nameEntryVtx[phi_t1 + 1].v.color[1] =
                    this->nameEntryVtx[phi_t1 + 2].v.color[1] = this->nameEntryVtx[phi_t1 + 3].v.color[1] =
                        this->nameEntryVtx[phi_t1].v.color[2] = this->nameEntryVtx[phi_t1 + 1].v.color[2] =
                            this->nameEntryVtx[phi_t1 + 2].v.color[2] = this->nameEntryVtx[phi_t1 + 3].v.color[2] =
                                this->nameEntryVtx[phi_t1].v.color[3] = this->nameEntryVtx[phi_t1 + 1].v.color[3] =
                                    this->nameEntryVtx[phi_t1 + 2].v.color[3] = this->nameEntryVtx[phi_t1 + 3].v.color[3] =
                                        0xFF;
    }

    this->nameEntryVtx[1].v.vector[0] = this->nameEntryVtx[3].v.vector[0] = this->nameEntryVtx[0].v.vector[0] + 0x6C;
    this->nameEntryVtx[2].v.vector[1] = this->nameEntryVtx[3].v.vector[1] = this->nameEntryVtx[0].v.vector[1] - 0x10;
    this->nameEntryVtx[1].v.tc[0] = this->nameEntryVtx[3].v.tc[0] = 0xD80;

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                    this->nameEntryBoxAlpha);
    gSPVertex(POLY_OPA_DISP++, this->nameEntryVtx, 4, 0);
    gDPLoadTextureBlock(POLY_OPA_DISP++, gFileSelNameBoxTex, G_IM_FMT_IA, G_IM_SIZ_16b, 108, 16, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);
    gSPVertex(POLY_OPA_DISP++, this->nameEntryVtx + 4, 32, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->nameEntryBoxAlpha);

    for (phi_v0 = 0, phi_s0 = 0; phi_s0 < 0x20; phi_s0 += 4, phi_v0++) {
        FileSelect_DrawCharacter(this->state.gfxCtx,
                                 font->fontBuf + this->fileNames[this->buttonIndex][phi_v0] * FONT_CHAR_TEX_SIZE,
                                 phi_s0);
    }

    this->nameEntryVtx[0x25].v.tc[0] = this->nameEntryVtx[0x26].v.tc[1] = this->nameEntryVtx[0x27].v.tc[0] =
        this->nameEntryVtx[0x27].v.tc[1] = this->nameEntryVtx[0x29].v.tc[0] = this->nameEntryVtx[0x2A].v.tc[1] =
            this->nameEntryVtx[0x2B].v.tc[0] = this->nameEntryVtx[0x2B].v.tc[1] = 0x300;

    if ((this->kbdButton == 0) || (this->kbdButton == 1) || (this->kbdButton == 4)) {
        this->nameEntryVtx[0x29].v.tc[0] = this->nameEntryVtx[0x2B].v.tc[0] = 0x700;
    } else if ((this->kbdButton == 2) || (this->kbdButton == 3)) {
        this->nameEntryVtx[0x29].v.tc[0] = this->nameEntryVtx[0x2B].v.tc[0] = 0x500;
    }

    CLOSE_DISPS(this->state.gfxCtx, "../z_file_nameset_PAL.c", 307);
}

void FileSelect_DrawKeyboard(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    Font* font = &this->font;
    s16 i = 0;
    s16 tmp;
    s16 vtx = 0;

    OPEN_DISPS(this->state.gfxCtx, "../z_file_nameset_PAL.c", 324);

    Gfx_SetupDL_42Opa(this->state.gfxCtx);
    gDPSetCycleType(POLY_OPA_DISP++, G_CYC_2CYCLE);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_XLU_SURF2);
    gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, PRIMITIVE, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, COMBINED, 0,
                      0, 0, COMBINED);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, this->charBgAlpha, 255, 255, 255, 255);

    while (vtx < 0x100) {
        gSPVertex(POLY_OPA_DISP++, &this->keyboardVtx[vtx], 32, 0);

        for (tmp = 0; tmp < 32; i++, tmp += 4) {
            FileSelect_DrawCharacter(this->state.gfxCtx, font->fontBuf + D_808123F0[i] * FONT_CHAR_TEX_SIZE, tmp);
        }

        vtx += 32;
    }

    gSPVertex(POLY_OPA_DISP++, &this->keyboardVtx[0x100], 4, 0);
    FileSelect_DrawCharacter(this->state.gfxCtx, font->fontBuf + D_808123F0[i] * FONT_CHAR_TEX_SIZE, 0);

    CLOSE_DISPS(this->state.gfxCtx, "../z_file_nameset_PAL.c", 347);
}

void FileSelect_DrawNameEntry(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    Font* font = &this->font;
    Input* input = &this->state.input[0];
    s16 i;
    s16 tmp;
    u16 dayTime;
    s16 validName;

    OPEN_DISPS(this->state.gfxCtx, "../z_file_nameset_PAL.c", 368);

    FileSelect_SetKeyboardVtx(&this->state);
    FileSelect_SetNameEntryVtx(&this->state);
    FileSelect_PulsateCursor(&this->state);

    tmp = (this->newFileNameCharCount * 4) + 4;
    this->nameEntryVtx[36].v.vector[0] = this->nameEntryVtx[38].v.vector[0] = this->nameEntryVtx[tmp].v.vector[0] - 6;
    this->nameEntryVtx[37].v.vector[0] = this->nameEntryVtx[39].v.vector[0] = this->nameEntryVtx[36].v.vector[0] + 24;
    this->nameEntryVtx[36].v.vector[1] = this->nameEntryVtx[37].v.vector[1] = this->nameEntryVtx[tmp].v.vector[1] + 7;
    this->nameEntryVtx[38].v.vector[1] = this->nameEntryVtx[39].v.vector[1] = this->nameEntryVtx[36].v.vector[1] - 24;

    if ((this->kbdButton == FS_KBD_BTN_HIRA) || (this->kbdButton == FS_KBD_BTN_KATA) ||
        (this->kbdButton == FS_KBD_BTN_END)) {
        if (this->kbdX != this->kbdButton) {
            osSyncPrintf("014 xpos=%d  contents=%d\n", this->kbdX, this->kbdButton);
        }
        this->nameEntryVtx[40].v.vector[0] = this->nameEntryVtx[42].v.vector[0] = D_80811BB0[(this->kbdX + 1) * 4].v.vector[0] - 4;
        this->nameEntryVtx[41].v.vector[0] = this->nameEntryVtx[43].v.vector[0] = this->nameEntryVtx[40].v.vector[0] + 52;
        this->nameEntryVtx[40].v.vector[1] = this->nameEntryVtx[41].v.vector[1] = D_80811BB0[(this->kbdX + 1) * 4].v.vector[1] + 4;

    } else if ((this->kbdButton == FS_KBD_BTN_ENG) || (this->kbdButton == FS_KBD_BTN_BACKSPACE)) {
        if (this->kbdX != this->kbdButton) {
            osSyncPrintf("23 xpos=%d  contents=%d\n", this->kbdX, this->kbdButton);
        }
        this->nameEntryVtx[40].v.vector[0] = this->nameEntryVtx[42].v.vector[0] = D_80811BB0[(this->kbdX + 1) * 4].v.vector[0] - 4;
        this->nameEntryVtx[41].v.vector[0] = this->nameEntryVtx[43].v.vector[0] = this->nameEntryVtx[40].v.vector[0] + 40;
        this->nameEntryVtx[40].v.vector[1] = this->nameEntryVtx[41].v.vector[1] = D_80811BB0[(this->kbdX + 1) * 4].v.vector[1] + 4;
    } else {
        if (this->charIndex >= 65) {
            osSyncPrintf("mjp=%d  xpos=%d  ypos=%d  name_contents=%d\n", this->charIndex, this->kbdX, this->kbdY,
                         this->kbdButton);
        }

        this->nameEntryVtx[40].v.vector[0] = this->nameEntryVtx[42].v.vector[0] =
            this->keyboardVtx[this->charIndex * 4].v.vector[0] - D_80812544[this->charIndex] - 6;
        this->nameEntryVtx[41].v.vector[0] = this->nameEntryVtx[43].v.vector[0] = this->nameEntryVtx[40].v.vector[0] + 24;
        this->nameEntryVtx[40].v.vector[1] = this->nameEntryVtx[41].v.vector[1] =
            this->keyboardVtx[this->charIndex * 4].v.vector[1] + 6;
    }

    this->nameEntryVtx[42].v.vector[1] = this->nameEntryVtx[43].v.vector[1] = this->nameEntryVtx[40].v.vector[1] - 24;

    gSPVertex(POLY_OPA_DISP++, &this->nameEntryVtx[36], 8, 0);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, 1, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, 1, 0, PRIMITIVE, 0, TEXEL0, 0,
                      PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->highlightColor[0], this->highlightColor[1], this->highlightColor[2],
                    this->highlightColor[3]);
    gDPLoadTextureBlock(POLY_OPA_DISP++, gFileSelCharHighlightTex, G_IM_FMT_I, G_IM_SIZ_8b, 24, 24, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);

    if ((this->kbdButton == FS_KBD_BTN_HIRA) || (this->kbdButton == FS_KBD_BTN_KATA) ||
        (this->kbdButton == FS_KBD_BTN_END)) {
        gDPLoadTextureBlock(POLY_OPA_DISP++, gFileSelMediumButtonHighlightTex, G_IM_FMT_I, G_IM_SIZ_8b, 56, 24, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

    } else if ((this->kbdButton == FS_KBD_BTN_ENG) || (this->kbdButton == FS_KBD_BTN_BACKSPACE)) {
        gDPLoadTextureBlock(POLY_OPA_DISP++, gFileSelSmallButtonHighlightTex, G_IM_FMT_I, G_IM_SIZ_8b, 40, 24, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
    }

    gSP1Quadrangle(POLY_OPA_DISP++, 4, 6, 7, 5, 0);

    FileSelect_DrawKeyboard(&this->state);
    gDPPipeSync(POLY_OPA_DISP++);
    Gfx_SetupDL_42Opa(this->state.gfxCtx);

    gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

    if (this->configMode == CM_NAME_ENTRY) {
        if (CHECK_BTN_ALL(input->press.button, BTN_START)) {
            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_L, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            // place cursor on END button
            this->kbdY = 5;
            this->kbdX = 4;
        } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
            if ((this->newFileNameCharCount == 7) && (this->fileNames[this->buttonIndex][7] != 0x3E)) {
                for (i = this->newFileNameCharCount; i < 7; i++) {
                    this->fileNames[this->buttonIndex][i] = this->fileNames[this->buttonIndex][i + 1];
                }

                this->fileNames[this->buttonIndex][i] = 0x3E;
                Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_S, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            } else {
                this->newFileNameCharCount--;

                if (this->newFileNameCharCount < 0) {
                    this->newFileNameCharCount = 0;
                    this->configMode = CM_NAME_ENTRY_TO_MAIN;
                } else {
                    for (i = this->newFileNameCharCount; i < 7; i++) {
                        this->fileNames[this->buttonIndex][i] = this->fileNames[this->buttonIndex][i + 1];
                    }

                    this->fileNames[this->buttonIndex][i] = 0x3E;
                    Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_S, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                         &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                }
            }
        } else {
            if (this->charPage <= FS_CHAR_PAGE_ENG) {
                if (this->kbdY != 5) {
                    // draw the character the cursor is hovering over in yellow
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 0, 255);
                    gSPVertex(POLY_OPA_DISP++, &this->keyboardVtx[this->charIndex * 4], 4, 0);

                    FileSelect_DrawCharacter(this->state.gfxCtx,
                                             font->fontBuf + D_808123F0[this->charIndex] * FONT_CHAR_TEX_SIZE, 0);

                    if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
                        Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_S, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                        this->fileNames[this->buttonIndex][this->newFileNameCharCount] = D_808123F0[this->charIndex];
                        this->newFileNameCharCount++;

                        if (this->newFileNameCharCount > 7) {
                            this->newFileNameCharCount = 7;
                        }
                    }
                } else if (CHECK_BTN_ALL(input->press.button, BTN_A) && (this->charPage != this->kbdButton)) {
                    if (this->kbdButton == FS_KBD_BTN_BACKSPACE) {
                        if ((this->newFileNameCharCount == 7) && (this->fileNames[this->buttonIndex][7] != 0x3E)) {
                            for (i = this->newFileNameCharCount; i < 7; i++) {
                                this->fileNames[this->buttonIndex][i] = this->fileNames[this->buttonIndex][i + 1];
                            }

                            this->fileNames[this->buttonIndex][i] = 0x3E;
                            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_S, &gSfxDefaultPos, 4,
                                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
                                                 &gSfxDefaultReverb);
                        } else {
                            this->newFileNameCharCount--;

                            if (this->newFileNameCharCount < 0) {
                                this->newFileNameCharCount = 0;
                            }

                            for (i = this->newFileNameCharCount; i < 7; i++) {
                                this->fileNames[this->buttonIndex][i] = this->fileNames[this->buttonIndex][i + 1];
                            }

                            this->fileNames[this->buttonIndex][i] = 0x3E;
                            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_S, &gSfxDefaultPos, 4,
                                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
                                                 &gSfxDefaultReverb);
                        }
                    } else if (this->kbdButton == FS_KBD_BTN_END) {
                        validName = false;

                        for (i = 0; i < 8; i++) {
                            if (this->fileNames[this->buttonIndex][i] != 0x3E) {
                                validName = true;
                                break;
                            }
                        }

                        if (validName) {
                            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_L, &gSfxDefaultPos, 4,
                                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
                                                 &gSfxDefaultReverb);
                            gSaveContext.fileNum = this->buttonIndex;
                            dayTime = ((void)0, gSaveContext.dayTime);
                            Sram_InitSave(this, &this->sramCtx);
                            gSaveContext.dayTime = dayTime;
                            this->configMode = CM_NAME_ENTRY_TO_MAIN;
                            this->nameBoxAlpha[this->buttonIndex] = this->nameAlpha[this->buttonIndex] = 200;
                            this->connectorAlpha[this->buttonIndex] = 255;
                            Rumble_Request(300.0f, 180, 20, 100);
                        } else {
                            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_ERROR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                        }
                    }
                }

                if (CHECK_BTN_ALL(input->press.button, BTN_CRIGHT)) {
                    Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                         &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                    this->newFileNameCharCount++;

                    if (this->newFileNameCharCount > 7) {
                        this->newFileNameCharCount = 7;
                    }
                } else if (CHECK_BTN_ALL(input->press.button, BTN_CLEFT)) {
                    Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                         &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                    this->newFileNameCharCount--;

                    if (this->newFileNameCharCount < 0) {
                        this->newFileNameCharCount = 0;
                    }
                }
            }
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);

    CLOSE_DISPS(this->state.gfxCtx, "../z_file_nameset_PAL.c", 550);
}

/**
 * Fade in the name entry box and slide it to the center of the screen from the right side.
 * After the name entry box is in place, init the keyboard/cursor and change modes.
 * Update function for `CM_START_NAME_ENTRY`
 */
void FileSelect_StartNameEntry(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->nameEntryBoxAlpha += 25;

    if (this->nameEntryBoxAlpha >= 255) {
        this->nameEntryBoxAlpha = 255;
    }

    this->nameEntryBoxPosX -= 30;

    if (this->nameEntryBoxPosX <= 0) {
        this->nameEntryBoxPosX = 0;
        this->nameEntryBoxAlpha = 255;
        this->kbdX = 0;
        this->kbdY = 0;
        this->kbdButton = 99;
        this->configMode = CM_NAME_ENTRY;
    }
}

/**
 * Update the keyboard cursor and play sound effects at the appropriate times.
 * There are many special cases for warping the cursor depending on where
 * the cursor currently is.
 * Update function for `CM_NAME_ENTRY`
 */
void FileSelect_UpdateKeyboardCursor(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 prevKbdX;

    this->kbdButton = 99;

    if (this->kbdY != 5) {
        if (this->stickAdjX < -30) {
            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->charIndex--;
            this->kbdX--;
            if (this->kbdX < 0) {
                this->kbdX = 12;
                this->charIndex = (this->kbdY * 13) + this->kbdX;
            }
        } else if (this->stickAdjX > 30) {
            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->charIndex++;
            this->kbdX++;
            if (this->kbdX > 12) {
                this->kbdX = 0;
                this->charIndex = (this->kbdY * 13) + this->kbdX;
            }
        }
    } else {
        if (this->stickAdjX < -30) {
            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->kbdX--;
            if (this->kbdX < 2) {
                this->kbdX = 4;
            }
        } else if (this->stickAdjX > 30) {
            Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->kbdX++;
            if (this->kbdX > 4) {
                this->kbdX = 3;
            }
        }
    }

    if (this->stickAdjY > 30) {
        Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        this->kbdY--;

        if (this->kbdY < 0) {
            // don't go to bottom row
            if (this->kbdX < 8) {
                this->kbdY = 4;
                this->charIndex = (s32)(this->kbdX + 52);
            } else {
                this->kbdY = 5;
                this->charIndex += 52;
                prevKbdX = this->kbdX;

                if (this->kbdX < 10) {
                    this->kbdX = 3;
                } else if (this->kbdX < 13) {
                    this->kbdX = 4;
                }

                this->unk_1CAD6[this->kbdX] = prevKbdX;
            }
        } else {
            this->charIndex -= 13;

            if (this->kbdY == 4) {
                this->charIndex = 52;
                this->kbdX = this->unk_1CAD6[this->kbdX];
                this->charIndex += this->kbdX;
            }
        }
    } else if (this->stickAdjY < -30) {
        Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        this->kbdY++;

        if (this->kbdY > 5) {
            this->kbdY = 0;
            this->kbdX = this->unk_1CAD6[this->kbdX];
            this->charIndex = this->kbdX;
        } else {
            this->charIndex += 13;

            if (this->kbdY == 5) {
                if (this->kbdX < 8) {
                    this->kbdY = 0;
                    this->charIndex = this->kbdX;
                } else {
                    prevKbdX = this->kbdX;

                    if (this->kbdX < 3) {
                        this->kbdX = 0;
                    } else if (this->kbdX < 6) {
                        this->kbdX = 1;
                    } else if (this->kbdX < 8) {
                        this->kbdX = 2;
                    } else if (this->kbdX < 10) {
                        this->kbdX = 3;
                    } else if (this->kbdX < 13) {
                        this->kbdX = 4;
                    }

                    this->unk_1CAD6[this->kbdX] = prevKbdX;
                }
            }
        }
    }

    if (this->kbdY == 5) {
        this->kbdButton = this->kbdX;
    }
}

/**
 * This function is mostly a copy paste of `FileSelect_StartNameEntry`.
 * The name entry box fades and slides in even though it is not visible.
 * After this is complete, change to the options config mode.
 * Update function for `CM_START_OPTIONS`
 */
void FileSelect_StartOptions(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->nameEntryBoxAlpha += 25;

    if (this->nameEntryBoxAlpha >= 255) {
        this->nameEntryBoxAlpha = 255;
    }

    this->nameEntryBoxPosX -= 30;

    if (this->nameEntryBoxPosX <= 0) {
        this->nameEntryBoxPosX = 0;
        this->nameEntryBoxAlpha = 255;
        this->configMode = CM_OPTIONS_MENU;
    }
}

static u8 sSelectedSetting;

/**
 * Update the cursor and appropriate settings for the options menu.
 * If the player presses B, write the selected options to the SRAM header
 * and set config mode to rotate back to the main menu.
 * Update function for `CM_OPTIONS_MENU`
 */
void FileSelect_UpdateOptionsMenu(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    Input* input = &this->state.input[0];

    if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_L, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        this->configMode = CM_OPTIONS_TO_MAIN;
        sramCtx->readBuff[0] = gSaveContext.audioSetting;
        sramCtx->readBuff[1] = gSaveContext.zTargetSetting;
        osSyncPrintf("ＳＡＶＥ");
        Sram_WriteSramHeader(sramCtx);
        osSyncPrintf(VT_FGCOL(YELLOW));
        osSyncPrintf("sram->read_buff[2] = J_N = %x\n", sramCtx->readBuff[2]);
        osSyncPrintf("sram->read_buff[2] = J_N = %x\n", &sramCtx->readBuff[2]);
        osSyncPrintf("Na_SetSoundOutputMode = %d\n", gSaveContext.audioSetting);
        osSyncPrintf("Na_SetSoundOutputMode = %d\n", gSaveContext.audioSetting);
        osSyncPrintf("Na_SetSoundOutputMode = %d\n", gSaveContext.audioSetting);
        osSyncPrintf(VT_RST);
        func_800F6700(gSaveContext.audioSetting);
        osSyncPrintf("終了\n");
        return;
    }

    if (this->stickAdjX < -30) {
        Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);

        if (sSelectedSetting == FS_SETTING_AUDIO) {
            gSaveContext.audioSetting--;

            // because audio setting is unsigned, can't check for < 0
            if (gSaveContext.audioSetting > 0xF0) {
                gSaveContext.audioSetting = FS_AUDIO_SURROUND;
            }
        } else {
            gSaveContext.zTargetSetting ^= 1;
        }
    } else if (this->stickAdjX > 30) {
        Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);

        if (sSelectedSetting == FS_SETTING_AUDIO) {
            gSaveContext.audioSetting++;

            if (gSaveContext.audioSetting > FS_AUDIO_SURROUND) {
                gSaveContext.audioSetting = FS_AUDIO_STEREO;
            }
        } else {
            gSaveContext.zTargetSetting ^= 1;
        }
    }

    if ((this->stickAdjY < -30) || (this->stickAdjY > 30)) {
        Audio_PlaySfxGeneral(NA_SE_SY_FSEL_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        sSelectedSetting ^= 1;
    } else if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
        Audio_PlaySfxGeneral(NA_SE_SY_FSEL_DECIDE_L, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                             &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        sSelectedSetting ^= 1;
    }
}

typedef struct {
    /* 0x00 */ void* texture[3];
    /* 0x0C */ u16 width[3];
    /* 0x12 */ u16 height;
} OptionsMenuTextureInfo; // size = 0x14

static OptionsMenuTextureInfo sOptionsMenuHeaders[] = {
    {
        { gFileSelOptionsENGTex, gFileSelOptionsENGTex, gFileSelOptionsENGTex },
        { 128, 128, 128 },
        16,
    },
    {
        { gFileSelSOUNDENGTex, gFileSelSOUNDENGTex, gFileSelSOUNDENGTex },
        { 64, 64, 64 },
        16,
    },
    {
        { gFileSelLTargetingENGTex, gFileSelLTargetingENGTex, gFileSelLTargetingENGTex },
        { 64, 144, 64 },
        16,
    },
    {
        { gFileSelCheckBrightnessENGTex, gFileSelCheckBrightnessENGTex, gFileSelCheckBrightnessENGTex },
        { 96, 96, 96 },
        16,
    },
};

static OptionsMenuTextureInfo sOptionsMenuSettings[] = {
    {
        { gFileSelStereoENGTex, gFileSelStereoENGTex, gFileSelStereoENGTex },
        { 48, 48, 48 },
        16,
    },
    {
        { gFileSelMonoENGTex, gFileSelMonoENGTex, gFileSelMonoENGTex },
        { 48, 48, 48 },
        16,
    },
    {
        { gFileSelHeadsetENGTex, gFileSelHeadsetENGTex, gFileSelHeadsetENGTex },
        { 48, 48, 48 },
        16,
    },
    {
        { gFileSelSurroundENGTex, gFileSelSurroundENGTex, gFileSelSurroundENGTex },
        { 48, 48, 48 },
        16,
    },
    {
        { gFileSelSwitchENGTex, gFileSelSwitchENGTex, gFileSelSwitchENGTex },
        { 48, 80, 48 },
        16,
    },
    {
        { gFileSelHoldENGTex, gFileSelHoldENGTex, gFileSelHoldENGTex },
        { 48, 80, 48 },
        16,
    },
};

void FileSelect_DrawOptionsImpl(GameState* thisx) {
    static s16 cursorPrimRed = 255;
    static s16 cursorPrimGreen = 255;
    static s16 cursorPrimBlue = 255;
    static s16 cursorEnvRed = 0;
    static s16 cursorEnvGreen = 0;
    static s16 cursorEnvBlue = 0;
    static s16 cursorPulseDir = 1;
    static s16 cursorFlashTimer = 20;
    static s16 cursorPrimColors[][3] = {
        { 255, 255, 255 },
        { 0, 255, 255 },
    };
    static s16 cursorEnvColors[][3] = {
        { 0, 0, 0 },
        { 0, 150, 150 },
    };
    FileSelectState* this = (FileSelectState*)thisx;
    s16 cursorRed;
    s16 cursorGreen;
    s16 cursorBlue;
    s16 i;
    s16 j;
    s16 vtx;

    OPEN_DISPS(this->state.gfxCtx, "../z_file_nameset_PAL.c", 848);

    cursorRed = ABS(cursorPrimRed - cursorPrimColors[cursorPulseDir][0]) / cursorFlashTimer;
    cursorGreen = ABS(cursorPrimGreen - cursorPrimColors[cursorPulseDir][1]) / cursorFlashTimer;
    cursorBlue = ABS(cursorPrimBlue - cursorPrimColors[cursorPulseDir][2]) / cursorFlashTimer;

    if (cursorPrimRed >= cursorPrimColors[cursorPulseDir][0]) {
        cursorPrimRed -= cursorRed;
    } else {
        cursorPrimRed += cursorRed;
    }

    if (cursorPrimGreen >= cursorPrimColors[cursorPulseDir][1]) {
        cursorPrimGreen -= cursorGreen;
    } else {
        cursorPrimGreen += cursorGreen;
    }

    if (cursorPrimBlue >= cursorPrimColors[cursorPulseDir][2]) {
        cursorPrimBlue -= cursorBlue;
    } else {
        cursorPrimBlue += cursorBlue;
    }

    cursorRed = ABS(cursorEnvRed - cursorEnvColors[cursorPulseDir][0]) / cursorFlashTimer;
    cursorGreen = ABS(cursorEnvGreen - cursorEnvColors[cursorPulseDir][1]) / cursorFlashTimer;
    cursorBlue = ABS(cursorEnvBlue - cursorEnvColors[cursorPulseDir][2]) / cursorFlashTimer;

    if (cursorEnvRed >= cursorEnvColors[cursorPulseDir][0]) {
        cursorEnvRed -= cursorRed;
    } else {
        cursorEnvRed += cursorRed;
    }

    if (cursorEnvGreen >= cursorEnvColors[cursorPulseDir][1]) {
        cursorEnvGreen -= cursorGreen;
    } else {
        cursorEnvGreen += cursorGreen;
    }

    if (cursorEnvBlue >= cursorEnvColors[cursorPulseDir][2]) {
        cursorEnvBlue -= cursorBlue;
    } else {
        cursorEnvBlue += cursorBlue;
    }

    if (--cursorFlashTimer == 0) {
        cursorPrimRed = cursorPrimColors[cursorPulseDir][0];
        cursorPrimGreen = cursorPrimColors[cursorPulseDir][1];
        cursorPrimBlue = cursorPrimColors[cursorPulseDir][2];

        cursorEnvRed = cursorEnvColors[cursorPulseDir][0];
        cursorEnvGreen = cursorEnvColors[cursorPulseDir][1];
        cursorEnvBlue = cursorEnvColors[cursorPulseDir][2];

        cursorFlashTimer = 20;

        if (++cursorPulseDir > 1) {
            cursorPulseDir = 0;
        }
    }
        
    gSPVertex(POLY_OPA_DISP++, D_80811D30, 32, 0);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->titleAlpha[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);

    for (i = 0, vtx = 0; i < 4; i++, vtx += 4) {
        gDPLoadTextureBlock(POLY_OPA_DISP++, sOptionsMenuHeaders[i].texture[gSaveContext.language], G_IM_FMT_IA,
                            G_IM_SIZ_8b, sOptionsMenuHeaders[i].width[gSaveContext.language],
                            sOptionsMenuHeaders[i].height, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(POLY_OPA_DISP++, vtx, vtx + 2, vtx + 3, vtx + 1, 0);
    }

    gSPVertex(POLY_OPA_DISP++, D_80811F30, 32, 0);

    for (i = 0, vtx = 0; i < 4; i++, vtx += 4) {
        gDPPipeSync(POLY_OPA_DISP++);
        if (i == gSaveContext.audioSetting) {
            if (sSelectedSetting == FS_SETTING_AUDIO) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, cursorPrimRed, cursorPrimGreen, cursorPrimBlue,
                                this->titleAlpha[0]);
                gDPSetEnvColor(POLY_OPA_DISP++, cursorEnvRed, cursorEnvGreen, cursorEnvBlue, 255);
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->titleAlpha[0]);
                gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
            }
        } else {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 120, 120, 120, this->titleAlpha[0]);
            gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
        }

        gDPLoadTextureBlock(POLY_OPA_DISP++, sOptionsMenuSettings[i].texture[gSaveContext.language], G_IM_FMT_IA,
                            G_IM_SIZ_8b, sOptionsMenuSettings[i].width[gSaveContext.language],
                            sOptionsMenuHeaders[i].height, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(POLY_OPA_DISP++, vtx, vtx + 2, vtx + 3, vtx + 1, 0);
    }

    for (; i < 6; i++, vtx += 4) {
        gDPPipeSync(POLY_OPA_DISP++);

        if (i == (gSaveContext.zTargetSetting + 4)) {
            if (sSelectedSetting != FS_SETTING_AUDIO) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, cursorPrimRed, cursorPrimGreen, cursorPrimBlue,
                                this->titleAlpha[0]);
                gDPSetEnvColor(POLY_OPA_DISP++, cursorEnvRed, cursorEnvGreen, cursorEnvBlue, 0xFF);
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->titleAlpha[0]);
                gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
            }
        } else {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 120, 120, 120, this->titleAlpha[0]);
            gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
        }

        gDPLoadTextureBlock(POLY_OPA_DISP++, sOptionsMenuSettings[i].texture[gSaveContext.language], G_IM_FMT_IA,
                            G_IM_SIZ_8b, sOptionsMenuSettings[i].width[gSaveContext.language],
                            sOptionsMenuHeaders[i].height, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(POLY_OPA_DISP++, vtx, vtx + 2, vtx + 3, vtx + 1, 0);
    }

    gDPPipeSync(POLY_OPA_DISP++);

    // check brightness bars
    gDPLoadTextureBlock_4b(POLY_OPA_DISP++, gFileSelBrightnessCheckTex, G_IM_FMT_IA, 96, 16, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 55, 55, 55, this->titleAlpha[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, 40, 40, 40, 255);
    gSP1Quadrangle(POLY_OPA_DISP++, vtx, vtx + 2, vtx + 3, vtx + 1, 0);

    vtx += 4;

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 30, 30, 30, this->titleAlpha[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSP1Quadrangle(POLY_OPA_DISP++, vtx, vtx + 2, vtx + 3, vtx + 1, 0);

    vtx += 4;

    // blue divider lines
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 255, 255, this->titleAlpha[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    gDPLoadTextureBlock_4b(POLY_OPA_DISP++, gFileSelOptionsDividerTex, G_IM_FMT_IA, 256, 2, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);

    Matrix_Push();
    Matrix_Translate(0.0f, 0.1f, 0.0f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx, "../z_file_nameset_PAL.c", 1009),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(POLY_OPA_DISP++, gOptionsDividerTopVtx, 4, 0);
    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
    Matrix_Pop();

    Matrix_Push();
    Matrix_Translate(0.0f, 0.2f, 0.0f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx, "../z_file_nameset_PAL.c", 1021),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(POLY_OPA_DISP++, gOptionsDividerMiddleVtx, 4, 0);
    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
    Matrix_Pop();

    Matrix_Push();
    Matrix_Translate(0.0f, 0.4f, 0.0f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx, "../z_file_nameset_PAL.c", 1033),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(POLY_OPA_DISP++, gOptionsDividerBottomVtx, 4, 0);
    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
    Matrix_Pop();

    CLOSE_DISPS(this->state.gfxCtx, "../z_file_nameset_PAL.c", 1040);
}

void FileSelect_DrawOptions(GameState* thisx) {
    FileSelect_DrawOptionsImpl(thisx);
}

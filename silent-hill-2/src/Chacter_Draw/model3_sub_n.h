#ifndef MODEL3_SUB_N_H
#define MODEL3_SUB_N_H

#include "sh2_common.h"

void Model3Init(void);

void sh2_Model3UpdateTextures(sh_Model* model);

void Model3UpdateMatrices(Model* model, ModelWork* work, float (* mwm)[4], int model_type);

void Model3UpdateEnvelopeMatrices(Model* model, ModelWork* work); // @note second arg not in dwarf

void Model3UpdateLightEnv(Model* model, ModelWork* work); // @note args not in dwarf

void Model3UpdateGlobalAmbient(void);

#endif

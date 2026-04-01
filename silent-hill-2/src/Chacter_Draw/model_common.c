#include "model_common.h"

static int initialized = 0;
static ModelCommonWork model_common_work_db[2];
static int model_common_work_page;

ModelCommonWork* model_common_work;

void ModelCommonWorkInit(void) {
    if (initialized == 0) {
        model_common_work_page = 0;
        model_common_work = model_common_work_db;

        initialized = 1;
    }
}

void ModelCommonWorkFlip(void) {
    model_common_work = model_common_work_db + (model_common_work_page ^= 1);
}

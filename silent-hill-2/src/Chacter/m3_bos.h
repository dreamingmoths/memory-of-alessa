#ifndef M3_BOS_H
#define M3_BOS_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyBOSLow(SubCharacter* scp);
int shCharacterEnemyBOSAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyBOSAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyBOSAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);
int shCharacterEnemySCUAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyMKNAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyTYUAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyREDAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyONIAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyNSEAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyIKEAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyPAPAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyEDBAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyARMAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
int shCharacterEnemyBOSAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);

#endif // M3_BOS_H

#ifndef M3_BOS_H
#define M3_BOS_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyBOSLow(SubCharacter* scp);
int shCharacterEnemyBOSAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyBOSAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyBOSAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);
int shCharacterEnemySCUAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyMKNAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyTYUAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyREDAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyONIAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyNSEAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyIKEAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyPAPAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyEDBAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyARMAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
int shCharacterEnemyBOSAnimeSetP(struct SubCharacter * scp /* r17 */, signed int anime_id /* r18 */, signed int comp /* r16 */);
#endif // M3_BOS_H

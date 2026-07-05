#include "Chacter/player_result.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2dt.h"
#include "vec.h"

void GameTimerCountUp(void) {
    playing.time += shGetDT();
}

void GameMoveDistanceCountUp(struct SubCharacter* scp, int status) {
    float distance = vec3_dist((float*) &scp->pos, (float*) &scp->b_pos);
    
    if (distance < 200.0f) {
        switch (status) {
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                playing.run_distance += distance;
                break;
            default:
                playing.walk_distance += distance;
                break;
        }
    }
}
void GameKillEnemyCountUp(u_short atk /* r2 */) {
    switch (atk) {
        case 1:
        case 2:
        case 4:
        case 6:
            playing.kill_by_shot++;
            break;
        default:
            playing.kill_by_fight++;
            break;
    }    
}

void GameBoatTimerCountUp(void) {
    playing.boat_clear_time += shGetDT();
}

void GameBoatMaxSpeedCheck(float spd) {
    if (!(spd <= playing.boat_max_speed)) {
        playing.boat_max_speed = spd;
    }
}

void GameItemGetCountUp(void) {
    playing.item_get++;
}

void GameJamesDamagedCountUp(float damage) {
    playing.jms_damage_total += damage;
}

void GameMariaDamagedCountUp(u_short atk, float damage) {
    if (atk >= 36) {
        playing.mar_damage_by_enemy += damage;
        return;
    }
    playing.mar_damage_by_jms += damage;
}

u_int GameCalcRankSaveCount(void) {
    if (playing.savecount < 3) return 5;        
    if (playing.savecount < 6) return 4;
    if (playing.savecount < 11) return 3;
    if (playing.savecount < 21) return 2;
    return playing.savecount < 31;
}


u_int GameCalcRankEndingKind(void) {
    u_int result = 0; // r2

    if ((playing.clear_end_kind | 1) != 0) {
        result += 4;
    }
    if ((playing.clear_end_kind | 2) != 0) {
        result += 4;
    }
    if ((playing.clear_end_kind | 4) != 0) {
        result += 4;
    }
    if ((playing.clear_end_kind | 8) != 0) {
        result += 4;
    }
    if ((playing.clear_end_kind | 16) != 0) {
        result += 4;
    }
    return result;
}

u_int GameCalcRankBattleLevel(void) {
    switch (playing.battle_level) { 
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 5;
        default:
            ASSERT_ON_LINE(0, 264);

    }
}

u_int GameCalcRankRiddleLevel(void) {
    switch (playing.riddle_level) { 
        case 0:
            return 1;
        case 1:
            return 3;
        case 2:
            return 5;
        default:
            ASSERT_ON_LINE(0, 292);
        }
}

u_int GameCalcRankItemGet(void) {
    if (100 < playing.item_get) {
        return 10;
    }
    return (playing.item_get / 10) + (playing.item_get >> 31);
}

u_int GameCalcRankHiddenItemGet(void) {
    u_int result = 0;

    if (playing.hidden_item_get & 1) {
        result++;
    }
    if (playing.hidden_item_get & 2) {
        result++;
    }
    if (playing.hidden_item_get & 4) {
        result += 3;
    }
    return result;
}

u_int GameCalcRankKillByShot(void) {
    if (150 < playing.kill_by_shot) {
        return 15;
    }
    return (playing.kill_by_shot / 10) + (playing.kill_by_shot >> 31);
}

u_int GameCalcRankKillByFight(void) {
    if (150 < playing.kill_by_fight) {
        return 15;
    }
    return (playing.kill_by_fight / 10) + (playing.kill_by_fight >> 31);
}

u_int GameCalcRankClearTime(void) {
    float time; // r1

    time = playing.time / 60.0f;
    if (time <= 120.0f) {
        return 10;
    }
    if (time <= 180.0f) {
        return 5;
    }
    if (time <= 240.0f) {
        return 3;
    }
    if (time <= 360.0f) {
        return 2;
    }
    if (!(time <= 720.0f)) {
        return 0;
    }
    return 1;
}

u_int GameCalcRankBoatClearTime(void) {
    if (playing.boat_clear_time <= 60.0f) {
        return 5;
    }
    if (playing.boat_clear_time <= 120.0f) {
        return 4;
    }
    if (playing.boat_clear_time <= 240.0f) {
        return 3;
    }
    if (playing.boat_clear_time <= 480.0f) {
        return 2;
    }
    if (!(playing.boat_clear_time <= 960.0f)) {
        return 0;
    }
    return 1;
}

u_int GameCalcRankJamesDamage(void) {
    if (playing.jms_damage_total <= 200.0f) {
        return 5;
    }
    if (playing.jms_damage_total <= 400.0f) {
        return 4;
    }
    if (playing.jms_damage_total <= 800.0f) {
        return 3;
    }
    if (playing.jms_damage_total <= 1600.0f) {
        return 2;
    }
    if (!(playing.jms_damage_total <= 3200.0f)) {
        return 0;
    }
    return 1;
}

u_int GameCalcRankTotal(void) {
    return GameCalcRankSaveCount() 
            + GameCalcRankEndingKind()
            + GameCalcRankBattleLevel()
            + GameCalcRankRiddleLevel()
            + GameCalcRankItemGet()
            + GameCalcRankHiddenItemGet()
            + GameCalcRankKillByShot()
            + GameCalcRankKillByFight()
            + GameCalcRankClearTime()
            + GameCalcRankBoatClearTime()
            + GameCalcRankJamesDamage();
}

void GameSavePreviousTotalRank(void) {
    playing.rank = GameCalcRankTotal();
}

void GameSaveSprayPower(void) {
    if (playing.rank < 6) {
        playing.spray_pow = -1;
        return;
    }
    if (playing.rank < 80) {
        playing.spray_pow = 0;
        return;
    }
    if (playing.rank < 100) {
        playing.spray_pow = 1;
        return;
    }
    playing.spray_pow = 2;
}

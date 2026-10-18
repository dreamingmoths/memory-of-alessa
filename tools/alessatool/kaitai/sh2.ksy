meta:
  id: sh2
  endian: le
  bit-endian: le

types:
  q:
    instances:
      u128:
        pos: 0
        type: u16

      u64:
        pos: 0
        type: u8
        repeat: expr
        repeat-expr: 2

      u32:
        pos: 0
        type: u4
        repeat: expr
        repeat-expr: 4

      u16:
        pos: 0
        type: u2
        repeat: expr
        repeat-expr: 8

      u8:
        pos: 0
        type: u1
        repeat: expr
        repeat-expr: 16

      s64:
        pos: 0
        type: s8
        repeat: expr
        repeat-expr: 2

      s32:
        pos: 0
        type: s4
        repeat: expr
        repeat-expr: 4

      s16:
        pos: 0
        type: s2
        repeat: expr
        repeat-expr: 8

      s8:
        pos: 0
        type: s1
        repeat: expr
        repeat-expr: 16

      q:
        pos: 0
        type: s4
        repeat: expr
        repeat-expr: 4

      fv:
        pos: 0
        type: f4
        repeat: expr
        repeat-expr: 4

      iv:
        pos: 0
        type: s4
        repeat: expr
        repeat-expr: 4

    seq:
      - size: 16

  q_worddata:
    instances:
      ui32:
        pos: 0
        type: u4
        repeat: expr
        repeat-expr: 4

      us16:
        pos: 0
        type: u2
        repeat: expr
        repeat-expr: 8

      fl32:
        pos: 0
        type: f4
        repeat: expr
        repeat-expr: 4

      uc8:
        pos: 0
        type: u1
        repeat: expr
        repeat-expr: 16

      si32:
        pos: 0
        type: s4
        repeat: expr
        repeat-expr: 4

      ss16:
        pos: 0
        type: s2
        repeat: expr
        repeat-expr: 8

      sc8:
        pos: 0
        type: s1
        repeat: expr
        repeat-expr: 16

      ul64:
        pos: 0
        type: u8
        repeat: expr
        repeat-expr: 2

      ul128:
        pos: 0
        type: u16

    seq:
      - size: 16

  vector4:
    seq:
      - id: x
        type: f4

      - id: y
        type: f4

      - id: z
        type: f4

      - id: w
        type: f4

  i_vector4:
    seq:
      - id: x
        type: s4

      - id: y
        type: s4

      - id: z
        type: s4

      - id: w
        type: s4

  matrix4:
    seq:
      - id: d
        type: f4
        repeat: expr
        repeat-expr: 16

  sh_skelton:
    seq:
      - id: next
        type: pointer('sh_skelton')

      - id: parent
        type: pointer('sh_skelton')

      - size: 8

      - id: src_m
        type: matrix4

      - id: src_t
        type: vector4

      - id: des_m
        type: matrix4

      - id: des_t
        type: vector4

      - id: axis
        type: vector4

      - id: theta
        type: f4

      - id: xx
        type: f4

      - id: yy
        type: f4

      - id: zz
        type: f4

      - id: xy
        type: f4

      - id: yz
        type: f4

      - id: zx
        type: f4

      - id: c_count
        type: u2

      - id: c_speed
        type: u2

      - id: change
        type: s1

      - id: reserved
        type: s1

      - id: is_key
        type: s1

      - id: pad
        type: s1

      - id: untouchable
        type: pointer('data')

      - size: 8

  sh_skelton_work:
    seq:
      - id: work
        type: sh_skelton
        repeat: expr
        repeat-expr: 400

      - id: free
        type: pointer('sh_skelton')

      - id: last
        type: s4

      - size: 8

  usxy:
    seq:
      - id: x
        type: u2

      - id: y
        type: u2

  sxy:
    seq:
      - id: x
        type: s2

      - id: y
        type: s2

  ixy:
    seq:
      - id: x
        type: s4

      - id: y
        type: s4

  anime_info:
    seq:
      - id: name
        type: u2

      - id: frame
        type: u2

      - id: speed
        type: s2

      - id: start
        type: u2

      - id: end
        type: u2

      - id: loop
        type: u1

      - id: pad
        type: s1

  sh_cluster_anime:
    seq:
      - id: data
        type: pointer('data')

      - id: used
        type: u1

      - id: n_clusters
        type: u1

      - id: is_repeat
        type: u1

      - id: frame_updated
        type: u1

      - id: frame_no
        type: s4

      - id: weights
        type: pointer('data')

  element1:
    seq:
      - id: frame
        type: u2

      - id: weight
        type: s2

  cluster1:
    seq:
      - id: n_keys
        type: u2

      - id: elements
        type: element1
        repeat: eos

  sh_anime3d:
    seq:
      - id: top
        type: pointer('sh_skelton')

      - id: anime
        type: pointer('data')

      - id: frame_top
        type: pointer('data')

      - id: p_anime
        type: pointer('data')

      - id: p_frame_top
        type: pointer('data')

      - id: frame_size
        type: u4

      - id: total_count
        type: s4

      - id: c_count
        type: ixy

      - id: c_speed
        type: sxy

      - id: total_speed
        type: sxy

      - id: cur_frame
        type: usxy

      - id: first_bone_type
        type: s1

      - id: comp_type
        type: s1

      - size: 2

      - id: anim_a
        type: pointer('anime_info')

      - id: anim_b
        type: pointer('anime_info')

      - size: 4

      - id: rot_neck
        type: vector4

      - id: rot_arms
        type: vector4

      - id: rot_body_neck
        type: vector4

      - id: rot_body
        type: vector4

      - id: scale
        type: f4

      - size: 12

  cluster_anime_work:
    seq:
      - id: ca
        type: sh_cluster_anime
        repeat: expr
        repeat-expr: 32

  sh_battle_area:
    seq:
      - id: center
        type: f4

      - id: radius
        type: f4

  cl_hitpoly_head:
    seq:
      - id: kind
        type: u1

      - id: shape
        type: u1

      - id: pad
        type: u2

      - id: weight
        type: u4

      - id: material
        type: u4

      - id: flg
        type: s4

  cl_vhit_wall:
    seq:
      - id: cp
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: nl
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: pd
        type: pointer('cl_hitpoly_head')

      - size: 12

  cl_vhit_chara:
    seq:
      - id: sc
        type: pointer('sub_character')

      - size: 12

      - id: cp
        type: f4
        repeat: expr
        repeat-expr: 4

  cl_vhit_result:
    seq:
      - id: kind
        type: s4

      - size: 12

      - id: hobj
        type: cl_vhit_result_anon_1
        size: 48

  cl_vhit_result_anon_1:
    instances:
      wall:
        pos: 0
        type: cl_vhit_wall

      chara:
        pos: 0
        type: cl_vhit_chara

    seq:
      - size: 48

  sh_battle_info:
    seq:
      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: vec
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: id
        type: u2

      - id: kind
        type: u2

      - id: dead_timer
        type: f4

      - id: damage
        type: f4

      - id: shock
        type: f4

      - id: atk_result
        type: s4

      - size: 12

      - id: prev_atk_pos
        type: vector4

      - id: target
        type: pointer('sub_character')

      - id: hp
        type: f4

      - id: hp_max
        type: f4

      - id: hp_rate
        type: f4

      - id: status
        type: u4

      - id: look
        type: sh_battle_area

      - id: feel
        type: sh_battle_area

      - id: se
        type: u1

      - size: 11

  sub_character:
    seq:
      - id: index
        type: s4

      - id: status
        type: u4

      - id: sub_status
        type: u4

      - id: sub_st
        type: u4

      - id: kind
        type: s2

      - id: id
        type: s2

      - id: step
        type: u4

      - id: model_type
        type: u4

      - size: 4

      - id: pos
        type: vector4

      - id: rot
        type: vector4

      - id: pos_spd
        type: vector4

      - id: rot_spd
        type: vector4

      - id: mat
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: sk_top
        type: pointer('sh_skelton')

      - id: eye_y
        type: f4

      - id: center_y
        type: f4

      - id: spd
        type: f4

      - id: spd_org
        type: f4

      - id: spd_y
        type: f4

      - id: spd_roty
        type: f4

      - size: 4

      - id: grnd_normal
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: grnd_height
        type: f4

      - size: 12

      - id: b_pos
        type: vector4

      - id: b_rot
        type: vector4

      - id: en_first_status
        type: s4

      - id: colis_fall_timer
        type: s4

      - size: 8

      - id: battle
        type: sh_battle_info

      - id: eye
        type: cl_vhit_result

      - id: function
        type: pointer('data')

      - id: effecter_function
        type: pointer('data')

      - id: pre
        type: pointer('sub_character')

      - id: next
        type: pointer('sub_character')

      - id: work
        type: u1
        repeat: expr
        repeat-expr: 4

      - id: enemy_p
        type: pointer('data')

      - size: 8

  sh2gfw_model_draw_man:
    seq:
      - id: chara_id
        type: u4

      - id: test_sub_char
        type: pointer('sub_character')

      - id: model_head
        type: pointer('data')

      - id: p_model_header
        type: pointer('data')

      - id: sh_model
        type: pointer('data')

      - id: p_anime
        type: pointer('data')

      - id: p_cluster
        type: pointer('data')

      - id: p_kg1_work
        type: pointer('data')

      - id: allnum
        type: s2

      - id: nowtex
        type: s2

      - id: tb_change_vu1num
        type: u2

      - id: tb_change_vu1now
        type: u2

      - id: tb_change_vu1
        type: u2
        repeat: expr
        repeat-expr: 4

      - id: tb_index_vu1
        type: u2
        repeat: expr
        repeat-expr: 4

      - id: tb_change_vu0num
        type: u2

      - id: tb_change_vu0now
        type: u2

      - id: tb_change_vu0
        type: u2
        repeat: expr
        repeat-expr: 2

      - id: tb_index_vu0
        type: u2
        repeat: expr
        repeat-expr: 2

      - id: chr_slotid
        type: s4
        repeat: expr
        repeat-expr: 6

      - id: chr_cid
        type: s4
        repeat: expr
        repeat-expr: 6

      - id: d1cid
        type: s4

      - id: d2c1d
        type: s4

      - id: p_tex_man
        type: pointer('data')
        repeat: expr
        repeat-expr: 6

  sub_character_disp:
    seq:
      - id: sc
        type: sub_character

      - id: anime2
        type: sh_anime3d

      - id: anime
        type: sh_anime3d

      - id: cluster_anime
        type: pointer('sh_cluster_anime')

      - id: models
        type: pointer('data')
        repeat: expr
        repeat-expr: 3

      - id: work
        type: pointer('data')

      - id: data
        type: pointer('data')

      - id: model_adr
        type: u4

      - id: anime_adr
        type: u4

      - id: clani_adr
        type: u4

      - id: anime_list
        type: pointer('data')

      - id: clani_list
        type: pointer('data')

      - size: 4

  sh_character_all:
    seq:
      - id: work
        type: sub_character_disp
        repeat: expr
        repeat-expr: 32

      - id: free
        type: pointer('sub_character_disp')

      - id: head
        type: pointer('sub_character')

      - id: player
        type: pointer('sub_character')

      - id: total
        type: s1

      - size: 3

  en_path_data:
    seq:
      - id: angle
        type: f4

      - id: markangle
        type: f4

      - id: dist
        type: f4

      - id: step
        type: s1

      - id: deadend
        type: s1

      - id: timer
        type: s2

  en_ambush_data:
    seq:
      - id: pl_x_min
        type: f4

      - id: pl_z_min
        type: f4

      - id: pl_x_max
        type: f4

      - id: pl_z_max
        type: f4

      - id: pos_x
        type: f4

      - id: pos_z
        type: f4

      - id: dir
        type: f4

  en_scu_data:
    seq:
      - id: stpos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: target
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: ambush
        type: pointer('en_ambush_data')

      - id: count
        type: s4

      - id: dc
        type: s1

      - id: dcm
        type: s1

      - size: 2

  en_mkn_data:
    seq:
      - id: stpos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: target
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: tp
        type: pointer('data')

      - id: fall
        type: f4

      - id: frame
        type: s2

      - id: dc
        type: s1

      - id: dcm
        type: s1

  en_communication:
    seq:
      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: kind
        type: s4

      - id: type
        type: s4

      - id: time
        type: s4

      - id: dist
        type: f4

  en_tyu_data:
    seq:
      - id: point
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: tcomm
        type: pointer('en_communication')

      - id: near_count
        type: s4

      - id: dist
        type: f4

      - id: count
        type: s2

      - id: moves
        type: s1

      - size: 1

  en_red_data:
    seq:
      - id: attack_count
        type: s4

      - id: boss_timer
        type: s4

      - id: tp
        type: pointer('data')

  en_oni_data:
    seq:
      - id: id
        type: s1

      - id: check
        type: s1

      - id: warp
        type: s1

      - size: 1

      - id: timer2
        type: s2

      - size: 2

      - id: other
        type: pointer('data')

      - id: tp
        type: pointer('data')

  en_nse_data:
    seq:
      - id: speed
        type: f4

      - id: tspeed
        type: f4

      - id: signs
        type: s1

      - id: count
        type: s1

      - id: dc
        type: s1

      - id: dcm
        type: s1

  en_ike_data:
    seq:
      - id: handpos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: swing
        type: f4

      - id: near_count
        type: s4

      - id: dist
        type: f4

      - id: direc
        type: s1

      - id: signs
        type: s1

      - id: count
        type: s1

      - id: pipe_count
        type: s1

  en_pap_data:
    seq:
      - id: target
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: dc
        type: s1

      - id: dcm
        type: s1

      - id: signs
        type: s1

      - id: count
        type: s1

  en_edb_data:
    seq:
      - id: target
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rot
        type: f4

      - id: arot
        type: f4

      - id: speed
        type: f4

      - id: bullet
        type: s1

      - id: mark
        type: s1
        repeat: expr
        repeat-expr: 3

      - id: mark_n
        type: s1

      - id: turn
        type: s1

      - id: afford
        type: s1

      - id: ccount
        type: s1

      - id: pcount
        type: s1

      - size: 3

  en_arm_data:
    seq:
      - id: hand_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: old_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: near_count
        type: s4

      - id: dist
        type: f4

      - id: arm
        type: s1

      - id: attack
        type: s1

      - id: scount
        type: s1

      - id: signs
        type: s1

      - id: count
        type: s1

      - id: dir
        type: s1

      - size: 2

  en_bos_data:
    seq:
      - id: target
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: insect_dp
        type: pointer('data')

      - id: near_count
        type: s4

      - id: dist
        type: f4

      - id: move_speed
        type: f4

      - id: rot_speed
        type: f4

      - id: rot_add
        type: f4

      - id: y_speed
        type: f4

      - id: mode
        type: s4

      - id: end_count
        type: s4

      - id: signs
        type: s1

      - id: count
        type: s1

      - size: 2

  en_nik_data:
    seq:
      - id: swing
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: acc
        type: f4
        repeat: expr
        repeat-expr: 4

  en_ins_data:
    seq:
      - id: view_rot
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rot_add
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: leader
        type: pointer('data')

      - id: def_speed
        type: f4

      - id: move_speed
        type: f4

      - id: speed_add
        type: f4

      - id: rot_speed
        type: f4

      - id: y_speed
        type: f4

      - id: twin_dist
        type: f4

      - id: dist_add
        type: f4

  en_local_data:
    seq:
      - id: kind
        type: s1

      - id: kind2
        type: s1

      - id: mlv
        type: s1

      - id: slv
        type: s1

      - id: sslv
        type: s1

      - id: type
        type: s1

      - id: weight
        type: u1

      - id: lie
        type: s1

      - id: d_count
        type: s1

      - id: last_atk
        type: s1

      - id: anim
        type: s1

      - id: anim_loop
        type: u1

      - id: anim_s
        type: s2

      - size: 2

      - id: flag
        type: u4

      - id: anim_n
        type: s4

      - id: anim_step
        type: s4

      - id: scp
        type: pointer('sub_character')

      - id: path
        type: en_path_data

      - id: vec
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: endurance
        type: f4

      - id: endurance_max
        type: f4

      - id: hb_x
        type: f4

      - id: hb_z
        type: f4

      - id: hb_s
        type: f4

      - id: tx
        type: f4

      - id: tz
        type: f4

      - id: tx2
        type: f4

      - id: tz2
        type: f4

      - id: trx
        type: f4

      - id: trz
        type: f4

      - id: size
        type: f4

      - id: new_size
        type: f4

      - id: tall
        type: f4

      - id: new_tall
        type: f4

      - id: center_y
        type: f4

      - id: new_center
        type: f4

      - id: eye_y
        type: f4

      - id: new_eye
        type: f4

      - id: p_dist
        type: f4

      - id: radio
        type: f4

      - id: timer
        type: s4

      - id: sound_wait
        type: s4

      - id: randseed
        type: s4

      - type: en_local_data_anon_2
        size: 64

  en_local_data_anon_2:
    instances:
      scu:
        pos: 0
        type: en_scu_data

      mkn:
        pos: 0
        type: en_mkn_data

      tyu:
        pos: 0
        type: en_tyu_data

      red:
        pos: 0
        type: en_red_data

      oni:
        pos: 0
        type: en_oni_data

      nse:
        pos: 0
        type: en_nse_data

      ike:
        pos: 0
        type: en_ike_data

      pap:
        pos: 0
        type: en_pap_data

      edb:
        pos: 0
        type: en_edb_data

      arm:
        pos: 0
        type: en_arm_data

      bos:
        pos: 0
        type: en_bos_data

      nik:
        pos: 0
        type: en_nik_data

      ins:
        pos: 0
        type: en_ins_data

    seq:
      - size: 64

  ci_sub_character:
    seq:
      - id: status
        type: u4

      - id: sub_status
        type: u4

      - id: sub_st
        type: u4

      - id: kind
        type: s2

      - id: id
        type: s2

      - id: pos
        type: vector4

      - id: rot
        type: vector4

      - id: pos_spd
        type: vector4

      - id: ot_spd
        type: vector4

      - id: b_pos
        type: vector4

      - id: b_rot
        type: vector4

      - id: en_first_status
        type: s4

      - id: eye_y
        type: f4

      - id: center_y
        type: f4

      - id: spd
        type: f4

      - id: spd_org
        type: f4

      - id: spd_y
        type: f4

      - id: spd_roty
        type: f4

      - id: battle_hp
        type: f4

      - id: battle_hp_max
        type: f4

      - id: battle_hp_rate
        type: f4

      - id: battle_status
        type: u4

      - size: 4

  cl_hitpoly_column:
    seq:
      - id: kind
        type: u1

      - id: shape
        type: u1

      - id: pad
        type: u2

      - id: weight
        type: u4

      - id: material
        type: u4

      - id: flg
        type: s4

      - id: p
        type: f4
        repeat: expr
        repeat-expr: 8

  pad_3d:
    seq:
      - id: round_way
        type: s1

      - id: reserved1
        type: u1

      - id: lslide
        type: u1

      - id: rslide
        type: u1

      - id: lturn180
        type: u1

      - id: rturn180
        type: u1

  pad_2d:
    seq:
      - id: pow
        type: u1

      - id: lower_motion
        type: u1

      - size: 2

      - id: dir
        type: f4

  pad_info:
    seq:
      - id: action
        type: u1

      - id: dash
        type: u1

      - id: attack0
        type: u1

      - id: attack1
        type: u1

      - id: attack2
        type: u1

      - id: menu
        type: u1

      - id: hold
        type: u1

      - id: search
        type: u1

      - id: map
        type: u1

      - id: light_
        type: b4

      - id: light
        type: b4

      - id: l_button
        type: u1

      - id: r_button
        type: u1

      - id: lstick_x
        type: s1

      - id: lstick_y
        type: s1

      - id: rstick_x
        type: s1

      - id: rstick_y
        type: s1

      - id: forward
        type: u1

      - id: backward
        type: u1

      - id: lround
        type: u1

      - id: rround
        type: u1

      - id: skip
        type: u1

      - id: pause
        type: u1

      - size: 2

      - type: pad_info_anon_3
        size: 8

  pad_info_anon_3:
    instances:
      pad3d:
        pos: 0
        type: pad_3d

      pad2d:
        pos: 0
        type: pad_2d

    seq:
      - size: 8

  sh_player_work:
    seq:
      - id: player
        type: pointer('sub_character')

      - size: 12

      - id: dist_rot
        type: vector4

      - id: dist_pos
        type: vector4

      - id: pos
        type: vector4

      - id: rot
        type: vector4

      - id: rot_y
        type: f4

      - id: inner_to_wall
        type: f4

      - id: dist_to_wall
        type: f4

      - id: dir_tgt_2d
        type: f4

      - id: dir_now_2d
        type: f4

      - id: map_mode
        type: u1

      - id: reserve0
        type: u1

      - id: step
        type: u1

      - id: sub_step
        type: u1

      - id: timer
        type: u2

      - id: timer2
        type: u2

      - id: allbody_now
        type: u4

      - id: upper_now
        type: u1

      - id: lower_now
        type: u1

      - size: 2

      - id: allbody_prev
        type: u4

      - id: upper_prev
        type: u1

      - id: lower_prev
        type: u1

      - id: event_status_now
        type: u1

      - id: event_status_prev
        type: u1

      - id: event_move_mode
        type: u1

      - id: reserve1
        type: u1

      - size: 2

      - id: upper_st_flg
        type: u4

      - id: lower_st_flg
        type: u4

      - id: u_anime_st_flg
        type: u4

      - id: l_anime_st_flg
        type: u4

      - id: anime_pause
        type: u4

      - id: act_with_wep
        type: u4

      - id: light_vec_inner_rate
        type: f4

      - size: 4

      - id: light_pos_revise
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_vec_revise
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_vec
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_pos_revise_reverse
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_vec_revise_reverse
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_pos_reverse
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_vec_reverse
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_vec_neck
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: room_name_prev
        type: s4

      - id: room_name_now
        type: s4

      - size: 8

      - id: r_side
        type: cl_vhit_result

      - id: l_side
        type: cl_vhit_result

      - id: foot
        type: cl_vhit_result

      - id: ft_floor
        type: cl_vhit_result

      - id: r_foot
        type: cl_vhit_result

      - id: l_foot
        type: cl_vhit_result

      - id: column_mov
        type: cl_hitpoly_column

      - id: column_atk
        type: cl_hitpoly_column

      - id: col_mov_z_hosei
        type: f4

      - id: col_atk_z_hosei
        type: f4

      - id: wep_no_hit_floor
        type: u1

      - id: efct_upper
        type: u1

      - id: light_reverse
        type: u1

      - id: water_road
        type: u1

      - id: pad
        type: pad_info
        repeat: expr
        repeat-expr: 10

      - id: rstick_x
        type: f4

      - id: rstick_y
        type: f4

      - id: lstick_x
        type: f4

      - id: lstick_y
        type: f4

      - id: lstick_p
        type: f4

      - id: cam_rot_y
        type: f4
        repeat: expr
        repeat-expr: 2

      - id: now_cam_no
        type: u1

      - id: cam_chg_flg
        type: u1

      - id: ctrl_unit
        type: u1

      - id: ctrl_inputing
        type: u1

      - id: se_upper
        type: u1
        repeat: expr
        repeat-expr: 4

      - id: se_foot
        type: u1
        repeat: expr
        repeat-expr: 4

      - id: csaw_se_vol
        type: f4

      - id: csaw_se_flg
        type: u1

      - id: d_shock
        type: u1

      - id: reserve2
        type: u1

      - id: strike_splash_flg
        type: u1

      - id: event_anime
        type: s4

      - id: tgt_body_angle
        type: vector4

      - id: tgt_neck_angle
        type: vector4

      - id: tgt_arms_angle
        type: vector4

      - id: hold_chg
        type: u1
        repeat: expr
        repeat-expr: 2

      - id: hold_loop
        type: u1
        repeat: expr
        repeat-expr: 2

      - id: motion_no
        type: u1

      - id: shotgun_dir
        type: u1

      - id: shotgun_prev
        type: u1

      - id: guard_check
        type: u1

      - id: parts_light
        type: s4

      - id: parts_rhand
        type: s4

      - id: parts_lhand
        type: s4

      - id: target
        type: pointer('sub_character')

      - id: look_tgt
        type: pointer('sub_character')

      - id: non_input
        type: f4

      - id: hugging_gauge
        type: f4

      - id: running_time
        type: f4

      - id: muteki_time
        type: f4

      - id: hp
        type: f4

      - id: hp_max
        type: f4

      - id: hp_recover
        type: f4

      - id: shock
        type: f4

      - id: spray_time
        type: f4

      - id: tired
        type: s4

      - id: tired_max
        type: s4

      - id: spirit
        type: s4

      - id: enemy_liedown
        type: pointer('sub_character')

      - id: enemy_around
        type: u1

      - id: enemy_atk_area
        type: u1

      - id: enemy_near
        type: u1

      - id: lock_on
        type: u1

      - id: running
        type: u1

      - id: cannot_run
        type: u1

      - id: fall_type
        type: u1

      - id: reload
        type: u1

      - id: weapon
        type: u1

      - id: shoot_val
        type: u1

      - id: reload_val
        type: u1

      - id: atk_type
        type: u1

      - id: atk_reserve
        type: u1
        repeat: expr
        repeat-expr: 2

      - id: attack_ok
        type: u1

      - id: hold_type
        type: s1

      - id: dead
        type: u1

      - id: no_damage
        type: u1

      - id: atk_count
        type: u1

      - id: hug_status
        type: u1

      - id: hug_dir
        type: u1

      - id: se_on
        type: u1

      - id: spray_set
        type: u1

      - id: spray_pow
        type: s1

      - id: damage_no
        type: u2

      - id: attack_no
        type: u2

      - size: 4

  sh_chara_info:
    seq:
      - id: pos
        type: vector4

      - id: rot
        type: vector4

      - id: pos_spd
        type: vector4

      - id: rot_spd
        type: vector4

      - id: mat
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: sk_top
        type: pointer('sh_skelton')

      - size: 12

  character_info:
    seq:
      - id: spray_time
        type: f4

      - id: running_time
        type: f4

      - id: tired
        type: s4

      - id: tired_max
        type: s4

      - id: spirit
        type: s4

      - id: weapon
        type: s4

      - id: spray_set
        type: u1

      - size: 7

      - id: ci_sc
        type: ci_sub_character
        repeat: expr
        repeat-expr: 32

      - id: total
        type: s1

      - size: 15

  sh_maria_work:
    seq:
      - id: mar_p
        type: pointer('sub_character')

      - size: 12

      - id: dist_rot
        type: vector4

      - id: dist_pos
        type: vector4

      - id: pos
        type: vector4

      - id: rot
        type: vector4

      - id: to_target
        type: f4

      - size: 12

      - id: tgt_pos
        type: f4
        repeat: expr
        repeat-expr: 20

      - id: tgt_pointer
        type: s4

      - id: pushed_dir
        type: s4

      - id: main_status_now
        type: u1

      - id: main_status_prev
        type: u1

      - id: sub_status_now
        type: u1

      - id: sub_status_prev
        type: u1

      - id: sub_st_flg
        type: u4

      - id: anime_st_flg
        type: u4

      - id: anime_pause
        type: u4

      - size: 8

      - id: r_forward
        type: cl_vhit_result

      - id: l_forward
        type: cl_vhit_result

      - id: forward
        type: cl_vhit_result

      - id: ft_floor
        type: cl_vhit_result

      - id: r_foot
        type: cl_vhit_result

      - id: l_foot
        type: cl_vhit_result

      - id: column_mov
        type: cl_hitpoly_column

      - id: column_atk
        type: cl_hitpoly_column

      - id: col_mov_z_hosei
        type: f4

      - id: col_atk_z_hosei
        type: f4

      - id: se_upper
        type: u1
        repeat: expr
        repeat-expr: 4

      - id: se_foot
        type: u1
        repeat: expr
        repeat-expr: 4

      - id: tgt_neck_angle
        type: vector4

      - id: look_tgt
        type: pointer('sub_character')

      - id: look_obj
        type: pointer('sub_character')

      - id: dist_to_jms
        type: f4

      - id: hp_recover
        type: f4

      - id: stand_time
        type: f4

      - id: move_time
        type: f4

      - id: muteki_time
        type: f4

      - id: relax_time
        type: f4

      - id: afraid_time
        type: f4

      - id: hp
        type: f4

      - id: hp_max
        type: f4

      - id: tired
        type: s4

      - id: tired_max
        type: s4

      - id: relax_flag
        type: u1

      - id: no_damage
        type: u1

      - id: dead
        type: u1

      - size: 1

      - id: damage_no
        type: u2

      - id: enemy_around
        type: u1

      - id: enemy_atk_area
        type: u1

      - id: look_jms
        type: u1

      - id: random_status
        type: u1

      - id: active_type
        type: u1

      - size: 1

  text_pos:
    seq:
      - id: block_index
        type: u4

      - id: texture_no
        type: u4

  sh_in_area:
    seq:
      - id: look_on
        type: b2

      - id: feel_on
        type: b2

      - id: light_on
        type: b4

  sh_in_area_tgt_info:
    seq:
      - id: adr
        type: sh_in_area_tgt_info_anon_4
        size: 4

      - id: distance
        type: f4

      - id: in_area
        type: sh_in_area

      - size: 3

  sh_in_area_tgt_info_anon_4:
    instances:
      scp:
        pos: 0
        type: pointer('sub_character')

    seq:
      - size: 4

  sh_battle_shot:
    seq:
      - id: test_a
        type: f4

      - id: test_b
        type: f4

      - id: test_c
        type: f4

  sh_battle_fight:
    seq:
      - id: test_a
        type: f4

      - id: test_b
        type: f4

      - id: test_c
        type: f4

  sh_attack_info:
    seq:
      - id: id
        type: u2

      - id: kind
        type: u2

      - id: ap
        type: f4

      - id: sp
        type: f4

      - id: min_range
        type: f4

      - id: max_range
        type: f4

      - id: hit_check
        type: sh_attack_info_anon_5
        size: 12

      - id: atk_start
        type: u1

      - id: atk_end
        type: u1

      - id: sd
        type: u1

      - id: eff
        type: u1

  sh_attack_info_anon_5:
    instances:
      fight:
        pos: 0
        type: sh_battle_fight

      shot:
        pos: 0
        type: sh_battle_shot

    seq:
      - size: 12

  sh_attack_queue_one:
    seq:
      - id: scp
        type: pointer('sub_character')

      - id: wep_no
        type: u1

      - size: 1

      - id: atk_no
        type: u2

  sh_attack_queue:
    seq:
      - id: rest
        type: s4

      - id: queue
        type: sh_attack_queue_one
        repeat: expr
        repeat-expr: 20

  cl_chara_list:
    seq:
      - id: col
        type: cl_hitpoly_column

      - id: wcol
        type: cl_hitpoly_column

      - id: sc
        type: pointer('sub_character')

      - size: 12

      - id: opos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: mvec
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: wallcv
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: mang
        type: f4

      - id: wflg
        type: s4

      - size: 8

      - id: ccvec
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: movflg
        type: s2

      - id: batflg
        type: s2

      - id: heightfunc
        type: pointer('data')

      - size: 8

  cl_select_map:
    seq:
      - id: base
        type: pointer('data')

      - id: sect
        type: u1

      - size: 3

  cl_hitpoly_plane:
    seq:
      - id: kind
        type: u1

      - id: shape
        type: u1

      - id: pad
        type: u2

      - id: weight
        type: u4

      - id: material
        type: u4

      - id: flg
        type: s4

      - id: p
        type: f4
        repeat: expr
        repeat-expr: 16

  cl_wallhitdat:
    seq:
      - id: kind
        type: s4

      - size: 12

      - id: cv
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: pl
        type: pointer('cl_hitpoly_plane')

      - size: 12

      - id: normal
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: nang
        type: f4

      - size: 12

  cl_battle_result:
    seq:
      - id: enable
        type: s4

      - id: id
        type: u4

      - id: atr
        type: s4

      - size: 4

      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: vec
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: kind
        type: u2

      - id: btlid
        type: u2

      - id: obj
        type: cl_battle_result_anon_6
        size: 4

      - size: 8

  cl_battle_result_anon_6:
    instances:
      en:
        pos: 0
        type: pointer('sub_character')

      pl:
        pos: 0
        type: pointer('cl_hitpoly_plane')

      cl:
        pos: 0
        type: pointer('cl_hitpoly_column')

    seq:
      - size: 4

  cl_cldheader:
    seq:
      - id: sx
        type: f4

      - id: sz
        type: f4

      - id: b0size
        type: s4

      - id: b1size
        type: s4

      - id: b2size
        type: s4

      - id: b3size
        type: s4

      - id: csize
        type: s4

      - id: disable
        type: s4

      - id: b0ofs
        type: s4
        repeat: expr
        repeat-expr: 16

      - id: b1ofs
        type: s4
        repeat: expr
        repeat-expr: 16

      - id: b2ofs
        type: s4
        repeat: expr
        repeat-expr: 16

      - id: b3ofs
        type: s4
        repeat: expr
        repeat-expr: 16

      - id: clofs
        type: s4
        repeat: expr
        repeat-expr: 16

      - id: fldofs
        type: u4

      - id: wldofs
        type: u4

      - id: cedofs
        type: u4

      - id: swdofs
        type: u4

      - id: cldofs
        type: u4

  cl_battle_que:
    seq:
      - id: kind
        type: u2

      - id: btlid
        type: u2

      - id: sc
        type: pointer('sub_character')

      - size: 8

      - id: svs
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: sve
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: evs
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: eve
        type: f4
        repeat: expr
        repeat-expr: 4

  cl_dynamicfloor_list:
    seq:
      - id: use
        type: s4

      - id: dw
        type: pointer('cl_hitpoly_plane')
        repeat: expr
        repeat-expr: 16

  cl_dynamicwall_list:
    seq:
      - id: use
        type: s4

      - id: dw
        type: pointer('cl_hitpoly_plane')
        repeat: expr
        repeat-expr: 32

  cl_hitresult:
    seq:
      - id: chk
        type: s4

      - size: 12

      - id: cp
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: cv
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: pd
        type: pointer('cl_hitpoly_head')

      - size: 12

  item:
    seq:
      - id: flag
        type: u4
        repeat: expr
        repeat-expr: 2

      - id: number
        type: u2
        repeat: expr
        repeat-expr: 11

      - id: light_switch
        type: u1

      - id: radio_switch
        type: u1

      - id: radio_volume
        type: u1

      - id: equip
        type: u1

      - size: 2

      - id: ampoule_efficacy
        type: f4

      - id: event_use
        type: u2
        repeat: expr
        repeat-expr: 3

      - id: short_pad
        type: u2

      - id: last_cursor
        type: u1

      - size: 3

  event_list:
    seq:
      - id: flag
        type: s4

      - id: cond
        type: s4

      - id: rslt0
        type: s4

      - id: rslt1
        type: s4

  game_flag:
    seq:
      - id: flag
        type: u4
        repeat: expr
        repeat-expr: 255

      - id: time_deai
        type: f4

      - id: enemy
        type: u4
        repeat: expr
        repeat-expr: 32

      - id: safe
        type: u1
        repeat: expr
        repeat-expr: 4

      - id: rotate
        type: s1
        repeat: expr
        repeat-expr: 4

      - id: guruguru
        type: s1
        repeat: expr
        repeat-expr: 4

      - id: cylinder
        type: s1
        repeat: expr
        repeat-expr: 4

      - id: clock
        type: u2

      - id: carbon
        type: u2

      - id: runaway
        type: s1
        repeat: expr
        repeat-expr: 4

      - id: hanging
        type: u2

      - id: pad
        type: s2

      - id: trunk
        type: s1
        repeat: expr
        repeat-expr: 4

  item_list:
    seq:
      - id: pos_x
        type: f4

      - id: pos_z
        type: f4

      - id: pos_y
        type: u2

      - id: rot_y
        type: u2

      - id: st
        type: u4

  event_door_sound:
    seq:
      - id: open
        type: s2

      - id: close
        type: s2

      - id: unlock
        type: s2

      - id: jam
        type: s2

      - id: lock
        type: s2

      - id: pad
        type: s2

  radio_data:
    seq:
      - id: se_call
        type: s4

      - id: event
        type: s4

      - size: 8

      - id: track
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: pan
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: volume
        type: f4

      - size: 12

      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

  model_list:
    seq:
      - id: kind
        type: s2

      - id: id
        type: s2

      - id: flag_off
        type: s2

      - id: flag_on
        type: s2

      - size: 8

      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rot
        type: f4
        repeat: expr
        repeat-expr: 4

  enemy_list:
    seq:
      - id: kind
        type: s2

      - id: id
        type: s2

      - id: pos_x
        type: s4

      - id: pos_z
        type: s4

      - id: pos_y
        type: s2

      - id: rot_y
        type: s2

      - id: status
        type: s2

      - id: condition
        type: u2

  gfw_func:
    seq:
      - id: spec_draw
        type: pointer('data')

      - id: pre_draw
        type: pointer('data')

      - id: post_draw
        type: pointer('data')

      - id: chara_draw_hook
        type: pointer('data')

  stage_data:
    seq:
      - id: ev_list
        type: pointer('event_list')

      - id: ev_pos
        type: pointer('data')

      - id: ev_prog
        type: pointer('data')

      - id: gi_list
        type: pointer('item_list')

      - id: mdl_list
        type: pointer('model_list')

      - id: en_list
        type: pointer('enemy_list')

      - id: stage_init
        type: pointer('data')

      - id: room_init
        type: pointer('data')

      - id: alltime_func
        type: pointer('data')

      - id: glb_crd
        type: s4

      - id: pc_model
        type: s4

      - id: stg_anim_info
        type: pointer('anime_info')

      - id: bgm_control
        type: pointer('data')

      - id: gfw_func
        type: pointer('gfw_func')

      - id: chara_data_clear
        type: pointer('data')

      - id: sound_call_after_load
        type: pointer('data')

      - id: reserve_11
        type: s4

  en_sound_queue:
    seq:
      - id: scp
        type: pointer('sub_character')

      - id: num
        type: s4

      - id: vol
        type: f4

      - id: time
        type: f4

  en_forbiddenarea:
    seq:
      - id: x0
        type: f4

      - id: z0
        type: f4

      - id: x1
        type: f4

      - id: z1
        type: f4

  en_local_work:
    seq:
      - id: data
        type: en_local_data
        repeat: expr
        repeat-expr: 32

      - id: communication
        type: en_communication
        repeat: expr
        repeat-expr: 8

      - id: forbidden_area
        type: en_forbiddenarea
        repeat: expr
        repeat-expr: 2

      - id: sound_queue
        type: en_sound_queue
        repeat: expr
        repeat-expr: 8

      - id: communication_num
        type: s4

      - id: forbidden_num
        type: s4

      - id: sound_queue_num
        type: s4

      - id: status
        type: u4

      - id: this
        type: pointer('en_local_data')

      - size: 12

      - id: hit_result
        type: cl_vhit_result

      - id: max3d_sounds
        type: s4

      - id: active_enemy
        type: s4

      - size: 8

  en_anime_data:
    seq:
      - id: anime
        type: u2

      - id: loop
        type: u1

      - size: 1

  sh_item_screen_object_setting_data:
    seq:
      - id: chara_id
        type: s4

      - id: scale
        type: f4

      - size: 8

      - id: rot
        type: vector4

  block:
    seq:
      - id: xz
        type: s2

      - id: block
        type: s2

  hh_class_wrapper_work:
    seq:
      - id: view_frustum_primitive_clip_matrix
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: view_frustum_bounding_box_clip_matrix
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: always_front_world_view_matrix
        type: f4
        repeat: expr
        repeat-expr: 16

  impact_queue_element_option:
    seq:
      - id: vector
        type: f4
        repeat: expr
        repeat-expr: 8

      - id: float_value
        type: f4
        repeat: expr
        repeat-expr: 2

      - id: int_value
        type: s4
        repeat: expr
        repeat-expr: 2

  impact_queue_element:
    seq:
      - id: class_descriptor
        type: u4

      - id: h_instance
        type: u4

      - id: p_result_handle_address
        type: pointer('data')

      - id: reserved
        type: u4

      - id: option
        type: impact_queue_element_option

  object_instance:
    seq:
      - id: element
        type: impact_queue_element

      - id: enable
        type: u4

      - id: h_instance
        type: u4

      - id: p_block
        type: pointer('data')

      - id: timer
        type: f4

      - id: p_prev
        type: pointer('object_instance')

      - id: p_next
        type: pointer('object_instance')

      - size: 8

  object_data_block_header:
    seq:
      - id: enable
        type: u4

      - id: p_next
        type: pointer('object_data_block_header')

      - size: 8

  object_data_pool_infomeation:
    seq:
      - id: block_size
        type: u4

      - id: block_index_max
        type: u4

      - id: p_block_table
        type: pointer('data')

      - id: p_free_block_list
        type: pointer('object_data_block_header')

  object_instance_table_infomeation:
    seq:
      - id: p_instance_table
        type: pointer('object_instance')

      - id: instance_max
        type: u4

      - id: h_instance_history
        type: u4

      - id: p_hierarchy_table
        type: pointer('data')

      - id: p_free_table
        type: pointer('object_instance')

      - size: 12

  object_class:
    seq:
      - id: p_prefix
        type: pointer('data')

      - id: p_main
        type: pointer('data')

      - id: p_suffix
        type: pointer('data')

      - id: disable
        type: u4

  impact_queue_object:
    seq:
      - id: en_queue
        type: u4

      - id: de_queue
        type: u4

      - id: length_current
        type: u4

      - id: length_max
        type: u4

      - id: p_element
        type: pointer('impact_queue_element')

      - size: 12

  object_class_association_infomeation:
    seq:
      - id: p_class_list
        type: pointer('object_class')

      - id: p_data_pool_info
        type: pointer('object_data_pool_infomeation')

      - id: p_class_priority_list
        type: pointer('data')

      - id: class_max
        type: u4

  object_group_infomeation:
    seq:
      - id: association_info
        type: object_class_association_infomeation

      - id: instance_table_info
        type: object_instance_table_infomeation

      - id: queue_info
        type: impact_queue_object

      - id: enable
        type: u4

      - id: step
        type: u4

      - size: 8

  sh_game_key_assign:
    seq:
      - id: type
        type: u2

      - id: dir_ax
        type: u1

      - id: dir_ay
        type: u1

      - id: dir_bx
        type: u1

      - id: dir_by
        type: u1

      - id: dir_cx
        type: u1

      - id: dir_cy
        type: u1

      - id: drink
        type: u2

      - id: radio
        type: u2

      - id: light
        type: u2

      - id: item
        type: u2

      - id: map
        type: u2

      - id: decide
        type: u2

      - id: cancel
        type: u2

      - id: skip
        type: u2

      - id: pause
        type: u2

      - id: action
        type: u2

      - id: dash
        type: u2

      - id: lslide
        type: u2

      - id: rslide
        type: u2

      - id: ready
        type: u2

      - id: view
        type: u2

  pad_key_config:
    seq:
      - id: enter
        type: s4

      - id: cancel
        type: s4

      - id: skip
        type: s4

      - id: front_move
        type: s4

      - id: back_move
        type: s4

      - id: right_turn
        type: s4

      - id: left_turn
        type: s4

      - id: right_move
        type: s4

      - id: left_move
        type: s4

      - id: action
        type: s4

      - id: attack
        type: s4

      - id: dash
        type: s4

      - id: light
        type: s4

      - id: item
        type: s4

      - id: search_view
        type: s4

      - id: ready
        type: s4

      - id: pause
        type: s4

      - id: map
        type: s4

      - id: padding
        type: s4
        repeat: expr
        repeat-expr: 6

  memory_pool_association_infomeation:
    seq:
      - id: existent
        type: u4

      - size: 12

      - id: data_pool_info
        type: object_data_pool_infomeation

      - id: link_list_max
        type: u4

      - id: p_link_list
        type: pointer('data')

      - size: 8

  filter_work:
    seq:
      - id: gs_filter_kind
        type: s4

      - id: flg
        type: s4

      - id: kind_history
        type: s4

      - id: mode
        type: s4

      - id: filter_data
        type: q_worddata
        repeat: expr
        repeat-expr: 8

      - id: copy_filter_color
        type: q_worddata
        size: 16

  filter_params:
    seq:
      - id: base_ix
        type: s2

      - id: base_iy
        type: s2

      - id: fo_timer
        type: s2

      - id: max_timer
        type: s2

      - id: target_sec
        type: s1

      - id: fio_ratio
        type: s1

      - id: blur_mode
        type: s1

      - id: blur_ratio
        type: s1

      - id: lesser_a
        type: s1

      - id: greater_a
        type: s1

      - id: sw_flg
        type: s1

      - id: dp_flg
        type: s1

      - id: soft_iter
        type: u1

      - id: soft_cit
        type: u1

      - id: soft_aref
        type: u1

      - id: soft_mode
        type: s1

      - id: soft_shift
        type: s1

      - id: trim_alpha
        type: s1

      - id: tex_trim_ex
        type: s2

      - id: tex_trim_ey
        type: s2

      - id: tex_trim_sx
        type: s2

      - id: tex_trim_sy
        type: s2

      - size: 2

      - id: dof_z_depth
        type: s4

      - id: key_alpha
        type: u1

      - id: testkind
        type: u1

      - id: s1_iter
        type: u1

      - id: s1_alpha
        type: u1

      - id: s1_shift
        type: s1

      - id: s1_base_ix
        type: s1

      - id: s2_iter
        type: u1

      - id: s2_alpha
        type: u1

      - id: s2_shift
        type: s1

      - id: s2_base_ix
        type: s1

      - size: 2

  fog_part_data:
    seq:
      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: mv
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: dd
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: degree
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: tdx
        type: f4

      - id: tdy
        type: f4

      - id: alp
        type: f4

      - id: dpos
        type: s4

      - id: alp_now
        type: f4

      - id: alp_add
        type: f4

      - id: bounce
        type: s4

      - id: erase
        type: s4

  fog_asm_data1:
    seq:
      - id: part_size
        type: f4

      - id: wall_range
        type: f4

      - id: rev_rate
        type: f4

      - id: part_m_rate
        type: f4

      - id: escape_range
        type: f4

      - id: r_escape_range
        type: f4

      - id: alpha_max
        type: f4

      - id: pad1
        type: f4

      - id: minus_alpha
        type: f4

      - id: rand_rate1
        type: f4

      - id: rand_rate2
        type: f4

      - id: rand_rate3
        type: f4

      - id: fadepos
        type: f4

      - id: r_fadepos
        type: f4

      - id: pad2
        type: f4

      - id: pad3
        type: f4

      - id: maxpos
        type: f4

      - id: maxpos_x2
        type: f4

      - id: screendiv
        type: f4

      - id: r_maxpos
        type: f4

      - id: gridrate
        type: f4

      - id: r_height
        type: f4

      - id: alpha
        type: f4

      - id: double_rate
        type: f4

      - id: higher_y
        type: f4

      - id: lower_y
        type: f4

      - id: y_max
        type: f4

      - id: higher_y2
        type: f4

  fog_asm_data2:
    seq:
      - id: center_x
        type: f4

      - id: center_y
        type: f4

      - id: part_size_proj
        type: f4

      - id: center_w
        type: f4

      - id: screen_width
        type: f4

      - id: screen_height
        type: f4

      - id: pad1
        type: f4

      - id: w_width
        type: f4

      - id: part_size
        type: f4

      - id: pixel_aspect
        type: f4

      - id: part_size_proj2
        type: f4

      - id: r_part_size
        type: f4

      - id: tex_sth
        type: f4

      - id: floor_y
        type: f4

      - id: tex_move_speed
        type: f4

      - id: n128
        type: f4

      - id: near_w
        type: f4

      - id: near_w2
        type: f4

      - id: r_near_w2
        type: f4

      - id: nr_128
        type: f4

      - id: light_max
        type: f4

      - id: light_rate
        type: f4

      - id: light_under
        type: f4

      - id: r_light_under
        type: f4

      - id: d_rate
        type: f4

      - id: d_under
        type: f4

      - id: d_rate2
        type: f4

      - id: proj
        type: f4

  fog_asm_data3:
    seq:
      - id: maxpos
        type: f4

      - id: r_screendiv
        type: f4

      - id: movespeed
        type: f4

      - id: r_double
        type: f4

  fog_asm_data_p:
    seq:
      - id: part
        type: pointer('fog_part_data')

      - id: packet
        type: pointer('data')

      - id: asm_data
        type: pointer('data')

      - id: world_screen
        type: pointer('data')

      - id: world_view
        type: pointer('data')

      - id: camera_pos
        type: pointer('data')

      - id: world_pos
        type: pointer('data')

      - id: light_pos
        type: pointer('data')

  fog_pack_work:
    seq:
      - id: packet
        type: u16
        repeat: expr
        repeat-expr: 6400

      - id: pk_env
        type: pointer('data')

      - id: pk_screen
        type: pointer('data')

      - id: pk_tex0
        type: pointer('data')

      - id: pk_vifmark
        type: pointer('data')

  fog_wall_data:
    seq:
      - id: normal
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: v0
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: min
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: max
        type: f4
        repeat: expr
        repeat-expr: 4

  fog_obj_data:
    seq:
      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: mv
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: type
        type: s4

      - id: rer
        type: f4

      - id: id
        type: u8

  fog_colis_head:
    seq:
      - id: wall1
        type: u2

      - id: wall2
        type: u2

      - id: obj1
        type: u2

      - id: obj2
        type: u2

      - id: area
        type: u2

      - id: env
        type: u2

  fog_env_data:
    seq:
      - id: part_num
        type: s2

      - id: max_pos
        type: s2

      - id: part_size
        type: s2

      - id: escape_range
        type: s2

      - id: floor_y
        type: s2

      - id: limit_y
        type: s2

      - id: limit_height
        type: s2

      - id: water_y
        type: s2

      - id: wind_def
        type: u1

      - id: flag
        type: u1

      - id: double
        type: u1

      - id: alpha
        type: u1

      - id: grid_rate
        type: f4

  fog_work:
    seq:
      - id: part
        type: fog_part_data
        repeat: expr
        repeat-expr: 700

      - id: grid_dense
        type: f4
        repeat: expr
        repeat-expr: 512

      - id: wall
        type: fog_wall_data
        repeat: expr
        repeat-expr: 188

      - id: obj
        type: fog_obj_data
        repeat: expr
        repeat-expr: 168

      - id: world_screen_m
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: world_view_m
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: camera_pos_v
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: old_camera_v
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: world_pos_v
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: local_pos_v
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: map_pos_v
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: light_pos_v
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: wind_v
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: fewdense
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: stay_point
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: limit_y
        type: f4

      - id: limit_y2
        type: f4

      - id: water_y
        type: f4

      - id: speed_level
        type: f4

      - id: sc_degree
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: sc_tdx
        type: f4

      - id: sc_tdy
        type: f4

      - id: max_pos
        type: f4

      - id: fade_pos
        type: f4

      - id: part_size
        type: f4

      - id: projection
        type: f4

      - id: escape_range
        type: f4

      - id: grid_rate
        type: f4

      - id: floor_y
        type: f4

      - id: part_num
        type: s2

      - id: wall_num
        type: s2

      - id: obj_max
        type: s2

      - id: obj_num
        type: s2

      - id: obj_num2
        type: s2

      - id: alpha
        type: s2

      - id: wind_def
        type: s2

      - id: double
        type: s1

      - id: load_step
        type: s1

      - id: global_
        type: s1

      - size: 1

      - id: area_max
        type: u2

      - id: flag
        type: u2

      - size: 2

      - id: color
        type: u4

      - id: sum_w
        type: s4

      - id: fid
        type: s4

      - id: wind_timer
        type: s4

      - id: colis_head
        type: pointer('fog_colis_head')

      - id: area_top
        type: pointer('fog_area_data')

      - id: env_top
        type: pointer('fog_env_data')

      - id: env_now
        type: pointer('fog_env_data')

      - size: 4

  fog_blow_point:
    seq:
      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: vec
        type: f4
        repeat: expr
        repeat-expr: 4

  fog_work2:
    seq:
      - id: part_num
        type: s2

      - id: blow_point_num
        type: s2

      - id: blow_point_id
        type: s4

      - id: blow_point
        type: pointer('fog_blow_point')

      - id: blow_timer
        type: s4
        repeat: expr
        repeat-expr: 16

      - id: blow_interval
        type: s4

      - id: gravity
        type: f4

      - id: expand
        type: f4

  scratchpad_fog:
    seq:
      - id: unk0
        type: u1
        repeat: expr
        repeat-expr: 16352

      - id: wind2
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: wind
        type: f4
        repeat: expr
        repeat-expr: 4

  change_list:
    seq:
      - id: sd_se
        type: s4

      - id: sd_3d
        type: s4

      - id: file
        type: s4

  se_track_buffer:
    seq:
      - id: status
        type: u1

      - id: fade_in_type
        type: u1

      - id: fade_out_type
        type: u1

      - id: pad
        type: u1

      - id: volume
        type: f4

  se_bgm_buffer:
    seq:
      - id: current
        type: s4

      - id: next
        type: s4

      - id: read
        type: s4

      - id: sdb_no
        type: s4

      - id: volume
        type: f4

      - id: track
        type: se_track_buffer
        repeat: expr
        repeat-expr: 7

  se2d_manage_data:
    seq:
      - id: sd
        type: s4

      - size: 12

      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: vol
        type: f4

      - id: room
        type: s2

      - id: pos_on
        type: u1

      - id: pre_dist
        type: u1

      - id: pre_pan
        type: s2

      - id: status
        type: s2

      - id: timer
        type: f4

      - id: base
        type: f4

      - size: 12

  se3d_channel_data:
    seq:
      - id: sd
        type: s4

      - id: room
        type: s4

      - id: status
        type: s4

      - size: 4

      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: vol
        type: f4

      - size: 12

  snd_road_area:
    seq:
      - id: x0
        type: f4

      - id: z0
        type: f4

      - id: x1
        type: f4

      - id: z1
        type: f4

      - id: x2
        type: f4

      - id: z2
        type: f4

      - id: min_hy
        type: f4

      - id: max_hy
        type: f4

  sound_data:
    seq:
      - id: lim_sw
        type: snd_road_area

      - id: flags
        type: s4

      - id: chanstat
        type: s4
        repeat: expr
        repeat-expr: 7

  near_sound_data:
    seq:
      - id: in_vol
        type: s1
        repeat: expr
        repeat-expr: 7

      - id: out_vol
        type: s1
        repeat: expr
        repeat-expr: 7

      - size: 2

      - id: err_code
        type: s4

      - id: abs_index
        type: s4

      - id: len
        type: f4

  sound_work:
    seq:
      - id: sound_ary
        type: pointer('sound_data')

      - size: 12

      - id: chara_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: half_w
        type: f4

      - id: page
        type: s4

      - id: near_sound_num
        type: s4

      - id: near_sound_ary
        type: near_sound_data
        repeat: expr
        repeat-expr: 8

      - id: on_num
        type: s4

      - id: on_chan
        type: s1
        repeat: expr
        repeat-expr: 7

      - size: 1

      - id: abs_num
        type: s4

      - id: nearindex
        type: s4

  playing_info:
    seq:
      - id: stage
        type: u1

      - id: enemy_off
        type: u1

      - id: voice_off
        type: u1

      - id: memo_select
        type: u1

      - id: clear_end_kind
        type: u1

      - id: clear_end_number
        type: u1

      - id: rank
        type: u1

      - id: game_stage
        type: u1

      - id: hidden_item_get
        type: u1

      - id: spray_pow
        type: s1

      - id: savecount
        type: u2

      - id: clearcount
        type: u2

      - id: item_get
        type: u2

      - id: kill_by_shot
        type: u2

      - id: kill_by_fight
        type: u2

      - id: time
        type: f4

      - id: walk_distance
        type: f4

      - id: run_distance
        type: f4

      - id: boat_clear_time
        type: f4

      - id: boat_max_speed
        type: f4

      - id: jms_damage_total
        type: f4

      - id: mar_damage_by_enemy
        type: f4

      - id: mar_damage_by_jms
        type: f4

      - id: stage_check_point
        type: f4
        repeat: expr
        repeat-expr: 7

      - id: stage_score
        type: u4
        repeat: expr
        repeat-expr: 7

      - id: total_score
        type: u4

      - id: total_time
        type: f4

      - id: battle_level
        type: u1

      - id: riddle_level
        type: u1

      - id: brightness_level
        type: u1

      - id: screen_position_x
        type: s1

      - id: screen_position_y
        type: s1

      - id: vibration
        type: u1

      - id: auto_load
        type: u1

      - id: sound
        type: u1

      - id: bgm_volume
        type: u1

      - id: se_volume
        type: u1

      - id: weapon_control
        type: u1

      - id: blood_color
        type: u1

      - id: view_control
        type: u1

      - id: retreat_turn
        type: u1

      - id: walk_run_control
        type: u1

      - id: auto_aiming
        type: u1

      - id: view_mode
        type: u1

      - id: bullet_adjust
        type: u1

      - id: language
        type: u1

      - id: subtitles
        type: u1

      - id: control_type
        type: u1

      - id: radar
        type: u1

      - size: 2

  camera_dat:
    seq:
      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: zdir
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: ydir
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rot
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: clip_volume
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: world_view
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: view_screen
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: view_clip
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: world_screen
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: world_clip
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: clip_screen
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: camera_pam
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: screen_pam1
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: screen_pam2
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rot_zdir
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rot_ydir
        type: f4
        repeat: expr
        repeat-expr: 4

  vb_coordinate:
    seq:
      - id: flg
        type: u4

      - size: 12

      - id: coord
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: work
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: param
        type: pointer('data')

      - id: super
        type: pointer('vb_coordinate')

      - id: sub
        type: pointer('vb_coordinate')

      - id: r
        type: vb_coordinate_anon_7

      - size: 12

      - id: lw
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: ls
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: rot
        type: f4
        repeat: expr
        repeat-expr: 4

  vb_coordinate_anon_7:
    seq:
      - id: vx
        type: s2

      - id: vy
        type: s2

      - id: vz
        type: s2

      - id: pad
        type: s2

  vb_rview:
    seq:
      - id: vp
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: vr
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rz
        type: f4

      - id: super
        type: pointer('vb_coordinate')

      - size: 8

  vb_wvsmatrix:
    seq:
      - id: wvm
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: vsm
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: wsm
        type: f4
        repeat: expr
        repeat-expr: 16

  vb_screeninfo:
    seq:
      - id: scr_z
        type: f4

      - id: sx
        type: f4

      - id: sy
        type: f4

      - id: cx
        type: f4

      - id: cy
        type: f4

      - id: zmin
        type: f4

      - id: zmax
        type: f4

      - id: nearz
        type: f4

      - id: farz
        type: f4

  sema_param:
    seq:
      - id: current_count
        type: s4

      - id: max_count
        type: s4

      - id: init_count
        type: s4

      - id: num_wait_threads
        type: s4

      - id: attr
        type: u4

      - id: option
        type: u4

  thread_param:
    seq:
      - id: status
        type: s4

      - id: entry
        type: pointer('data')

      - id: stack
        type: pointer('data')

      - id: stack_size
        type: s4

      - id: gp_reg
        type: pointer('data')

      - id: init_priority
        type: s4

      - id: current_priority
        type: s4

      - id: attr
        type: u4

      - id: option
        type: u4

      - id: wait_type
        type: s4

      - id: wait_id
        type: s4

      - id: wakeup_count
        type: s4

  t_tcount:
    seq:
      - id: count
        type: u16

      - id: p0
        type: u16

  t_tmode:
    seq:
      - id: clks
        type: b2

      - id: gate
        type: b1

      - id: gats
        type: b1

      - id: gatm
        type: b2

      - id: zret
        type: b1

      - id: cue
        type: b1

      - id: cmpe
        type: b1

      - id: ovfe
        type: b1

      - id: equf
        type: b1

      - id: ovff
        type: b1

      - id: p0
        type: b20

  t_tcomp:
    seq:
      - id: comp
        type: u16

      - id: p0
        type: u16

  t_thold:
    seq:
      - id: hold
        type: u16

      - id: p0
        type: u16

  t_ipu_cmd_write:
    seq:
      - id: option
        type: b28

      - id: code
        type: b4

  t_ipu_cmd_read:
    seq:
      - id: data
        type: b32

      - id: p0
        type: b31

      - id: busy
        type: b1

  t_ipu_top:
    seq:
      - id: bstop
        type: b32

      - id: p0
        type: b31

      - id: busy
        type: b1

  t_ipu_ctrl:
    seq:
      - id: ifc
        type: b4

      - id: ofc
        type: b4

      - id: cbp
        type: b6

      - id: ecd
        type: b1

      - id: scd
        type: b1

      - id: idp
        type: b2

      - id: p0
        type: b2

      - id: as_
        type: b1

      - id: ivf
        type: b1

      - id: qst
        type: b1

      - id: mp1
        type: b1

      - id: pct
        type: b3

      - id: p1
        type: b3

      - id: rst
        type: b1

      - id: busy
        type: b1

  t_ipu_bp:
    seq:
      - id: bp
        type: b7

      - id: p0
        type: b1

      - id: ifc
        type: b4

      - id: p1
        type: b4

      - id: fp
        type: b2

      - id: p2
        type: b14

  t_gif_ctrl:
    seq:
      - id: rst
        type: b1

      - id: p0
        type: b2

      - id: pse
        type: b1

      - id: p1
        type: b28

  t_gif_mode:
    seq:
      - id: m3r
        type: b1

      - id: p0
        type: b1

      - id: imt
        type: b1

      - id: p1
        type: b29

  t_gif_stat:
    seq:
      - id: m3r
        type: b1

      - id: m3p
        type: b1

      - id: imt
        type: b1

      - id: pse
        type: b1

      - id: p0
        type: b1

      - id: ip3
        type: b1

      - id: p3q
        type: b1

      - id: p2q
        type: b1

      - id: p1q
        type: b1

      - id: oph
        type: b1

      - id: apath
        type: b2

      - id: dir
        type: b1

      - id: p1
        type: b11

      - id: fqc
        type: b5

      - id: p2
        type: b3

  t_gif_tag0:
    seq:
      - id: nloop
        type: b15

      - id: eop
        type: b1

      - id: tag
        type: u16

  t_gif_tag1:
    seq:
      - id: tag
        type: b14

      - id: pre
        type: b1

      - id: prim
        type: b11

      - id: flg
        type: b2

      - id: nreg
        type: b4

  t_gif_tag2:
    seq:
      - id: tag
        type: b32

  t_gif_tag3:
    seq:
      - id: tag
        type: b32

  t_gif_cnt:
    seq:
      - id: loopcnt
        type: b15

      - id: p0
        type: b1

      - id: regcnt
        type: b4

      - id: vuaddr
        type: b10

      - id: p1
        type: b2

  t_gif_p3cnt:
    seq:
      - id: p3cnt
        type: b15

      - id: p0
        type: b17

  t_gif_p3tag:
    seq:
      - id: loopcnt
        type: b15

      - id: eop
        type: b1

      - id: p0
        type: u16

  t_vif0_stat:
    seq:
      - id: vps
        type: b2

      - id: vew
        type: b1

      - id: p0
        type: b3

      - id: mrk
        type: b1

      - id: p1
        type: b1

      - id: vss
        type: b1

      - id: vfs
        type: b1

      - id: vis
        type: b1

      - id: int
        type: b1

      - id: ero
        type: b1

      - id: er1
        type: b1

      - id: p2
        type: b10

      - id: fqc
        type: b4

      - id: p3
        type: b4

  t_vif0_fbrst:
    seq:
      - id: rst
        type: b1

      - id: fbk
        type: b1

      - id: stp
        type: b1

      - id: stc
        type: b1

      - id: p0
        type: b28

  t_vif0_err:
    seq:
      - id: mii
        type: b1

      - id: me0
        type: b1

      - id: me1
        type: b1

      - id: p0
        type: b29

  t_vif_mark:
    seq:
      - id: mark
        type: u16

      - id: p0
        type: u16

  t_vif_cycle:
    seq:
      - id: cl
        type: b8

      - id: wl
        type: b8

      - id: p0
        type: u16

  t_vif_mode:
    seq:
      - id: mod
        type: b2

      - id: p0
        type: b30

  t_vif0_num:
    seq:
      - id: num
        type: b8

      - id: p0
        type: b24

  t_vif_mask:
    seq:
      - id: m0
        type: b2

      - id: m1
        type: b2

      - id: m2
        type: b2

      - id: m3
        type: b2

      - id: m4
        type: b2

      - id: m5
        type: b2

      - id: m6
        type: b2

      - id: m7
        type: b2

      - id: m8
        type: b2

      - id: m9
        type: b2

      - id: m10
        type: b2

      - id: m11
        type: b2

      - id: m12
        type: b2

      - id: m13
        type: b2

      - id: m14
        type: b2

      - id: m15
        type: b2

  t_vif_code:
    seq:
      - id: immediate
        type: u16

      - id: num
        type: b8

      - id: cmd
        type: b8

  t_vif_itops:
    seq:
      - id: itops
        type: b10

      - id: p0
        type: b22

  t_vif_itop:
    seq:
      - id: itop
        type: b10

      - id: p0
        type: b22

  t_vif_r0:
    seq:
      - id: r0
        type: b32

  t_vif_r1:
    seq:
      - id: r1
        type: b32

  t_vif_r2:
    seq:
      - id: r2
        type: b32

  t_vif_r3:
    seq:
      - id: r3
        type: b32

  t_vif_c0:
    seq:
      - id: c0
        type: b32

  t_vif_c1:
    seq:
      - id: c1
        type: b32

  t_vif_c2:
    seq:
      - id: c2
        type: b32

  t_vif_c3:
    seq:
      - id: c3
        type: b32

  t_vif1_stat:
    seq:
      - id: vps
        type: b2

      - id: vew
        type: b1

      - id: vgw
        type: b1

      - id: p0
        type: b2

      - id: mrk
        type: b1

      - id: dbf
        type: b1

      - id: vss
        type: b1

      - id: vfs
        type: b1

      - id: vis
        type: b1

      - id: int
        type: b1

      - id: ero
        type: b1

      - id: er1
        type: b1

      - id: p1
        type: b9

      - id: fdr
        type: b1

      - id: fqc
        type: b5

      - id: p2
        type: b3

  t_vif1_fbrst:
    seq:
      - id: rst
        type: b1

      - id: fbk
        type: b1

      - id: stp
        type: b1

      - id: stc
        type: b1

      - id: p0
        type: b28

  t_vif1_err:
    seq:
      - id: mii
        type: b1

      - id: me0
        type: b1

      - id: me1
        type: b1

      - id: p0
        type: b29

  t_vif1_num:
    seq:
      - id: num
        type: b8

      - id: p0
        type: b24

  t_vif1_base:
    seq:
      - id: base
        type: b10

      - id: p0
        type: b22

  t_vif1_ofst:
    seq:
      - id: offset
        type: b10

      - id: p0
        type: b22

  t_vif1_tops:
    seq:
      - id: tops
        type: b10

      - id: p0
        type: b22

  t_vif1_top:
    seq:
      - id: top
        type: b10

      - id: p0
        type: b22

  t_dchcr:
    seq:
      - id: dir
        type: b1

      - id: p0
        type: b1

      - id: mod
        type: b2

      - id: asp
        type: b2

      - id: tte
        type: b1

      - id: tie
        type: b1

      - id: str
        type: b1

      - id: p1
        type: b7

      - id: tag
        type: u16

  t_dmadr:
    seq:
      - id: addr
        type: b31

      - id: spr
        type: b1

  t_dqwc:
    seq:
      - id: qwc
        type: u16

      - id: p0
        type: u16

  t_dtadr:
    seq:
      - id: addr
        type: b31

      - id: spr
        type: b1

  t_dasr0:
    seq:
      - id: addr
        type: b31

      - id: spr
        type: b1

  t_dasr1:
    seq:
      - id: addr
        type: b31

      - id: spr
        type: b1

  t_dsadr:
    seq:
      - id: addr
        type: b14

      - id: p0
        type: b18

  t_dctrl:
    seq:
      - id: dmae
        type: b1

      - id: rele
        type: b1

      - id: mfd
        type: b2

      - id: sts
        type: b2

      - id: std
        type: b2

      - id: rcyc
        type: b3

      - id: p0
        type: b21

  t_dstat:
    seq:
      - id: cis0
        type: b1

      - id: cis1
        type: b1

      - id: cis2
        type: b1

      - id: cis3
        type: b1

      - id: cis4
        type: b1

      - id: cis5
        type: b1

      - id: cis6
        type: b1

      - id: cis7
        type: b1

      - id: cis8
        type: b1

      - id: cis9
        type: b1

      - id: p0
        type: b3

      - id: sis
        type: b1

      - id: meis
        type: b1

      - id: beis
        type: b1

      - id: cim0
        type: b1

      - id: cim1
        type: b1

      - id: cim2
        type: b1

      - id: cim3
        type: b1

      - id: cim4
        type: b1

      - id: cim5
        type: b1

      - id: cim6
        type: b1

      - id: cim7
        type: b1

      - id: cim8
        type: b1

      - id: cim9
        type: b1

      - id: p1
        type: b3

      - id: sim
        type: b1

      - id: meim
        type: b1

      - id: p2
        type: b1

  t_dpcr:
    seq:
      - id: cpc0
        type: b1

      - id: cpc1
        type: b1

      - id: cpc2
        type: b1

      - id: cpc3
        type: b1

      - id: cpc4
        type: b1

      - id: cpc5
        type: b1

      - id: cpc6
        type: b1

      - id: cpc7
        type: b1

      - id: cpc8
        type: b1

      - id: cpc9
        type: b1

      - id: p0
        type: b6

      - id: cde0
        type: b1

      - id: cde1
        type: b1

      - id: cde2
        type: b1

      - id: cde3
        type: b1

      - id: cde4
        type: b1

      - id: cde5
        type: b1

      - id: cde6
        type: b1

      - id: cde7
        type: b1

      - id: cde8
        type: b1

      - id: cde9
        type: b1

      - id: p1
        type: b5

      - id: pce
        type: b1

  t_dsqwc:
    seq:
      - id: sqwc
        type: b8

      - id: p0
        type: b8

      - id: tqwc
        type: b8

      - id: p1
        type: b8

  t_drbsr:
    seq:
      - id: rmsk
        type: b31

      - id: p0
        type: b1

  t_drbor:
    seq:
      - id: addr
        type: b31

      - id: p0
        type: b1

  t_dstadr:
    seq:
      - id: addr
        type: b31

      - id: p0
        type: b1

  t_denabler:
    seq:
      - id: p0
        type: u16

      - id: cpnd
        type: b1

      - id: p1
        type: b15

  t_denablew:
    seq:
      - id: p0
        type: u16

      - id: cpnd
        type: b1

      - id: p1
        type: b15

  t_gs_pmode:
    seq:
      - id: en1
        type: b1

      - id: en2
        type: b1

      - id: crtmd
        type: b3

      - id: mmod
        type: b1

      - id: amod
        type: b1

      - id: slbg
        type: b1

      - id: alp
        type: b8

      - id: p0
        type: u16

      - id: p1
        type: u4

  t_gs_smode2:
    seq:
      - id: int
        type: b1

      - id: ffmd
        type: b1

      - id: dpms
        type: b2

      - id: p0
        type: b28

      - id: p1
        type: u4

  t_gs_dispfb1:
    seq:
      - id: fbp
        type: b9

      - id: fbw
        type: b6

      - id: psm
        type: b5

      - id: p0
        type: b12

      - id: dbx
        type: b11

      - id: dby
        type: b11

      - id: p1
        type: b10

  t_gs_display1:
    seq:
      - id: dx
        type: b12

      - id: dy
        type: b11

      - id: magh
        type: b4

      - id: magv
        type: b2

      - id: p0
        type: b3

      - id: dw
        type: b12

      - id: dh
        type: b11

      - id: p1
        type: b9

  t_gs_dispfb2:
    seq:
      - id: fbp
        type: b9

      - id: fbw
        type: b6

      - id: psm
        type: b5

      - id: p0
        type: b12

      - id: dbx
        type: b11

      - id: dby
        type: b11

      - id: p1
        type: b10

  t_gs_display2:
    seq:
      - id: dx
        type: b12

      - id: dy
        type: b11

      - id: magh
        type: b4

      - id: magv
        type: b2

      - id: p0
        type: b3

      - id: dw
        type: b12

      - id: dh
        type: b11

      - id: p1
        type: b9

  t_gs_extbuf:
    seq:
      - id: exbp
        type: b14

      - id: exbw
        type: b6

      - id: fbin
        type: b2

      - id: wffmd
        type: b1

      - id: emoda
        type: b2

      - id: emodc
        type: b2

      - id: p0
        type: b5

      - id: wdx
        type: b11

      - id: wdy
        type: b11

      - id: p1
        type: b10

  t_gs_extdata:
    seq:
      - id: sx
        type: b12

      - id: sy
        type: b11

      - id: smph
        type: b4

      - id: smpv
        type: b2

      - id: p0
        type: b3

      - id: ww
        type: b12

      - id: wh
        type: b11

      - id: p1
        type: b9

  t_gs_extwrite:
    seq:
      - id: write
        type: b1

      - id: p0
        type: b31

      - id: p1
        type: u4

  t_gs_bgcolor:
    seq:
      - id: r
        type: b8

      - id: g
        type: b8

      - id: b
        type: b8

      - id: p0
        type: b8

      - id: p1
        type: u4

  t_gs_csr:
    seq:
      - id: signal
        type: b1

      - id: finish
        type: b1

      - id: hsint
        type: b1

      - id: vsint
        type: b1

      - id: edwint
        type: b1

      - id: p0
        type: b3

      - id: flush
        type: b1

      - id: reset
        type: b1

      - id: p1
        type: b2

      - id: nfield
        type: b1

      - id: field
        type: b1

      - id: fifo
        type: b2

      - id: rev
        type: b8

      - id: id
        type: b8

      - id: p2
        type: u4

  t_gs_imr:
    seq:
      - id: p0
        type: b8

      - id: sigmsk
        type: b1

      - id: finishmsk
        type: b1

      - id: hsmsk
        type: b1

      - id: vsmsk
        type: b1

      - id: edwmsk
        type: b1

      - id: p1
        type: b19

      - id: p2
        type: u4

  t_gs_busdir:
    seq:
      - id: dir
        type: b1

      - id: p0
        type: b31

      - id: p1
        type: u4

  t_gs_siglblid:
    seq:
      - id: sigid
        type: b32

      - id: lblid
        type: b32

  sce_dma_tag:
    seq:
      - id: qwc
        type: u2

      - id: mark
        type: u1

      - id: id
        type: u1

      - id: next
        type: pointer('sce_dma_tag')

      - id: p
        type: u4
        repeat: expr
        repeat-expr: 2

  sce_dma_env:
    seq:
      - id: sts
        type: u1

      - id: std
        type: u1

      - id: mfd
        type: u1

      - id: rcycle
        type: u1

      - id: express
        type: u2

      - id: notify
        type: u2

      - id: sqwc
        type: u2

      - id: tqwc
        type: u2

      - id: rbadr
        type: pointer('data')

      - id: rbmsk
        type: u4

  sce_dma_chan:
    seq:
      - id: chcr
        type: t_dchcr

      - id: p0
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: madr
        type: pointer('data')

      - id: p1
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: qwc
        type: u4

      - id: p2
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: tadr
        type: pointer('sce_dma_tag')

      - id: p3
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: as0
        type: pointer('data')

      - id: p4
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: as1
        type: pointer('data')

      - id: p5
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: p6
        type: u4
        repeat: expr
        repeat-expr: 4

      - id: p7
        type: u4
        repeat: expr
        repeat-expr: 4

      - id: sadr
        type: pointer('data')

      - id: p8
        type: u4
        repeat: expr
        repeat-expr: 3

  sce_cd_clock:
    seq:
      - id: stat
        type: u1

      - id: second
        type: u1

      - id: minute
        type: u1

      - id: hour
        type: u1

      - id: pad
        type: u1

      - id: day
        type: u1

      - id: month
        type: u1

      - id: year
        type: u1

  sce_cd_rmode:
    seq:
      - id: trycount
        type: u1

      - id: spindlctrl
        type: u1

      - id: datapattern
        type: u1

      - id: pad
        type: u1

  sce_cdl_file:
    seq:
      - id: lsn
        type: u4

      - id: size
        type: u4

      - id: name
        type: s1
        repeat: expr
        repeat-expr: 16

      - id: date
        type: u1
        repeat: expr
        repeat-expr: 8

      - id: flag
        type: u4

  sce_scf_t10k_config:
    seq:
      - id: time_zone
        type: s2

      - id: aspect
        type: u1

      - id: date_notation
        type: u1

      - id: language
        type: u1

      - id: spdif
        type: u1

      - id: summer_time
        type: u1

      - id: time_notation
        type: u1

  sce_gif_tag:
    seq:
      - id: nloop
        type: b15

      - id: eop
        type: b1

      - id: pad16
        type: u16

      - id: id
        type: b14

      - id: pre
        type: b1

      - id: prim
        type: b11

      - id: flg
        type: b2

      - id: nreg
        type: b4

      - id: regs0
        type: b4

      - id: regs1
        type: b4

      - id: regs2
        type: b4

      - id: regs3
        type: b4

      - id: regs4
        type: b4

      - id: regs5
        type: b4

      - id: regs6
        type: b4

      - id: regs7
        type: b4

      - id: regs8
        type: b4

      - id: regs9
        type: b4

      - id: regs10
        type: b4

      - id: regs11
        type: b4

      - id: regs12
        type: b4

      - id: regs13
        type: b4

      - id: regs14
        type: b4

      - id: regs15
        type: b4

  sce_gif_pack_rgbaq:
    seq:
      - id: r
        type: u4

      - id: g
        type: u4

      - id: b
        type: u4

      - id: a
        type: u4

  sce_gif_pack_ad:
    seq:
      - id: data
        type: u8

      - id: addr
        type: u8

  sce_gif_pack_st:
    seq:
      - id: s
        type: f4

      - id: t
        type: f4

      - id: q
        type: f4

      - id: pad96
        type: u4

  sce_gif_pack_uv:
    seq:
      - id: u
        type: s4

      - id: v
        type: s4

      - id: pad64
        type: s8

  sce_gif_pack_xyzf:
    seq:
      - id: x
        type: s4

      - id: y
        type: s4

      - id: z
        type: u4

      - id: f
        type: b12

      - id: pad108
        type: b3

      - id: adc
        type: b1

      - id: pad112
        type: u16

  sce_gif_pack_xyz:
    seq:
      - id: x
        type: s4

      - id: y
        type: s4

      - id: z
        type: u4

      - id: pad96
        type: b15

      - id: adc
        type: b1

      - id: pad112
        type: u16

  sce_gif_pack_fog:
    seq:
      - id: pad
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: f
        type: u4

  sce_gif_pack_nop:
    seq:
      - id: pad
        type: u8
        repeat: expr
        repeat-expr: 2

  sce_gs_alpha:
    seq:
      - id: a
        type: b2

      - id: b
        type: b2

      - id: c
        type: b2

      - id: d
        type: b2

      - id: pad8
        type: b24

      - id: fix
        type: b8

      - id: pad40
        type: b24

  sce_gs_bitbltbuf:
    seq:
      - id: sbp
        type: b14

      - id: pad14
        type: b2

      - id: sbw
        type: b6

      - id: pad22
        type: b2

      - id: spsm
        type: b6

      - id: pad30
        type: b2

      - id: dbp
        type: b14

      - id: pad46
        type: b2

      - id: dbw
        type: b6

      - id: pad54
        type: b2

      - id: dpsm
        type: b6

      - id: pad62
        type: b2

  sce_gs_clamp:
    seq:
      - id: wms
        type: b2

      - id: wmt
        type: b2

      - id: minu
        type: b10

      - id: maxu
        type: b10

      - id: minv
        type: b10

      - id: maxv
        type: b10

      - id: pad44
        type: b20

  sce_gs_colclamp:
    seq:
      - id: clamp
        type: b1

      - id: pad01
        type: b63

  sce_gs_dimx:
    seq:
      - id: dimx00
        type: b3

      - id: pad00
        type: b1

      - id: dimx01
        type: b3

      - id: pad01
        type: b1

      - id: dimx02
        type: b3

      - id: pad02
        type: b1

      - id: dimx03
        type: b3

      - id: pad03
        type: b1

      - id: dimx10
        type: b3

      - id: pad10
        type: b1

      - id: dimx11
        type: b3

      - id: pad11
        type: b1

      - id: dimx12
        type: b3

      - id: pad12
        type: b1

      - id: dimx13
        type: b3

      - id: pad13
        type: b1

      - id: dimx20
        type: b3

      - id: pad20
        type: b1

      - id: dimx21
        type: b3

      - id: pad21
        type: b1

      - id: dimx22
        type: b3

      - id: pad22
        type: b1

      - id: dimx23
        type: b3

      - id: pad23
        type: b1

      - id: dimx30
        type: b3

      - id: pad30
        type: b1

      - id: dimx31
        type: b3

      - id: pad31
        type: b1

      - id: dimx32
        type: b3

      - id: pad32
        type: b1

      - id: dimx33
        type: b3

      - id: pad33
        type: b1

  sce_gs_dthe:
    seq:
      - id: dthe
        type: b1

      - id: pad01
        type: b63

  sce_gs_fba:
    seq:
      - id: fba
        type: b1

      - id: pad01
        type: b63

  sce_gs_finish:
    seq:
      - id: pad00
        type: u8

  sce_gs_fog:
    seq:
      - id: pad00
        type: b56

      - id: f
        type: b8

  sce_gs_fogcol:
    seq:
      - id: fcr
        type: b8

      - id: fcg
        type: b8

      - id: fcb
        type: b8

      - id: pad24
        type: b40

  sce_gs_frame:
    seq:
      - id: fbp
        type: b9

      - id: pad09
        type: b7

      - id: fbw
        type: b6

      - id: pad22
        type: b2

      - id: psm
        type: b6

      - id: pad30
        type: b2

      - id: fbmsk
        type: b32

  sce_gs_hwreg:
    seq:
      - id: wdata
        type: u8

  sce_gs_label:
    seq:
      - id: id
        type: u4

      - id: idmsk
        type: u4

  sce_gs_miptbp1:
    seq:
      - id: tbp1
        type: b14

      - id: tbw1
        type: b6

      - id: tbp2
        type: b14

      - id: tbw2
        type: b6

      - id: tbp3
        type: b14

      - id: tbw3
        type: b6

      - id: pad60
        type: b4

  sce_gs_miptbp2:
    seq:
      - id: tbp4
        type: b14

      - id: tbw4
        type: b6

      - id: tbp5
        type: b14

      - id: tbw5
        type: b6

      - id: tbp6
        type: b14

      - id: tbw6
        type: b6

      - id: pad60
        type: b4

  sce_gs_pabe:
    seq:
      - id: pabe
        type: b1

      - id: pad01
        type: b63

  sce_gs_prim:
    seq:
      - id: prim
        type: b3

      - id: iip
        type: b1

      - id: tme
        type: b1

      - id: fge
        type: b1

      - id: abe
        type: b1

      - id: aa1
        type: b1

      - id: fst
        type: b1

      - id: ctxt
        type: b1

      - id: fix
        type: b1

      - id: pad11
        type: b53

  sce_gs_prmode:
    seq:
      - id: pad00
        type: b3

      - id: iip
        type: b1

      - id: tme
        type: b1

      - id: fge
        type: b1

      - id: abe
        type: b1

      - id: aa1
        type: b1

      - id: fst
        type: b1

      - id: ctxt
        type: b1

      - id: fix
        type: b1

      - id: pad11
        type: b53

  sce_gs_prmodecont:
    seq:
      - id: ac
        type: b1

      - id: pad01
        type: b63

  sce_gs_rgbaq:
    seq:
      - id: r
        type: b8

      - id: g
        type: b8

      - id: b
        type: b8

      - id: a
        type: b8

      - id: q
        type: f4

  sce_gs_scanmsk:
    seq:
      - id: msk
        type: b2

      - id: pad02
        type: b62

  sce_gs_scissor:
    seq:
      - id: scax0
        type: b11

      - id: pad11
        type: b5

      - id: scax1
        type: b11

      - id: pad27
        type: b5

      - id: scay0
        type: b11

      - id: pad43
        type: b5

      - id: scay1
        type: b11

      - id: pad59
        type: b5

  sce_gs_signal:
    seq:
      - id: id
        type: u4

      - id: idmsk
        type: u4

  sce_gs_st:
    seq:
      - id: s
        type: f4

      - id: t
        type: f4

  sce_gs_test:
    seq:
      - id: ate
        type: b1

      - id: atst
        type: b3

      - id: aref
        type: b8

      - id: afail
        type: b2

      - id: date
        type: b1

      - id: datm
        type: b1

      - id: zte
        type: b1

      - id: ztst
        type: b2

      - id: pad19
        type: b45

  sce_gs_tex0:
    seq:
      - id: tbp0
        type: b14

      - id: tbw
        type: b6

      - id: psm
        type: b6

      - id: tw
        type: b4

      - id: th
        type: b4

      - id: tcc
        type: b1

      - id: tfx
        type: b2

      - id: cbp
        type: b14

      - id: cpsm
        type: b4

      - id: csm
        type: b1

      - id: csa
        type: b5

      - id: cld
        type: b3

  sce_gs_tex1:
    seq:
      - id: lcm
        type: b1

      - id: pad01
        type: b1

      - id: mxl
        type: b3

      - id: mmag
        type: b1

      - id: mmin
        type: b3

      - id: mtba
        type: b1

      - id: pad10
        type: b9

      - id: l
        type: b2

      - id: pad21
        type: b11

      - id: k
        type: b12

      - id: pad44
        type: b20

  sce_gs_tex2:
    seq:
      - id: pad00
        type: b20

      - id: psm
        type: b6

      - id: pad26
        type: b11

      - id: cbp
        type: b14

      - id: cpsm
        type: b4

      - id: csm
        type: b1

      - id: csa
        type: b5

      - id: cld
        type: b3

  sce_gs_texa:
    seq:
      - id: ta0
        type: b8

      - id: pad08
        type: b7

      - id: aem
        type: b1

      - id: pad16
        type: u16

      - id: ta1
        type: b8

      - id: pad40
        type: b24

  sce_gs_texclut:
    seq:
      - id: cbw
        type: b6

      - id: cou
        type: b6

      - id: cov
        type: b10

      - id: pad22
        type: b42

  sce_gs_texflush:
    seq:
      - id: pad00
        type: u8

  sce_gs_trxdir:
    seq:
      - id: xdr
        type: b2

      - id: pad02
        type: b62

  sce_gs_trxpos:
    seq:
      - id: ssax
        type: b11

      - id: pad11
        type: b5

      - id: ssay
        type: b11

      - id: pad27
        type: b5

      - id: dsax
        type: b11

      - id: pad43
        type: b5

      - id: dsay
        type: b11

      - id: dir
        type: b2

      - id: pad61
        type: b3

  sce_gs_trxreg:
    seq:
      - id: rrw
        type: b12

      - id: pad12
        type: b20

      - id: rrh
        type: b12

      - id: pad44
        type: b20

  sce_gs_uv:
    seq:
      - id: u
        type: b14

      - id: pad14
        type: b2

      - id: v
        type: b14

      - id: pad30
        type: b34

  sce_gs_xyoffset:
    seq:
      - id: ofx
        type: u16

      - id: pad16
        type: u16

      - id: ofy
        type: u16

      - id: pad48
        type: u16

  sce_gs_xyz:
    seq:
      - id: x
        type: u16

      - id: y
        type: u16

      - id: z
        type: b32

  sce_gs_xyzf:
    seq:
      - id: x
        type: u16

      - id: y
        type: u16

      - id: z
        type: b24

      - id: f
        type: b8

  sce_gs_zbuf:
    seq:
      - id: zbp
        type: b9

      - id: pad09
        type: b15

      - id: psm
        type: b4

      - id: pad28
        type: b4

      - id: zmsk
        type: b1

      - id: pad33
        type: b31

  sce_vif0_packet:
    seq:
      - id: p_current
        type: pointer('data')

      - id: p_base
        type: pointer('data')

      - id: p_dma_tag
        type: pointer('data')

      - id: p_vif_code
        type: pointer('data')

      - id: numlen
        type: u4

      - id: pad11
        type: u4

      - id: pad12
        type: u4

      - id: pad13
        type: u4

  sce_vif1_packet:
    seq:
      - id: p_current
        type: pointer('data')

      - id: p_base
        type: pointer('data')

      - id: p_dma_tag
        type: pointer('data')

      - id: p_vif_code
        type: pointer('data')

      - id: numlen
        type: u4

      - id: p_gif_tag
        type: pointer('data')

      - id: pad12
        type: u4

      - id: pad13
        type: u4

  sh2_sys:
    seq:
      - id: step
        type: u4
        repeat: expr
        repeat-expr: 8

      - id: pre_playable
        type: u4

      - id: main_status
        type: s4

      - id: soft_reset
        type: u4

      - id: frame_cnt
        type: u4

  chara_bound:
    seq:
      - id: chara_id
        type: s4

      - id: r
        type: f4

  drama_demo_message_time:
    seq:
      - id: start
        type: u2

      - id: end
        type: u2

  drama_demo_play_info:
    seq:
      - id: demo_no
        type: s4

      - id: adr_dds_top
        type: pointer('data')

      - id: adr_anim
        type: pointer('data')

      - id: adr_msg_time
        type: pointer('drama_demo_message_time')

      - id: msg_start
        type: s2

      - id: voice_sd_no
        type: s2

      - id: adr_voice
        type: pointer('data')

      - id: stream_no
        type: s4

      - id: stream_start
        type: f4

      - id: add_pos_x
        type: f4

      - id: add_pos_z
        type: f4

  drama_demo_anim_info:
    seq:
      - id: name
        type: s1
        repeat: expr
        repeat-expr: 32

      - id: kind
        type: s2

      - id: id
        type: s2

      - id: start
        type: s2

      - id: end
        type: s2

  dds_frame:
    seq:
      - id: frame
        type: f4

      - size: 12

      - id: camera
        type: dds_frame_anon_8

      - id: light
        type: dds_frame_anon_9
        repeat: expr
        repeat-expr: 6

      - id: character
        type: dds_frame_anon_10
        repeat: expr
        repeat-expr: 7

  dds_frame_anon_8:
    seq:
      - id: position
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: interest
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: roll
        type: f4

      - id: plane
        type: f4

      - size: 8

  dds_frame_anon_9:
    seq:
      - id: position
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: interest
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: roll
        type: f4

      - size: 12

      - id: color
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: falloff
        type: f4
        repeat: expr
        repeat-expr: 2

      - id: cone
        type: f4
        repeat: expr
        repeat-expr: 2

      - id: visible
        type: s4

      - size: 12

  dds_frame_anon_10:
    seq:
      - id: position
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: visible
        type: s4

      - size: 12

  chizu_current_block:
    seq:
      - id: chizu
        type: s4

      - id: cp_x
        type: f4

      - id: cp_y
        type: f4

  chizu_marker_tex:
    seq:
      - id: u0
        type: s2

      - id: v0
        type: s2

      - id: u1
        type: s2

      - id: v1
        type: s2

  chizu_marker_list:
    seq:
      - id: tex
        type: pointer('chizu_marker_tex')

      - id: data
        type: pointer('data')

      - id: head
        type: s4

      - id: tail
        type: s4

  chizu_connect_info:
    seq:
      - id: up
        type: s1

      - id: down
        type: s1

      - id: right
        type: s1

      - id: left
        type: s1

  sh2gfw_area_head:
    seq:
      - id: area_id
        type: u4

      - id: to_global_tex_head
        type: u4

      - id: to_global_cluts_head
        type: u4

      - id: date
        type: u4

  sh2gfw_block_head:
    seq:
      - id: block_id
        type: u4

      - id: to_globaldef
        type: u4

      - id: to_localdef
        type: u4

      - id: to_rawblockdata_parms
        type: u4

      - id: to_local_tex
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: to_localcluts
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: texnum
        type: u4

      - id: globaltexnum
        type: u1

      - id: transtexnum
        type: u1

      - id: divflg
        type: u1

      - id: padc
        type: u1

  sh2gfw_blockglobal_head:
    seq:
      - id: gsregsamount
        type: u4

      - id: transamount
        type: u4

      - id: gtexnum
        type: u1

      - id: gtransnum
        type: u1

      - id: pads
        type: u2

      - id: pad2
        type: u4

  sh2gfw_blocklocal_head:
    seq:
      - id: gsregsamount
        type: u2
        repeat: expr
        repeat-expr: 3

      - id: transamount
        type: u2
        repeat: expr
        repeat-expr: 3

      - id: ltexnum
        type: u2

      - id: pads
        type: u2

  sh2gfw_gsregs_head:
    seq:
      - id: clutssize
        type: u4

      - id: to_next_data
        type: u4

      - id: to_tex_head
        type: u4

      - id: clutamount
        type: u1

      - id: transamount
        type: u1

      - id: eop_flg
        type: u1

      - id: tr_flg
        type: u1

      - id: fmt
        type: u1
        repeat: expr
        repeat-expr: 16

      - id: transparency
        type: u1
        repeat: expr
        repeat-expr: 16

  sh2gfw_giftag_head:
    seq:
      - id: gsregs_amount
        type: u2

      - id: trans_flg
        type: u1

      - id: eop_flg
        type: u1

      - id: to_next_gifhead
        type: u4

      - id: id
        type: u2

      - id: tcc
        type: u1

      - id: tfx
        type: u1

      - id: abe
        type: u1

      - id: pad1
        type: u1

      - id: pad2
        type: u1

      - id: pad3
        type: u1

  sh2gfw_tex_head:
    seq:
      - id: texture_no
        type: u4

      - id: x
        type: u2

      - id: y
        type: u2

      - id: w
        type: u2

      - id: h
        type: u2

      - id: color
        type: u1

      - id: padbyte
        type: u1

      - id: importance
        type: u2

      - id: datasize
        type: u4

      - id: allsize
        type: u4

      - id: sendpsm
        type: u1

      - id: drawpsm
        type: u1

      - id: bitshift
        type: u1

      - id: tagpoint
        type: u1

      - id: bitw
        type: u1

      - id: bith
        type: u1

      - id: check
        type: u2

      - id: giftag
        type: q_worddata
        size: 16

  sh2gfw_cluts_head:
    seq:
      - id: clutssize
        type: u4

      - id: to_gsregs
        type: u4

      - id: to_raw_clut
        type: u4

      - id: clutamount
        type: u1

      - id: transcluts
        type: u1

      - id: clw
        type: u1

      - id: clh
        type: u1

      - id: fmt
        type: u1
        repeat: expr
        repeat-expr: 16

      - id: transparency
        type: u1
        repeat: expr
        repeat-expr: 16

  sh2gfw_effect_man:
    seq:
      - id: effectid
        type: u2

      - id: vifmark
        type: u2

      - id: valid_id
        type: u2

      - id: pads
        type: u2

      - id: thr_cid
        type: s4

      - id: thr_sid
        type: s4

      - id: tex0_data
        type: u16

      - id: alpha
        type: u16

      - id: p_tex_man
        type: pointer('data')

      - id: p_tex_head
        type: pointer('data')

      - id: p_top
        type: pointer('data')

      - id: p_pad
        type: pointer('data')

  sh2gfw_area_data_man:
    seq:
      - id: areaid
        type: u4

      - id: use_globalflg
        type: u1
        repeat: expr
        repeat-expr: 7

      - id: use_transflg
        type: u1
        repeat: expr
        repeat-expr: 7

      - id: block_id
        type: u2
        repeat: expr
        repeat-expr: 7

      - id: block_man
        type: pointer('data')
        repeat: expr
        repeat-expr: 7

      - id: p_ah
        type: pointer('sh2gfw_area_head')

      - id: global_tex
        type: pointer('sh2gfw_tex_head')

      - id: global_clut
        type: pointer('sh2gfw_cluts_head')

      - id: global_transtex
        type: pointer('sh2gfw_tex_head')

      - id: global_transclut
        type: pointer('sh2gfw_cluts_head')

      - id: g_tex_man
        type: pointer('sh2gfw_tex_man')

      - id: g_transtex_man
        type: pointer('sh2gfw_tex_man')

      - id: gtex_mode
        type: u2

      - id: gtrans_mode
        type: u2

      - id: pad1
        type: u4

  sh2gfw_trans_man:
    seq:
      - id: blockid
        type: u4

      - id: p_am
        type: pointer('sh2gfw_area_data_man')

      - id: objnum
        type: u2
        repeat: expr
        repeat-expr: 4

      - id: trans_clutnum
        type: u4

      - id: pad2
        type: u4

      - id: pad3
        type: u4

      - id: pad4
        type: u4

      - id: trgehead
        type: pointer('data')
        repeat: expr
        repeat-expr: 4

      - id: p_tr_global_gif_h
        type: pointer('sh2gfw_giftag_head')
        repeat: expr
        repeat-expr: 64

      - id: p_g_tex_head
        type: pointer('sh2gfw_tex_head')

      - id: p_g_clut_head
        type: pointer('sh2gfw_cluts_head')

      - id: p_g_tex_man
        type: pointer('sh2gfw_tex_man')

      - id: used_ggifnum
        type: u1
        repeat: expr
        repeat-expr: 4

      - id: p_tr_trans_gif_h
        type: pointer('sh2gfw_giftag_head')
        repeat: expr
        repeat-expr: 64

      - id: p_tr_tex_head
        type: pointer('sh2gfw_tex_head')

      - id: p_tr_clut_head
        type: pointer('sh2gfw_cluts_head')

      - id: p_tr_tex_man
        type: pointer('sh2gfw_tex_man')

      - id: used_t_rgifnum
        type: u1
        repeat: expr
        repeat-expr: 4

  sh2gfw_model_header:
    seq:
      - id: no_texture_id
        type: u1

      - id: padc
        type: u1
        repeat: expr
        repeat-expr: 3

      - id: chara_id
        type: u4

      - id: texnum
        type: u4

      - id: to_tex_head_offset
        type: u4

      - id: to_cluts_head_offset
        type: u4

      - id: to_model_offset
        type: u4

      - id: to_kg1_offset
        type: s4

      - id: padi
        type: s4

      - id: p_tex_man
        type: pointer('data')
        repeat: expr
        repeat-expr: 8

  sh2gfw_all_model_data_man:
    seq:
      - id: n_active_character
        type: s4

      - id: n_load_character
        type: s4

      - id: p_mdm
        type: pointer('sh2gfw_model_draw_man')
        repeat: expr
        repeat-expr: 32

      - id: file_struct
        type: pointer('data')
        repeat: expr
        repeat-expr: 32

      - id: fid_model
        type: s4
        repeat: expr
        repeat-expr: 32

      - id: fid_anim
        type: s4
        repeat: expr
        repeat-expr: 32

      - id: fid_clus
        type: s4
        repeat: expr
        repeat-expr: 32

      - id: fid_kg1
        type: s4
        repeat: expr
        repeat-expr: 32

  sh2gfw_load_model_memman:
    seq:
      - id: index_model
        type: u4

      - id: index_anime
        type: u4

      - id: index_clus
        type: u4

      - id: p_lm_head
        type: pointer('data')

      - id: p_la_head
        type: pointer('data')

      - id: p_cl_head
        type: pointer('data')

  pic_draw_data:
    seq:
      - id: ap
        type: pointer('sh2gfw_area_head')

      - id: tex
        type: s4

      - id: clut
        type: s4

      - id: x0
        type: s2

      - id: y0
        type: s2

      - id: x1
        type: s2

      - id: y1
        type: s2

      - id: x2
        type: s2

      - id: y2
        type: s2

      - id: x3
        type: s2

      - id: y3
        type: s2

      - id: us0
        type: s4

      - id: vt0
        type: s4

      - id: us1
        type: s4

      - id: vt1
        type: s4

      - id: r
        type: u1

      - id: g
        type: u1

      - id: b
        type: u1

      - id: a
        type: u1

      - id: alpha_a
        type: u1

      - id: alpha_b
        type: u1

      - id: alpha_c
        type: u1

      - id: alpha_d
        type: u1

      - id: alpha_fix
        type: u1

      - id: test_ate
        type: u1

      - id: test_atst
        type: u1

      - id: test_aref
        type: u1

      - id: test_afail
        type: u1

      - id: test_date
        type: u1

      - id: test_datm
        type: u1

      - id: test_zte
        type: u1

      - id: test_ztst
        type: u1

      - id: pad
        type: u1
        repeat: expr
        repeat-expr: 3

      - id: otp
        type: s2

      - id: status
        type: s2

  fs_mgc_file:
    seq:
      - id: type
        type: b8

      - id: padding
        type: b24

      - id: parent
        type: pointer('fs_file')

      - id: start
        type: pointer('data')

      - id: end
        type: pointer('data')

  fs_cd_file:
    seq:
      - id: type
        type: b8

      - id: number
        type: b24

      - id: name
        type: pointer('data')

      - id: lsn
        type: s4

      - id: size
        type: s4

  fs_hd_file:
    seq:
      - id: type
        type: b8

      - id: padding
        type: b24

      - id: name
        type: pointer('data')

      - id: offset
        type: s4

      - id: size
        type: s4

  fs_mgp_file:
    seq:
      - id: type
        type: b8

      - id: padding
        type: b24

      - id: file
        type: pointer('fs_file')

      - id: start
        type: pointer('fs_mgc_file')

      - id: end
        type: pointer('fs_mgc_file')

  fs_mgf_file:
    seq:
      - id: type
        type: b8

      - id: padding
        type: b24

      - id: parent
        type: pointer('fs_file')

      - id: offset
        type: s4

      - id: size
        type: s4

  fs_file:
    instances:
      check:
        pos: 0
        type: fs_file_anon_11

      pack:
        pos: 0
        type: u16

      cd:
        pos: 0
        type: fs_cd_file

      hd:
        pos: 0
        type: fs_hd_file

      mgc:
        pos: 0
        type: fs_mgc_file

      mgf:
        pos: 0
        type: fs_mgf_file

      mgp:
        pos: 0
        type: fs_mgp_file

    seq:
      - size: 16

  fs_file_anon_11:
    seq:
      - id: type
        type: b8

      - id: number
        type: b24

      - id: pad0
        type: s4

      - id: pad1
        type: s4

      - id: pad2
        type: s4

  fs_file_index:
    instances:
      index:
        pos: 0
        type: fs_file_index_anon_12

      pack:
        pos: 0
        type: u8

    seq:
      - size: 8

  fs_file_index_anon_12:
    seq:
      - id: fp
        type: pointer('fs_file')

      - id: name
        type: pointer('data')

  chara_data_mem_admin_one:
    seq:
      - id: file
        type: pointer('fs_file_index')

      - id: adress
        type: pointer('data')

      - id: size
        type: s4

  chara_data_mem_admin:
    seq:
      - id: category
        type: s1

      - id: priority
        type: s1

      - id: kind
        type: s2

      - id: model
        type: chara_data_mem_admin_one

      - id: animation
        type: chara_data_mem_admin_one

      - id: shadow
        type: chara_data_mem_admin_one

      - id: cluster
        type: chara_data_mem_admin_one

  chara_data_item_file:
    seq:
      - id: kind
        type: s4

      - id: file
        type: pointer('fs_file_index')

  chara_data_entry_list_one:
    seq:
      - id: load
        type: s4

      - id: file
        type: pointer('fs_file_index')

      - id: adress
        type: pointer('data')

  chara_data_weapon_file:
    seq:
      - id: equip
        type: s2

      - id: kind
        type: s2

      - id: james_anim
        type: pointer('fs_file_index')

      - id: weapon_model
        type: pointer('fs_file_index')

      - id: weapon_model_r
        type: pointer('fs_file_index')

      - id: shadow_model
        type: pointer('fs_file_index')

  chara_data_entry_list:
    seq:
      - id: category
        type: s4

      - id: delete
        type: s2

      - id: kind
        type: s2

      - id: model
        type: chara_data_entry_list_one

      - id: animation
        type: chara_data_entry_list_one

      - id: shadow
        type: chara_data_entry_list_one

      - id: cluster
        type: chara_data_entry_list_one

  chara_data_demo_list:
    seq:
      - id: kind
        type: s4

      - id: model
        type: pointer('fs_file_index')

      - id: animation
        type: pointer('fs_file_index')

      - id: shadow
        type: pointer('fs_file_index')

      - id: cluster
        type: pointer('fs_file_index')

  chara_data_standard_list:
    seq:
      - id: kind
        type: s4

      - id: model
        type: pointer('fs_file_index')

      - id: animation
        type: pointer('fs_file_index')

      - id: shadow
        type: pointer('fs_file_index')

  chara_data_extra:
    seq:
      - id: adress
        type: pointer('data')

      - id: size
        type: s4

  chara_admin_room_distance:
    seq:
      - id: rm0
        type: s2

      - id: rm1
        type: s2

  vc_through_door_cam_param:
    seq:
      - id: active_f
        type: s4

      - id: timer
        type: f4

      - id: rail_ang_y
        type: f4

      - size: 4

      - id: rail_sta_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rail_sta_to_chara_dist
        type: f4

      - size: 12

  vc_cam_mv_param:
    seq:
      - id: accel_xz
        type: f4

      - id: accel_y
        type: f4

      - id: max_spd_xz
        type: f4

      - id: max_spd_y
        type: f4

  vc_watch_mv_param:
    seq:
      - id: ang_accel_x
        type: f4

      - id: ang_accel_y
        type: f4

      - id: max_ang_spd_x
        type: f4

      - id: max_ang_spd_y
        type: f4

  vc_fix_cam_manager:
    seq:
      - id: exception_f
        type: s4

      - id: add_ang_y
        type: f4

      - id: add_rd_x
        type: f4

      - id: add_rd_z
        type: f4

  vc_cir_cam_manager:
    seq:
      - id: origin
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: sw_l
        type: f4
        repeat: expr
        repeat-expr: 4

  vc_limit_area:
    seq:
      - id: min_hx
        type: f4

      - id: max_hx
        type: f4

      - id: min_hz
        type: f4

      - id: max_hz
        type: f4

      - id: min_hy
        type: f4

      - id: max_hy
        type: f4

  vc_road_area:
    seq:
      - id: x0
        type: f4

      - id: z0
        type: f4

      - id: x1
        type: f4

      - id: z1
        type: f4

      - id: x2
        type: f4

      - id: z2
        type: f4

      - id: min_hy
        type: f4

      - id: max_hy
        type: f4

  vc_chase_cam_param:
    seq:
      - id: ofs_hy
        type: f4

      - id: ratio_r_xz
        type: f4

      - id: lr_lim_ang_y
        type: f4

      - id: rr_lim_ang_y
        type: f4

  vc_settle_cam_param:
    seq:
      - id: sta_base_ang_y
        type: f4

      - id: end_base_ang_y
        type: f4

      - id: lr_lim_ang_y
        type: f4

      - id: rr_lim_ang_y
        type: f4

  vc_fix_ang_cam_param:
    seq:
      - id: ang_x
        type: f4

      - id: ang_y
        type: f4

      - id: ofs_hy
        type: f4

      - id: cam2wth_dist
        type: f4

  vc_locus_circle_cam_param:
    seq:
      - id: origin_x
        type: f4

      - id: origin_z
        type: f4

      - id: ang_y
        type: f4

      - id: radius
        type: f4

  vc_road_data:
    seq:
      - id: lim_sw
        type: vc_road_area

      - id: lim_rd
        type: vc_road_area

      - id: kind_id
        type: s4

      - id: flags
        type: s4

      - id: area_size_type
        type: s4

      - id: rd_type
        type: s4

      - id: mv_y_type
        type: s4

      - id: ofs_watch_hy
        type: f4

      - id: trace_btm_hy
        type: f4

      - id: rd_dir_type
        type: s4

      - id: projection
        type: f4

      - id: proj_volume
        type: f4

      - id: proj_sec
        type: f4

      - id: cam_mv_type
        type: s4

      - id: tmp
        type: vc_road_data_anon_13
        size: 16

  vc_road_data_anon_13:
    instances:
      data:
        pos: 0
        type: u1
        repeat: expr
        repeat-expr: 16

      chs:
        pos: 0
        type: vc_chase_cam_param

      stl:
        pos: 0
        type: vc_settle_cam_param

      fix:
        pos: 0
        type: vc_fix_ang_cam_param

      cir:
        pos: 0
        type: vc_locus_circle_cam_param

    seq:
      - size: 16

  vc_near_road_data:
    seq:
      - id: road_p
        type: pointer('vc_road_data')

      - id: rd_dir_type
        type: s4

      - id: use_priority
        type: s4

      - id: chara2road_sum_dist
        type: f4

      - id: chara2road_vec_x
        type: f4

      - id: chara2road_vec_z
        type: f4

      - id: rd
        type: vc_limit_area

      - id: sw
        type: vc_limit_area

      - size: 8

      - id: rd_rzm
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: rd_rim
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: sw_rzm
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: sw_rim
        type: f4
        repeat: expr
        repeat-expr: 16

  vc_work:
    seq:
      - id: view_cam_active_f
        type: s4

      - id: vc_road_ary_list
        type: pointer('data')

      - id: flags
        type: u2

      - size: 2

      - id: through_door_activate_init_f
        type: s4

      - id: through_door
        type: vc_through_door_cam_param

      - id: scr_half_ang_wy
        type: f4

      - id: scr_half_ang_wx
        type: f4

      - id: user_cam_mv_prm
        type: vc_cam_mv_param

      - size: 8

      - id: cam_tgt_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: cam_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: cam_mv_ang_y
        type: f4

      - size: 12

      - id: cam_velo
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: old_cam_excl_area_r
        type: f4

      - id: ideal_cam_pos_h
        type: f4

      - id: user_watch_mv_prm
        type: vc_watch_mv_param

      - size: 8

      - id: watch_tgt_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: watch_tgt_max_y
        type: f4

      - id: watch_tgt_ang_z
        type: f4

      - size: 8

      - id: cam_mat_ang
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: cam_mat
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: ofs_cam_ang
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: ofs_cam_ang_spd
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: base_cam_ang
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: old_base_cam_ang
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: cam_chara2ideal_ang_y
        type: f4

      - size: 12

      - id: cam_tgt_velo
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: cam_tgt_mv_ang_y
        type: f4

      - id: cam_tgt_spd
        type: f4

      - size: 8

      - id: chara_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: chara_bottom_y
        type: f4

      - id: chara_top_y
        type: f4

      - id: chara_center_y
        type: f4

      - id: chara_grnd_y
        type: f4

      - id: chara_head_pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: chara_mv_spd
        type: f4

      - id: chara_mv_ang_y
        type: f4

      - id: chara_ang_spd_y
        type: f4

      - id: chara_eye_ang_y
        type: f4

      - id: chara_eye_ang_wy
        type: f4

      - id: chara_watch_xz_r
        type: f4

      - id: fix_man
        type: vc_fix_cam_manager

      - size: 8

      - id: cir_man
        type: vc_cir_cam_manager

      - id: near_road_ary
        type: vc_near_road_data
        repeat: expr
        repeat-expr: 128

      - id: near_road_suu
        type: s4

      - size: 12

      - id: cur_near_road
        type: vc_near_road_data

      - id: nearest_enemy_p
        type: pointer('sub_character')

      - id: nearest_enemy_xz_dist
        type: f4

      - id: enemy_input_watch_y
        type: f4

      - id: nearest_item_p
        type: pointer('sub_character')

      - id: nearest_item_xz_dist
        type: f4

      - size: 12

  vc_camera_intinfo:
    seq:
      - id: mode
        type: s4

      - id: mv_smooth
        type: s4

      - id: ev_cam_rate
        type: f4

  vc_projection_params:
    seq:
      - id: new
        type: f4

      - id: old
        type: f4

      - id: delta
        type: f4

      - id: flg
        type: s4

  vc_pre_info:
    seq:
      - id: hero_neck_wm
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: hero_neck_lm
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: hero_neck_lwm
        type: f4
        repeat: expr
        repeat-expr: 16

      - id: hero_head_ang_x
        type: f4

      - id: hero_head_ang_y
        type: f4

      - id: hero_eye_y
        type: f4

  kanri:
    seq:
      - id: pos
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: ang
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: rot_spd
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: velo_y
        type: f4

      - id: velo_xz
        type: f4

      - id: velo_houi
        type: f4

  sys_w:
    seq:
      - id: cam_ang_y
        type: f4

      - id: cam_ang_z
        type: f4

      - id: cam_r_xz
        type: f4

      - id: cam_y
        type: f4

      - id: hero
        type: kanri

  wfont_stream_data:
    seq:
      - id: x
        type: u2

      - id: y
        type: u2

      - id: vw
        type: u2

      - id: vh
        type: u2

      - id: u
        type: u2

      - id: v
        type: u2

      - id: rgb_u
        type: u4

      - id: rgb_d
        type: u4

      - id: w
        type: u2

      - id: h
        type: u2

  mfont_stream_data:
    seq:
      - id: x
        type: u2

      - id: y
        type: u2

      - id: u
        type: u2

      - id: v
        type: u2

  font_stream_data:
    seq:
      - id: x
        type: u2

      - id: y
        type: u2

      - id: w
        type: u2

      - id: h
        type: u2

      - id: u
        type: u2

      - id: v
        type: u2

      - id: rgb_u
        type: u4

      - id: rgb_d
        type: u4

  font_data:
    seq:
      - id: tex_head
        type: u4
        repeat: expr
        repeat-expr: 12

      - id: clut_head
        type: u4
        repeat: expr
        repeat-expr: 12

      - id: clut
        type: u4
        repeat: expr
        repeat-expr: 8

      - id: texbuf
        type: u1
        repeat: expr
        repeat-expr: 131072

      - id: tex0
        type: u8

      - id: fonttype
        type: s4

      - id: rgb_u
        type: u4

      - id: rgb_d
        type: u4

      - id: rgb_s
        type: u4
        repeat: expr
        repeat-expr: 4

      - id: alpha
        type: u4

      - id: alpha_base
        type: u4

      - id: flag
        type: u4

      - id: x
        type: u2

      - id: y
        type: u2

      - id: wide_w
        type: u2

      - id: wide_h
        type: u2

      - id: right_x
        type: u2

      - id: right_y
        type: u2

      - id: wm
        type: u2

      - id: hm
        type: u2

      - id: wait_count
        type: s2

      - id: wait_type
        type: s2

      - id: page_sound
        type: s2

      - id: code
        type: u2
        repeat: expr
        repeat-expr: 400

      - id: upper
        type: s2
        repeat: expr
        repeat-expr: 400

      - id: lower
        type: s2
        repeat: expr
        repeat-expr: 400

      - id: top
        type: s2

      - id: bottom
        type: s2

      - id: st_num
        type: s2

      - id: w_st_num
        type: s2

      - id: prl_count
        type: s2

      - id: preload
        type: s2

      - id: shadow_max
        type: s2

      - id: shadow_now
        type: s2

      - id: sel_xl
        type: u2

      - id: sel_xr
        type: u2

      - id: sel_yu
        type: u2
        repeat: expr
        repeat-expr: 4

      - id: sel_yd
        type: u2
        repeat: expr
        repeat-expr: 4

      - id: sel_max
        type: s2

      - id: sel_now
        type: s2

      - id: mes_v
        type: u2
        repeat: expr
        repeat-expr: 640

      - size: 2

      - id: mes_str_now
        type: pointer('data')

      - id: mes_str
        type: pointer('data')

      - id: prl_str
        type: pointer('data')

      - id: stream
        type: pointer('font_stream_data')

      - id: w_stream
        type: pointer('wfont_stream_data')

      - id: m_stream
        type: pointer('mfont_stream_data')

      - id: stream_max
        type: u2

      - id: w_stream_max
        type: u2

      - id: m_stream_max
        type: u2

      - id: m_code
        type: u2
        repeat: expr
        repeat-expr: 256

      - id: m_upper
        type: s2
        repeat: expr
        repeat-expr: 256

      - id: m_lower
        type: s2
        repeat: expr
        repeat-expr: 256

      - id: m_top
        type: s2

      - id: m_bottom
        type: s2

      - id: m_st_num
        type: s2

      - id: m_base_x
        type: s4

      - id: m_base_y
        type: s4

      - id: m_base_z
        type: s4

      - id: m_rgba
        type: u4

      - id: m_sx
        type: s4

      - id: m_sy
        type: s4

      - id: m_w
        type: s4

      - id: m_h
        type: s4

      - id: m_x
        type: s4

      - id: m_y
        type: s4

      - id: bar_blink
        type: f4

      - id: p_cur
        type: pointer('data')

      - id: base_x
        type: s4

      - id: base_y
        type: s4

      - id: base_z
        type: s4

  sce_gs_disp_env:
    seq:
      - id: pmode
        type: t_gs_pmode

      - id: smode2
        type: t_gs_smode2

      - id: dispfb
        type: t_gs_dispfb2

      - id: display
        type: t_gs_display2

      - id: bgcolor
        type: t_gs_bgcolor

  sce_gs_draw_env1:
    seq:
      - id: frame1
        type: sce_gs_frame

      - id: frame1addr
        type: u8

      - id: zbuf1
        type: sce_gs_zbuf

      - id: zbuf1addr
        type: s8

      - id: xyoffset1
        type: sce_gs_xyoffset

      - id: xyoffset1addr
        type: s8

      - id: scissor1
        type: sce_gs_scissor

      - id: scissor1addr
        type: s8

      - id: prmodecont
        type: sce_gs_prmodecont

      - id: prmodecontaddr
        type: s8

      - id: colclamp
        type: sce_gs_colclamp

      - id: colclampaddr
        type: s8

      - id: dthe
        type: sce_gs_dthe

      - id: dtheaddr
        type: s8

      - id: test1
        type: sce_gs_test

      - id: test1addr
        type: s8

  sce_gs_draw_env2:
    seq:
      - id: frame2
        type: sce_gs_frame

      - id: frame2addr
        type: u8

      - id: zbuf2
        type: sce_gs_zbuf

      - id: zbuf2addr
        type: s8

      - id: xyoffset2
        type: sce_gs_xyoffset

      - id: xyoffset2addr
        type: s8

      - id: scissor2
        type: sce_gs_scissor

      - id: scissor2addr
        type: s8

      - id: prmodecont
        type: sce_gs_prmodecont

      - id: prmodecontaddr
        type: s8

      - id: colclamp
        type: sce_gs_colclamp

      - id: colclampaddr
        type: s8

      - id: dthe
        type: sce_gs_dthe

      - id: dtheaddr
        type: s8

      - id: test2
        type: sce_gs_test

      - id: test2addr
        type: s8

  sce_gs_clear:
    seq:
      - id: testa
        type: sce_gs_test

      - id: testaaddr
        type: s8

      - id: prim
        type: sce_gs_prim

      - id: primaddr
        type: s8

      - id: rgbaq
        type: sce_gs_rgbaq

      - id: rgbaqaddr
        type: s8

      - id: xyz2a
        type: sce_gs_xyz

      - id: xyz2aaddr
        type: s8

      - id: xyz2b
        type: sce_gs_xyz

      - id: xyz2baddr
        type: s8

      - id: testb
        type: sce_gs_test

      - id: testbaddr
        type: s8

  sce_gs_dbuff:
    seq:
      - id: disp
        type: sce_gs_disp_env
        repeat: expr
        repeat-expr: 2

      - id: giftag0
        type: sce_gif_tag

      - id: draw0
        type: sce_gs_draw_env1

      - id: clear0
        type: sce_gs_clear

      - id: giftag1
        type: sce_gif_tag

      - id: draw1
        type: sce_gs_draw_env1

      - id: clear1
        type: sce_gs_clear

  sce_gs_dbuff_dc:
    seq:
      - id: disp
        type: sce_gs_disp_env
        repeat: expr
        repeat-expr: 2

      - id: giftag0
        type: sce_gif_tag

      - id: draw01
        type: sce_gs_draw_env1

      - id: draw02
        type: sce_gs_draw_env2

      - id: clear0
        type: sce_gs_clear

      - id: giftag1
        type: sce_gif_tag

      - id: draw11
        type: sce_gs_draw_env1

      - id: draw12
        type: sce_gs_draw_env2

      - id: clear1
        type: sce_gs_clear

  sce_gs_tex_env:
    seq:
      - id: texflush
        type: sce_gs_texflush

      - id: texflushaddr
        type: s8

      - id: tex11
        type: sce_gs_tex1

      - id: tex11addr
        type: s8

      - id: tex01
        type: sce_gs_tex0

      - id: tex01addr
        type: s8

      - id: clamp1
        type: sce_gs_clamp

      - id: clamp1addr
        type: s8

  sce_gs_tex_env2:
    seq:
      - id: texflush
        type: sce_gs_texflush

      - id: texflushaddr
        type: s8

      - id: tex12
        type: sce_gs_tex1

      - id: tex12addr
        type: s8

      - id: tex02
        type: sce_gs_tex0

      - id: tex02addr
        type: s8

      - id: clamp2
        type: sce_gs_clamp

      - id: clamp2addr
        type: s8

  sce_gs_alpha_env:
    seq:
      - id: alpha1
        type: sce_gs_alpha

      - id: alpha1addr
        type: s8

      - id: pabe
        type: sce_gs_pabe

      - id: pabeaddr
        type: s8

      - id: texa
        type: sce_gs_texa

      - id: texaaddr
        type: s8

      - id: fba1
        type: sce_gs_fba

      - id: fba1addr
        type: s8

  sce_gs_alpha_env2:
    seq:
      - id: alpha2
        type: sce_gs_alpha

      - id: alpha2addr
        type: s8

      - id: pabe
        type: sce_gs_pabe

      - id: pabeaddr
        type: s8

      - id: texa
        type: sce_gs_texa

      - id: texaaddr
        type: s8

      - id: fba2
        type: sce_gs_fba

      - id: fba2addr
        type: s8

  sce_gs_load_image:
    seq:
      - id: giftag0
        type: sce_gif_tag

      - id: bitbltbuf
        type: sce_gs_bitbltbuf

      - id: bitbltbufaddr
        type: s8

      - id: trxpos
        type: sce_gs_trxpos

      - id: trxposaddr
        type: s8

      - id: trxreg
        type: sce_gs_trxreg

      - id: trxregaddr
        type: s8

      - id: trxdir
        type: sce_gs_trxdir

      - id: trxdiraddr
        type: s8

      - id: giftag1
        type: sce_gif_tag

  sce_gs_store_image:
    seq:
      - id: vifcode
        type: u4
        repeat: expr
        repeat-expr: 4

      - id: giftag
        type: sce_gif_tag

      - id: bitbltbuf
        type: sce_gs_bitbltbuf

      - id: bitbltbufaddr
        type: s8

      - id: trxpos
        type: sce_gs_trxpos

      - id: trxposaddr
        type: s8

      - id: trxreg
        type: sce_gs_trxreg

      - id: trxregaddr
        type: s8

      - id: finish
        type: sce_gs_finish

      - id: finishaddr
        type: s8

      - id: trxdir
        type: sce_gs_trxdir

      - id: trxdiraddr
        type: s8

  sce_gs_gparam:
    seq:
      - id: sce_gs_inter_mode
        type: s2

      - id: sce_gs_out_mode
        type: s2

      - id: sce_gs_ff_mode
        type: s2

      - id: sce_gs_version
        type: s2

      - id: sce_gs_vs_cfunc
        type: pointer('data')

      - id: sce_gs_vs_cid
        type: s4

  sh_gs_loop_env:
    seq:
      - id: gs_draw_fb_ps
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: gs_now_disp_fb_ps
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: gs_next_disp_fb_ps
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: gs_tex_tb_ps
        type: u4
        repeat: expr
        repeat-expr: 24

      - id: gs_shadow_fbp
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: gs_shadow_work_fbp
        type: u4
        repeat: expr
        repeat-expr: 3

      - id: clutsize
        type: u2

      - id: clutamount
        type: u2

      - id: gs_clut_page
        type: u2
        repeat: expr
        repeat-expr: 8

  sh_gs_draw_env:
    seq:
      - id: giftag
        type: sce_gif_tag

      - id: draw
        type: sce_gs_draw_env1

      - id: drawq2
        type: q_worddata
        repeat: expr
        repeat-expr: 5

      - id: clear
        type: sce_gs_clear

      - id: giftag_nc
        type: sce_gif_tag

      - id: draw_nc
        type: sce_gs_draw_env1

      - id: drawq2_nc
        type: q_worddata
        repeat: expr
        repeat-expr: 5

      - id: gifad_frame_normal
        type: q_worddata
        size: 16

      - id: frame_normal
        type: q_worddata
        size: 16

      - id: gifad_frame_mskalpha
        type: q_worddata
        size: 16

      - id: frame_mskalpha
        type: q_worddata
        size: 16

      - id: gifad_frame_msk_dalpha
        type: q_worddata
        size: 16

      - id: frame_msk_dalpha
        type: q_worddata
        size: 16

      - id: gifad_frame_msk_rgb
        type: q_worddata
        size: 16

      - id: frame_msk_rgb
        type: q_worddata
        size: 16

  sh_gs_stencil_draw_env:
    seq:
      - id: giftag
        type: sce_gif_tag

      - id: draw
        type: sce_gs_draw_env1

      - id: alpha1
        type: q_worddata
        size: 16

      - id: drawq2
        type: q_worddata
        repeat: expr
        repeat-expr: 6

      - id: clear
        type: sce_gs_clear

      - id: frame
        type: q_worddata
        size: 16

      - id: giftag_nc
        type: sce_gif_tag

      - id: draw_nc
        type: sce_gs_draw_env1

      - id: alpha1_nc
        type: q_worddata
        size: 16

      - id: drawq2_nc
        type: q_worddata
        repeat: expr
        repeat-expr: 6

      - id: gifad_frame_normal
        type: q_worddata
        size: 16

      - id: frame_normal
        type: q_worddata
        size: 16

      - id: gifad_frame_mskalpha
        type: q_worddata
        size: 16

      - id: frame_mskalpha
        type: q_worddata
        size: 16

      - id: gifad_frame_msk_dalpha
        type: q_worddata
        size: 16

      - id: frame_msk_dalpha
        type: q_worddata
        size: 16

  sh_gs_tiny_draw_env:
    seq:
      - id: giftag
        type: q_worddata
        size: 16

      - id: frame
        type: q_worddata
        size: 16

      - id: scissor
        type: q_worddata
        size: 16

      - id: xyoffset
        type: q_worddata
        size: 16

      - id: zbuf
        type: q_worddata
        size: 16

      - id: test
        type: q_worddata
        size: 16

      - id: gifad_normal
        type: q_worddata
        size: 16

      - id: frame_normal
        type: q_worddata
        size: 16

      - id: gifad_mskalpha
        type: q_worddata
        size: 16

      - id: frame_mskalpha
        type: q_worddata
        size: 16

      - id: gifad_msk_dalpha
        type: q_worddata
        size: 16

      - id: frame_msk_dalpha
        type: q_worddata
        size: 16

  sh_gs_all_env:
    seq:
      - id: loop_counter
        type: u8

      - id: loop
        type: u4

      - id: loop3
        type: u4

      - id: loop_env
        type: sh_gs_loop_env

      - id: disp_env
        type: sce_gs_disp_env
        repeat: expr
        repeat-expr: 3

      - size: 8

      - id: draw_env
        type: sh_gs_draw_env
        repeat: expr
        repeat-expr: 3

      - id: stencil_buf
        type: sh_gs_stencil_draw_env
        repeat: expr
        repeat-expr: 3

      - id: stencil_work
        type: sh_gs_tiny_draw_env
        repeat: expr
        repeat-expr: 6

      - id: default_env
        type: q_worddata
        repeat: expr
        repeat-expr: 10

      - id: stencil_env
        type: q_worddata
        repeat: expr
        repeat-expr: 10

      - id: compshadow_env
        type: q_worddata
        repeat: expr
        repeat-expr: 10

      - id: filter_a
        type: q_worddata
        repeat: expr
        repeat-expr: 10

      - id: filter_b
        type: q_worddata
        repeat: expr
        repeat-expr: 10

      - id: filter_c
        type: q_worddata
        repeat: expr
        repeat-expr: 10

      - id: filter_d
        type: q_worddata
        repeat: expr
        repeat-expr: 10

      - id: move_gtex
        type: q_worddata
        repeat: expr
        repeat-expr: 8

      - id: gs_reg_alpha_a
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_alpha_b
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_alpha_c
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_alpha_d
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_alpha_e
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_test_a
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_test_b
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_test_c
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_test_d
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_texa_a
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_texa_b
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_zbuf_a
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_zbuf_b
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_pabe_a
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_pabe_b
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_fba_a
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_fba_b
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_prmodecont_a
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_reg_prmodecont_b
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_sync_dummy_label
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: gs_sync_dummy_texflush
        type: q_worddata
        repeat: expr
        repeat-expr: 2

      - id: now_draw_env
        type: sh_gs_draw_env

  sce_mc_st_date_time:
    seq:
      - id: resv2
        type: u1

      - id: sec
        type: u1

      - id: min
        type: u1

      - id: hour
        type: u1

      - id: day
        type: u1

      - id: month
        type: u1

      - id: year
        type: u2

  sce_mc_tbl_get_dir:
    seq:
      - id: create
        type: sce_mc_st_date_time

      - id: modify
        type: sce_mc_st_date_time

      - id: file_size_byte
        type: u4

      - id: attr_file
        type: u2

      - id: reserve1
        type: u2

      - id: reserve2
        type: u4

      - id: pda_apl_no
        type: u4

      - id: entry_name
        type: u1
        repeat: expr
        repeat-expr: 32

  mc_fileinfo:
    seq:
      - id: dirid
        type: u1

      - id: fileid
        type: u1

      - id: scene
        type: u1

      - id: b_level
        type: u1

      - id: r_level
        type: u1

      - id: status
        type: u1

      - id: savecount
        type: u2

      - id: time
        type: f4

      - id: total_time
        type: f4

      - id: csum
        type: u4

  mc_dirdata:
    seq:
      - id: message
        type: s1
        repeat: expr
        repeat-expr: 28

      - id: flag
        type: u4

      - id: file
        type: mc_fileinfo
        repeat: expr
        repeat-expr: 15

      - id: playing
        type: playing_info

      - id: lastsave
        type: s4

      - id: id
        type: u4

      - id: csum
        type: u4
        repeat: expr
        repeat-expr: 4

      - id: pad
        type: u4
        repeat: expr
        repeat-expr: 130

      - id: csum_all
        type: u8

  mc_savedata:
    seq:
      - id: csum1
        type: u4

      - id: csum2
        type: u4

      - id: data
        type: u1
        repeat: expr
        repeat-expr: 8168

      - id: csum3
        type: u4

      - id: pad
        type: u4

      - id: csum4
        type: u8

  mc_jobs:
    seq:
      - id: job
        type: s1

      - id: port
        type: s1

      - id: data
        type: s2

  mc_codec_data:
    seq:
      - id: key1
        type: u1
        repeat: expr
        repeat-expr: 24

      - id: key2
        type: u1
        repeat: expr
        repeat-expr: 16

      - id: mode
        type: s4

      - id: step
        type: s4

      - id: pos
        type: pointer('data')

      - id: count
        type: s4

      - id: zcount
        type: s4

      - id: csum1
        type: u4

      - id: csum2
        type: u4

      - size: 4

      - id: csum4
        type: u8

  mc_work:
    seq:
      - id: status
        type: u2

      - id: ls_port
        type: s1

      - id: ls_dir
        type: s1

      - id: ls_file
        type: s1

      - size: 3

      - id: ls_dir_id
        type: u4

  mc_work2:
    seq:
      - id: dirdata
        type: mc_dirdata

      - id: savedata
        type: mc_savedata

      - id: dirtbl
        type: sce_mc_tbl_get_dir
        repeat: expr
        repeat-expr: 20

      - id: tmpinfo
        type: mc_fileinfo
        repeat: expr
        repeat-expr: 75

      - id: fileinfo
        type: mc_fileinfo
        repeat: expr
        repeat-expr: 225

      - id: jobs
        type: mc_jobs
        repeat: expr
        repeat-expr: 16

      - id: port
        type: s1

      - id: dirnum
        type: s1

      - id: files
        type: s1

      - id: tbl_files
        type: s1

      - id: job
        type: s1

      - id: job_port
        type: s1

      - id: job_data
        type: s1

      - id: job_step
        type: s1

      - id: job_num
        type: s1

      - id: job_end
        type: s1

      - size: 2

      - id: result
        type: s4

      - id: type
        type: s4
        repeat: expr
        repeat-expr: 2

      - id: free
        type: s4
        repeat: expr
        repeat-expr: 2

      - id: format
        type: s4
        repeat: expr
        repeat-expr: 2

      - id: info
        type: s4
        repeat: expr
        repeat-expr: 2

      - id: d_ent
        type: u1
        repeat: expr
        repeat-expr: 2

      - id: portstatus
        type: s1
        repeat: expr
        repeat-expr: 3

      - id: dirstatus
        type: s1
        repeat: expr
        repeat-expr: 15

      - id: filemax
        type: s1
        repeat: expr
        repeat-expr: 3

      - id: tmp_status
        type: s1
        repeat: expr
        repeat-expr: 3

      - size: 2

      - id: type_old
        type: s4

      - id: retry
        type: s2

      - id: info_count
        type: s2

      - id: fd
        type: s4

      - id: fid
        type: s4
        repeat: expr
        repeat-expr: 2

      - id: autoload
        type: s2

      - id: saveload
        type: s1

      - id: menu_step
        type: s1

      - id: menu_sstep
        type: s1

      - id: menu_base
        type: s1
        repeat: expr
        repeat-expr: 3

      - id: menu_num
        type: s1
        repeat: expr
        repeat-expr: 3

      - id: tmp_num
        type: s1

      - id: menu_info
        type: s1

      - id: menu_infotype
        type: s1

      - id: menu_timer
        type: s1

      - id: menu_port
        type: s1

      - id: menu_yesno
        type: s1

      - id: menu_newdir
        type: s1

      - id: menu_bk
        type: s1

      - size: 1

      - id: menu_scroll
        type: f4

      - id: menu_count
        type: f4

      - id: menu_an_count
        type: f4

      - id: extra_name
        type: s1
        repeat: expr
        repeat-expr: 8

      - id: extra_adr
        type: pointer('data')

      - id: extra_size
        type: s4

      - id: dirid
        type: u4
        repeat: expr
        repeat-expr: 15

      - id: dirid_new
        type: u4

      - id: fname
        type: s1
        repeat: expr
        repeat-expr: 64

      - id: dtime
        type: u8
        repeat: expr
        repeat-expr: 2

      - id: loaddata
        type: pointer('mc_fileinfo')

      - size: 4

      - id: cd
        type: mc_codec_data

      - size: 24

  mc_icon_sys:
    seq:
      - id: head
        type: u1
        repeat: expr
        repeat-expr: 4

      - id: reserv1
        type: u2

      - id: offs_lf
        type: u2

      - id: reserv2
        type: u4

      - id: trans_rate
        type: u4

      - id: bg_color
        type: s4
        repeat: expr
        repeat-expr: 16

      - id: light_dir
        type: f4
        repeat: expr
        repeat-expr: 12

      - id: light_color
        type: f4
        repeat: expr
        repeat-expr: 12

      - id: ambient
        type: f4
        repeat: expr
        repeat-expr: 4

      - id: title_name
        type: u1
        repeat: expr
        repeat-expr: 68

      - id: fname_view
        type: u1
        repeat: expr
        repeat-expr: 64

      - id: fname_copy
        type: u1
        repeat: expr
        repeat-expr: 64

      - id: fname_del
        type: u1
        repeat: expr
        repeat-expr: 64

      - id: reserve3
        type: u1
        repeat: expr
        repeat-expr: 512

  opd_w:
    seq:
      - id: u0
        type: f4

      - id: u1
        type: f4

      - id: v0
        type: f4

      - id: v1
        type: f4

      - id: x0
        type: f4

      - id: y0
        type: f4

      - id: x1
        type: f4

      - id: y1
        type: f4

      - id: offset_x
        type: f4

      - id: offset_y
        type: f4

      - id: scale_x
        type: f4

      - id: scale_y
        type: f4

      - id: rgb
        type: u1

      - id: step
        type: u1

      - id: timer
        type: u1

      - size: 1

  title_spr_work:
    seq:
      - id: u0
        type: s2

      - id: v0
        type: s2

      - id: u1
        type: s2

      - id: v1
        type: s2

      - id: w
        type: s2

      - id: h
        type: s2

      - size: 4

      - id: rgba
        type: s4
        repeat: expr
        repeat-expr: 4

  title_point_list:
    seq:
      - id: pos_x
        type: f4

      - id: pos_y
        type: f4

      - id: pos_z
        type: f4

      - id: rot
        type: f4

      - id: stg
        type: s4

      - id: jump_nemu_id
        type: s4

  title_data_work:
    seq:
      - id: memcard
        type: s4

      - id: mode
        type: s4

      - id: sel
        type: s4

      - id: timer
        type: f4

      - id: alpha
        type: s4

      - id: alphar
        type: f4

      - id: menu
        type: u4
        repeat: expr
        repeat-expr: 10

      - id: pic0
        type: pic_draw_data

      - id: pload0
        type: pointer('data')

      - id: pload1
        type: pointer('data')

      - id: texadr
        type: s4

      - id: clutadr
        type: s4

  title_spr_chg_color_work:
    seq:
      - id: start_rgba
        type: s4
        repeat: expr
        repeat-expr: 4

      - id: end_rgba
        type: s4
        repeat: expr
        repeat-expr: 4

      - id: cycle
        type: f4

      - id: timer
        type: f4

      - size: 8

  debug_print_info:
    seq:
      - id: xofs
        type: s4

      - id: yofs
        type: s4

      - id: x
        type: s4

      - id: y
        type: s4

      - id: w
        type: s4

      - id: h
        type: s4

      - id: tab
        type: s4

      - id: xofs_r
        type: s4

      - id: yofs_r
        type: s4

      - id: y_r
        type: s4

  screen_effect_parameter:
    seq:
      - id: fade_status
        type: s4

      - id: fade_type
        type: s4

      - id: fade_timer_now
        type: f4

      - id: fade_timer_max
        type: f4

  movie_wrk:
    seq:
      - id: play_event_no
        type: s4

      - id: play_event_sta
        type: s4

  qword:
    instances:
      q:
        pos: 0
        type: u16

      l:
        pos: 0
        type: u8
        repeat: expr
        repeat-expr: 2

      i:
        pos: 0
        type: u4
        repeat: expr
        repeat-expr: 4

      s:
        pos: 0
        type: u2
        repeat: expr
        repeat-expr: 8

      c:
        pos: 0
        type: u1
        repeat: expr
        repeat-expr: 16

    seq:
      - size: 16

  str_file:
    seq:
      - id: is_on_cd
        type: s4

      - id: size
        type: s4

      - id: fp
        type: sce_cdl_file

      - id: iop_buf
        type: pointer('data')

      - id: fd
        type: s4

  anon_14:
    seq:
      - id: status
        type: s4

      - id: ctrl
        type: s4

      - id: file
        type: pointer('fs_file_index')

      - id: readrest
        type: s4

      - id: writerest
        type: s4

      - id: is_paused
        type: s4

      - id: is_started
        type: s4

      - id: proceed_zero_count
        type: s2

      - size: 2

      - id: cnt
        type: s4

      - id: st_frame
        type: s4

      - id: movieabort
        type: s4

      - id: framecnt
        type: s4

      - id: maskon
        type: s4

  sce_mpeg:
    seq:
      - id: width
        type: s4

      - id: height
        type: s4

      - id: frame_count
        type: s4

      - size: 4

      - id: pts
        type: s8

      - id: dts
        type: s8

      - id: flags
        type: u8

      - id: pts2nd
        type: s8

      - id: dts2nd
        type: s8

      - id: flags2nd
        type: u8

      - id: sys
        type: pointer('data')

      - size: 4

  sce_mpeg_cb_data_error:
    seq:
      - id: type
        type: u1

      - size: 3

      - id: err_message
        type: pointer('data')

  sce_mpeg_cb_data_time_stamp:
    seq:
      - id: type
        type: u1

      - size: 7

      - id: pts
        type: s8

      - id: dts
        type: s8

  sce_mpeg_cb_data_str:
    seq:
      - id: type
        type: u1

      - size: 3

      - id: header
        type: pointer('data')

      - id: data
        type: pointer('data')

      - id: len
        type: u4

      - id: pts
        type: s8

      - id: dts
        type: s8

  sce_mpeg_cb_data:
    instances:
      type:
        pos: 0
        type: u1

      error:
        pos: 0
        type: sce_mpeg_cb_data_error

      ts:
        pos: 0
        type: sce_mpeg_cb_data_time_stamp

      str:
        pos: 0
        type: sce_mpeg_cb_data_str

    seq:
      - size: 32

  sce_ipu_rgb32:
    seq:
      - id: pix
        type: u4
        repeat: expr
        repeat-expr: 256

  sce_ipu_dma_env:
    seq:
      - id: d4madr
        type: u4

      - id: d4tadr
        type: u4

      - id: d4qwc
        type: u4

      - id: d4chcr
        type: u4

      - id: d3madr
        type: u4

      - id: d3qwc
        type: u4

      - id: d3chcr
        type: u4

      - id: ipubp
        type: u4

      - id: ipuctrl
        type: u4

  sce_ipu_raw8:
    seq:
      - id: y
        type: u1
        repeat: expr
        repeat-expr: 256

      - id: cb
        type: u1
        repeat: expr
        repeat-expr: 64

      - id: cr
        type: u1
        repeat: expr
        repeat-expr: 64

  time_stamp:
    seq:
      - id: pts
        type: s8

      - id: dts
        type: s8

      - id: pos
        type: s4

      - id: len
        type: s4

  vi_buf:
    seq:
      - id: data
        type: pointer('data')

      - id: tag
        type: pointer('data')

      - id: n
        type: s4

      - id: dma_start
        type: s4

      - id: dma_n
        type: s4

      - id: read_bytes
        type: s4

      - id: buff_size
        type: s4

      - id: env
        type: sce_ipu_dma_env

      - id: sema
        type: s4

      - id: is_active
        type: s4

      - id: total_bytes
        type: s8

      - id: ts
        type: pointer('time_stamp')

      - id: n_ts
        type: s4

      - id: count_ts
        type: s4

      - id: wt_ts
        type: s4

  csc_vu1:
    seq:
      - id: micro
        type: pointer('data')
        repeat: expr
        repeat-expr: 6

  vo_data:
    seq:
      - id: v
        type: u1
        repeat: expr
        repeat-expr: 393216

  vo_tag:
    seq:
      - id: status
        type: s4

      - id: v
        type: pointer('data')

      - id: dummy
        type: s4
        repeat: expr
        repeat-expr: 14

  vo_buf:
    seq:
      - id: data
        type: pointer('vo_data')

      - id: tag_inter
        type: pointer('vo_tag')

      - id: tag
        type: pointer('vo_tag')

      - id: write
        type: s4

      - id: count
        type: s4

      - id: size
        type: s4

  video_dec:
    seq:
      - id: vibuf
        type: vi_buf

      - id: state
        type: s4

      - id: sema
        type: s4

      - id: hid_endimage
        type: s4

      - id: hid_vblank
        type: s4

      - id: cscvu1
        type: csc_vu1

  spu_stream_header:
    seq:
      - id: id
        type: s1
        repeat: expr
        repeat-expr: 4

      - id: size
        type: s4

      - id: type
        type: s4

      - id: rate
        type: s4

      - id: ch
        type: s4

      - id: inter_size
        type: s4

      - id: loop_start
        type: s4

      - id: loop_end
        type: s4

  spu_stream_body:
    seq:
      - id: id
        type: s1
        repeat: expr
        repeat-expr: 4

      - id: size
        type: s4

  audio_dec:
    seq:
      - id: state
        type: s4

      - id: sshd
        type: spu_stream_header

      - id: ssbd
        type: spu_stream_body

      - id: hdr_count
        type: s4

      - id: data
        type: pointer('data')

      - id: put
        type: s4

      - id: count
        type: s4

      - id: size
        type: s4

      - id: total_bytes
        type: s4

      - id: iop_buff
        type: s4

      - id: iop_buff_size
        type: s4

      - id: iop_last_pos
        type: s4

      - id: iop_pause_pos
        type: s4

      - id: total_bytes_sent
        type: s4

      - id: iop_zero
        type: s4

  read_buf:
    seq:
      - id: data
        type: u1
        repeat: expr
        repeat-expr: 327680

      - id: put
        type: s4

      - id: count
        type: s4

      - id: size
        type: s4

  pss_common_work:
    seq:
      - id: mpeg_workp
        type: pointer('data')

      - id: read_bufp
        type: pointer('read_buf')

      - id: vi_buf_datap
        type: pointer('data')

      - size: 52

      - id: time_stamp
        type: time_stamp
        repeat: expr
        repeat-expr: 512

      - id: vo_buf_datap
        type: pointer('vo_data')

      - size: 60

      - id: audio_buff
        type: u1
        repeat: expr
        repeat-expr: 49152

      - id: tag_inter_datap
        type: pointer('data')

      - id: video_dec_th
        type: s4

      - id: default_th
        type: s4

      - size: 52

      - id: def_stack
        type: s1
        repeat: expr
        repeat-expr: 2048

      - id: video_dec_stack
        type: s1
        repeat: expr
        repeat-expr: 16384

      - id: db
        type: sce_gs_dbuff

      - size: 16

  pss_message_time:
    seq:
      - id: start
        type: u2

      - id: end
        type: u2

  pss_subtitle_ctrl:
    seq:
      - id: msg_start
        type: s4

      - id: msg_no
        type: s4

      - id: msg_bufp
        type: pointer('data')

      - id: adr_msg_time
        type: pointer('pss_message_time')

  load_bg_common_info_t:
    seq:
      - id: glb_crd
        type: s4

      - id: px
        type: f4

      - id: pz
        type: f4

      - id: fcx
        type: f4

      - id: fcz
        type: f4

      - id: icx
        type: s4

      - id: icz
        type: s4

      - id: minx
        type: s4

      - id: minz
        type: s4

      - id: outdoor
        type: s4

      - id: room_id
        type: s4

      - id: block_id
        type: s4
        repeat: expr
        repeat-expr: 4

      - id: around_id
        type: s4
        repeat: expr
        repeat-expr: 25

      - id: unit
        type: s4

      - id: load
        type: s4

      - id: need
        type: s4

      - id: lock
        type: s4

      - id: miss
        type: s4

      - id: hide_map
        type: s4

      - id: hide_map_request
        type: s4

  u16:
    seq:
      - id: bytes
        size: 16

  pointer:
    params:
      - id: to
        type: str

    seq:
      - id: address
        type: u4


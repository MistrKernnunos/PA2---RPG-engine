//
// Created by machavi on 6/7/21.
//

#include "CPlayerCreator.h"

CPlayerCreator::CPlayerCreator() {
  m_Player = CPlayer::Create();
  m_Stats.emplace("attack", m_Player->m_AttackPower);
}

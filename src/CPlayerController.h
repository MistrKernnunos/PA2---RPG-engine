//
// Created by machavi on 6/2/21.
//
#pragma once
#include <memory>
#include <vector>

#include "CControler.h"
#include "CInterface.h"
#include "CInventory.h"
#include "CWeapon.h"
class CPlayer;

class CPlayerController : public CControler {
 public:
  CPlayerController() = default;

  /**
   * function to start control player
   * @param toControl player to control
   * @return false if player wants to end the game
   */
  bool Control(CEntity& toControl) override;
  static std::shared_ptr<CControler> Create();

 private:
  /**
   * returns index of entity to attack
   * @param toControl player  that is under control
   * @param entitiesToAttack vector of entities to attack
   * @return index of entity to attack
   */
  size_t chooseEntityToAttack(CEntity& toControl, std::vector<std::shared_ptr<CEntity>>& entitiesToAttack);
  /**
   * shows user possible actions and the user can choose
   * @param toControl player  that is under control
   * @return what has the user chosen
   */
  int showActions(CEntity& toControl);
  /**
   * asks player where to move and then tries to move there
   * @param toControl player  that is under control
   */
  void move(CEntity& toControl);
  /**
   * asks player who to attack with what
   * @param toControl player  that is under control
   */
  void attack(CEntity& toControl);
  /**
   * gives weapons to choose
   * @param toControl player  that is under control
   * @return index of the chosen weapon
   */
  size_t chooseWeapon(CEntity& toControl);
  /**
   * function to control inventory
   * @param toControl player  that is under control
   */
  void inventory(CEntity& toControl);
  /**
   * gives player choice of items of type
   * @param toControl player  that is under control
   * @param type type of the items
   * @return
   */
  size_t chooseItem(CEntity& toControl, invType type);
  /**
   * tries to use item on index
   * @param toControl player  that is under control
   * @param index of the item to use
   * @return true if successful
   */
  bool useItem(CEntity& toControl, size_t index);
  /**
   * facilitates looting other entities
   * @param toControl player  that is under control
   */
  void loot(CEntity& toControl);
  /**
   * gives player choice of entities which are lootable
   * @param entities vector of lootable entities
   * @param toControl player  that is under control
   * @return index of chosen entity
   */
  size_t chooseEntityToLoot(std::vector<std::shared_ptr<CEntity>>& entities, CEntity& toControl);
  /**
   * remove item from inventory
   * @param toControl entity to control
   * @param index of item to drop
   */
  void dropItem(CEntity& toControl, size_t index);
};

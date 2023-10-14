#ifndef SPEAR_POWERUP_HPP
#define SPEAR_POWERUP_HPP
class SpearPowerup;
#include "AlwaysActivePowerup.hpp"
#include "../../entities/Player.hpp"
#include "../../util/Position.hpp"
#include "../../util/RenderableList.hpp"

class SpearPowerup : public AlwaysActivePowerup {
protected:
	int durability, maxDurability;
	void killEnemiesAt(Player *player, Position pos);
public:
	SpearPowerup(Position position, int maxDurability);
	void tick(Player *player);
	void onPickUp(Player *player);
	void getName(char name[], const int length);
	void getRenderInfo(char titleInfo[], const int length);
	void getPlayerRenderInfo(Player *player, RenderableList *list);
};

#endif /* SPEAR_POWERUP_HPP */

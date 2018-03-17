#ifndef P3DDATA_GAMEDATA_HPP
#define P3DDATA_GAMEDATA_HPP

#include <pioneers3d/data/TextureType.hpp>
#include <pioneers3d/data/BoardData.hpp>
#include <pioneers3d/data/PlayerData.hpp>
#include <stdint.h>
#include <vector>
#include <assert.h>

namespace pioneers3d
{

enum class eGameState : uint32_t
{
	IDLE = 0,
	GAME_MENU,
	GAME_INIT_PLAYER,
	GAME_INIT_BOARD,
	GAME_DICE,
	GAME_PLACE_ROBBER,
	GAME_PLACE_FIRST_ROAD,
	GAME_PLACE_FIRST_SETTLEMENT,
	GAME_PLACE_SECOND_ROAD,
	GAME_PLACE_SECOND_SETTLEMENT,
	GAME_LOOP,
	GAME_END,
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	COUNT,
	// FORCE32BIT = 0xffffffff
};

enum class eGameType : uint32_t
{
	GT_STANDARD = 0,
	GT_EXT_FISHER = 1,
	GT_EXT_PIRATES = 2,
	GT_EXT_THIEFS = 4,
	GT_EXT_CARDS = 8,
	// GT_FORCE32BIT = 0xffffffff
};

class Game
{
public:
	Game( irr::IrrlichtDevice * device );
	~Game();
	irr::IrrlichtDevice* getDevice() { return m_Device; }
	uint32_t getTextureCount() const { return m_Textures.size(); }
	irr::video::ITexture* getTexture( int i ) { return m_Textures[ i ]; }
	eGameType getGameType() const { return m_GameType; }
	eGameState getGameState() const { return m_GameState; }
	BoardData * getBoard() const { return m_Board; }
	uint32_t getCurrentPlayer() const { return m_CurrentPlayer; }
	uint32_t getPlayerCount() const { return m_Players.size(); }
	PlayerData* getPlayer( uint32_t i ) const { assert( i < getPlayerCount() ); return m_Players[ i ]; }

	void setGameType( eGameType type ) { m_GameType = type; }
	void setGameState( eGameState state ) { m_GameState = state; }

	void resetGame();
	void startGame();
	void saveGame();
	void loadGame();

	// void createGame();
	// void editGame();

private:
	irr::IrrlichtDevice * m_Device;
	std::vector< irr::video::ITexture* > m_Textures;
	eGameType m_GameType;
	eGameState m_GameState;
	BoardData * m_Board;
	uint32_t m_CurrentPlayer;
	std::vector< PlayerData* > m_Players;
};

} // end namespace pioneers3d

#endif // P3DDATA_GAMEDATA_HPP

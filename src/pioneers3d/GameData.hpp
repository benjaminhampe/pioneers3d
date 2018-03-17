#ifndef PIONEERS3D_GAME_DATA_HPP
#define PIONEERS3D_GAME_DATA_HPP

#include <pioneers3d/BoardData.hpp>
#include <pioneers3d/PlayerData.hpp>
#include <pioneers3d/GameType.hpp>

namespace pioneers3d {

class GameData
{
public:
	GameData();
	~GameData();
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

#endif // PIONEERS3D_GAME_DATA_HPP

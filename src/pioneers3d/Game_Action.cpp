#include "Game_Action.hpp"

#include <pioneers3d/Game_Bank.hpp>
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Player.hpp>
#include <pioneers3d/Game_UI.hpp>
#include <pioneers3d/Game_Chat.hpp>

#define PRINT_FUNCTION { std::cout << __FUNCTION__ << ":" << __LINE__ << "()\n"; }

//void Action_Dice( Game_t* game );
//void Action_Bank( Game_t* game );
//void Action_Trade( Game_t* game );
//void Action_BuyEventCard( Game_t* game );
//void Action_BuyRoad( Game_t* game );
//void Action_BuySettlement( Game_t* game );
//void Action_BuyCity( Game_t* game );
//void Action_EndTurn( Game_t* game );
//void Action_PlayEventCard( Game_t* game );
//void Action_PlaceRobber( Game_t* game );
//void Action_PlaceRoad( Game_t* game );
//void Action_PlaceSettlement( Game_t* game );
//void Action_PlaceCity( Game_t* game );
//void Action_Win( Game_t* game );

namespace pioneers3d {

void Action_Dice( Game_t* game )
{
    PRINT_FUNCTION
    setPlayerActionEnabled( game, getCurrentPlayer( game ), eAction::ENDTURN, true );
    setPlayerActionEnabled( game, getCurrentPlayer( game ), eAction::DICE, false );
    ActionUI_update( game );

    setWindowVisible( game, eWindow::DICE, true );
    game->Dice.A = rand() % 6 + 1;
    game->Dice.B = rand() % 6 + 1;
    game->UI.Dice.A->setImage( Game_getDiceTexture( game, game->Dice.A ) );
    game->UI.Dice.B->setImage( Game_getDiceTexture( game, game->Dice.B ) );

    int dice = game->Dice.sum();
    int playerIndex = game->Player;
    uint32_t playerColor = getPlayerColor( game, playerIndex );
    std::string playerName = getPlayerName( game, playerIndex );

    std::stringstream s; s << "Player dice " << dice << " = (" << game->Dice.A << " + " << game->Dice.B << " )";
    Chat_addItem( game, playerIndex, playerName, playerColor, s.str() );

    if ( dice == 7 )
    {
        Action_PlaceRobber( game );
        return;
    }

    // Collect ressource cards
    Bank_t bank;
    Bank_clear( bank );

    for ( uint32_t i = 0; i < game->Tiles.size(); ++i )
    {
        Tile_t & tile = game->Tiles[ i ];
        if ( tile.DiceValue == dice )
        {
            std::cout << __FUNCTION__ << " :: [Ok] Found Tile with diceValue(" << dice << ") that has type(" << tile.Type.toString() << ")\n";
            Bank_addRessource( bank, tile.Type );
        }
    }

    std::cout << __FUNCTION__ << " :: [Ok] " << Bank_toString( bank ) << "\n";

}

void Action_EndTurn( Game_t* game )
{
    PRINT_FUNCTION
    int32_t playerIndex = game->Player + 1;
    int32_t playerCount = game->Players.size();
    if ( playerIndex >= playerCount ) playerIndex = 0;
    game->Player = playerIndex;

    setPlayerActionEnabled( game, game->Player, eAction::DICE, true );
    setPlayerActionEnabled( game, game->Player, eAction::ENDTURN, false );
    PlayerUI_update( game );
    ActionUI_update( game );
    setWindowVisible( game, eWindow::DICE, false );

    game->RoundCounter++;
}

void Action_Bank( Game_t* game )
{
    PRINT_FUNCTION
    game->UI.Bank.Window->setVisible( true );
    //game->UI.Bank.Window->getEnvironment()->getRootGUIElement()->bringToFront( game->UI.Bank.Window );
}

void Action_Trade( Game_t* game )
{
    PRINT_FUNCTION
}

void Action_BuyEventCard( Game_t* game )
{
    PRINT_FUNCTION
}

void Action_BuyRoad( Game_t* game )
{
    PRINT_FUNCTION
}

void Action_BuySettlement( Game_t* game )
{
    PRINT_FUNCTION
}

void Action_BuyCity( Game_t* game )
{
    PRINT_FUNCTION
}

void Action_PlaceRobber( Game_t * game )
{
    PRINT_FUNCTION
}

void Action_PlaceRoad( Game_t* game )
{
    PRINT_FUNCTION
}

void Action_PlaceSettlement( Game_t* game )
{
    PRINT_FUNCTION
}

void Action_PlaceCity( Game_t* game )
{
    PRINT_FUNCTION
}

/*
uint32_t Player_getActionMask( Game_t* game, int player )
{
    if ( !game )
    {
        return 0x00000000;
    }
    if ( player >= game->Players.size() )
    {
        return 0x00000000;
    }
    return game->Players[ player].ActionMask;
}

uint32_t Player_setActionMask( Game_t* game, int player, uint32_t actionMask )
{
    if ( !game )
    {
        return 0x00000000;
    }
    if ( player >= game->Players.size() )
    {
        return 0x00000000;
    }
    game->Players[ player].ActionMask = actionMask;
}
*/

} // end namespace pioneers3d

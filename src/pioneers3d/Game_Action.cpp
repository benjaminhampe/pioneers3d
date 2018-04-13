#include "Game_Action.hpp"

#include <pioneers3d/Game_Bank.hpp>
#include <pioneers3d/Game_Texture.hpp>
#include <pioneers3d/Game_Player.hpp>
#include <pioneers3d/gui/UI_Player.hpp>
#include <pioneers3d/gui/UI_Action.hpp>

#define PRINT_FUNCTION_NAME { std::cout << __FUNCTION__ << ":" << __LINE__ << "()\n"; }

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
    PRINT_FUNCTION_NAME
    game->Dice.A = rand() % 6 + 1;
    game->Dice.B = rand() % 6 + 1;
    int dice = game->Dice.A + game->Dice.B;
    if ( dice == 7 )
    {
        Action_PlaceRobber( game );
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

    game->UI.Dice.A->setImage( Game_getDiceTexture( game, game->Dice.A ) );
    game->UI.Dice.B->setImage( Game_getDiceTexture( game, game->Dice.B ) );

    std::cout << __FUNCTION__ << " :: [Ok] " << Bank_toString( bank ) << "\n";

}

void Action_EndTurn( Game_t* game )
{
    PRINT_FUNCTION_NAME
    int32_t playerIndex = game->Player + 1;
    int32_t playerCount = game->Players.size();
    if ( playerIndex >= playerCount ) playerIndex = 0;
    game->Player = playerIndex;
    PlayerUI_update( game );
    ActionUI_update( game );
}

void Action_Bank( Game_t* game )
{
    PRINT_FUNCTION_NAME
    game->UI.Bank.Window->setVisible( true );
    //game->UI.Bank.Window->getEnvironment()->getRootGUIElement()->bringToFront( game->UI.Bank.Window );
}

void Action_Trade( Game_t* game )
{
    PRINT_FUNCTION_NAME
}

void Action_BuyEventCard( Game_t* game )
{
    PRINT_FUNCTION_NAME
}

void Action_BuyRoad( Game_t* game )
{
    PRINT_FUNCTION_NAME
}

void Action_BuySettlement( Game_t* game )
{
    PRINT_FUNCTION_NAME
}

void Action_BuyCity( Game_t* game )
{
    PRINT_FUNCTION_NAME
}

void Action_PlaceRobber( Game_t * game )
{
    PRINT_FUNCTION_NAME
}

void Action_PlaceRoad( Game_t* game )
{
    PRINT_FUNCTION_NAME
}

void Action_PlaceSettlement( Game_t* game )
{
    PRINT_FUNCTION_NAME
}

void Action_PlaceCity( Game_t* game )
{
    PRINT_FUNCTION_NAME
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

#include "LobbyScene.hpp"

/**
 * @brief Lobby scene join server sequence
 */

namespace spnet {

/**
 * @brief Text-based keyboard until layout is created
 */
static const f32 scKeyboardLeft = 100.0f;
static const f32 scKeyboardTop = 100.0f;
static const f32 scKeyboardKeySize = 50.0f;
static const s32 scKeyboardNumKeys = 12;
static s32 sKeyboardCurrChar = 0;
static char sKeyboardBuffer[scKeyboardNumKeys] = {};

void LobbyScene::CalcSeqJoinServer() {}

void LobbyScene::DrawSeqJoinServer() {
    for (int i = 0; i < scKeyboardNumKeys; i++) {
        Printf(100.0f, 100.0f, 2.0f, true, mato::scColorWhite, "A");
    }
}

} // namespace spnet
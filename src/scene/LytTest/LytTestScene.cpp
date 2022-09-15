#include "LytTestScene.hpp"

namespace spnet {

LytTestScene::LytTestScene()
    : mSocket(Socket::SOCK_STREAM),
      mPort(12345),
      mClient(NULL),
      mLayout(NULL) {}

LytTestScene::~LytTestScene() {
    mSocket.Disconnect();
    delete mClient;
    delete mLayout;
}

void LytTestScene::OnConfigure() {
    MATO_LOG("[Layout Test]");

    // Start server
    MATO_ASSERT(mSocket.Bind(mPort));
    MATO_ASSERT(mSocket.Listen());

    // Print server info to console
    const u32 ip = mSocket.GetHostIP();
    const u8* oct = reinterpret_cast<const u8*>(&ip);
    MATO_LOG_EX("Listening on %d.%d.%d.%d, port %d", oct[0], oct[1], oct[2],
                oct[3], mPort);
}

void LytTestScene::OnLoadResource() {}

void LytTestScene::OnReset() {}

void LytTestScene::OnCalculate() {
    // Accept incoming connection
    if (mClient == NULL) {
        mClient = mSocket.Accept();
    }
}

void LytTestScene::OnExit() {}

void LytTestScene::OnUserDraw() {}

} // namespace spnet
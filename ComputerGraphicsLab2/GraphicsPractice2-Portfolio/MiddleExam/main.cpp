#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <SDL2/SDL.h>
#include <iostream>

class MiddleExamFrameListener : public Ogre::FrameListener, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* playerNode;
    Ogre::SceneNode* aiNode;
    Ogre::SceneNode* ballNode;

    bool spacePressed;
    Ogre::Vector3 ballDirection;
public:
    MiddleExamFrameListener(Ogre::SceneNode* player, Ogre::SceneNode* ai, Ogre::SceneNode* ball)
        : playerNode(player), aiNode(ai), ballNode(ball), spacePressed(false), ballDirection(1, 1, 0) {}

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
        {
            Ogre::Root::getSingleton().queueEndRendering();
        }
        else if (evt.keysym.sym == OgreBites::SDLK_SPACE)
        {
            spacePressed = true; // 스페이스바가 눌렸음을 표시
        }
        else if (evt.keysym.sym == OgreBites::SDLK_UP)
        {
            playerNode->translate(0, 10, 0); // 플레이어를 위로 이동
        }
        else if (evt.keysym.sym == OgreBites::SDLK_DOWN)
        {
            playerNode->translate(0, -10, 0); // 플레이어를 아래로 이동
        }
        return true;
    }

    bool keyReleased(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == OgreBites::SDLK_SPACE)
        {
            spacePressed = false; // 스페이스바가 눌림 상태 해제
        }
        return true;
    }

    bool frameRenderingQueued(const Ogre::FrameEvent& evt) override
    {
        // 공을 일정 속도로 이동시킴
        ballNode->translate(ballDirection * 50 * evt.timeSinceLastFrame);

        // AI 노드가 공의 Y 위치에 맞추도록 이동
        Ogre::Vector3 ballPos = ballNode->getPosition();
        Ogre::Vector3 aiPos = aiNode->getPosition();
        if (aiPos.y < ballPos.y)
        {
            aiNode->translate(0, 10, 0);
        }
        else if (aiPos.y > ballPos.y)
        {
            aiNode->translate(0, -10, 0);
        }

        // 공이 화면 밖으로 나가지 않도록 처리
        if (ballPos.y > 50 || ballPos.y < -50)
        {
            ballDirection.y = -ballDirection.y; // 위아래 경계에서 반전
        }

        // 공과 플레이어의 충돌 체크
        Ogre::Vector3 playerPos = playerNode->getPosition();
        Ogre::Vector3 playerSize = playerNode->getScale() * 50; // 플레이어 노드의 크기 고려
        if (ballPos.x < playerPos.x + playerSize.x && ballPos.x > playerPos.x && ballPos.y > playerPos.y - playerSize.y && ballPos.y < playerPos.y + playerSize.y)
        {
            if (spacePressed) {
                ballDirection.x = -ballDirection.x; // 플레이어와 충돌 시 공의 방향을 반전시킴
            }
        }

        // 공과 AI 노드의 충돌 체크
        Ogre::Vector3 aiSize = aiNode->getScale() * 50; // AI 노드의 크기 고려
        if (ballPos.x > aiPos.x - aiSize.x && ballPos.x < aiPos.x && ballPos.y > aiPos.y - aiSize.y && ballPos.y < aiPos.y + aiSize.y)
        {
            ballDirection.x = -ballDirection.x; // AI 노드와 충돌 시 공의 방향을 반전시킴
        }

        return true;
    }
};


class MiddleExam : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* ballNode;
    Ogre::SceneNode* playerNode;
    Ogre::SceneNode* aiNode;
public:
    MiddleExam() : OgreBites::ApplicationContext("MiddleExam"), ballNode(nullptr) {}

    void setup() override
    {
        // 기본 설정 초기화
        OgreBites::ApplicationContext::setup();

        // Root, SceneManager 및 RenderWindow 가져오기
        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // 카메라 설정
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 59, 322);
        camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
        camNode->attachObject(cam);

        // Viewport에 카메라 추가
        getRenderWindow()->addViewport(cam);

        scnMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
  
        // 조명 추가
        Ogre::Light* light = scnMgr->createLight("Light");
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        //light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 0.0f));

        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(20, 80, 50);
        lightNode->attachObject(light);

 
        Ogre::Entity* ballEnt = scnMgr->createEntity("MySphere", Ogre::SceneManager::PT_SPHERE);
        ballEnt->setMaterialName("Examples/TextureEffect2");
        ballNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        ballNode->setPosition(0, 0, 0);
        ballNode->setScale(0.1f, 0.1f, 0.1f);
        ballNode->attachObject(ballEnt);

        Ogre::Entity* playerEnt = scnMgr->createEntity("PlayerNinja", "ninja.mesh");
        playerEnt->setMaterialName("MyMaterial10");
        playerNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        playerNode->yaw(Ogre::Degree(-90)); // 플레이어의 방향 설정
        playerNode->setPosition(-100, 0, 0);
        playerNode->setScale(0.5f, 0.05f, 0.5f);
        playerNode->attachObject(playerEnt);

        Ogre::Entity* aiEnt = scnMgr->createEntity("AINinja", "ninja.mesh");
        aiEnt->setMaterialName("MyMaterial10");
        aiNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        aiNode->yaw(Ogre::Degree(90)); // AI의 방향 설정
        aiNode->setPosition(100, 0, 0);
        aiNode->setScale(0.5f, 0.05f, 0.5f);
        aiNode->attachObject(aiEnt);

        // 랜덤 시드 초기화
        std::srand(std::time(nullptr));

        // 프레임 리스너 및 입력 리스너 추가
        MiddleExamFrameListener* frameListener = new MiddleExamFrameListener(playerNode, aiNode, ballNode);
        root->addFrameListener(frameListener);
        addInputListener(frameListener);
    }
};

int main(int argc, char** argv)
{
    try {
        MiddleExam app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (Ogre::Exception& e) {
        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
    }
    return 0;
}

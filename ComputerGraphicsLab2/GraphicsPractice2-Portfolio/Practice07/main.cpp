//#include <Ogre.h>
//#include <OgreApplicationContext.h>
//#include <OgreInput.h>
//#include <OgreRTShaderSystem.h>
//#include <SDL2/SDL.h>
//
//class Practice7FrameListener : public Ogre::FrameListener
//{
//private:
//    Ogre::SceneNode* _node;
//    SDL_Event _event;
//    bool _isJumping;
//    float _jumpSpeed;
//    float _gravity;
//
//public:
//    Practice7FrameListener(Ogre::SceneNode* node)
//        : _node(node), _isJumping(false), _jumpSpeed(50.0f), _gravity(9.8f) {}
//
//    bool frameStarted(const Ogre::FrameEvent& evt) override
//    {
//        //while (SDL_PollEvent(&_event))
//        //{
//        //    if (_event.type == SDL_QUIT)
//        //    {
//        //        return false;
//        //    }
//        //    if (_event.type == SDL_KEYDOWN)
//        //    {
//        //        if (_event.key.keysym.sym == SDLK_ESCAPE)
//        //        {
//        //            return false;
//        //        }
//        //        else if (_event.key.keysym.sym == SDLK_SPACE && !_isJumping)
//        //        {
//        //            _isJumping = true;
//        //        }
//        //    }
//        //}
//
//        //if (_isJumping)
//        //{
//        //    static float verticalSpeed = _jumpSpeed;
//        //    _node->translate(0, verticalSpeed * evt.timeSinceLastFrame, 0);
//
//        //    verticalSpeed -= _gravity * evt.timeSinceLastFrame;
//
//        //    if (_node->getPosition().y <= 20.0f) // Assume 20 is the ground level
//        //    {
//        //        _node->setPosition(_node->getPosition().x, 20.0f, _node->getPosition().z);
//        //        _isJumping = false;
//        //        verticalSpeed = _jumpSpeed;
//        //    }
//        //}
//
//          Ogre::Vector3 translate(0, 0, 0);
//
//        while (SDL_PollEvent(&_event))
//        {
//            if (_event.type == SDL_KEYDOWN)
//            {
//                if (_event.key.keysym.sym == SDLK_w)
//                {
//                    translate += Ogre::Vector3(10, 0, 0);
//                }
//            }
//            if (_event.type == SDL_QUIT)
//            {
//                return false;
//            }
//        }
//        _node->translate(translate * evt.timeSinceLastFrame);
//        return true;
//    }
//};
//
//class Practice7 : public OgreBites::ApplicationContext
//{
//private:
//    Ogre::SceneNode* _SinbadNode;
//public:
//    Practice7()
//        : OgreBites::ApplicationContext("Practice7"), _SinbadNode(nullptr) {}
//
//    void setup() override
//    {
//        OgreBites::ApplicationContext::setup();
//
//        // SDL 초기화
//        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
//        {
//            Ogre::LogManager::getSingleton().logMessage("Could not initialize SDL.");
//            return;
//        }
//
//        // Root, SceneManager 및 RenderWindow 가져오기
//        Ogre::Root* root = getRoot();
//        Ogre::SceneManager* scnMgr = root->createSceneManager();
//
//        // RTShader 시스템 초기화
//        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
//        shadergen->addSceneManager(scnMgr);
//
//        // 카메라 설정
//        Ogre::Camera* cam = scnMgr->createCamera("myCam");
//        cam->setNearClipDistance(5);
//        cam->setAutoAspectRatio(true);
//        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        camNode->setPosition(0, 100, 200);
//        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
//        camNode->attachObject(cam);
//
//        // Viewport에 카메라 추가
//        getRenderWindow()->addViewport(cam);
//
//        // 평면 생성
//        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
//        Ogre::MeshManager::getSingleton().createPlane("plane",
//            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
//            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
//
//        Ogre::Entity* planeEntity = scnMgr->createEntity("plane");
//        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(planeEntity);
//        planeEntity->setMaterialName("Examples/BeachStones");
//
//        // 조명 추가
//        Ogre::Light* light = scnMgr->createLight("Light");
//        light->setType(Ogre::Light::LT_DIRECTIONAL);
//        light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 0.0f));
//
//        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        lightNode->setPosition(0, 20, 0);
//        lightNode->setDirection(Ogre::Vector3(0, -1, -1));
//        lightNode->attachObject(light);
//
//        Ogre::Light* light1 = scnMgr->createLight("Light1");
//        light1->setType(Ogre::Light::LT_POINT);
//        light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
//        light1->setSpotlightInnerAngle(Ogre::Degree(5.0f));
//        light1->setSpotlightOuterAngle(Ogre::Degree(45.0f));
//        light1->setSpotlightFalloff(0.0f);
//        light1->setDiffuseColour(Ogre::ColourValue(0.0f, 1.0f, 0.0f));
//
//        Ogre::SceneNode* lightNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
//        lightNode2->setPosition(0, 20, 0);
//        lightNode2->attachObject(light1);
//
//        // Sinbad 엔티티 추가
//        _SinbadNode = scnMgr->createSceneNode("Node1");
//        scnMgr->getRootSceneNode()->addChild(_SinbadNode);
//
//        Ogre::Entity* Sinbad = scnMgr->createEntity("Sinbad", "Sinbad.mesh");
//        _SinbadNode = _SinbadNode->createChildSceneNode("SinbadNode");
//        _SinbadNode->setScale(3.0f, 3.0f, 3.0f);
//        _SinbadNode->setPosition(Ogre::Vector3(0.0f, 20.0f, 0.0f));
//        _SinbadNode->attachObject(Sinbad);
//
//        // 그림자 설정
//        scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
//        scnMgr->setShadowTextureSize(1024);
//        scnMgr->setShadowTextureCount(1);
//
//        // 프레임 리스너 추가
//        Ogre::FrameListener* frameListener = new Practice7FrameListener(_SinbadNode);
//        root->addFrameListener(frameListener);
//    }
//
//    void shutdown() override
//    {
//        SDL_Quit();
//        OgreBites::ApplicationContext::shutdown();
//    }
//};
//
//int main(int argc, char** argv)
//{
//    Practice7 app;
//    app.initApp();
//    app.getRoot()->startRendering();
//    app.closeApp();
//    return 0;
//}
//



//#include <Ogre.h>
//#include <OgreApplicationContext.h>
//#include <OgreInput.h>
//#include <OgreRTShaderSystem.h>
//#include <SDL2/SDL.h>
//
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include <queue>
//#include <iostream>
//
//class EventQueue {
//private:
//    std::queue<SDL_Event> queue;
//    std::mutex mtx;
//    std::condition_variable cv;
//
//public:
//    void push(const SDL_Event& event) {
//        std::lock_guard<std::mutex> lock(mtx);
//        queue.push(event);
//        cv.notify_all();
//    }
//
//    bool pop(SDL_Event& event) {
//        std::unique_lock<std::mutex> lock(mtx);
//        if (queue.empty()) return false;
//        event = queue.front();
//        queue.pop();
//        return true;
//    }
//
//    void wait() {
//        std::unique_lock<std::mutex> lock(mtx);
//        cv.wait(lock, [this] { return !queue.empty(); });
//    }
//};
//
//EventQueue eventQueue;
//
//class Practice7FrameListener : public Ogre::FrameListener
//{
//private:
//    Ogre::SceneNode* _node;
//    bool _isJumping;
//    float _jumpSpeed;
//    float _gravity;
//
//public:
//    Practice7FrameListener(Ogre::SceneNode* node)
//        : _node(node), _isJumping(false), _jumpSpeed(50.0f), _gravity(9.8f) {}
//
//    bool frameStarted(const Ogre::FrameEvent& evt) override
//    {
//        SDL_Event event;
//        while (eventQueue.pop(event))
//        {
//            if (event.type == SDL_KEYDOWN)
//            {
//                if (event.key.keysym.sym == SDLK_w)
//                {
//                    _node->translate(10 * evt.timeSinceLastFrame, 0, 0);
//                }
//                else if (event.key.keysym.sym == SDLK_ESCAPE)
//                {
//                    return false;
//                }
//                else if (event.key.keysym.sym == SDLK_SPACE && !_isJumping)
//                {
//                    _isJumping = true;
//                }
//            }
//        }
//
//        if (_isJumping)
//        {
//            static float verticalSpeed = _jumpSpeed;
//            _node->translate(0, verticalSpeed * evt.timeSinceLastFrame, 0);
//
//            verticalSpeed -= _gravity * evt.timeSinceLastFrame;
//
//            if (_node->getPosition().y <= 20.0f) // Assume 20 is the ground level
//            {
//                _node->setPosition(_node->getPosition().x, 20.0f, _node->getPosition().z);
//                _isJumping = false;
//                verticalSpeed = _jumpSpeed;
//            }
//        }
//
//        return true;
//    }
//};
//class Practice7 : public OgreBites::ApplicationContext
//{
//private:
//    Ogre::SceneNode* _SinbadNode;
//    std::thread keyboardThread;
//    bool running;
//
//    void pollKeyboardEvents() {
//        while (running) {
//            SDL_Event event;
//            while (SDL_PollEvent(&event)) {
//
//                std::cerr << "key down\n";
//
//                if (event.type == SDL_KEYDOWN) {
//                    eventQueue.push(event);
//                }
//                if (event.type == SDL_QUIT) {
//                    running = false;
//                    return;
//                }
//            }
//            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // To prevent busy waiting
//        }
//    }
//
//public:
//    Practice7()
//        : OgreBites::ApplicationContext("Practice7"), _SinbadNode(nullptr), running(true) {}
//
//    void setup() override
//    {
//        OgreBites::ApplicationContext::setup();
//
//        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
//        {
//            Ogre::LogManager::getSingleton().logMessage("Could not initialize SDL.");
//            return;
//        }
//
//        Ogre::Root* root = getRoot();
//        Ogre::SceneManager* scnMgr = root->createSceneManager();
//
//        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
//        shadergen->addSceneManager(scnMgr);
//
//        Ogre::Camera* cam = scnMgr->createCamera("myCam");
//        cam->setNearClipDistance(5);
//        cam->setAutoAspectRatio(true);
//        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        camNode->setPosition(0, 100, 200);
//        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
//        camNode->attachObject(cam);
//
//        getRenderWindow()->addViewport(cam);
//
//        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
//        Ogre::MeshManager::getSingleton().createPlane("plane",
//            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
//            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
//
//        Ogre::Entity* planeEntity = scnMgr->createEntity("plane");
//        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(planeEntity);
//        planeEntity->setMaterialName("Examples/BeachStones");
//
//        Ogre::Light* light = scnMgr->createLight("Light");
//        light->setType(Ogre::Light::LT_DIRECTIONAL);
//        light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 0.0f));
//
//        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        lightNode->setPosition(0, 20, 0);
//        lightNode->setDirection(Ogre::Vector3(0, -1, -1));
//        lightNode->attachObject(light);
//
//        Ogre::Light* light1 = scnMgr->createLight("Light1");
//        light1->setType(Ogre::Light::LT_POINT);
//        light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
//        light1->setSpotlightInnerAngle(Ogre::Degree(5.0f));
//        light1->setSpotlightOuterAngle(Ogre::Degree(45.0f));
//        light1->setSpotlightFalloff(0.0f);
//        light1->setDiffuseColour(Ogre::ColourValue(0.0f, 1.0f, 0.0f));
//
//        Ogre::SceneNode* lightNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
//        lightNode2->setPosition(0, 20, 0);
//        lightNode2->attachObject(light1);
//
//        _SinbadNode = scnMgr->createSceneNode("Node1");
//        scnMgr->getRootSceneNode()->addChild(_SinbadNode);
//
//        Ogre::Entity* Sinbad = scnMgr->createEntity("Sinbad", "Sinbad.mesh");
//        _SinbadNode = _SinbadNode->createChildSceneNode("SinbadNode");
//        _SinbadNode->setScale(3.0f, 3.0f, 3.0f);
//        _SinbadNode->setPosition(Ogre::Vector3(0.0f, 20.0f, 0.0f));
//        _SinbadNode->attachObject(Sinbad);
//
//        scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
//        scnMgr->setShadowTextureSize(1024);
//        scnMgr->setShadowTextureCount(1);
//
//        Ogre::FrameListener* frameListener = new Practice7FrameListener(_SinbadNode);
//        root->addFrameListener(frameListener);
//
//        keyboardThread = std::thread(&Practice7::pollKeyboardEvents, this);
//    }
//
//    void shutdown() override
//    {
//        running = false;
//        keyboardThread.join();
//        SDL_Quit();
//        OgreBites::ApplicationContext::shutdown();
//    }
//};
//
//int main(int argc, char** argv)
//{
//    Practice7 app;
//    app.initApp();
//    app.getRoot()->startRendering();
//    app.closeApp();
//    return 0;
//}


#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <SDL2/SDL.h>



class Practice7FrameListener : public Ogre::FrameListener, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* _node;
    bool _isJumping;
    float _jumpSpeed;
    float _gravity;
    float _verticalSpeed;
    bool _moveForward, _moveBackward, _moveLeft, _moveRight;

public:
    Practice7FrameListener(Ogre::SceneNode* node)
        : _node(node), _isJumping(false), _jumpSpeed(50.0f), _gravity(9.8f), _verticalSpeed(0.0f),
        _moveForward(false), _moveBackward(false), _moveLeft(false), _moveRight(false) {}

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
        {
            return false; // 종료 신호
        }
        else if (evt.keysym.sym == OgreBites::SDLK_SPACE && !_isJumping)
        {
            _isJumping = true;
            _verticalSpeed = _jumpSpeed;
        }
        else if (evt.keysym.sym == SDLK_w)
        {
            _moveForward = true;
        }
        else if (evt.keysym.sym == SDLK_s)
        {
            _moveBackward = true;
        }
        else if (evt.keysym.sym == SDLK_a)
        {
            _moveLeft = true;
        }
        else if (evt.keysym.sym == SDLK_d)
        {
            _moveRight = true;
        }
        return true;
    }

    bool keyReleased(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == SDLK_w)
        {
            _moveForward = false;
        }
        else if (evt.keysym.sym == SDLK_s)
        {
            _moveBackward = false;
        }
        else if (evt.keysym.sym == SDLK_a)
        {
            _moveLeft = false;
        }
        else if (evt.keysym.sym == SDLK_d)
        {
            _moveRight = false;
        }
        return true;
    }

    bool frameStarted(const Ogre::FrameEvent& evt) override
    {
        Ogre::Vector3 translate(0, 0, 0);

        // 점프 처리
        if (_isJumping)
        {
            _node->translate(0, _verticalSpeed * evt.timeSinceLastFrame, 0);
            _verticalSpeed -= _gravity * evt.timeSinceLastFrame;

            if (_node->getPosition().y <= 20.0f) // Assume 20 is the ground level
            {
                _node->setPosition(_node->getPosition().x, 20.0f, _node->getPosition().z);
                _isJumping = false;
                _verticalSpeed = 0.0f;
            }
        }

        // 이동 처리
        if (_moveForward)
        {
            translate += Ogre::Vector3(0, 0, 10);
        }
        if (_moveBackward)
        {
            translate += Ogre::Vector3(0, 0, -10);
        }
        if (_moveLeft)
        {
            translate += Ogre::Vector3(-10, 0, 0);
        }
        if (_moveRight)
        {
            translate += Ogre::Vector3(10, 0, 0);
        }

        _node->translate(translate * evt.timeSinceLastFrame);

        return true;
    }
};


class Practice7 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* _SinbadNode;

public:
    Practice7()
        : OgreBites::ApplicationContext("Practice7"), _SinbadNode(nullptr) {}

    void setup() override
    {
        OgreBites::ApplicationContext::setup();

        // Root, SceneManager 및 RenderWindow 가져오기
        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();

        // RTShader 시스템 초기화
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // 카메라 설정
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 100, 200);
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
        camNode->attachObject(cam);

        // Viewport에 카메라 추가
        getRenderWindow()->addViewport(cam);

        // 평면 생성
        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
        Ogre::MeshManager::getSingleton().createPlane("plane",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        Ogre::Entity* planeEntity = scnMgr->createEntity("plane");
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(planeEntity);
        planeEntity->setMaterialName("Examples/BeachStones");

        // 조명 추가
        Ogre::Light* light = scnMgr->createLight("Light");
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        //light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 0.0f));

        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 20, 0);
        lightNode->setDirection(Ogre::Vector3(0, -1, -1));
        lightNode->attachObject(light);

        Ogre::Light* light1 = scnMgr->createLight("Light1");
        light1->setType(Ogre::Light::LT_POINT);
        light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
        light1->setSpotlightInnerAngle(Ogre::Degree(5.0f));
        light1->setSpotlightOuterAngle(Ogre::Degree(45.0f));
        light1->setSpotlightFalloff(0.0f);
        light1->setDiffuseColour(Ogre::ColourValue(0.0f, 1.0f, 0.0f));

        Ogre::SceneNode* lightNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode2->setPosition(0, 20, 0);
        lightNode2->attachObject(light1);

        // Sinbad 엔티티 추가
        _SinbadNode = scnMgr->createSceneNode("Node1");
        scnMgr->getRootSceneNode()->addChild(_SinbadNode);

        Ogre::Entity* Sinbad = scnMgr->createEntity("Sinbad", "Sinbad.mesh");
        _SinbadNode = _SinbadNode->createChildSceneNode("SinbadNode");
        _SinbadNode->setScale(3.0f, 3.0f, 3.0f);
        _SinbadNode->setPosition(Ogre::Vector3(0.0f, 20.0f, 0.0f));
        _SinbadNode->attachObject(Sinbad);

        // 그림자 설정
        scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
        scnMgr->setShadowTextureSize(1024);
        scnMgr->setShadowTextureCount(1);

        // 프레임 리스너 추가
        Practice7FrameListener* frameListener = new Practice7FrameListener(_SinbadNode);
        root->addFrameListener(frameListener);

        // 입력 리스너 추가
        addInputListener(frameListener);
    }
};

int main(int argc, char** argv)
{
    Practice7 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}

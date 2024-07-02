#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <SDL2/SDL.h>

class Practice8FrameListener : public Ogre::FrameListener, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* _camNode;
    float _movementspeed;
    bool _moveForward, _moveBackward, _moveLeft, _moveRight;
    Ogre::Vector3 _direction;

public:
    Practice8FrameListener(Ogre::SceneNode* camNode)
        : _camNode(camNode), _movementspeed(200.0f), _moveForward(false),
        _moveBackward(false), _moveLeft(false), _moveRight(false), _direction(Ogre::Vector3::ZERO) {}

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == SDLK_ESCAPE)
        {
            return false;
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

    bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override
    {
        float rotX = evt.xrel * -0.001f;
        float rotY = evt.yrel * -0.001f;

        _camNode->yaw(Ogre::Radian(rotX));
        _camNode->pitch(Ogre::Radian(rotY));

        return true;
    }

    bool frameStarted(const Ogre::FrameEvent& evt) override
    {
        _direction = Ogre::Vector3::ZERO;

        if (_moveForward)
        {
            _direction.z -= 1;
        }
        if (_moveBackward)
        {
            _direction.z += 1;
        }
        if (_moveLeft)
        {
            _direction.x -= 1;
        }
        if (_moveRight)
        {
            _direction.x += 1;
        }

        _camNode->translate(_direction * evt.timeSinceLastFrame * _movementspeed, Ogre::Node::TS_LOCAL);

        return true;
    }
};

class Practice8 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* _SinbadNode;

public:
    Practice8() : OgreBites::ApplicationContext("Practice8") {}

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

        // Add FrameListener
        Practice8FrameListener* frameListener = new Practice8FrameListener(camNode);
        root->addFrameListener(frameListener);
        addInputListener(frameListener);
    }
};

int main(int argc, char** argv)
{
    Practice8 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}

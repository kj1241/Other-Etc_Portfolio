#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <SDL2/SDL.h>

class Practice10FrameListener : public Ogre::FrameListener, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* _node;
    Ogre::Camera* _cam;
    Ogre::SceneNode* _camNode;
    Ogre::PolygonMode _PolyMode;
    float _movementspeed;
    bool _moveForward, _moveBackward, _moveLeft, _moveRight;
    bool _pressedBefore;
    Ogre::Entity* _ent;
    Ogre::AnimationState* _aniStateIdle;
    Ogre::AnimationState* _aniStateWalk;
    Ogre::AnimationState* _aniStateAttack;
    Ogre::Vector3 _translateVector;

public:
    Practice10FrameListener(Ogre::SceneNode* node, Ogre::Entity* ent, Ogre::SceneNode* camNode, Ogre::Camera* cam)
        : _node(node), _ent(ent), _camNode(camNode), _cam(cam), _movementspeed(200.0f), _pressedBefore(false),
        _PolyMode(Ogre::PolygonMode::PM_SOLID), _moveForward(false), _moveBackward(false),
        _moveLeft(false), _moveRight(false), _translateVector(Ogre::Vector3::ZERO)
    {
        _aniStateIdle = _ent->getAnimationState("IdleBase");
        _aniStateIdle->setEnabled(true);
        _aniStateIdle->setLoop(true);

        _aniStateWalk = _ent->getAnimationState("RunBase");
        _aniStateWalk->setEnabled(false);
        _aniStateWalk->setLoop(true);

        _aniStateAttack = _ent->getAnimationState("SliceVertical");
        _aniStateAttack->setEnabled(false);
        _aniStateAttack->setLoop(false);
    }

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == SDLK_ESCAPE)
        {
            return false;
        }
        if (evt.keysym.sym == SDLK_w)
        {
            _moveForward = true;
            changeAnimationState(_aniStateWalk);
        }
        else if (evt.keysym.sym == SDLK_s)
        {
            _moveBackward = true;
            changeAnimationState(_aniStateWalk);
        }
        else if (evt.keysym.sym == SDLK_a)
        {
            _moveLeft = true;
            changeAnimationState(_aniStateWalk);
        }
        else if (evt.keysym.sym == SDLK_d)
        {
            _moveRight = true;
            changeAnimationState(_aniStateWalk);
        }
        else if (evt.keysym.sym == SDLK_r && !_pressedBefore)
        {
            _pressedBefore = true;
            if (_PolyMode == Ogre::PolygonMode::PM_SOLID)
            {
                _PolyMode = Ogre::PolygonMode::PM_WIREFRAME;
            }
            else if (_PolyMode == Ogre::PolygonMode::PM_WIREFRAME)
            {
                _PolyMode = Ogre::PolygonMode::PM_POINTS;
            }
            else if (_PolyMode == Ogre::PolygonMode::PM_POINTS)
            {
                _PolyMode = Ogre::PolygonMode::PM_SOLID;
            }

            _cam->setPolygonMode(_PolyMode);
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
        else if (evt.keysym.sym == SDLK_r)
        {
            _pressedBefore = false;
        }

        if (!_moveForward && !_moveBackward && !_moveLeft && !_moveRight)
        {
            changeAnimationState(_aniStateIdle);
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

    bool mousePressed(const OgreBites::MouseButtonEvent& evt) override
    {
        if (evt.button == SDL_BUTTON_RIGHT)
        {
            changeAnimationState(_aniStateAttack);
        }
        return true;
    }

    bool frameStarted(const Ogre::FrameEvent& evt) override
    {
        _translateVector = Ogre::Vector3::ZERO;

        if (_moveForward)
        {
            _translateVector.z -= 1;
        }
        if (_moveBackward)
        {
            _translateVector.z += 1;
        }
        if (_moveLeft)
        {
            _translateVector.x -= 1;
        }
        if (_moveRight)
        {
            _translateVector.x += 1;
        }

        _node->translate(_translateVector * evt.timeSinceLastFrame * _movementspeed, Ogre::Node::TS_LOCAL);

        _aniStateIdle->addTime(evt.timeSinceLastFrame);
        _aniStateWalk->addTime(evt.timeSinceLastFrame);
        _aniStateAttack->addTime(evt.timeSinceLastFrame);

        return true;
    }

    void changeAnimationState(Ogre::AnimationState* newState)
    {
        _aniStateIdle->setEnabled(false);
        _aniStateWalk->setEnabled(false);
        _aniStateAttack->setEnabled(false);

        newState->setEnabled(true);
        newState->setTimePosition(0);
    }
};

class Practice10 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* _SinbadNode;
    Ogre::Entity* _SinbadEnt;

public:
    Practice10() : OgreBites::ApplicationContext("Practice10") {}

    void setup() override
    {
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();

        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);

        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->attachObject(cam);
        camNode->setPosition(0, 100, 200);
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);

        getRenderWindow()->addViewport(cam);

        Ogre::Light* light = scnMgr->createLight("MainLight");
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);
        lightNode->attachObject(light);

        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
        Ogre::MeshManager::getSingleton().createPlane(
            "plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        Ogre::Entity* ent = scnMgr->createEntity("LightPlaneEntity", "plane");
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
        ent->setMaterialName("Examples/BeachStones");

        _SinbadEnt = scnMgr->createEntity("Sinbad", "Sinbad.mesh");
        _SinbadNode = scnMgr->getRootSceneNode()->createChildSceneNode("SinbadNode");
        _SinbadNode->setScale(3.0f, 3.0f, 3.0f);
        _SinbadNode->setPosition(Ogre::Vector3(0.0f, 4.0f, 0.0f));
        _SinbadNode->attachObject(_SinbadEnt);

        scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
        scnMgr->setShadowTextureSize(1024);
        scnMgr->setShadowTextureCount(1);

        Practice10FrameListener* frameListener = new Practice10FrameListener(_SinbadNode, _SinbadEnt, camNode, cam);
        root->addFrameListener(frameListener);
        addInputListener(frameListener);
    }
};

int main(int argc, char** argv)
{
    Practice10 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
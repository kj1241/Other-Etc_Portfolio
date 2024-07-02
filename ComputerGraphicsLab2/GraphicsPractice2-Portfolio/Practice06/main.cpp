#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>

class Practice6FrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _node;
public:
    Practice6FrameListener(Ogre::SceneNode* node) : _node(node) {}

    bool frameStarted(const Ogre::FrameEvent& evt) override
    {
        _node->translate(Ogre::Vector3(10, 0, 0) * evt.timeSinceLastFrame);
        return true;
    }
};

class Practice6 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
private:
    Ogre::SceneNode* _SinbadNode;
public:
    Practice6() : OgreBites::ApplicationContext("Practice6"), _SinbadNode(nullptr) {}

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
        camNode->setPosition(0, 50, 150);  // 카메라를 더 멀리 설정
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);  // 평면 중심을 바라보도록 설정
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
        lightNode->setPosition(0, 20, 0);  // 조명을 카메라 근처에 위치
        lightNode->setDirection(Ogre::Vector3(0, -1, -1));
        lightNode->attachObject(light);

        Ogre::Light* light1 = scnMgr->createLight("Light1");
        light1->setType(Ogre::Light::LT_POINT);
        light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
        light1->setSpotlightInnerAngle(Ogre::Degree(5.0f));
        light1->setSpotlightOuterAngle(Ogre::Degree(45.0f));
        light1->setSpotlightFalloff(0.0f);
        //light1->setDiffuseColour(Ogre::ColourValue(0.0f, 1.0f, 0.0f));

        Ogre::SceneNode* lightNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode2->setPosition(0, 20, 0);  // 조명을 카메라 근처에 위치
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
        scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);  // 텍스처 기반 그림자 기술로 변경
        scnMgr->setShadowTextureSize(1024);  // 그림자 텍스처 크기 설정
        scnMgr->setShadowTextureCount(1);  // 그림자 텍스처 개수 설정

        // 프레임 리스너 추가
        Ogre::FrameListener* frameListener = new Practice6FrameListener(_SinbadNode);
        root->addFrameListener(frameListener);
    }
};

int main(int argc, char** argv)
{
    Practice6 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}

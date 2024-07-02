#include <Ogre.h>
#include <OgreApplicationContext.h>

class Practice5 : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    Practice5() : OgreBites::ApplicationContext("Practice5") {}

    void setup() override {
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        // 기본적인 Ogre3D 객체 설정
        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();

        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // 카메라 설정
        //Ogre::Camera* cam = scnMgr->createCamera("myCam");
        //cam->setNearClipDistance(5);
        //cam->setAutoAspectRatio(true);
        //Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        //camNode->setPosition(0, 0, 140);
        //camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
        //camNode->attachObject(cam);

        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 50, 150);  // 카메라를 더 멀리 설정
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);  // 평면 중심을 바라보도록 설정
        camNode->attachObject(cam);

        // 뷰포트 설정
        getRenderWindow()->addViewport(cam);

        // 조명 설정
        Ogre::Light* light = scnMgr->createLight("Light");
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 0.0f));

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

        // 평면 생성
        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
        Ogre::MeshManager::getSingleton().createPlane(
            "ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane, 1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        // 평면 엔티티 생성 및 텍스처 적용
        Ogre::Entity* groundEntity = scnMgr->createEntity("ground");
        groundEntity->setMaterialName("Examples/BeachStones"); // "Examples/Rockwall"은 샘플 텍스처 이름입니다.
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

        // Sinbad 모델 추가
        Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
        scnMgr->getRootSceneNode()->addChild(node);

        Ogre::Entity* Sinbad = scnMgr->createEntity("Sinbad", "Sinbad.mesh");
        node = node->createChildSceneNode("SinbadNode");
        node->setScale(3.0f, 3.0f, 3.0f);
        node->setPosition(Ogre::Vector3(0.0f, 20.0f, 0.0f));
        node->attachObject(Sinbad);

        // 그림자 설정
        scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);  // 텍스처 기반 그림자 기술로 변경
        scnMgr->setShadowTextureSize(1024);  // 그림자 텍스처 크기 설정
        scnMgr->setShadowTextureCount(1);  // 그림자 텍스처 개수 설정

    }
};

int main(int argc, char** argv)
{
    Practice5 app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}